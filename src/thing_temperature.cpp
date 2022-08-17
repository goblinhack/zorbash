//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::temperature_tick(void)
{
  TRACE_NO_INDENT();

  if (is_dead || is_dying) {
    return;
  }

  if (! is_temperature_sensitive()) {
    return;
  }

  dbg("Temperature tick (%u)", game->tick_current);
  TRACE_AND_INDENT();

  //
  // Add in the temperature of the location
  //
  int  location_t     = 0;
  bool location_t_set = false;

  //
  // Items being carried in side a chest are insulated.
  //
  auto owner = immediate_owner();
  if (owner && owner->is_bag_item_container()) {
    temperature_set(0);
  }

  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }

    if (t == this) {
      continue;
    }

    if (on_fire_anim_id() == t->id) {
      //
      // You "carry" fire when on fire.
      //
    } else {
      //
      // Ignore carried things
      //
      if (t->immediate_owner() == this) {
        continue;
      }
    }

    if (! t->has_temperature()) {
      continue;
    }

    //
    // So bats can flyu over lava
    //
    if (t->is_lava()) {
      if (is_flying()) {
        continue;
      }
    }

    dbg("location temp now %d due to %s", location_t, t->to_string().c_str());

    location_t += t->temperature;
    location_t_set = true;
  }
  FOR_ALL_THINGS_END()

  if (! location_t_set) {
    return;
  }

  int t = temperature;
  dbg("Temperature tick, my temp %d, location temp: %d", t, location_t);
  TRACE_AND_INDENT();

  //
  // Over time we gradually get closer to the location temperature.
  //
  if (t != location_t) {
    int delta = (location_t - t) / 2;

    if (is_fire() || is_icecube() || is_wall() || is_door() || is_rock()) {
      delta = (location_t - t) / 10;
    }

    temperature_incr(delta);

    dbg("Temperature tick, my temp now %d, location temp: %d", t, location_t);
    TRACE_AND_INDENT();
  }

  if (is_temperature_sensitive()) {
    if (game->tick_current != tick_last_i_was_attacked()) {
      if (t <= -100) {
        if (! is_immune_to_cold() || is_player()) {
          auto damage = abs(t) / 10;
          if (is_stone()) {
            popup("Crack!");
            if (is_player()) {
              msg("%%fg=cyan$%s fractures from the extreme cold.%%fg=reset$", text_The().c_str());
            } else {
              msg("%s fractures from the extreme cold.", text_The().c_str());
            }
          } else {
            if (is_player()) {
              msg("%%fg=cyan$%s suffers from the extreme cold.%%fg=reset$", text_The().c_str());
            } else if (is_alive_monst()) {
              msg("%s suffers from the extreme cold.", text_The().c_str());
            }
          }
          is_attacked_with_damage_cold(this, this, damage);
        }
      } else if (t >= 100) {
        if (! is_immune_to_fire()) {
          auto damage = abs(t) / 10;
          if (fire_tick()) {
            dbg("Fire attack");
            TRACE_AND_INDENT();
            is_attacked_with_damage_fire(this, this, damage);
          } else {
            if (is_stone()) {
              popup("Crack!");
              if (is_player()) {
                msg("%%fg=orange$%s fractures from the extreme heat.%%fg=reset$", text_The().c_str());
              } else {
                msg("%s fractures from the extreme heat.", text_The().c_str());
              }
            } else {
              if (is_player()) {
                msg("%%fg=orange$%s suffers from the extreme heat.%%fg=reset$", text_The().c_str());
              } else if (is_alive_monst()) {
                msg("%s suffers from the extreme heat.", text_The().c_str());
              }
            }
          }
        }
      } else if (t >= 50) {
        if (! is_immune_to_fire()) {
          auto damage = abs(t) / 20;
          if (torch_tick()) {
            dbg("Torch attack");
            TRACE_AND_INDENT();
            is_attacked_with_damage_fire(this, this, damage);
          }
        }
      }
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
    game->request_remake_rightbar = true;
  }
  temperature = v;
  return v;
}

int Thing::temperature_decr(int v) { return temperature_incr(-v); }

int Thing::temperature_incr(int temperature_change)
{
  TRACE_NO_INDENT();

  if (! temperature_change) {
    return temperature_change;
  }

  if (is_flying()) {
    return temperature_change;
  }
  if (is_floating()) {
    return temperature_change;
  }
  if (is_dead) {
    return temperature_change;
  }
  if (is_undead()) {
    return temperature_change;
  }

  int temperature_curr = temperature_get();
  dbg2("Increment temp by %d, current temp %d", temperature_change, temperature_curr);
  TRACE_AND_INDENT();

  if (is_temperature_change_sensitive()) {
    if (temperature_change > 25) {
      if (temperature_curr < -25) {
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
    } else if (temperature_change < -25) {
      if (temperature_curr > 25) {
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
    game->request_remake_rightbar = true;
  }

  auto n = (temperature += temperature_change);
  if (n > 1000) {
    n           = 1000;
    temperature = temperature_change;
  } else if (n < -1000) {
    n           = -1000;
    temperature = temperature_change;
  }

  return n;
}

int Thing::temperature_decr(void) { return temperature_incr(-1); }

int Thing::temperature_incr(void) { return temperature_incr(1); }

bool Thing::has_temperature(void) { return tp()->has_temperature(); }
