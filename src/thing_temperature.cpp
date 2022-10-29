//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::temperature_tick(void)
{
  TRACE_NO_INDENT();

  int  location_temp     = 0;
  bool location_temp_set = false;

  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_floor()) {
      continue;
    }

    //
    // Without this check a player will heat themselves up ridiculously
    //
    if (t == this) {
      continue;
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
      if (top_owner() == t) {
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

      IF_DEBUG2
      {
        dbg("Location temp now %d due to %s (%d)", location_temp, t->to_short_string().c_str(), t->temperature);
      }

      if (location_temp > TEMPERATURE_MAX) {
        location_temp = TEMPERATURE_MAX;
      } else if (location_temp < TEMPERATURE_MIN) {
        location_temp = TEMPERATURE_MIN;
      }
    }
  }
  FOR_ALL_THINGS_END()

  if (! location_temp_set) {
    return;
  }

  int thing_temp = temperature;

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
    dbg("Temperature tick, my temp %d, location temp: %d", thing_temp, location_temp);
    TRACE_AND_INDENT();

    int delta = (location_temp - thing_temp) / 2;

    if (is_lava() || is_fire() || is_block_of_ice() || is_wall() || is_door() || is_rock()) {
      delta = (location_temp - thing_temp) / 10;
    }

    temperature_incr(delta);

    thing_temp = temperature;
    dbg("Temperature tick, my temp now %d, location temp: %d", thing_temp, location_temp);
    TRACE_AND_INDENT();
  }

  if (is_dead || is_dying) {
    if (is_able_to_freeze()) {
      if (! is_frozen) {
        if (thing_temp < 0) {
          dbg("Freeze the dead monst");
          is_frozen = true;
        }
      }
    }

    if (is_able_to_burn()) {
      if (! is_burnt) {
        if (thing_temp > 0) {
          dbg("Burn the dead monst");
          is_burnt = true;
        }
      }
    }
    return;
  }

  if (! is_temperature_sensitive() && ! is_able_to_freeze()) {
    return;
  }

  if (game->tick_current == tick_last_i_was_attacked()) {
    return;
  }

  if ((thing_temp <= -200) && is_stone()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Crack!");
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_cold(this, this, damage);
      return;
    }
  }

  if ((thing_temp <= -100) && is_wooden()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Shatter!");
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_cold(this, this, damage);
      return;
    }
  }

  if ((thing_temp <= -50) && is_humanoid()) {
    if (thing_check_for_cold_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_cold(this, this, damage);
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
    if (thing_check_for_cold_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_cold(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp <= 0) && is_gelatinous()) {
    if (thing_check_for_cold_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply cold damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_cold(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp < 0) && is_fire()) {
    auto damage = abs(thing_temp) / 10;
    dbg("Apply cold damage");
    TRACE_AND_INDENT();
    is_attacked_with_damage_cold(this, this, damage);
    return;
  }

  if ((thing_temp > 0) && is_block_of_ice()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
      popup("Melting!");
      return;
    }
  }

  if ((thing_temp >= 20) && is_plant()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
      popup("Wilts!");
      return;
    }
  }

  if ((thing_temp >= 30) && is_gelatinous()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
      popup("Melts!");
      return;
    }
  }

  if ((thing_temp >= 50) && is_humanoid()) {
    dbg("Check for fire damage");
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
      if (is_on_fire()) {
        //
        // It's pretty obvious you are suffering if on fire!
        //
      } else {
        if (is_player()) {
          if (level->is_lava(curr_at)) {
            msg("%%fg=orange$You swim in lava!%%fg=reset$");
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
          // Should be obvious you are too hot.
          //
        } else {
          msg("You sweat from the extreme heat.");
        }
      }
    }
  }

  if ((thing_temp >= 100) && is_wooden()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Burn!");
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
    }
  }

  if ((thing_temp >= 200) && is_stone()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Crack!");
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
    }
  }

  if ((thing_temp >= 100) && is_able_to_burn()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Burn!");
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
    }
  }

  if ((thing_temp >= 50) && is_able_to_melt()) {
    if (thing_check_for_heat_damage()) {
      auto damage = abs(thing_temp) / 10;
      popup("Melt!");
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
    }
  }

  if (thing_temp >= 100) {
    auto damage = abs(thing_temp) / 20;
    if (torch_tick()) {
      dbg("Torch attack");
      TRACE_AND_INDENT();
      dbg("Apply fire damage");
      TRACE_AND_INDENT();
      is_attacked_with_damage_fire(this, this, damage);
    }
  }
}

int Thing::temperature_get(void)
{
  TRACE_NO_INDENT();
  return temperature;
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

  if (is_temperature_change_sensitive()) {
    if (temperature_change > 50) {
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
        is_attacked_with_damage_fire(this, this, damage);
      }
    } else if (temperature_change < -50) {
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
        is_attacked_with_damage_cold(this, this, damage);
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
