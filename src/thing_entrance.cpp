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

bool Thing::entrance_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend || 
        is_waiting_to_fall || 
        is_jumping) { 
        return false;
    }

    if (owner_get()) {
        return false;
    }

    if (!is_able_to_change_levels()) {
        return false;
    }

    if (!level->is_entrance(mid_at.x, mid_at.y)) {
        return false;
    }

    if (get_tick() - get_tick_last_level_change() < 1) {
        return false;
    }

    if (level->world_at.z > 1) {
        if (is_player()) {
            level->timestamp_fade_out_begin = time_get_time_ms_cached();
            is_waiting_to_ascend = true;
            return true;
        } else {
            return ascend();
        }
    }

    return false;
}

bool Thing::ascend (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_descend || 
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
            MINICON("The entrance is permanently blocked!");
        }
        return false;
    }

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_exit(x, y)) {
                if (is_player()) {
                    game->level = l;
                    MINICON("You bravely ascend");
                }

                log("move to previous level exit");
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
                log("moved to previous level exit");
                if (is_player()) {
                    level->timestamp_fade_in_begin = time_get_time_ms_cached();
                    level->update();
                }
                return true;
            }
        }
    }

    game->tick_begin("ascend to new level");
    if (is_player()) {
        level->timestamp_fade_in_begin = time_get_time_ms_cached();
        level->update();
    }
    return true;
}
