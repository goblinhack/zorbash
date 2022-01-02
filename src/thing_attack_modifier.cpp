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

  int attack_modifier      = 0;
  int last_attack_modifier = 0;

  attack_modifier += stat_to_bonus(get_stat_strength());
  attack_modifier += get_attack_bonus();
  last_attack_modifier = attack_modifier;
  dbg("Attack modifier: (str %d/%d): %d", get_stat_strength(), stat_to_bonus(get_stat_strength()), attack_modifier);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      attack_modifier += stat_to_bonus(equip->get_stat_strength());
      attack_modifier += equip->get_attack_bonus();

      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Attack modifier with (%s str %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_strength(),
            stat_to_bonus(equip->get_stat_strength()), attack_modifier);

        //
        // Add enchanted strength
        //
        attack_modifier += equip->get_enchant();
        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Attack modifier with (enchant %d): %d", equip->get_enchant(), attack_modifier);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    for (auto id : get_itemsp()->buffs) {
      auto buff = level->thing_find(id);
      if (buff) {
        attack_modifier += stat_to_bonus(buff->get_stat_strength());
        attack_modifier += buff->get_attack_bonus();

        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Attack modifier with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(),
              buff->get_stat_strength(), stat_to_bonus(buff->get_stat_strength()), attack_modifier);
        }
      }
    }

    for (auto id : get_itemsp()->debuffs) {
      auto buff = level->thing_find(id);
      if (buff) {
        attack_modifier += stat_to_bonus(buff->get_stat_strength());
        attack_modifier += buff->get_attack_bonus();

        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Attack modifier with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(),
              buff->get_stat_strength(), stat_to_bonus(buff->get_stat_strength()), attack_modifier);
        }
      }
    }
  }

  attack_modifier -= get_stuck_count();
  if (attack_modifier != last_attack_modifier) {
    last_attack_modifier = attack_modifier;
    dbg("Attack modifier with (stuck count %d): %d", get_stuck_count(), attack_modifier);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic()) {
    if (level->is_water(curr_at)) {
      attack_modifier /= 2;
      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Attack modifier with (water penalty): %d", attack_modifier);
      }
    }
    if (level->is_deep_water(curr_at)) {
      attack_modifier /= 2;
      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Attack modifier with (deep water penalty): %d", attack_modifier);
      }
    }
  }

  return attack_modifier;
}
