//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

int Thing::stat_con_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_con();
  prev = stat;
  dbg("Con: %d: %d", stat_con(), stat);

  stat += stat_con_mod();
  if (stat != prev) {
    prev = stat;
    dbg("Con: with mod (%s): %d", modifier_to_string(stat_con_mod()).c_str(), stat);
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_con_total();
      if (stat != prev) {
        prev = stat;
        dbg("Con: with (%s %s): %d", iter->to_short_string().c_str(),
            modifier_to_string(iter->stat_con_mod()).c_str(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(iter)) {
          continue;
        }
        //
        // Things that are equipped must be equipped to get the benefit.
        // Other items give the benefit by just being carried.
        //
        if (iter->is_auto_equipped()) {
          continue;
        }
        stat += iter->stat_con_total();
        if (stat != prev) {
          prev = stat;
          dbg("Con: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_con_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_con_total();
        if (stat != prev) {
          prev = stat;
          dbg("Con: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_con_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_con_total();
        if (stat != prev) {
          prev = stat;
          dbg("Con: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_con_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_con_total();
        if (stat != prev) {
          prev = stat;
          dbg("Con: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_con_mod()).c_str(), stat);
        }
      }
    }
  }

  if (stat) {
    auto enchant = enchant_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg("Con: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_con(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_con);
  } else {
    return 0;
  }
}

int Thing::stat_con_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con = v);
  return (n);
}

int Thing::stat_con_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con -= v);
  return (n);
}

int Thing::stat_con_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con += v);
  return (n);
}

int Thing::stat_con_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con--);
  return (n);
}

int Thing::stat_con_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con++);
  return (n);
}
