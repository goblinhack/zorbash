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

int Thing::get_stat_luck_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_luck();
  }

  int stat = 0;
  int prev = 0;

  stat = get_stat_luck();
  prev = stat;
  dbg("Luck: (%d/%d): %d", get_stat_luck(), stat_to_bonus(get_stat_luck()), stat);

  FOR_ALL_EQUIP(e)
  {
    auto iter = get_equip(e);
    if (iter) {
      stat += iter->get_stat_luck_mod();
      if (stat != prev) {
        prev = stat;
        dbg("Luck: with (%s %s): %d", iter->to_short_string().c_str(),
            modifier_to_string(iter->get_stat_luck_mod()).c_str(), stat);
      }

      auto enchant = iter->get_enchant();
      stat += enchant;
      if (stat != prev) {
        prev = stat;
        dbg("Luck: with (%s enchant %d): %d", iter->to_short_string().c_str(), enchant, stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->get_stat_luck_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Luck: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->get_stat_luck_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->get_stat_luck_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Luck: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->get_stat_luck_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->get_stat_luck_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Luck: with (%s %s): %d", iter->to_short_string().c_str(),
              modifier_to_string(iter->get_stat_luck_mod()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::get_stat_luck(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->stat_luck);
  } else {
    return 0;
  }
}

int Thing::set_stat_luck(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_luck = v);
  return (n);
}

int Thing::stat_luck_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_luck -= v);
  return (n);
}

int Thing::stat_luck_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_luck += v);
  return (n);
}

int Thing::stat_luck_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_luck--);
  return (n);
}

int Thing::stat_luck_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_luck++);
  return (n);
}
