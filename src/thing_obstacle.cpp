//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"

bool Thing::is_ai_obstacle_for_me (const point &p)
{_
    //
    // Avoid threats and treat them as obstacles
    //
    for (auto& t : get(level->all_thing_ptrs_at, p.x, p.y)) {
        if (!t) {
            continue;
        }

        if (t->is_the_grid) { continue; }

        //
        // "true" on collision
        //
        if (ai_obstacle(t)) {
            if (t->is_loggable_for_unimportant_stuff()) {
                log(" is an obstacle for me %s", t->to_string().c_str());
            }
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
    // Stop beholders piling on top of each other
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
    if (it->is_movement_blocking_hard()) {
        if (is_able_to_walk_through_walls()) {
            return false;
        }

        if (!it->is_open) {
            return true;
        }
    }

    if (it->is_movement_blocking_soft()) {
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
        if (level->is_corpse(p)) {
            if (level->is_monst(p) > 1) {
                return true;
            }
        } else {
            if (level->is_monst(p) > 0) {
                return true;
            }
        }

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
 
        if (will_avoid_threat(it)) {
            return true;
        }

        if (it->is_player()) {
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
    // Stop beholders piling on top of each other
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
    if (it->is_movement_blocking_hard()) {
        if (is_able_to_walk_through_walls()) {
            return false;
        }

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
 
        if (will_avoid_threat(it)) {
            return true;
        }
    }

    return false;
}

