//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_wid_console.h"
#include "my_sdl.h"
#include "my_ascii.h"
#include "my_wid.h"
#include "my_thing.h"
#include "my_dmap.h"
#include <algorithm>

//
// Move the cursor to whatever thing it is now over
//
void thing_cursor_move (void)
{_
    if (game->paused()) {
        return;
    }

#if 0
    //
    // Blocks scrolling when over item and status bars!
    //
    int x = mouse_x;
    int y = mouse_y;
    pixel_to_ascii(&x, &y);
    if (get(wid_on_screen_at, x, y)) {
        return;
    }
#endif

    if ((wheel_x != 0) || (wheel_y != 0)) {
        level->map_wanted_at += fpoint(wheel_x, -wheel_y);
    }

    //
    // Dampen mouse moves at level start
    //
    if (level->timestamp_dungeon_created &&
        time_have_x_tenths_passed_since(2, level->timestamp_dungeon_created)) {
        level->mouse = mouse_tick;
        if (level->mouse > level->mouse_old) {
            level->mouse_old = level->mouse;
            level->cursor_needs_update = true;
            level->cursor_found = false;
            level->map_follow_player = false;
        }
    } else {
        level->mouse = mouse_tick;
        level->mouse_old = level->mouse;
        level->map_follow_player = true;
        level->cursor_needs_update = false;
    }

    auto cursor = level->cursor;
    if (cursor) {
        if (level->cursor_at != level->cursor_at_old) {
            level->cursor_at_old = level->cursor_at;
            cursor->move(level->cursor_at);

            //
            // If the cursor has moved, update the cursor path as long
            // as the move was not initiated by the player manually moving.
            //
            if (level->player) {
                if (!level->map_follow_player) {
                    if (0) { // no longer used
                        thing_cursor_path_create();
                    }
                }
            }
        }
    }
}

//
// Make the map scroll to the cursor (or the player)
//
void thing_cursor_scroll_map_to_follow (void)
{_
    fpoint follow;
    float sensitivity;
    float x_sensitivity;
    float y_sensitivity;

    if (level->player && level->map_follow_player) {
        follow = level->player->at;
        sensitivity = 0.5;
        x_sensitivity = sensitivity * game->config.video_w_h_ratio;
        y_sensitivity = sensitivity;
    } else if (level->cursor && !level->map_follow_player) {
        //
        // If over a widget, do not scroll
        //
        extern Widp wid_itembar;
        if (wid_over) {
            return;
        }
        if (!wid_itembar) {
            return;
        }

        //
        // If we are in the portion of the lower screen above the itembar
        // then do not scroll
        //
        int x = mouse_x;
        int y = mouse_y;
        pixel_to_ascii(&x, &y);

        static int tlx, tly, brx, bry, cached;
        if (cached != ASCII_HEIGHT) {
            cached = ASCII_HEIGHT;
            wid_get_tl_x_tl_y_br_x_br_y(wid_itembar, &tlx, &tly, &brx, &bry);
        }

        if ((x >= tlx) && (x <= brx) && (y >= tly - ASCII_HEIGHT / 4)) {
            return;
        }

        follow = level->cursor->at;
        sensitivity = TILES_ACROSS / 6;
        x_sensitivity = sensitivity * game->config.video_w_h_ratio;
        y_sensitivity = sensitivity;
    } else {
        return;
    }

    float x1 = ((float)TILES_ACROSS / 2) - x_sensitivity;
    float x2 = ((float)TILES_ACROSS / 2) + x_sensitivity;
    float y1 = ((float)TILES_DOWN / 2) - y_sensitivity;
    float y2 = ((float)TILES_DOWN / 2) + y_sensitivity;

    float dx = follow.x - level->map_wanted_at.x + 1.0;
    if (dx > x2) {
        level->map_wanted_at.x++;
    }
    if (dx < x1) {
        level->map_wanted_at.x--;
    }

    float dy = follow.y - level->map_wanted_at.y + 1.0;
    if (dy > y2) {
        level->map_wanted_at.y++;
    }
    if (dy < y1) {
        level->map_wanted_at.y--;
    }
//CON("  follow %f %f at %f %f dx %f dy %f", follow.x, 
//follow.y,level->map_wanted_at.x, level->map_wanted_at.y, dx - x2, dy - y1);
}

void Thing::update_cursor (void)
{_
    if (is_cursor_can_hover_over()) {
        if (is_blitted) {
            float tl_mx = game->config.video_pix_width * last_blit_tl.x;
            float br_mx = game->config.video_pix_width * last_blit_br.x;
            float tl_my = game->config.video_pix_height * last_blit_tl.y;
            float br_my = game->config.video_pix_height * last_blit_br.y;
            if ((mouse_x >= tl_mx) && (mouse_x <= br_mx)) {
                if ((mouse_y >= tl_my) && (mouse_y <= br_my)) {
                    level->cursor_at = at;
                    level->cursor_found = true;
                }
            }
        }
    }
}

void thing_cursor_reset_if_needed (void)
{_
    if (level->map_follow_player) {
        if (level->cursor) {
            if (level->player) {
                auto d = distance(level->player->at, level->cursor->at);
                if (d > std::min(TILES_ACROSS/4, TILES_DOWN/4)) {
                    level->cursor_needs_update = true;
                }
            }
        }
    }
}

void thing_cursor_find (uint16_t minx, uint16_t miny,
                        uint16_t maxx, uint16_t maxy)
{_
    if (level->cursor_needs_update) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                FOR_ALL_THINGS(level, t, x, y) {
                    t->update_cursor();
                } FOR_ALL_THINGS_END();
            }
        }
    }
}
