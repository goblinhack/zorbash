//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
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

bool Thing::possible_to_attack(const Thingp victim)
{
  TRACE_AND_INDENT();
  auto me = tp();

  if (victim == this) {
    return false;
  }

  auto my_owner  = get_top_owner();
  auto its_owner = victim->get_top_owner();
  if (my_owner && (my_owner == its_owner)) {
    return false;
  }

  auto my_minion_owner  = get_top_minion_owner();
  auto its_minion_owner = victim->get_top_minion_owner();
  if (my_minion_owner && (my_minion_owner == its_minion_owner)) {
    return false;
  }

  auto my_spawned_owner  = get_top_spawned_owner();
  auto its_spawned_owner = victim->get_top_spawned_owner();
  if (my_spawned_owner && (my_spawned_owner == its_spawned_owner)) {
    return false;
  }

  //
  // Weapons can't attack all by themselves. That would be nuts.
  //
  if (is_weapon() || is_wand() || is_ring()) {
    if (! my_owner) {
      return false;
    }
  }

  dbg("Is it possible to attack %s?", victim->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon()) {
      dbg("Cannot attack %s, I am fire", victim->to_string().c_str());
      return false;
    }
  }

  if (is_meat_eater() || attack_meat()) {
    //
    // Meat eaters eat you when you are dead!
    //
  } else {
    if (victim->is_dead) {
      dbg("Cannot attack %s, it's dead", victim->to_string().c_str());
      return false;
    }
  }

  //
  // No attacking of open doors!
  //
  if (victim->is_open) {
    dbg("Cannot attack %s, it's open", victim->to_string().c_str());
    return false;
  }

  if (is_alive_monst() || is_resurrected) {
    if (me->is_jelly_baby_eater()) {
      if (victim->is_jelly_baby()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_treasure_type_eater()) {
      if (victim->is_treasure_type()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
      if (victim->is_carrying_treasure()) {
        dbg("Can steal from %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_potion_eater()) {
      if (victim->is_potion()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Cleaners can attack cleaners?
    //
    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical_eater()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Can we eats it?
    //
    if (me->is_meat_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead meat: %s", victim->to_string().c_str());
          return true;
        }

        dbg("Can attack meat or blood: %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Can we attack the meat? Only if it is alive.
    //
    if (me->attack_meat()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("no, cannot attack %s, not is_attackable by meat eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_string().c_str());
          return false;
        }
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_string().c_str());
          return false;
        }

        dbg("Can attack living meat: %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_blood()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead blood: %s", victim->to_string().c_str());
          return true;
        }

        dbg("Can attack blood or blood: %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->attack_humanoid()) {
      if (victim->is_humanoid()) {
        if (! victim->is_dead) {
          dbg("Can attack humanoid: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_living()) {
      if (victim->is_living()) {
        if (! victim->is_dead) {
          dbg("Can attack living: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_undead()) {
      if (victim->is_undead()) {
        if (! victim->is_dead) {
          dbg("Can attack undead: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->is_food_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by food eating monst", victim->to_string().c_str());
        return false;
      }
      if (victim->is_food()) {
        dbg("Can attack food: %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (is_player()) {
    if (victim->is_attackable_by_player()) {
      if (game->robot_mode) {
        if (victim->is_barrel()) {
          dbg("No, do not attack %s, is explosive barrel", victim->to_string().c_str());
          return false;
        }
      }
      if (victim->is_foilage()) {
        dbg("No, do not attack %s", victim->to_string().c_str());
        return false;
      }
      dbg("Can attack %s", victim->to_string().c_str());
      return true;
    }
    dbg("No, cannot attack %s, not is_attackable", victim->to_string().c_str());
    return false;
  }

  if (is_weapon()) {
    auto o = get_immediate_owner();
    if (o) {
      if (o->is_monst()) {
        if (! victim->is_attackable_by_monst()) {
          // Too noisy
          // dbg("Cannot weapon attack %s, not is_attackable by monst",
          //     victim->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      } else {
        if (! victim->is_attackable_by_player()) {
          dbg("Cannot weapon attack %s, not is_attackable by player", victim->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (me->is_fire() || me->is_lava()) {
    if (me->is_monst()) {
      //
      // Fire monsters do not attack always
      //
    } else if (victim->is_burnable() || victim->is_very_combustible() || victim->is_combustible()) {
      if (! victim->is_fire() && ! victim->is_lava()) {
        dbg("Can attack as I am firey %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (is_enemy(victim)) {
    dbg("Can attack enemy %s", victim->to_string().c_str());
    return true;
  }

  if (is_weapon()) {
    if (victim->is_foilage() || victim->is_sticky() || victim->is_spiderweb()) {
      dbg("Can attack scenery %s", victim->to_string().c_str());
      return true;
    }
  }

  if (victim->is_alive_monst() || victim->is_combustible() || victim->is_very_combustible() ||
      victim->is_burnable() || victim->is_wall() || victim->is_rock() || victim->is_door() || victim->is_bridge() ||
      victim->is_dry_grass() || victim->is_treasure_type() || victim->is_enchantstone() || victim->is_skillstone() ||
      victim->is_foilage() || victim->is_spiderweb() || victim->is_sticky() || victim->is_brazier() ||
      victim->is_barrel() || victim->is_player() || victim->is_food() || victim->is_bag_item()) {

    if (is_laser()) {
      dbg("Can attack as laser %s", victim->to_string().c_str());
      return true;
    }

    if (is_projectile()) {
      dbg("Can attack as projectile %s", victim->to_string().c_str());
      return true;
    }

    if (is_wand()) {
      dbg("Can attack as wand %s", victim->to_string().c_str());
      return true;
    }

    if (is_ring()) {
      dbg("Can attack as ring %s", victim->to_string().c_str());
      return true;
    }

    if (is_explosion()) {
      dbg("Can attack as explosion %s", victim->to_string().c_str());
      return true;
    }
  }

  dbg("Cannot attack %s, ignore", victim->to_string().c_str());

  return false;
}

bool Thing::attack(point future_pos)
{
  bool up     = future_pos.y < mid_at.y;
  bool down   = future_pos.y > mid_at.y;
  bool left   = future_pos.x < mid_at.x;
  bool right  = future_pos.x > mid_at.x;
  bool attack = true;
  bool idle   = false;

  verify(this);
  bool shove_allowed  = true;
  bool attack_allowed = true;
  return (move(future_pos, up, down, left, right, attack, idle, shove_allowed, attack_allowed));
}

bool Thing::attack(Thingp victim)
{
  TRACE_AND_INDENT();
  dbg("Attack %s", victim->to_string().c_str());
  TRACE_AND_INDENT();

  set_idle_count(0);

  //
  // Carry to eat later. Things attack their food.
  //
  auto owner = get_top_owner();
  if (owner) {
    //
    // We hit this path for swords. We don't really want the sword to
    // do the eating, so pass control to the owner.
    //

    //
    // Owner eat food?
    //
    if (owner == victim) {
      //
      // This is an odd one.
      //
      err("Trying to attack self");
    } else if (owner->can_eat(victim)) {
      //
      // Eat corpse?
      //
      IF_DEBUG2 { owner->log("Can eat %s", victim->to_string().c_str()); }

      if (victim->is_dead) {
        if (owner->eat(victim)) {
          //
          // Can't defeat victim twice, so hide victim
          //
          IF_DEBUG1 { owner->log("Eat corpse %s", victim->to_string().c_str()); }
          victim->hide();
          return true;
        }
      } else if (owner->is_player()) {
        owner->log("Carry %s", victim->to_string().c_str());
        if (owner->try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
          return true;
        }
        return false;
      }
    }
  } else {
    //
    // As above, but not for owner.
    //
    if (can_eat(victim)) {
      dbg("Try to eat instead of attacking %s", victim->to_string().c_str());
      //
      // Eat corpse?
      //
      if (is_item_carrier() &&
          ((is_jelly_eater() && victim->is_jelly()) || (is_food_eater() && victim->is_food()) ||
           (is_treasure_type_eater() && victim->is_treasure_type()) ||
           (is_item_magical_eater() && victim->is_item_magical()) || (is_potion_eater() && victim->is_potion())) &&
          try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
        dbg("Don't eat, try to carry %s", victim->to_string().c_str());
        return true;
      }

      if (is_monst() && victim->is_dead && ! victim->is_player() && eat(victim)) {
        //
        // Can only eat once alive things when dead... But the player is gone once dead.
        // Can't defeat victim twice, so hide victim
        //
        dbg("Eat corpse %s", victim->to_string().c_str());
        victim->hide();
        victim->gc();
        return true;
      }

      if (is_monst() && victim->is_food() &&
          ((is_jelly_eater() && victim->is_jelly()) || (is_meat_eater() && victim->is_meat()) ||
           (is_blood_eater() && victim->is_blood()) || (is_food_eater() && victim->is_food())) &&
          eat(victim)) {
        return true;
      }

      if (is_player()) {
        dbg("Don't attack, try to carry %s", victim->to_string().c_str());
        if (try_to_carry_if_worthwhile_dropping_items_if_needed(victim)) {
          return true;
        }
        return false;
      }
    }
  }

  if (! possible_to_attack(victim)) {
    dbg("Attack failed, not possible to attack %s", victim->to_string().c_str());
    return false;
  }

  if (is_able_to_tire()) {
    if (! get_stamina()) {
      if (is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
      }
      return false;
    }
  }

  //
  // attack modifier: strength + attack bonus
  //
  auto attack_total = get_stat_strength() + get_stat_attack_bonus();
  if (owner) {
    attack_total += owner->get_stat_strength();
    attack_total += owner->get_stat_attack_bonus();
  }

  attack_total -= get_idle_count();
  attack_total -= get_stuck_count();

  //
  // defence modifier: armor class + dexterity
  //
  auto defence_total = victim->get_stat_armor_class();
  defence_total += victim->get_stat_dexterity();

  auto victim_owner = get_top_owner();
  if (victim_owner) {
    defence_total = victim_owner->get_stat_armor_class();
    defence_total = victim_owner->get_stat_dexterity();
  }

  defence_total -= victim->get_idle_count();
  defence_total -= victim->get_stuck_count();

  //
  // We hit. See how much damage.
  //
  auto damage = get_damage_melee() + stat_to_bonus(attack_total);
  if (damage < 1) {
    damage = 1;
  }

  //
  // Chance of poison damage?
  //
  bool poison        = false;
  auto poison_damage = get_damage_poison();
  if ((int) pcg_random_range(0, 1000) < attack_poison_chance_d1000()) {
    damage = poison_damage;
    poison = true;
  }

  //
  // Bite?
  //
  auto bite        = false;
  auto bite_damage = get_damage_bite();
  if (bite_damage) {
    if (pcg_random_range(0, 100) < 50) {
      damage = bite_damage + stat_to_bonus(attack_total);
      bite   = true;
    }
  }

  if (damage <= 0) {
    dbg("Attack failed, no damage");
    return false;
  }

  if (is_player()) {
    //
    // Player always uses their weapon
    //
    if (get_equip(MONST_EQUIP_WEAPON)) {
      auto delta = victim->mid_at - mid_at;
      move_set_dir_from_delta(delta);
      equip_use_may_attack(MONST_EQUIP_WEAPON);
      return true;
    }
  } else if (is_monst()) {
    //
    // Don't swing weapons at pools of blood.
    //
    if (victim->is_alive_monst() || victim->is_door() || victim->is_player() || victim->is_minion_generator()) {
      if (get_equip(MONST_EQUIP_WEAPON)) {
        auto delta = victim->mid_at - mid_at;
        move_set_dir_from_delta(delta);
        equip_use_may_attack(MONST_EQUIP_WEAPON);
        return true;
      }
    } else if (is_monst()) {
      bite = true;
    }
  }

  bool crit   = false;
  bool fumble = false;

  //
  // See if we can bypass its defences
  //
  if (is_player() || is_alive_monst()) {
    if (victim->is_dead) {
      //
      // It's hard to miss a corpse.
      //
    } else if (victim->is_always_hit()) {
      //
      // You just cannot miss this.
      //
    } else {
      log("attack_total %d %s defence_total %d", attack_total, victim->to_string().c_str(), defence_total);
      auto hit = d20roll(attack_total, defence_total, fumble, crit);

      //
      // Cannot miss (if engulfing?)
      //
      if (victim->mid_at == mid_at) {
        hit = true;
      }

      if (! hit) {
        if (is_player() || (owner && owner->is_player())) {
          TOPCON("You miss %s.", victim->text_the().c_str());
          msg("!");
        } else if (victim->is_player()) {
          if (owner) {
            TOPCON("%s misses with %s.", owner->text_the().c_str(), text_The().c_str());
          } else {
            TOPCON("%s misses.", text_The().c_str());
          }
        } else {
          dbg("The attack missed (att %d, def %d) on %s", attack_total, defence_total, victim->to_string().c_str());
        }

        if (attack_lunge()) {
          lunge(victim->mid_at);
        }

        //
        // An attempt at an attack counts
        //
        victim->add_enemy(this);

        //
        // We tried to attack, so do not move
        //
        return true;
      }
    }
  }

  //
  // This handles when we are stuck inside a cleaner
  //
  if (is_engulfer()) {
    if (victim->mid_at == mid_at) {
      bite_damage = get_damage_swallow();
      if (victim->is_player()) {
        TOPCON("%%fg=red$You are being consumed by %s!%%fg=reset$", text_the().c_str());
        msg("Gulp!");
      }
    }
  }

  if (victim->is_hit(this, crit, bite, poison, damage)) {
    dbg("The attack succeeded");

    if (attack_lunge()) {
      lunge(victim->mid_at);
    }
    if (attack_eater()) {
      health_boost(victim->get_nutrition());
    }
    if (is_destroyed_on_hitting() || is_destroyed_on_hit_or_miss()) {
      dead("by foolishness");
    }

    decr_stamina();
    return true;
  }

  victim->on_you_miss_do(this);

  //
  // Missiles?
  //
  if (is_destroyed_on_hit_or_miss()) {
    if (is_loggable()) {
      dbg("Attack missed %s", victim->to_string().c_str());
    }
    if (attack_lunge()) {
      lunge(victim->mid_at);
    }
    dead("by foolishness");
    return true;
  }

  return false;
}

bool Thing::possible_to_attack_at(point at)
{
  bool ret = false;

  TRACE_AND_INDENT();
  dbg("Possible to attack at %s", at.to_string().c_str());
  TRACE_AND_INDENT();

  FOR_ALL_COLLISION_THINGS(level, victim, at.x, at.y)
  {
    if (! possible_to_attack(victim)) {
      continue;
    }
    dbg("Yes; %s", victim->to_string().c_str());
    ret = true;
  }

  if (! ret) {
    dbg("No");
  }

  FOR_ALL_THINGS_END()

  return ret;
}
