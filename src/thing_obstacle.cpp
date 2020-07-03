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

        //
        // "true" on collision
        //
        if (collision_obstacle(t)) {
            return (true);
        }
    }

    return (false);
}
