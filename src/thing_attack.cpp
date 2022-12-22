//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

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

  if (is_debug_type()) {
    dbg("Is it possible to attack %s?", victim->to_short_string().c_str());
  }

  if (is_friend(victim)) {
    if (is_able_to_attack_owner()) {
      //
      // Sword of plutonium / lightning fork.
      //
      return true;
    }

    if (is_debug_type()) {
      dbg("Cannot attack %s, friend", victim->to_short_string().c_str());
    }
    return false;
  }

  if (same_mob(victim)) {
    if (is_debug_type()) {
      dbg("Cannot attack %s, same mob", victim->to_short_string().c_str());
    }
    return false;
  }

  //
  // Weapons can't attack all by themselves. That would be nuts.
  //
  if (is_weapon() || is_staff() || is_ring()) {
    //
    // How can this happen? Confused
    //
    if (! top_owner()) {
      if (is_debug_type()) {
        dbg("Cannot attack %s, I have no owner", victim->to_short_string().c_str());
      }
      return false;
    }
  } else {
    //
    // If stuck in ice, we can only attack locally
    //
    if (level->is_block_of_ice(curr_at)) {
      if (victim->curr_at != curr_at) {
        if (is_debug_type()) {
          dbg("Cannot attack %s, stuck in ice", victim->to_short_string().c_str());
        }
        return false;
      }
    }

    //
    // If stuck in a web, we can only attack locally
    //
    if (! is_immune_to_spiderwebs()) {
      if (level->is_spiderweb(curr_at)) {
        if (victim->curr_at != curr_at) {
          if (is_debug_type()) {
            dbg("Cannot attack %s, stuck in a web", victim->to_short_string().c_str());
          }
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
          if (is_debug_type()) {
            dbg("Cannot attack %s, stuck in an engulfer (%s)", victim->to_short_string().c_str(),
                t->to_short_string().c_str());
          }
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
      if (is_debug_type()) {
        dbg("Cannot attack %s, it is on fire", victim->to_short_string().c_str());
      }
      return false;
    }
  }

  if (victim->is_cold()) {
    if (environ_avoids_cold()) {
      if (is_debug_type()) {
        dbg("Cannot attack %s, it is cold", victim->to_short_string().c_str());
      }
      return false;
    }
  }

  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon() && ! is_explosion()) {
      if (is_debug_type()) {
        dbg("Cannot attack %s, I am fire", victim->to_short_string().c_str());
      }
      return false;
    }
  }

  if (can_eat(victim)) {
    if (is_debug_type()) {
      dbg("Allow eater attack on %s", victim->to_short_string().c_str());
    }
    return true;
  }

  //
  // No attacking of open doors!
  //
  if (victim->is_open) {
    if (is_debug_type()) {
      dbg("Cannot attack %s, it's open", victim->to_short_string().c_str());
    }
    return false;
  }

  //
  // Attacking of closed doors?
  //
  if (victim->is_door()) {
    if (me->is_able_to_break_down_doors()) {
      if (is_debug_type()) {
        dbg("Can break down door %s", victim->to_short_string().c_str());
      }
      return true;
    }
  }

  //
  // Don't attack thy leader or follower
  //
  if (is_friend(victim) || same_mob(victim)) {
    return false;
  }

  //
  // Monsters (alive ones) can attack.
  // Or resurrected monsters.
  // Or carnivorous plants.
  //
  if ((! is_dead && is_carnivorous_plant()) || is_alive_monst() || is_resurrected) {
    //
    // Can we eats it?
    //
    if (me->is_edible(victim)) {
      if (is_debug_type()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
      }
      return true;
    }

    if (! victim->is_attackable_by_monst()) {
      if (is_debug_type()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", victim->to_short_string().c_str());
      }
      return false;
    }

    if (me->attack_humanoid()) {
      if (victim->is_humanoid()) {
        if (! victim->is_dead) {
          if (is_debug_type()) {
            dbg("Can attack humanoid: %s", victim->to_short_string().c_str());
          }
          return true;
        }
      }
    }

    if (me->attack_living()) {
      if (victim->is_living()) {
        if (! victim->is_dead) {
          if (is_debug_type()) {
            dbg("Can attack living: %s", victim->to_short_string().c_str());
          }
          return true;
        }
      }
    }

    if (me->attack_undead()) {
      if (victim->is_undead()) {
        if (! victim->is_dead) {
          if (is_debug_type()) {
            dbg("Can attack undead: %s", victim->to_short_string().c_str());
          }
          return true;
        }
      }
    }
  }

  if (is_player()) {
    if (victim->is_attackable_by_player()) {
      if (game->robot_mode) {
        if (victim->is_barrel()) {
          if (is_debug_type()) {
            dbg("No, do not attack %s, is explosive barrel", victim->to_short_string().c_str());
          }
          return false;
        }
      }
      if (victim->is_foliage() || victim->is_carnivorous_plant()) {
        if (is_debug_type()) {
          dbg("No, do not attack %s", victim->to_short_string().c_str());
        }
        return false;
      }
      if (is_debug_type()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
      }
      return true;
    }
    if (is_debug_type()) {
      dbg("No, cannot attack %s, not is_attackable", victim->to_short_string().c_str());
    }
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
        if (is_debug_type()) {
          dbg("Can attack %s", victim->to_short_string().c_str());
        }
        return true;
      }
      if (! victim->is_attackable_by_player()) {
        if (is_debug_type()) {
          dbg("Cannot weapon attack %s, not is_attackable by player", victim->to_short_string().c_str());
        }
        return false;
      }
      if (is_debug_type()) {
        dbg("Can attack %s", victim->to_short_string().c_str());
      }
      return true;
    }
  }

  if (me->is_fire() || me->is_lava()) {
    if (me->is_monst()) {
      //
      // Fire monsters do not attack always
      //
    } else if (victim->is_able_to_melt() || victim->is_able_to_burn() || victim->is_very_combustible() ||
               victim->is_combustible()) {
      if (! victim->is_fire() && ! victim->is_lava()) {
        if (is_debug_type()) {
          dbg("Can attack as I am firey %s", victim->to_short_string().c_str());
        }
        return true;
      }
    }
  }

  if (is_enemy(victim)) {
    if (is_debug_type()) {
      dbg("Can attack enemy %s", victim->to_short_string().c_str());
    }
    return true;
  }

  if (is_weapon()) {
    if (victim->is_sticky() || victim->is_spiderweb()) {
      if (is_able_to_break_out_of_webs()) {
        if (is_debug_type()) {
          dbg("Can attack and break out of web %s", victim->to_short_string().c_str());
        }
        return true;
      }
      if (is_debug_type()) {
        dbg("Can not break out of web %s", victim->to_short_string().c_str());
      }
      return false;
    }

    if (victim->is_block_of_ice()) {
      if (is_able_to_break_out_of_ice()) {
        if (is_debug_type()) {
          dbg("Can attack and break out of ice %s", victim->to_short_string().c_str());
        }
        return true;
      }
      if (is_debug_type()) {
        dbg("Can not break out of web %s", victim->to_short_string().c_str());
      }
      return false;
    }

    if (victim->is_foliage() || victim->is_carnivorous_plant()) {
      if (is_debug_type()) {
        dbg("Can attack scenery %s", victim->to_short_string().c_str());
      }
      return true;
    }
  }

  if (victim->is_alive_monst() || victim->is_combustible() || victim->is_very_combustible() ||
      victim->is_able_to_melt() || victim->is_able_to_burn() || victim->is_wall() || victim->is_rock() ||
      victim->is_door() || victim->is_bridge() || victim->is_dry_grass() || victim->is_wet_grass() ||
      victim->is_treasure_type() || victim->is_enchantstone() || victim->is_skillstone() || victim->is_foliage() ||
      victim->is_carnivorous_plant() || victim->is_spiderweb() || victim->is_block_of_ice() || victim->is_sticky() ||
      victim->is_brazier() || victim->is_barrel() || victim->is_player() || victim->is_food() ||
      victim->is_bag_item()) {
    if (is_laser()) {
      if (is_debug_type()) {
        dbg("Can attack as laser %s", victim->to_short_string().c_str());
      }
      return true;
    }

    if (is_projectile()) {
      if (is_debug_type()) {
        dbg("Can attack as projectile %s", victim->to_short_string().c_str());
      }
      return true;
    }

    if (is_staff()) {
      if (is_debug_type()) {
        dbg("Can attack as staff %s", victim->to_short_string().c_str());
      }
      return true;
    }

    if (is_ring()) {
      if (is_debug_type()) {
        dbg("Can attack as ring %s", victim->to_short_string().c_str());
      }
      return true;
    }

    if (is_explosion()) {
      if (is_debug_type()) {
        dbg("Can attack as explosion %s", victim->to_short_string().c_str());
      }
      return true;
    }
  }

  //
  // Some things can be helpful and attack mobs.
  //
  if (victim->is_mob() && is_able_to_attack_mobs()) {
    if (is_debug_type()) {
      dbg("Can attack mob %s", victim->to_short_string().c_str());
    }
    return true;
  }

  if (is_debug_type()) {
    dbg("Cannot attack %s, ignore", victim->to_short_string().c_str());
  }

  return false;
}

bool Thing::possible_to_attack_at(point at)
{
  TRACE_NO_INDENT();

  bool ret = false;

  FOR_ALL_COLLISION_THINGS(level, victim, at.x, at.y)
  {
    if (! possible_to_attack(victim)) {
      continue;
    }
    ret = true;
  }
  FOR_ALL_THINGS_END()

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

  ThingAttackOptions attack_options {};
  attack_options.shove_allowed  = true;
  attack_options.attack_allowed = true;
  attack_options.attack_at      = future_pos;
  attack_options.attack_at_set  = true;

  return (move(future_pos, up, down, left, right, attack, idle, &attack_options));
}

bool Thing::attack(Thingp victim, ThingAttackOptionsp attack_options)
{
  dbg("Attack %s", victim->to_short_string().c_str());
  TRACE_AND_INDENT();

  idle_count_set(0);

  auto owner = top_owner();

  if (! possible_to_attack(victim)) {
    if (is_debug_type()) {
      dbg("Attack failed, not possible to attack %s", victim->to_short_string().c_str());
    }
    return false;
  }

  if (victim->is_falling) {
    if (is_debug_type()) {
      dbg("Attack failed, victim is falling %s", victim->to_short_string().c_str());
    }
    return false;
  }

  //
  // Critical attack optins
  //
  if (d10000() < crit_chance_d10000()) {
    attack_options->crit = true;
  }

  if (! attack_options->crit) {
    if (victim->is_stuck_currently()) {
      if (d10000() < crit_chance_d10000()) {
        attack_options->crit = true;
      }
    }
  }

  if (victim->is_sleeping) {
    attack_options->crit = true;
  }

  int i_rolled = d20();

  if (i_rolled == 20) {
    attack_options->crit = true;
  }

  //
  // Poor frozen things are always critted.
  //
  if (victim->is_frozen) {
    attack_options->crit = true;
  }

  //
  // Too tired to attack
  //
  if (is_able_to_tire()) {
    if (stamina() < 5) {
      if (attack_options->crit) {
        if (is_player()) {
          msg("You are so tired but have a surge of energy!");
        }
      } else {
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
  }

  //
  // Too groggy to attack
  //
  if ((game->tick_current - infop()->tick_last_awoke < 2)) {
    if (! attack_options->crit) {
      dbg("Just woke up, cannot attack yet");
      return false;
    }
  }

  //
  // Allow multiple attacks
  //
  bool tried_to_attack = false;
  int  attack_count    = 0;

  dbg("Attack count #%d", attacks_per_round());
  TRACE_AND_INDENT();

  for (int attack_num = 0; attack_num < attacks_per_round(); attack_num++) {
    bool fumble = false;

    dbg("Attack num #%d", attack_num);
    TRACE_AND_INDENT();

    attack_options->attack_num = attack_num;

    if (attack_options->attack[ THING_ATTACK_POISON ]) {
      dbg("Attack type already set: attack[THING_ATTACK_POISON]");
    } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
      dbg("Attack type already set: attack[THING_ATTACK_DROWN]");
    } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
      dbg("Attack type already set: attack[THING_ATTACK_BITE]");
    } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
      dbg("Attack type already set: attack[THING_ATTACK_CLAW]");
    } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
      dbg("Attack type already set: attack[THING_ATTACK_COLD]");
    } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
      dbg("Attack type already set: attack[THING_ATTACK_FIRE]");
    } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
      dbg("Attack type already set: attack[THING_ATTACK_CRUSH]");
    } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
      dbg("Attack type already set: attack[THING_ATTACK_LIGHTNING]");
    } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
      dbg("Attack type already set: attack[THING_ATTACK_ENERGY]");
    } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
      dbg("Attack type already set: attack[THING_ATTACK_NEGATION]");
    } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
      dbg("Attack type already set: attack[THING_ATTACK_ACID]");
    } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
      dbg("Attack type already set: attack[THING_ATTACK_DIGEST]");
    } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
      dbg("Attack type already set: attack[THING_ATTACK_NECROSIS]");
    } else if (attack_options->attack[ THING_ATTACK_DRAINING ]) {
      dbg("Attack type already set: attack[THING_ATTACK_DRAINING]");
    }

    //
    // Attack  roll is 1d20 + stat_att_mod_total - penalties
    // Defence roll is        stat_def_total - penalties
    // Damage       is dam  + stat_att_mod_total
    //
    auto att_bonus = stat_att_mod_total();
    if (owner) {
      att_bonus = owner->stat_att_mod_total();
    }

    //
    // If a critical hit then ignore any negative attack bonus. This gives a 1 in 20 chance even
    // in bad siturations of achieving some damage.
    //
    if (attack_options->crit) {
      if (att_bonus < 0) {
        att_bonus = 1;
      }
    }

    auto att_penalty = stat_att_penalties_total();
    if (owner) {
      //
      // Only apply penalties if attacking a monster; not food.
      //
      if (victim->is_alive_monst() || victim->is_player()) {
        att_penalty = owner->stat_att_penalties_total();
      }
    }

    auto stat_def  = victim->stat_def_total() - victim->stat_def_penalties_total();
    auto def_bonus = 0;

    //
    // This can happen if the player is hiding and the monster stumbles into them.
    //
    if (is_monst()) {
      if (victim->is_player()) {
        if (! has_seen_player_msg_shown) {
          //
          // Bonus as the monster is surprised.
          //
          has_seen_player_msg_shown = true;
          if (is_msg_allowed_is_surprised()) {
            msg("%s is surprised to see you!", text_The().c_str());
          }

          if (is_able_to_be_surprised()) {
            def_bonus += 2;
          }
        }
      }
    } else if (is_player()) {
      if (victim->is_monst()) {
        if (! victim->has_seen_player_msg_shown) {
          //
          // Bonus as the monster is surprised.
          //
          victim->has_seen_player_msg_shown = true;
          if (is_msg_allowed_is_surprised()) {
            msg("You surprise %s!", text_the().c_str());
          }

          if (victim->is_able_to_be_surprised()) {
            att_bonus += 2;
          }
        }
      }
    }

    dbg("Set damage types");
    TRACE_AND_INDENT();

    //
    // Chance of poison damage?
    //
    if (! attack_options->attack[ THING_ATTACK_POISON ]) {
      if (! attack_options->dmg_set || attack_options->prefer_nat_att) {
        if (d1000() < dmg_poison_chance_d1000(attack_options->attack_num)) {
          int dmg_poison_val = dmg_poison();
          if (dmg_poison_val > 0) {
            attack_options->damage                        = dmg_poison_val;
            attack_options->dmg_set                       = true;
            attack_options->attack[ THING_ATTACK_POISON ] = true;
            victim->poison_reason_set(text_a_or_an());
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_DROWN] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_DROWN ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_drown_chance_d1000(attack_options->attack_num)) {
          int dmg_drown_val = dmg_drown();
          if (dmg_drown_val > 0) {
            attack_options->damage                       = dmg_drown_val;
            attack_options->dmg_set                      = true;
            attack_options->attack[ THING_ATTACK_DROWN ] = true;
            dbg("Set drown damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_BITE] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_BITE ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_bite_chance_d1000(attack_options->attack_num)) {
          int dmg_bite_val = dmg_bite();
          if (dmg_bite_val > 0) {
            attack_options->damage                      = dmg_bite_val;
            attack_options->dmg_set                     = true;
            attack_options->attack[ THING_ATTACK_BITE ] = true;
            dbg("Set bite damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_CLAW] damage?
    //
    if (! attack_options->dmg_set) {
      if (d1000() < dmg_claw_chance_d1000(attack_options->attack_num)) {
        int dmg_claw_val = dmg_claw();
        if (dmg_claw_val > 0) {
          attack_options->damage                      = dmg_claw_val;
          attack_options->dmg_set                     = true;
          attack_options->attack[ THING_ATTACK_CLAW ] = true;
          dbg("Set claw damage %d", attack_options->damage);
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_COLD] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_COLD ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_cold_chance_d1000(attack_options->attack_num)) {
          int dmg_cold_val = dmg_cold();
          if (dmg_cold_val > 0) {
            attack_options->damage                      = dmg_cold_val;
            attack_options->dmg_set                     = true;
            attack_options->attack[ THING_ATTACK_COLD ] = true;
            dbg("Set cold damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_FIRE] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_FIRE ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_fire_chance_d1000(attack_options->attack_num)) {
          int dmg_fire_val = dmg_fire();
          if (dmg_fire_val > 0) {
            attack_options->damage                      = dmg_fire_val;
            attack_options->dmg_set                     = true;
            attack_options->attack[ THING_ATTACK_FIRE ] = true;
            dbg("Set fire damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_HEAT] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_HEAT ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_heat_chance_d1000(attack_options->attack_num)) {
          int dmg_heat_val = dmg_heat();
          if (dmg_heat_val > 0) {
            attack_options->damage                      = dmg_heat_val;
            attack_options->dmg_set                     = true;
            attack_options->attack[ THING_ATTACK_FIRE ] = true;
            dbg("Set heat damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_CRUSH] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_CRUSH ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_crush_chance_d1000(attack_options->attack_num)) {
          int dmg_crush_val = dmg_crush();
          if (dmg_crush_val > 0) {
            attack_options->damage                       = dmg_crush_val;
            attack_options->dmg_set                      = true;
            attack_options->attack[ THING_ATTACK_CRUSH ] = true;
            dbg("Set crush damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_LIGHTNING] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_lightning_chance_d1000(attack_options->attack_num)) {
          int dmg_lightning_val = dmg_lightning();
          if (dmg_lightning_val > 0) {
            attack_options->damage                           = dmg_lightning_val;
            attack_options->dmg_set                          = true;
            attack_options->attack[ THING_ATTACK_LIGHTNING ] = true;
            dbg("Set lightning damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_ENERGY] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_ENERGY ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_energy_chance_d1000(attack_options->attack_num)) {
          int dmg_energy_val = dmg_energy();
          if (dmg_energy_val > 0) {
            attack_options->damage                        = dmg_energy_val;
            attack_options->dmg_set                       = true;
            attack_options->attack[ THING_ATTACK_ENERGY ] = true;
            dbg("Set energy damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_NEGATION] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_NEGATION ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_negation_chance_d1000(attack_options->attack_num)) {
          int dmg_negation_val = dmg_negation();
          if (dmg_negation_val > 0) {
            attack_options->damage                          = dmg_negation_val;
            attack_options->dmg_set                         = true;
            attack_options->attack[ THING_ATTACK_NEGATION ] = true;
            dbg("Set negation damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_ACID] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_ACID ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_acid_chance_d1000(attack_options->attack_num)) {
          int dmg_acid_val = dmg_acid();
          if (dmg_acid_val > 0) {
            attack_options->damage                      = dmg_acid_val;
            attack_options->dmg_set                     = true;
            attack_options->attack[ THING_ATTACK_ACID ] = true;
            dbg("Set acid damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_WATER] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_WATER ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_water_chance_d1000(attack_options->attack_num)) {
          int dmg_water_val = dmg_water();
          if (dmg_water_val > 0) {
            attack_options->damage                       = dmg_water_val;
            attack_options->dmg_set                      = true;
            attack_options->attack[ THING_ATTACK_WATER ] = true;
            dbg("Set water damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of attack[THING_ATTACK_DIGEST] damage?
    //
    if (! attack_options->attack[ THING_ATTACK_DIGEST ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_digest_chance_d1000(attack_options->attack_num)) {
          int dmg_digest_val = dmg_digest();
          if (dmg_digest_val > 0) {
            attack_options->damage                        = dmg_digest_val;
            attack_options->dmg_set                       = true;
            attack_options->attack[ THING_ATTACK_DIGEST ] = true;
            dbg("Set digest damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of necrosis damage?
    //
    if (! attack_options->attack[ THING_ATTACK_NECROSIS ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_necrosis_chance_d1000(attack_options->attack_num)) {
          int dmg_necrosis_val = dmg_necrosis();
          if (dmg_necrosis_val > 0) {
            attack_options->damage                          = dmg_necrosis_val;
            attack_options->dmg_set                         = true;
            attack_options->attack[ THING_ATTACK_NECROSIS ] = true;
            dbg("Set necro damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Chance of stamina damage?
    //
    if (! attack_options->attack[ THING_ATTACK_DRAINING ]) {
      if (! attack_options->dmg_set) {
        if (d1000() < dmg_draining_chance_d1000(attack_options->attack_num)) {
          int dmg_draining_val = dmg_draining();
          if (dmg_draining_val > 0) {
            attack_options->damage                          = dmg_draining_val;
            attack_options->dmg_set                         = true;
            attack_options->attack[ THING_ATTACK_DRAINING ] = true;
            dbg("Set drain damage %d", attack_options->damage);
          }
        }
      }
    }

    //
    // Bite?
    //
    if (! attack_options->attack[ THING_ATTACK_NATURAL ]) {
      if (! attack_options->dmg_set || attack_options->prefer_nat_att) {
        if (d1000() < dmg_nat_att_chance_d1000(attack_options->attack_num)) {
          int dmg_nat_att_val = dmg_nat_att();
          if (dmg_nat_att_val > 0) {
            attack_options->damage                         = dmg_nat_att_val + att_bonus;
            attack_options->dmg_set                        = true;
            attack_options->attack[ THING_ATTACK_NATURAL ] = true;
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
    if (! attack_options->dmg_set) {
      if (d1000() < dmg_melee_chance_d1000(attack_options->attack_num)) {
        auto damage            = dmg_melee();
        attack_options->damage = damage + att_bonus;
        dbg("Set melee damage %d att_bonus %d", damage, att_bonus);
        if (attack_options->damage > 0) {
          attack_options->dmg_set = true;
        }
      }
    }

    if (! attack_options->dmg_set) {
      if (owner) {
        if (d1000() < owner->dmg_melee_chance_d1000(attack_options->attack_num)) {
          auto damage            = dmg_melee();
          attack_options->damage = damage + att_bonus;
          dbg("Set owner melee damage %d att_bonus %d", damage, att_bonus);
          if (attack_options->damage > 0) {
            attack_options->dmg_set = true;
          }
        }
      }
    }

    //
    // This overrides other damage types. For when we are stuck inside a cleaner
    //
    if (is_engulfer()) {
      if (victim->curr_at == curr_at) {
        attack_options->damage                           = dmg_digest();
        attack_options->attack[ THING_ATTACK_POISON ]    = false;
        attack_options->attack[ THING_ATTACK_DROWN ]     = false;
        attack_options->attack[ THING_ATTACK_BITE ]      = false;
        attack_options->attack[ THING_ATTACK_CLAW ]      = false;
        attack_options->attack[ THING_ATTACK_COLD ]      = false;
        attack_options->attack[ THING_ATTACK_FIRE ]      = false;
        attack_options->attack[ THING_ATTACK_CRUSH ]     = false;
        attack_options->attack[ THING_ATTACK_LIGHTNING ] = false;
        attack_options->attack[ THING_ATTACK_ENERGY ]    = false;
        attack_options->attack[ THING_ATTACK_NEGATION ]  = false;
        attack_options->attack[ THING_ATTACK_ACID ]      = false;
        attack_options->attack[ THING_ATTACK_DIGEST ]    = true;
        attack_options->attack[ THING_ATTACK_NECROSIS ]  = false;
        attack_options->attack[ THING_ATTACK_NATURAL ]   = false;
        attack_options->dmg_set                          = true;
      }
    }

    //
    // If some attack type worked, then make sure we have some damage
    //
    if (attack_options->dmg_set) {
      if (attack_options->damage < 1) {
        attack_options->damage = 1;
      }
    }

    //
    // Ensure some damage if a critical hit.
    //
    if (attack_options->crit) {
      if (attack_options->damage < 1) {
        attack_options->damage = 10;
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

    //
    // This can happen if a weapon is damaged, if the thing is starving, or if trying to attack
    // when in deep water with penalties.
    //
    if (attack_options->damage <= 0) {
      //
      // Wake on attack
      //
      victim->wake("attacked, but no damage");

      if (is_player() || (owner && owner->is_player())) {
        //
        // If hitting a rock with a damaged weapon, give more feedback as to why there is no damage.
        //
        if (is_weapon() && (weapon_dmgd_pct() > 0)) {
          if (is_weapon() && (weapon_dmgd_pct() > 50)) {
            msg("%%fg=red$Your heavily damaged weapon inflicts no damage on %s.%%fg=reset$",
                victim->text_the().c_str());
          } else {
            msg("%%fg=red$Your damaged weapon inflicts no damage on %s.%%fg=reset$", victim->text_the().c_str());
          }
        } else if (stuck_count()) {
          msg("%%fg=orange$You find it hard to move and inflict no damage on %s.%%fg=reset$",
              victim->text_the().c_str());
        } else {
          msg("%%fg=orange$You inflict no damage on %s.%%fg=reset$", victim->text_the().c_str());
        }

        if (game->robot_mode) {
          BOTCON("Robot fails to damage %s.", victim->text_the().c_str());
        }
      } else if (victim->is_player()) {
        if (owner) {
          msg("%%fg=orange$%s fails to hit you with %s.%%fg=reset$", owner->text_The().c_str(), text_the().c_str());
        } else {
          msg("%%fg=orange$%s fails to hit you.%%fg=reset$", text_The().c_str());
        }
        popup("Miss!");

        if (game->robot_mode) {
          BOTCON("%s misses the robot.", text_The().c_str());
        }
      }

      dbg("The attack failed, no damage (att modifier %d, AC %d) on %s", att_bonus, stat_def,
          victim->to_short_string().c_str());

      //
      // Do we let it try to miss again? Why not.
      //
      continue;
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
        attack_options->attack[ THING_ATTACK_NATURAL ] = true;
      }
    }

    bool missed = false;

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
      } else if (victim->is_frozen) {
        //
        // If frozen, it cannot avoid the hits.
        //
      } else if (victim->stuck_count()) {
        //
        // If stuck, it cannot avoid the hits.
        //
      } else if (is_staff()) {
        //
        // Staffs always hit
        //
      } else {
        //
        // Attack  is 1d20 + stat_att_mod_total - penalties
        // Defence is        stat_def_total - penalties
        //
        bool hit               = false;
        int  to_hit            = stat_def + def_bonus;
        auto att_roll_modifier = att_bonus - att_penalty;

        if (i_rolled == 20) {
          attack_options->crit = true;
          hit                  = true;
          IF_DEBUG2
          {
            dbg("Attack on %s: ATT %s DEF %d(%s), to-hit %d, rolled %d -> crit", victim->to_short_string().c_str(),
                modifier_to_string(att_roll_modifier).c_str(), stat_def, modifier_to_string(def_bonus).c_str(),
                to_hit, i_rolled);
          }
        } else if (i_rolled == 1) {
          hit    = false;
          fumble = true;
          IF_DEBUG2
          {
            dbg("Attack on %s: ATT %s DEF %d(%s), to-hit %d, rolled %d -> fumble", victim->to_short_string().c_str(),
                modifier_to_string(att_roll_modifier).c_str(), stat_def, modifier_to_string(def_bonus).c_str(),
                to_hit, i_rolled);
          }
        } else {
          i_rolled += att_roll_modifier;
          hit = i_rolled >= to_hit;
          IF_DEBUG2
          {
            dbg("Attack on %s: ATT %s(%s,%s) DEF %d(%s), to-hit %d, rolled %d -> %s",
                victim->to_short_string().c_str(), modifier_to_string(att_roll_modifier).c_str(),
                modifier_to_string(att_bonus).c_str(), modifier_to_string(att_penalty).c_str(),

                stat_def, modifier_to_string(def_bonus).c_str(), to_hit, i_rolled, hit ? "hit" : "miss");
          }
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
              msg("%%fg=orange$You fumble and miss %s.%%fg=reset$", victim->text_the().c_str());
              popup("You fumble!");
            } else {
              msg("%%fg=orange$You miss %s.%%fg=reset$", victim->text_the().c_str());
              popup("You miss!");
            }
            if (game->robot_mode) {
              BOTCON("Robot misses %s.", victim->text_the().c_str());
            }
          } else if (victim->is_player()) {
            if (owner) {
              msg("%%fg=orange$%s misses you with %s.%%fg=reset$", owner->text_The().c_str(), text_the().c_str());
            } else {
              msg("%%fg=orange$%s misses you.%%fg=reset$", text_The().c_str());
            }
            popup("It misses you!");

            if (game->robot_mode) {
              BOTCON("%s misses the robot.", text_The().c_str());
            }
          } else {
            dbg("The attack missed (att modifier %d, AC %d) on %s", att_roll_modifier, stat_def,
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
            weapon_check_for_dmg(armor, victim);
          }

          auto shield = victim->equip_get(MONST_EQUIP_SHIELD);
          if (shield) {
            weapon_check_for_dmg(shield, victim);
          }

          auto helmet = victim->equip_get(MONST_EQUIP_HELMET);
          if (helmet) {
            weapon_check_for_dmg(helmet, victim);
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
          hunger_boost(victim->nutrition_get());
        }

        if (is_destroyed_on_hitting() || is_destroyed_on_hit_or_miss()) {
          dead("by foolishness");
        }

        //
        // See if the weapon crumbles
        //
        if (is_weapon()) {
          auto my_owner = top_owner();
          if (my_owner) {
            auto weapon = my_owner->equip_get(MONST_EQUIP_WEAPON);
            if (weapon) {
              weapon_check_for_dmg(weapon, victim);
            }

            auto gauntlet = my_owner->equip_get(MONST_EQUIP_GAUNTLET);
            if (gauntlet) {
              weapon_check_for_dmg(gauntlet, victim);
            }
          }
        }

        attack_count++;
      }
    }

    //
    // Reset to allow multiple attacks of the same type.
    //
    attack_options->attack[ THING_ATTACK_POISON ]    = false;
    attack_options->attack[ THING_ATTACK_DROWN ]     = false;
    attack_options->attack[ THING_ATTACK_BITE ]      = false;
    attack_options->attack[ THING_ATTACK_CLAW ]      = false;
    attack_options->attack[ THING_ATTACK_COLD ]      = false;
    attack_options->attack[ THING_ATTACK_FIRE ]      = false;
    attack_options->attack[ THING_ATTACK_CRUSH ]     = false;
    attack_options->attack[ THING_ATTACK_LIGHTNING ] = false;
    attack_options->attack[ THING_ATTACK_ENERGY ]    = false;
    attack_options->attack[ THING_ATTACK_NEGATION ]  = false;
    attack_options->attack[ THING_ATTACK_ACID ]      = false;
    attack_options->attack[ THING_ATTACK_DIGEST ]    = false;
    attack_options->attack[ THING_ATTACK_NECROSIS ]  = false;
    attack_options->attack[ THING_ATTACK_NATURAL ]   = false;
    attack_options->dmg_set                          = false;
    attack_options->damage                           = 0;
  }

  victim->wake("attacked");

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

    //
    // So we can tell when things are attacking us
    //
    tick_last_i_tried_to_attack_set(game->tick_current);

    dead("by foolishness");
    return true;
  }

  return tried_to_attack;
}

bool Thing::nat_att(Thingp victim)
{
  ThingAttackOptions attack_options {};
  attack_options.prefer_nat_att = true;
  return attack(victim, &attack_options);
}

int Thing::is_attacked_with_dmg_melee(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.real_hitter = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_nat_att(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_NATURAL ] = true;
  attack_options.real_hitter                    = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_poison(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_POISON ] = true;
  attack_options.real_hitter                   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_necrosis(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_NECROSIS ] = true;
  attack_options.real_hitter                     = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_draining(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_DRAINING ] = true;
  attack_options.real_hitter                     = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_drown(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_DROWN ] = true;
  attack_options.real_hitter                  = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_bite(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_BITE ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_claw(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_CLAW ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_COLD ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_fire(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_FIRE ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_heat(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (is_on_fire()) {
    return is_attacked_with_dmg_fire(hitter, real_hitter, damage);
  }
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_HEAT ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_crush(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_CRUSH ] = true;
  attack_options.real_hitter                  = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_lightning(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_LIGHTNING ] = true;
  attack_options.real_hitter                      = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_energy(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_ENERGY ] = true;
  attack_options.real_hitter                   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_negation(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_NEGATION ] = true;
  attack_options.real_hitter                     = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_acid(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_ACID ] = true;
  attack_options.real_hitter                 = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_water(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_WATER ] = true;
  attack_options.real_hitter                  = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}

int Thing::is_attacked_with_dmg_digest(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  ThingAttackOptions attack_options {};
  attack_options.attack[ THING_ATTACK_DIGEST ] = true;
  attack_options.real_hitter                   = real_hitter;
  return is_hit(hitter, &attack_options, damage);
}
