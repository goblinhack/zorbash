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
    return (infop_get()->noise);
  } else {
    return 0;
  }
}

int Thing::noise_total_get(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise();
  // con("NOISE %d", decibels);

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
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

  decibels -= stat_dex_mod_get() * 10;

  return decibels;
}

int Thing::noise_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->noise = v);
  return (n);
}

int Thing::noise_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->noise -= v);
  return (n);
}

int Thing::noise_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->noise += v);
  return (n);
}

int Thing::noise_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->noise--);
  return (n);
}

int Thing::noise_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->noise++);
  return (n);
}
