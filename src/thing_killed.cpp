//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_game.hpp"
#include "my_log.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::killed(Thingp defeater, const std::string &reason)
{
  TRACE_NO_INDENT();
  killed(defeater, reason.c_str());
}

//
// Things are first dead, then killed, then destroyed. At the end of this we
// will add the thing to the gc (if it is not a corpse or resurrectable).
//
void Thing::killed(Thingp defeater, const char *reason)
{
  //
  // Check we're not in a death loop
  //
  if (is_dying) {
    return;
  }
  is_dying = true;

  TRACE_NO_INDENT();
  if (is_loggable()) {
    if (reason) {
      dbg("Killed, reason: %s", reason);
    } else {
      dbg("Killed");
    }
  }
  TRACE_AND_INDENT();

  ///////////////////////////////////////////////////////////////
  // WARNING: defeater can be nullptr
  ///////////////////////////////////////////////////////////////
  auto is_corpse_currently = is_corpse();

  //
  // If already dead, do nothing
  //
  if (is_dead) {
    if (is_loggable()) {
      dbg("Already dead");
    }

    //
    // Unless it is already a corpse. In such a case, if a corpse is
    // eaten we want to remove it.
    //
    if (! is_corpse_currently) {
      if (is_loggable()) {
        dbg("Already a corpse, can't die again");
      }
      return;
    }

    //
    // You only die once
    //
    if (is_player()) {
      dbg("Player only dies once");
      return;
    }
  }

  //
  // Unequip weapons. Keep player items around for post mortem analysis.
  //
  if (! is_player()) {
    FOR_ALL_EQUIP(e) { unequip("owner is dead", e, false); }
  }

  //
  // If in a bag, get out of there!
  //
  auto immediate_owner = immediate_owner_get();
  if (immediate_owner) {
    immediate_owner->bag_remove(this);
  }

  //
  // If a minion mob dies, kill all minions
  //
  if (defeater && is_mob()) {
    destroy_minions(defeater);
  }

  if (defeater && is_spawner()) {
    destroy_spawned(defeater);
  }

  //
  // Set is_dead after the log message or we print it as dead
  //
  auto The_no_dying = text_The_no_dying();
  is_dead           = true;

  //
  // Resurrect unless say this was a minion and its mob died
  //
  if (! is_resurrection_blocked) {
    if (is_resurrectable()) {
      tick_resurrect_when_set(game->tick_current + resurrect_get());
    }
  }

  //
  // So that slimes don't keep moving when dead
  //
  move_finish();

  if (maybe_itemsp()) {
    //
    // Drop everything!
    //
    if (on_death_drop_all_items()) {
      dbg("Drop all items on death");
      TRACE_AND_INDENT();

      if (is_monst() || is_player()) {
        dbg("Final item list at death:");
        TRACE_AND_INDENT();

        check_all_carried_items_are_owned();
      }
      drop_all();
      dbg("Dropped all items");
    }
  }

  if (! is_corpse_currently) {
    if (on_death_is_open()) {
      dbg("Defeated, now open");
      level_pop();
      is_open = true;
      level_push();
      auto p = level->player;
      if (p) {
        int distance = distance_to_player();
        if (is_door()) {
          if (defeater && defeater->is_fire()) {
            if (distance < 5) {
              msg("The door burns through.");
            } else if (distance < DMAP_IS_PASSABLE) {
              msg("The hear the crackling of burning wood.");
            } else {
              msg("You smell smoke in the air.");
            }
          } else if (defeater && defeater->is_player()) {
            msg("The door crashes open.");
          } else {
            if (distance <= 1) {
              msg("You see the door crash open.");
            } else if (distance < DMAP_IS_PASSABLE) {
              msg("The hear the noise of a door crashing open.");
            } else {
              msg("The hear the distant noise of a door crashing open.");
            }
          }
          p->update_light();
        } else {
          //
          // e.g. treasure chest
          //
          if (defeater && defeater->is_fire()) {
            if (distance < 5) {
              msg("%s burns.", text_The().c_str());
            } else {
              msg("You smell smoke in the air.");
            }
          } else if (defeater && defeater->is_player()) {
            msg("%s breaks open.", text_The().c_str());
          } else {
            if (distance <= 1) {
              msg("You see %s crash open.", text_the().c_str());
            } else if (distance < DMAP_IS_PASSABLE) {
              msg("The hear the noise of a %s crashing open.", short_text_a_or_an().c_str());
            } else {
              msg("The hear the distant noise of %s crashing open.", short_text_a_or_an().c_str());
            }
          }
        }
      }
    }
  }

  if (! level->is_being_destroyed) {
    place_blood(true);

    //
    // Add to the hiscore table?
    //
    if (is_player()) {
      //
      // Poor player
      //
      if (game->robot_mode) {
        if (defeater && defeater->is_acid()) {
          msg("%%fg=red$RIP: Robot is dissolved to death %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_fire()) {
          msg("%%fg=red$RIP: Robot is burnt to death %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_water()) {
          msg("%%fg=red$RIP: Robot is drowned %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_necrotic_danger_level()) {
          msg("%%fg=red$RIP: Robot is falls to pieces, %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_engulfer()) {
          msg("%%fg=red$RIP: Robot is consumed, %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_monst()) {
          msg("%%fg=red$RIP: Robot is disassembled, %s.%%fg=reset$", reason);
        } else {
          msg("%%fg=red$RIP: Robot is deactivated, %s.%%fg=reset$", reason);
        }
      } else {
        if (defeater && defeater->is_acid()) {
          msg("%%fg=red$RIP: You are dissolved to death %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_fire()) {
          msg("%%fg=red$RIP: You are burnt to death %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_water()) {
          msg("%%fg=red$RIP: You are drowned %s.", reason);
        } else if (defeater && defeater->is_necrotic_danger_level()) {
          msg("%%fg=red$RIP: You are rotted to death %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_engulfer()) {
          msg("%%fg=red$RIP: You are consumed %s.%%fg=reset$", reason);
        } else if (defeater && defeater->is_monst()) {
          msg("%%fg=red$RIP: You are %s.%%fg=reset$", reason);
        } else {
          msg("%%fg=red$RIP: You are killed %s.%%fg=reset$", reason);
        }
      }
    }

    {
      auto on_death = on_death_do();
      if (! std::empty(on_death)) {
        auto t = split_tokens(on_death, '.');
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
          ERR("Bad on_death call [%s] expected mod:function, got %d elems", on_death.c_str(), (int) on_death.size());
        }
      }
    }

    //
    // If this is the leader, the followers may react
    //
    notify_followers_of_death_of_my_leader();

    //
    // Tell the leader I am dead
    //
    auto leader = leader_get();
    if (leader) {
      on_death_of_a_follower(leader);
    }

    //
    // Add to the hiscore table?
    //
    if (is_player()) {
      //
      // Poor player
      //
      if (! score_get()) {
        score_incr(1);
      }

      if (game->config.hiscores.is_new_hiscore(this)) {
        if (game->robot_mode) {
          msg("%%fg=yellow$New robo high score, %s place!%%fg=reset$", game->config.hiscores.place_str(this));
        } else {
          msg("%%fg=yellow$New high score, %s place!%%fg=reset$", game->config.hiscores.place_str(this));
        }
        game->config.hiscores.add_new_hiscore(this, title(), reason);
      }

      level->is_map_follow_player = false;
      game->wid_dead_select(reason);
    } else if (is_loggable()) {
      dbg("%s killed, %s", The_no_dying.c_str(), reason);
      if (defeater && (defeater != this)) {
        if (defeater->is_player()) {
          if (is_monst()) {
            if (is_undead()) {
              msg("%%fg=white$%s is vanquished, %s.%%fg=reset$", The_no_dying.c_str(), reason);
            } else if (is_jelly()) {
              msg("%%fg=white$%s is splattered, %s.%%fg=reset$", The_no_dying.c_str(), reason);
            } else {
              msg("%%fg=white$%s is dead, %s.%%fg=reset$", The_no_dying.c_str(), reason);
            }
          } else if (on_death_is_open()) {
            //
            // Already logged
            //
          } else {
            msg("%s is destroyed, %s.", The_no_dying.c_str(), reason);
          }

          defeater->score_add(this);
        } else if (is_monst() && (distance_to_player() >= DMAP_IS_PASSABLE)) {
          if (is_undead()) {
            msg("You hear the distant cry of the undead...");
          } else if (is_jelly()) {
            msg("You hear a distant splat...");
          } else if (is_humanoid()) {
            msg("You hear distant common language cursing...");
          } else if (is_meat()) {
            msg("You hear the distant crunching of bones...");
          } else {
            msg("You hear a distant shriek...");
          }
        }
      }
    }

    if (is_corpse_currently) {
      //
      // Already a corpse
      //
      dbg("Already a corpse, clean it up");
      if (! tick_resurrect_when_get()) {
        if (is_bony()) {
          dbg("Can place final bones");
          auto tpp = tp_random_bones();
          if (tpp) {
            (void) level->thing_new(tpp, curr_at);
          }
        }
      }
    } else if (is_corpse_on_death()) {
      //
      // Leaves a corpse
      //
      if (! level->is_being_destroyed) {
        dbg("Defeated, leaves corpse");
        level->is_corpse_set(curr_at.x, curr_at.y);

        if (i_set_is_monst) {
          i_set_is_monst = false;
          level->is_monst_unset(curr_at.x, curr_at.y);
        }
        return;
      }
    }

    //
    // If this was blocking the way to the player, update that now
    //
    if (is_obs_wall_or_door()) {
      level->request_dmap_to_player_update = true;
    }
  }

  is_dying = false;

  level_pop();

  if (is_loggable()) {
    dbg("Need to garbage collect");
  }

  gc();
}
