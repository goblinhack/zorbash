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

bool Thing::ascend_sewer_tick (void)
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
        return false;
    }

    if (get_immediate_owner()) {
        return false;
    }

    if (!is_able_to_change_levels()) {
        return false;
    }

    if (!level->is_ascend_sewer(mid_at.x, mid_at.y)) {
        return false;
    }

    if (get_tick() - get_tick_last_level_change() < 1) {
        return false;
    }

#if 0
    if (is_player()) {
        if (level->world_at.z & 1) {
            level->timestamp_fade_out_begin = time_get_time_ms_cached();
            is_waiting_to_ascend_sewer = true;
            return true;
        }
    } else {
        //
        // Not sure if monsts should do this as they crawl out of sewers
        //
        return false;
    }
#endif

    return false;
}

bool Thing::ascend_sewer (void)
{_
    return true;
}
