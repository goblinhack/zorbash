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

int Thing::noise(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->noise);
  } else {
    return 0;
  }
}

int Thing::get_noise_total(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise();
  // con("NOISE %d", decibels);

  FOR_ALL_EQUIP(e)
  {
    auto it = get_equip(e);
    if (it) {
      decibels += it->noise();
      // it->con("NOISE %d", decibels);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto it = level->thing_find(id);
      if (it) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(it)) {
          continue;
        }
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }
  }
  return decibels;
}

int Thing::set_noise(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->noise = v);
  return (n);
}

int Thing::decr_noise(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->noise -= v);
  return (n);
}

int Thing::incr_noise(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->noise += v);
  return (n);
}

int Thing::decr_noise(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->noise--);
  return (n);
}

int Thing::incr_noise(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->noise++);
  return (n);
}
