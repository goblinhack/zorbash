/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_light.h"
#include "my_fluid.h"

class Game game;

void game_init (void)
{
}

void game_fini (void)
{
    LOG("finishing: destroy all things");

    while (game.state.map.all_things.size()) {
        auto iter = game.state.map.all_things.begin();
        delete iter->second;
    }
}

static void game_place_walls (class Dungeon *d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    auto tp = tp_random_wall();
    auto what = tp_name(tp);

    while (tries--) {
        auto x = random_range(0, DUN_WIDTH - block_width + 1);
        auto y = random_range(0, DUN_HEIGHT - block_height + 1);

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
                if (game.state.map.is_wall(X, Y)) {
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
                game.state.map.set_wall(X, Y);

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
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_floors (class Dungeon *d,
                               std::string what,
                               int depth,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries)
{_
    while (tries--) {
        auto x = random_range(0, DUN_WIDTH - block_width + 1);
        auto y = random_range(0, DUN_HEIGHT - block_height + 1);

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

                if (game.state.map.is_floor(x, y)) {
                    can_place_here = false;
                    continue;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (game.state.map.is_floor(X, Y)) {
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
                game.state.map.set_floor(X, Y);

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
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_rocks (class Dungeon *d,
                              std::string what,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    while (tries--) {
        auto x = random_range(0, DUN_WIDTH - block_width + 1);
        auto y = random_range(0, DUN_HEIGHT - block_height + 1);

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
                if (game.state.map.is_rock(X, Y)) {
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
                game.state.map.set_rock(X, Y);

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
                t->current_tileinfo = nullptr;
                t->current_tile = tile;
            }
        }
    }
}

static void game_place_floor_under_objects (class Dungeon *d,
                                            std::string what,
                                            int depth)
{_
    for (auto x = 1; x < DUN_WIDTH - 1; x++) {
        for (auto y = 1; y < DUN_HEIGHT - 1; y++) {
            if (game.state.map.is_floor(x, y)) {
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
                if (!game.state.map.is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(2, fpoint(x, y + 1.0),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x, y - 1)) {
                if (!game.state.map.is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(2, fpoint(x, y - 1.0),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x + 1, y)) {
                if (!game.state.map.is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(2, fpoint(x + 1.0, y),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x - 1, y)) {
                if (!game.state.map.is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(2, fpoint(x - 1.0, y),
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }

            color c = CYAN;
            c.a = 50;
            double light_strength = 1.0;
            if (d->is_water(x, y + 1)) {
                if (!game.state.map.is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(light_strength, fpoint(x, y + 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x, y - 1)) {
                if (!game.state.map.is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(light_strength, fpoint(x, y - 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x + 1, y)) {
                if (!game.state.map.is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(light_strength, fpoint(x + 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x - 1, y)) {
                if (!game.state.map.is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(light_strength, fpoint(x - 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!game.state.map.is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!game.state.map.is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!game.state.map.is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!game.state.map.is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }

            c = DARKBLUE;
            c.a = 200;
            light_strength = 2.0;
            if (d->is_deep_water(x, y + 1)) {
                if (!game.state.map.is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(light_strength, fpoint(x, y + 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x, y - 1)) {
                if (!game.state.map.is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(light_strength, fpoint(x, y - 0.5),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x + 1, y)) {
                if (!game.state.map.is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(light_strength, fpoint(x + 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x - 1, y)) {
                if (!game.state.map.is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(light_strength, fpoint(x - 0.5, y),
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!game.state.map.is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!game.state.map.is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!game.state.map.is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!game.state.map.is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }
        }
    }
}

static void game_place_lava (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_lava(x, y)) {
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

static void game_place_random_blood (class Dungeon *d)
{_
    for (auto x = 1; x < DUN_WIDTH - 1; x++) {
        for (auto y = 1; y < DUN_HEIGHT - 1; y++) {
            if (game.state.map.is_blood(x, y)) {
                continue;
            }

            if (d->is_floor(x, y) &&
                d->is_floor(x - 1, y) &&
                d->is_floor(x + 1, y) &&
                d->is_floor(x - 1, y - 1) &&
                d->is_floor(x + 1, y + 1)) {
                if (game.state.map.is_water(x, y)) {
                    continue;
                }

                if (game.state.map.is_deep_water(x, y)) {
                    continue;
                }

                if (game.state.map.is_lava(x, y)) {
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

static void game_place_water (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_water(x, y)) {
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

static void game_place_deep_water (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_deep_water(x, y)) {
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

static void game_place_monst (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_monst(x, y)) {
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

static void game_place_food (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_food(x, y)) {
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

static void game_place_blood (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_blood(x, y)) {
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

static void game_place_keys (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_key(x, y)) {
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

static void game_place_floor_deco (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (!d->gfx_is_floor_deco_at(x, y)) {
                continue;
            }

            auto tp = tp_random_deco();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_wall_deco (class Dungeon *d)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (!d->gfx_is_wall_deco_at(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y + 1)) {
                continue;
            }

            auto tp = tp_random_wall_deco();
            thing_new(tp_name(tp), fpoint(x, y));

            tp = tp_random_wall();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_remaining_floor (class Dungeon *d,
                                        std::string what)
{_
    for (auto x = 1; x < DUN_WIDTH - 1; x++) {
        for (auto y = 1; y < DUN_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }
            if (!game.state.map.is_floor(x, y)) {
                thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void game_place_corridor (class Dungeon *d,
                                 std::string what,
                                 int depth)
{_
    for (auto x = 1; x < DUN_WIDTH - 1; x++) {
        for (auto y = 1; y < DUN_HEIGHT - 1; y++) {
            if (!d->is_corridor(x, y)) {
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

static void game_place_dirt (class Dungeon *d,
                             std::string what)
{_
    for (auto x = 1; x < DUN_WIDTH - 1; x++) {
        for (auto y = 1; y < DUN_HEIGHT - 1; y++) {
            if (!d->is_anything_at(x, y) || d->is_dirt(x, y)) {
                (void) thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void game_place_entrance (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (!d->is_entrance_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_exit (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (!d->is_exit_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_door (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (!d->is_door(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_walls (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_wall(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_rocks (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < DUN_WIDTH; x++) {
        for (auto y = 0; y < DUN_HEIGHT; y++) {
            if (game.state.map.is_rock(x, y)) {
                continue;
            }

            if (!d->is_rock(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void game_display (void)
{_
    static int first = true;
    if (first) {
        tp_init_after_loading();

        int seed = 663;
        //seed = myrand();
        mysrand(seed);
        LOG("dungeon: create dungeon %u", seed);
_
        auto dungeon = new Dungeon(DUN_WIDTH, DUN_HEIGHT, GRID_WIDTH,
                                   GRID_HEIGHT, seed);
        // auto dungeon = new Dungeon(0);

        LOG("dungeon: create blocks");
        game.state.map.clear();
        game_place_entrance(dungeon, "entrance1");
        game_place_exit(dungeon, "exit1");
        game_place_door(dungeon, "door1");

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
        game_place_dirt(dungeon, "dirt1");
        game_place_lava(dungeon, "lava1");
        game_place_water(dungeon, "water1");
        game_place_deep_water(dungeon, "deep_water1");
        //fluid_init();
        game_place_random_blood(dungeon);

        for (auto x = 0; x < DUN_WIDTH; x++) {
            for (auto y = 0; y < DUN_HEIGHT; y++) {
                if (dungeon->is_entrance_at(x, y)) {
                    auto t = thing_new("player1", fpoint(x, y));
                    auto w = tp_find("sword1");
                    t->wield(w);
                }
            }
        }

        game_place_monst(dungeon);
        game_place_food(dungeon);
        game_place_blood(dungeon);
        game_place_keys(dungeon);
        lights_calculate();

        LOG("dungeon: placed all blocks");
        thing_map_scroll_to_player();
    }

    first = false;

    /*
     * thing_render_all must come before thing_move_all as it populates
     * all the things into the map for collisions.
     */
_
    thing_render_all();
    thing_gc();
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
