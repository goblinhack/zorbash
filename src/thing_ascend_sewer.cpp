//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"

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

    if (level->world_at.z > 1) {
        if (is_player()) {
            level->timestamp_fade_out_begin = time_get_time_ms_cached();
            is_waiting_to_ascend_sewer = true;
            return true;
        } else {
            return ascend_sewer();
        }
    }

    return false;
}

bool Thing::ascend_sewer (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_fall || 
        is_jumping) { 
        return false;
    }

    if (!monstp) {
        return false;
    }

    //
    // No level change if too rapid
    //
    if (get_tick() - get_tick_last_level_change() <= 1) {
        return false;
    }

    auto next_level = level->world_at + point3d(0, 0, -1);
    game->init_level(next_level);

    if (is_player()) {
        game->current_level = next_level;
    }

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            TOPCON("The entrance is permanently blocked!");
        }
        return false;
    }

    int x = mid_at.x;
    int y = mid_at.y;

    if (is_player()) {
        game->level = l;
        TOPCON("You ascend out of the muck");
    }

    log("Move to previous level exit");
    is_changing_level = true;

    level_change(l);
    set_tick_last_level_change(get_tick());
    move_to_immediately(fpoint(x, y));
    move_carried_items_immediately();
    if (is_player()) {
        l->player = this;
        l->scroll_map_to_player();
        l->update();
        //
        // Make sure all monsts on the new level are at the
        // same tick or they will get lots of free attacks
        //
        l->update_all_ticks();
    }

    move_finish();
    set_interpolated_mid_at(mid_at);
    update_interpolated_position();
    location_check();
    update_light();

    if (is_player()) {
        level->cursor->move_to_immediately(mid_at);
    }

    is_changing_level = false;
    log("Moved to previous level exit");
    if (is_player()) {
        level->timestamp_fade_in_begin = time_get_time_ms_cached();
        level->update();
    }
    return true;
}
