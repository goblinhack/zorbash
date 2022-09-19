//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <set>

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::ai_obstacle_for_me(point p)
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

      if (t->is_floor()) {
        continue;
      }

      //
      // "true" on collision
      //
      if (ai_obstacle(t)) {
        return true;
      }
    }
  }

  return false;
}

bool Tp::ai_obstacle_for_me(Levelp level, point p)
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

      if (t->is_floor()) {
        continue;
      }

      //
      // "true" on collision
      //
      if (ai_obstacle(t)) {
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
  auto p = point(it->curr_at.x, it->curr_at.y);

  if (it == this) {
    return false;
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating() || it->is_flying()) {
    if (is_floating() || is_flying()) {
      IF_DEBUG2 { dbg("Collision obstacle (flying): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  //
  // Stop ghosts piling on top of each other
  //
  if (it->is_ethereal()) {
    if (is_ethereal()) {
      IF_DEBUG2 { dbg("Collision obstacle (ethereal): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  //
  // Allow movement through open doors only
  //
  if (it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    if (! it->is_open) {
      IF_DEBUG2 { dbg("Collision obstacle (not open): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  if (it->is_obs_destructable()) {
    if (! it->is_open) {
      IF_DEBUG2 { dbg("Collision obstacle (not open and destructable): %s", it->to_short_string().c_str()); }
      return true;
    }
  }

  if (is_player()) {
    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
      IF_DEBUG2 { dbg("Collision obstacle (monst): %s", it->to_short_string().c_str()); }
      return true;
    }
  } else if (is_monst()) {
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
        // Too many monsts (including one corpse)
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
        // Too many monsts (including one corpse)
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
      if (! is_floating() && ! is_flying()) {
        IF_DEBUG2 { dbg("Collision obstacle (floating): %s", it->to_short_string().c_str()); }
        return true;
      }
    }

    //
    // So we wont walk into fire for example
    //
    if (is_disliked_by_me(it)) {
      IF_DEBUG2 { dbg("Collision obstacle (disliked): %s", it->to_short_string().c_str()); }
      return true;
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
    if (it->is_dead) {
      //
      // Allow passing over corpses
      //
      if (it->is_obstacle_when_dead()) {
        IF_DEBUG2 { dbg("Collision obstacle (as dead): %s", it->to_short_string().c_str()); }
        return true;
      }
    }
  }

  return false;
}

//
// Return TRUE if this is something that should block AI
//
bool Thing::ai_obstacle(Thingp it)
{
  if (it == this) {
    return false;
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  if (is_internal() || is_hidden || is_falling || is_jumping || is_changing_level) {
    return false;
  }

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it)) {
    return false;
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating() || it->is_flying()) {
    if (is_floating() || is_flying()) {
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  //
  // Stop ghosts piling on top of each other
  //
  if (it->is_ethereal()) {
    if (is_ethereal()) {
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  //
  // Stop entities piling on top of each other
  //
  if (it->is_able_to_walk_through_walls()) {
    if (is_able_to_walk_through_walls()) {
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
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

  if (it->is_brazier() || it->is_barrel() || it->is_block_of_ice() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    //
    // Dead/extinguished braziers
    //
    if (it->is_dead) {
      return false;
    }

    if (! it->is_open) {
      if (it->is_door()) {
        if (is_able_to_open_doors()) {
          if (keys()) {
            return false;
          }
        }
        if (is_able_to_break_down_doors()) {
          return false;
        }
      }
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (it->is_secret_door()) {
    auto dist = distance(it->curr_at, curr_at);
    if (dist > THING_AI_CAN_SEE_SECRET_DOOR_DIST) {
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
    return false;
  }

  if (! is_ethereal()) {
    //
    // This lets you skip around mobs to avoid ghosts
    //
    if (is_minion()) {
      if (it->is_mob()) {
        if (it == top_mob()) {
          // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
          return true;
        }
      }
    }
  }

  if (same_leader(it)) {
    // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
    return true;
  }

  if (is_monst() || (is_player() && game->robot_mode)) {
    if (it->is_chasm()) {
      if (! is_floating() && ! is_flying()) {
        // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
        return true;
      }
    }

    //
    // Do not include this check. It stops monsts seeing down a corridor
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
    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
      // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
      return true;
    }
  }

  if (it->is_monst()) {
    if (it->is_dead) {
      //
      // Allow passing over corpses
      //
      if (it->is_obstacle_when_dead()) {
        // log("%s is an AI obstacle line %d", it->to_short_string().c_str(), __LINE__);
        return true;
      }
    }
  }

  return false;
}

//
// Return TRUE if this is something that should block AI
//
bool Tp::ai_obstacle(Thingp it)
{
  //
  // Skip things we cannot collide with
  //
  if (it->is_internal() || it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  //
  // Allow cleaners to engulf/swallow attack
  //
  if (is_engulfer() && can_eat(it)) {
    return false;
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
  if (it->is_floating() || it->is_flying()) {
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

  if (it->is_brazier() || it->is_barrel() || it->is_block_of_ice() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    //
    // Dead/extinguished braziers
    //
    if (it->is_dead) {
      return false;
    }

    if (! it->is_open) {
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
      if (! is_floating() && ! is_flying()) {
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
      if (it->is_obstacle_when_dead()) {
        return true;
      }
    }
  }

  return false;
}
