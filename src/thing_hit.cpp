//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
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
void Thing::on_you_are_hit(Thingp hitter,      // an arrow / monst /...
                           Thingp real_hitter, // who fired the arrow?
                           bool crit, bool bite, bool poison, bool necrosis, int damage)
{
  TRACE_AND_INDENT();
  auto on_you_are_hit = tp()->on_you_are_hit_do();
  if (std::empty(on_you_are_hit)) {
    return;
  }

  auto t = split_tokens(on_you_are_hit, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, bite=%d, damage=%d)", mod.c_str(), fn.c_str(), to_string().c_str(),
        hitter->to_string().c_str(), real_hitter->to_string().c_str(), crit, bite, damage);

    //
    // Warning cannot handle negative values here for damage
    //
    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) mid_at.x,
                    (unsigned int) mid_at.y, (unsigned int) crit, (unsigned int) bite, (unsigned int) poison,
                    (unsigned int) necrosis, (unsigned int) damage);
  } else {
    ERR("Bad on_you_are_hit call [%s] expected mod:function, got %d elems", on_you_are_hit.c_str(),
        (int) on_you_are_hit.size());
  }
}

//
// Python callback upon being miss
//
void Thing::on_you_miss_do(Thingp hitter)
{
  TRACE_AND_INDENT();
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), hitter->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_you_miss_do call [%s] expected mod:function, got %d elems", on_you_miss_do.c_str(),
        (int) on_you_miss_do.size());
  }
}

void Thing::on_you_bite_attack(void)
{
  TRACE_AND_INDENT();
  auto on_you_bite_attack = tp()->on_you_bite_attack_do();
  if (std::empty(on_you_bite_attack)) {
    return;
  }

  auto t = split_tokens(on_you_bite_attack, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_you_bite_attack call [%s] expected mod:function, got %d elems", on_you_bite_attack.c_str(),
        (int) on_you_bite_attack.size());
  }
}

int Thing::ai_hit_actual(Thingp hitter,      // an arrow / monst /...
                         Thingp real_hitter, // who fired the arrow?
                         bool crit, bool bite, bool poison, bool necrosis, int damage)
{
  TRACE_AND_INDENT();
  if (! hitter) {
    err("No hitter");
    return false;
  }

  if (! real_hitter) {
    err("No real hitter");
    return false;
  }

  if (! real_hitter->maybe_infop()) {
    real_hitter->err("Has no infop");
    return false;
  }

  if (crit) {
    damage *= 2;
  }

  if (real_hitter->is_fire() || real_hitter->is_lava()) {
    if (damage_value_doubled_from_fire()) {
      damage *= 2;
      dbg("Double damage from fire");
    }
  }

  if (real_hitter->is_acid()) {
    if (damage_value_doubled_from_acid()) {
      damage *= 2;
      dbg("Double damage from acid");
    }
  }

  if (real_hitter->is_poisonous_danger_level()) {
    if (damage_value_doubled_from_poison()) {
      damage *= 2;
      dbg("Double damage from poison");
    }
  }

  if (real_hitter->is_necrotic_danger_level()) {
    if (damage_value_doubled_from_necrosis()) {
      damage *= 2;
      dbg("Double damage from necrosis");
    }
  }

  if (environ_avoids_water()) {
    if (real_hitter->is_shallow_water() || real_hitter->is_deep_water()) {
      if (damage_value_doubled_from_water()) {
        damage *= 2;
        dbg("Double damage from water");
      }
    }
  }

  //
  // Cruel to let things keep on hitting you when you're dead
  //
  if (is_dead) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG2 { hitter->log("Hit bypass, eat it"); }
      damage = 0;
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

  auto delta = mid_at - hitter->mid_at;

  if (real_hitter->tp()->gfx_bounce_on_move()) {
    real_hitter->bounce(0.5, 0.1, 100, 3);
    real_hitter->move_set_dir_from_delta(delta);
  }

  if (real_hitter->is_able_to_tire()) {
    if (! real_hitter->get_stamina()) {
      if (real_hitter->is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
        return false;
      }
    }
    real_hitter->decr_stamina(1);
  }

  //
  // Check for immunity
  //
  if (environ_prefers_fire()) {
    if (hitter->is_fire() || real_hitter->is_fire()) {
      if (is_player()) {
        TOPCON("You bask in the fire!");
      } else if (real_hitter->is_player()) {
        TOPCON("%s basks in the fire!", text_The().c_str());
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
  if (poison) {
    if (environ_prefers_poison()) {
      if (hitter->is_poisonous_danger_level() || real_hitter->is_poisonous_danger_level()) {
        if (is_player()) {
          TOPCON("You drink in the poison!");
        } else if (real_hitter->is_player()) {
          TOPCON("%s drinks in the poison!", text_The().c_str());
        }
        health_boost(poison);
        return false;
      }
    } else if (poison) {
      if (is_player()) {
        TOPCON("%%fg=yellow$You are poisoned for %d damage!%%fg=reset$", poison);
      } else if (is_alive_monst() && real_hitter->is_player()) {
        TOPCON("%%fg=yellow$You poison %s for %d damage!%%fg=reset$", text_the().c_str(), poison);
      }
      if (real_hitter->is_poisonous_danger_level()) {
        incr_poisoned_amount(poison);
      }
      poisoned();
    }
  }

  //
  // Necrotic attack
  //
  if (necrosis) {
    if (is_undead() || is_ethereal()) {
      if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
        if (is_player()) {
          TOPCON("You are immune to the withering touch of %s!", text_the().c_str());
        } else if (real_hitter->is_player()) {
          TOPCON("%s shrugs off your withering touch!", text_The().c_str());
        }
        return false;
      }
    } else {
      if (pcg_random_range(0, 100) < 50) {
        if (environ_prefers_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              TOPCON("You gain strength from the withering touch!");
            } else if (real_hitter->is_player()) {
              TOPCON("%s gains strength from your withering touch!", text_The().c_str());
            }
            incr_stat_strength();
            return false;
          }
        } else {
          if (is_player()) {
            TOPCON("%%fg=limegreen$Your skin is rotting. You lose 1 permanent strength!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            TOPCON("%%fg=limegreen$Your rotting hand touches %s for 1 permanent strength damage!%%fg=reset$",
                   text_the().c_str());
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              incr_necrotized_amount(damage - 1);
            }
          }
          decr_stat_strength();
          rotting();
        }
      } else {
        if (environ_prefers_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              TOPCON("You gain constitution from the withering touch!");
            } else if (real_hitter->is_player()) {
              TOPCON("%s gains constitution from your withering touch!", text_The().c_str());
            }
            incr_stat_constitution();
            return false;
          }
        } else {
          if (is_player()) {
            TOPCON("%%fg=limegreen$Your skin is rotting. You lose 1 permanent constitution!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            TOPCON("%%fg=limegreen$Your rotting hand touches %s for 1 permanent constitution damage!%%fg=reset$",
                   text_the().c_str());
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              incr_necrotized_amount(damage - 1);
            }
          }
          decr_stat_constitution();
          rotting();
        }
      }
    }
  }

  IF_DEBUG2 { hitter->log("Hit %s (health %d) for damage %d", text_the().c_str(), get_health(), damage); }

  //
  // If hit by something then abort following any path
  //
  if (is_player()) {
    if (game->robot_mode) {
      if (get_infop()->monst_state == MONST_STATE_MOVING) {
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

  //
  // If a wand is firing a laser, then get the damage from the
  // wand so we can add in enchants.
  //
  if (hitter->is_laser()) {
    auto owner = hitter->get_immediate_owner();
    if (owner) {
      if (owner->get_current_damage()) {
        damage = owner->get_current_damage();
        owner->set_current_damage(0);
      }
    }
  }

  if (real_hitter->maybe_itemp()) {
    for (auto oid : real_hitter->get_itemp()->skills) {
      auto skill = level->thing_find(oid);
      if (skill && skill->is_activated) {
        //
        // Allow the damage to be modified
        //
        real_hitter->set_current_damage(damage);
        real_hitter->use(skill);
        damage = real_hitter->get_current_damage();
      }
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
      if (poison) {
        TOPCON("%%fg=darkred$Poison courses through your veins for %d damage!%%fg=reset$", damage);
      } else if (necrosis) {
        TOPCON("%%fg=limegreen$Your skin is falling away in chunks!%%fg=reset$");
      } else if (crit) {
        TOPCON("%%fg=red$You CRIT yourself for %d damage!%%fg=reset$", damage);
      } else if (hitter->is_weapon()) {
        TOPCON("%%fg=orange$You hit yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
      } else if (hitter->is_laser()) {
        TOPCON("%%fg=orange$You zap yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
      } else if (hitter->is_item_magical()) {
        TOPCON("%%fg=orange$You blast yourself for %d damage with %s!%%fg=reset$", damage,
               hitter->text_the().c_str());
      } else {
        TOPCON("%%fg=orange$You hurt yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
      }
    } else {
      if (poison) {
        TOPCON("%%fg=darkred$%s's bite poisons you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(),
               damage);
      } else if (necrosis) {
        TOPCON("%%fg=limegreen$%s's withering touch rots your skin!%%fg=reset$", real_hitter->text_The().c_str());
      } else if (crit) {
        TOPCON("%%fg=red$%s CRITS you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(), damage);
      } else if (hitter->is_weapon()) {
        TOPCON("%%fg=orange$%s hits you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
               hitter->text_the().c_str());
      } else if (hitter->is_laser()) {
        TOPCON("%%fg=orange$%s zaps you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
               hitter->text_the().c_str());
      } else if (hitter->is_item_magical()) {
        TOPCON("%%fg=orange$%s blasts you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
               hitter->text_the().c_str());
      } else if (hitter->is_projectile() || hitter->is_laser()) {
        TOPCON("%%fg=orange$%s blasted you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
               damage, hitter->text_the().c_str());
      } else if (bite) {
        if (real_hitter->mid_at == mid_at) {
          TOPCON("%%fg=orange$%s digests you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(), damage);
        } else {
          TOPCON("%%fg=orange$%s bites you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(), damage);
        }
      } else {
        TOPCON("%%fg=orange$%s %s you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(),
               real_hitter->text_hits().c_str(), damage);
      }
    }

    if (real_hitter->is_fire() || real_hitter->is_lava()) {
      if (set_on_fire("hit by fire")) {
        TOPCON("%%fg=red$You are literally ON FIRE!%%fg=reset$");
      }
    }

    //
    // Player being hit
    //
    if (is_bloodied() || (damage > THING_DAMAGE_SHAKE_ABOVE)) {
      level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
    }
  } else {
    if (real_hitter->is_player()) {
      //
      // Player hitting something else
      //
      if (is_alive_monst() || is_minion_generator()) {
        if (crit) {
          TOPCON("%%fg=red$You CRIT hit %s for %d damage!%%fg=reset$", text_the().c_str(), damage);
        } else {
          if (hitter && (hitter != real_hitter)) {
            if (poison) {
              TOPCON("You poison %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            } else if (necrosis) {
              TOPCON("You rot %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            } else if (hitter->is_weapon()) {
              TOPCON("You hit %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            } else if (hitter->is_laser()) {
              TOPCON("You zap %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            } else if (hitter->is_item_magical()) {
              TOPCON("You blast %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            } else {
              TOPCON("You hit %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
            }
          } else {
            if (poison) {
              TOPCON("You poison %s for %d damage.", text_the().c_str(), damage);
            } else if (necrosis) {
              TOPCON("You rot %s for %d damage.", text_the().c_str(), damage);
            } else if (hitter->is_weapon()) {
              TOPCON("You hit %s for %d damage.", text_the().c_str(), damage);
            } else if (hitter->is_laser()) {
              TOPCON("You zap %s for %d damage.", text_the().c_str(), damage);
            } else if (hitter->is_item_magical()) {
              TOPCON("You blast %s for %d damage.", text_the().c_str(), damage);
            } else {
              TOPCON("You hit %s for %d damage.", text_the().c_str(), damage);
            }
          }
        }
      } else if (is_item()) {
        if (hitter->is_weapon()) {
          TOPCON("You hit %s.", text_the().c_str());
        } else if (hitter->is_laser()) {
          TOPCON("You zap %s.", text_the().c_str());
        } else if (hitter->is_item_magical()) {
          TOPCON("You blast %s.", text_the().c_str());
        } else {
          TOPCON("You hit %s.", text_the().c_str());
        }
      } else {
        if (hitter->is_weapon()) {
          TOPCON("You hit %s for %d damage.", text_the().c_str(), damage);
        } else if (hitter->is_laser()) {
          TOPCON("You zap %s for %d damage.", text_the().c_str(), damage);
        } else if (hitter->is_item_magical()) {
          TOPCON("You blast %s for %d damage.", text_the().c_str(), damage);
        } else {
          TOPCON("You hit %s for %d damage.", text_the().c_str(), damage);
        }
      }
    } else {
      //
      // Something else hitting something else
      //
    }

    //
    // Monster or player hitting something
    //
    if (real_hitter->is_fire() || real_hitter->is_lava()) {
      set_on_fire("hit by fire or lava");
    }
  }

  //
  // Interrupt whatever the monster was doing.
  //
  if (is_monst() || (is_player() && game->robot_mode)) {
    ai_change_state(MONST_STATE_IDLE, "monst was attacked");
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
    msg(string_sprintf("%%fg=red$-%d", damage));
  } else if (is_monst()) {
    //
    // ThingInfo being hit
    //
    if (hitter->is_player() || real_hitter->is_player()) {
      //
      // ThingInfo being hit by player
      //
      msg(string_sprintf("%%fg=white$-%d", damage));
    }
  }

  real_hitter->set_tick_last_did_something(game->tick_current);

  //
  // Blood splat
  //
  if (is_monst() || is_player()) {
    level->thing_new(tp_random_blood_splatter()->name(), mid_at);
  }

  if (real_hitter->is_player() || real_hitter->is_monst()) {
    wobble(90);
    bounce(0.5 /* height */, 0.1 /* fade */, 100, 1);
  }

  //
  // Are we carrying a weapon? If not, see if we can do a claw attack
  //
  if (bite || ! real_hitter->get_equip_id_carry_anim(MONST_EQUIP_WEAPON).ok()) {
    auto claws = real_hitter->tp()->gfx_anim_use();
    if (claws != "") {
      auto bite = level->thing_new(claws, mid_at);
      bite->bounce(0.1, 0.1, 100, 3);
      bite->move_set_dir_from_delta(delta);

      //
      // Python callback
      //
      real_hitter->on_you_bite_attack();
    }
  }

  auto h = decr_health(damage);
  if (h <= 0) {
    h = set_health(0);

    //
    // Record who dun it.
    //
    dbg("Is defeated by (%s) %u damage, health now %d", real_hitter->to_string().c_str(), damage, h);
    std::string defeater = real_hitter->text_a_or_an();

    //
    // If not a monst, e.g. a generator then don't include defeated by
    //
    auto reason = "by " + defeater;

    if ((real_hitter->mid_at == mid_at) && real_hitter->is_engulfer()) {
      reason = "in the bowels of " + defeater;
    }

    dead(real_hitter, reason);

    //
    // Does the attacker feast on success?
    //
    if (real_hitter->can_eat(this)) {
      real_hitter->consume(this);
    }
  } else {
    dbg("Is hit by (%s) %u damage, health now %d", real_hitter->to_string().c_str(), damage, h);
  }

  if (is_player()) {
    incr_score(damage);
  }

  //
  // Python callback
  //
  if (! is_dead) {
    on_you_are_hit(hitter, real_hitter, crit, bite, poison, necrosis, damage);
  }

  //
  // Keep track of who hit me to avoid multiple hits per tick
  //
  if (maybe_aip()) {
    get_aip()->recently_hit_by[ real_hitter->id ] = true;
  }

  return true;
}

//
// Returns true on the target being dead.
//
int Thing::is_hit(Thingp hitter, bool crit, bool bite, bool poison, bool necrosis, int damage)
{
  TRACE_AND_INDENT();
  if (bite) {
    IF_DEBUG2 { hitter->log("Possible bite %s for %d bite damage", to_string().c_str(), damage); }
  } else if (poison) {
    IF_DEBUG2 { hitter->log("Possible poison attack %s for %d damage", to_string().c_str(), damage); }
  } else if (necrosis) {
    IF_DEBUG2 { hitter->log("Possible necrosis attack %s for %d damage", to_string().c_str(), damage); }
  } else if (damage) {
    IF_DEBUG2 { hitter->log("Possible melee hit %s for %d damage", to_string().c_str(), damage); }
  } else {
    IF_DEBUG2
    {
      hitter->log("No damage");
      return false;
    }
  }
  TRACE_AND_INDENT();

  //
  // If an arrow, who really fired it?
  //
  Thingp real_hitter = nullptr;

  if (hitter) {
    real_hitter = hitter->get_immediate_owner();

    //
    // If on fire, the fire is owned by the player. So don't make the
    // player the real hitter.
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
    if (get_aip()->recently_hit_by.find(real_hitter->id) != get_aip()->recently_hit_by.end()) {
      IF_DEBUG2 { hitter->log("No, I've already hit %s", to_string().c_str()); }
      return false;
    }
  }

  //
  // Cruel to let things keep on hitting you when you're dead
  // Even worse, to let them eat you, but better if you are dead first.
  //
  if (is_dead) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG2 { hitter->log("Cannot hit dead thing, but can eat: %s", to_string().c_str()); }
    } else {
      IF_DEBUG2 { hitter->log("Cannot hit: %s is dead", to_string().c_str()); }
      return false;
    }
  }

  if (is_indestructible()) {
    IF_DEBUG2 { hitter->log("Cannot hit: %s is indestructible", to_string().c_str()); }
    return false;
  }

  if (is_resurrecting) {
    IF_DEBUG2 { hitter->log("Cannot hit: %s is resurrecting", to_string().c_str()); }
    return false;
  }

  if (hitter && hitter->is_dead) {
    //
    // This case is hit if a ghost runs into a player. The ghost takes
    // damage. We don't want the player to keep absorbing hits when
    // already dead though.
    //
    IF_DEBUG2 { hitter->log("No, hitter %s is already dead", to_string().c_str()); }
    return false;
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
        IF_DEBUG2 { hitter->log("No, %s is immune (1)", to_string().c_str()); }
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
        IF_DEBUG2 { hitter->log("No, %s is immune (2)", to_string().c_str()); }
        return false;
      }
    }

    if (hitter->is_fire()) {
      IF_DEBUG2 { hitter->log("Fire attack"); }
    }
  }

  IF_DEBUG2 { hitter->log("Hit succeeds"); }
  int hit_and_destroyed;

  hit_and_destroyed = ai_hit_actual(hitter, real_hitter, crit, bite, poison, necrosis, damage);

  return (hit_and_destroyed);
}

int Thing::is_bitten_by(Thingp hitter, int damage)
{
  TRACE_AND_INDENT();
  return (is_hit(hitter, false, true, false, false, damage));
}

int Thing::is_attacked_by(Thingp hitter, int damage)
{
  TRACE_AND_INDENT();
  return (is_hit(hitter, false, false, false, false, damage));
}

int Thing::is_poisoned_by(Thingp hitter, int damage)
{
  TRACE_AND_INDENT();
  return (is_hit(hitter, false, false, true, false, damage));
}

int Thing::is_necrotized_by(Thingp hitter, int damage)
{
  TRACE_AND_INDENT();
  return (is_hit(hitter, false, false, false, true, damage));
}
