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

int Thing::get_stat_def_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_def_total();
  }

  int stat = 0;
  int prev = 0;

  stat = get_stat_def();
  prev = stat;
  dbg("AC: %d", stat);

  //
  // Add def bonus
  //
  stat += get_stat_def_mod();
  if (stat != prev) {
    prev = stat;
    dbg("AC: with: (mod %d): %d", get_stat_def_mod(), stat);
  }

  //
  // Add dex bonus to def
  //
  int dex_total = get_stat_dex_total();
  stat += stat_to_bonus(dex_total);
  if (stat != prev) {
    prev = stat;
    dbg("AC: with: (dex %d): %d", dex_total, stat);
  }

  //
  // Choose the highest armor
  //
  FOR_ALL_EQUIP(e)
  {
    auto iter = get_equip(e);
    if (iter) {
      stat = std::max(stat, iter->get_stat_def() + iter->get_stat_def_mod() + iter->get_enchant());
      if (stat != prev) {
        prev = stat;
        dbg("AC: with (%s def %d/%d): %d", iter->to_short_string().c_str(), iter->get_stat_def(),
            stat_to_bonus(iter->get_stat_def()), stat);
      }
    }
  }

  //
  // Now add modifiers
  //
  FOR_ALL_EQUIP(e)
  {
    auto iter = get_equip(e);
    if (iter) {
      stat += iter->get_stat_def_mod();
      if (stat != prev) {
        prev = stat;
        dbg("AC: with: (%s mod %d): %d", iter->to_short_string().c_str(), get_stat_def_mod(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->get_stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->get_stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->get_stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with skill (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat);
        }
      }
    }
  }

  //
  // Penalties
  //
  stat -= get_stuck_count();
  if (stat != prev) {
    prev = stat;
    dbg("AC: with (stuck count %d): %d", get_stuck_count(), stat);
  }

  stat -= get_idle_count();
  if (stat != prev) {
    prev = stat;
    dbg("AC: with (idle count %d): %d", get_stuck_count(), stat);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      stat /= 2;
      if (stat != prev) {
        prev = stat;
        dbg("AC: with (water penalty): %d", stat);
      }
    }
    if (level->is_deep_water(curr_at)) {
      stat /= 2;
      if (stat != prev) {
        prev = stat;
        dbg("AC: with (deep water penalty): %d", stat);
      }
    }
  }

  dbg("AC: final: %d", stat);
  return stat;
}

int Thing::get_stat_def(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = get_infop()->stat_def;
  }
  return v;
}

int Thing::set_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def = v);
  return (n);
}

int Thing::decr_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def -= v);
  if (get_infop()->stat_def < 0) {
    get_infop()->stat_def = 0;
  }
  return (n);
}

int Thing::incr_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def += v);
  return (n);
}

int Thing::decr_stat_def(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def--);
  if (get_infop()->stat_def < 0) {
    get_infop()->stat_def = 0;
  }
  return (n);
}

int Thing::incr_stat_def(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def++);
  return (n);
}
