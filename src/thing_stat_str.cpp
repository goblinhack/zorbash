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

int Thing::stat_str_total(void)
{
  TRACE_NO_INDENT();

  auto owner = top_owner();
  if (owner) {
    return owner->stat_str_get();
  }

  int stat = 0;
  int prev = 0;

  stat = stat_str_get();
  prev = stat;
  dbg("Str: (%d/%d): %d", stat_str_get(), stat_to_bonus(stat_str_get()), stat);

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_str_mod_get();
      if (stat != prev) {
        prev = stat;
        dbg("Str: with (%s %s): %d", iter->to_short_string().c_str(),
            modifier_to_string(iter->stat_str_mod_get()).c_str(), stat);
      }

      auto enchant = iter->enchant_get();
      stat += enchant;
      if (stat != prev) {
        prev = stat;
        dbg("Str: with (%s enchant %d): %d", iter->to_short_string().c_str(), enchant, stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_str_mod_get();
        if (stat != prev) {
          prev = stat;
          dbg("Str: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_str_mod_get()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_str_mod_get();
        if (stat != prev) {
          prev = stat;
          dbg("Str: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_str_mod_get()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_str_mod_get();
        if (stat != prev) {
          prev = stat;
          dbg("Str: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->stat_str_mod_get()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::stat_str_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop_get()->stat_str);
  } else {
    return 0;
  }
}

int Thing::stat_str_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_str = v);
  return (n);
}

int Thing::stat_str_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_str -= v);
  return (n);
}

int Thing::stat_str_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_str += v);
  return (n);
}

int Thing::stat_str_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_str--);
  return (n);
}

int Thing::stat_str_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_str++);
  return (n);
}
