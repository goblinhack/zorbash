//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

std::vector<point> Thing::ai_create_path (point start, point end)
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
            if ((level->is_monst(x,y) && !level->is_corpse(x,y)) ||
                level->is_door(x,y)                              ||
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

    dmap_start = point(minx, miny);
    dmap_end = point(maxx, maxy);

    set(d.val, end.x, end.y, DMAP_IS_GOAL);
    set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

    dmap_process_allow_diagonals(&d, dmap_start, dmap_end);
#if 0
    dmap_print(&d, start, dmap_start, dmap_end);
#endif
    auto p = dmap_solve_allow_diagonal(&d, start);
    return p;
}

bool Thing::ai_choose_wander (point& nh)
{_
    log("choose wander location");
    auto target = monstp->wander_target;

    //
    // Reached the target? Choose a new one.
    //
    if ((mid_at.x == target.x) && (mid_at.y == target.y)) {
        target = point(0, 0);
    }

    //
    // Try to use the same location.
    //
    if (target != point(0, 0)) {
        auto l = ai_create_path(point(mid_at.x, mid_at.y), target);
        if (l.size()) {
            nh = l[0];
            log("continue wander to %d,%d nh %d,%d", 
                target.x, target.y, nh.x, nh.y);
            return (true);
        }
    }

    //
    // Choose a new wander location
    //
    monstp->wander_target = point(0, 0);
    int tries = (MAP_WIDTH * MAP_HEIGHT) / 2;
    while (tries--) {
        auto x = random_range(MAP_BORDER, MAP_WIDTH - MAP_BORDER);
        auto y = random_range(MAP_BORDER, MAP_HEIGHT - MAP_BORDER);
        target = point(x, y);
        auto l = ai_create_path(point(mid_at.x, mid_at.y), target);
        if (!l.size()) {
            continue;
        }

        monstp->wander_target = point(x, y);
        nh = l[0];
        log("wander to %d,%d nh %d,%d", target.x, target.y, nh.x, nh.y);
        return (true);
    }

    return false;
}
