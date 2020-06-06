//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::lava_tick (void)
{_
    if (is_fire_hater()) {
        if (level->is_lava(mid_at.x, mid_at.y)) {
            if (!level->is_smoke(mid_at.x, mid_at.y)) {
                if (is_player()) {
                    MINICON("Your feet burn!");
                }
                auto smoke = thing_new("smoke1", fpoint((int)mid_at.x, (int)mid_at.y));
                smoke->set_lifespan(4);
            }
        }
    }
}
