//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_random.h"
#include "my_array_bounds_check.h"
#include "my_globals.h"
#include "my_ptrcheck.h"
#include "my_thing_ai.h"

bool Level::create_sewer (point3d at, int seed)
{_
    log("Create sewer at (%d,%d,%d)", at.x, at.y, at.z);

    is_sewer_level = true;

    place_the_grid();
    if (g_errored) { return false; }

    place_the_grid();
    if (g_errored) { return false; }

    if (!create_sewer_pipes(at)) {
        return false;
    }
    if (g_errored) { return false; }

    auto tries = 10000;
    create_sewer_place_walls(1, 6, 6, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 6, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 3, 6, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 3, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(2, 3, 3, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(2, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(3, 2, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 2, 1, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(2, 2, 1, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(1, 1, 2, tries);
    if (g_errored) { return false; }
    create_sewer_place_walls(2, 1, 2, tries);
    if (g_errored) { return false; }

    create_sewer_place_remaining_walls("sewer_wall");
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

    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> pipes_template = {};
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> sewer_pipe = {};
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> final_pipes = {};
    std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> failed = {};

    //
    // Draw some random pipes
    //
    auto min_pipe_distance = 10;
    auto max_pipe_distance = 20;
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; 
         x+=random_range(min_pipe_distance,max_pipe_distance)) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            set(pipes_template, x, y, true);
        }
    }

    for (auto y = MAP_BORDER_ROCK; y < MAP_WIDTH - MAP_BORDER_ROCK; 
         y+=random_range(min_pipe_distance,max_pipe_distance)) {
        for (auto x = MAP_BORDER_ROCK; x < MAP_HEIGHT - MAP_BORDER_ROCK; x++) {
            set(pipes_template, x, y, true);
        }
    }

    //
    // Place the sewers
    //
    std::vector<point> sewers;
    auto got_count = 0;

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            FOR_ALL_THINGS(prev, t, x, y) {
                if (t->is_descend_sewer()) {
                    point p(x, y);
                    sewers.push_back(p);
                    set(sewer_pipe, x, y, true);
                    got_count++;
                }
            } FOR_ALL_THINGS_END()
        }
    }

    if (got_count <= 1) {
        sewers.push_back(point(random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT)));
        sewers.push_back(point(random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT)));
        sewers.push_back(point(random_range(0, MAP_WIDTH), random_range(0, MAP_HEIGHT)));
    }

    //
    // Draw a line from the sewer to a nearby pipe
    //
    for (auto n = 0U; n < sewers.size(); n++) {
        auto p = sewers[n];
        int dx = 0, dy = 0;
        switch (random_range_inclusive(0, 3)) {
            case 0: dx = -1; dy = 0; break;
            case 1: dx =  1; dy = 0; break;
            case 2: dx =  0; dy = -1; break;
            case 3: dx =  0; dy = 1; break;
        }

        while (true) {
            if (p.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
                break;
            }
            if (p.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
                break;
            }
            if (p.x <= MAP_BORDER_ROCK) {
                break;
            }
            if (p.y <= MAP_BORDER_ROCK) {
                break;
            }

            //
            // Try to follow the pipe template
            //
            if (get(pipes_template, p.x, p.y)) {
                break;
            }
            set(pipes_template, p.x, p.y, true);
            p.x += dx;
            p.y += dy;
        }
    }

    //
    // For each sewer, try to find another
    //
    for (auto n = 0U; n < sewers.size(); n++) {
        auto a = sewers[n];
        auto b = sewers[random_range(0, sewers.size())];
        while (a == b) {
            b = sewers[random_range(0, sewers.size())];
        }

        std::array< std::array<bool, MAP_WIDTH>, MAP_HEIGHT> walked = {};
        int tries = 0;
        while (tries < 1000) {
            set(final_pipes, a.x, a.y, true);
            set(walked, a.x, a.y, true);
            if (a.x >= MAP_WIDTH - MAP_BORDER_ROCK) {
                break;
            }
            if (a.y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
                break;
            }
            if (a.x <= MAP_BORDER_ROCK) {
                break;
            }
            if (a.y <= MAP_BORDER_ROCK) {
                break;
            }

            //
            // Try to follow the pipe template
            //
            if ((a.x < b.x) && get(pipes_template, a.x + 1, a.y)) {
                a.x++;
                continue;
            }
            if ((a.x > b.x) && get(pipes_template, a.x - 1, a.y)) {
                a.x--;
                continue;
            }
            if ((a.y < b.y) && get(pipes_template, a.x, a.y + 1)) {
                a.y++;
                continue;
            }
            if ((a.y > b.y) && get(pipes_template, a.x, a.y - 1)) {
                a.y--;
                continue;
            }
            if (!get(walked, a.x + 1, a.y) && get(pipes_template, a.x + 1, a.y)) {
                a.x++;
                continue;
            }
            if (!get(walked, a.x - 1, a.y) && get(pipes_template, a.x - 1, a.y)) {
                a.x--;
                continue;
            }
            if (!get(walked, a.x, a.y + 1) && get(pipes_template, a.x, a.y + 1)) {
                a.y++;
                continue;
            }
            if (!get(walked, a.x, a.y - 1) && get(pipes_template, a.x, a.y - 1)) {
                a.y--;
                continue;
            }
            if (!get(walked, a.x + 1, a.y)) {
                a.x++;
                continue;
            }
            if (!get(walked, a.x - 1, a.y)) {
                a.x--;
                continue;
            }
            if (!get(walked, a.x, a.y + 1)) {
                a.y++;
                continue;
            }
            if (!get(walked, a.x, a.y - 1)) {
                a.y--;
                continue;
            }
            set(failed, a.x, a.y, true);
            break;
        }
    }

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            point p(x, y);
            if (get(final_pipes, x, y)) {
                (void) thing_new("corridor2", p);
                if (random_range(0, 100) < 25) {
                    (void) thing_new("water1", p);
                }
            }
            if (get(sewer_pipe, x, y)) {
                (void) thing_new("ascend_sewer1", p);
            }
        }
    }

#if 0
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_HEIGHT; x++) {
            if (get(failed, x, y)) {
                printf("F");
            } else if (get(sewer_pipe, x, y)) {
                printf("S");
            } else if (get(final_pipes, x, y)) {
                printf("p");
            } else if (get(pipes_template, x, y)) {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
#endif

    return true;
}

void Level::create_sewer_place_walls (int variant, int block_width, int block_height, int tries)
{_
    auto tp = tp_random_sewer_wall();
    if (!tp) {
        ERR("Place walls failed");
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

                if (is_corridor(X, Y) || 
                    is_shallow_water(X, Y) || 
                    is_ascend_sewer(X, Y) || 
                    is_deep_water(X, Y)) {
                    can_place_here = false;
                    continue;
                }

                //
                // We place large blocks and avoid splatting them with
                // smaller ones here.
                //
                if (is_wall(X, Y)) {
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
                set_is_wall(X, Y);

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
                    ERR("wall tile %s not found", tilename.c_str());
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

void Level::create_sewer_place_remaining_walls (const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {

            if (is_corridor(x, y) || 
                is_shallow_water(x, y) || 
                is_ascend_sewer(x, y) || 
                is_deep_water(x, y)) {
                continue;
            }

            if (is_wall(x, y)) {
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
