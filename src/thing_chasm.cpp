//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
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
    if (g_opt_debug3) {
        log("Chasm tick");
    }

    auto immediate_owner = get_immediate_owner();
    if (immediate_owner) {
        if (g_opt_debug3) {
            log("No, has owner %s", immediate_owner->to_string().c_str());
        }
        return false;
    }

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend_to_next_level || 
        is_waiting_to_descend_to_sewer || 
        is_waiting_to_fall || 
        is_chasm() || 
        is_the_grid || 
        is_jumping) { 
        if (g_opt_debug3) {
            log("No, not relevent");
        }
        return true;
    }

    if (is_floating()) {
        if (g_opt_debug3) {
            log("No, is floating");
        }
        return false;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        log("Over a chasm");
        fall(1, 750);
        return true;
    }

    return false;
}
