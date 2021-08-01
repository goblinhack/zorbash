//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>

#include "my_sys.h"
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::dmap_modify_terrain_cost (point p, uint8_t *d)
{_
    int pref = *d;

    if (collision_obstacle(p)) {
        pref++;
    }

    if (is_hazardous_to_me(p)) {
        pref += DMAP_LESS_PREFERRED_TERRAIN;
    }

    std::vector<std::pair<Thingp, int> > possible;

    static const std::vector<point> all_deltas = {
        point(-1, -1),
        point( 1, -1),
        point(-1,  1),
        point( 1,  1),
        point(0, 0),
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    for (const auto& d : all_deltas) {
        auto x = p.x + d.x;
        auto y = p.y + d.y;

        FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, MAP_DEPTH_OBJ) {
            auto tpp = t->tp();
            if (!tpp->is_monst()) {
                continue;
            }

            if (t->is_dead) {
                continue;
            }

            if (will_avoid_threat(point(x, y))) {
                pref += t->get_health_max();
            }

            if (is_dangerous(t)) {
                pref += DMAP_LESS_PREFERRED_TERRAIN;
            }

        } FOR_ALL_THINGS_END()
    }

    if (pref > DMAP_MAX_LESS_PREFERRED_TERRAIN) {
        pref = DMAP_MAX_LESS_PREFERRED_TERRAIN;
    }

    *d = (uint8_t) pref;
}

uint8_t Thing::get_terrain_cost (point p)
{_
    uint8_t pref = 0;

    dmap_modify_terrain_cost(p, &pref);

    return (uint8_t) pref;
}

bool Thing::will_prefer_terrain (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_water_lover()) {
        if (it->is_shallow_water() || it->is_deep_water()) {
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
