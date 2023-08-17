//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

ThingShoved Thing::try_to_shove(Thingp victim, point delta, bool force)
{
  TRACE_NO_INDENT();

  if (! is_able_to_shove()) {
    return (THING_SHOVE_NEVER_TRIED);
  }

  dbg("Try to shove, %s delta %d,%d", victim->to_short_string().c_str(), (int) delta.x, (int) delta.y);
  TRACE_AND_INDENT();

  //
  // Are we daring enough to try shoving a larger creatuee?
  //
  if (! is_daring() && ! is_fearless()) {
    if (victim->thing_size() - thing_size() > 1) {
      dbg("Too large to shove, don't even try to shove %s", victim->to_short_string().c_str());
      return (THING_SHOVE_NEVER_TRIED);
    }
  }

  //
  // Wake on shove
  //
  bool was_sleeping = victim->is_sleeping;
  victim->wake("shoved");

  if (! victim->is_shovable()) {
    dbg("Not able to shove %s", victim->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  if (is_friend(victim)) {
    dbg("Not able to shove (same owner) %s", victim->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  if (same_mob(victim)) {
    dbg("Not able to shove (same master) %s", victim->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  //
  // Sanity check we cannot shove more than one tile
  //
  if ((fabs(delta.x) > 1) || (fabs(delta.y) > 1)) {
    dbg("Not able to shove (too far) %s", victim->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  dbg("Can shove, %s delta %d,%d", victim->to_short_string().c_str(), (int) delta.x, (int) delta.y);
  TRACE_AND_INDENT();

  move_finish();

  idle_count_set(0);

  bool was_dead = victim->is_dead;
  auto old_at   = victim->curr_at;

  //
  // If I'm on fire. set it on fire too!
  //
  if (on_fire_anim_id().ok()) {
    victim->on_fire_set("I am on fire, set it on fire too");
  }

  //
  // Annoy the thing being pushed
  //
  if (victim->is_alive_monst()) {
    victim->add_attacker(this);
  }

  point shove_delta = delta;
  point shove_pos   = victim->curr_at + shove_delta;

  if (force) {
    //
    // For example, shoving an block_of_ice with something it it, we need to bypass most checks.
    //
  } else {
    if (victim->is_block_of_ice()) {
      //
      // Allow to shove regardless of size
      //
    } else {
      //
      // Stop shoving of much larger things
      //
      if (victim->thing_size() - thing_size() > 1) {
        if (is_player()) {
          msg("%s is too large to be shoved!", victim->text_The().c_str());
        } else if (victim->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
      }
    }

    if (! victim->is_brazier() && ! victim->is_barrel() && ! victim->is_block_of_ice()) {
      if (! victim->shove_ok(shove_pos)) {
        if (is_player()) {
          msg("%s cannot be shoved! Something is in the way.", victim->text_The().c_str());
        } else if (victim->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
      }
    }

    if (! victim->is_dead) {
      dbg("Shove: Its strength %d vs me %d", victim->stat_str(), stat_str());

      int its_strength = victim->stat_str_total() + victim->shove_strength_total();

      if (victim->is_heavy()) {
        its_strength += 10;
      }

      if (victim->is_very_heavy()) {
        its_strength += 10;
      }

      if (was_sleeping) {
        its_strength /= 4;
      }

      dbg("Shove: Its strength (+ mods) %d vs me %d (+ mods)", its_strength, stat_str() + shove_strength_total());

      //
      // If my strength is greater than its strength, shove succeeds
      //
      if (d20_ge(stat_str_total() + shove_strength_total(), its_strength)) {
        //
        // You manage to shove it
        //
      } else {
        //
        // You fail to shove it
        //
        if (is_player()) {
          if (victim->is_monst()) {
            if (victim->is_able_to_shove()) {
              msg("%s shoves you back!", victim->text_The().c_str());
            } else {
              msg("%s is resolute!", victim->text_The().c_str());
            }
          } else {
            msg("%s refuses to budge!", victim->text_The().c_str());
          }
        } else if (victim->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return THING_SHOVE_TRIED_AND_FAILED;
      }

      if (victim->is_monst()) {
        if (! victim->is_dead) {
          victim->popup(string_sprintf("%%fg=orange$!"));
        }
      }
    }
  }

  //
  // If pushed into a chasm, move the thing first and then let it spawn dead things
  //
  dbg("Shove it");
  TRACE_AND_INDENT();

  //
  // The force check here is to allow something that is in a block of ice to be shoved to the new location where the
  // ice is.
  //
  if (! force && ! victim->shove_ok(shove_pos)) {
    //
    // This is a failure to shove
    //
    if (victim->is_brazier()) {
      if (! victim->is_dead) {
        if (is_player()) {
          msg("The brazier falls back on you!");
        }
        victim->move_to(curr_at);
      }
    } else if (victim->is_barrel()) {
      if (is_player()) {
        msg("The barrel will not budge!");
      }
    } else if (victim->is_block_of_ice()) {
      if (is_player()) {
        msg("The block of ice will not budge!");
      }
    } else {
      if (is_player()) {
        msg("%s cannot be shoved! Something blocks the way.", text_The().c_str());
      }
    }
  } else {
    if (is_player()) {
      if (victim->is_brazier()) {
        if (victim->is_dead) {
          msg("You kick the brazier around. Why though?");
        } else {
          msg("You knock over %s!", victim->text_the().c_str());
        }
      } else {
        if (victim->is_dead) {
          msg("You kick %s!", victim->text_the().c_str());
        } else {
          msg("You shove %s!", victim->text_the().c_str());
        }
      }
    } else if (victim->is_player()) {
      if (level->is_chasm(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the abyss, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the abyss!%%fg=reset$", text_The().c_str());
      } else if (level->is_lava(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%%fg=red$%s tries to shove you into the lava, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the red death!%%fg=reset$", text_The().c_str());
      } else if (level->is_deep_water(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%%fg=red$%s tries to shove you into the depths, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the depths!%%fg=reset$", text_The().c_str());
      } else if (level->is_water(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%%fg=red$%s tries to shove you into the puddle, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the puddle!%%fg=reset$", text_The().c_str());
      } else if (level->is_fire(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%%fg=red$%s tries to shove you into the flames, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the flames!%%fg=reset$", text_The().c_str());
      } else if (level->is_spiderweb(shove_pos)) {
        if (d20_ge(victim->stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%%fg=red$%s tries to shove you into the web, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the sticky web!%%fg=reset$", text_The().c_str());
      } else if (victim->is_dead) {
        if (d20_ge(stat_luck_total(), SAVING_ROLL_HARD)) {
          if (is_monst()) {
            msg("%s kicks your corpse for fun, but hurts itself!", text_The().c_str());
          }
        } else {
          msg("%s kicks your corpse for fun!", text_The().c_str());
        }
      } else {
        msg("%s shoves you!", text_The().c_str());
      }
    }

    victim->move_to(shove_pos);
  }

  if (! victim->is_dead) {
    if (victim->is_dead_on_shove()) {
      dbg("Shove and defeat");
      victim->dead("by being shoved");

      //
      // e.g. shoving a brazier creates a dead one
      //
      auto spawn_what = victim->spawn_on_shoved();
      if (spawn_what != "") {
        auto spawn_at = victim->curr_at;
        if (spawn_at.x > curr_at.x) {
          victim->dir_set_left();
        } else {
          victim->dir_set_right();
        }

        //
        // Must check at the new location
        //
        auto n = level->thing_new(spawn_what, spawn_at);
        if (n) {
          n->location_check();
        }
      }
    }
  }

  dbg("Handle location for shoved thing: %s", victim->to_short_string().c_str());
  victim->location_check();
  if (victim->is_player()) {
    //
    // Need this as we need to force a temperature check again, e.g. if shoved into lava
    //
    game->tick_begin("Shoved");
    victim->clear_move_path("Shoved");
  }

  //
  // If shoving something on fire! set yourself on fire!
  //
  if (! was_dead) {
    if (victim->is_fire()) {
      if (d20_ge(stat_luck_total(), SAVING_ROLL_HARD)) {
        if (is_player()) {
          msg("%%fg=orange$It burns as you shove it, but you luckily avoid the flames.%%fg=reset$");
        }
      } else if (pcg_random_range(0, 100) < 5) {
        if (is_player()) {
          if (on_fire_set("set yourself on fire")) {
            msg("%%fg=red$Clumsy! You set yourself on fire!%%fg=reset$");
          }
        }
      } else {
        if (is_player()) {
          msg("%%fg=orange$It burns as you shove it, but you avoid the flames.%%fg=reset$");
        }
      }
    }
  }

  //
  // For example, if shoving something like a block of ice, drag a dead dogman that is inside it.
  //
  if (! force) {
    //
    // No shove recursion
    //
    if (victim->is_shovable_and_sticky()) {
      TRACE_NO_INDENT();
      FOR_ALL_NON_INTERNAL_THINGS(level, t, old_at.x, old_at.y)
      {
        if (t == this) {
          continue;
        }

        if (t == victim) {
          continue;
        }

        if (! t->is_shovable()) {
          continue;
        }

        if (t->curr_at == victim->curr_at) {
          continue;
        }
        try_to_shove(t, delta, true);
      }

      TRACE_NO_INDENT();
      FOR_ALL_THINGS_END()
    }
  }

  return (THING_SHOVE_TRIED_AND_PASSED);
}

//
// Can we shove to this location?
//
bool Thing::shove_ok(point future_pos)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();
  FOR_ALL_COLLISION_THINGS(level, victim, future_pos.x, future_pos.y)
  {
    if (this == victim) {
      continue;
    }

    //
    // Skip things we cannot collide with
    //
    if (victim->is_falling || victim->is_jumping || victim->is_changing_level) {
      continue;
    }

    if (victim->is_obs_shoving()) {
      return false;
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  return true;
}

ThingShoved Thing::try_to_shove(point future_pos)
{
  TRACE_NO_INDENT();

  dbg("Try to shove, future pos %d,%d", (int) future_pos.x, (int) future_pos.y);
  TRACE_AND_INDENT();

  if (! is_able_to_shove()) {
    dbg("Not able to shove");
    return THING_SHOVE_NEVER_TRIED;
  }

  //
  // Check adjacent
  //
  auto  x     = future_pos.x;
  auto  y     = future_pos.y;
  auto  delta = point(x, y) - curr_at;
  point p(future_pos.x, future_pos.y);

  if ((fabs(delta.x) > 1) || (fabs(delta.y) > 1)) {
    dbg("Not adjacent to shove");
    return THING_SHOVE_NEVER_TRIED;
  }

  //
  // Try to shove heavy things first.
  //
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_THAT_INTERACT(level, victim, p.x, p.y)
  {
    if (this == victim) {
      continue;
    }
    dbg("Shove candidate, %s", victim->to_short_string().c_str());

    if (! victim->is_shovable()) {
      continue;
    }

    if (! victim->is_heavy()) {
      continue;
    }

    dbg("Shove heavy candidate, %s", victim->to_short_string().c_str());
    point shove_delta = delta;
    return (try_to_shove(victim, shove_delta));
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  TRACE_NO_INDENT();
  FOR_ALL_THINGS_THAT_INTERACT(level, victim, p.x, p.y)
  {
    if (this == victim) {
      continue;
    }
    dbg("Shove candidate, %s", victim->to_short_string().c_str());

    if (! victim->is_shovable()) {
      continue;
    }

    dbg("Shove candidate, %s", victim->to_short_string().c_str());
    point shove_delta = delta;
    return (try_to_shove(victim, shove_delta));
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  return (THING_SHOVE_NEVER_TRIED);
}

ThingShoved Thing::try_to_shove_into_hazard(Thingp victim, point delta)
{
  if (is_able_to_shove()) {
    auto shoved_to_position = victim->curr_at + delta;
    if (level->is_hazard((int) shoved_to_position.x, (int) shoved_to_position.y)) {
      return (try_to_shove(victim, delta));
    }
  }
  return (THING_SHOVE_NEVER_TRIED);
}
