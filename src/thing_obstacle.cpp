//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

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
        // Handle ghosts
        //
        if (is_able_to_walk_through_walls()) {
            if (t->is_wall() || t->is_corridor()) {
                continue;
            }
        }

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
