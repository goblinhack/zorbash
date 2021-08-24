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

bool Thing::descend_dungeon_tick (void)
{_
    if (!is_able_to_change_levels()) {
        return false;
    }

    if (!level->is_descend_dungeon(mid_at.x, mid_at.y)) {
        return false;
    }

    if (is_player()) {
        dbg("Location check, descend");
    }

#if 0
    if (get_tick() - get_tick_last_level_change() < 1) {
        if (is_player()) {
            dbg("Location check, descend, no too soon");
        }
        return false;
    }
#endif

    if (is_player()) {
        level->timestamp_fade_out_begin = time_get_time_ms_cached();
        level->fbo_light = sdl_fbo_save(FBO_FULLMAP_LIGHT);
        is_waiting_to_descend_dungeon = true;
        return true;
    } else {
        return descend_dungeon();
    }
}

bool Thing::descend_dungeon (void)
{_
    dbg("Descend dungeon");
    if (is_changing_level ||
        is_hidden ||
        is_falling ||
        is_waiting_to_ascend_dungeon ||
        is_waiting_to_descend_sewer ||
        is_waiting_to_fall ||
        is_jumping) {
        dbg("Descend dungeon, no");
        return false;
    }

    if (!monstp) {
        return false;
    }

    if (is_monst()) {
        if (level->player) {
            //
            // Don't descend if player is on the same level
            //
            return false;
        }
    }

    auto next_level = level->world_at + point3d(0, 0, 2);
    game->init_level(next_level);

    if (is_player()) {
        game->current_level = next_level;
    }

    dbg("Is trying to descend");

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            TOPCON("The exit is permanently blocked!");
        }
        return false;
    }

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_ascend_dungeon(x, y)) {
                if (is_player()) {
                    game->level = l;
                    TOPCON("You bravely descend.");
                }

                dbg("Move to next level entrance");
                is_changing_level = true;

                dbg("Level change");
                level_change(l);
                set_tick_last_level_change(game->tick_current);

                dbg("Level change move to destination");
                move_to_immediately(fpoint(x, y));

                dbg("Level change move carried items");
                move_carried_items_immediately();

                if (is_player()) {
                    l->player = this;
                    dbg("Level change scroll map");
                    l->scroll_map_to_player();
                    l->update_new_level();
                    //
                    // Make sure all monsts on the new level are at the
                    // same tick or they will get lots of free attacks
                    //
                    l->update_all_ticks();
                }

                dbg("Level change finish move");
                move_finish();

                dbg("Level change update interpolated position");
                set_interpolated_mid_at(mid_at);
                update_interpolated_position();

                dbg("Level change location check");
                location_check();
                update_light();

                if (is_player() && level->cursor) {
                    level->cursor->move_to_immediately(mid_at);
                }

                is_changing_level = false;
                dbg("Moved to next level entrance");
                if (is_player()) {
                    level->timestamp_fade_in_begin = time_get_time_ms_cached();
                    level->update_new_level();
                }

                if (is_player()) {
                    if (game->robot_mode) {
                        game->tick_begin("Begin exploring");
                    }
                }

                return true;
            }
        }
    }

    return false;
}
