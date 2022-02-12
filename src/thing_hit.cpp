//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_english.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Python callback upon being hit
//
void Thing::on_you_are_hit_but_still_alive(Thingp hitter,      // an arrow / monst /...
                                           Thingp real_hitter, // who fired the arrow?
                                           bool crit, int damage)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_you_are_hit_but_still_alive = tp()->on_you_are_hit_but_still_alive_do();
  if (std::empty(on_you_are_hit_but_still_alive)) {
    return;
  }

  auto t = split_tokens(on_you_are_hit_but_still_alive, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, damage=%d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), crit, damage);

    //
    // Warning cannot handle negative values here for damage
    //
    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y, (unsigned int) crit, (unsigned int) damage);
  } else {
    ERR("Bad on_you_are_hit_but_still_alive call [%s] expected mod:function, got %d elems",
        on_you_are_hit_but_still_alive.c_str(), (int) on_you_are_hit_but_still_alive.size());
  }
}

void Thing::on_you_are_hit_and_now_dead(Thingp hitter,      // an arrow / monst /...
                                        Thingp real_hitter, // who fired the arrow?
                                        bool crit, int damage)
{
  TRACE_NO_INDENT();
  auto on_you_are_hit_and_now_dead = tp()->on_you_are_hit_and_now_dead_do();
  if (std::empty(on_you_are_hit_and_now_dead)) {
    return;
  }

  auto t = split_tokens(on_you_are_hit_and_now_dead, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, damage=%d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), crit, damage);

    //
    // Warning cannot handle negative values here for damage
    //
    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y, (unsigned int) crit, (unsigned int) damage);
  } else {
    ERR("Bad on_you_are_hit_and_now_dead call [%s] expected mod:function, got %d elems",
        on_you_are_hit_and_now_dead.c_str(), (int) on_you_are_hit_and_now_dead.size());
  }
}

//
// Python callback upon being miss
//
void Thing::on_you_miss_do(Thingp hitter)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_you_miss_do = tp()->on_you_miss_do();
  if (std::empty(on_you_miss_do)) {
    return;
  }

  auto t = split_tokens(on_you_miss_do, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), hitter->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_miss_do call [%s] expected mod:function, got %d elems", on_you_miss_do.c_str(),
        (int) on_you_miss_do.size());
  }
}

void Thing::on_you_natural_attack(void)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_you_natural_attack = tp()->on_you_natural_attack_do();
  if (std::empty(on_you_natural_attack)) {
    return;
  }

  auto t = split_tokens(on_you_natural_attack, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_natural_attack call [%s] expected mod:function, got %d elems", on_you_natural_attack.c_str(),
        (int) on_you_natural_attack.size());
  }
}

int Thing::ai_hit_actual(Thingp hitter,      // an arrow / monst /...
                         Thingp real_hitter, // who fired the arrow?
                         bool crit, bool attack_natural, bool attack_poison, bool attack_necrosis,
                         bool attack_future1, bool attack_future2, bool attack_future3, bool attack_cold,
                         bool attack_fire, bool attack_crush, bool attack_lightning, bool attack_energy,
                         bool attack_acid, bool attack_digest, int damage)
{
  TRACE_NO_INDENT();
  if (! hitter) {
    err("No hitter");
    return false;
  }

  if (! real_hitter) {
    err("No real hitter");
    return false;
  }

  if (! real_hitter->maybe_infop()) {
    real_hitter->err("Hitter (orig %s) has no infop", hitter->to_short_string().c_str());
    return false;
  }

  if (attack_poison) {
    damage = buff_on_damage_poison(real_hitter, damage);
    damage = on_damage_poison(real_hitter, damage);
  } else if (attack_future1) {
    damage = buff_on_damage_future1(real_hitter, damage);
    damage = on_damage_future1(real_hitter, damage);
  } else if (attack_future2) {
    damage = buff_on_damage_future2(real_hitter, damage);
    damage = on_damage_future2(real_hitter, damage);
  } else if (attack_future3) {
    damage = buff_on_damage_future3(real_hitter, damage);
    damage = on_damage_future3(real_hitter, damage);
  } else if (attack_cold) {
    damage = buff_on_damage_cold(real_hitter, damage);
    damage = on_damage_cold(real_hitter, damage);

    if (is_on_fire()) {
      if (is_player()) {
        msg("%%fg=green$The cold attack puts out the flames!%%fg=reset$");
      }
      unset_on_fire();

      auto smoke = level->thing_new("smoke", curr_at);
      smoke->lifespan_set(pcg_random_range(1, 10));
    }
  } else if (attack_fire) {
    damage = buff_on_damage_fire(real_hitter, damage);
    damage = on_damage_fire(real_hitter, damage);
  } else if (attack_crush) {
    damage = buff_on_damage_crush(real_hitter, damage);
    damage = on_damage_crush(real_hitter, damage);
  } else if (attack_lightning) {
    damage = buff_on_damage_lightning(real_hitter, damage);
    damage = on_damage_lightning(real_hitter, damage);
  } else if (attack_energy) {
    damage = buff_on_damage_energy(real_hitter, damage);
    damage = on_damage_energy(real_hitter, damage);
  } else if (attack_acid) {
    damage = buff_on_damage_acid(real_hitter, damage);
    damage = on_damage_acid(real_hitter, damage);
  } else if (attack_digest) {
    damage = buff_on_damage_digest(real_hitter, damage);
    damage = on_damage_digest(real_hitter, damage);
  } else if (attack_necrosis) {
    damage = buff_on_damage_necrosis(real_hitter, damage);
    damage = on_damage_necrosis(real_hitter, damage);
  } else if (attack_natural) {
    damage = buff_on_damage_natural_attack(real_hitter, damage);
    damage = on_damage_natural_attack(real_hitter, damage);
  } else {
    damage = buff_on_damage_melee(real_hitter, damage);
    damage = on_damage_melee(real_hitter, damage);
  }

  std::string damage_type;

  if (attack_poison) {
    if (! damage) {
      real_hitter->log("No poison damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack poison damage %d on %s", damage, to_short_string().c_str());
      damage_type = "poison ";
    }
  } else if (attack_future1) {
    if (! damage) {
      real_hitter->log("No damage_future1 damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_future1 damage %d on %s", damage, to_short_string().c_str());
      damage_type = "damage_future1 ";
    }
  } else if (attack_future2) {
    if (! damage) {
      real_hitter->log("No damage_future2 damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_future2 damage %d on %s", damage, to_short_string().c_str());
      damage_type = "damage_future2 ";
    }
  } else if (attack_future3) {
    if (! damage) {
      real_hitter->log("No damage_future3 damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_future3 damage %d on %s", damage, to_short_string().c_str());
      damage_type = "damage_future3 ";
    }
  } else if (attack_cold) {
    if (! damage) {
      real_hitter->log("No damage_cold damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_cold damage %d on %s", damage, to_short_string().c_str());
      damage_type = "cold ";
    }
  } else if (attack_fire) {
    if (! damage) {
      real_hitter->log("No damage_fire damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_fire damage %d on %s", damage, to_short_string().c_str());
      damage_type = "fire ";
    }
  } else if (attack_crush) {
    if (! is_crushable()) {
      real_hitter->log("Cannot crush %s", to_short_string().c_str());
      return false;
    }

    if (! damage) {
      real_hitter->log("No damage_crush damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_crush damage %d on %s", damage, to_short_string().c_str());
      damage_type = "crush ";
    }
  } else if (attack_lightning) {
    if (! damage) {
      real_hitter->log("No damage_lightning damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_lightning damage %d on %s", damage, to_short_string().c_str());
      damage_type = "lightning ";
    }
  } else if (attack_energy) {
    if (! damage) {
      real_hitter->log("No damage_energy damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_energy damage %d on %s", damage, to_short_string().c_str());
      damage_type = "energy ";
    }
  } else if (attack_acid) {
    if (! damage) {
      real_hitter->log("No damage_acid damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_acid damage %d on %s", damage, to_short_string().c_str());
      damage_type = "acid ";
    }
  } else if (attack_digest) {
    if (! damage) {
      real_hitter->log("No damage_digest damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack damage_digest damage %d on %s", damage, to_short_string().c_str());
      damage_type = "digest ";
    }
  } else if (attack_necrosis) {
    if (! damage) {
      real_hitter->log("No necrosis damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack necrosis damage %d on %s", damage, to_short_string().c_str());
      damage_type = "rotting ";
    }
  } else if (attack_natural) {
    if (! damage) {
      real_hitter->log("No natural attack damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack natural attack damage %d on %s", damage, to_short_string().c_str());
      damage_type = real_hitter->damage_natural_attack_type() + " ";
    }
  } else {
    if (! damage) {
      real_hitter->log("No melee damage on %s", to_short_string().c_str());
      return false;
    } else {
      real_hitter->log("Attack melee damage %d on %s", damage, to_short_string().c_str());
    }
  }

  if (real_hitter->is_fire() || real_hitter->is_lava()) {
    if (damage_received_doubled_from_fire()) {
      damage *= 2;
      damage_type = "double " + damage_type;
      dbg("Double damage from fire");
    }
  }

  if (real_hitter->is_acid()) {
    if (damage_received_doubled_from_acid()) {
      damage *= 2;
      damage_type = "double " + damage_type;
      dbg("Double damage from acid");
    }
  }

  if (real_hitter->is_poisonous_danger_level()) {
    if (damage_received_doubled_from_poison()) {
      damage *= 2;
      damage_type = "double " + damage_type;
      dbg("Double damage from poison");
    }
  }

  if (real_hitter->is_necrotic_danger_level()) {
    if (damage_received_doubled_from_necrosis()) {
      damage *= 2;
      damage_type = "double " + damage_type;
      dbg("Double damage from necrosis");
    }
  }

  if (environ_avoids_water()) {
    if (real_hitter->is_shallow_water() || real_hitter->is_deep_water()) {
      if (damage_received_doubled_from_water()) {
        damage *= 2;
        damage_type = "double " + damage_type;
        dbg("Double damage from water");
      }
    }
  }

  //
  // Cruel to let things keep on hitting you when you're dead
  //
  if (is_dead || is_dying) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG2 { hitter->log("Hit bypass, eat it"); }
    } else {
      IF_DEBUG2 { hitter->log("Hit fails, it's dead"); }
      return false;
    }
  } else {
    if (! damage) {
      IF_DEBUG2 { hitter->log("Hit fails, no damage"); }
      return false;
    }
  }

  auto delta = curr_at - hitter->curr_at;

  if (real_hitter != this) {
    if (real_hitter->tp()->gfx_bounce_on_move()) {
      real_hitter->bounce(0.5, 0.1, 100, 3);
      real_hitter->move_set_dir_from_delta(delta);
    }
  }

  if (real_hitter->is_able_to_tire()) {
    if (! real_hitter->stamina_get()) {
      if (real_hitter->is_player()) {
        msg("You are too tired to attack.");
        return false;
      }
    }
    real_hitter->stamina_decr(1);
  }

  //
  // Check for immunity
  //
  if (is_immune_to_fire()) {
    if (hitter->is_fire() || real_hitter->is_fire()) {
      if (is_player()) {
        msg("You bask in the fire!");
      } else if (real_hitter->is_player()) {
        msg("%s basks in the fire! You do no damage!", text_The().c_str());
      }
      return false;
    }
  }

  //
  // Try to push the thing into a hazard if we can just to be sneaky
  //
  if (this == hitter) {
    //
    // On fire?
    //
  } else if (hitter->is_monst()) {
    switch (hitter->try_to_shove_into_hazard(this, delta)) {
      case THING_SHOVE_TRIED_AND_FAILED : return true;
      case THING_SHOVE_TRIED_AND_PASSED : return true;
      case THING_SHOVE_NEVER_TRIED : break;
    }
  }

  //
  // Try to steal instead of attacking?
  //
  if (real_hitter->is_item_eater()) {
    if (is_carrying_item()) {
      if (real_hitter->steal_item_from(this)) {
        return true;
      }
    }
  }

  //
  // Poison attack
  //
  if (attack_poison) {
    if (is_immune_to_poison()) {
      if (hitter->is_poisonous_danger_level() || real_hitter->is_poisonous_danger_level()) {
        if (is_player()) {
          msg("You drink in the poison!");
        } else if (real_hitter->is_player()) {
          msg("%s drinks in the poison! You do no damage!", text_The().c_str());
        }
        health_boost(damage);
        return false;
      }
    } else {
      if (real_hitter->is_poisonous_danger_level()) {
        poisoned_amount_incr(damage / 2);
      }
      poisoned();
    }
  }

  //
  // Necrotic attack
  //
  if (attack_necrosis) {
    if (is_undead() || is_ethereal()) {
      if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
        if (is_player()) {
          msg("You are immune to the withering touch of %s!", text_the().c_str());
        } else if (real_hitter->is_player()) {
          msg("%s shrugs off your withering touch!", text_The().c_str());
        }
        return false;
      }
    } else {
      if (pcg_random_range(0, 100) < 50) {
        if (is_immune_to_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              msg("You gain strength from the withering touch!");
            } else if (real_hitter->is_player()) {
              msg("%s gains strength from your withering touch!", text_The().c_str());
            }
            stat_str_incr();
            return false;
          }
        } else {
          if (real_hitter->is_necrotic_danger_level()) {
            damage = real_hitter->is_necrotic_danger_level();
          } else {
            damage = 1;
          }
          damage = buff_on_damage_stat_str(real_hitter, damage);
          if (! damage) {
            real_hitter->log("No strength damage");
            return false;
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              rotting();
              necrotized_amount_incr(damage - 1);
            }
          }
          stat_str_decr();
          if (is_player()) {
            msg("%%fg=limegreen$Your skin is rotting. You lose 1 permanent strength!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            msg("%%fg=limegreen$Your rotting hand touches %s for 1 permanent strength damage!%%fg=reset$",
                text_the().c_str());
          }
          return true;
        }
      } else {
        if (is_immune_to_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              msg("You gain constitution from the withering touch!");
            } else if (real_hitter->is_player()) {
              msg("%s gains constitution from your withering touch!", text_The().c_str());
            }
            stat_con_incr();
            return false;
          }
        } else {
          if (real_hitter->is_necrotic_danger_level()) {
            damage = real_hitter->is_necrotic_danger_level();
          } else {
            damage = 1;
          }
          damage = buff_on_damage_stat_con(real_hitter, damage);
          if (! damage) {
            real_hitter->log("No con damage");
            return false;
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              rotting();
              necrotized_amount_incr(damage - 1);
            }
          }
          stat_con_decr();
          if (is_player()) {
            msg("%%fg=limegreen$Your skin is rotting. You lose 1 permanent con!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            msg("%%fg=limegreen$Your rotting hand touches %s for 1 permanent con damage!%%fg=reset$",
                text_the().c_str());
          }
          return true;
        }
      }
    }
  }

  //
  // If a wand is firing a laser, then get the damage from the
  // wand so we can add in enchants.
  //
  if (hitter->is_laser()) {
    auto owner = hitter->immediate_owner_get();
    if (owner) {
      if (owner->current_damage_get()) {
        damage = owner->current_damage_get();
        owner->current_damage_set(0);
      }
    }
  }

  if (real_hitter->maybe_itemsp()) {
    FOR_ALL_SKILLS_FOR(real_hitter, oid)
    {
      auto skill = level->thing_find(oid);
      if (skill && skill->is_activated) {
        //
        // Allow the damage to be modified
        //
        real_hitter->current_damage_set(damage);
        real_hitter->use(skill);
        damage = real_hitter->current_damage_get();
      }
    }
  }

  if (crit) {
    damage *= 2;
    IF_DEBUG2 { hitter->log("Hit %s (health %d) for CRIT damage %d", text_the().c_str(), health_get(), damage); }
  } else {
    IF_DEBUG2 { hitter->log("Hit %s (health %d) for damage %d", text_the().c_str(), health_get(), damage); }
  }

  //
  // If hit by something then abort following any path
  //
  if (is_player()) {
    if (game->robot_mode) {
      if (infop_get()->monst_state == MONST_STATE_MOVING) {
        clear_move_path("robot was hit while moving");
      } else {
        //
        // Allow the robot to continue resting as it might have been
        // trying to eat food to recover.
        //
      }
    } else {
      clear_move_path("player was hit");
    }
  }

  real_hitter->reset_goal_penalty(this);

  if (is_player()) {
    //
    // Player being hit
    //
    if (real_hitter == this) {
      //
      // You hit yourself
      //
      if (attack_poison) {
        if (level->is_gas_poison(curr_at.x, curr_at.y)) {
          msg("%%fg=yellow$Poison burns your lungs for %s%d damage!%%fg=reset$", damage_type.c_str(), damage);
        } else {
          msg("%%fg=yellow$Poison circulates through your veins for %s%d damage!%%fg=reset$", damage_type.c_str(),
              damage);
        }
      } else if (hitter->is_weapon()) {
        msg("%%fg=orange$You hit yourself for %d %sdamage with %s!%%fg=reset$", damage, damage_type.c_str(),
            hitter->text_the().c_str());
      } else if (hitter->is_laser()) {
        msg("%%fg=orange$You zap yourself for %d %sdamage with %s!%%fg=reset$", damage, damage_type.c_str(),
            hitter->text_the().c_str());
      } else if (hitter->is_item_magical()) {
        msg("%%fg=orange$You blast yourself for %d %sdamage with %s!%%fg=reset$", damage, damage_type.c_str(),
            hitter->text_the().c_str());
      } else if (attack_fire) {
        msg("%%fg=orange$You burn for %d %sdamage!%%fg=reset$", damage, damage_type.c_str());
      } else if (attack_cold) {
        msg("%%fg=cyan$You blister for %d %sdamage!%%fg=reset$", damage, damage_type.c_str());
      } else if (attack_necrosis) {
        msg("%%fg=limegreen$Your skin is falling away in chunks!%%fg=reset$");
      } else {
        msg("%%fg=orange$You hurt yourself for %d %sdamage with %s!%%fg=reset$", damage, damage_type.c_str(),
            hitter->text_the().c_str());
      }
    } else {
      if (is_dead || is_dying) {
        //
        // Fatal/final hit
        //
        if (attack_poison) {
          msg("%%fg=red$%s's fangs suck the last sustenance from you!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_necrosis) {
          msg("%%fg=red$%s's withering touch finishes you off!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (hitter->is_weapon()) {
          msg("%%fg=red$%s cuts you down with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              hitter->text_the(false).c_str());
        } else if (hitter->is_laser()) {
          msg("%%fg=red$%s zaps you apart with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              hitter->text_the().c_str());
        } else if (hitter->is_item_magical()) {
          msg("%%fg=red$%s blasts you into pieces with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              hitter->text_the().c_str());
        } else if (hitter->is_projectile() || hitter->is_laser()) {
          msg("%%fg=red$%s blasted you into bits with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              hitter->text_the().c_str());
        } else if (attack_acid) {
          msg("%%fg=red$%s dissolves your body!%%fg=reset$", real_hitter->text_The().c_str());
          popup("%%fg=red$Sizzle!");
        } else if (attack_natural) {
          msg("%%fg=red$%s %s deep!%%fg=reset$", real_hitter->text_The().c_str(),
              pluralise(real_hitter->damage_natural_attack_type()).c_str());
          popup("%%fg=red$Urk!");
        } else if (attack_energy) {
          msg("%%fg=red$%s blasts you apart!%%fg=reset$", real_hitter->text_The().c_str());
          popup("%%fg=red$Zap!");
        } else if (attack_lightning) {
          msg("%%fg=red$%s fries your body!%%fg=reset$", real_hitter->text_The().c_str());
          popup("%%fg=red$Brzzt!");
        } else if (attack_crush) {
          msg("%%fg=red$You are flattened by %s!%%fg=reset$", real_hitter->text_the().c_str());
          popup("%%fg=red$Splat!");
        } else if (attack_fire) {
          msg("%%fg=red$You are burnt to a crisp by %s!%%fg=reset$", real_hitter->text_the().c_str());
          popup("%%fg=red$Sizzle!");
        } else if (attack_digest) {
          msg("%%fg=red$You are being eaten by %s!%%fg=reset$", real_hitter->text_the().c_str());
          popup("%%fg=red$Slurp!");
        } else {
          msg("%%fg=red$%s %s you fatally!%%fg=reset$", real_hitter->text_The().c_str(),
              real_hitter->text_hits().c_str());
        }
      } else {
        //
        // Hit when not dead yet...
        //
        if (attack_poison) {
          msg("%%fg=yellow$%s's fangs poisons you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(),
              damage, damage_type.c_str());
        } else if (attack_necrosis) {
          msg("%%fg=limegreen$%s's withering touch rots your skin!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (crit) {
          msg("%%fg=red$%s CRITS you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str());
        } else if (hitter->is_weapon()) {
          msg("%%fg=orange$%s hits you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str(), hitter->text_the(false).c_str());
        } else if (hitter->is_laser()) {
          msg("%%fg=orange$%s zaps you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str(), hitter->text_the().c_str());
        } else if (hitter->is_item_magical()) {
          msg("%%fg=orange$%s blasts you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              damage, damage_type.c_str(), hitter->text_the().c_str());
        } else if (hitter->is_projectile() || hitter->is_laser()) {
          msg("%%fg=orange$%s blasted you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
              damage, damage_type.c_str(), hitter->text_the().c_str());
        } else if (attack_acid) {
          msg("%%fg=orange$%s burns you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str());
          popup("%%fg=red$Sizzle!");
        } else if (attack_natural) {
          if (! real_hitter->damage_natural_attack_type().empty()) {
            msg("%%fg=orange$%s attacks you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                damage_type.c_str());
            popup("%%fg=red$" + capitalise(real_hitter->damage_natural_attack_type()));
          } else {
            msg("%%fg=orange$%s bites you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                damage_type.c_str());
            popup("%%fg=red$Chomp!");
          }
        } else if (attack_energy) {
          msg("%%fg=orange$%s blasts you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str());
          popup("%%fg=red$Zap!");
        } else if (attack_lightning) {
          msg("%%fg=orange$%s electrocutes you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              damage_type.c_str());
          popup("%%fg=red$Brzzt!");
        } else if (attack_crush) {
          msg("%%fg=orange$You are being crushed by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
              damage);
          popup("%%fg=red$Ouch!");
        } else if (attack_fire) {
          if (real_hitter->is_explosion()) {
            msg("%%fg=orange$You are blasted by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
                damage);
          } else {
            msg("%%fg=orange$You are burnt by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(), damage);
          }
          popup("%%fg=red$!");
        } else if (attack_digest) {
          msg("%%fg=red$You are being consumed by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
              damage);
          popup("%%fg=red$Gulp!");
        } else {
          msg("%%fg=orange$%s %s you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(),
              real_hitter->text_hits().c_str(), damage, damage_type.c_str());
        }
      }
    }

    //
    // Player being hit
    //
    if (is_bloodied() || (damage > THING_DAMAGE_SHAKE_ABOVE)) {
      level->wobble_set(damage / THING_DAMAGE_SHAKE_SCALE);
    }
  } else {
    if (real_hitter->is_player()) {
      //
      // Player hitting something else
      //
      if (is_alive_monst() || is_mob()) {
        if (crit) {
          msg("%%fg=red$You CRIT hit %s for %d %sdamage!%%fg=reset$", text_the().c_str(), damage,
              damage_type.c_str());
        } else {
          if (hitter && (hitter != real_hitter)) {
            if (attack_poison) {
              msg("You poison %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            } else if (attack_necrosis) {
              msg("You rot %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            } else if (hitter->is_weapon()) {
              msg("You hit %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            } else if (hitter->is_laser()) {
              msg("You zap %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            } else if (hitter->is_item_magical()) {
              msg("You blast %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            } else {
              msg("You hit %s for %d %sdamage with %s.", text_the().c_str(), damage, damage_type.c_str(),
                  hitter->text_the().c_str());
            }
          } else {
            if (attack_poison) {
              msg("You poison %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            } else if (attack_necrosis) {
              msg("You rot %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            } else if (hitter->is_weapon()) {
              msg("You hit %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            } else if (hitter->is_laser()) {
              msg("You zap %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            } else if (hitter->is_item_magical()) {
              msg("You blast %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            } else {
              msg("You hit %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
            }
          }
        }
      } else if (is_item()) {
        if (hitter->is_weapon()) {
          msg("You hit %s.", text_the().c_str());
        } else if (hitter->is_laser()) {
          msg("You zap %s.", text_the().c_str());
        } else if (hitter->is_item_magical()) {
          msg("You blast %s.", text_the().c_str());
        } else {
          msg("You hit %s.", text_the().c_str());
        }
      } else if (is_rock() || is_wall_dungeon()) {
        if (hitter->is_weapon()) {
          msg("You hit %s, why though?", text_the().c_str());
        } else if (hitter->is_laser()) {
          msg("You zap %s, why though?", text_the().c_str());
        } else if (hitter->is_item_magical()) {
          msg("You blast %s, why though?", text_the().c_str());
        } else {
          msg("You hit %s, why though?", text_the().c_str());
        }
      } else {
        if (hitter->is_weapon()) {
          msg("You hit %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
        } else if (hitter->is_laser()) {
          msg("You zap %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
        } else if (hitter->is_item_magical()) {
          msg("You blast %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
        } else {
          msg("You hit %s for %d %sdamage.", text_the().c_str(), damage, damage_type.c_str());
        }
      }
    } else {
      //
      // Something else hitting something else
      //
    }
  }

  //
  // Trail of blood?
  //
  place_blood();

  //
  // Check for wand of fire projectiles (this is the non real hitter case)
  //
  if (attack_fire || hitter->is_fire() || hitter->is_lava() || real_hitter->is_fire() || real_hitter->is_lava()) {
    if (on_fire_set("hit by fire")) {
      if (is_player()) {
        msg("%%fg=red$You are literally ON FIRE!%%fg=reset$");
      } else {
        msg("%s is on fire!", text_The().c_str());
      }
      if (is_monst() || (is_player() && game->robot_mode)) {
        change_state(MONST_STATE_IDLE, "monst was set on fire");
      }
    }
  } else if (is_on_fire()) {
    if (is_player()) {
      if (real_hitter->is_monst()) {
        msg("%%fg=red$You burn whilst being attacked!%%fg=reset$");
      }
    }
    if (hitter->on_fire_set("hit by fire due to attacking")) {
      msg("%s sets itself on fire!", hitter->text_The().c_str());
    }
  }

  //
  // Interrupt whatever the monster was doing.
  //
  if (is_monst() || (is_player() && game->robot_mode)) {
    change_state(MONST_STATE_IDLE, "monst was attacked");
  }

  //
  // In player robot mode we want to keep track of enemies also
  //
  add_enemy(real_hitter);

  //
  // Visible hit indication
  //
  if (is_player()) {
    //
    // Player being hit
    //
    popup(string_sprintf("%%fg=red$-%d", damage));
  } else if (is_monst()) {
    //
    // ThingInfo being hit
    //
    if (hitter->is_player() || real_hitter->is_player()) {
      //
      // ThingInfo being hit by player
      //
      popup(string_sprintf("%%fg=white$-%d", damage));
    }
  }

  real_hitter->tick_last_did_something_set(game->tick_current);

  //
  // Splat graphics
  //
  if (is_monst() || is_player()) {
    if (is_pink_blooded()) {
      level->thing_new(tp_random_pink_splatter()->name(), curr_at);
    } else if (is_green_blooded()) {
      level->thing_new(tp_random_green_splatter()->name(), curr_at);
    } else if (is_red_blooded()) {
      level->thing_new(tp_random_red_splatter()->name(), curr_at);
    } else {
      //
      // Need something else for the undead?
      //
      level->thing_new(tp_random_red_splatter()->name(), curr_at);
    }
  }

  if (real_hitter != this) {
    if (real_hitter->is_player() || real_hitter->is_monst()) {
      wobble(90);
      bounce(0.5 /* height */, 0.1 /* fade */, 100, 1);
    }
  }

  //
  // Python callback. Poison looks like an attack on self, so avoid.
  //
  if (real_hitter != this) {
    //
    // Are we carrying a weapon? If not, see if we can do a claw attack
    //
    if (attack_natural || attack_poison || attack_digest ||
        ! real_hitter->equip_id_carry_anim_get(MONST_EQUIP_WEAPON).ok()) {
      auto claws = real_hitter->tp()->gfx_anim_use();
      if (claws != "") {
        auto natural_attack_effect = level->thing_new(claws, curr_at);
        natural_attack_effect->bounce(0.1, 0.1, 100, 3);
        natural_attack_effect->move_set_dir_from_delta(delta);

        real_hitter->on_you_natural_attack();
      }
    }
  }

  auto h = health_decr(damage);
  if (h <= 0) {
    h = health_set(0);

    //
    // Record who dun it.
    //
    dbg("Is killed by (%s) %u damage, health now %d", real_hitter->to_short_string().c_str(), damage, h);
    std::string defeater = real_hitter->text_a_or_an();

    //
    // If not a monst, e.g. a mob then don't include defeated by
    //
    auto reason = "by " + defeater;

    if (real_hitter->is_monst() || real_hitter->is_player()) {
      reason = "killed by " + defeater;
    }

    if ((real_hitter->curr_at == curr_at) && real_hitter->is_engulfer()) {
      reason = "digested in the bowels of " + defeater;
    }

    if (real_hitter == this) {
      if (attack_poison) {
        if (level->is_gas_poison(curr_at.x, curr_at.y)) {
          reason = "by poison gas";
        } else {
          reason = "by poisoning";
        }
      } else if (attack_future1) {
        reason = "by future1";
      } else if (attack_future2) {
        reason = "by future2";
      } else if (attack_future3) {
        reason = "by future3";
      } else if (attack_cold) {
        reason = "by cold";
      } else if (attack_fire) {
        reason = "by fire";
      } else if (attack_crush) {
        reason = "by crushing";
      } else if (attack_fire) {
        reason = "by burning";
      } else if (attack_lightning) {
        reason = "by a bolt of lighting";
      } else if (attack_energy) {
        reason = "by too much energy";
      } else if (attack_acid) {
        reason = "by acid";
      } else if (attack_digest) {
        reason = "by digestion";
      } else if (attack_necrosis) {
        reason = "by rotting";
      } else if (attack_natural) {
        reason = "by over friendly biting";
      }
    }

    dead(real_hitter, reason);

    //
    // Does the attacker feast on success?
    //
    if (real_hitter->can_eat(this)) {
      real_hitter->consume(this);
    }
  } else {
    dbg("Is hit by (%s) %u damage, health now %d", real_hitter->to_short_string().c_str(), damage, h);
  }

  //
  // Used by AI to know if we can relax
  //
  tick_last_i_was_attacked_set(game->tick_current);

  if (is_player()) {
    score_incr(damage);
  }

  //
  // This might trigger more damage
  //
  temperature_incr(hitter->temperature_get());

  //
  // Python callback
  //
  if (is_dead || is_dying) {
    on_you_are_hit_and_now_dead(hitter, real_hitter, crit, damage);

    //
    // Set up noise, for example a door being hit
    //
    level->noisemap_in_incr(curr_at.x, curr_at.y, noise_on_you_are_hit_but_still_alive());
  } else {
    on_you_are_hit_but_still_alive(hitter, real_hitter, crit, damage);

    //
    // Set up noise, for example a door being broken
    //
    level->noisemap_in_incr(curr_at.x, curr_at.y, noise_on_you_are_hit_and_now_dead());
  }

  //
  // Keep track of who hit me to avoid multiple hits per tick
  //
  if (maybe_aip()) {
    if (is_dead) {
      //
      // If dead, allow things to chomp on your bones
      //
    } else {
      //
      // If alive, one hit per tick
      //
      aip()->recently_hit_by[ real_hitter->id ] = true;
    }
  }

  return true;
}

//
// Returns true on the target being dead.
//
int Thing::is_hit(Thingp hitter, bool crit, bool attack_natural, bool attack_poison, bool attack_necrosis,
                  bool attack_future1, bool attack_future2, bool attack_future3, bool attack_cold, bool attack_fire,
                  bool attack_crush, bool attack_lightning, bool attack_energy, bool attack_acid, bool attack_digest,
                  int damage)
{
  TRACE_NO_INDENT();
  if (attack_natural || attack_digest) {
    //
    // Allow attacks when dead
    //
    hitter->log("Possible attack on %s", to_short_string().c_str());
  } else if (damage) {
    //
    // Filter attacks when dead
    //
    if (is_dead || is_dying) {
      hitter->log("Already dead, no more melee hits %s", to_short_string().c_str());
      return false;
    }
    hitter->log("Possible attack on %s", to_short_string().c_str());
  } else {
    //
    // Failed attack
    hitter->log("No damage");
    return false;
  }
  TRACE_NO_INDENT();

  //
  // If an arrow, who really fired it?
  //
  Thingp real_hitter = nullptr;

  if (hitter) {
    real_hitter = hitter->top_owner_get();

    //
    // If on fire, the fire is owned by the player. So don't make the player the real hitter.
    //
    if (real_hitter) {
      if (real_hitter->is_fire()) {
        if (real_hitter == this) {
          real_hitter = nullptr;
        }
      }
    }

    if (! real_hitter) {
      real_hitter = hitter;
    }
  }

  //
  // If we are pushed into lava and then catch fire, the spawn of fire causes another location check.
  // Avoid the lava hitting twice.
  //
  if (maybe_aip()) {
    if (aip()->recently_hit_by.find(real_hitter->id) != aip()->recently_hit_by.end()) {
      IF_DEBUG2 { hitter->log("No, I've already hit %s", to_short_string().c_str()); }
      return false;
    }
  }

  //
  // Cruel to let things keep on hitting you when you're dead
  // Even worse, to let them eat you, but better if you are dead first.
  //
  if (is_dead || is_dying) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG2 { hitter->log("Cannot hit dead thing, but can eat: %s", to_short_string().c_str()); }
    } else {
      IF_DEBUG2 { hitter->log("Cannot hit: %s is dead", to_short_string().c_str()); }
      return false;
    }
  }

  //
  // Allow rocks on the main level to be destoryed; but not in the border
  //
  if (is_toughness_very_hard()) {
    if ((curr_at.x < MAP_BORDER_ROCK) || (curr_at.y < MAP_BORDER_ROCK) ||
        (curr_at.x >= MAP_WIDTH - MAP_BORDER_ROCK) || (curr_at.y >= MAP_HEIGHT - MAP_BORDER_ROCK)) {
      IF_DEBUG2 { hitter->log("Cannot hit: %s is very_hard", to_short_string().c_str()); }
      return false;
    }
  }

  if (is_resurrecting) {
    IF_DEBUG2 { hitter->log("Cannot hit: %s is resurrecting", to_short_string().c_str()); }
    return false;
  }

  if (hitter && (hitter->is_dead || hitter->is_dying)) {
    //
    // This case is hit if a ghost runs into a player. The ghost takes
    // damage. We don't want the player to keep absorbing hits when
    // the ghost is dead though.
    //
    if (hitter->is_monst()) {
      IF_DEBUG2 { hitter->log("No, hitter %s is already dead", to_short_string().c_str()); }
      return false;
    }
  }

  //
  // Check to see if this is a thing that can be damaged by the hitter.
  //
  if (hitter) {
    //
    // Walls and doors and other solid object are not damaged by poison
    // or similar effects. Limit it to explosions and the like.
    //
    auto hitter_tp = hitter->tp();
    if (is_door()) {
      if (! hitter_tp->is_explosion() && ! hitter_tp->is_projectile() && ! hitter_tp->is_laser() &&
          ! hitter_tp->is_weapon() && ! hitter_tp->is_item_magical() && ! hitter_tp->is_fire() &&
          ! hitter_tp->is_lava() && ! hitter_tp->gfx_attack_anim()) {
        //
        // Not something that typically damages walls.
        //
        IF_DEBUG2 { hitter->log("No, %s is immune (1)", to_short_string().c_str()); }
        return false;
      }
    }

    if (is_wall() || is_rock()) {
      if (! hitter_tp->is_explosion() && ! hitter_tp->is_projectile() && ! hitter_tp->is_laser() &&
          ! hitter_tp->is_weapon() && ! hitter_tp->is_item_magical() && ! hitter_tp->is_fire() &&
          ! hitter_tp->is_lava() && ! hitter_tp->gfx_attack_anim()) {
        //
        // Not something that typically damages walls.
        //
        IF_DEBUG2 { hitter->log("No, %s is immune (2)", to_short_string().c_str()); }
        return false;
      }
    }

    if (hitter->is_fire()) {
      IF_DEBUG2 { hitter->log("Fire attack"); }
    }
  }

  IF_DEBUG2 { hitter->log("Hit succeeds"); }
  int hit_and_destroyed;

  hit_and_destroyed =
      ai_hit_actual(hitter, real_hitter, crit, attack_natural, attack_poison, attack_necrosis, attack_future1,
                    attack_future2, attack_future3, attack_cold, attack_fire, attack_crush, attack_lightning,
                    attack_energy, attack_acid, attack_digest, damage);

  return (hit_and_destroyed);
}
