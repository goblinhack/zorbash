//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::lava_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_jumping) { 
        return;
    }

    if (!is_fire_hater()) {
        return;
    }

    if (!level->is_lava(mid_at.x, mid_at.y)) {
        return;
    }

    bool hit = false;

    log("acid tick");

    //
    // Give the player a chance
    //
    if (!level->is_smoke(mid_at.x, mid_at.y)) {
        auto smoke = level->thing_new("smoke1", mid_at);
        smoke->set_lifespan(4);

        hit = ((int)random_range(0, 100) < 80);
    } else {
        hit = true;
    }

    if (hit) {
        FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_LAVA) {
            auto tpp = t->tp();
            if (!tpp->is_lava()) {
                continue;
            }
            is_hit_by(t, t->get_stats_attack());
            break;
        } FOR_ALL_THINGS_END()
    } else {
        if (is_player()) {
            MINICON("You stand on a sightly cooler rock in the lava!");
            MINICON("Your feet are warm and toasty!");
        }
    }
}
