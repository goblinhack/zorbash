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

bool Thing::ai_create_path (point &nh, const point start, const point end)
{_
    Dmap dmap {};
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
                set(dmap.val, x, y, DMAP_IS_WALL);
            } else {
                auto c = is_less_preferred_terrain(point(x, y));
                if (c >= DMAP_MAX_LESS_PREFERRED_TERRAIN) {
                    set(dmap.val, x, y, c);
                } else {
                    set(dmap.val, x, y, DMAP_IS_PASSABLE);
                }
            }
        }
    }

    dmap_start = point(minx, miny);
    dmap_end = point(maxx, maxy);

    set(dmap.val, end.x, end.y, DMAP_IS_GOAL);
    set(dmap.val, start.x, start.y, DMAP_IS_PASSABLE);

    dmap_process(&dmap, dmap_start, dmap_end);
#if 0
    dmap_print(&dmap, start, dmap_start, dmap_end);
#endif

    auto p = dmap_solve(&dmap, start);

    char path_debug = '\0'; // astart path debug
    auto result = astar_solve(path_debug, start, end, &dmap);
#if 0
    for (auto i : result.path) {
        set(dmap.val, i.x, i.y, (uint8_t)0);
    }
    dmap_print(&dmap, start, dmap_start, dmap_end);
#endif
#ifdef ENABLE_DEBUG_AI_WANDER
    for (auto i : result.path) {
        thing_new("ai_path1", fpoint(i.x , i.y));
    }
#endif

    auto hops = result.path;
    auto hops_len = hops.size();

    if (hops_len >= 2) {
        auto hop0 = get(hops, hops_len - 1);
        auto hop1 = get(hops, hops_len - 2);
        if (dmap_can_i_move_diagonally(&dmap, start, hop0, hop1)) {
            nh = hop1;
        } else {
            nh = hop0;
        }
        return true;
    } else if (hops_len >= 1) {
        auto hop0 = get(hops, hops_len - 1);
        nh = hop0;
        return true;
    } else {
        return false;
    }
}

bool Thing::ai_choose_wander (point& nh)
{_
    //
    // Reached the target? Choose a new one.
    //
    auto target = monstp->wander_target;
    if ((mid_at.x == target.x) && (mid_at.y == target.y)) {
        log("reached target");
        target = point(0, 0);
    }

    //
    // Try to use the same location.
    //
    if (target != point(0, 0)) {
        if (ai_create_path(nh, point(mid_at.x, mid_at.y), target)) {
            return true;
        }
    }

    //
    // Choose a new wander location
    //
    monstp->wander_target = point(0, 0);

    target = get_random_scent_target();
    if (!ai_create_path(nh, point(mid_at.x, mid_at.y), target)) {
        dbg("wander failed");
        return false;
    }

    monstp->wander_target = target;
#ifdef ENABLE_DEBUG_AI_WANDER
    thing_new("ai_path2", fpoint(target.x , target.y));
#endif
    log("wander to %d,%d nh %d,%d", target.x, target.y, nh.x, nh.y);
    return true;
}

bool Thing::ai_wander (void)
{_
    log("ai wander");
    auto tries = 10;
    while (tries--) {
        point nh;
        if (ai_choose_wander(nh)) {
            if (!is_less_preferred_terrain(nh)) {
                if (move_to_or_attack(nh)) {
                    return true;
                }
            }

            //
            // Set this so next time we will choose another target
            //
            monstp->wander_target = point(0, 0);
        }
    }
_
    log("no wander goal");
    return false;
}

bool Thing::ai_escape (void)
{_
    log("ai escape");
    auto tries = 10;
    while (tries--) {
        point nh;
        if (ai_choose_wander(nh)) {
            if (move_to_or_attack(nh)) {
                return true;
            }

            //
            // Set this so next time we will choose another target
            //
            monstp->wander_target = point(0, 0);
        }
    }
_
    log("no escape goal");
    return false;
}
