//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_dmap.h"
#include "my_level.h"
#include "my_math.h"
#include "my_monst.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include <algorithm>

bool Thing::possible_to_attack(const Thingp it)
{
  TRACE_AND_INDENT();
  auto me = tp();

  auto owner = get_top_owner();

  //
  // Allow wands to reflect and attack the owner. Weapons though, no.
  //
  if (is_weapon()) {
    if (owner && owner->is_player()) {
      if (it->is_attackable_by_player()) {
        dbg("Owned by player");
      } else {
        dbg("Owned by player; not is_attackable by player");
      }
    }
  }

  dbg("Is it possible to attack %s?", it->to_string().c_str());
  TRACE_AND_INDENT();
  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon()) {
      dbg("Cannot attack %s, I am fire", it->to_string().c_str());
      return false;
    }
  }

  if (is_meat_eater() || attack_meat()) {
    //
    // Meat eaters eat you when you are dead!
    //
  } else {
    if (it->is_dead) {
      dbg("Cannot attack %s, it's dead", it->to_string().c_str());
      return false;
    }
  }

  //
  // No attacking of open doors!
  //
  if (it->is_open) {
    dbg("Cannot attack %s, it's open", it->to_string().c_str());
    return false;
  }

  if (is_alive_monst() || is_resurrected) {
    if (me->is_jelly_baby_eater()) {
      if (it->is_jelly_baby()) {
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      }
    }

    if (me->is_treasure_type_eater()) {
      if (it->is_treasure_type()) {
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      }
      if (it->is_carrying_treasure()) {
        dbg("Can steal from %s", it->to_string().c_str());
        return true;
      }
    }

    if (me->is_potion_eater()) {
      if (it->is_potion()) {
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      }
    }

    if (me->is_wand_eater()) {
      if (it->is_wand()) {
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      }
    }

    //
    // Can we eats it?
    //
    if (me->is_meat_eater()) {
      if (! it->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", it->to_string().c_str());
        return false;
      }

      if (it->is_meat() || it->is_blood()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (it->is_dead) {
          dbg("Can eat dead meat: %s", it->to_string().c_str());
          return true;
        }

        dbg("Can attack meat or blood: %s", it->to_string().c_str());
        return true;
      }
    }

    //
    // Can we attack the meat? Only if it is alive.
    //
    if (me->attack_meat()) {
      if (! it->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", it->to_string().c_str());
        return false;
      }

      if (it->is_meat() || it->is_blood()) {
        if (it->is_dead) {
          dbg("Can not attack dead meat: %s", it->to_string().c_str());
          return false;
        }

        dbg("Can attack living meat: %s", it->to_string().c_str());
        return true;
      }
    }

    if (me->attack_humanoid()) {
      if (it->is_humanoid()) {
        if (! it->is_dead) {
          dbg("Can attack humanoid: %s", it->to_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_living()) {
      if (it->is_living()) {
        if (! it->is_dead) {
          dbg("Can attack living: %s", it->to_string().c_str());
          return true;
        }
      }
    }

    if (me->is_food_eater()) {
      if (! it->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by food eating monst", it->to_string().c_str());
        return false;
      }
      if (it->is_food()) {
        dbg("Can attack food: %s", it->to_string().c_str());
        return true;
      }
    }
  }

  if (is_player()) {
    //
    // If player is attacking with bare fists, allow an attack
    // Else if it is a weapon, the weapon will attack
    //
    if (! weapon_get()) {
      if (! it->is_attackable_by_player()) {
        dbg("No, cannot attack %s, not is_attackable", it->to_string().c_str());
        return false;
      }
      dbg("Can attack %s", it->to_string().c_str());
      return true;
    }
  }

  if (is_weapon()) {
    auto o = get_immediate_owner();
    if (o) {
      if (o->is_monst()) {
        if (! it->is_attackable_by_monst()) {
          // Too noisy
          // dbg("Cannot weapon attack %s, not is_attackable by monst",
          //     it->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      } else {
        if (! it->is_attackable_by_player()) {
          dbg("Cannot weapon attack %s, not is_attackable by player", it->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", it->to_string().c_str());
        return true;
      }
    }
  }

  if (me->is_fire() || me->is_lava()) {
    if (me->is_monst()) {
      //
      // Fire monsters do not attack always
      //
    } else if (it->is_burnable() || it->is_very_combustible() || it->is_combustible()) {
      if (! it->is_fire() && ! it->is_lava()) {
        dbg("Can attack as I am firey %s", it->to_string().c_str());
        return true;
      }
    }
  }

  if (is_enemy(it)) {
    dbg("Can attack enemy %s", it->to_string().c_str());
    return true;
  }

  if (is_weapon()) {
    if (it->is_foilage() || it->is_sticky() || it->is_spiderweb()) {
      dbg("Can attack scenery %s", it->to_string().c_str());
      return true;
    }
  }

  if (it->is_alive_monst() || it->is_combustible() || it->is_very_combustible() || it->is_burnable() || it->is_wall() ||
      it->is_rock() || it->is_door() || it->is_bridge() || it->is_dry_grass() || it->is_treasure_type() ||
      it->is_enchantstone() || it->is_skillstone() || it->is_foilage() || it->is_spiderweb() || it->is_sticky() ||
      it->is_brazier() || it->is_barrel() || it->is_player() || it->is_food() || it->is_bag_item()) {

    if (is_laser()) {
      dbg("Can attack as laser %s", it->to_string().c_str());
      return true;
    }

    if (is_projectile()) {
      dbg("Can attack as projectile %s", it->to_string().c_str());
      return true;
    }

    if (is_wand()) {
      dbg("Can attack as wand %s", it->to_string().c_str());
      return true;
    }

    if (is_explosion()) {
      dbg("Can attack as explosion %s", it->to_string().c_str());
      return true;
    }
  }

  dbg("Cannot attack %s, ignore", it->to_string().c_str());

#if 0
  if (is_lava() || is_fire() || is_wand() || is_laser() || is_projectile() || is_explosion()) {
    // continue
  } else if (owner && owner->is_monst() && it->is_attackable_by_monst()) {
    // monst weapon, continue
  } else if (is_monst() && it->is_attackable_by_monst()) {
    // continue
  } else if (is_player() && it->is_attackable_by_player()) {
    // continue
  } else if (owner && owner->is_player() && it->is_attackable_by_player()) {
    // continue
  } else {
    IF_DEBUG4 { // very noisy
      dbg("Cannot attack %s", it->to_string().c_str());
    }
    return false;
  }
#endif
  return false;
}

bool Thing::attack(fpoint future_pos)
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

bool Thing::attack(Thingp it)
{
  TRACE_AND_INDENT();
  dbg("Attack %s", it->to_string().c_str());
  TRACE_AND_INDENT();
  //
  // Carry to eat later. Monsts attack their food.
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
    if (owner == it) {
      //
      // This is an odd one.
      //
      err("Trying to attack self");
    } else if (owner->can_eat(it)) {
      //
      // Eat corpse?
      //
      IF_DEBUG2 { owner->log("Can eat %s", it->to_string().c_str()); }

      if (it->is_dead) {
        if (owner->eat(it)) {
          //
          // Can't kill it twice, so hide it
          //
          IF_DEBUG1 { owner->log("Eat corpse %s", it->to_string().c_str()); }
          it->hide();
          return true;
        }
      } else if (owner->is_player()) {
        owner->log("Carry %s", it->to_string().c_str());
        if (owner->try_to_carry_if_worthwhile_dropping_items_if_needed(it)) {
          return true;
        }
        return false;
      }
    }
  } else {
    //
    // As above, but not for owner.
    //
    if (can_eat(it)) {
      dbg("Try to eat instead of attacking %s", it->to_string().c_str());
      //
      // Eat corpse?
      //
      if (is_item_carrier() &&
          ((is_jelly_eater() && it->is_jelly()) || (is_food_eater() && it->is_food()) ||
           (is_treasure_type_eater() && it->is_treasure_type()) || (is_wand_eater() && it->is_wand()) ||
           (is_potion_eater() && it->is_potion())) &&
          try_to_carry_if_worthwhile_dropping_items_if_needed(it)) {
        dbg("Don't eat, try to carry %s", it->to_string().c_str());
        return true;
      }

      if (is_monst() && it->is_dead && ! it->is_player() && eat(it)) {
        //
        // Can only eat once alive things when dead... But the player is gone once dead.
        // Can't kill it twice, so hide it
        //
        dbg("Eat corpse %s", it->to_string().c_str());
        it->hide();
        it->gc();
        return true;
      }

      if (is_monst() && it->is_food() &&
          ((is_jelly_eater() && it->is_jelly()) || (is_meat_eater() && it->is_meat()) ||
           (is_food_eater() && it->is_food())) &&
          eat(it)) {
        return true;
      }

      if (is_player()) {
        dbg("Don't attack, try to carry %s", it->to_string().c_str());
        if (try_to_carry_if_worthwhile_dropping_items_if_needed(it)) {
          return true;
        }
        return false;
      }
    }
  }

  if (! possible_to_attack(it)) {
    dbg("Attack failed, not possible to attack %s", it->to_string().c_str());
    return false;
  }

  if (is_stamina_check()) {
    if (! get_stamina()) {
      if (is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
      }
      return false;
    }
  }

  auto att_mod = stat_to_bonus(get_stat_strength()) + stat_to_bonus(get_stat_attack());
  if (owner) {
    att_mod += stat_to_bonus(owner->get_stat_strength());
    att_mod += stat_to_bonus(owner->get_stat_attack());
  }

  auto def_mod  = stat_to_bonus(it->get_stat_defence());
  auto it_owner = get_top_owner();
  if (it_owner) {
    def_mod = stat_to_bonus(it_owner->get_stat_defence());
  }

  //
  // We hit. See how much damage.
  //
  auto damage       = get_damage_melee();
  auto poison       = get_damage_poison();
  auto total_damage = damage + att_mod;

  //
  // Bite?
  //
  auto bite        = false;
  auto bite_damage = get_damage_bite();
  if (bite_damage) {
    if (pcg_random_range(0, 100) < 50) {
      total_damage = bite_damage;
      bite         = true;
    }
  }

  if (is_player()) {
    //
    // Player always uses their weapon
    //
    if (weapon_get()) {
      auto delta = it->mid_at - mid_at;
      move_set_dir_from_delta(delta);
      use_weapon();
      return true;
    }
  } else if (is_monst()) {
    //
    // Don't swing weapons at pools of blood.
    //
    if (it->is_alive_monst() || it->is_door() || it->is_player() || it->is_minion_generator()) {
      if (weapon_get()) {
        auto delta = it->mid_at - mid_at;
        move_set_dir_from_delta(delta);
        use_weapon();
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
    if (it->is_dead) {
      //
      // It's hard to miss a corpse.
      //
    } else if (it->is_always_hit()) {
      //
      // You just cannot miss this.
      //
    } else {
      // it->topcon("att_mod %d def_mod %d", att_mod, def_mod);
      auto hit = d20roll(att_mod, def_mod, fumble, crit);

      //
      // Cannot miss (if engulfing?)
      //
      if (it->mid_at == mid_at) {
        hit = true;
      }

      if (! hit) {
        if (is_player() || (owner && owner->is_player())) {
          TOPCON("You miss %s.", it->text_the().c_str());
          msg("!");
        } else if (it->is_player()) {
          if (owner) {
            TOPCON("%s misses with %s.", owner->text_the().c_str(), text_The().c_str());
          } else {
            TOPCON("%s misses.", text_The().c_str());
          }
        } else {
          dbg("The attack missed (att %d, def %d) on %s", att_mod, def_mod, it->to_string().c_str());
        }

        if (attack_lunge()) {
          lunge(it->get_interpolated_mid_at());
        }

        //
        // An attempt at an attack counts
        //
        it->add_enemy(this);

        //
        // We tried to attack, so do not move
        //
        return true;
      }
    }
  }

  if (total_damage <= 0) {
    total_damage = 1;
  }

  //
  // This handles when we are stuck inside a cleaner
  //
  if (is_engulfer()) {
    if (it->mid_at == mid_at) {
      bite_damage = get_damage_swallow();
      if (it->is_player()) {
        TOPCON("%%fg=red$You are being consumed by %s!%%fg=reset$", text_the().c_str());
        msg("Gulp!");
      }
    }
  }

  if (it->is_hit_by(this, crit, bite, poison, total_damage)) {
    dbg("The attack succeeded (dmg %d att, def %d) on %s", att_mod, def_mod, it->to_string().c_str());

    if (attack_lunge()) {
      lunge(it->get_interpolated_mid_at());
    }
    if (attack_eater()) {
      health_boost(it->get_nutrition());
    }
    if (is_killed_on_hitting() || is_killed_on_hit_or_miss()) {
      dead("by foolishness");
    }

    decr_stamina();
    return true;
  }

  it->on_miss(this);

  //
  // Missiles?
  //
  if (is_killed_on_hit_or_miss()) {
    if (is_loggable()) {
      dbg("Attack missed %s", it->to_string().c_str());
    }
    if (attack_lunge()) {
      lunge(it->get_interpolated_mid_at());
    }
    dead("by foolishness");
    return true;
  }

  return false;
}
