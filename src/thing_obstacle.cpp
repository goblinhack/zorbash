//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"

bool Thing::ai_obstacle_for_me (const point &p)
{_
  //
  // Avoid threats and treat them as obstacles
  //
  for (auto& t : get(level->all_things_ptr_at[THING_GROUP_ALL], p.x, p.y)) {
    if (!t) {
      continue;
    }

    if (t->is_the_grid) { continue; }

    //
    // "true" on collision
    //
    if (ai_obstacle(t)) {
      return true;
    }
  }

  return false;
}

//
// Return TRUE if this is something that should physically block
//
bool Thing::collision_obstacle (Thingp it)
{
  auto p = point(it->mid_at.x, it->mid_at.y);

  if (it == this) {
    return false;
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_hidden ||
    it->is_falling ||
    it->is_jumping ||
    it->is_changing_level) {
    return false;
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating()) {
    if (is_floating()) {
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
  if (it->is_movement_blocking_wall_or_locked_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    if (!it->is_open) {
      return true;
    }
  }

  if (it->is_movement_blocking_but_destructable()) {
    if (!it->is_open) {
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
      if (!it->is_engulfer()) {
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
        if (it->is_alive_monst() && !it->is_ethereal()) {
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
        if (it->is_alive_monst() && !it->is_ethereal()) {
          //
          // Cannot pass through
          //
          return true;
        }
      }
    }

    if (it->is_chasm()) {
      if (!is_floating()) {
        return true;
      }
    }

    if (will_avoid_hazard(it)) {
      return true;
    }

    if (it->is_player()) {
      //
      // Allow cleaners to engulf/swallow attack
      //
      if (is_engulfer()) {
        return false;
      }

      return true;
    }
  }

  return false;
}

//
// Return TRUE if this is something that should block AI
//
bool Thing::ai_obstacle (Thingp it)
{
  if (it == this) {
    return false;
  }

  //
  // Skip things we cannot collide with
  //
  if (it->is_hidden ||
    it->is_falling ||
    it->is_jumping ||
    it->is_changing_level) {
    return false;
  }

  //
  // Lava, acid etc...
  //
  if (is_hazardous_to_me(make_point(it->mid_at))) {
    return true;
  }

  //
  // Stop tentacleyes piling on top of each other
  //
  if (it->is_floating()) {
    if (is_floating()) {
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
  if (it->is_brazier() ||
    it->is_barrel() ||
    it->is_movement_blocking_wall_or_locked_door()) {
    if (is_able_to_walk_through_walls()) {
      return false;
    }

    if (!it->is_open) {
      return true;
    }
  }

  if (is_monst() || (is_player() && game->robot_mode)) {
    if (it->is_chasm()) {
      if (!is_floating()) {
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

  return false;
}
