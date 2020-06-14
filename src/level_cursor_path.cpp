//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

//
// Create the cursor path, avoiding things like lava
//
void Level::cursor_path_draw (point start, point end)
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
    auto player = level->player;
    auto cursor = level->cursor;

    if (player &&
        level->is_hazard((int)player->mid_at.x, (int)player->mid_at.y)) {
        //
        // If already on a hazard we can plot a course via hazards.
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if ((level->is_monst(x,y) && !level->is_corpse(x,y)) ||
                    level->is_secret_door(x,y)                       ||
                    level->is_rock(x, y)                             ||
                    level->is_wall(x, y)) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    } else if (cursor &&
        level->is_hazard((int)cursor->mid_at.x, (int)cursor->mid_at.y)) {
        //
        // If the cursor is on a hazard we can plot a course via hazards.
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if ((level->is_monst(x,y) && !level->is_corpse(x,y)) ||
                    level->is_secret_door(x,y)                       ||
                    level->is_rock(x, y)                             ||
                    level->is_wall(x, y)) {
                    set(d.val, x, y, DMAP_IS_WALL);
                } else {
                    set(d.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    } else {
        //
        // Else avoid hazards
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if ((level->is_monst(x,y) && !level->is_corpse(x,y)) ||
                    level->is_secret_door(x,y)                       ||
                    level->is_hazard(x,y)                            ||
                    level->is_rock(x, y)                             ||
                    level->is_wall(x, y)) {
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

    dmap_process(&d, dmap_start, dmap_end);
    // dmap_print(&d, start, dmap_start, dmap_end);
    auto p = dmap_solve_allow_diagonal(&d, start);
    game->cursor_move_path = p;

    for (auto& c : p) {
        thing_new("cursor_path", fpoint(c.x , c.y));
    }
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

    auto cursor = level->cursor;
    if (!cursor) {
        return;
    }

    cursor_path_clear();

    //
    // If not following the player, draw the path
    //
    if (level->player) {
        cursor_path_draw(
            point(level->player->mid_at.x, level->player->mid_at.y),
            point(level->cursor_at.x, level->cursor_at.y));
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

    auto cursor = level->cursor;
    if (!cursor) {
        return;
    }

    game->cursor_move_path.clear();

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y) {
                t->dead("end of life");
            } FOR_ALL_THINGS_END()
        }
    }
}
