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

uint8_t Thing::is_less_preferred_terrain (point p)
{_
    int pref = 0;

    if (will_avoid(p)) {
        pref++;
    }

    int heat = level->heatmap(p);
    if (heat > 1) {
        if (is_fire_hater()) {
            int hate_how_much = is_fire_hater();
            pref += hate_how_much + heat;
        }
    }

    if (pref > DMAP_MAX_LESS_PREFERRED_TERRAIN) {
        pref = DMAP_MAX_LESS_PREFERRED_TERRAIN;
    }

    return (uint8_t) pref;
}

bool Thing::will_prefer_terrain (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_water_lover()) {
        if (it->is_water() || it->is_deep_water()) {
            return true;
        }
    }
    if (me->is_acid_lover()) {
        if (it->is_acid()) {
            return true;
        }
    }
    return false;
}
