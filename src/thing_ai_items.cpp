//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::try_to_enchant_items(void)
{
  //
  // Be a bit more careful if there is something that might want to
  // attack us, even if it is not a threat. i.e. a harmless goblin
  // could push us off of a cliff while we're doing other stuff.
  //
  AI_LOG("Unfriendly monst check");
  TRACE_NO_INDENT();

  if (any_unfriendly_monst_visible()) {
    AI_LOG("Unfriendlies are near, skip enchanting items");
    return false;
  }

  //
  // Can we enchant something?
  //
  AI_LOG("Enchant check");
  if (is_able_to_enchant_items()) {
    if (enchantstone_count() && can_enchant_something()) {
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
  if (is_able_to_learn_skills()) {
    if (skillstone_count() && can_learn_a_skill()) {
      AI_LOG("Try to use a skillstone");
      if (is_player()) {
        game->tick_begin("Robot can learn something");
      }
      change_state(MONST_STATE_USING_SKILLSTONE, "can learn something");
      return true;
    }
  }

  //
  // Can we learn some spells?
  //
  if (is_able_to_learn_spells()) {
    if (spellbook_count() && can_learn_a_spell()) {
      AI_LOG("Try to use a spellbook");
      if (is_player()) {
        game->tick_begin("Robot can learn something");
      }
      change_state(MONST_STATE_USING_SPELLBOOK, "can learn something");
      return true;
    }
  }

  return false;
}

bool Thing::try_to_use_weapon(void)
{
  //
  // Can we switch to a better weapon? Only if we can use weapons. We don't
  // staff slimes wandering around with swords!
  //
  if (! is_able_to_use_weapons()) {
    return false;
  }

  AI_LOG("Weapon check");
  TRACE_NO_INDENT();

  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  Thingp best_weapon = nullptr;
  carried_weapon_highest_value(&best_weapon);
  if (best_weapon) {
    auto curr_weapon_val = curr_weapon ? value(curr_weapon) : 0;
    auto best_weapon_val = value(best_weapon);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_WEAPON;
    use_options.preferred_equip_set = true;

    if (! curr_weapon) {
      if (use(best_weapon, use_options)) {
        AI_LOG("Change weapon", best_weapon);
        if (is_player()) {
          game->tick_begin("Robot, has equipped weapon");
        }
        return true;
      }
    } else if (best_weapon_val > curr_weapon_val) {
      if (use(best_weapon, use_options)) {
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

  Thingp curr_armor = equip_get(MONST_EQUIP_ARMOR);
  Thingp best_armor = nullptr;
  carried_armor_highest_value(&best_armor);
  if (best_armor) {
    auto curr_armor_val = curr_armor ? value(curr_armor) : 0;
    auto best_armor_val = value(best_armor);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_ARMOR;
    use_options.preferred_equip_set = true;

    if (! curr_armor) {
      if (use(best_armor, use_options)) {
        AI_LOG("Change armor", best_armor);
        if (is_player()) {
          game->tick_begin("Robot, has equipped armor");
        }
        return true;
      }
    } else if (best_armor_val > curr_armor_val) {
      if (use(best_armor, use_options)) {
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

  Thingp curr_helmet = equip_get(MONST_EQUIP_HELMET);
  Thingp best_helmet = nullptr;
  carried_helmet_highest_value(&best_helmet);
  if (best_helmet) {
    auto curr_helmet_val = curr_helmet ? value(curr_helmet) : 0;
    auto best_helmet_val = value(best_helmet);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_HELMET;
    use_options.preferred_equip_set = true;

    if (! curr_helmet) {
      if (use(best_helmet, use_options)) {
        AI_LOG("Change helmet", best_helmet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped helmet");
        }
        return true;
      }
    } else if (best_helmet_val > curr_helmet_val) {
      if (use(best_helmet, use_options)) {
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

  Thingp curr_amulet = equip_get(MONST_EQUIP_AMULET);
  Thingp best_amulet = nullptr;
  carried_amulet_highest_value(&best_amulet);
  if (best_amulet) {
    auto curr_amulet_val = curr_amulet ? value(curr_amulet) : 0;
    auto best_amulet_val = value(best_amulet);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_AMULET;
    use_options.preferred_equip_set = true;

    if (! curr_amulet) {
      if (use(best_amulet, use_options)) {
        AI_LOG("Change amulet", best_amulet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped amulet");
        }
        return true;
      }
    } else if (best_amulet_val > curr_amulet_val) {
      if (use(best_amulet, use_options)) {
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

  Thingp curr_boots = equip_get(MONST_EQUIP_BOOTS);
  Thingp best_boots = nullptr;
  carried_boots_highest_value(&best_boots);
  if (best_boots) {
    auto curr_boots_val = curr_boots ? value(curr_boots) : 0;
    auto best_boots_val = value(best_boots);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_BOOTS;
    use_options.preferred_equip_set = true;

    if (! curr_boots) {
      if (use(best_boots, use_options)) {
        AI_LOG("Change boots", best_boots);
        if (is_player()) {
          game->tick_begin("Robot, has equipped boots");
        }
        return true;
      }
    } else if (best_boots_val > curr_boots_val) {
      if (use(best_boots, use_options)) {
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

  Thingp curr_gauntlet = equip_get(MONST_EQUIP_GAUNTLET);
  Thingp best_gauntlet = nullptr;
  carried_gauntlet_highest_value(&best_gauntlet);
  if (best_gauntlet) {
    auto curr_gauntlet_val = curr_gauntlet ? value(curr_gauntlet) : 0;
    auto best_gauntlet_val = value(best_gauntlet);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_GAUNTLET;
    use_options.preferred_equip_set = true;

    if (! curr_gauntlet) {
      if (use(best_gauntlet, use_options)) {
        AI_LOG("Change gauntlet", best_gauntlet);
        if (is_player()) {
          game->tick_begin("Robot, has equipped gauntlet");
        }
        return true;
      }
    } else if (best_gauntlet_val > curr_gauntlet_val) {
      if (use(best_gauntlet, use_options)) {
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

  Thingp curr_shield = equip_get(MONST_EQUIP_SHIELD);
  Thingp best_shield = nullptr;
  carried_shield_highest_value(&best_shield);
  if (best_shield) {
    auto curr_shield_val = curr_shield ? value(curr_shield) : 0;
    auto best_shield_val = value(best_shield);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_SHIELD;
    use_options.preferred_equip_set = true;

    if (! curr_shield) {
      if (use(best_shield, use_options)) {
        AI_LOG("Change shield", best_shield);
        if (is_player()) {
          game->tick_begin("Robot, has equipped shield");
        }
        return true;
      }
    } else if (best_shield_val > curr_shield_val) {
      if (use(best_shield, use_options)) {
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

  Thingp curr_cloak = equip_get(MONST_EQUIP_CLOAK);
  Thingp best_cloak = nullptr;
  carried_cloak_highest_value(&best_cloak);
  if (best_cloak) {
    auto curr_cloak_val = curr_cloak ? value(curr_cloak) : 0;
    auto best_cloak_val = value(best_cloak);

    UseOptions use_options          = {};
    use_options.preferred_equip     = MONST_EQUIP_CLOAK;
    use_options.preferred_equip_set = true;

    if (! curr_cloak) {
      if (use(best_cloak, use_options)) {
        AI_LOG("Change cloak", best_cloak);
        if (is_player()) {
          game->tick_begin("Robot, has equipped cloak");
        }
        return true;
      }
    } else if (best_cloak_val > curr_cloak_val) {
      if (use(best_cloak, use_options)) {
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
  Thingp curr_ring1 = equip_get(MONST_EQUIP_RING1);
  Thingp curr_ring2 = equip_get(MONST_EQUIP_RING2);
  Thingp best_ring  = nullptr;

  carried_ring_highest_value(&best_ring);
  if (best_ring) {
    auto curr_ring1_val = curr_ring1 ? value(curr_ring1) : 0;
    auto curr_ring2_val = curr_ring2 ? value(curr_ring2) : 0;
    auto best_ring_val  = value(best_ring);

    if (! curr_ring1) {
      UseOptions use_options          = {};
      use_options.preferred_equip     = MONST_EQUIP_RING1;
      use_options.preferred_equip_set = true;
      if (use(best_ring, use_options)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has equipped ring1");
        }
        return true;
      }
    } else if (! curr_ring2) {
      UseOptions use_options          = {};
      use_options.preferred_equip     = MONST_EQUIP_RING2;
      use_options.preferred_equip_set = true;
      if (use(best_ring, use_options)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has equipped ring2");
        }
        return true;
      }
    } else if (best_ring_val > curr_ring1_val) {
      UseOptions use_options          = {};
      use_options.preferred_equip     = MONST_EQUIP_RING1;
      use_options.preferred_equip_set = true;
      if (use(best_ring, use_options)) {
        AI_LOG("Change ring", best_ring);
        if (is_player()) {
          game->tick_begin("Robot, has changed ring1");
        }
        return true;
      }
    } else if (best_ring_val > curr_ring2_val) {
      UseOptions use_options          = {};
      use_options.preferred_equip     = MONST_EQUIP_RING2;
      use_options.preferred_equip_set = true;
      if (use(best_ring, use_options)) {
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
