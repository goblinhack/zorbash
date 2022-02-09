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

    location_t += t->get_temperature();
  }
  FOR_ALL_THINGS_END()

  auto t = get_temperature();
  if (! location_t && ! t) {
    return;
  }

  dbg("Temperature tick");
  TRACE_AND_INDENT();

  incr_temperature(location_t);

  t = get_temperature();
  if (! t) {
    return;
  }

  t = (int) ((float) t * 0.95);
  set_temperature(t);
}

int Thing::get_temperature(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->temperature);
  } else {
    return 0;
  }
}

int Thing::set_temperature(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->temperature = v);
  return (n);
}

int Thing::decr_temperature(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->temperature -= v);
  return (n);
}

int Thing::incr_temperature(int v)
{
  TRACE_NO_INDENT();

  if (! v) {
    return v;
  }

  log("Increment temp %d", v);
  TRACE_AND_INDENT();

  auto T   = get_temperature();
  bool hit = false;

  if (temperature_change_sensitive()) {
    if (v > 0) {
      if (T < 0) {
        if (is_alive_monst() || is_player()) {
          auto damage = (v - T) / 10;
          hit         = true;
          if (is_stone()) {
            popup("Crack!");
            msg("%s cracks from the change in temperature for %d damage.", text_The().c_str(), damage);
          } else {
            msg("%s suffers from the change in temperature for %d damage.", text_The().c_str(), damage);
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
            msg("%s cracks from the change in temperature for %d damage.", text_The().c_str(), damage);
          } else {
            msg("%s suffers from the change in temperature for %d damage.", text_The().c_str(), damage);
          }
          is_attacked_with_damage_cold(this, damage);
        }
      }
    }
  }

  if (game->tick_current != get_tick_last_i_was_attacked()) {
    if (! hit) {
      if (v < -100) {
        if (is_alive_monst()) {
          if (! is_immune_to_cold() || is_player()) {
            auto damage = abs(v) / 20;
            if (is_stone()) {
              popup("Crack!");
              msg("%s fractures from the extreme cold for %d damage.", text_The().c_str(), damage);
            } else {
              msg("%s suffers from the extreme cold for %d damage.", text_The().c_str(), damage);
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
              msg("%s fractures from the extreme heat for %d damage.", text_The().c_str(), damage);
            } else {
              msg("%s suffers from the extreme heat for %d damage.", text_The().c_str(), damage);
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
  auto n = (get_infop()->temperature += v);

  if (n > 1000) {
    n                        = 1000;
    get_infop()->temperature = v;
  } else if (n < -1000) {
    n                        = -1000;
    get_infop()->temperature = v;
  }

  return (n);
}

int Thing::decr_temperature(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->temperature--);
  return (n);
}

int Thing::incr_temperature(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->temperature++);
  return (n);
}
