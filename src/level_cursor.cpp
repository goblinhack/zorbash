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
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"

void Level::cursor_check_if_scroll_needed (void)
{_
    if (map_follow_player) {
        if (cursor) {
            if (player) {
                auto d = distance(player->mid_at, cursor->mid_at);
                if (d > std::min(TILES_ACROSS/2, TILES_DOWN/2)) {
                    cursor->move(player->mid_at);
                }
            }
        }
    }
}

void Level::cursor_find_on_visible_things (
                        const uint16_t minx, const uint16_t miny,
                        const uint16_t maxx, const uint16_t maxy)
{
    if (game->state == Game::STATE_MOVING_ITEMS) {
        return;
    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
        return;
    }

    if (!cursor_needs_update) {
        return;
    }

    if (wid_find_under_mouse()) {
        return;
    }

    if ((game->minimap_over.x > 0) && (game->minimap_over.y > 0)) {
        //
        // Don't move onto lava unless double click
        //
        auto to = make_fpoint(game->minimap_over);
        if (!wid_mouse_double_click) {
            if (cursor) {_
                FOR_ALL_THINGS(this, t, to.x, to.y) {
                    if (t->is_cursor_can_hover_over_but_needs_double_click()) {
                        return;
                    }
                } FOR_ALL_THINGS_END()
            }
        }
        cursor->mid_at = to;
    } else {
        //
        // What tile are we over?
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_GRID_THINGS(this, t, x, y) {
                    t->cursor_hover_over_check();
                } FOR_ALL_THINGS_END();
            }
        }
    }

    cursor_needs_update = false;

    game->wid_thing_info_destroy();

    if (cursor) {
        auto p = cursor->mid_at;
        hover_over = nullptr;

        FOR_ALL_ACTIVE_THINGS(this, t, p.x, p.y) {
            int x = p.x;
            int y = p.y;
            if (!is_lit(x, y) && !is_visited(x, y)) {_
                continue;
            }

            if (t->get_immediate_owner() ||
                t->is_cursor() ||
                t->is_cursor_path() ||
                t->is_the_grid) {
                continue;
            }

            if (t->is_on_fire()) {
                BOTCON("%%fg=red$Burning! %s", t->text_description().c_str());
            } else {
                t->describe_when_hovering_over();

                if (t->tp()->long_text_description() != "") {
                    game->wid_thing_info_create_when_hovering_over(t);
                }
            }

            hover_over = t;
            return;
        } FOR_ALL_THINGS_END()

        FOR_ALL_INTERESTING_THINGS(this, t, p.x, p.y) {
            int x = p.x;
            int y = p.y;
            if (!is_lit(x, y) && !is_visited(x, y)) {_
                continue;
            }

            if (t->get_immediate_owner() ||
                t->is_cursor() ||
                t->is_cursor_path() ||
                t->is_the_grid) {
                continue;
            }

            t->describe_when_hovering_over();

            if (t->tp()->long_text_description() != "") {
                game->wid_thing_info_create_when_hovering_over(t);
            }
            hover_over = t;
            return;
        } FOR_ALL_THINGS_END()

        FOR_ALL_THINGS(this, t, p.x, p.y) {
            int x = p.x;
            int y = p.y;
            if (!is_lit(x, y) && !is_visited(x, y)) {_
                continue;
            }

            if (t->get_immediate_owner() ||
                t->is_cursor() ||
                t->is_cursor_path() ||
                t->is_the_grid) {
                continue;
            }

            t->describe_when_hovering_over();

            if (t->tp()->long_text_description() != "") {
                game->wid_thing_info_create_when_hovering_over(t);
            }
            hover_over = t;
            return;
        } FOR_ALL_THINGS_END()
    }
}

//
// Move the cursor to whatever thing it is now over
//
void Level::cursor_move (void)
{_
    if (is_mouse_over_inventory()) {
        return;
    }

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

    cursor->dead("update");
    if (game->state == Game::STATE_CHOOSING_TARGET) {
        if (DISTANCE(player->mid_at.x, player->mid_at.y, 
                     mid_at.x, mid_at.y)  >
                player->get_throw_distance()) {
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
