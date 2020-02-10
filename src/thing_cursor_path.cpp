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
// Create the cursor path, avoiding things like lava
//
static void thing_cursor_path_draw (point start, point end)
{
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
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (world->is_deep_water(x,y)  ||
                world->is_water(x,y)       ||
                world->is_monst(x,y)       ||
                world->is_lava(x,y)        ||
                world->is_wall(x, y)) {
                set(d.val, x, y, DMAP_IS_WALL);
            } else {
                set(d.val, x, y, DMAP_IS_PASSABLE);
            }
        }
    }

    dmap_start = point(minx, miny);
    dmap_end = point(maxx, maxy);

    set(d.val, end.x, end.y, DMAP_IS_GOAL);
    set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

    dmap_process_allow_diagonals(&d, dmap_start, dmap_end);
    // dmap_print(&d, start, dmap_start, dmap_end);
    auto p = dmap_solve_allow_diagonal(&d, start);
    game->move_path = p;

    for (auto c : p) {
        thing_new("cursor_path", fpoint(c.x , c.y));
    }
}

//
// Using a dmap, solve the path to where the cursor is, creating a highlighted
// path to follow.
//
void thing_cursor_path_create (void)
{_
    if (game->paused()) {
        return;
    }

    auto cursor = world->cursor;
    if (!cursor) {
        return;
    }

    game->move_path.clear();

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_CURSOR_PATH_THINGS(world, t, x, y) {
                t->dead("eol");
            }
        }
    }

    //
    // If not following the player, draw the path
    //
    if (world->player) {
        thing_cursor_path_draw(
            point(world->player->mid_at.x, world->player->mid_at.y),
            point(world->cursor_at.x, world->cursor_at.y));
    }
}

bool Thing::cursor_path_pop_next_and_move (void)
{
    if (monst && monst->move_path.size()) {
        auto to = monst->move_path[0];
        auto future_pos = fpoint(to.x + 0.5, to.y + 0.5);
        FOR_ALL_CURSOR_PATH_THINGS(world, t, to.x, to.y) {
            t->dead("eol");
        }
        monst->move_path.erase(monst->move_path.begin());
        return (move(future_pos));
    } else {
        return (false);
    }
}

void Thing::cursor_path_grab (void)
{
    if (game->move_path.size()) {
        new_monst();
        monst->move_path = game->move_path;
        game->move_path.clear();
        cursor_path_pop_next_and_move();
    }
}
