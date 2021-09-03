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
#include "my_sdl.h"
#include "my_gl.h"

bool Thing::descend_sewer_tick (void)
{_
    if (!level->is_descend_sewer(mid_at.x, mid_at.y)) {
        return false;
    }

    if (is_player()) {
        dbg("Location check, descend sewer");
    }

#if 0
    if (get_tick() - get_tick_last_level_change() < 1) {
        if (is_player()) {
            dbg("Location check, descend sewer, no too soon");
        }
        return false;
    }
#endif

    if (is_player()) {
        if (level->world_at.z & 1) {
            dbg("Descending sewer");
            level->timestamp_fade_out_begin = time_get_time_ms_cached();
            level->fbo_light = sdl_fbo_save(FBO_FULLMAP_LIGHT);
            is_waiting_to_descend_sewer = true;
            move_finish();
            return true;
        }
    } else {
        //
        // Not sure if monsts should do this as they crawl out of sewers
        //
        dbg("Monst cannot descend sewer");
        return false;
    }

    dbg("Cannot descend sewer");
    return false;
}

bool Thing::descend_sewer (void)
{_
    dbg("Descend sewer");
    if (is_changing_level ||
        is_hidden ||
        is_falling ||
        is_waiting_to_fall ||
        is_waiting_to_ascend_dungeon ||
        is_waiting_to_ascend_sewer ||
        is_jumping) {
        dbg("Descend sewer, no");
        return false;
    }

    if (!monstp) {
        return false;
    }

    auto player = level->player;
    if (is_monst()) {
        if (player) {
            //
            // Don't descend if player is on the same level
            //
            return false;
        }
    }

    auto next_level = level->world_at + point3d(0, 0, 1);
    game->init_level(next_level);

    if (is_player()) {
        game->current_level = next_level;
    }

    dbg("Is trying to descend to the sewer");

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            TOPCON("The sewer is permanently blocked!");
        }
        return false;
    }

    int x = player->mid_at.x;
    int y = player->mid_at.y;

    if (is_player()) {
        game->level = l;
        TOPCON("You climb into the sewer. Why though?");
    }

    dbg("Move to next level sewer entrance");
    is_changing_level = true;

    level_change(l);
    set_tick_last_level_change(game->tick_current);
    move_to_immediately(fpoint(x, y));
    move_carried_items_immediately();
    if (is_player()) {
        l->player = this;
        l->scroll_map_to_player();
        l->update_new_level();
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

    if (is_player() && level->cursor) {
        level->cursor->move_to_immediately(mid_at);
    }

    is_changing_level = false;
    dbg("Moved to next level sewer");
    if (is_player()) {
        level->timestamp_fade_in_begin = time_get_time_ms_cached();
        level->update_new_level();

        if (game->robot_mode) {
            game->tick_begin("Begin exploring the new level");
        }
    }

    return true;
}
