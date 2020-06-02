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

uint8_t Thing::is_less_preferred_terrain (point p) const
{_
    int pref = 0;

    if (level->is_water(p)) {
        if (is_water_hater()) {
            pref += is_water_hater();
        }
    }

    int heat = level->heatmap(p);
    if (heat) {
        int hate_how_much = is_fire_hater();
        if (is_fire_hater()) {
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

    if (me->is_water_dweller()) {
        if (it->is_water() || it->is_deep_water()) {
            return (true);
        }
    }
    return (false);
}
