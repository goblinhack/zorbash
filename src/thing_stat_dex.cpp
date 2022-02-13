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

int Thing::stat_dex_total(void)
{
  TRACE_NO_INDENT();

  auto owner = top_owner_get();
  if (owner) {
    return owner->stat_dex();
  }

  int stat = 0;
  int prev = 0;

  stat = stat_dex();
  prev = stat;
  dbg("Dex: (%d/%d): %d", stat_dex(), stat_to_bonus(stat_dex()), stat);

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_dex_mod();
      if (stat != prev) {
        prev = stat;
        dbg("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
            modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
      }

      auto enchant = iter->enchant_get();
      stat += enchant;
      if (stat != prev) {
        prev = stat;
        dbg("Dex: with (%s enchant %d): %d", iter->to_short_string().c_str(), enchant, stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::stat_dex(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop_get()->stat_dex);
  } else {
    return 0;
  }
}

int Thing::stat_dex_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_dex = v);
  return (n);
}

int Thing::stat_dex_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_dex -= v);
  return (n);
}

int Thing::stat_dex_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_dex += v);
  return (n);
}

int Thing::stat_dex_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_dex--);
  return (n);
}

int Thing::stat_dex_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_dex++);
  return (n);
}
