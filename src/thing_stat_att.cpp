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
  int strength_total       = get_stat_str_total();

  attack_modifier = stat_to_bonus(strength_total);
  attack_modifier += get_attack_bonus();
  last_attack_modifier = attack_modifier;
  dbg("Att: (str %d): %d", strength_total, attack_modifier);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      attack_modifier += equip->get_attack_bonus();
      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Att with (%s): %d", equip->to_short_string().c_str(), attack_modifier);

        //
        // Add enchanted strength
        //
        attack_modifier += equip->get_enchant();
        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Att with (enchant %d): %d", equip->get_enchant(), attack_modifier);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        attack_modifier += buff->get_attack_bonus();
        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Att with buff (%s): %d", buff->to_short_string().c_str(), attack_modifier);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        attack_modifier += buff->get_attack_bonus();
        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Att with debuff (%s): %d", buff->to_short_string().c_str(), attack_modifier);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        attack_modifier += buff->get_attack_bonus();
        if (attack_modifier != last_attack_modifier) {
          last_attack_modifier = attack_modifier;
          dbg("Att with skill (%s): %d", buff->to_short_string().c_str(), attack_modifier);
        }
      }
    }
  }

  //
  // Penalties
  //
  attack_modifier -= get_stuck_count();
  if (attack_modifier != last_attack_modifier) {
    last_attack_modifier = attack_modifier;
    dbg("Att with (stuck count %d): %d", get_stuck_count(), attack_modifier);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      attack_modifier /= 2;
      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Att with (water penalty): %d", attack_modifier);
      }
    }
    if (level->is_deep_water(curr_at)) {
      attack_modifier /= 2;
      if (attack_modifier != last_attack_modifier) {
        last_attack_modifier = attack_modifier;
        dbg("Att with (deep water penalty): %d", attack_modifier);
      }
    }
  }

  return attack_modifier;
}
