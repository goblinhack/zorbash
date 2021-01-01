//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::chasm_tick (void)
{_
    if (get_immediate_owner()) {
        return false;
    }

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend || 
        is_waiting_to_fall || 
        is_jumping) { 
        return true;
    }

    if (is_floating()) {
        return false;
    }

    //
    // Things on the edge of a chasm fall in
    //
    if (is_lava() || is_water()) {
        if ((mid_at.x > 0) && 
            (mid_at.x < MAP_WIDTH - 1) && 
            (mid_at.y > 0) && 
            (mid_at.y < MAP_HEIGHT - 1)) {

            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (level->is_chasm(mid_at.x + dx, mid_at.y + dy)) {
                        log("Near a chasm");
                        fall(1, 1000);
                        return true;
                    }
                }
            }
        }
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        log("Over a chasm");
        fall(1, 750);
        return true;
    }

    return false;
}
