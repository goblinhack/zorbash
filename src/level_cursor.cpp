//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_game_status.h"

void Level::cursor_check_if_scroll_needed (void)
{
    if (map_follow_player) {
        if (cursor) {
            if (player) {
                auto d = distance(player->mid_at,
                                  cursor->mid_at);
                if (d > std::min(TILES_ACROSS/4, TILES_DOWN/4)) {
                    cursor_needs_update = true;
                }
            }
        }
    }
}

void Level::cursor_find_on_visible_things (
                        const uint16_t minx, const uint16_t miny,
                        const uint16_t maxx, const uint16_t maxy)
{
    if (cursor_needs_update) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS(game->level, t, x, y) {
                    t->cursor_hover_over_check();
                } FOR_ALL_THINGS_END();
            }
        }
    }
}

//
// Move the cursor to whatever thing it is now over
//
void Level::cursor_move (void)
{
    if (is_mouse_over_actionbar()) {
        return;
    }

    if ((wheel_x != 0) || (wheel_y != 0)) {
        if (wid_find_under_mouse()) {
            return;
        }
        map_wanted_at += fpoint(wheel_x, -wheel_y);
    }

    if (game->paused()) {
        return;
    }

    //
    // Dampen mouse moves at level start
    //
    if (timestamp_dungeon_created &&
        time_have_x_tenths_passed_since(2, timestamp_dungeon_created)) {
        mouse = mouse_tick;
        if (mouse > mouse_old) {
            mouse_old = mouse;
            cursor_needs_update = true;
            cursor_found = false;
            map_follow_player = false;
        }
    } else {
        mouse = mouse_tick;
        mouse_old = mouse;
        map_follow_player = true;
        cursor_needs_update = false;
    }

    if (cursor) {
        if (cursor_at != cursor_at_old) {
            cursor_at_old = cursor_at;
            cursor->move(cursor_at);
            cursor_path_create();
        }
    }
}
