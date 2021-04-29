//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::acid_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_waiting_to_fall || 
        is_jumping) { 
        return;
    }

    if (!hates_acid()) {
        return;
    }

    if (!level->is_acid(mid_at.x, mid_at.y)) {
        return;
    }

    bool hit;

    log("Acid tick");

    //
    // Give the player a chance
    //
    if (!level->is_smoke(mid_at.x, mid_at.y)) {
        auto smoke = level->thing_new("smoke", mid_at);
        smoke->set_lifespan(random_range(1, 10));

        hit = ((int)random_range(0, 100) < 50);
    } else {
        hit = false;
    }

    if (hit) {
        FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_FLOOR2) {
            auto tpp = t->tp();
            if (!tpp->is_acid()) {
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
            TOPCON("Your shoes are dissolving!");
        }
    }
}
