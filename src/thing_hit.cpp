//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_python.h"
#include "my_sprintf.h"
#include "my_string.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_tile.h"

//
// Python callback upon being hit
//
void Thing::on_hit(Thingp hitter,      // an arrow / monst /...
                   Thingp real_hitter, // who fired the arrow?
                   bool crit, bool bite, int damage)
{
  TRACE_AND_INDENT();
  auto on_hit = tp()->on_hit_do();
  if (std::empty(on_hit)) {
    return;
  }

  auto t = split_tokens(on_hit, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, bite=%d, damage=%d)", mod.c_str(), fn.c_str(), to_string().c_str(),
        hitter->to_string().c_str(), real_hitter->to_string().c_str(), crit, bite, damage);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) mid_at.x,
                    (unsigned int) mid_at.y, (unsigned int) crit, (unsigned int) bite, (unsigned int) damage);
  } else {
    ERR("Bad on_hit call [%s] expected mod:function, got %d elems", on_hit.c_str(), (int) on_hit.size());
  }
}

//
// Python callback upon being miss
//
void Thing::on_miss(Thingp hitter)
{
  TRACE_AND_INDENT();
  auto on_miss = tp()->on_miss_do();
  if (std::empty(on_miss)) {
    return;
  }

  auto t = split_tokens(on_miss, '.');
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
    ERR("Bad on_miss call [%s] expected mod:function, got %d elems", on_miss.c_str(), (int) on_miss.size());
  }
}

void Thing::on_bite(void)
{
  TRACE_AND_INDENT();
  auto on_bite = tp()->on_bite_do();
  if (std::empty(on_bite)) {
    return;
  }

  auto t = split_tokens(on_bite, '.');
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
    ERR("Bad on_bite call [%s] expected mod:function, got %d elems", on_bite.c_str(), (int) on_bite.size());
  }
}

int Thing::ai_hit_actual(Thingp hitter,      // an arrow / monst /...
                         Thingp real_hitter, // who fired the arrow?
                         bool crit, bool bite, int poison, int damage)
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

  if (! real_hitter->monstp) {
    real_hitter->err("Has no monstp");
    return false;
  }

  IF_DEBUG2 { hitter->log("Hit %s (health %d) for damage %d", text_the().c_str(), get_health(), damage); }

  auto delta = mid_at - hitter->mid_at;

  if (crit) {
    damage *= 2;
  }

  //
  // Check for immunity
  //
  if (loves_fire()) {
    if (hitter->is_fire() || real_hitter->is_fire()) {
      if (is_player()) {
        TOPCON("You bask in the fire!");
      } else if (real_hitter->is_player()) {
        TOPCON("%s basks in the fire!", text_The().c_str());
      }
      return false;
    }
  }

  if (bite || poison) {
    if (loves_poison()) {
      if (hitter->is_poison() || real_hitter->is_poison()) {
        if (is_player()) {
          TOPCON("You drink in the poison!");
        } else if (real_hitter->is_player()) {
          TOPCON("%s drinks in the poison!", text_The().c_str());
        }
        health_boost(poison);
        return false;
      }
    } else if (poison) {
      incr_poison(poison);
      if (is_player()) {
        TOPCON("%%fg=yellow$You are poisoned for %d damage!%%fg=reset$", poison);
      } else if (real_hitter->is_player()) {
        TOPCON("%%fg=yellow$You poison %s for %d damage!%%fg=reset$", text_The().c_str(), poison);
      }
    }
  }

  if (real_hitter->is_stamina_check()) {
    if (! real_hitter->get_stamina()) {
      if (real_hitter->is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
        return false;
      }
    }
    real_hitter->decr_stamina(1);
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

  //
  // If hit by something then abort following any path
  //
  if (is_player()) {
    if (game->robot_mode) {
      if (monstp->robot_state == ROBOT_STATE_MOVING) {
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

  if (real_hitter->tp()->gfx_bounce_on_move()) {
    real_hitter->bounce(0.5, 0.1, 100, 3);
    real_hitter->move_set_dir_from_delta(delta);
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

  if (hates_fire()) {
    if (real_hitter->is_fire() || real_hitter->is_lava()) {
      if (damage_doubled_from_fire()) {
        damage *= 2;
        dbg("Double damage from fire");
      }
    }
  }

  if (hates_acid()) {
    if (real_hitter->is_acid()) {
      if (damage_doubled_from_acid()) {
        damage *= 2;
        dbg("Double damage from acid");
      }
    }
  }

  if (hates_poison()) {
    if (real_hitter->is_poison()) {
      if (damage_doubled_from_poison()) {
        damage *= 2;
        dbg("Double damage from poison");
      }
    }
  }

  if (hates_water()) {
    if (real_hitter->is_shallow_water() || real_hitter->is_deep_water()) {
      if (damage_doubled_from_water()) {
        damage *= 2;
        dbg("Double damage from water");
      }
    }
  }

  //
  // Try to steal
  //
  if (real_hitter->is_item_eater()) {
    if (is_carrying_item()) {
      if (real_hitter->steal_item_from(this)) {
        return true;
      }
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

  for (auto oid : real_hitter->monstp->skills) {
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

  if (is_player()) {
    if (damage > THING_DAMAGE_SHAKE_ABOVE) {
      level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
      if (real_hitter == this) {
        if (crit) {
          TOPCON("%%fg=red$You CRIT yourselfd for %d damage!%%fg=reset$", damage);
        } else {
          if (hitter->is_weapon()) {
            TOPCON("%%fg=red$You hit yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
          } else if (hitter->is_wand()) {
            TOPCON("%%fg=red$You zap yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
          } else {
            TOPCON("%%fg=red$You hurt yourself for %d damage with %s!%%fg=reset$", damage, hitter->text_the().c_str());
          }
        }

        if (game->robot_mode) {
          robot_change_state(ROBOT_STATE_IDLE, "robot CRIT attacked itself");
        }
      } else {
        if (crit) {
          TOPCON("%%fg=red$%s CRITS you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(), damage);
        } else {
          if (hitter->is_weapon()) {
            TOPCON("%%fg=red$%s hits you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                   hitter->text_the().c_str());
          } else if (hitter->is_wand()) {
            TOPCON("%%fg=red$%s zaps you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                   hitter->text_the().c_str());
          } else if (hitter->is_projectile() || hitter->is_laser()) {
            TOPCON("%%fg=red$%s blastd you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                   hitter->text_the().c_str());
          } else {
            TOPCON("%%fg=red$%s %s you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(),
                   real_hitter->text_hits().c_str(), damage);
          }
        }
      }

      if (real_hitter->is_fire() || real_hitter->is_lava()) {
        if (set_on_fire("hit by fire")) {
          TOPCON("%%fg=red$You are literally ON FIRE!%%fg=reset$");
        }
      }
    } else {
      if (real_hitter == this) {
        if (bite) {
          TOPCON("%%fg=yellow$You bite yourself for %d damage!%%fg=reset$", damage);
        } else {
          if (hitter->is_weapon()) {
            TOPCON("%%fg=yellow$You hit yourself for %d damage with %s!%%fg=reset$", damage,
                   hitter->text_the().c_str());
          } else if (hitter->is_wand()) {
            TOPCON("%%fg=yellow$You zap yourself for %d damage with %s!%%fg=reset$", damage,
                   hitter->text_the().c_str());
          } else {
            TOPCON("%%fg=yellow$You hurt yourself for %d damage with %s!%%fg=reset$", damage,
                   hitter->text_the().c_str());
          }
        }

        if (game->robot_mode) {
          robot_change_state(ROBOT_STATE_IDLE, "robot attacked itself");
        }
      } else {
        if (bite) {
          TOPCON("%%fg=yellow$%s bites you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(), damage);
        } else {
          if (hitter->is_weapon()) {
            TOPCON("%%fg=yellow$%s hits you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                   hitter->text_the().c_str());
          } else if (hitter->is_wand()) {
            TOPCON("%%fg=yellow$%s zaps you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                   hitter->text_the().c_str());
          } else if (hitter->is_projectile() || hitter->is_laser()) {
            TOPCON("%%fg=yellow$%s blasts you for %d damage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                   damage, hitter->text_the().c_str());
          } else {
            TOPCON("%%fg=yellow$%s %s you for %d damage!%%fg=reset$", real_hitter->text_The().c_str(),
                   real_hitter->text_hits().c_str(), damage);
          }
        }
      }
    }

    if (is_bloodied()) {
      level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
    }
  } else {
    if (game->robot_mode) {
      robot_change_state(ROBOT_STATE_IDLE, "robot attacked");
    }

    if (real_hitter->is_player()) {
      if (is_alive_monst() || is_minion_generator()) {
        if (crit) {
          TOPCON("%%fg=red$You CRIT hit %s for %d damage!%%fg=reset$", text_the().c_str(), damage);
        } else {
          if (hitter && (hitter != real_hitter)) {
            TOPCON("You hit %s for %d damage with %s.", text_the().c_str(), damage, hitter->text_the().c_str());
          } else {
            TOPCON("You hit %s for %d damage.", text_the().c_str(), damage);
          }
        }
      } else {
        TOPCON("You hit %s.", text_the().c_str());
      }
    }
    if (real_hitter->is_fire() || real_hitter->is_lava()) {
      set_on_fire("hit by fire or lava");
    }
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
    // Monst being hit
    //
    if (hitter->is_player() || real_hitter->is_player()) {
      //
      // Monst being hit by player
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
  if (bite || ! real_hitter->get_weapon_id_carry_anim().ok()) {
    auto claws = real_hitter->tp()->gfx_anim_attack();
    if (claws != "") {
      auto bite = level->thing_new(claws, mid_at);
      bite->bounce(0.1, 0.1, 100, 3);
      bite->move_set_dir_from_delta(delta);

      //
      // Python callback
      //
      real_hitter->on_bite();
    }
  }

  auto h = decr_health(damage);
  if (h <= 0) {
    h = set_health(0);

    //
    // Record who dun it.
    //
    dbg("Is killed by (%s) %u damage, health now %d", real_hitter->to_string().c_str(), damage, h);
    std::string killer = real_hitter->text_a_or_an();

    //
    // If not a monst, e.g. a generator then don't include killed by
    //
    auto reason = "killed by " + killer;
    if (! is_monst()) {
      reason = "by " + killer;
    }

    if ((real_hitter->mid_at == mid_at) && real_hitter->is_engulfer()) {
      reason = "in the bowels of " + killer;
    }

    dead(real_hitter, reason);

    //
    // Does the attacker feast on success?
    //
    if (real_hitter->can_eat(this)) {
      real_hitter->eat(this);
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
    on_hit(hitter, real_hitter, crit, bite, damage);
  }

  return true;
}

//
// Returns true on the target being dead.
//
int Thing::is_hit_by(Thingp hitter, bool crit, bool bite, int poison, int damage)
{
  TRACE_AND_INDENT();
  IF_DEBUG2 { hitter->log("Possible hit %s for %u", to_string().c_str(), damage); }
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
          ! hitter_tp->is_weapon() && ! hitter_tp->is_wand() && ! hitter_tp->is_fire() && ! hitter_tp->is_lava() &&
          ! hitter_tp->gfx_attack_anim()) {
        //
        // Not something that typically damages walls.
        //
        IF_DEBUG2 { hitter->log("No, %s is immune (1)", to_string().c_str()); }
        return false;
      }
    }

    if (is_wall() || is_rock()) {
      if (! hitter_tp->is_explosion() && ! hitter_tp->is_projectile() && ! hitter_tp->is_laser() &&
          ! hitter_tp->is_wand() && ! hitter_tp->gfx_attack_anim()) {
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
  int hit_and_killed;

  hit_and_killed = ai_hit_actual(hitter, real_hitter, crit, bite, poison, damage);

  return (hit_and_killed);
}

int Thing::is_hit_by(Thingp hitter, int damage)
{
  TRACE_AND_INDENT();
  return (is_hit_by(hitter, false, false, 0, damage));
}

int Thing::is_hit_by(Thingp hitter)
{
  TRACE_AND_INDENT();
  return (is_hit_by(hitter, false, false, hitter->get_damage_poison(), hitter->get_damage_melee()));
}
