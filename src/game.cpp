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
    game.config.movement_min_speed  = 0.008;
    game.config.movement_max_speed  = 1.000;
    game.config.movement_accel_step = 0.060;
    game.config.movement_accel_run  = 0.100;
    game.config.movement_friction   = 0.700;
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

                if (!d->is_wall_at(X, Y)) {
                    can_place_here = false;
                    break;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (game.state.map.is_wall[X][Y]) {
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
                game.state.map.is_wall[X][Y] = 1;

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

                if (!d->is_floor_at(X, Y)) {
                    can_place_here = false;
                    break;
                }

                if (game.state.map.is_floor[x][y]) {
                    can_place_here = false;
                    continue;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (game.state.map.is_floor[X][Y]) {
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
                game.state.map.is_floor[X][Y] = 1;

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

static void game_place_floor_under_objects (class Dungeon *d,
                                            std::string what,
                                            int depth)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (game.state.map.is_floor[x][y]) {
                continue;
            }

            if (!d->is_floor_at(x, y)) {
                continue;
            }

            if (depth) {
                if (depth != d->get_grid_depth_at(x, y)) {
                    continue;
                }
            }

            (void) thing_new(what, fpoint(x, y));

            if (d->is_lava_at(x, y + 1)) {
                if (!game.state.map.is_floor[x][y + 1]) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(2, fpoint(x, y + 1.0), 
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava_at(x, y - 1)) {
                if (!game.state.map.is_floor[x][y - 1]) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(2, fpoint(x, y - 1.0), 
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava_at(x + 1, y)) {
                if (!game.state.map.is_floor[x + 1][y]) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(2, fpoint(x + 1.0, y), 
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava_at(x - 1, y)) {
                if (!game.state.map.is_floor[x - 1][y]) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(2, fpoint(x - 1.0, y), 
                                     LIGHT_QUALITY_POINT, ORANGE);
                }
            }

            color c = CYAN;
            c.a = 50;
            double light_strength = 1.0;
            if (d->is_water_at(x, y + 1)) {
                if (!game.state.map.is_floor[x][y + 1]) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(light_strength, fpoint(x, y + 0.5), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water_at(x, y - 1)) {
                if (!game.state.map.is_floor[x][y - 1]) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(light_strength, fpoint(x, y - 0.5), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water_at(x + 1, y)) {
                if (!game.state.map.is_floor[x + 1][y]) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(light_strength, fpoint(x + 0.5, y), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water_at(x - 1, y)) {
                if (!game.state.map.is_floor[x - 1][y]) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(light_strength, fpoint(x - 0.5, y), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst_at(x, y + 1) ||
                d->is_key_at(x, y + 1)) {
                if (!game.state.map.is_floor[x][y + 1]) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst_at(x, y - 1) ||
                d->is_key_at(x, y - 1)) {
                if (!game.state.map.is_floor[x][y - 1]) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst_at(x + 1, y) ||
                d->is_key_at(x + 1, y)) {
                if (!game.state.map.is_floor[x + 1][y]) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst_at(x - 1, y) ||
                d->is_key_at(x - 1, y)) {
                if (!game.state.map.is_floor[x - 1][y]) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }

            c = DARKBLUE;
            c.a = 200;
            light_strength = 2.0;
            if (d->is_deep_water_at(x, y + 1)) {
                if (!game.state.map.is_floor[x][y + 1]) {
                    thing_new(what, fpoint(x, y + 1));
                    (void) light_new(light_strength, fpoint(x, y + 0.5), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water_at(x, y - 1)) {
                if (!game.state.map.is_floor[x][y - 1]) {
                    thing_new(what, fpoint(x, y - 1));
                    (void) light_new(light_strength, fpoint(x, y - 0.5), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water_at(x + 1, y)) {
                if (!game.state.map.is_floor[x + 1][y]) {
                    thing_new(what, fpoint(x + 1, y));
                    (void) light_new(light_strength, fpoint(x + 0.5, y), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water_at(x - 1, y)) {
                if (!game.state.map.is_floor[x - 1][y]) {
                    thing_new(what, fpoint(x - 1, y));
                    (void) light_new(light_strength, fpoint(x - 0.5, y), 
                                     LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst_at(x, y + 1) ||
                d->is_key_at(x, y + 1)) {
                if (!game.state.map.is_floor[x][y + 1]) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst_at(x, y - 1) ||
                d->is_key_at(x, y - 1)) {
                if (!game.state.map.is_floor[x][y - 1]) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst_at(x + 1, y) ||
                d->is_key_at(x + 1, y)) {
                if (!game.state.map.is_floor[x + 1][y]) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst_at(x - 1, y) ||
                d->is_key_at(x - 1, y)) {
                if (!game.state.map.is_floor[x - 1][y]) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }
        }
    }
}

static void game_place_lava (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_lava[x][y]) {
                continue;
            }

            if (!d->is_lava_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (random_range(0, 100) < 80) {
                thing_new("smoke1", fpoint(x, y), fpoint(2, 2));
            }
        }
    }
}

static void game_place_blood (class Dungeon *d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (game.state.map.is_blood[x][y]) {
                continue;
            }

            if (d->is_floor_at(x, y) &&
                d->is_floor_at(x - 1, y) &&
                d->is_floor_at(x + 1, y) &&
                d->is_floor_at(x - 1, y - 1) &&
                d->is_floor_at(x + 1, y + 1)) {
                if (game.state.map.is_water[x][y]) {
                    continue;
                }

                if (game.state.map.is_deep_water[x][y]) {
                    continue;
                }

                if (game.state.map.is_lava[x][y]) {
                    continue;
                }

                if (random_range(0, 1000) > 5000) {
                    continue;
                }

                int splatters = random_range(2, 10);
                for (int splatter = 0; splatter < splatters; splatter++) {
                    auto tp = tp_random_blood();
                    (void) thing_new(tp_name(tp), 
                                     fpoint(x, y),
                                     fpoint(1, 1));
                }
            }
        }
    }
}

static void game_place_water (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_water[x][y]) {
                continue;
            }

            if (!d->is_water_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (!d->is_floor_at(x, y)) {
                (void) thing_new("dirt2", fpoint(x, y));
            }
        }
    }
}

static void game_place_deep_water (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_deep_water[x][y]) {
                continue;
            }

            if (!d->is_deep_water_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (!d->is_floor_at(x, y)) {
                (void) thing_new("dirt3", fpoint(x, y));
            }
        }
    }
}

static void game_place_monsts (class Dungeon *d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_monst[x][y]) {
                continue;
            }

            if (!d->is_monst_at(x, y)) {
                continue;
            }

            auto tp = tp_random_monst();
            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_keys (class Dungeon *d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_key[x][y]) {
                continue;
            }

            if (!d->is_key_at(x, y)) {
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
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
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
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->gfx_is_wall_deco_at(x, y)) {
                continue;
            }

            if (!d->is_wall_at(x, y + 1)) {
                continue;
            }

            auto tp = tp_random_wall_deco();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void game_place_remaining_floor (class Dungeon *d,
                                        std::string what)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_floor_at(x, y)) {
                continue;
            }
            if (!game.state.map.is_floor[x][y]) {
                thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void game_place_corridor (class Dungeon *d,
                                 std::string what,
                                 int depth)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_corridor_at(x, y)) {
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
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_anything_at(x, y) || d->is_dirt_at(x, y)) {
                (void) thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void game_place_entrance (class Dungeon *d, std::string what)
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

static void game_place_exit (class Dungeon *d, std::string what)
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

static void game_place_door (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (!d->is_door_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void game_place_remaining_walls (class Dungeon *d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (game.state.map.is_wall[x][y]) {
                continue;
            }

            if (!d->is_wall_at(x, y)) {
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
//        auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH, 
//        GRID_HEIGHT, seed);
        auto dungeon = new Dungeon(0);

        LOG("dungeon: create blocks");

        memset(game.state.map.is_blood, sizeof(game.state.map.is_blood), 0);
        memset(game.state.map.is_corridor, sizeof(game.state.map.is_corridor), 0);
        memset(game.state.map.is_deep_water, sizeof(game.state.map.is_deep_water), 0);
        memset(game.state.map.is_dirt, sizeof(game.state.map.is_dirt), 0);
        memset(game.state.map.is_floor, sizeof(game.state.map.is_floor), 0);
        memset(game.state.map.is_key, sizeof(game.state.map.is_key), 0);
        memset(game.state.map.is_lava, sizeof(game.state.map.is_lava), 0);
        memset(game.state.map.is_light, sizeof(game.state.map.is_light), 0);
        memset(game.state.map.is_monst, sizeof(game.state.map.is_monst), 0);
        memset(game.state.map.is_solid, sizeof(game.state.map.is_solid), 0);
        memset(game.state.map.gfx_large_shadow_caster, sizeof(game.state.map.gfx_large_shadow_caster), 0);
        memset(game.state.map.is_door, sizeof(game.state.map.is_door), 0);
        memset(game.state.map.is_wall, sizeof(game.state.map.is_wall), 0);
        memset(game.state.map.is_water, sizeof(game.state.map.is_water), 0);

        game_place_entrance(dungeon, "entrance1");
        game_place_exit(dungeon, "exit1");
        game_place_door(dungeon, "door1");

        auto tries = 1000;
        game_place_walls(dungeon, "wall1", 1, 6, 6, tries);
        game_place_walls(dungeon, "wall1", 2, 6, 6, tries);
        game_place_walls(dungeon, "wall1", 1, 6, 3, tries);
        game_place_walls(dungeon, "wall1", 1, 3, 6, tries);
        game_place_walls(dungeon, "wall1", 1, 3, 3, tries);
        game_place_walls(dungeon, "wall1", 2, 3, 3, tries);
        game_place_walls(dungeon, "wall1", 3, 3, 3, tries);
        game_place_walls(dungeon, "wall1", 4, 3, 3, tries);
        game_place_walls(dungeon, "wall1", 1, 2, 2, tries);
        game_place_walls(dungeon, "wall1", 2, 2, 2, tries);
        game_place_walls(dungeon, "wall1", 1, 2, 1, tries);
        game_place_walls(dungeon, "wall1", 2, 2, 1, tries);
        game_place_walls(dungeon, "wall1", 3, 2, 1, tries);
        game_place_walls(dungeon, "wall1", 4, 2, 1, tries);
        game_place_walls(dungeon, "wall1", 1, 1, 2, tries);
        game_place_walls(dungeon, "wall1", 2, 1, 2, tries);
        game_place_walls(dungeon, "wall1", 3, 2, 1, tries);
        game_place_walls(dungeon, "wall1", 4, 2, 1, tries);

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
        game_place_dirt(dungeon, "dirt1");
        game_place_lava(dungeon, "lava1");
        game_place_water(dungeon, "water1");
        game_place_deep_water(dungeon, "deep_water1");
        //fluid_init();
        game_place_blood(dungeon);

        for (auto x = 0; x < MAP_WIDTH; x++) {
            for (auto y = 0; y < MAP_HEIGHT; y++) {
                if (dungeon->is_entrance_at(x, y)) {
                    auto t = thing_new("player1", fpoint(x, y));
                    auto w = tp_find("sword1");
                    t->wield(w);
                }
            }
        }

        game_place_monsts(dungeon);
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

#if 0
    if (!game.editor_mode) {
        thing_move_all();
    }
#endif
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
