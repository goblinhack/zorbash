//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_wid_console.h"
#include "my_sdl.h"
#include <algorithm>

//
// Move the cursor to whatever thing it is now over
//
void thing_cursor_move (void)
{_
    if ((wheel_x != 0) || (wheel_y != 0)) {
        world->map_wanted_at += fpoint(wheel_x, -wheel_y);
    }

    //
    // Dampen mouse moves at level start
    //
    if (world->timestamp_dungeon_created &&
        time_have_x_tenths_passed_since(2, world->timestamp_dungeon_created)) {
        world->mouse = mouse_tick;
        if (world->mouse > world->mouse_old) {
            world->mouse_old = world->mouse;
            world->cursor_needs_update = true;
            world->cursor_found = false;
            world->map_follow_player = false;
        }
    } else {
        world->mouse = mouse_tick;
        world->mouse_old = world->mouse;
        world->map_follow_player = true;
        world->cursor_needs_update = false;
    }

    auto cursor = world->cursor;
    if (cursor) {
        if (world->cursor_at != world->cursor_at_old) {
            world->cursor_at_old = world->cursor_at;
            cursor->move(world->cursor_at);
        }
    }
}

//
// Make the map scroll to the cursor (or the player)
//
void thing_cursor_map_follow (void)
{
    fpoint follow;
    float sensitivity;
    float x_sensitivity;
    float y_sensitivity;

    if (world->player && world->map_follow_player) {
        follow = world->player->mid_at;
        sensitivity = 0.5;
        x_sensitivity = sensitivity * game->config.video_w_h_ratio;
        y_sensitivity = sensitivity;
    } else if (world->cursor && !world->map_follow_player) {
        follow = world->cursor->mid_at;
        sensitivity = TILES_ACROSS / 4;
        x_sensitivity = sensitivity * game->config.video_w_h_ratio;
        y_sensitivity = sensitivity;
    } else {
        return;
    }

    float x1 = ((float)TILES_ACROSS / 2) - x_sensitivity;
    float x2 = ((float)TILES_ACROSS / 2) + x_sensitivity;
    float y1 = ((float)TILES_DOWN / 2) - y_sensitivity;
    float y2 = ((float)TILES_DOWN / 2) + y_sensitivity;

    float dx = follow.x - world->map_wanted_at.x + 1.0;
    if (dx > x2) {
        world->map_wanted_at.x++;
    }
    if (dx < x1) {
        world->map_wanted_at.x--;
    }

    float dy = follow.y - world->map_wanted_at.y + 1.0;
    if (dy > y2) {
        world->map_wanted_at.y++;
    }
    if (dy < y1) {
        world->map_wanted_at.y--;
    }
//CON("  follow %f %f at %f %f dx %f dy %f", follow.x, follow.y,
//world->map_wanted_at.x, world->map_wanted_at.y, dx - x2, dy - y1);
}

void Thing::update_cursor (void)
{
    if (is_cursor_hover()) {
        if (is_blitted) {
            float tl_mx = game->config.video_pix_width * last_blit_tl.x;
            float br_mx = game->config.video_pix_width * last_blit_br.x;
            float tl_my = game->config.video_pix_height * last_blit_tl.y;
            float br_my = game->config.video_pix_height * last_blit_br.y;
            if ((mouse_x >= tl_mx) && (mouse_x <= br_mx)) {
                if ((mouse_y >= tl_my) && (mouse_y <= br_my)) {
                    world->cursor_at = mid_at;
                    world->cursor_found = true;
                }
            }
        }
    }
}

void thing_cursor_reset_if_needed (void)
{
    if (world->map_follow_player) {
        if (world->cursor) {
            if (world->player) {
                auto d = distance(world->player->mid_at, world->cursor->mid_at);
                if (d > std::min(TILES_ACROSS/4, TILES_DOWN/4)) {
                    world->cursor_needs_update = true;
                }
            }
        }
    }
}

void thing_cursor_find (uint16_t minx, uint16_t miny,
                        uint16_t maxx, uint16_t maxy)
{
    if (world->cursor_needs_update) {
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                for (auto z = 0; z < MAP_DEPTH; z++) {
                    FOR_ALL_THINGS(world, t, x, y, z) {
                        t->update_cursor();
                    }
                }
            }
        }
    }
}
