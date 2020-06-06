//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::water_tick (void)
{_
    if (is_water_hater()) {
        if (level->is_water(mid_at.x, mid_at.y)) {
            dead("killed by water");
            if (is_fire()) {
                auto owner = owner_get();
                if (owner) {
                    if (owner->is_player()) {
                        MINICON("%%fg=green$You quench the flames!%%fg=reset$");
                    }
                }
            }
            auto smoke = thing_new("smoke1", fpoint((int)mid_at.x, (int)mid_at.y));
            smoke->set_lifespan(4);
        }
    }
}
