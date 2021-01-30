//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"

void Thing::water_tick (void)
{_
    if (avoids_water()) {
        if (level->is_shallow_water(mid_at.x, mid_at.y)) {
            dead("a watery end");
            if (is_fire()) {
                auto owner = get_top_owner();
                if (owner) {
                    if (owner->is_player()) {
                        MINICON("%%fg=green$You quench the flames!%%fg=reset$");
                    }
                }
            }
            auto smoke = level->thing_new("smoke", mid_at);
            smoke->set_lifespan(random_range(1, 10));
        }
    }
}
