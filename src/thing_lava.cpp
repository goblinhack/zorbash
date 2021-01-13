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

void Thing::lava_tick (void)
{_
    if (g_opt_debug3) {
        log("Lava tick");
    }

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend || 
        is_waiting_to_fall || 
        is_jumping) { 
        if (g_opt_debug3) {
            log("No, not relevent");
        }
        return;
    }

    if (!is_fire_avoider()) {
        if (g_opt_debug3) {
            log("No, not a fire hater");
        }
        return;
    }

    fpoint at = get_interpolated_mid_at();
    if (!level->is_lava(at.x, at.y)) {
        if (g_opt_debug3) {
            log("No, no lava");
        }
        return;
    }

    bool hit = false;

    log("Lava tick");

    //
    // Give the player a chance
    //
    if (!level->is_smoke(at.x, at.y)) {
        hit = ((int)random_range(0, 100) < 80);
    } else {
        hit = true;
    }

    if (is_on_fire()) {
        hit = true;
    }

    if (hit) {
        FOR_ALL_THINGS_AT_DEPTH(level, t, at.x, at.y, MAP_DEPTH_LAVA) {
            auto tpp = t->tp();
            if (!tpp->is_lava()) {
                continue;
            }
            if (t->get_tick() < game->tick_current) {
                t->set_tick(game->tick_current);
                is_hit_by(t, t->get_damage_melee());
                break;
            }
        } FOR_ALL_THINGS_END()
    } else {
        if (is_player()) {
            MINICON("You stand on a sightly cooler rock in the lava!");
            MINICON("Your feet are warm and toasty!");
        }
    }

    if (!level->is_smoke(at.x, at.y)) {
        auto smoke = level->thing_new("smoke1", at);
        smoke->set_lifespan(random_range(1, 10));
    }
}
