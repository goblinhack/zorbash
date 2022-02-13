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

int Thing::stat_def_total(void)
{
  TRACE_NO_INDENT();

  auto owner = top_owner_get();
  if (owner) {
    return owner->stat_def_total();
  }

  int stat = 0;
  int prev = 0;

  stat = stat_def();
  prev = stat;
  dbg("AC: %d", stat);

  //
  // Add def bonus
  //
  stat += stat_def_mod();
  if (stat != prev) {
    prev = stat;
    dbg("AC: with: (mod %d): %d", stat_def_mod(), stat);
  }

  //
  // Add dex bonus to def
  //
  int dex_total = stat_dex_total();
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
    auto iter = equip_get(e);
    if (iter) {
      stat = std::max(stat, iter->stat_def() + iter->stat_def_mod() + iter->enchant_get());
      if (stat != prev) {
        prev = stat;
        dbg("AC: with (%s def %d/%d): %d", iter->to_short_string().c_str(), iter->stat_def(),
            stat_to_bonus(iter->stat_def()), stat);
      }
    }
  }

  //
  // Now add modifiers
  //
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_def_mod();
      if (stat != prev) {
        prev = stat;
        dbg("AC: with: (%s mod %d): %d", iter->to_short_string().c_str(), stat_def_mod(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->stat_def(),
              stat_to_bonus(buff->stat_def()), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->stat_def(),
              stat_to_bonus(buff->stat_def()), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_def_mod();
        if (stat != prev) {
          prev = stat;
          dbg("AC: with skill (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->stat_def(),
              stat_to_bonus(buff->stat_def()), stat);
        }
      }
    }
  }

  dbg("AC: final: %d", stat);
  return stat;
}

int Thing::stat_def_penalties_total(void)
{
  TRACE_NO_INDENT();

  int penalty = 0;
  int prev    = 0;

  //
  // Positional penalties
  //
  if (stat_def_penalty_when_stuck()) {
    int p = stat_def_penalty_when_stuck() + stuck_count();
    p     = std::min(p, stat_def_penalty_when_stuck_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg("AC penalty: stuck %d", p);
    }
  } else if (stat_def_penalty_when_idle()) {
    int p = stat_def_penalty_when_idle() + idle_count();
    p     = std::min(p, stat_def_penalty_when_idle_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg("AC penalty: idle %d", p);
    }
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      int p = stat_def_penalty_when_in_shallow_water();
      if (p) {
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg("AC penalty: with (in shallow water %d): %d", p, penalty);
        }
      }
    }
    if (level->is_deep_water(curr_at)) {
      int p = stat_def_penalty_when_in_deep_water();
      if (p) {
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg("AC penalty: with (in deep water %d): %d", p, penalty);
        }
      }
    }
  }

  if (penalty) {
    dbg("AC penalty: %d", penalty);
  }
  return penalty;
}

int Thing::stat_def(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop_get()->stat_def;
  }
  return v;
}

int Thing::stat_def_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_def = v);
  return (n);
}

int Thing::stat_def_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_def -= v);
  if (infop_get()->stat_def < 0) {
    infop_get()->stat_def = 0;
  }
  return (n);
}

int Thing::stat_def_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_def += v);
  return (n);
}

int Thing::stat_def_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_def--);
  if (infop_get()->stat_def < 0) {
    infop_get()->stat_def = 0;
  }
  return (n);
}

int Thing::stat_def_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop_get()->stat_def++);
  return (n);
}
