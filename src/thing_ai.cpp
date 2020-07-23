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

void Thing::ai_get_next_hop (void)
{_
    log("AI");
_
    point start((int)mid_at.x, (int)mid_at.y);

    //
    // If on fire, try and put it out!
    //
    if (is_on_fire() && is_fire_hater()) {
        if (is_intelligent()) {
            if (ai_on_fire()) {
                return;
            }
        }
    }

    //
    // If somewhere bad, escape
    //
    if (is_less_preferred_terrain(start) >= DMAP_MAX_LESS_PREFERRED_TERRAIN) {
        log("on bad terrain, escape");
        if (ai_escape()) {
            return;
        }

        monstp->wander_target = point(0, 0);
        log("cannot escape, try to wander");
        if (ai_wander()) {
            return;
        }
    }

    //
    // If going somewhere, continue
    //
    if (monstp->wander_target != point(0, 0)) {
        if (random_range(0, 100) < 50) {
            log("try to continue wander");
            if (ai_wander()) {
                return;
            }
        }
    }

    //
    // Find the best goal to go to
    //
    if (ai_choose_goal()) {
        monstp->wander_target = point(0, 0);
        return;
    }

    //
    // If we get here we found no goal. Try to wander.
    //
    if (ai_wander()) {
        return;
    }

    //
    // Ok our attempted move is done. We failed.
    //
    is_tick_done = true;
    move_finish();
}
