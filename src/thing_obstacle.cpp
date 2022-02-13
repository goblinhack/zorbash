//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::ai_obstacle_for_me(point p)
{
  TRACE_NO_INDENT();

  //
  // Avoid threats and treat them as obstacles
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto &t : get(level->all_things_ptr_at[ group ], p.x, p.y)) {
      if (unlikely(! t)) {
        continue;
      }

      if (t->is_the_grid) {
        continue;
      }
      if (t->is_floor()) {
        continue;
      }
      if (t->is_hidden) {
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
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto &t : get(level->all_things_ptr_at[ group ], p.x, p.y)) {
      if (unlikely(! t)) {
        continue;
      }

      if (t->is_the_grid) {
        continue;
      }
      if (t->is_floor()) {
        continue;
      }
      if (t->is_hidden) {
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
  if (it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
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
  // Allow movement through open doors only
  //
  if (it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    if (! it->is_open) {
      return true;
    }
  }

  if (it->is_obs_destructable()) {
    if (! it->is_open) {
      return true;
    }
  }

  if (is_player()) {
    if (it->is_alive_monst()) {
      //
      // Ignore is_ethereal to make it easier to attack ghosts
      //
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
        return true;
      }
      if (monst_count == 2) {
        if (it->is_alive_monst() && ! it->is_ethereal()) {
          //
          // Cannot pass through
          //
          return true;
        }
      }
    } else {
      if (monst_count > 1) {
        //
        // Too many monsts (including one corpse)
        //
        return true;
      }
      if (monst_count == 1) {
        if (it->is_alive_monst() && ! it->is_ethereal()) {
          //
          // Cannot pass through
          //
          return true;
        }
      }
    }

    if (it->is_chasm()) {
      if (! is_floating() && ! is_flying()) {
        return true;
      }
    }

    //
    // So we wont walk into fire for example
    //
    if (is_disliked_by_me(it)) {
      return true;
    }

    if (it->is_monst() || it->is_player()) {
      //
      // Allow cleaners to engulf/swallow attack
      //
      if (is_engulfer()) {
        return false;
      }

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
  if (it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
    return false;
  }

  if (is_hidden || is_falling || is_jumping || is_changing_level) {
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
  if (is_disliked_by_me(it->curr_at)) {
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

  if (it->is_brazier() || it->is_barrel() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
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
      return true;
    }
  }

  if (it->is_secret_door()) {
    auto dist = distance(it->curr_at, curr_at);
    if (dist > THING_AI_CAN_SEE_SECRET_DOOR_DIST) {
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
          return true;
        }
      }
    }
  }

  if (same_leader(it)) {
    return true;
  }

  if (is_monst() || (is_player() && game->robot_mode)) {
    if (it->is_chasm()) {
      if (! is_floating() && ! is_flying()) {
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

//
// Return TRUE if this is something that should block AI
//
bool Tp::ai_obstacle(Thingp it)
{
  //
  // Skip things we cannot collide with
  //
  if (it->is_hidden || it->is_falling || it->is_jumping || it->is_changing_level) {
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

  if (it->is_brazier() || it->is_barrel() || it->is_obs_wall_or_door()) {
    if (is_able_to_walk_through_walls()) {
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
