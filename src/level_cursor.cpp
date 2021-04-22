//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"

void Level::cursor_check_if_scroll_needed (void)
{_
    //
    // Not sure why I have this and what it does :)
    //
    if (map_follow_player) {
        if (cursor) {
            if (player) {
                auto d = distance(player->mid_at, cursor->mid_at);
                if (d > std::min(TILES_ACROSS, TILES_DOWN)) {
                    cursor->move(player->mid_at);
                }
            }
        }
    }
}

//
// Move the cursor to whatever thing it is now over
//
void Level::cursor_move (void)
{_
    if (is_mouse_over_any_bag()) {
        return;
    }

    if (wid_find_under_mouse()) {
        return;
    }

    if ((wheel_x != 0) || (wheel_y != 0)) {
        if (wid_find_under_mouse_when_scrolling()) {
            return;
        }
        map_wanted_at += fpoint(wheel_x, -wheel_y);
        map_follow_player = false;
        return;
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
        }
    } else {
        mouse = mouse_tick;
        mouse_old = mouse;
        map_follow_player = true;
        cursor_needs_update = false;
    }

    if (cursor) {_
        verify(cursor);
        if (cursor_at != cursor_at_old) {
            cursor_at_old = cursor_at;
            cursor->move(cursor_at);
            cursor_recreate();
        }
    }
}

void Level::cursor_recreate (void)
{_
    if (!cursor) {
        err("no cursor");
        return;
    }

    auto mid_at = cursor->mid_at;

    auto what = game->request_to_throw_item;
    if (!what) {
        what = game->request_to_laser_item;
    }

    cursor->dead("update");
    if (what && (game->state == Game::STATE_CHOOSING_TARGET)) {
        bool too_far = false;
        auto dist = DISTANCE(player->mid_at.x, player->mid_at.y,
                             mid_at.x, mid_at.y);
        if (what->get_throw_distance()) {
            too_far = dist > player->get_throw_distance();
        } else if (what->range_max()) {
            too_far = dist > what->range_max();
        }

        if (too_far) {
            cursor = thing_new("cursor_select_fail", mid_at);
        } else {
            cursor = thing_new("cursor_select", mid_at);
        }
    } else {
        cursor = thing_new("cursor", mid_at);
    }
    cursor->hide();
    cursor_path_create();
}
