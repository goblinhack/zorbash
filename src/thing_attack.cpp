//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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

  auto my_owner  = top_owner();
  auto its_owner = victim->top_owner();
  if (my_owner && ((my_owner == its_owner) || (my_owner == victim))) {
    if (is_able_to_attack_owner()) {
      //
      // Sword of plutonium / lightning fork.
      //
      return true;
    }

    return false;
  }

  auto my_mob  = top_mob();
  auto its_mob = victim->top_mob();
  if (my_mob && (my_mob == its_mob)) {
    return false;
  }

  auto my_spawned_owner  = top_spawned_owner();
  auto its_spawned_owner = victim->top_spawned_owner();
  if (my_spawned_owner && (my_spawned_owner == its_spawned_owner)) {
    return false;
  }

  if (same_leader(victim)) {
    return false;
  }

  dbg("Is it possible to attack %s?", victim->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // Weapons can't attack all by themselves. That would be nuts.
  //
  if (is_weapon() || is_wand_or_staff() || is_ring()) {
    if (! my_owner) {
      dbg("Cannot attack %s, I have no owner", victim->to_short_string().c_str());
      return false;
    }
  } else {
    //
    // If stuck in ice, we can only attack locally
    //
    if (level->is_block_of_ice(curr_at)) {
      if (victim->curr_at != curr_at) {
        dbg("Cannot attack %s, stuck in ice", victim->to_short_string().c_str());
        return false;
      }
    }

    //
    // If stuck in a web, we can only attack locally
    //
    if (! is_immune_to_spiderwebs()) {
      if (level->is_spiderweb(curr_at)) {
        if (victim->curr_at != curr_at) {
          dbg("Cannot attack %s, stuck in a web", victim->to_short_string().c_str());
          return false;
        }
      }
    }

    //
    // If trapped in an engulfer, you can only attack locally
    //
    FOR_ALL_COLLISION_THINGS(level, t, curr_at.x, curr_at.y)
    {
      if (t == this) {
        continue;
      }

      if (t == victim) {
        continue;
      }

      if (t->is_engulfer()) {
        //
        // If stuck in an engulfer, we can only attack locally
        //
        if (victim->curr_at != curr_at) {
          dbg("Cannot attack %s, stuck in an engulfer (%s)", victim->to_short_string().c_str(),
              t->to_short_string().c_str());
          return false;
        }
      }
    }
    FOR_ALL_THINGS_END();
  }

  //
  // Cannot attack something firey
  //
  if (victim->is_on_fire()) {
    if (environ_avoids_fire()) {
      dbg("Cannot attack %s, it is on fire", victim->to_short_string().c_str());
      return false;
    }
  }

  if (victim->is_cold()) {
    if (environ_avoids_cold()) {
      dbg("Cannot attack %s, it is cold", victim->to_short_string().c_str());
      return false;
    }
  }

  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon() && ! is_explosion()) {
      dbg("Cannot attack %s, I am fire", victim->to_short_string().c_str());
      return false;
    }
  }

  if (is_meat_eater() || attack_meat()) {
    //
    // Meat eaters eat you when you are dead!
    //
    if (victim->is_meat()) {
      dbg("Allow meat eater attack on corpse of %s", victim->to_short_string().c_str());
      return true;
    }
  } else {
    if (victim->is_dead) {
      if (victim->is_frozen) {
        dbg("Allow frozen corpse attack on %s", victim->to_short_string().c_str());
        return true;
      } else {
        dbg("Cannot attack %s, it's dead", victim->to_short_string().c_str());
        return false;
      }
    }
  }

  //
  // No attacking of open doors!
  //
  if (victim->is_open) {
    dbg("Cannot attack %s, it's open", victim->to_short_string().c_str());
    return false;
  }

  //
  // Attacking of closed doors?
  //
  if (victim->is_door()) {
    if (me->is_able_to_break_down_doors()) {
      dbg("Can break down door %s", victim->to_short_string().c_str());
      return true;
    }
  }

  //
  // Don't attadk thy leader or follower
  //
  if (same_leader(victim)) {
    return false;
  }

  //
  // Monsters (alive ones) can attack.
  // Or resurrected monsters.
  // Or carnivorous plants.
  //
  if ((! is_dead && is_carnivorous_plant()) || is_alive_monst() || is_resurrected) {
    if (me->is_jelly_baby_eater()) {
      if (victim->is_jelly_baby()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_treasure_eater()) {
      if (victim->is_treasure_type()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
      if (victim->is_carrying_treasure()) {
        dbg("Can steal from %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_potion_eater()) {
      if (victim->is_potion()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
    }

    //
    // Cleaners can attack cleaners?
    //
    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical_eater()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
    }

    //
    // Can we eats it?
    //
    if (me->is_meat_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", victim->to_short_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead meat: %s", victim->to_short_string().c_str());
          return true;
        }

        dbg("Can attack meat or blood: %s", victim->to_short_string().c_str());
        return true;
      }
    }

    //
    // Can we attack the meat? Only if it is alive.
    //
    if (me->attack_meat()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("no, cannot attack %s, not is_attackable by meat eating monst", victim->to_short_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_short_string().c_str());
          return false;
        }
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_short_string().c_str());
          return false;
        }

        dbg("Can attack living meat: %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_red_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_short_string().c_str());
        return false;
      }

      if (victim->is_red_blood()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead blood: %s", victim->to_short_string().c_str());
          return true;
        }

        dbg("Can attack blood or blood: %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->is_green_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_short_string().c_str());
        return false;
      }

      if (victim->is_green_blood()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead blood: %s", victim->to_short_string().c_str());
          return true;
        }

        dbg("Can attack blood or blood: %s", victim->to_short_string().c_str());
        return true;
      }
    }

    if (me->attack_humanoid()) {
      if (victim->is_humanoid()) {
        if (! victim->is_dead) {
          dbg("Can attack humanoid: %s", victim->to_short_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_living()) {
      if (victim->is_living()) {
        if (! victim->is_dead) {
          dbg("Can attack living: %s", victim->to_short_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_undead()) {
      if (victim->is_undead()) {
        if (! victim->is_dead) {
          dbg("Can attack undead: %s", victim->to_short_string().c_str());
          return true;
        }
      }
    }

    if (me->is_food_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by food eating monst", victim->to_short_string().c_str());
        return false;
      }
      if (victim->is_food()) {
        dbg("Can attack food: %s", victim->to_short_string().c_str());
        return true;
      }
    }
  }

  if (is_player()) {
    if (victim->is_attackable_by_player()) {
      if (game->robot_mode) {
        if (victim->is_barrel()) {
          dbg("No, do not attack %s, is explosive barrel", victim->to_short_string().c_str());
          return false;
        }
      }
      if (victim->is_foilage() || victim->is_carnivorous_plant()) {
        dbg("No, do not attack %s", victim->to_short_string().c_str());
        return false;
      }
      dbg("Can attack %s", victim->to_short_string().c_str());
      return true;
    }
    dbg("No, cannot attack %s, not is_attackable", victim->to_short_string().c_str());
    return false;
  }

  if (is_weapon()) {
    auto o = immediate_owner();
    if (o) {
      if (o->is_monst()) {
        if (! victim->is_attackable_by_monst()) {
          // Too noisy
          // dbg("Cannot weapon attack %s, not is_attackable by monst",
          //     victim->to_short_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      } else {
        if (! victim->is_attackable_by_player()) {
          dbg("Cannot weapon attack %s, not is_attackable by player", victim->to_short_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_short_string().c_str());
        return true;
      }
    }
  }

  if (me->is_fire() || me->is_lava()) {
    if (me->is_monst()) {
      //
      // Fire monsters do not attack always
      //
    } else if (victim->is_meltable() || victim->is_able_to_burn() || victim->is_very_combustible() ||
               victim->is_combustible()) {
      if (! victim->is_fire() && ! victim->is_lava()) {
        dbg("Can attack as I am firey %s", victim->to_short_string().c_str());
        return true;
      }
    }
  }

  if (is_enemy(victim)) {
    dbg("Can attack enemy %s", victim->to_short_string().c_str());
    return true;
  }

  if (is_weapon()) {
    if (victim->is_sticky() || victim->is_spiderweb()) {
      if (is_able_to_break_out_of_webs()) {
        dbg("Can attack and break out of web %s", victim->to_short_string().c_str());
        return true;
      } else {
        dbg("Can not break out of web %s", victim->to_short_string().c_str());
        return false;
      }
    }

    if (victim->is_block_of_ice()) {
      if (is_able_to_break_out_of_ice()) {
        dbg("Can attack and break out of ice %s", victim->to_short_string().c_str());
        return true;
      } else {
        dbg("Can not break out of web %s", victim->to_short_string().c_str());
        return false;
      }
    }

    if (victim->is_foilage() || victim->is_carnivorous_plant()) {
      dbg("Can attack scenery %s", victim->to_short_string().c_str());
      return true;
    }
  }

  if (victim->is_alive_monst() || victim->is_combustible() || victim->is_very_combustible() ||
      victim->is_meltable() || victim->is_able_to_burn() || victim->is_wall() || victim->is_rock() ||
      victim->is_door() || victim->is_bridge() || victim->is_dry_grass() || victim->is_wet_grass() ||
      victim->is_treasure_type() || victim->is_enchantstone() || victim->is_skillstone() || victim->is_foilage() ||
      victim->is_carnivorous_plant() || victim->is_spiderweb() || victim->is_block_of_ice() || victim->is_sticky() ||
      victim->is_brazier() || victim->is_barrel() || victim->is_player() || victim->is_food() ||
      victim->is_bag_item()) {
    if (is_laser()) {
      dbg("Can attack as laser %s", victim->to_short_string().c_str());
      return true;
    }

    if (is_projectile()) {
      dbg("Can attack as projectile %s", victim->to_short_string().c_str());
      return true;
    }

    if (is_wand_or_staff()) {
      dbg("Can attack as wand %s", victim->to_short_string().c_str());
      return true;
    }

    if (is_ring()) {
      dbg("Can attack as ring %s", victim->to_short_string().c_str());
      return true;
    }

    if (is_explosion()) {
      dbg("Can attack as explosion %s", victim->to_short_string().c_str());
      return true;
    }
  }

  dbg("Cannot attack %s, ignore", victim->to_short_string().c_str());

  return false;
}

bool Thing::possible_to_attack_at(point at)
{
  dbg("Possible to attack? at %s", at.to_string().c_str());
  TRACE_AND_INDENT();

  bool ret = false;

  FOR_ALL_COLLISION_THINGS(level, victim, at.x, at.y)
  {
    if (! possible_to_attack(victim)) {
      continue;
    }
    dbg("Yes; %s", victim->to_short_string().c_str());
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
  dbg("Attack at %s", future_pos.to_string().c_str());
  TRACE_AND_INDENT();

  bool up     = future_pos.y < curr_at.y;
  bool down   = future_pos.y > curr_at.y;
  bool left   = future_pos.x < curr_at.x;
  bool right  = future_pos.x > curr_at.x;
  bool attack = true;
  bool idle   = false;

  verify(MTYPE_THING, this);

  AttackOptions attack_options {};
  attack_options.shove_allowed  = true;
  attack_options.attack_allowed = true;
  attack_options.attack_at      = future_pos;
  attack_options.attack_at_set  = true;

  return (move(future_pos, up, down, left, right, attack, idle, &attack_options));
}

bool Thing::attack(Thingp victim, AttackOptions *attack_options)
{
  dbg("Attack %s", victim->to_short_string().c_str());
  TRACE_AND_INDENT();

  idle_count_set(0);

  auto owner = top_owner();

  if (! possible_to_attack(victim)) {
    dbg("Attack failed, not possible to attack %s", victim->to_short_string().c_str());
    return false;
  }

  if (victim->is_falling) {
    dbg("Attack failed, victim is falling %s", victim->to_short_string().c_str());
    return false;
  }

  //
  // Too tired to attack
  //
  if (is_able_to_tire()) {
    if (stamina() < 5) {
      if (is_player()) {
        if (d20roll_under(stat_con_total())) {
          msg("You are so tired but dig deep and attack!");
        } else {
          msg("You are too tired to attack.");
          game->tick_begin("too tired to attack");
          return false;
        }
      }
    }
  }

  //
  // Too groggy to attack
  //
  if ((game->tick_current - infop()->tick_last_awoke < 2)) {
    dbg("Just woke up, cannot attack yet");
    return false;
  }

  //
  // Allow multiple attacks
  //
  bool tried_to_attack = false;
  int  attack_count    = 0;

  for (int attack_num = 0; attack_num < attacks_per_round(); attack_num++) {
    bool fumble = false;

    dbg("Attack num #%d", attack_num);
    TRACE_AND_INDENT();

    attack_options->attack_num = attack_num;

    if (attack_options->attack_poison) {
      dbg("Attack type already set: attack_poison");
    } else if (attack_options->attack_future1) {
      dbg("Attack type already set: attack_future1");
    } else if (attack_options->attack_future2) {
      dbg("Attack type already set: attack_future2");
    } else if (attack_options->attack_future3) {
      dbg("Attack type already set: attack_future3");
    } else if (attack_options->attack_cold) {
      dbg("Attack type already set: attack_cold");
    } else if (attack_options->attack_fire) {
      dbg("Attack type already set: attack_fire");
    } else if (attack_options->attack_crush) {
      dbg("Attack type already set: attack_crush");
    } else if (attack_options->attack_lightning) {
      dbg("Attack type already set: attack_lightning");
    } else if (attack_options->attack_energy) {
      dbg("Attack type already set: attack_energy");
    } else if (attack_options->attack_acid) {
      dbg("Attack type already set: attack_acid");
    } else if (attack_options->attack_digest) {
      dbg("Attack type already set: attack_digest");
    } else if (attack_options->attack_necrosis) {
      dbg("Attack type already set: attack_necrosis");
    } else if (attack_options->attack_draining) {
      dbg("Attack type already set: attack_draining");
    }

    //
    // Attack  is 1d20 + stat_att_total - penalties
    // Defence is        stat_def_total - penalties
    //
    auto attack_bonus = stat_att_total() - stat_att_penalties_total();
    if (owner) {
      attack_bonus = owner->stat_att_total() - owner->stat_att_penalties_total();
    }

    auto stat_def = victim->stat_def_total() - victim->stat_def_penalties_total();

    dbg("Set damage types");
    TRACE_AND_INDENT();

    //
    // Chance of poison damage?
    //
    if (! attack_options->attack_poison) {
      if (! attack_options->damage_set || attack_options->prefer_nat_att) {
        if (d1000() < damage_poison_chance_d1000(attack_options->attack_num)) {
          int damage_poison_val = damage_poison();
          if (damage_poison_val > 0) {
            attack_options->damage        = damage_poison_val;
            attack_options->damage_set    = true;
            attack_options->attack_poison = true;
            victim->poison_reason_set(text_a_or_an());
          }
        }
      }
    }

    //
    // Chance of attack_future1 damage?
    //
    if (! attack_options->attack_future1) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_future1_chance_d1000(attack_options->attack_num)) {
          int damage_future1_val = damage_future1();
          if (damage_future1_val > 0) {
            attack_options->damage         = damage_future1_val;
            attack_options->damage_set     = true;
            attack_options->attack_future1 = true;
            dbg("Set future1 damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_future2 damage?
    //
    if (! attack_options->attack_future2) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_future2_chance_d1000(attack_options->attack_num)) {
          int damage_future2_val = damage_future2();
          if (damage_future2_val > 0) {
            attack_options->damage         = damage_future2_val;
            attack_options->damage_set     = true;
            attack_options->attack_future2 = true;
            dbg("Set future2 damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_future3 damage?
    //
    if (! attack_options->damage_set) {
      if (d1000() < damage_future3_chance_d1000(attack_options->attack_num)) {
        int damage_future3_val = damage_future3();
        if (damage_future3_val > 0) {
          attack_options->damage         = damage_future3_val;
          attack_options->damage_set     = true;
          attack_options->attack_future3 = true;
          dbg("Set future3 damage %d", attack_options->damage);
        }
      }
    }

    //
    // Chance of attack_cold damage?
    //
    if (! attack_options->attack_cold) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_cold_chance_d1000(attack_options->attack_num)) {
          int damage_cold_val = damage_cold();
          if (damage_cold_val > 0) {
            attack_options->damage      = damage_cold_val;
            attack_options->damage_set  = true;
            attack_options->attack_cold = true;
            dbg("Set cold damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_fire damage?
    //
    if (! attack_options->attack_fire) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_fire_chance_d1000(attack_options->attack_num)) {
          int damage_fire_val = damage_fire();
          if (damage_fire_val > 0) {
            attack_options->damage      = damage_fire_val;
            attack_options->damage_set  = true;
            attack_options->attack_fire = true;
            dbg("Set fire damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_crush damage?
    //
    if (! attack_options->attack_crush) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_crush_chance_d1000(attack_options->attack_num)) {
          int damage_crush_val = damage_crush();
          if (damage_crush_val > 0) {
            attack_options->damage       = damage_crush_val;
            attack_options->damage_set   = true;
            attack_options->attack_crush = true;
            dbg("Set crush damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_lightning damage?
    //
    if (! attack_options->attack_lightning) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_lightning_chance_d1000(attack_options->attack_num)) {
          int damage_lightning_val = damage_lightning();
          if (damage_lightning_val > 0) {
            attack_options->damage           = damage_lightning_val;
            attack_options->damage_set       = true;
            attack_options->attack_lightning = true;
            dbg("Set lightning damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_energy damage?
    //
    if (! attack_options->attack_energy) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_energy_chance_d1000(attack_options->attack_num)) {
          int damage_energy_val = damage_energy();
          if (damage_energy_val > 0) {
            attack_options->damage        = damage_energy_val;
            attack_options->damage_set    = true;
            attack_options->attack_energy = true;
            dbg("Set energy damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_acid damage?
    //
    if (! attack_options->attack_acid) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_acid_chance_d1000(attack_options->attack_num)) {
          int damage_acid_val = damage_acid();
          if (damage_acid_val > 0) {
            attack_options->damage      = damage_acid_val;
            attack_options->damage_set  = true;
            attack_options->attack_acid = true;
            dbg("Set acid damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_water damage?
    //
    if (! attack_options->attack_water) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_water_chance_d1000(attack_options->attack_num)) {
          int damage_water_val = damage_water();
          if (damage_water_val > 0) {
            attack_options->damage       = damage_water_val;
            attack_options->damage_set   = true;
            attack_options->attack_water = true;
            dbg("Set water damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack_digest damage?
    //
    if (! attack_options->attack_digest) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_digest_chance_d1000(attack_options->attack_num)) {
          int damage_digest_val = damage_digest();
          if (damage_digest_val > 0) {
            attack_options->damage        = damage_digest_val;
            attack_options->damage_set    = true;
            attack_options->attack_digest = true;
            dbg("Set digest damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of necrosis damage?
    //
    if (! attack_options->attack_necrosis) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_necrosis_chance_d1000(attack_options->attack_num)) {
          int damage_necrosis_val = damage_necrosis();
          if (damage_necrosis_val > 0) {
            attack_options->damage          = damage_necrosis_val;
            attack_options->damage_set      = true;
            attack_options->attack_necrosis = true;
            dbg("Set necro damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of stamina damage?
    //
    if (! attack_options->attack_draining) {
      if (! attack_options->damage_set) {
        if (d1000() < damage_draining_chance_d1000(attack_options->attack_num)) {
          int damage_draining_val = damage_draining();
          if (damage_draining_val > 0) {
            attack_options->damage          = damage_draining_val;
            attack_options->damage_set      = true;
            attack_options->attack_draining = true;
            dbg("Set drain damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Bite?
    //
    if (! attack_options->attack_natural) {
      if (! attack_options->damage_set || attack_options->prefer_nat_att) {
        if (d1000() < damage_nat_att_chance_d1000(attack_options->attack_num)) {
          int damage_nat_att_val = damage_nat_att();
          if (damage_nat_att_val > 0) {
            attack_options->damage         = damage_nat_att_val + attack_bonus;
            attack_options->damage_set     = true;
            attack_options->attack_natural = true;
            dbg("Set natural damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Melee?
    //
    // Not sure if I should keep melee chance as it is the fallback attack if nothing
    // else hits.
    //
    if (! attack_options->damage_set) {
      if (d1000() < damage_melee_chance_d1000(attack_options->attack_num)) {
        auto damage            = damage_melee();
        attack_options->damage = damage + attack_bonus;
        dbg("Set melee damage %d attack_bonus %d", damage, attack_bonus);
        if (attack_options->damage > 0) {
          attack_options->damage_set = true;
        }
      }
    }

    if (! attack_options->damage_set) {
      if (owner) {
        if (d1000() < owner->damage_melee_chance_d1000(attack_options->attack_num)) {
          auto damage            = damage_melee();
          attack_options->damage = damage + attack_bonus;
          dbg("Set owner melee damage %d attack_bonus %d", damage, attack_bonus);
          if (attack_options->damage > 0) {
            attack_options->damage_set = true;
          }
        }
      }
    }

    //
    // This overrides other damage types. For when we are stuck inside a cleaner
    //
    if (is_engulfer()) {
      if (victim->curr_at == curr_at) {
        attack_options->damage           = damage_digest();
        attack_options->attack_poison    = false;
        attack_options->attack_future1   = false;
        attack_options->attack_future2   = false;
        attack_options->attack_future3   = false;
        attack_options->attack_cold      = false;
        attack_options->attack_fire      = false;
        attack_options->attack_crush     = false;
        attack_options->attack_lightning = false;
        attack_options->attack_energy    = false;
        attack_options->attack_acid      = false;
        attack_options->attack_digest    = true;
        attack_options->attack_necrosis  = false;
        attack_options->attack_natural   = false;
        attack_options->damage_set       = true;
      }
    }

    //
    // If some attack type worked, then make sure we have some damage
    //
    if (attack_options->damage_set) {
      if (attack_options->damage < 1) {
        attack_options->damage = 1;
      }
    }

    //
    // An attack counts as making noise.
    //
    if (owner) {
      level->noisemap_in_incr(curr_at.x, curr_at.y, owner->noise_total());
    } else {
      level->noisemap_in_incr(curr_at.x, curr_at.y, noise_total());
    }

    if (attack_options->damage <= 0) {
      //
      // Wake on attack
      //
      victim->wake("attacked, but no damage");

      if (is_player() || (owner && owner->is_player())) {
        //
        // If hitting a rock with a damaged weapon, give more feedback as to why there is no damage.
        //
        if (is_weapon() && (weapon_damaged_pct() < 100)) {
          msg("Your damaged weapon inflicts no damage on %s.", victim->text_the().c_str());
        } else {
          msg("You inflict no damage on %s.", victim->text_the().c_str());
        }

        if (game->robot_mode) {
          BOTCON("Robot fails to damage %s.", victim->text_the().c_str());
        }
      }
      dbg("Attack failed, no damage");
      return false;
    }

    if (is_player()) {
      //
      // Player always uses their weapon
      //
      if (equip_get(MONST_EQUIP_WEAPON)) {
        auto delta = victim->curr_at - curr_at;
        move_set_dir_from_dest_or_delta(delta);
        equip_use_may_attack(MONST_EQUIP_WEAPON);
        victim->wake("player attacked with weapon");
        return true;
      }
    } else if (is_monst()) {
      //
      // Don't swing weapons at pools of blood.
      //
      if (victim->is_alive_monst() || victim->is_door() || victim->is_player() || victim->is_mob()) {
        if (equip_get(MONST_EQUIP_WEAPON)) {
          auto delta = victim->curr_at - curr_at;
          move_set_dir_from_dest_or_delta(delta);
          equip_use_may_attack(MONST_EQUIP_WEAPON);
          victim->wake("monst attacked with weapon");
          return true;
        }
      } else if (is_monst()) {
        attack_options->attack_natural = true;
      }
    }

    bool missed = false;

    if (d10000() < crit_chance_d10000()) {
      attack_options->crit = true;
    }

    if (! attack_options->crit) {
      if (victim->is_stuck()) {
        if (d10000() < crit_chance_d10000()) {
          attack_options->crit = true;
        }
      }
    }

    if (victim->is_sleeping) {
      attack_options->crit = true;
    }

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
        //
        // Attack  is 1d20 + stat_att_total - penalties
        // Defence is        stat_def_total - penalties
        //
        bool hit      = false;
        int  to_hit   = stat_def;
        int  i_rolled = d20();

        if (i_rolled == 20) {
          attack_options->crit = true;
          hit                  = true;
          con("Attack on %s: ATT %s DEF %d, to-hit %d, crit rolled %d -> hit", victim->to_short_string().c_str(),
              modifier_to_string(attack_bonus).c_str(), stat_def, to_hit, i_rolled);
        } else if (i_rolled == 1) {
          hit    = false;
          fumble = true;
          con("Attack on %s: ATT %s DEF %d, to-hit %d, fumble rolled %d -> miss", victim->to_short_string().c_str(),
              modifier_to_string(attack_bonus).c_str(), stat_def, to_hit, i_rolled);
        } else {
          i_rolled += attack_bonus;
          hit = i_rolled >= to_hit;
          con("Attack on %s: ATT %s DEF %d, to-hit %d, rolled %d -> %s", victim->to_short_string().c_str(),
              modifier_to_string(attack_bonus).c_str(), stat_def, to_hit, i_rolled, hit ? "hit" : "miss");
        }

        //
        // Cannot miss (if engulfing?)
        //
        if (victim->curr_at == curr_at) {
          hit = true;
        }

        if (! hit) {
          if (is_player() || (owner && owner->is_player())) {
            if (fumble) {
              msg("You fubmle and miss %s.", victim->text_the().c_str());
              popup("You fumble!");
            } else {
              msg("You miss %s.", victim->text_the().c_str());
              popup("You miss!");
            }
            if (game->robot_mode) {
              BOTCON("Robot misses %s.", victim->text_the().c_str());
            }
          } else if (victim->is_player()) {
            if (owner) {
              msg("%s misses you with %s.", owner->text_the().c_str(), text_the().c_str());
            } else {
              msg("%s misses you.", text_The().c_str());
            }
            popup("It misses you!");

            if (game->robot_mode) {
              BOTCON("%s misses the robot.", text_the().c_str());
            }
          } else {
            dbg("The attack missed (att modifier %d, AC %d) on %s", attack_bonus, stat_def,
                victim->to_short_string().c_str());
          }

          if (victim != this) {
            if (attack_lunge()) {
              lunge(victim->curr_at);
            }
          }

          //
          // An attempt at an attack counts
          //
          if (victim->wake("missed, but should still wake")) {
            victim->add_enemy(this);
          }

          //
          // See if armor crumbles
          //
          auto armor = victim->equip_get(MONST_EQUIP_ARMOR);
          if (armor) {
            weapon_check_for_damage(armor, victim);
          }

          auto shield = victim->equip_get(MONST_EQUIP_SHIELD);
          if (shield) {
            weapon_check_for_damage(shield, victim);
          }

          auto helmet = victim->equip_get(MONST_EQUIP_HELMET);
          if (helmet) {
            weapon_check_for_damage(helmet, victim);
          }

          //
          // We tried to attack, so do not move
          //
          missed          = true;
          tried_to_attack = true;
        }
      }
    }

    if (! missed) {
      dbg("Do the hit");
      TRACE_AND_INDENT();
      if (victim->is_hit(this, attack_options, attack_options->damage)) {
        dbg("The attack succeeded");

        if (victim != this) {
          if (attack_lunge()) {
            lunge(victim->curr_at);
          }
        }

        if (attack_eater()) {
          health_boost(victim->nutrition_get());
        }

        if (is_destroyed_on_hitting() || is_destroyed_on_hit_or_miss()) {
          dead("by foolishness");
        }

        //
        // See if the weapon crumbles
        //
        auto my_owner = top_owner();
        if (my_owner) {
          auto weapon = my_owner->equip_get(MONST_EQUIP_WEAPON);
          if (weapon) {
            weapon_check_for_damage(weapon, victim);
          }

          auto gauntlet = my_owner->equip_get(MONST_EQUIP_GAUNTLET);
          if (gauntlet) {
            weapon_check_for_damage(gauntlet, victim);
          }
        }

        attack_count++;
      }
    }

    //
    // Reset to allow multiple attacks of the same type.
    //
    attack_options->attack_poison    = false;
    attack_options->attack_future1   = false;
    attack_options->attack_future2   = false;
    attack_options->attack_future3   = false;
    attack_options->attack_cold      = false;
    attack_options->attack_fire      = false;
    attack_options->attack_crush     = false;
    attack_options->attack_lightning = false;
    attack_options->attack_energy    = false;
    attack_options->attack_acid      = false;
    attack_options->attack_digest    = false;
    attack_options->attack_necrosis  = false;
    attack_options->attack_natural   = false;
    attack_options->damage_set       = false;
    attack_options->damage           = 0;
  }

  if (! victim->wake("attacked")) {
    dbg("Failed to wake the %s", victim->to_short_string().c_str());
    return false;
  }

  if (attack_count) {
    return true;
  }

  victim->on_you_are_hit_but_dodge_it_do(this);

  //
  // Missiles?
  //
  if (is_destroyed_on_hit_or_miss()) {
    if (is_loggable()) {
      dbg("Attack missed %s", victim->to_short_string().c_str());
    }
    if (victim != this) {
      if (attack_lunge()) {
        lunge(victim->curr_at);
      }
    }
    dead("by foolishness");
    return true;
  }

  return tried_to_attack;
}

bool Thing::nat_att(Thingp victim)
{
  AttackOptions attack_options {};
  attack_options.prefer_nat_att = true;
  return attack(victim, &attack_options);
}

int Thing::is_attacked_with_damage_melee(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_digest = true;
  attack_options.real_hitter   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_nat_att(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_natural = true;
  attack_options.real_hitter    = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_poison(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_poison = true;
  attack_options.real_hitter   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_necrosis(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_necrosis = true;
  attack_options.real_hitter     = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_draining(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_draining = true;
  attack_options.real_hitter     = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_future1(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_future1 = true;
  attack_options.real_hitter    = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_future2(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_future2 = true;
  attack_options.real_hitter    = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_future3(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_future3 = true;
  attack_options.real_hitter    = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_cold = true;
  attack_options.real_hitter = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_fire(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_fire = true;
  attack_options.real_hitter = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_crush(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_crush = true;
  attack_options.real_hitter  = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_lightning(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_lightning = true;
  attack_options.real_hitter      = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_energy(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_energy = true;
  attack_options.real_hitter   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_acid(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_acid = true;
  attack_options.real_hitter = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_water(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_water = true;
  attack_options.real_hitter  = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_damage_digest(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  AttackOptions attack_options {};
  attack_options.attack_digest = true;
  attack_options.real_hitter   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}
