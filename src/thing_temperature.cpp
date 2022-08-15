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
  int location_t = 0;

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
        if (t->temperature()) {
          dbg("Temperature tick, ignore: %s", t->to_string().c_str());
        }
        continue;
      }
    }

    //
    // So bats can flyu over lava
    //
    if (t->is_lava()) {
      if (is_flying()) {
        continue;
      }
    }

    location_t += t->temperature();
  }
  FOR_ALL_THINGS_END()

  auto t = temperature_get();
  if (! location_t && ! t) {
    return;
  }

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
  if (maybe_infop()) {
    return (infop()->temperature);
  } else {
    return 0;
  }
}

int Thing::temperature_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
  }
  new_infop();
  auto n = (infop()->temperature = v);
  return n;
}

int Thing::temperature_decr(int v) { return temperature_incr(-v); }

int Thing::temperature_incr(int v)
{
  TRACE_NO_INDENT();

  if (! v) {
    return v;
  }

  if (is_flying()) {
    return v;
  }
  if (is_floating()) {
    return v;
  }
  if (is_dead) {
    return v;
  }
  if (is_undead()) {
    return v;
  }

  int T = temperature_get();
  dbg2("Increment temp by %d, current temp %d", v, T);
  TRACE_AND_INDENT();

  if (is_temperature_change_sensitive()) {
    if (v > 25) {
      if (T < -25) {
        auto damage = (v - T) / 10;
        if (is_stone()) {
          popup("Crack!");
          if (is_player()) {
            msg("%%fg=orange$%s cracks from the change in temperature.%%fg=reset$", text_The().c_str());
          } else {
            msg("%s cracks from the change in temperature.%%fg=reset$", text_The().c_str());
          }
        } else {
          if (is_player()) {
            msg("%%fg=orange$%s suffers from the change in temperature.%%fg=reset$", text_The().c_str());
          } else {
            msg("%s suffers from the change in temperature.%%fg=reset$", text_The().c_str());
          }
        }
        is_attacked_with_damage_fire(this, this, damage);
      }
    } else if (v < -25) {
      if (T > 25) {
        auto damage = (T - v) / 10;
        if (is_stone()) {
          popup("Crack!");
          if (is_player()) {
            msg("%%fg=cyan$%s cracks from the change in temperature.%%fg=reset$", text_The().c_str());
          } else {
            msg("%s cracks from the change in temperature.", text_The().c_str());
          }
        } else {
          if (is_player()) {
            msg("%%fg=cyan$%s suffers from the change in temperature.%%fg=reset$", text_The().c_str());
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

  new_infop();
  auto n = (infop()->temperature += v);

  if (n > 1000) {
    n                    = 1000;
    infop()->temperature = v;
  } else if (n < -1000) {
    n                    = -1000;
    infop()->temperature = v;
  }

  return n;
}

int Thing::temperature_decr(void) { return temperature_incr(-1); }

int Thing::temperature_incr(void) { return temperature_incr(1); }
