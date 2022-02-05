//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"
#include <algorithm>
#include <set>

bool Thing::try_to_enchant_items(void)
{
  //
  // Be a bit more careful if there is somethjing that might want to
  // attack us, even if it is not a threat. i.e. a harmless goblin
  // could push us off of a cliff while we're doing other stuff.
  //
  if (! is_able_to_enchant_items() && ! is_able_to_learn_skills()) {
    return false;
  }

  AI_LOG("Unfriendly monst check");
  TRACE_NO_INDENT();

  if (any_unfriendly_monst_visible()) {
    AI_LOG("Unfriendlies are near");
    return false;
  }

  //
  // Can we enchant something?
  //
  AI_LOG("Enchant check");
  if (is_able_to_enchant_items()) {
    if (get_enchantstone_count() && can_enchant_something()) {
      AI_LOG("Try to enchant something");
      if (is_player()) {
        game->tick_begin("Robot can enchant something");
      }
      change_state(MONST_STATE_USING_ENCHANTSTONE, "can enchant something");
      return true;
    }
  }

  //
  // Can we learn some skills?
  //
  AI_LOG("Enchant check");
  if (is_able_to_learn_skills()) {
    if (get_skillstone_count() && can_learn_something()) {
      AI_LOG("Try to use a skillstone");
      if (is_player()) {
        game->tick_begin("Robot can learn something");
      }
      change_state(MONST_STATE_USING_SKILLSTONE, "can learn something");
      return true;
    }
  }

  return false;
}

bool Thing::try_to_use_weapon(void)
{
  //
  // Can we switch to a better weapon? Only if we can use weapons. We don't
  // wand jellys wandering around with swords!
  //
  if (! is_able_to_use_weapons()) {
    return false;
  }

  AI_LOG("Weapon check");
  TRACE_NO_INDENT();

  Thingp curr_weapon = get_equip(MONST_EQUIP_WEAPON);
  Thingp best_weapon = nullptr;
  get_carried_weapon_highest_value(&best_weapon);
  if (best_weapon) {
    auto curr_weapon_val = curr_weapon ? get_value(curr_weapon) : 0;
    auto best_weapon_val = get_value(best_weapon);

    if (! curr_weapon) {
      if (use(best_weapon, MONST_EQUIP_WEAPON)) {
        AI_LOG("Change weapon", best_weapon);
        if (is_player()) {
          game->tick_begin("Robot, has equipped weapon");
        }
        return true;
      }
    } else if (best_weapon_val > curr_weapon_val) {
      if (use(best_weapon, MONST_EQUIP_WEAPON)) {
        AI_LOG("Change weapon", best_weapon);
        if (is_player()) {
          game->tick_begin("Robot, has changed weapon");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_armor(void)
{
  if (! is_able_to_use_armor()) {
    return false;
  }

  AI_LOG("Armor check");
  TRACE_NO_INDENT();

  Thingp curr_armor = get_equip(MONST_EQUIP_ARMOR);
  Thingp best_armor = nullptr;
  get_carried_armor_highest_value(&best_armor);
  if (best_armor) {
    auto curr_armor_val = curr_armor ? get_value(curr_armor) : 0;
    auto best_armor_val = get_value(best_armor);

    if (! curr_armor) {
      if (use(best_armor, MONST_EQUIP_ARMOR)) {
        AI_LOG("Change armor", best_armor);
        if (is_player()) {
          game->tick_begin("Robot, has equipped armor");
        }
        return true;
      }
    } else if (best_armor_val > curr_armor_val) {
      if (use(best_armor, MONST_EQUIP_ARMOR)) {
        AI_LOG("Change armor", best_armor);
        if (is_player()) {
          game->tick_begin("Robot, has changed armor");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_helmet(void)
{
  if (! is_able_to_use_helmet()) {
    return false;
  }

  AI_LOG("Helmet check");
  TRACE_NO_INDENT();

  Thingp curr_helmet = get_equip(MONST_EQUIP_HELMET);
  Thingp best_helmet = nullptr;
  get_carried_helmet_highest_value(&best_helmet);
  if (best_helmet) {
    auto curr_helmet_val = curr_helmet ? get_value(curr_helmet) : 0;
    auto best_helmet_val = get_value(best_helmet);

    if (! curr_helmet) {
      if (use(best_helmet, MONST_EQUIP_HELMET)) {
        AI_LOG("Change helmet", best_helmet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped helmet");
        }
        return true;
      }
    } else if (best_helmet_val > curr_helmet_val) {
      if (use(best_helmet, MONST_EQUIP_HELMET)) {
        AI_LOG("Change helmet", best_helmet);
        if (is_player()) {
          game->tick_begin("Robot, has changed helmet");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_amulet(void)
{
  if (! is_able_to_use_amulet()) {
    return false;
  }

  AI_LOG("Amulet check");
  TRACE_NO_INDENT();

  Thingp curr_amulet = get_equip(MONST_EQUIP_AMULET);
  Thingp best_amulet = nullptr;
  get_carried_amulet_highest_value(&best_amulet);
  if (best_amulet) {
    auto curr_amulet_val = curr_amulet ? get_value(curr_amulet) : 0;
    auto best_amulet_val = get_value(best_amulet);

    if (! curr_amulet) {
      if (use(best_amulet, MONST_EQUIP_AMULET)) {
        AI_LOG("Change amulet", best_amulet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped amulet");
        }
        return true;
      }
    } else if (best_amulet_val > curr_amulet_val) {
      if (use(best_amulet, MONST_EQUIP_AMULET)) {
        AI_LOG("Change amulet", best_amulet);
        if (is_player()) {
          game->tick_begin("Robot, has changed amulet");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_boots(void)
{
  if (! is_able_to_use_boots()) {
    return false;
  }

  AI_LOG("Boots check");
  TRACE_NO_INDENT();

  Thingp curr_boots = get_equip(MONST_EQUIP_BOOTS);
  Thingp best_boots = nullptr;
  get_carried_boots_highest_value(&best_boots);
  if (best_boots) {
    auto curr_boots_val = curr_boots ? get_value(curr_boots) : 0;
    auto best_boots_val = get_value(best_boots);

    if (! curr_boots) {
      if (use(best_boots, MONST_EQUIP_BOOTS)) {
        AI_LOG("Change boots", best_boots);
        if (is_player()) {
          game->tick_begin("Robot, has equipped boots");
        }
        return true;
      }
    } else if (best_boots_val > curr_boots_val) {
      if (use(best_boots, MONST_EQUIP_BOOTS)) {
        AI_LOG("Change boots", best_boots);
        if (is_player()) {
          game->tick_begin("Robot, has changed boots");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_gauntlet(void)
{
  if (! is_able_to_use_gauntlet()) {
    return false;
  }

  AI_LOG("Gauntlet check");
  TRACE_NO_INDENT();

  Thingp curr_gauntlet = get_equip(MONST_EQUIP_GAUNTLET);
  Thingp best_gauntlet = nullptr;
  get_carried_gauntlet_highest_value(&best_gauntlet);
  if (best_gauntlet) {
    auto curr_gauntlet_val = curr_gauntlet ? get_value(curr_gauntlet) : 0;
    auto best_gauntlet_val = get_value(best_gauntlet);

    if (! curr_gauntlet) {
      if (use(best_gauntlet, MONST_EQUIP_GAUNTLET)) {
        AI_LOG("Change gauntlet", best_gauntlet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped gauntlet");
        }
        return true;
      }
    } else if (best_gauntlet_val > curr_gauntlet_val) {
      if (use(best_gauntlet, MONST_EQUIP_GAUNTLET)) {
        AI_LOG("Change gauntlet", best_gauntlet);
        if (is_player()) {
          game->tick_begin("Robot, has changed gauntlet");
        }
        return true;
      }
    }
  }

  return false;
}

bool Thing::try_to_use_shield(void)
{
  if (! is_able_to_use_shield()) {
    return false;
  }

  AI_LOG("Shield check");
  TRACE_NO_INDENT();

  Thingp curr_shield = get_equip(MONST_EQUIP_SHIELD);
  Thingp best_shield = nullptr;
  get_carried_shield_highest_value(&best_shield);
  if (best_shield) {
    auto curr_shield_val = curr_shield ? get_value(curr_shield) : 0;
    auto best_shield_val = get_value(best_shield);

    if (! curr_shield) {
      if (use(best_shield, MONST_EQUIP_SHIELD)) {
        AI_LOG("Change shield", best_shield);
        if (is_player()) {
          game->tick_begin("Robot, has equipped shield");
        }
        return true;
      }
    } else if (best_shield_val > curr_shield_val) {
      if (use(best_shield, MONST_EQUIP_SHIELD)) {
        AI_LOG("Change shield", best_shield);
        if (is_player()) {
          game->tick_begin("Robot, has changed shield");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_cloak(void)
{
  if (! is_able_to_use_cloak()) {
    return false;
  }

  AI_LOG("Cloak check");
  TRACE_NO_INDENT();

  Thingp curr_cloak = get_equip(MONST_EQUIP_CLOAK);
  Thingp best_cloak = nullptr;
  get_carried_cloak_highest_value(&best_cloak);
  if (best_cloak) {
    auto curr_cloak_val = curr_cloak ? get_value(curr_cloak) : 0;
    auto best_cloak_val = get_value(best_cloak);

    if (! curr_cloak) {
      if (use(best_cloak, MONST_EQUIP_CLOAK)) {
        AI_LOG("Change cloak", best_cloak);
        if (is_player()) {
          game->tick_begin("Robot, has equipped cloak");
        }
        return true;
      }
    } else if (best_cloak_val > curr_cloak_val) {
      if (use(best_cloak, MONST_EQUIP_CLOAK)) {
        AI_LOG("Change cloak", best_cloak);
        if (is_player()) {
          game->tick_begin("Robot, has changed cloak");
        }
        return true;
      }
    }
  }
  return false;
}

bool Thing::try_to_use_rings(void)
{
  if (! is_able_to_use_rings()) {
    return false;
  }

  AI_LOG("Ring check");
  TRACE_NO_INDENT();

  //
  // Can we switch to a better ring?
  //
  Thingp curr_ring1 = get_equip(MONST_EQUIP_RING1);
  Thingp curr_ring2 = get_equip(MONST_EQUIP_RING2);
  Thingp best_ring  = nullptr;

  get_carried_ring_highest_value(&best_ring);
  if (best_ring) {
    auto curr_ring1_val = curr_ring1 ? get_value(curr_ring1) : 0;
    auto curr_ring2_val = curr_ring2 ? get_value(curr_ring2) : 0;
    auto best_ring_val  = get_value(best_ring);

    if (! curr_ring1) {
      if (use(best_ring, MONST_EQUIP_RING1)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has equipped ring1");
        }
        return true;
      }
    } else if (! curr_ring2) {
      if (use(best_ring, MONST_EQUIP_RING2)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has equipped ring2");
        }
        return true;
      }
    } else if (best_ring_val > curr_ring1_val) {
      if (use(best_ring, MONST_EQUIP_RING1)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has changed ring1");
        }
        return true;
      }
    } else if (best_ring_val > curr_ring2_val) {
      if (use(best_ring, MONST_EQUIP_RING2)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has changed ring2");
        }
        return true;
      }
    }
  }

  return false;
}
