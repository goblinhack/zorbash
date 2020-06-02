//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

bool Thing::is_obstacle_for_me (const point &p)
{_
    //
    // Avoid threats and treat them as obstacles
    //
    for (auto& t : get(level->all_thing_ptrs_at, p.x, p.y)) {
        if (!t) {
            continue;
        }
        if (t->is_dead) {
            continue;
        }
        if (t->is_wall()) {
            return (true);
        }
        if (t->is_rock()) {
            return (true);
        }
        if (t->is_door()) {
            return (true);
        }
        if (t->is_movement_blocking()) {
            return (true);
        }
        if (t->is_hazard()) {
            return (true);
        }
        if (t == this) {
            continue;
        }
        if (t->is_hidden) {
            continue;
        }

        //
        // Do not include this check. It stops monsts seeing down a corridor
        // with a monst already in it
        //
        // if (t->is_alive_monst()) {
        //   return (true);
        // }
        //

        if (will_avoid(t)) {
            return (true);
        }
    }

    return (false);
}
