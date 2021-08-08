//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"

void Thing::water_tick (void)
{_
    if (!level->is_water(mid_at.x, mid_at.y)) {
        return;
    }

    if (is_on_fire()) {
        unset_on_fire();

        auto owner = get_top_owner();
        if (owner) {
            if (owner->is_player()) {
                TOPCON("%%fg=green$You quench the flames!%%fg=reset$");
            }
        }

        auto smoke = level->thing_new("smoke", mid_at);
        smoke->set_lifespan(pcg_random_range(1, 10));
        return;
    }

    if (!hates_water()) {
        return;
    }

    dead("by a watery end");
    auto smoke = level->thing_new("smoke", mid_at);
    smoke->set_lifespan(pcg_random_range(1, 10));
}
