//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_globals.h"
#include "my_ptrcheck.h"
#include "my_dmap.h"

void Level::cursor_path_draw_circle (void)
{_
    auto what = game->request_to_throw_item;
    if (!what) {
        return;
    }

    auto radius_min = what->tp()->is_item_effect_min_radius();
    auto radius_max = what->tp()->is_item_effect_max_radius();
    auto mid_at = cursor->mid_at;

    bool too_far = false;
    if (DISTANCE(player->mid_at.x, player->mid_at.y, mid_at.x, mid_at.y) >
        player->get_throw_distance()) {
        too_far = true;
    }

    for (auto x = mid_at.x - radius_max; x <= mid_at.x + radius_max; x++) {
        for (auto y = mid_at.y - radius_max; y <= mid_at.y + radius_max; y++) {
            float dist = DISTANCE(x, y, mid_at.x, mid_at.y);

            if (is_oob(x, y)) {
                continue;
            }

            if (dist > radius_max) {
                continue;
            }

            if (dist < radius_min) {
                continue;
            }

            if (is_rock(x, y) || is_wall(x, y)) {
                continue;
            }

            if (too_far) {
                thing_new("cursor_select_fail_path", fpoint(x, y));
            } else {
                thing_new("cursor_select_path", fpoint(x, y));
            }
        }
    }
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw_line (point start, point end)
{_
    Dmap d {};
    point dmap_start = start;
    point dmap_end = end;

    int minx, miny, maxx, maxy;
    if (dmap_start.x < dmap_end.x) {
        minx = dmap_start.x;
        maxx = dmap_end.x;
    } else {
        minx = dmap_end.x;
        maxx = dmap_start.x;
    }
    if (dmap_start.y < dmap_end.y) {
        miny = dmap_start.y;
        maxy = dmap_end.y;
    } else {
        miny = dmap_end.y;
        maxy = dmap_start.y;
    }

    auto border = TILES_ACROSS / 2;
    minx -= border;
    miny -= border;
    maxx += border;
    maxy += border;

    if (minx < 0) {
        minx = 0;
    }
    if (miny < 0) {
        miny = 0;
    }
    if (maxx >= MAP_WIDTH) {
        maxx = MAP_WIDTH - 1;
    }
    if (maxy >= MAP_HEIGHT) {
        maxy = MAP_HEIGHT - 1;
    }

    //
    // Set up obstacles for the search
    //
    if (is_extreme_hazard(player->mid_at.x, player->mid_at.y)) {
        //
        // Just map the shortest path outta here
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (is_movement_blocking_hard(x, y)) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    } else if (cursor && is_extreme_hazard(cursor->mid_at.x, cursor->mid_at.y)) {
        //
        // If the cursor is on a hazard we can plot a course via hazards.
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (is_movement_blocking_hard(x, y)) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    } else if (player->collision_obstacle(player->mid_at)) {
        //
        // If already on a hazard we can plot a course via hazards.
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (is_extreme_hazard(x, y) ||
                    is_movement_blocking_hard(x, y)) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    } else {
        //
        // Else avoid all hazards as we are not standing on one
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (is_extreme_hazard(x, y) ||
                    player->collision_obstacle(point(x, y))) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    }

    dmap_start = point(minx, miny);
    dmap_end = point(maxx, maxy);

    set(d.val, end.x, end.y, DMAP_IS_GOAL);
    set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

    if (g_opt_debug3) {
        log("Make cursor path %d,%d to %d,%d", start.x, start.y, end.x, end.y);
    }

    dmap_process(&d, dmap_start, dmap_end);
    //dmap_print(&d, start, dmap_start, dmap_end);
    auto p = dmap_solve_allow_diagonal(&d, start);
    game->cursor_move_path = p;

    for (auto& c : p) {
        if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
            continue;
        }
        thing_new("cursor_path", fpoint(c.x , c.y));
    }
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw (point start, point end)
{_
    if (!player) {
        return;
    }

    if (game->request_to_throw_item) {
        cursor_path_draw_circle();
    } else {
        cursor_path_draw_line(start, end);
    }

    //
    // Let's see the path
    //
    minimap_valid = false;
}

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw (void)
{_
    if (!player) {
        return;
    }

    if (game->request_to_throw_item) {
        cursor_path_draw_circle();
    }

    //
    // Let's see the path
    //
    minimap_valid = false;
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::cursor_path_create (void)
{_
    if (game->paused()) {
        return;
    }

    if (!cursor) {
        return;
    }

    cursor_path_clear();

    //
    // If not following the player, draw the path
    //
    if (player) {
        cursor_path_draw(
            point(player->mid_at.x, player->mid_at.y),
            point(cursor_at.x, cursor_at.y));
    }
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void Level::cursor_path_clear (void)
{_
    if (game->paused()) {
        return;
    }

    auto level = game->level;
    if (!level) {
        return;
    }

    game->cursor_move_path.clear();

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y) {
                t->hide();
                t->dead("end of life");
            } FOR_ALL_THINGS_END()
        }
    }
}
