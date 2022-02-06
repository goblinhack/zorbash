//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

ThingShoved Thing::try_to_shove(Thingp it, point delta)
{
  TRACE_NO_INDENT();

  dbg("Try to shove, %s delta %d,%d", it->to_short_string().c_str(), (int) delta.x, (int) delta.y);
  TRACE_AND_INDENT();

  if (! is_able_to_shove()) {
    dbg("Not able to shove");
    return (THING_SHOVE_NEVER_TRIED);
  }

  //
  // Wake on shove
  //
  it->wake();

  if (! it->is_shovable()) {
    dbg("Not able to shove %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  auto my_owner  = get_top_owner();
  auto its_owner = it->get_top_owner();
  if (my_owner && (my_owner == its_owner)) {
    dbg("Not able to shove (same owner) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  auto my_mob  = get_top_mob();
  auto its_mob = it->get_top_mob();
  if (my_mob && (my_mob == its_mob)) {
    dbg("Not able to shove (same master) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  auto my_leader  = get_leader();
  auto its_leader = it->get_leader();
  if (my_leader && (my_leader == its_leader)) {
    dbg("Not able to shove (same leader) %s", it->to_short_string().c_str());
    return (THING_SHOVE_NEVER_TRIED);
  }

  auto my_spawned_owner  = get_top_spawned_owner();
  auto its_spawned_owner = it->get_top_spawned_owner();
  if (my_spawned_owner && (my_spawned_owner == its_spawned_owner)) {
    dbg("Not able to shove (same spawner) %s", it->to_short_string().c_str());
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

  set_idle_count(0);

  bool was_dead = it->is_dead;

  //
  // If I'm on fire. set it on fire too!
  //
  if (get_on_fire_anim_id().ok()) {
    it->set_on_fire("I am on fire, set it on fire too");
  }

  //
  // Annoy the thing being pushed
  //
  if (it->is_alive_monst()) {
    it->add_enemy(this);
  }

  point shove_delta = delta;
  point shove_pos   = it->curr_at + shove_delta;

  if (it->monst_size() - monst_size() > 1) {
    if (is_player()) {
      msg("%s is too large to be shoved!", it->text_The().c_str());
    } else if (it->is_player()) {
      msg("%s fails to shove you!", text_The().c_str());
    }
    return (THING_SHOVE_TRIED_AND_FAILED);
  }

  if (! it->is_brazier() && ! it->is_barrel()) {
    if (it->collision_check_only(shove_pos)) {
      if (is_player()) {
        msg("%s cannot be shoved!", it->text_The().c_str());
      } else if (it->is_player()) {
        msg("%s fails to shove you!", text_The().c_str());
      }
      return (THING_SHOVE_TRIED_AND_FAILED);
    }
  }

  if (! it->is_dead) {
    dbg("Shove: It strength %d vs me %d", it->get_stat_str(), get_stat_str());

    int its_strength = it->get_stat_str();
    if (it->is_heavy()) {
      its_strength += 4;
    }

    if (! d20roll(get_stat_str(), its_strength)) {
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
      return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (it->is_monst()) {
      if (! it->is_dead) {
        it->popup(string_sprintf("%%fg=orange$!"));
      }
    }
  }

  //
  // If pushed into a chasm, move the thing first and then
  // let it spawn dead things
  //
  dbg("Shove it");
  TRACE_AND_INDENT();

  if (it->collision_check_only(shove_pos)) {
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
        msg("%%fg=red$%s shoves you into the abyss!%%fg=reset$", text_The().c_str());
      } else if (level->is_lava(shove_pos)) {
        msg("%%fg=red$%s shoves you into the red death!%%fg=reset$", text_The().c_str());
      } else if (level->is_water(shove_pos)) {
        msg("%%fg=red$%s shoves you into the depths!%%fg=reset$", text_The().c_str());
      } else if (level->is_fire(shove_pos)) {
        msg("%%fg=red$%s shoves you into the flames!%%fg=reset$", text_The().c_str());
      } else if (level->is_spiderweb(shove_pos)) {
        msg("%%fg=red$%s shoves you into the sticky web!%%fg=reset$", text_The().c_str());
      } else if (it->is_dead) {
        msg("%s kicks your corpse for fun!", text_The().c_str());
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
      auto spawn_what = it->spawn_on_shoved();
      if (spawn_what != "") {
        auto spawn_at = it->curr_at;
        if (spawn_at.x > curr_at.x) {
          it->dir_set_left();
        } else {
          it->dir_set_right();
        }
        auto n = level->thing_new(spawn_what, spawn_at);
        n->location_check_forced();
      }
    }
  }

  dbg("Handle location for shoved thing: %s", it->to_short_string().c_str());
  it->location_check_forced();

  //
  // If shoving something on fire! set yourself on fire!
  //
  if (! was_dead) {
    if (it->is_fire()) {
      if (pcg_random_range(0, 100) < 5) {
        if (is_player()) {
          if (set_on_fire("set yourself on fire")) {
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

  return (THING_SHOVE_TRIED_AND_PASSED);
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
