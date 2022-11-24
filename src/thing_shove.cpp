//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <math.h>

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

ThingShoved Thing::try_to_shove(Thingp it, point delta, bool force)
{
  TRACE_NO_INDENT();

  if (! is_able_to_shove()) {
    return (THING_SHOVE_NEVER_TRIED);
  }

  dbg("Try to shove, %s delta %d,%d", it->to_short_string().c_str(), (int) delta.x, (int) delta.y);
  TRACE_AND_INDENT();

  //
  // Wake on shove
  //
  bool was_sleeping = it->is_sleeping;
  it->wake("shoved");

  if (! it->is_shovable()) {
    dbg("Not able to shove %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  if (is_friend(it)) {
    dbg("Not able to shove (same owner) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  if (same_mob(it)) {
    dbg("Not able to shove (same master) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  //
  // Sanity check we cannot shove more than one tile
  //
  if ((fabs(delta.x) > 1) || (fabs(delta.y) > 1)) {
    dbg("Not able to shove (too far) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  dbg("Can shove, %s delta %d,%d", it->to_short_string().c_str(), (int) delta.x, (int) delta.y);
  TRACE_AND_INDENT();

  move_finish();

  idle_count_set(0);

  bool was_dead = it->is_dead;
  auto old_at   = it->curr_at;

  //
  // If I'm on fire. set it on fire too!
  //
  if (on_fire_anim_id().ok()) {
    it->on_fire_set("I am on fire, set it on fire too");
  }

  //
  // Annoy the thing being pushed
  //
  if (it->is_alive_monst()) {
    it->add_enemy(this);
  }

  point shove_delta = delta;
  point shove_pos   = it->curr_at + shove_delta;

  if (force) {
    //
    // For example, shoving an block_of_ice with something it it, we need to bypass most checks.
    //
  } else {
    if (it->is_block_of_ice()) {
      //
      // Allow to shove regardless of size
      //
    } else {
      //
      // Stop shoving of much larger things
      //
      if (it->thing_size() - thing_size() > 1) {
        if (is_player()) {
          msg("%s is too large to be shoved!", it->text_The().c_str());
        } else if (it->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
      }
    }

    if (! it->is_brazier() && ! it->is_barrel() && ! it->is_block_of_ice()) {
      if (! it->shove_ok(shove_pos)) {
        if (is_player()) {
          msg("%s cannot be shoved! Something is in the way.", it->text_The().c_str());
        } else if (it->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
      }
    }

    if (! it->is_dead) {
      dbg("Shove: It strength %d vs me %d", it->stat_str(), stat_str());

      int its_strength = it->stat_str_total() + it->shove_strength_total();

      if (it->is_heavy()) {
        its_strength += 10;
      }

      if (it->is_very_heavy()) {
        its_strength += 10;
      }

      if (was_sleeping) {
        its_strength /= 4;
      }

      dbg("Shove: Its strength %d vs me %d", its_strength, stat_str());

      if (! d20roll(stat_str() + shove_strength_total(), its_strength)) {
        if (is_player()) {
          if (it->is_monst()) {
            if (it->is_able_to_shove()) {
              msg("%s shoves you back!", it->text_The().c_str());
            } else {
              msg("%s is resolute!", it->text_The().c_str());
            }
          } else {
            msg("%s refuses to budge!", it->text_The().c_str());
          }
        } else if (it->is_player()) {
          msg("%s fails to shove you!", text_The().c_str());
        }
        return THING_SHOVE_TRIED_AND_FAILED;
      }

      if (it->is_monst()) {
        if (! it->is_dead) {
          it->popup(string_sprintf("%%fg=orange$!"));
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
  if (! force && ! it->shove_ok(shove_pos)) {
    //
    // This is a failure to shove
    //
    if (it->is_brazier()) {
      if (! it->is_dead) {
        if (is_player()) {
          msg("The brazier falls back on you!");
        }
        it->move_to(curr_at);
      }
    } else if (it->is_barrel()) {
      if (is_player()) {
        msg("The barrel will not budge!");
      }
    } else if (it->is_block_of_ice()) {
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
      if (it->is_brazier()) {
        if (it->is_dead) {
          msg("You kick the brazier around. Why though?");
        } else {
          msg("You knock over %s!", it->text_the().c_str());
        }
      } else {
        if (it->is_dead) {
          msg("You kick %s!", it->text_the().c_str());
        } else {
          msg("You shove %s!", it->text_the().c_str());
        }
      }
    } else if (it->is_player()) {

      if (level->is_chasm(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the abyss, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the abyss!%%fg=reset$", text_The().c_str());
      } else if (level->is_lava(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the lava, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the red death!%%fg=reset$", text_The().c_str());
      } else if (level->is_deep_water(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the depths, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the depths!%%fg=reset$", text_The().c_str());
      } else if (level->is_water(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the puddle, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the puddle!%%fg=reset$", text_The().c_str());
      } else if (level->is_fire(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the flames, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the flames!%%fg=reset$", text_The().c_str());
      } else if (level->is_spiderweb(shove_pos)) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%%fg=red$%s tries to shove you into the web, but luckily you avoid it!%%fg=reset$",
                text_The().c_str());
          }
          return (THING_SHOVE_TRIED_AND_FAILED);
        }
        msg("%%fg=red$%s shoves you into the sticky web!%%fg=reset$", text_The().c_str());
      } else if (it->is_dead) {
        if (d20roll_under(stat_luck_total())) {
          if (is_player()) {
            msg("%s kicks your corpse for fun, but hurts itself!", text_The().c_str());
          }
        } else {
          msg("%s kicks your corpse for fun!", text_The().c_str());
        }
      } else {
        msg("%s shoves you!", text_The().c_str());
      }
    }

    it->move_to(shove_pos);
  }

  if (! it->is_dead) {
    if (it->is_dead_on_shove()) {
      dbg("Shove and defeat");
      it->dead("by being shoved");

      //
      // e.g. shoving a brazier creates a dead one
      //
      auto spawn_what = it->spawn_on_shoved();
      if (spawn_what != "") {
        auto spawn_at = it->curr_at;
        if (spawn_at.x > curr_at.x) {
          it->dir_set_left();
        } else {
          it->dir_set_right();
        }

        //
        // Must check at the new location
        //
        auto n = level->thing_new(spawn_what, spawn_at);
        n->location_check();
      }
    }
  }

  dbg("Handle location for shoved thing: %s", it->to_short_string().c_str());
  it->location_check();

  //
  // If shoving something on fire! set yourself on fire!
  //
  if (! was_dead) {
    if (it->is_fire()) {
      if (d20roll_under(stat_luck_total())) {
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
    if (it->is_shovable_and_sticky()) {
      FOR_ALL_NON_INTERNAL_THINGS(level, t, old_at.x, old_at.y)
      {
        if (t == this) {
          continue;
        }

        if (t == it) {
          continue;
        }

        if (! t->is_shovable()) {
          continue;
        }

        if (t->curr_at == it->curr_at) {
          continue;
        }
        try_to_shove(t, delta, true);
      }

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

  FOR_ALL_COLLISION_THINGS(level, it, future_pos.x, future_pos.y)
  {
    if (this == it) {
      continue;
    }

    //
    // Skip things we cannot collide with
    //
    if (it->is_falling || it->is_jumping || it->is_changing_level) {
      continue;
    }

    if (it->is_obs_for_shoving()) {
      return false;
    }
  }
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
  FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
  {
    if (this == it) {
      continue;
    }
    dbg("Shove candidate, %s", it->to_short_string().c_str());

    if (! it->is_shovable()) {
      continue;
    }

    if (! it->is_heavy()) {
      continue;
    }

    dbg("Shove heavy candidate, %s", it->to_short_string().c_str());
    point shove_delta = delta;
    return (try_to_shove(it, shove_delta));
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_THINGS_THAT_INTERACT(level, it, p.x, p.y)
  {
    if (this == it) {
      continue;
    }
    dbg("Shove candidate, %s", it->to_short_string().c_str());

    if (! it->is_shovable()) {
      continue;
    }

    dbg("Shove candidate, %s", it->to_short_string().c_str());
    point shove_delta = delta;
    return (try_to_shove(it, shove_delta));
  }
  FOR_ALL_THINGS_END()

  return (THING_SHOVE_NEVER_TRIED);
}

ThingShoved Thing::try_to_shove_into_hazard(Thingp it, point delta)
{
  if (is_able_to_shove()) {
    auto shoved_to_position = it->curr_at + delta;
    if (level->is_hazard((int) shoved_to_position.x, (int) shoved_to_position.y)) {
      return (try_to_shove(it, delta));
    }
  }
  return (THING_SHOVE_NEVER_TRIED);
}
