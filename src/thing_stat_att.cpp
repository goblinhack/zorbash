//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

int Thing::get_attack_modifier(const Thingp victim)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_attack_modifier(victim);
  }

  int stat = 0;
  int prev = 0;

  //
  // Add att bonus
  //
  stat += get_stat_att_mod();
  if (stat != prev) {
    prev = stat;
    dbg("Att: with: (mod %d): %d", get_stat_att_mod(), stat);
  }

  //
  // Add str bonus to att
  //
  int str_total = get_stat_str_total();
  stat          = stat_to_bonus(str_total);
  stat += get_stat_att_mod();
  prev = stat;
  dbg("Att: (str %d): %d", str_total, stat);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      stat += equip->get_stat_att_mod();
      if (stat != prev) {
        prev = stat;
        dbg("Att with (%s): %d", equip->to_short_string().c_str(), stat);
      }

      auto enchant = equip->get_enchant();
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
        stat += buff->get_stat_att_mod();
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
        stat += buff->get_stat_att_mod();
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
        stat += buff->get_stat_att_mod();
        if (stat != prev) {
          prev = stat;
          dbg("Att with skill (%s): %d", buff->to_short_string().c_str(), stat);
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
    dbg("Att with (stuck count %d): %d", get_stuck_count(), stat);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      stat /= 2;
      if (stat != prev) {
        prev = stat;
        dbg("Att with (water penalty): %d", stat);
      }
    }
    if (level->is_deep_water(curr_at)) {
      stat /= 2;
      if (stat != prev) {
        prev = stat;
        dbg("Att with (deep water penalty): %d", stat);
      }
    }
  }

  dbg("Att: final: %d", stat);
  return stat;
}
