//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_att_total()
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_att();
  prev = stat;
  if (stat) {
    dbg2("Att: %d", stat);
  }

  stat += stat_att_mod();
  if (stat != prev) {
    prev = stat;
    dbg2("Att: with mod (%s): %d", modifier_to_string(stat_att_mod()).c_str(), stat);
  }

  //
  // Add str bonus to att
  //
  if (is_monst() || is_player()) {
    int str_total = stat_str_total();
    stat += stat_to_bonus(str_total);
    if (stat != prev) {
      prev = stat;
      dbg2("Att: (str %d): %d", str_total, stat);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_att_total();
      if (stat != prev) {
        prev = stat;
        dbg2("Att: with (%s %s): %d", iter->to_short_string().c_str(),
             modifier_to_string(iter->stat_att_mod()).c_str(), stat);
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
        stat += iter->stat_att_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Att: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_att_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_att_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Att: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_att_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_att_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Att: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_att_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_att_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Att: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_att_mod()).c_str(), stat);
        }
      }
    }
  }

  if (stat) {
    auto enchant = enchant_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg2("Att: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_att_penalties_total(void)
{
  TRACE_NO_INDENT();

  int penalty = 0;
  int prev    = 0;

  //
  // Positional penalties
  //
  if (stuck_count() && stat_att_penalty_when_stuck()) {
    int p = stat_att_penalty_when_stuck() + stuck_count();
    p     = std::min(p, stat_att_penalty_when_stuck_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg2("Att penalty: stuck %d", p);
    }
  } else if (idle_count() && stat_att_penalty_when_idle()) {
    int p = stat_att_penalty_when_idle() + idle_count();
    p     = std::min(p, stat_att_penalty_when_idle_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg2("Att penalty: idle %d", p);
    }
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      int p = stat_att_penalty_when_in_shallow_water();
      if (p) {
        if (is_able_to_swim()) {
          p /= 2;
        }
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg2("Att penalty: with (in shallow water %d): %d", p, penalty);
        }
      }
    }
    if (level->is_deep_water(curr_at)) {
      int p = stat_att_penalty_when_in_deep_water();
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
          dbg2("Att penalty: with (in deep water %d): %d", p, penalty);
        }
      }
    }
  }

  if (penalty) {
    dbg2("Att penalty: %d", penalty);
  }
  return penalty;
}

int Thing::stat_att(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_att);
  } else {
    return 0;
  }
}

int Thing::stat_att_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att = v);
  return n;
}

int Thing::stat_att_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att -= v);
  return n;
}

int Thing::stat_att_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att += v);
  return n;
}

int Thing::stat_att_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att--);
  return n;
}

int Thing::stat_att_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att++);
  return n;
}
