//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_random.h"

bool Level::create_sewer (point3d at, int seed)
{_
    log("Create sewer at (%d,%d,%d)", at.x, at.y, at.z);

    place_the_grid();
    if (g_errored) { return false; }

    place_the_grid();
    if (g_errored) { return false; }

    if (!create_sewer_pipes(at)) {
        return false;
    }
    if (g_errored) { return false; }

    auto tries = 10000;
    create_sewer_place_rocks(1, 6, 6, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 6, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 3, 6, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 3, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(2, 3, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(2, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(3, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 2, 1, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(2, 2, 1, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(1, 1, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_rocks(2, 1, 2, tries);
    if (g_errored) { return false; }

    create_sewer_place_remaining_rocks("rock1");
    if (g_errored) { return false; }

    return true;
}

bool Level::create_sewer_pipes (point3d at)
{_
    auto prev = get(game->world.levels, at.x, at.y, at.z - 1);
    if (!prev) {
        err("no previous level for sewer");
        return false;
    }

    auto player = prev->player;
    if (!prev) {
        err("no previous level player for sewer");
        return false;
    }

    Dmap dmap {};

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            set(dmap.val, x, y, DMAP_IS_PASSABLE);
        }
    }

    set(dmap.val, player->mid_at.x, player->mid_at.y, DMAP_IS_GOAL);

    //
    // Find all pipes and mark them as goals.
    //
    point midpoint;
    int got_count = 0;

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            FOR_ALL_THINGS(prev, t, x, y) {
                if (t->is_sewer_entrance()) {
                    set(dmap.val, x, y, DMAP_IS_GOAL);
                    midpoint += point(x, y);
                    got_count++;
                }
            } FOR_ALL_THINGS_END()
        }
    }

    if (!got_count) {
        set(dmap.val, random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT), DMAP_IS_GOAL);
        set(dmap.val, random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT), DMAP_IS_GOAL);
        set(dmap.val, random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT), DMAP_IS_GOAL);
        set(dmap.val, random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT), DMAP_IS_GOAL);
        midpoint.x = random_range(0, MAP_WIDTH);
        midpoint.y = random_range(0, MAP_HEIGHT);
    } else {
        midpoint /= got_count;
    }

    point midpoint2;
    midpoint2.x = random_range(0, MAP_WIDTH);
    midpoint2.y = random_range(0, MAP_HEIGHT);

    dmap_print(&dmap);
    dmap_process(&dmap);

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            FOR_ALL_THINGS(prev, t, x, y) {
                if (t->is_sewer_entrance()) {
                    char path_debug = '\0'; // astart path debug
                    auto result = astar_solve(path_debug, midpoint, point(x, y), &dmap);

                    for (auto p : result.path) {
                        (void) thing_new("corridor2", p);
                        if (random_range(0, 100) < 50) {
                            if (random_range(0, 100) < 50) {
                                (void) thing_new("water1", p);
                            } else {
                                (void) thing_new("deep_water1", p);
                            }
                        }
                    }

                    if (random_range(0, 100) < 20) {
                        auto result = astar_solve(path_debug, midpoint2, point(x, y), &dmap);
                        for (auto p : result.path) {
                            (void) thing_new("corridor3", p);
                        }
                    }

                    (void) thing_new("sewer_exit1", point(x, y));
                }
            } FOR_ALL_THINGS_END()
        }
    }

    return true;
}

void Level::create_sewer_place_rocks (int variant, int block_width, int block_height, int tries)
{_
    auto tp = tp_random_rock();
    if (!tp) {
        ERR("Place rocks failed");
        return;
    }
    auto what = tp->name();

    while (tries--) {
        auto x = random_range(0, MAP_WIDTH - block_width + 1);
        auto y = random_range(0, MAP_HEIGHT - block_height + 1);

        auto can_place_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (is_corridor(X, Y) || is_shallow_water(X, Y) || is_deep_water(X, Y)) {
                    can_place_here = false;
                    continue;
                }

                //
                // We place large blocks and avoid splatting them with
                // smaller ones here.
                //
                if (is_rock(X, Y)) {
                    can_place_here = false;
                    continue;
                }
            }

            if (!can_place_here) {
                break;
            }
        }

        if (!can_place_here) {
            continue;
        }

        auto cnt = 1;
        for (auto dy = 0; dy < block_height; dy++) {
            auto Y = y + dy;
            for (auto dx = 0; dx < block_width; dx++) {
                auto X = x + dx;
                set_is_rock(X, Y);

                auto tilename = what + ".";
                tilename += std::to_string(variant);
                if (!((block_width == 1) && (block_height == 1))) {
                    tilename += ".";
                    tilename += std::to_string(block_width);
                    tilename += "x";
                    tilename += std::to_string(block_height);
                    tilename += ".";
                    tilename += std::to_string(cnt);
                    cnt++;
                }

                auto t = thing_new(what, fpoint(X, Y));
                auto tile = tile_find(tilename);
                if (!tile) {
                    ERR("Rock tile %s not found", tilename.c_str());
                    return;
                }
                t->tile_curr = tile->global_index;

                //
                // Need this so we can display chasms under walls
                //
                (void) thing_new("wall_floor1", fpoint(X, Y));
            }
        }
    }
}

void Level::create_sewer_place_remaining_rocks (const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {

            if (is_corridor(x, y) || is_shallow_water(x, y) || is_deep_water(x, y)) {
                continue;
            }

            if (is_rock(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            //
            // Need this so we can display chasms under walls
            //
            (void) thing_new("wall_floor1", fpoint(x, y));
        }
    }
}
