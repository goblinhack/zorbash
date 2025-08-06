//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::is_obs_ai_for_me(point p)
{
  TRACE_NO_INDENT();

  //
  // Avoid threats and treat them as obstacles
  //
  {
    for (auto &t : get(level->all_things_ptr_at, p.x, p.y)) {
      if (unlikely(! t)) {
        continue;
      }

      if (t->is_hidden || t->is_internal()) {
        continue;
      }

      if (t->is_floor() || t->is_corridor()) {
        continue;
      }

      //
      // "true" on collision
      //
      if (is_obs_ai(t)) {
        return true;
      }
    }
  }

  return false;
}

bool Tp::is_obs_ai_for_me(Levelp level, point p)
{
  TRACE_NO_INDENT();

  //
  // Avoid threats and treat them as obstacles
  //
  {
    for (auto &t : get(level->all_things_ptr_at, p.x, p.y)) {
      if (unlikely(! t)) {
        continue;
      }

      if (t->is_hidden || t->is_internal()) {
        continue;
      }

      if (t->is_floor() || t->is_corridor()) {
        continue;
      }

      //
      // "true" on collision
      //
      if (is_obs_ai(t)) {
        return true;
      }
    }
  }

  return false;
}

//
// Return TRUE if this is something that should physically block
//
bool Thing::collision_obstacle(Thingp it)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, it);

  auto p = point(it->curr_at.x, it->curr_at.y);

  TRACE_NO_INDENT();
  if (it == this) {
    return false;
  }

  if (! level) {
    err("No level for thing?");
    return false;
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  //
  // Limit krakens to the depths, but allow eels and piranha_giants free roam.
  //
  if (is_swimmer()) {
    TRACE_NO_INDENT();
    if (environ_likes_deep_water() && environ_likes_shallow_water()) {
      if (! level->is_water(it->curr_at)) {
        return true;
      }
    } else if (environ_likes_deep_water()) {
      if (! level->is_deep_water(it->curr_at)) {
        return true;
      }
    } else if (environ_likes_shallow_water()) {
      if (! level->is_shallow_water(it->curr_at)) {
        if (! is_able_to_live_out_of_water()) {
          return true;
        }
      }
    } else {
      if (! level->is_water(it->curr_at)) {
        return true;
      }
    }
  }

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it)) {
    TRACE_NO_INDENT();
    if (it->thing_size() > thing_size()) {
      return false;
    }
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating_currently() || it->is_flying()) {
    TRACE_NO_INDENT();
    if (is_floating_currently() || is_flying()) {
      IF_DEBUG2 { dbg("Collision obstacle (flying): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  //
  // Stop ghosts piling on top of each other
  //
  if (it->is_ethereal()) {
    TRACE_NO_INDENT();
    if (is_ethereal()) {
      IF_DEBUG2 { dbg("Collision obstacle (ethereal): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  //
  // Allow movement through open doors only
  //
  if (it->is_obs_wall_or_door()) {
    TRACE_NO_INDENT();
    if (! is_able_to_walk_through_walls()) {
      if (! it->is_open && ! it->is_dead) {
        IF_DEBUG2 { dbg("Collision obstacle (not open): %s", it->to_short_string().c_str()); }
        return true;
      }
    }
  }

  if (it->is_obs_destructable()) {
    TRACE_NO_INDENT();
    if (! it->is_open && ! it->is_dead) {
      IF_DEBUG2 { dbg("Collision obstacle (not open and destructable): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  if (is_player()) {
    TRACE_NO_INDENT();

    //
    // Allow the player to walk through pets without attacking
    //
    auto l = it->leader();
    if (l && (l == this)) {
      IF_DEBUG2 { dbg("Collision obstacle (pet): %s", it->to_short_string().c_str()); }
      return false;
    }

    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
      IF_DEBUG2 { dbg("Collision obstacle (monst): %s", it->to_short_string().c_str()); }
      return true;
    }
  } else if (is_monst()) {
    TRACE_NO_INDENT();
    auto monst_count = level->is_monst(p);

    //
    // Allow cleaners to engulf/swallow attack
    //
    if (is_engulfer()) {
      if (! it->is_engulfer()) {
        return false;
      }
    }

    if (level->is_corpse(p)) {
      if (monst_count > 2) {
        //
        // Too many monsters (including one corpse)
        //
        IF_DEBUG2 { dbg("Collision obstacle (too many monst + corpse): %s", it->to_short_string().c_str()); }
        return true;
      }
      if (monst_count == 2) {
        if (it->is_alive_monst() && ! it->is_ethereal()) {
          //
          // Cannot pass through
          //
          IF_DEBUG2
          {
            dbg("Collision obstacle (too many non ethereal monst + corpse): %s", it->to_short_string().c_str());
          }
          return true;
        }
      }
    } else {
      if (monst_count > 1) {
        //
        // Too many monsters (including one corpse)
        //
        IF_DEBUG2 { dbg("Collision obstacle (too many monst): %s", it->to_short_string().c_str()); }
        return true;
      }
      if (monst_count == 1) {
        if (it->is_alive_monst() && ! it->is_ethereal()) {
          //
          // Cannot pass through
          //
          IF_DEBUG2 { dbg("Collision obstacle (corpse): %s", it->to_short_string().c_str()); }
          return true;
        }
      }
    }

    if (it->is_chasm()) {
      if (confused_count() || entranced_count()) {
        //
        // Walk onto the lava when confused. Is this too cruel?
        //
      } else if (is_floating_currently() || is_flying()) {
        //
        // Can fly over chasms
        //
      } else {
        IF_DEBUG2 { dbg("Collision obstacle (chasm): %s", it->to_short_string().c_str()); }
        return true;
      }
    }

    //
    // So we wont walk into fire for example
    //
    if (is_disliked_by_me(it)) {
      if (confused_count() || entranced_count()) {
        //
        // Walk onto the lava when confused. Is this too cruel?
        //
      } else {
        //
        // Avoid walking onto lava
        //
        IF_DEBUG2 { dbg("Collision obstacle (disliked): %s", it->to_short_string().c_str()); }
        return true;
      }
    }

    if (it->is_monst() || it->is_player()) {
      //
      // Allow cleaners to engulf/swallow attack
      //
      if (is_engulfer()) {
        return false;
      }

      IF_DEBUG2 { dbg("Collision obstacle (monst or player): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  if (it->is_monst()) {
    TRACE_NO_INDENT();
    if (it->is_dead) {
      //
      // Allow passing over corpses
      //
      if (it->is_obs_when_dead()) {
        IF_DEBUG2 { dbg("Collision obstacle (as dead): %s", it->to_short_string().c_str()); }
        return true;
      }
    }
  }

  if (is_friend(it)) {
    if (debug && is_debug_type()) {
      IF_DEBUG2 { dbg("Collision obstacle (friend): %s", it->to_short_string().c_str()); }
    }
    return true;
  }

  return false;
}

//
// Return TRUE if this is something that should block AI
//
bool Thing::is_obs_ai(Thingp it)
{
  const bool debug = false;

  if (it == this) {
    return false;
  }

  if (debug && is_debug_type()) {
    con("check collision with %s", it->to_string().c_str());
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    if (debug && is_debug_type()) {
      con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
    }
    return false;
  }

  if (is_internal() || is_hidden || is_falling || is_jumping || is_changing_level) {
    if (debug && is_debug_type()) {
      con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
    }
    return false;
  }

  //
  // Intelligent monsters avoid traps
  //
  if (is_intelligent()) {
    if (! is_player()) {
      if (level->is_trap(it->curr_at)) {
        if (debug && is_debug_type()) {
          con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    }
  }

  //
  // Limit krakens to the depths, but allow eels and piranha_giants free roam.
  //
  if (is_swimmer()) {
    if (environ_likes_deep_water() && environ_likes_shallow_water()) {
      if (! level->is_water(it->curr_at)) {
        if (debug && is_debug_type()) {
          con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    } else if (environ_likes_deep_water()) {
      if (! level->is_deep_water(it->curr_at)) {
        if (debug && is_debug_type()) {
          con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    } else if (environ_likes_shallow_water()) {
      if (! level->is_shallow_water(it->curr_at)) {
        if (! is_able_to_live_out_of_water()) {
          if (debug && is_debug_type()) {
            con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
          }
          return true;
        }
      }
    } else {
      if (! level->is_water(it->curr_at)) {
        if (debug && is_debug_type()) {
          con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    }
  }

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it)) {
    if (it->thing_size() > thing_size()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating_currently() || it->is_flying()) {
    if (is_floating_currently() || is_flying()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  //
  // Stop ghosts piling on top of each other
  //
  if (it->is_ethereal()) {
    if (is_ethereal()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  //
  // Stop entities piling on top of each other
  //
  if (it->is_able_to_walk_through_walls()) {
    if (is_able_to_walk_through_walls()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  //
  // Allow movement through open doors only
  //
  if (it->is_able_to_see_through_doors()) {
    if (it->is_door()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
      }
      return false;
    }
  }

  if (it->is_totem() || it->is_turret() || it->is_brazier() || it->is_barrel() || it->is_block_of_ice()
      || it->is_block_of_crystal() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      if (debug && is_debug_type()) {
        con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
      }
      return false;
    }

    //
    // Dead/extinguished braziers cause no collision
    //
    if (it->is_dead) {
      if (debug && is_debug_type()) {
        con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
      }
      return false;
    }

    //
    // Check for open doors. Ignore dead/broken doors.
    //
    if (! it->is_open && ! it->is_dead) {
      if (it->is_door()) {
        if (is_able_to_open_doors()) {
          if (keys()) {
            if (debug && is_debug_type()) {
              con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
            }
            return false;
          }
        }
        if (is_able_to_break_down_doors()) {
          if (debug && is_debug_type()) {
            con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
          }
          return false;
        }
      }
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }

    //
    // Stops the robot trying to walk through a brazier; which if there is something in
    // the way of the brazier, like a mob or a wall, then it gets stuck.
    //
    return true;
  }

  if (it->is_secret_door()) {
    auto dist = distance(it->curr_at, curr_at);
    if (dist > THING_AI_CAN_SEE_SECRET_DOOR_DIST) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
    if (debug && is_debug_type()) {
      con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
    }
    return false;
  }

  auto m = it->top_mob();
  if ((is_monst() || is_player()) && it->is_ethereal() && m && (m == this)) {
    //
    // This is to allow the player to walk through their own spectral blades when spawned
    // due to multiplicity.
    //
    if (debug && is_debug_type()) {
      con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
    }
  } else if (is_ethereal()) {
    //
    // This lets you skip around mobs to avoid ghosts
    //
    if (debug && is_debug_type()) {
      con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
    }
  } else {
    //
    // No walking through your fellow minions
    //
    if (same_mob(it)) {
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  if (is_monst() || (is_player() && game->robot_mode)) {
    if (it->is_chasm()) {
      if (confused_count() || entranced_count()) {
        //
        // Walk onto the lava when confused. Is this too cruel?
        //
      } else if (is_floating_currently() || is_flying()) {
        //
        // Can fly over chasms
        //
      } else {
        if (debug && is_debug_type()) {
          con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    }

    //
    // Do not include this check. It stops monsters seeing down a corridor
    // with a monst already in it
    //
    // if (it->is_alive_monst()) {
    //     return true;
    // }

    //
    // Don't include this, it means a monst will not attack a threat as
    // it effectively is not allowed to see it as we consider it like a
    // hard obstacle
    //
    // if (will_avoid_threat(it)) {
    //     return true;
    // }
  } else if (is_player()) {
    //
    // Allow the player to walk through pets without attacking
    //
    auto l = it->leader();
    if (l && (l == level->player)) {
      if (debug && is_debug_type()) {
        con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
      }
      return false;
    }

    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
      if (debug && is_debug_type()) {
        con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
      }
      return true;
    }
  }

  if (it->is_monst()) {
    if (it->is_dead) {
      //
      // Allow passing over corpses
      //
      if (it->is_obs_when_dead()) {
        if (debug && is_debug_type()) {
          con("check collision with %s, yes at line %d", it->to_string().c_str(), __LINE__);
        }
        return true;
      }
    }
  }

  if (debug && is_debug_type()) {
    con("check collision with %s, no at line %d", it->to_string().c_str(), __LINE__);
  }

  return false;
}

//
// Return TRUE if this is something that should block AI
//
bool Tp::is_obs_ai(Thingp it)
{
  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  //
  // Intelligent monsters avoid traps
  //
  if (is_intelligent()) {
    if (! is_player()) {
      if (it->is_trap()) {
        return true;
      }
    }
  }

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it)) {
    if (it->thing_size() > thing_size()) {
      return true;
    }
  }

  //
  // Lava, acid etc...
  //
  if (is_disliked_by_me(it->level, it->curr_at)) {
    return true;
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating_currently() || it->is_flying()) {
    if (is_floating() || is_flying()) {
      return true;
    }
  }

  //
  // Stop ghosts piling on top of each other
  //
  if (it->is_ethereal()) {
    if (is_ethereal()) {
      return true;
    }
  }

  //
  // Stop entities piling on top of each other
  //
  if (it->is_able_to_walk_through_walls()) {
    if (is_able_to_walk_through_walls()) {
      return true;
    }
  }

  //
  // Allow movement through open doors only
  //
  if (it->is_able_to_see_through_doors()) {
    if (it->is_door()) {
      return false;
    }
  }

  if (it->is_spell_of_holding_barrier()) {
    if (! is_immune_to_spell_of_holding()) {
      return true;
    }
  }

  if (is_monst()) {
    if (it->is_spell_of_sanctuary_barrier()) {
      if (! is_immune_to_spell_of_sanctuary()) {
        return true;
      }
    }
  }

  if (it->is_totem() || it->is_turret() || it->is_brazier() || it->is_barrel() || it->is_portal()
      || it->is_block_of_ice() || it->is_block_of_crystal() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    //
    // Dead/extinguished braziers
    //
    if (it->is_dead) {
      return false;
    }

    if (! it->is_open && ! it->is_dead) {
      if (it->is_door()) {
        if (is_able_to_open_doors()) {
          return false;
        }
        if (is_able_to_break_down_doors()) {
          return false;
        }
      }
      return true;
    }
  }

  if (it->is_secret_door()) {
    return false;
  }

  if (! is_ethereal()) {
    //
    // This lets you skip around mobs to avoid ghosts
    //
    if (is_minion()) {
      if (it->is_mob()) {
        return true;
      }
    }
  }

  if (is_monst() || (is_player() && game->robot_mode)) {
    if (it->is_chasm()) {
      if (is_floating() || is_flying()) {
        //
        // Can fly over chasms
        //
      } else {
        return true;
      }
    }
  } else if (is_player()) {
    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
      return true;
    }
  }

  if (it->is_monst()) {
    if (it->is_dead) {
      //
      // Allow passing over corpses
      //
      if (it->is_obs_when_dead()) {
        return true;
      }
    }
  }

  return false;
}
