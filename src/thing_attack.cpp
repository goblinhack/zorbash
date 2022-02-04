//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
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

bool Thing::possible_to_attack(const Thingp victim)
{
  TRACE_NO_INDENT();
  auto me = tp();

  if (victim == this) {
    return false;
  }

  //
  // Note the victim may not be adjacent; the AI uses this to assess various
  // things that may be some distant off.
  //
  // Check adjacent. No don't. The AI uses this to look ahead.
  //
  // auto delta = victim->curr_at - curr_at;
  // if ((fabs(delta.x) > 1) || (fabs(delta.y) > 1)) {
  //   dbg("Not adjacent to attack");
  //   return false;
  // }

  auto my_owner  = get_top_owner();
  auto its_owner = victim->get_top_owner();
  if (my_owner && ((my_owner == its_owner) || (my_owner == victim))) {
    if (is_laser()) {
      //
      // This is to allow lightning to strike the owner if they fire in water
      //
    } else {
      return false;
    }
  }

  auto my_mob  = get_top_mob();
  auto its_mob = victim->get_top_mob();
  if (my_mob && (my_mob == its_mob)) {
    return false;
  }

  auto my_spawned_owner  = get_top_spawned_owner();
  auto its_spawned_owner = victim->get_top_spawned_owner();
  if (my_spawned_owner && (my_spawned_owner == its_spawned_owner)) {
    return false;
  }

  if (same_leader(victim)) {
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

  if (victim->is_on_fire()) {
    if (environ_avoids_fire()) {
      dbg("Cannot attack %s, it is on fire", victim->to_string().c_str());
      return false;
    }
  }

  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon() && ! is_explosion()) {
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

  //
  // Attacking of closed doors?
  //
  if (victim->is_door()) {
    if (me->is_able_to_break_down_doors()) {
      dbg("Can break down door %s", victim->to_string().c_str());
      return true;
    }
  }

  //
  // Don't attadk thy leader or follower
  //
  if (same_leader(victim)) {
    return false;
  }

  if (is_alive_monst() || is_resurrected) {
    if (me->is_jelly_baby_eater()) {
      if (victim->is_jelly_baby()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_treasure_eater()) {
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

    if (me->is_red_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_red_blood()) {
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

    if (me->is_green_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_green_blood()) {
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

    if (me->is_pink_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_pink_blood()) {
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
    } else if (victim->is_meltable() || victim->is_burnable() || victim->is_very_combustible() ||
               victim->is_combustible()) {
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
    if (victim->is_sticky() || victim->is_spiderweb()) {
      if (is_able_to_break_out_of_webs()) {
        dbg("Can attack and break out of web %s", victim->to_string().c_str());
        return true;
      } else {
        dbg("Can not break out of web %s", victim->to_string().c_str());
        return false;
      }
    }
  }

  if (is_weapon()) {
    if (victim->is_foilage()) {
      dbg("Can attack scenery %s", victim->to_string().c_str());
      return true;
    }
  }

  if (victim->is_alive_monst() || victim->is_combustible() || victim->is_very_combustible() ||
      victim->is_meltable() || victim->is_burnable() || victim->is_wall() || victim->is_rock() || victim->is_door() ||
      victim->is_bridge() || victim->is_dry_grass() || victim->is_wet_grass() || victim->is_treasure_type() ||
      victim->is_enchantstone() || victim->is_skillstone() || victim->is_foilage() || victim->is_spiderweb() ||
      victim->is_sticky() || victim->is_brazier() || victim->is_barrel() || victim->is_player() ||
      victim->is_food() || victim->is_bag_item()) {
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

bool Thing::possible_to_attack_at(point at)
{
  bool ret = false;

  dbg("Possible to attack? at %s", at.to_string().c_str());
  TRACE_AND_INDENT();

  FOR_ALL_COLLISION_THINGS(level, victim, at.x, at.y)
  {
    if (! possible_to_attack(victim)) {
      continue;
    }
    dbg("Yes; %s", victim->to_string().c_str());
    ret = true;
  }
  FOR_ALL_THINGS_END()

  if (! ret) {
    dbg("No");
  }

  return ret;
}

bool Thing::attack(point future_pos)
{
  bool up     = future_pos.y < curr_at.y;
  bool down   = future_pos.y > curr_at.y;
  bool left   = future_pos.x < curr_at.x;
  bool right  = future_pos.x > curr_at.x;
  bool attack = true;
  bool idle   = false;

  verify(MTYPE_THING, this);
  bool shove_allowed  = true;
  bool attack_allowed = true;
  return (move(future_pos, up, down, left, right, attack, idle, shove_allowed, attack_allowed));
}

bool Thing::attack(Thingp victim, bool prefer_natural_attack)
{
  dbg("Attack %s", victim->to_string().c_str());
  TRACE_AND_INDENT();

  set_idle_count(0);

  auto owner = get_top_owner();

  if (! possible_to_attack(victim)) {
    dbg("Attack failed, not possible to attack %s", victim->to_string().c_str());
    return false;
  }

  if (is_able_to_tire()) {
    if (get_stamina() < 5) {
      if (is_player()) {
        if (d20roll_under(get_stat_con())) {
          msg("You are so tired but dig deep and attack!");
        } else {
          msg("You are too tired to attack.");
          game->tick_begin("too tired to attack");
          return false;
        }
      }
    }
  }

  auto stat_att = get_attack_modifier(victim) - get_stat_att_penalties_total();
  auto stat_def = victim->get_stat_def_total() - victim->get_stat_def_penalties_total();

  bool damage_set       = false;
  bool attack_poison    = false;
  bool attack_future1   = false;
  bool attack_future2   = false;
  bool attack_future3   = false;
  bool attack_cold      = false;
  bool attack_fire      = false;
  bool attack_crush     = false;
  bool attack_lightning = false;
  bool attack_energy    = false;
  bool attack_acid      = false;
  bool attack_digest    = false;
  bool attack_necrosis  = false;
  bool attack_natural   = false;
  int  damage           = 0;

  dbg("Set damage types");
  TRACE_AND_INDENT();

  //
  // Chance of poison damage?
  //
  if (! damage_set || prefer_natural_attack) {
    if (d1000() < damage_poison_chance_d1000()) {
      int damage_poison = get_damage_poison();
      if (damage_poison > 0) {
        damage        = damage_poison;
        damage_set    = true;
        attack_poison = true;
        dbg("Set poison damage %d", damage);
      }
    }
  }
  //
  // Chance of attack_future1 damage?
  //
  if (! damage_set) {
    if (d1000() < damage_future1_chance_d1000()) {
      int damage_future1 = get_damage_future1();
      if (damage_future1 > 0) {
        damage         = damage_future1;
        damage_set     = true;
        attack_future1 = true;
        dbg("Set future1 damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_future2 damage?
  //
  if (! damage_set) {
    if (d1000() < damage_future2_chance_d1000()) {
      int damage_future2 = get_damage_future2();
      if (damage_future2 > 0) {
        damage         = damage_future2;
        damage_set     = true;
        attack_future2 = true;
        dbg("Set future2 damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_future3 damage?
  //
  if (! damage_set) {
    if (d1000() < damage_future3_chance_d1000()) {
      int damage_future3 = get_damage_future3();
      if (damage_future3 > 0) {
        damage         = damage_future3;
        damage_set     = true;
        attack_future3 = true;
        dbg("Set future3 damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_cold damage?
  //
  if (! damage_set) {
    if (d1000() < damage_cold_chance_d1000()) {
      int damage_cold = get_damage_cold();
      if (damage_cold > 0) {
        damage      = damage_cold;
        damage_set  = true;
        attack_cold = true;
        dbg("Set cold damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_fire damage?
  //
  if (! damage_set) {
    if (d1000() < damage_fire_chance_d1000()) {
      int damage_fire = get_damage_fire();
      if (damage_fire > 0) {
        damage      = damage_fire;
        damage_set  = true;
        attack_fire = true;
        dbg("Set fire damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_crush damage?
  //
  if (! damage_set) {
    if (d1000() < damage_crush_chance_d1000()) {
      int damage_crush = get_damage_crush();
      if (damage_crush > 0) {
        damage       = damage_crush;
        damage_set   = true;
        attack_crush = true;
        dbg("Set crush damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_lightning damage?
  //
  if (! damage_set) {
    if (d1000() < damage_lightning_chance_d1000()) {
      int damage_lightning = get_damage_lightning();
      if (damage_lightning > 0) {
        damage           = damage_lightning;
        damage_set       = true;
        attack_lightning = true;
        dbg("Set lightning damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_energy damage?
  //
  if (! damage_set) {
    if (d1000() < damage_energy_chance_d1000()) {
      int damage_energy = get_damage_energy();
      if (damage_energy > 0) {
        damage        = damage_energy;
        damage_set    = true;
        attack_energy = true;
        dbg("Set energy damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_acid damage?
  //
  if (! damage_set) {
    if (d1000() < damage_acid_chance_d1000()) {
      int damage_acid = get_damage_acid();
      if (damage_acid > 0) {
        damage      = damage_acid;
        damage_set  = true;
        attack_acid = true;
        dbg("Set acid damage %d", damage);
      }
    }
  }

  //
  // Chance of attack_digest damage?
  //
  if (! damage_set) {
    if (d1000() < damage_digest_chance_d1000()) {
      int damage_digest = get_damage_digest();
      if (damage_digest > 0) {
        damage        = damage_digest;
        damage_set    = true;
        attack_digest = true;
        dbg("Set digest damage %d", damage);
      }
    }
  }

  //
  // Chance of necrosis damage?
  //
  if (! damage_set || prefer_natural_attack) {
    if (d1000() < damage_necrosis_chance_d1000()) {
      int damage_necrosis = get_damage_necrosis();
      if (damage_necrosis > 0) {
        damage          = damage_necrosis;
        damage_set      = true;
        attack_necrosis = true;
        dbg("Set necro damage %d", damage);
      }
    }
  }

  //
  // Bite?
  //
  if (! damage_set || prefer_natural_attack) {
    if (d1000() < damage_natural_attack_chance_d1000()) {
      int damage_natural_attack = get_damage_natural_attack();
      if (damage_natural_attack > 0) {
        damage         = damage_natural_attack + stat_att;
        damage_set     = true;
        attack_natural = true;
        dbg("Set natural damage %d", damage);
      }
    }
  }

  //
  // Melee?
  //
  // Not sure if I should keep melee chance as it is the fallback attack if nothing
  // else hits.
  //
  if (! damage_set) {
    if (d1000() < damage_melee_chance_d1000()) {
      damage = get_damage_melee() + stat_att;
      if (damage > 0) {
        dbg("Set melee damage %d", damage);
        damage_set = true;
      }
    }
  }
  if (! damage_set) {
    if (owner) {
      if (d1000() < owner->damage_melee_chance_d1000()) {
        damage = get_damage_melee() + stat_att;
        if (damage > 0) {
          dbg("Set melee damage %d", damage);
          damage_set = true;
        }
      }
    }
  }

  //
  // This overrides other damage types. For when we are stuck inside a cleaner
  //
  if (is_engulfer()) {
    if (victim->curr_at == curr_at) {
      damage           = get_damage_digest();
      attack_poison    = false;
      attack_future1   = false;
      attack_future2   = false;
      attack_future3   = false;
      attack_cold      = false;
      attack_fire      = false;
      attack_crush     = false;
      attack_lightning = false;
      attack_energy    = false;
      attack_acid      = false;
      attack_digest    = true;
      attack_necrosis  = false;
      attack_natural   = false;
      damage_set       = true;
    }
  }

  //
  // If some attack type worked, then make sure we have some damage
  //
  if (damage_set) {
    if (damage < 1) {
      damage = 1;
    }
  }

  if (damage <= 0) {
    if (is_player() || (owner && owner->is_player())) {
      msg("You inflict no damage on %s.", victim->text_the().c_str());
    }
    dbg("Attack failed, no damage");
    return false;
  }

  if (is_player()) {
    //
    // Player always uses their weapon
    //
    if (get_equip(MONST_EQUIP_WEAPON)) {
      auto delta = victim->curr_at - curr_at;
      move_set_dir_from_target_or_delta(delta);
      equip_use_may_attack(MONST_EQUIP_WEAPON);
      return true;
    }
  } else if (is_monst()) {
    //
    // Don't swing weapons at pools of blood.
    //
    if (victim->is_alive_monst() || victim->is_door() || victim->is_player() || victim->is_mob()) {
      if (get_equip(MONST_EQUIP_WEAPON)) {
        auto delta = victim->curr_at - curr_at;
        move_set_dir_from_target_or_delta(delta);
        equip_use_may_attack(MONST_EQUIP_WEAPON);
        return true;
      }
    } else if (is_monst()) {
      attack_natural = true;
    }
  }

  bool crit = false;

  //
  // See if we can bypass its defences
  //
  if (is_player() || is_alive_monst() || (owner && (owner->is_player() || owner->is_alive_monst()))) {
    if (victim->is_dead) {
      //
      // It's hard to miss a corpse.
      //
    } else if (victim->is_always_hit()) {
      //
      // You just cannot miss this.
      //
    } else {
      bool hit      = false;
      int  to_hit   = stat_def - stat_att;
      int  i_rolled = d20();

      if (i_rolled == 20) {
        crit = true;
        hit  = true;
        dbg("Attack on %s: ATT %s AC %d, to-hit %d, crit rolled %d -> hit", victim->to_short_string().c_str(),
            modifier_to_string(stat_att).c_str(), stat_def, to_hit, i_rolled);
      } else if (i_rolled == 1) {
        hit = false;
        dbg("Attack on %s: ATT %s AC %d, to-hit %d, fumble rolled %d -> miss", victim->to_short_string().c_str(),
            modifier_to_string(stat_att).c_str(), stat_def, to_hit, i_rolled);
      } else {
        hit = i_rolled >= to_hit;
        dbg("Attack on %s: ATT %s AC %d, to-hit %d, rolled %d -> %s", victim->to_short_string().c_str(),
            modifier_to_string(stat_att).c_str(), stat_def, to_hit, i_rolled, hit ? "hit" : "miss");
      }

      //
      // Cannot miss (if engulfing?)
      //
      if (victim->curr_at == curr_at) {
        hit = true;
      }

      if (! hit) {
        if (is_player() || (owner && owner->is_player())) {
          msg("You miss %s.", victim->text_the().c_str());
          popup("missed!");
        } else if (victim->is_player()) {
          if (owner) {
            msg("%s misses with %s.", owner->text_the().c_str(), text_the().c_str());
          } else {
            msg("%s misses.", text_The().c_str());
          }
          popup("misses!");
        } else {
          dbg("The attack missed (att modifier %d, AC %d) on %s", stat_att, stat_def, victim->to_string().c_str());
        }

        if (victim != this) {
          if (attack_lunge()) {
            lunge(victim->curr_at);
          }
        }

        //
        // An attempt at an attack counts
        //
        victim->add_enemy(this);

        //
        // See if armor crumbles
        //
        auto armor = victim->get_equip(MONST_EQUIP_ARMOR);
        if (armor) {
          if (d10000() < armor->break_chance_d10000()) {
            if (is_player()) {
              msg("%s falls apart.", armor->text_The().c_str());
              popup("!!!");
            }
            armor->dead("broken");
          }
        }

        auto shield = victim->get_equip(MONST_EQUIP_SHIELD);
        if (shield) {
          if (d10000() < shield->break_chance_d10000()) {
            if (is_player()) {
              msg("%s falls apart.", shield->text_The().c_str());
              popup("!!!");
            }
            shield->dead("broken");
          }
        }

        auto helmet = victim->get_equip(MONST_EQUIP_HELMET);
        if (helmet) {
          if (d10000() < helmet->break_chance_d10000()) {
            if (is_player()) {
              msg("%s falls apart.", helmet->text_The().c_str());
              popup("!!!");
            }
            helmet->dead("broken");
          }
        }

        //
        // We tried to attack, so do not move
        //
        return true;
      }
    }
  }

  dbg("Do the hit");
  TRACE_AND_INDENT();
  if (victim->is_hit(this, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                     attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy,
                     attack_acid, attack_digest, damage)) {
    dbg("The attack succeeded");

    if (victim != this) {
      if (attack_lunge()) {
        lunge(victim->curr_at);
      }
    }
    if (attack_eater()) {
      health_boost(victim->get_nutrition());
    }
    if (is_destroyed_on_hitting() || is_destroyed_on_hit_or_miss()) {
      dead("by foolishness");
    }

    //
    // See if the weapon crumbles
    //
    auto my_owner = get_top_owner();
    if (my_owner) {
      auto weapon = my_owner->get_equip(MONST_EQUIP_WEAPON);
      if (weapon) {
        auto break_chance = weapon->break_chance_d10000();
        if (victim->is_toughness_soft()) {
          break_chance /= 2;
        }
        if (victim->is_toughness_hard()) {
          break_chance *= 2;
        }
        if (victim->is_toughness_very_tough()) {
          break_chance *= 2;
        }
        if (d10000() < break_chance) {
          weapon->dead("broken");
        }
      }

      auto gauntlet = my_owner->get_equip(MONST_EQUIP_GAUNTLET);
      if (gauntlet) {
        auto break_chance = gauntlet->break_chance_d10000();
        if (victim->is_toughness_soft()) {
          break_chance /= 2;
        }
        if (victim->is_toughness_hard()) {
          break_chance *= 2;
        }
        if (victim->is_toughness_very_tough()) {
          break_chance *= 2;
        }
        if (d10000() < break_chance) {
          gauntlet->dead("broken");
        }
      }
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
    if (victim != this) {
      if (attack_lunge()) {
        lunge(victim->curr_at);
      }
    }
    dead("by foolishness");
    return true;
  }

  return false;
}
bool Thing::natural_attack(Thingp victim) { return attack(victim, true); }

int Thing::is_attacked_with_damage_melee(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_natural_attack(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = true;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_poison(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = true;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_necrosis(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = true;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_future1(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = true;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_future2(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = true;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_future3(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = true;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_cold(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = true;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_fire(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = true;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_crush(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = true;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_lightning(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = true;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_energy(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = true;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_acid(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = true;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}

int Thing::is_attacked_with_damage_digest(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_natural   = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_cold      = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = true;
  return (is_hit(hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning, attack_energy, attack_acid,
                 attack_digest, damage));
}
