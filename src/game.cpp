/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

class Game game;

void game_init (void)
{
}

void game_fini (void)
{
    LOG("finishing: destroy all things");

    //
    // Do we need this?
    // 
    //while (world->all_things.size()) {
    //    auto iter = world->all_things.begin();
    //    delete iter->second;
    //}
}

static void game_place_walls (Worldp world,
                              Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    auto tp = tp_random_wall();
    auto what = tp_name(tp);

    while (tries--) {
        auto x = random_range(0, CHUNK_WIDTH - block_width + 1);
        auto y = random_range(0, CHUNK_HEIGHT - block_height + 1);

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

                auto t = thing_new(world, what, fpoint(X, Y));
                auto tile = tile_find(tilename);
                if (!tile) {
                    DIE("wall tile %s not found", tilename.c_str());
                }
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_floors (Worldp world,
                               Dungeonp d,
                               std::string what,
                               int depth,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries)
{_
    while (tries--) {
        auto x = random_range(0, CHUNK_WIDTH - block_width + 1);
        auto y = random_range(0, CHUNK_HEIGHT - block_height + 1);

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

                auto t = thing_new(world, new_thing, fpoint(X, Y));
                auto tile = tile_find(tilename);
                if (!tile) {
                    DIE("floor tile %s not found", tilename.c_str());
                }
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_rocks (Worldp world,
                              Dungeonp d,
                              std::string what,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    while (tries--) {
        auto x = random_range(0, CHUNK_WIDTH - block_width + 1);
        auto y = random_range(0, CHUNK_HEIGHT - block_height + 1);

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

                auto t = thing_new(world, what, fpoint(X, Y));
                auto tile = tile_find(tilename);
                if (!tile) {
                    DIE("rock tile %s not found", tilename.c_str());
                }
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_floor_under_objects (Worldp world,
                                            Dungeonp d,
                                            std::string what,
                                            int depth)
{_
    for (auto x = 1; x < CHUNK_WIDTH - 1; x++) {
        for (auto y = 1; y < CHUNK_HEIGHT - 1; y++) {
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

            (void) thing_new(world, what, fpoint(x, y));

            if (d->is_lava(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(world, what, fpoint(x, y + 1));
                    (void) light_new(world, 2, fpoint(x, y + 1.0),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(world, what, fpoint(x, y - 1));
                    (void) light_new(world, 2, fpoint(x, y - 1.0),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(world, what, fpoint(x + 1, y));
                    (void) light_new(world, 2, fpoint(x + 1.0, y),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(world, what, fpoint(x - 1, y));
                    (void) light_new(world, 2, fpoint(x - 1.0, y),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }

            color c = CYAN;
            c.a = 50;
            double light_strength = 1.0;
            if (d->is_water(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(world, what, fpoint(x, y + 1));
                    (void) light_new(world, light_strength, fpoint(x, y + 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(world, what, fpoint(x, y - 1));
                    (void) light_new(world, light_strength, fpoint(x, y - 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(world, what, fpoint(x + 1, y));
                    (void) light_new(world, light_strength, fpoint(x + 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(world, what, fpoint(x - 1, y));
                    (void) light_new(world, light_strength, fpoint(x - 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(world, what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(world, what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(world, what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(world, what, fpoint(x - 1, y));
                }
            }

            c = DARKBLUE;
            c.a = 200;
            light_strength = 2.0;
            if (d->is_deep_water(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(world, what, fpoint(x, y + 1));
                    (void) light_new(world, light_strength, fpoint(x, y + 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(world, what, fpoint(x, y - 1));
                    (void) light_new(world, light_strength, fpoint(x, y - 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(world, what, fpoint(x + 1, y));
                    (void) light_new(world, light_strength, fpoint(x + 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(world, what, fpoint(x - 1, y));
                    (void) light_new(world, light_strength, fpoint(x - 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!world->is_floor(x, y + 1)) {
                    thing_new(world, what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!world->is_floor(x, y - 1)) {
                    thing_new(world, what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!world->is_floor(x + 1, y)) {
                    thing_new(world, what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!world->is_floor(x - 1, y)) {
                    thing_new(world, what, fpoint(x - 1, y));
                }
            }
        }
    }
}

static void game_place_lava (Worldp world,
                             Dungeonp d, 
                             std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_lava(x, y)) {
                continue;
            }

            if (!d->is_lava(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));

            if (random_range(0, 100) < 80) {
                thing_new(world, "smoke1", fpoint(x, y), fpoint(0.5, 0.5));
            }
        }
    }
}

static void game_place_random_blood (Worldp world, Dungeonp d)
{_
    for (auto x = 1; x < CHUNK_WIDTH - 1; x++) {
        for (auto y = 1; y < CHUNK_HEIGHT - 1; y++) {
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
                    (void) thing_new(world, tp_name(tp),
                                     fpoint(x, y),
                                     fpoint(0.25, 0.25));
                }
            }
        }
    }
}

static void game_place_water (Worldp world, Dungeonp d, std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_water(x, y)) {
                continue;
            }

            if (!d->is_water(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));

            if (!d->is_floor(x, y)) {
                (void) thing_new(world, "dirt2", fpoint(x, y));
            }
        }
    }
}

static void game_place_deep_water (Worldp world, Dungeonp d, 
                                   std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_deep_water(x, y)) {
                continue;
            }

            if (!d->is_deep_water(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));

            if (!d->is_floor(x, y)) {
                (void) thing_new(world, "dirt3", fpoint(x, y));
            }
        }
    }
}

static void game_place_monst (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_monst(x, y)) {
                continue;
            }

            if (!d->is_monst(x, y)) {
                continue;
            }

            auto tp = tp_random_monst();

            (void) thing_new(world, tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_food (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_food(x, y)) {
                continue;
            }

            if (!d->is_food(x, y)) {
                continue;
            }

            auto tp = tp_random_food();
            (void) thing_new(world, tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_blood (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_blood(x, y)) {
                continue;
            }

            if (!d->is_blood(x, y)) {
                continue;
            }

            auto tp = tp_random_blood();

            (void) thing_new(world, tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_keys (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_key(x, y)) {
                continue;
            }

            if (!d->is_key(x, y)) {
                continue;
            }

            auto tp = tp_random_key();
            auto t = thing_new(world, tp_name(tp), fpoint(x, y));
            t->bounce(0.2, 1.0, 500, 99999);
        }
    }
}

static void game_place_floor_deco (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (!d->gfx_is_floor_deco_at(x, y)) {
                continue;
            }

            auto tp = tp_random_deco();
            thing_new(world, tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_wall_deco (Worldp world, Dungeonp d)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (!d->gfx_is_wall_deco_at(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y + 1)) {
                continue;
            }

            auto tp = tp_random_wall_deco();
            thing_new(world, tp_name(tp), fpoint(x, y));

            tp = tp_random_wall();
            thing_new(world, tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_remaining_floor (Worldp world, Dungeonp d,
                                        std::string what)
{_
    for (auto x = 1; x < CHUNK_WIDTH - 1; x++) {
        for (auto y = 1; y < CHUNK_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }
            if (!world->is_floor(x, y)) {
                thing_new(world, what, fpoint(x, y));
            }
        }
    }
}

static void game_place_corridor (Worldp world, Dungeonp d,
                                 std::string what, int depth)
{_
    for (auto x = 1; x < CHUNK_WIDTH - 1; x++) {
        for (auto y = 1; y < CHUNK_HEIGHT - 1; y++) {
            if (!d->is_corridor(x, y)) {
                continue;
            }

            if (depth) {
                if (depth != d->get_grid_depth_at(x, y)) {
                    continue;
                }
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

static void game_place_dirt (Worldp world, Dungeonp d)
{_
    for (auto x = 1; x < CHUNK_WIDTH - 1; x++) {
        for (auto y = 1; y < CHUNK_HEIGHT - 1; y++) {
            if (!d->is_anything_at(x, y) || d->is_dirt(x, y)) {
                auto tp = tp_random_dirt();
                (void) thing_new(world, tp_name(tp), fpoint(x, y));
            }
        }
    }
}

static void game_place_grass (Worldp world, Dungeonp d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!world->is_anything_at(x, y)) {
                if (random_range(0, 100) < 10) {
                    auto tp = tp_random_grass();
                    (void) thing_new(world, tp_name(tp), fpoint(x, y));
                } else if (random_range(0, 100) < 10) {
                    auto tp = tp_random_soil();
                    (void) thing_new(world, tp_name(tp), fpoint(x, y));
                } else {
                    (void) thing_new(world, "water1", fpoint(x, y));
                }
            }
        }
    }
}

static void game_place_entrance (Worldp world, Dungeonp d, std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (!d->is_entrance_at(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

static void game_place_exit (Worldp world, Dungeonp d, std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (!d->is_exit_at(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

static void game_place_door (Worldp world, Dungeonp d, std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (!d->is_door(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_walls (Worldp world, Dungeonp d, 
                                        std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_wall(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_rocks (Worldp world, Dungeonp d, 
                                        std::string what)
{_
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT; y++) {
            if (world->is_rock(x, y)) {
                continue;
            }

            if (!d->is_rock(x, y)) {
                continue;
            }

            (void) thing_new(world, what, fpoint(x, y));
        }
    }
}

void game_init_chunk (Worldp world, point c)
{_
// XXX
    if (world->chunk_inited[c.x][c.y]) {
        return;
    }
    world->chunk_inited[c.x][c.y] = true;
#if 0
#endif
}

void game_display (Worldp world)
{_
    static int first = true;
    if (first) {
        tp_init_after_loading();

        int seed = 667;
        //seed = myrand();
//        world->terrain = terrain_init(seed);
        mysrand(seed);
        LOG("dungeon: create dungeon %u", seed);
_
        auto dungeon = new Dungeon(CHUNK_WIDTH, CHUNK_HEIGHT, GRID_WIDTH,
                                   GRID_HEIGHT, seed);
        // auto dungeon = new Dungeon(0);

        LOG("dungeon: create blocks");
        world->clear();
        game_place_entrance(world, dungeon, "entrance1");
        game_place_exit(world, dungeon, "exit1");
        game_place_door(world, dungeon, "door1");

        auto tries = 1000;

        game_place_walls(world, dungeon, 1, 6, 6, tries);
        game_place_walls(world, dungeon, 2, 6, 6, tries);
        game_place_walls(world, dungeon, 1, 6, 3, tries);
        game_place_walls(world, dungeon, 1, 3, 6, tries);
        game_place_walls(world, dungeon, 1, 3, 3, tries);
        game_place_walls(world, dungeon, 2, 3, 3, tries);
        game_place_walls(world, dungeon, 3, 3, 3, tries);
        game_place_walls(world, dungeon, 4, 3, 3, tries);
        game_place_walls(world, dungeon, 1, 2, 2, tries);
        game_place_walls(world, dungeon, 2, 2, 2, tries);
        game_place_walls(world, dungeon, 1, 2, 1, tries);
        game_place_walls(world, dungeon, 2, 2, 1, tries);
        game_place_walls(world, dungeon, 3, 2, 1, tries);
        game_place_walls(world, dungeon, 4, 2, 1, tries);
        game_place_walls(world, dungeon, 1, 1, 2, tries);
        game_place_walls(world, dungeon, 2, 1, 2, tries);
        game_place_walls(world, dungeon, 3, 2, 1, tries);
        game_place_walls(world, dungeon, 4, 2, 1, tries);

        for (auto d = 1; d < 3; d++) {
            int nloops = 10;
            while (nloops--) {
                auto s = "floor";

                int tries = 100;
                switch (random_range(0, 5)) {
                    case 0: game_place_floors(world, dungeon, s, d, 1, 3, 3, tries); break;
                    case 1: game_place_floors(world, dungeon, s, d, 2, 3, 3, tries); break;
                    case 2: game_place_floors(world, dungeon, s, d, 1, 2, 2, tries); break;
                    case 3: game_place_floors(world, dungeon, s, d, 2, 2, 2, tries); break;
                    case 4: game_place_floors(world, dungeon, s, d, 3, 2, 2, tries); break;
                }
            }
        }

        game_place_floor_under_objects(world, dungeon, "floor1", 1);
        game_place_floor_under_objects(world, dungeon, "floor2", 2);
        game_place_floor_under_objects(world, dungeon, "floor3", 3);
        game_place_floor_under_objects(world, dungeon, "floor4", 4);
        game_place_floor_under_objects(world, dungeon, "floor5", 5);
        game_place_floor_under_objects(world, dungeon, "floor6", 6);
        game_place_floor_under_objects(world, dungeon, "floor7", 7);
        game_place_floor_under_objects(world, dungeon, "floor8", 8);
        game_place_floor_under_objects(world, dungeon, "floor9", 9);
        game_place_remaining_walls(world, dungeon, "wall1");
        game_place_remaining_floor(world, dungeon, "floor1");
        game_place_corridor(world, dungeon, "corridor1", 0);
        game_place_floor_deco(world, dungeon);
        game_place_wall_deco(world, dungeon);
        game_place_rocks(world, dungeon, "rock1", 1, 6, 6, tries);
        game_place_rocks(world, dungeon, "rock1", 2, 6, 6, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 6, 3, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 3, 6, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 3, 3, tries);
        game_place_rocks(world, dungeon, "rock1", 2, 3, 3, tries);
        game_place_rocks(world, dungeon, "rock1", 3, 3, 3, tries);
        game_place_rocks(world, dungeon, "rock1", 4, 3, 3, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 2, 2, tries);
        game_place_rocks(world, dungeon, "rock1", 2, 2, 2, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 2, 1, tries);
        game_place_rocks(world, dungeon, "rock1", 2, 2, 1, tries);
        game_place_rocks(world, dungeon, "rock1", 3, 2, 1, tries);
        game_place_rocks(world, dungeon, "rock1", 4, 2, 1, tries);
        game_place_rocks(world, dungeon, "rock1", 1, 1, 2, tries);
        game_place_rocks(world, dungeon, "rock1", 2, 1, 2, tries);
        game_place_rocks(world, dungeon, "rock1", 3, 2, 1, tries);
        game_place_rocks(world, dungeon, "rock1", 4, 2, 1, tries);
        game_place_remaining_rocks(world, dungeon, "rock1");
        game_place_dirt(world, dungeon);
        game_place_lava(world, dungeon, "lava1");
        game_place_water(world, dungeon, "water1");
        game_place_deep_water(world, dungeon, "deep_water1");
        //fluid_init();
        game_place_random_blood(world, dungeon);
        game_place_grass(world, dungeon);

        for (auto x = 0; x < CHUNK_WIDTH; x++) {
            for (auto y = 0; y < CHUNK_HEIGHT; y++) {
                if (dungeon->is_entrance_at(x, y)) {
                    auto t = thing_new(world, "player1", fpoint(x, y));
                    auto w = tp_find("sword1");
                    t->wield(w);
                }
            }
        }

        game_place_monst(world, dungeon);
        game_place_food(world, dungeon);
        game_place_blood(world, dungeon);
        game_place_keys(world, dungeon);
        lights_calculate(world);

        LOG("dungeon: placed all blocks");
        thing_map_scroll_to_player(world);
    }

    first = false;

    /*
     * thing_render_all must come before thing_move_all as it populates
     * all the things into the map for collisions.
     */
    thing_render_all(world);
    thing_gc(world);
}

uint8_t
game_mouse_motion (int32_t x, int32_t y,
                   int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
    return (false);
}

void
game_mouse_over (int32_t x, int32_t y,
                 int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
}

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
CON("TBD %s", __FUNCTION__);
    return (false);
}

uint8_t
game_key_down (const struct SDL_KEYSYM *key)
{_
    return (false);
}
