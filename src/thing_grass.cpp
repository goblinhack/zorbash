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
#include "my_globals.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

void Thing::grass_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_waiting_to_fall || 
        is_the_grid || 
        is_jumping) { 
        return;
    }

    if (!level->is_dry_grass(mid_at.x, mid_at.y)) {
        return;
    }

    if (!is_alive_monst() && !is_player()) {
        return;
    }

    if (is_ethereal()) {
        return;
    }

    if (is_floating()) {
        return;
    }

    FOR_ALL_THINGS_AT_DEPTH(level, t, mid_at.x, mid_at.y, MAP_DEPTH_FLOOR2) {
        auto tpp = t->tp();
        if (!tpp->is_dry_grass()) {
            continue;
        }

        if (tpp->name() != "dry_grass") {
            return;
        }

        t->dead("trampled");
        level->thing_new("dry_grass_trampled", t->mid_at);

    } FOR_ALL_THINGS_END()
}
