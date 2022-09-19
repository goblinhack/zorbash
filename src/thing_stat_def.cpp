//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_def_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_def();
  prev = stat;
  if (stat) {
    dbg3("Def: %d", stat);
  }

  stat += stat_def_mod();
  if (stat != prev) {
    prev = stat;
    dbg3("Def: with mod (%s): %d", modifier_to_string(stat_def_mod()).c_str(), stat);
  }

  //
  // Add dex bonus to def
  //
  if (is_monst() || is_player()) {
    int dex_total = stat_dex_total();
    stat += stat_to_bonus(dex_total);
    if (stat != prev) {
      prev = stat;
      dbg3("Def: with: (dex %d): %d", dex_total, stat);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_def_total();
      if (stat != prev) {
        prev = stat;
        dbg3("Def: with (%s %s): %d", iter->to_short_string().c_str(),
             modifier_to_string(iter->stat_def_mod()).c_str(), stat);
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
        stat += iter->stat_def_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Def: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_def_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_def_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Def: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_def_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_def_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Def: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_def_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_def_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Def: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_def_mod()).c_str(), stat);
        }
      }
    }
  }

  if (stat) {
    auto enchant = enchant_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg3("Def: with enchant %d: %d", enchant, stat);
    }
  }

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
  if (stuck_count() && stat_att_penalty_when_stuck()) {
    int p = stat_def_penalty_when_stuck() + stuck_count();
    p     = std::min(p, stat_def_penalty_when_stuck_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg3("AC penalty: stuck %d", p);
    }
  } else if (idle_count() && stat_att_penalty_when_idle()) {
    int p = stat_def_penalty_when_idle() + idle_count();
    p     = std::min(p, stat_def_penalty_when_idle_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg3("AC penalty: idle %d", p);
    }
  }

  //
  // Hunger penalties
  //
  if (is_starving) {
    int p = HUNGER_PENALTY_WHEN_STARVING;
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg2("AC penalty: starving %d", p);
    }
  } else if (is_hungry) {
    int p = THING_HUNGER_PENALTY_WHEN_HUNGRY;
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg2("AC penalty: hunger %d", p);
    }
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      int p = stat_def_penalty_when_in_shallow_water();
      if (p) {
        if (is_able_to_swim()) {
          p /= 2;
        }
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg3("AC penalty: with (in shallow water %d): %d", p, penalty);
        }
      }
    }
    if (level->is_deep_water(curr_at)) {
      int p = stat_def_penalty_when_in_deep_water();
      if (p) {
        if (is_able_to_swim()) {
          p /= 2;
        }
        if (is_heavy()) {
          p *= 2;
        }
        if (is_stone()) {
          p *= 2;
        }
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg3("AC penalty: with (in deep water %d): %d", p, penalty);
        }
      }
    }
  }

  if (penalty) {
    dbg3("AC penalty: %d", penalty);
  }
  return penalty;
}

int Thing::stat_def(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->stat_def;
  }
  return v;
}

int Thing::stat_def_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def = v);
  return n;
}

int Thing::stat_def_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def -= v);
  if (infop()->stat_def < 0) {
    infop()->stat_def = 0;
  }
  return n;
}

int Thing::stat_def_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def += v);
  return n;
}

int Thing::stat_def_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def--);
  if (infop()->stat_def < 0) {
    infop()->stat_def = 0;
  }
  return n;
}

int Thing::stat_def_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def++);
  return n;
}
