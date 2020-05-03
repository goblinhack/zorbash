//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_wid_console.h"
#include "my_sdl.h"
#include "my_ascii.h"
#include "my_wid.h"
#include "my_thing.h"
#include "my_dmap.h"

//
// Can the two things reach each other, bar a solid obstacle
//
int thing_can_reach (point start, point end)
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
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (level->is_wall(x, y)       ||
                level->is_rock(x,y)        ||
                level->is_door(x,y)        ||
                level->is_secret_door(x,y)) {
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
    return (p.size());
}

int thing_can_reach_player (point start)
{_
    auto player = level->player;
    if (!player) {
        return (0);
    }

    static point last_player_at;
    static Levelp last_level;
    point end((int)player->mid_at.x, player->mid_at.y);

    if ((last_level != level) || (end != last_player_at) ||
        !game->player_dmap) {

        if (!game->player_dmap) {
            game->player_dmap = new Dmap();
        }
        last_level = level;
        last_player_at = end;

        auto d = game->player_dmap;

        point tl = end -
          point(MAX_LIGHT_PLAYER_DISTANCE / 2, MAX_LIGHT_PLAYER_DISTANCE / 2);
        point br = end +
          point(MAX_LIGHT_PLAYER_DISTANCE / 2, MAX_LIGHT_PLAYER_DISTANCE / 2);

        if (tl.x < 0) { tl.x = 0; }
        if (tl.y < 0) { tl.y = 0; }
        if (tl.x >= MAP_WIDTH) { tl.x = MAP_WIDTH - 1; }
        if (tl.y >= MAP_HEIGHT) { tl.y = MAP_HEIGHT - 1; }

        if (br.x < 0) { br.x = 0; }
        if (br.y < 0) { br.y = 0; }
        if (br.x >= MAP_WIDTH) { br.x = MAP_WIDTH - 1; }
        if (br.y >= MAP_HEIGHT) { br.y = MAP_HEIGHT - 1; }

        //
        // Set up obstacles for the search
        //
        for (auto y = tl.y; y < br.y; y++) {
            for (auto x = tl.x; x < br.x; x++) {
                if (level->is_wall(x, y)       ||
                    level->is_rock(x,y)        ||
                    level->is_door(x,y)        ||
                    level->is_secret_door(x,y)) {
                    set(d->val, x, y, DMAP_IS_WALL);
                } else {
                    set(d->val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }

        set(d->val, end.x, end.y, DMAP_IS_GOAL);
        dmap_process_allow_diagonals(d, tl, br);
        // dmap_print(&d, start, dmap_start, dmap_end);
    }

    auto d = game->player_dmap;
    auto p = dmap_solve_allow_diagonal(d, start);

    return (p.size());
}
