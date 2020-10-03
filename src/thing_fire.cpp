//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::fire_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend || 
        is_waiting_to_fall || 
        is_jumping) { 
        return;
    }

    if (!is_on_fire()) {
        return;
    }

    //
    // Give the player a chance
    //
    bool hit = false;
    if (!level->is_smoke(mid_at.x, mid_at.y)) {
        auto smoke = level->thing_new("smoke1", mid_at);
        smoke->set_lifespan(4);

        hit = ((int)random_range(0, 100) < 20);
    } else {
        hit = false;
    }

    if (hit) {
        auto fire = tp_find("fire");
        auto damage = fire->get_stats_attack();

        if (is_fire_hater()) {
            damage *= 2;
        }

        auto h = decr_stats_health(damage);
        if (is_player()) {
            MINICON("%%fg=red$You take %u burn damage!%%fg=reset$", damage);
        }

        if (h <= 0) {
            h = set_stats_health(0);
            dead("burned to death");
        }
    }
}
