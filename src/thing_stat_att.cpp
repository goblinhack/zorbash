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

int Thing::attack_modifier_get(const Thingp victim)
{
  TRACE_NO_INDENT();

  auto owner = top_owner_get();
  if (owner) {
    return owner->attack_modifier_get(victim);
  }

  int stat = 0;
  int prev = 0;

  //
  // Add att bonus
  //
  stat += stat_att_mod();
  if (stat != prev) {
    prev = stat;
    dbg("Att: with: (mod %d): %d", stat_att_mod(), stat);
  }

  //
  // Add str bonus to att
  //
  int str_total = stat_str_total_get();
  stat          = stat_to_bonus(str_total);
  stat += stat_att_mod();
  prev = stat;
  dbg("Att: (str %d): %d", str_total, stat);

  FOR_ALL_EQUIP(e)
  {
    auto equip = equip_get(e);
    if (equip) {
      stat += equip->stat_att_mod();
      if (stat != prev) {
        prev = stat;
        dbg("Att with (%s): %d", equip->to_short_string().c_str(), stat);
      }

      auto enchant = equip->enchant_get();
      stat += enchant;
      if (stat != prev) {
        prev = stat;
        dbg("Att with (%s enchant %d): %d", equip->to_short_string().c_str(), enchant, stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_att_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Att with buff (%s): %d", buff->to_short_string().c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_att_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Att with debuff (%s): %d", buff->to_short_string().c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat += buff->stat_att_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Att with skill (%s): %d", buff->to_short_string().c_str(), stat);
        }
      }
    }
  }

  dbg("Att: final: %d", stat);
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
  if (stat_att_penalty_when_stuck()) {
    int p = stat_att_penalty_when_stuck() + stuck_count_get();
    p     = std::min(p, stat_att_penalty_when_stuck_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg("Att penalty: stuck %d", p);
    }
  } else if (stat_att_penalty_when_idle()) {
    int p = stat_att_penalty_when_idle() + idle_count_get();
    p     = std::min(p, stat_att_penalty_when_idle_max());
    penalty += p;
    if (penalty != prev) {
      prev = penalty;
      dbg("Att penalty: idle %d", p);
    }
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      int p = stat_att_penalty_when_in_shallow_water();
      if (p) {
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg("Att penalty: with (in shallow water %d): %d", p, penalty);
        }
      }
    }
    if (level->is_deep_water(curr_at)) {
      int p = stat_att_penalty_when_in_deep_water();
      if (p) {
        penalty += p;
        if (penalty != prev) {
          prev = penalty;
          dbg("Att penalty: with (in deep water %d): %d", p, penalty);
        }
      }
    }
  }

  if (penalty) {
    dbg("Att penalty: %d", penalty);
  }
  return penalty;
}
