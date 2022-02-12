//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::temperature_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_alive_monst() && ! is_player()) {
    return;
  }

  //
  // Add in the temperature of the location
  //
  int location_t = 0;

  FOR_ALL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_hidden) {
      continue;
    }

    if (t == this) {
      continue;
    }

    location_t += t->temperature_get();
  }
  FOR_ALL_THINGS_END()

  auto t = temperature_get();
  if (! location_t && ! t) {
    return;
  }

  dbg("Temperature tick");
  TRACE_AND_INDENT();

  temperature_incr(location_t);

  t = temperature_get();
  if (! t) {
    return;
  }

  t = (int) ((float) t * 0.95);
  temperature_set(t);
}

int Thing::temperature_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop_get()->temperature);
  } else {
    return 0;
  }
}

int Thing::temperature_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->temperature = v);
  return (n);
}

int Thing::temperature_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->temperature -= v);
  return (n);
}

int Thing::temperature_incr(int v)
{
  TRACE_NO_INDENT();

  if (! v) {
    return v;
  }

  log("Increment temp %d", v);
  TRACE_AND_INDENT();

  auto T   = temperature_get();
  bool hit = false;

  if (temperature_change_sensitive()) {
    if (v > 0) {
      if (T < 0) {
        if (is_alive_monst() || is_player()) {
          auto damage = (v - T) / 10;
          hit         = true;
          if (is_stone()) {
            popup("Crack!");
            if (is_player()) {
              msg("%%fg=orange$%s cracks from the change in temperature for %d damage.%%fg=reset$",
                  text_The().c_str(), damage);
            } else {
            }
          } else {
            if (is_player()) {
              msg("%%fg=orange$%s suffers from the change in temperature for %d damage.%%fg=reset$",
                  text_The().c_str(), damage);
            } else {
            }
          }
          is_attacked_with_damage_fire(this, damage);
        }
      }
    } else if (v < 0) {
      if (T > 0) {
        if (is_alive_monst() || is_player()) {
          auto damage = (T - v) / 10;
          hit         = true;
          if (is_stone()) {
            popup("Crack!");
            if (is_player()) {
              msg("%%fg=cyan$%s cracks from the change in temperature for %d damage.%%fg=reset$", text_The().c_str(),
                  damage);
            } else {
              msg("%s cracks from the change in temperature for %d damage.", text_The().c_str(), damage);
            }
          } else {
            if (is_player()) {
              msg("%%fg=cyan$%s suffers from the change in temperature for %d damage.%%fg=reset$", text_The().c_str(),
                  damage);
            } else {
              msg("%s suffers from the change in temperature for %d damage.", text_The().c_str(), damage);
            }
          }
          is_attacked_with_damage_cold(this, damage);
        }
      }
    }
  }

  if (game->tick_current != tick_last_i_was_attacked_get()) {
    if (! hit) {
      if (v < -100) {
        if (is_alive_monst()) {
          if (! is_immune_to_cold() || is_player()) {
            auto damage = abs(v) / 20;
            if (is_stone()) {
              popup("Crack!");
              if (is_player()) {
                msg("%%fg=cyan$%s fractures from the extreme cold for %d damage.%%fg=reset$", text_The().c_str(),
                    damage);
              } else {
                msg("%s fractures from the extreme cold for %d damage.", text_The().c_str(), damage);
              }
            } else {
              if (is_player()) {
                msg("%%fg=cyan$%s suffers from the extreme cold for %d damage.%%fg=reset$", text_The().c_str(),
                    damage);
              } else {
                msg("%s suffers from the extreme cold for %d damage.", text_The().c_str(), damage);
              }
            }
            is_attacked_with_damage_cold(this, damage);
          }
        }
      } else if (v > 100) {
        if (is_alive_monst() || is_player()) {
          if (! is_immune_to_fire()) {
            auto damage = abs(v) / 20;
            if (is_stone()) {
              popup("Crack!");
              if (is_player()) {
                msg("%%fg=orange$%s fractures from the extreme heat for %d damage.%%fg=reset$", text_The().c_str(),
                    damage);
              } else {
                msg("%s fractures from the extreme heat for %d damage.", text_The().c_str(), damage);
              }
            } else {
              if (is_player()) {
                msg("%%fg=orange$%s suffers from the extreme heat for %d damage.%%fg=reset$", text_The().c_str(),
                    damage);
              } else {
                msg("%s suffers from the extreme heat for %d damage.", text_The().c_str(), damage);
              }
            }
            is_attacked_with_damage_fire(this, damage);
          }
        }
      }
    }
  }

  if (is_player()) {
    game->request_update_rightbar = true;
  }

  new_infop();
  auto n = (infop_get()->temperature += v);

  if (n > 1000) {
    n                        = 1000;
    infop_get()->temperature = v;
  } else if (n < -1000) {
    n                        = -1000;
    infop_get()->temperature = v;
  }

  return (n);
}

int Thing::temperature_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->temperature--);
  return (n);
}

int Thing::temperature_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->temperature++);
  return (n);
}