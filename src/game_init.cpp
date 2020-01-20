//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

static void game_place_walls (Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    auto tp = tp_random_wall();
    auto what = tp_name(tp);

    while (tries--) {
        auto x = random_range(0, MAP_WIDTH - block_width + 1);
        auto y = random_range(0, MAP_HEIGHT - block_height + 1);

        auto can_place_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
                }

                if (!d->is_wall(X, Y)) {
                    can_place_here = false;
                    break;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (world->is_wall(X, Y)) {
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
                world->set_wall(X, Y);

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
                    DIE("wall tile %s not found", tilename.c_str());
                }

                t->tile_curr = tile->global_index;
            }
        }
    }
}

static void game_place_floors (Dungeonp d,
                               std::string what,
                               int depth,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries)
{_
    while (tries--) {
        auto x = random_range(0, MAP_WIDTH - block_width + 1);
        auto y = random_range(0, MAP_HEIGHT - block_height + 1);

        auto can_place_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
                }

                if (depth) {
                    if (depth != d->get_grid_depth_at(X, Y)) {
                        can_place_here = false;
                        continue;
                    }
                }

                if (!d->is_floor(X, Y)) {
                    can_place_here = false;
                    break;
                }

                if (world->is_floor(x, y)) {
                    can_place_here = false;
                    continue;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (world->is_floor(X, Y)) {
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
                world->set_floor(X, Y);

                auto new_thing = what + std::to_string(depth);
                auto tilename = new_thing + ".";

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

                auto t = thing_new(new_thing, fpoint(X, Y));
                auto tile = tile_find(tilename);
                if (!tile) {
                    DIE("floor tile %s not found", tilename.c_str());
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

static void game_place_rocks (Dungeonp d,
                              std::string what,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    while (tries--) {
        auto x = random_range(0, MAP_WIDTH - block_width + 1);
        auto y = random_range(0, MAP_HEIGHT - block_height + 1);

        auto can_place_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
                }

                if (!d->is_rock(X, Y)) {
                    can_place_here = false;
                    break;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (world->is_rock(X, Y)) {
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
                world->set_rock(X, Y);

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
                    DIE("rock tile %s not found", tilename.c_str());
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

static void game_place_floor_under_objects (Dungeonp d,
                                            std::string what,
                                            int depth)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (world->is_floor(x, y)) {
                continue;
            }

            if (!d->is_floor(x, y)) {
                continue;
            }

            if (depth) {
                if (depth != d->get_grid_depth_at(x, y)) {
                    continue;
                }
            }

            (void) thing_new(what, fpoint(x, y));

            if (d->is_lava(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 1.0), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 1.0), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 1.0, y), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 1.0, y), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }

            color c = CYAN;
            c.a = 50;
            double light_strength = 1.0;
            if (d->is_water(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }

            c = DARKBLUE;
            c.a = 200;
            light_strength = 2.0;
            if (d->is_deep_water(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }
        }
    }
}

static void game_place_lava (Dungeonp d,
                             std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_lava(x, y)) {
                continue;
            }

            if (!d->is_lava(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (random_range(0, 100) < 80) {
                thing_new("smoke1", fpoint(x, y), fpoint(0.5, 0.5));
            }
        }
    }
}

static void game_place_random_blood (Dungeonp d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (world->is_blood(x, y)) {
                continue;
            }

            if (d->is_floor(x, y) &&
                d->is_floor(x - 1, y) &&
                d->is_floor(x + 1, y) &&
                d->is_floor(x - 1, y - 1) &&
                d->is_floor(x + 1, y + 1)) {
                if (world->is_water(x, y)) {
                    continue;
                }

                if (world->is_deep_water(x, y)) {
                    continue;
                }

                if (world->is_lava(x, y)) {
                    continue;
                }

                if (random_range(0, 1000) > 20) {
                    continue;
                }

                int splatters = random_range(2, 10);
                for (int splatter = 0; splatter < splatters; splatter++) {
                    auto tp = tp_random_blood();
                    (void) thing_new(tp_name(tp),
                                     fpoint(x, y),
                                     fpoint(0.25, 0.25));
                }
            }
        }
    }
}

static void game_place_water (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_water(x, y)) {
                continue;
            }

            if (!d->is_water(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (!d->is_floor(x, y)) {
                (void) thing_new("dirt2", fpoint(x, y));
            }
        }
    }
}

static void game_place_deep_water (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_deep_water(x, y)) {
                continue;
            }

            if (!d->is_deep_water(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (!d->is_floor(x, y)) {
                (void) thing_new("dirt3", fpoint(x, y));
            }
        }
    }
}

static void game_place_monst (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_monst(x, y)) {
                continue;
            }

            if (!d->is_monst(x, y)) {
                continue;
            }

            auto tp = tp_random_monst();

            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_food (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_food(x, y)) {
                continue;
            }

            if (!d->is_food(x, y)) {
                continue;
            }

            auto tp = tp_random_food();
            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_blood (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_blood(x, y)) {
                continue;
            }

            if (!d->is_blood(x, y)) {
                continue;
            }

            auto tp = tp_random_blood();

            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_keys (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_key(x, y)) {
                continue;
            }

            if (!d->is_key(x, y)) {
                continue;
            }

            auto tp = tp_random_key();
            auto t = thing_new(tp_name(tp), fpoint(x, y));
            t->bounce(0.2, 1.0, 500, 99999);
        }
    }
}

static void game_place_floor_deco (Dungeonp d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (!d->is_floor(x - 1, y) ||
                !d->is_floor(x + 1, y) ||
                !d->is_floor(x, y - 1) ||
                !d->is_floor(x, y + 1) ||
                !d->is_floor(x - 1, y - 1) ||
                !d->is_floor(x + 1, y - 1) ||
                !d->is_floor(x - 1, y + 1) ||
                !d->is_floor(x + 1, y + 1)) {
                continue;
            }

            if (random_range(0, 100) < 90) {
                continue;
            }

            auto tp = tp_random_deco();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_wall_deco (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_wall(x, y)) {
                continue;
            }

            if (d->is_floor(x, y - 1)) {
                continue;
            }
            if (d->is_wall(x, y + 1)) {
                continue;
            }
            if (d->is_rock(x, y + 1)) {
                continue;
            }
            if (random_range(0, 100) < 90) {
                continue;
            }

            auto tp = tp_random_wall_deco();
            thing_new(tp_name(tp), fpoint(x, y));

            tp = tp_random_wall();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_remaining_floor (Dungeonp d, std::string what)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }
            if (!world->is_floor(x, y)) {
                thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void game_place_corridor (Dungeonp d, std::string what, int depth)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_corridor(x, y) &&
                !d->is_secret_corridor_at(x, y)) {
                continue;
            }

            if (depth) {
                if (depth != d->get_grid_depth_at(x, y)) {
                    continue;
                }
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_dirt (Dungeonp d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_anything_at(x, y) || d->is_dirt(x, y)) {
                auto tp = tp_random_dirt();
                (void) thing_new(tp_name(tp), fpoint(x, y));
            }
        }
    }
}

static void game_place_entrance (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->is_entrance_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_exit (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->is_exit_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_secret_door (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->is_secret_door(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_door (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->is_door(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_walls (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_wall(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_rocks (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (world->is_rock(x, y)) {
                continue;
            }

            if (!d->is_rock(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

//
// Keep track of which tiles were part of the original dungeon so we can
// display things like just the walls without all the hidden stuff like rock
//
static void game_mark_dungeon_tiles (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (d->is_floor(x, y) ||
                d->is_corridor(x, y) ||
                d->is_wall(x, y) ||
                world->is_floor(x, y) ||
                world->is_corridor(x, y)) {
                world->set_dungeon(x, y);
            }
        }
    }
}

void Game::init (void)
{_
    seed = 667;
    //seed = myrand();
//        world->terrain = terrain_init(seed);
//
    LOG("-");
    CON("DUNGEON: creating, seed %u", seed);
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");
_
    LOG("DUNGEON: create blocks");
    world.clear();

    mysrand(seed);
    auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH,
                               GRID_HEIGHT, seed);
    // auto dungeon = new Dungeon(0);
    game_place_entrance(dungeon, "entrance1");
    game_place_exit(dungeon, "exit1");
    game_place_door(dungeon, "door1");
    game_place_secret_door(dungeon, "secret_door1");

    auto tries = 1000;

    game_place_walls(dungeon, 1, 6, 6, tries);
    game_place_walls(dungeon, 2, 6, 6, tries);
    game_place_walls(dungeon, 1, 6, 3, tries);
    game_place_walls(dungeon, 1, 3, 6, tries);
    game_place_walls(dungeon, 1, 3, 3, tries);
    game_place_walls(dungeon, 2, 3, 3, tries);
    game_place_walls(dungeon, 3, 3, 3, tries);
    game_place_walls(dungeon, 4, 3, 3, tries);
    game_place_walls(dungeon, 1, 2, 2, tries);
    game_place_walls(dungeon, 2, 2, 2, tries);
    game_place_walls(dungeon, 1, 2, 1, tries);
    game_place_walls(dungeon, 2, 2, 1, tries);
    game_place_walls(dungeon, 3, 2, 1, tries);
    game_place_walls(dungeon, 4, 2, 1, tries);
    game_place_walls(dungeon, 1, 1, 2, tries);
    game_place_walls(dungeon, 2, 1, 2, tries);
    game_place_walls(dungeon, 3, 2, 1, tries);
    game_place_walls(dungeon, 4, 2, 1, tries);

    for (auto d = 1; d < 3; d++) {
        int nloops = 10;
        while (nloops--) {
            auto s = "floor";

            int tries = 100;
            switch (random_range(0, 5)) {
                case 0: game_place_floors(dungeon, s, d, 1, 3, 3, tries); break;
                case 1: game_place_floors(dungeon, s, d, 2, 3, 3, tries); break;
                case 2: game_place_floors(dungeon, s, d, 1, 2, 2, tries); break;
                case 3: game_place_floors(dungeon, s, d, 2, 2, 2, tries); break;
                case 4: game_place_floors(dungeon, s, d, 3, 2, 2, tries); break;
            }
        }
    }

    game_place_floor_under_objects(dungeon, "floor1", 1);
    game_place_floor_under_objects(dungeon, "floor2", 2);
    game_place_floor_under_objects(dungeon, "floor3", 3);
    game_place_floor_under_objects(dungeon, "floor4", 4);
    game_place_floor_under_objects(dungeon, "floor5", 5);
    game_place_floor_under_objects(dungeon, "floor6", 6);
    game_place_floor_under_objects(dungeon, "floor7", 7);
    game_place_floor_under_objects(dungeon, "floor8", 8);
    game_place_floor_under_objects(dungeon, "floor9", 9);
    game_place_remaining_walls(dungeon, "wall1");
    game_place_remaining_floor(dungeon, "floor1");
    game_place_corridor(dungeon, "corridor1", 0);
    game_place_floor_deco(dungeon);
    game_place_wall_deco(dungeon);
    game_place_rocks(dungeon, "rock1", 1, 6, 6, tries);
    game_place_rocks(dungeon, "rock1", 2, 6, 6, tries);
    game_place_rocks(dungeon, "rock1", 1, 6, 3, tries);
    game_place_rocks(dungeon, "rock1", 1, 3, 6, tries);
    game_place_rocks(dungeon, "rock1", 1, 3, 3, tries);
    game_place_rocks(dungeon, "rock1", 2, 3, 3, tries);
    game_place_rocks(dungeon, "rock1", 3, 3, 3, tries);
    game_place_rocks(dungeon, "rock1", 4, 3, 3, tries);
    game_place_rocks(dungeon, "rock1", 1, 2, 2, tries);
    game_place_rocks(dungeon, "rock1", 2, 2, 2, tries);
    game_place_rocks(dungeon, "rock1", 1, 2, 1, tries);
    game_place_rocks(dungeon, "rock1", 2, 2, 1, tries);
    game_place_rocks(dungeon, "rock1", 3, 2, 1, tries);
    game_place_rocks(dungeon, "rock1", 4, 2, 1, tries);
    game_place_rocks(dungeon, "rock1", 1, 1, 2, tries);
    game_place_rocks(dungeon, "rock1", 2, 1, 2, tries);
    game_place_rocks(dungeon, "rock1", 3, 2, 1, tries);
    game_place_rocks(dungeon, "rock1", 4, 2, 1, tries);
    game_place_remaining_rocks(dungeon, "rock1");
    game_place_dirt(dungeon);
    game_place_lava(dungeon, "lava1");
    game_place_water(dungeon, "water1");
    game_place_deep_water(dungeon, "deep_water1");
    //fluid_init();
CON("TODO fix place blood");
if (0) {
    game_place_random_blood(dungeon);
}

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (dungeon->is_entrance_at(x, y)) {
                auto t = thing_new("player1", fpoint(x, y));
                auto w = thing_new("sword1", fpoint(x, y));
                t->carry(w);
                game->world.cursor = thing_new("cursor", fpoint(x, y));
                game->world.map_follow_player = true;
                game->world.mouse = -1;
                game->world.mouse_old = -1;
                game->world.minimap_valid = false;
            }
        }
    }

    game_place_monst(dungeon);
    game_place_food(dungeon);
CON("TODO fix place blood");
    if (0) {
    game_place_blood(dungeon);
    }
    game_place_keys(dungeon);
    game_mark_dungeon_tiles(dungeon);

    thing_map_scroll_to_player();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: created, seed %u", seed);
    LOG("-");

    started = true;
}
