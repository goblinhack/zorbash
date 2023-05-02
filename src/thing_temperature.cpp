//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

void Thing::temperature_tick(void)
{
  TRACE_NO_INDENT();

  int  location_temp     = 0;
  bool location_temp_set = false;

  //
  // Not sure what I should do with things like pillars and smoke. Do we want them
  // to change temperature? I guess if so, set an initial temp.
  //
  if (! initial_temperature_is_set()) {
    return;
  }

  //
  // Don't allow things inside chests to catch fire.
  //
  auto o_top = top_owner();
  if (o_top && ! o_top->initial_temperature_is_set()) {
    return;
  }

  if (is_ethereal()) {
    //
    // Ghosts don't burn or freeze.
    //
    return;
  }

  auto initial_temp = initial_temperature_get();
  auto current_temp = temperature_get();

  if (current_temp != initial_temp) {
    if (temperature_min_is_set()) {
      if (current_temp < temperature_min_get()) {
        dbg("Too cold (%d)", current_temp);
        TRACE_AND_INDENT();
        if (is_fire()) {
          dead("extinguished");
        } else {
          is_attacked_with_dmg_cold(this, this, abs((temperature_min_get() - current_temp) / 10));
        }
      }
    }

    if (temperature_max_is_set()) {
      if (current_temp > temperature_max_get()) {
        dbg("Too hot (%d)", current_temp);
        TRACE_AND_INDENT();
        is_attacked_with_dmg_heat(this, this, abs((current_temp - temperature_max_get()) / 10));
      }
    }

    temperature_set((initial_temperature_get() + (temperature_get() * 5)) / 6);
  }

  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_floor() || t->is_corridor()) {
      continue;
    }

    //
    // Do not count hidden (carried) items
    //
    if (t->is_hidden) {
      continue;
    }

    //
    // Without this check a player will heat themselves up ridiculously
    //
    if (t == this) {
      if (! is_frozen) {
        continue;
      }
    }

    //
    // Should "dead" fire skeletons cause fire damage to those standing on the same tile ?
    //
    if (t->is_dead) {
      continue;
    }

    //
    // If the player is standing in the same tile as a torch, don't burn them.
    // Same goes for things like treasure chests on the same tile as a torch.
    //
    if (t->is_torch()) {
      if (is_treasure_chest() || (o_top && o_top->is_treasure_chest())) {
        //
        // Don't ignite torches inside chests.
        //
        continue;
      } else if (is_combustible()) {
        //
        // But make exceptions for combustible things so that they will react to a flaming torch.
        //
      } else if (is_able_to_melt()) {
        //
        // Ice?
        //
      } else if (is_frozen) {
        //
        // Make another exception for frozen things so they can defrost.
        //
      } else {
        //
        // Ignore the torch.
        //
        continue;
      }
    }

    if (on_fire_anim_id() == t->id) {
      //
      // You "carry" fire when on fire.
      //
    } else if (t->is_fire()) {
      //
      // Even if the owner of the fire is dead...
      //
    } else {
      //
      // Ignore carried things
      //
      if (t->top_owner() == this) {
        continue;
      }

      //
      // If a bag, ignore the temperature of the carrier.
      //
      if (o_top == t) {
        continue;
      }
    }

    if (! t->has_temperature()) {
      continue;
    }

    //
    // So bats can fly over lava
    //
    if (t->is_lava()) {
      if (is_flying()) {
        continue;
      }
    }

    //
    // If we have 4 socks at 20 degrees and 1 torch at 100 degrees, what is the temperature of the tile ?
    // It's not 180 degrees :) and it's not the average.
    //
    // To try and quantize this instead I ignore things that are within normal ranges and so we would only
    // consider the torch.
    //
    if (abs(t->temperature) >= TEMPERATURE_THRESHOLD) {
      location_temp += t->temperature;
      location_temp_set = true;

      dbg("Location temp now %d due to %s (%d)", location_temp, t->to_short_string().c_str(), t->temperature);

      if (location_temp > TEMPERATURE_MAX) {
        location_temp = TEMPERATURE_MAX;
      } else if (location_temp < TEMPERATURE_MIN) {
        location_temp = TEMPERATURE_MIN;
      }
    }
  }
  FOR_ALL_THINGS_END()

  int thing_temp = temperature;
  if (is_able_to_freeze()) {
    if ((thing_temp > 0) && is_frozen) {
      frozen_unset();
    }
  }

  if (thing_temp < 0) {
    if (is_dead || is_dying) {
      if (is_able_to_freeze()) {
        if (! is_frozen) {
          dbg("Freeze the dead monst");
          frozen_set();
        }
      }
      return;
    }
  }

  if (is_burnable()) {
    if (is_dead || is_dying) {
      if (! is_burnt) {
        if (thing_temp > 0) {
          dbg("Burn the dead monst");
          is_burnt = true;
        }
      }
      return;
    }
  }

  if (! location_temp_set) {
    return;
  }

  dbg("Temperature tick, my temp %d, location temp: %d", thing_temp, location_temp);
  TRACE_AND_INDENT();

  //
  // Items being carried in side a chest are insulated.
  //
  auto owner = immediate_owner();
  if (owner && owner->is_bag_item_container()) {
    thing_temp = TEMPERATURE_ROOM;
  }

  //
  // Over time we gradually get closer to the location temperature.
  //
  if (thing_temp != location_temp) {
    int delta = (location_temp - thing_temp) / 2;

    if (is_lava() || is_wall() || is_door() || is_rock()) {
      delta = (location_temp - thing_temp) / 10;
    }

    temperature_incr(delta);

    thing_temp = temperature;
    dbg2("Temperature tick, my temp now %d, location temp: %d", thing_temp, location_temp);
  }

  if (game->tick_current == tick_last_i_was_attacked()) {
    return;
  }

  if ((thing_temp <= -200) && is_stone()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Crack!");
      dbg("Apply cold damage");
      TRACE_AND_INDENT();

      TRACE_AND_INDENT();
      is_attacked_with_dmg_cold(this, this, damage);
      return;
    }
  }

  if ((thing_temp <= -100) && is_wooden()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Shatter!");
      dbg("Apply cold damage");
      TRACE_AND_INDENT();

      TRACE_AND_INDENT();
      is_attacked_with_dmg_cold(this, this, damage);
      return;
    }
  }

  if ((thing_temp <= -50) && is_humanoid()) {
    if (thing_check_for_cold_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();

      is_attacked_with_dmg_cold(this, this, damage);
      if (is_player()) {
        msg("%%fg=lightblue$%s suffers from the extreme cold.%%fg=reset$", text_The().c_str());
      } else if (is_alive_monst()) {
        msg("%s suffers from the extreme cold.", text_The().c_str());
      }
      popup("Freezes!");
      return;
    }
  }

  if ((thing_temp <= -20) && is_plant()) {
    if (thing_check_for_cold_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_cold(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp <= 0) && is_gelatinous()) {
    if (thing_check_for_cold_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_cold(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp < TEMPERATURE_THRESHOLD) && is_fire()) {
    auto damage = abs(thing_temp) / 20;
    dbg("Apply cold damage");
    TRACE_AND_INDENT();
    is_attacked_with_dmg_cold(this, this, damage);
    return;
  }

  if ((thing_temp > 0) && is_block_of_ice()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      popup("Melting!");
      return;
    }
  }

  if ((thing_temp >= 20) && is_plant()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp >= 30) && is_gelatinous()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      popup("Melts!");
      return;
    }
  }

  if ((thing_temp >= 50) && is_humanoid()) {
    dbg("Check for heat damage");
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      if (is_on_fire()) {
        //
        // It's pretty obvious you are suffering if on fire!
        //
      } else {
        if (is_player()) {
          if (level->is_lava(curr_at)) {
            msg("%%fg=orange$You are swimming in lava!%%fg=reset$");
          } else {
            msg("%%fg=orange$You suffer from the extreme heat.%%fg=reset$");
          }
        } else if (is_alive_monst()) {
          if (level->is_lava(curr_at)) {
            msg("%%fg=orange$%s swims in lava!%%fg=reset$", text_The().c_str());
          } else {
            msg("%%fg=orange$%s suffers from the extreme heat.%%fg=reset$", text_The().c_str());
          }
        }
      }
    } else {
      //
      // No heat damage
      //
      if (is_player()) {
        if (level->is_lava(curr_at)) {
          //
          // Should be obvious you are too hot!
          //
          if (is_immune_to_fire()) {
            msg("You bask in the lava.");
          }
        } else {
          if (is_immune_to_fire()) {
            msg("You bask in the heat.");
          } else {
            msg("You sweat from the extreme heat.");
          }
        }
      }
    }
  }

  if ((thing_temp >= 100) && is_wooden()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Burn!");
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      return;
    }
  }

  if ((thing_temp >= 200) && is_stone()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Crack!");
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      return;
    }
  }

  if ((thing_temp >= 100) && is_burnable()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Burn!");
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      return;
    }
  }

  if ((thing_temp >= 50) && is_able_to_melt()) {
    if (thing_check_for_heat_dmg()) {
      auto damage = abs(thing_temp) / 20;
      popup("Melt!");
      dbg("Apply heat damage");
      TRACE_AND_INDENT();
      is_attacked_with_dmg_heat(this, this, damage);
      return;
    }
  }

  if (! is_immune_to_fire()) {
    if (thing_temp >= 100) {
      auto damage = abs(thing_temp) / 20;
      if (torch_tick()) {
        dbg("Torch attack");
        TRACE_AND_INDENT();

        dbg("Apply heat damage");
        TRACE_AND_INDENT();

        is_attacked_with_dmg_heat(this, this, damage);
        return;
      }
    }
  }

  dbg2("Temperature tick, final my temp %d", temperature_get());
}

int Thing::temperature_get(void)
{
  TRACE_NO_INDENT();
  return temperature;
}

int Thing::initial_temperature_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->initial_temperature());
}

bool Thing::initial_temperature_is_set(void)
{
  TRACE_NO_INDENT();
  return (tp()->initial_temperature_is_set());
}

int Thing::temperature_min_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_min());
}

bool Thing::temperature_min_is_set(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_min_is_set());
}

int Thing::temperature_max_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_max());
}

bool Thing::temperature_max_is_set(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_max_is_set());
}

int Thing::temperature_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  temperature = v;
  return v;
}

void Thing::temperature_decr(int v) { temperature_incr(-v); }

void Thing::temperature_incr(int temperature_change)
{
  TRACE_NO_INDENT();

  if (! temperature_change) {
    return;
  }

  if (is_flying()) {
    return;
  }

  int temperature_curr = temperature_get();
  dbg2("Increment temp by %d, current temp %d", temperature_change, temperature_curr);
  TRACE_AND_INDENT();

  if (temperature_sensitive_to_sudden_changes()) {
    if (temperature_change > 50) {
      if (is_immune_to_fire()) {
        if (is_player()) {
          msg("%%fg=orange$%s basks in the increasing heat.%%fg=reset$", text_The().c_str());
        } else if (is_monst()) {
          msg("%s basks in the increasing heat.", text_The().c_str());
        }
      } else {
        if ((temperature_curr < 0) && (temperature_curr > -25)) {
          auto damage = (temperature_change - temperature_curr) / 10;
          if (is_stone()) {
            popup("Crack!");
            if (is_player()) {
              msg("%%fg=orange$%s cracks from the increase in temperature.%%fg=reset$", text_The().c_str());
            } else {
              msg("%s cracks from the change in temperature.%%fg=reset$", text_The().c_str());
            }
          } else {
            if (is_player()) {
              msg("%%fg=orange$%s suffers from the increase in temperature.%%fg=reset$", text_The().c_str());
            } else {
              msg("%s suffers from the change in temperature.%%fg=reset$", text_The().c_str());
            }
          }
          is_attacked_with_dmg_heat(this, this, damage);
        }
      }
    } else if (temperature_change < -50) {
      if (is_immune_to_cold()) {
        if (is_player()) {
          msg("%%fg=cyan$%s basks in the increasing cold.%%fg=reset$", text_The().c_str());
        } else if (is_monst()) {
          msg("%s basks in the increasing cold.", text_The().c_str());
        }
      } else {
        if ((temperature_curr > 0) && (temperature_curr < 25)) {
          auto damage = (temperature_curr - temperature_change) / 10;
          if (is_stone()) {
            popup("Crack!");
            if (is_player()) {
              msg("%%fg=cyan$%s cracks from the decrease in temperature.%%fg=reset$", text_The().c_str());
            } else {
              msg("%s cracks from the change in temperature.", text_The().c_str());
            }
          } else {
            if (is_player()) {
              msg("%%fg=cyan$%s suffers from the decrease in temperature.%%fg=reset$", text_The().c_str());
            } else {
              msg("%s suffers from the change in temperature.", text_The().c_str());
            }
          }
          is_attacked_with_dmg_cold(this, this, damage);
        }
      }
    }
  }

  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }

  temperature += temperature_change;

  if (temperature > TEMPERATURE_MAX) {
    temperature = TEMPERATURE_MAX;
  } else if (temperature < TEMPERATURE_MIN) {
    temperature = TEMPERATURE_MIN;
  }
}

void Thing::temperature_decr(void) { temperature_incr(-1); }

void Thing::temperature_incr(void) { temperature_incr(1); }

bool Thing::has_temperature(void) { return tp()->has_temperature(); }
