//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

static void level_place_walls (Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries);
static void level_place_floors(Dungeonp d,
                               std::string what,
                               int depth,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries);
static void level_place_rocks(Dungeonp d,
                              std::string what,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries);
static void level_place_floor_under_objects(Dungeonp d,
                                            std::string what,
                                            int depth);
static void level_place_lava(Dungeonp d, std::string what);
static void level_place_chasm(Dungeonp d, std::string what);
static void level_place_random_blood(Dungeonp d);
static void level_place_water(Dungeonp d, std::string what);
static void level_place_deep_water(Dungeonp d, std::string what);
static void level_place_monst(Dungeonp d);
static void level_place_food(Dungeonp d);
static void level_place_blood(Dungeonp d);
static void level_place_keys(Dungeonp d);
static void level_place_floor_deco(Dungeonp d);
static void level_place_wall_deco(Dungeonp d);
static void level_place_remaining_floor(Dungeonp d, std::string what);
static void level_place_corridor(Dungeonp d, std::string what, int depth);
static void level_place_dirt(Dungeonp d);
static void level_place_entrance(Dungeonp d, std::string what);
static void level_place_exit(Dungeonp d, std::string what);
static void level_place_secret_door(Dungeonp d, std::string what);
static void level_place_door(Dungeonp d, std::string what);
static void level_place_remaining_walls(Dungeonp d, std::string what);
static void level_place_remaining_rocks(Dungeonp d, std::string what);
static void game_mark_dungeon_tiles(Dungeonp d);

void Level::clear (void)
{_
    _is_blood = {};
    _is_corridor = {};
    _is_deep_water = {};
    _is_dirt = {};
    _is_floor = {};
    _is_lava = {};
    _is_chasm = {};
    _is_rock = {};
    _is_visited = {};
    _is_gfx_large_shadow = {};
    _is_corpse = {};
    _is_wall = {};
    _is_water = {};
    _is_dungeon = {};

    next_thing_id = 1;
    timestamp_dungeon_created = time_get_time_ms();
    timestamp_dungeon_saved = 0;
}

void Level::init (point3d at, int seed_in)
{_
    clear();

    world_at = at;
    seed = seed_in;
    seed += (at.x + 1) * (at.y + 1) * (at.z + 1);
    mysrand(seed);

    log("-");
    log("creating, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH,
                               GRID_HEIGHT, seed);
    if (errored) { return; }
    // auto dungeon = new Dungeon(0);
    level_place_entrance(dungeon, "entrance1");
    if (errored) { return; }
    level_place_exit(dungeon, "exit1");
    if (errored) { return; }
    level_place_door(dungeon, "door1");
    if (errored) { return; }
    level_place_secret_door(dungeon, "secret_door1");
    if (errored) { return; }

    auto tries = 1000;

    level_place_walls(dungeon, 1, 6, 6, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 2, 6, 6, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 6, 3, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 3, 6, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 3, 3, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 2, 3, 3, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 3, 3, 3, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 4, 3, 3, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 2, 2, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 2, 2, 2, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 2, 1, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 2, 2, 1, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 3, 2, 1, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 4, 2, 1, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 1, 1, 2, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 2, 1, 2, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 3, 2, 1, tries);
    if (errored) { return; }
    level_place_walls(dungeon, 4, 2, 1, tries);
    if (errored) { return; }

    for (auto d = 1; d < 3; d++) {
        int nloops = 10;
        while (nloops--) {
            auto s = "floor";

            int tries = 100;
            switch (random_range(0, 5)) {
                case 0: level_place_floors(dungeon, s, d, 1, 3, 3, tries); break;
                case 1: level_place_floors(dungeon, s, d, 2, 3, 3, tries); break;
                case 2: level_place_floors(dungeon, s, d, 1, 2, 2, tries); break;
                case 3: level_place_floors(dungeon, s, d, 2, 2, 2, tries); break;
                case 4: level_place_floors(dungeon, s, d, 3, 2, 2, tries); break;
            }
        }
    }

    level_place_floor_under_objects(dungeon, "floor1", 1);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor2", 2);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor3", 3);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor4", 4);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor5", 5);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor6", 6);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor7", 7);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor8", 8);
    if (errored) { return; }
    level_place_floor_under_objects(dungeon, "floor9", 9);
    if (errored) { return; }
    level_place_remaining_walls(dungeon, "wall1");
    if (errored) { return; }
    level_place_remaining_floor(dungeon, "floor1");
    if (errored) { return; }
    level_place_corridor(dungeon, "corridor1", 0);
    if (errored) { return; }
    level_place_floor_deco(dungeon);
    if (errored) { return; }
    level_place_wall_deco(dungeon);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 6, 6, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 2, 6, 6, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 6, 3, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 3, 6, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 3, 3, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 2, 3, 3, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 3, 3, 3, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 4, 3, 3, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 2, 2, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 2, 2, 2, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 2, 1, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 2, 2, 1, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 3, 2, 1, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 4, 2, 1, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 1, 1, 2, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 2, 1, 2, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 3, 2, 1, tries);
    if (errored) { return; }
    level_place_rocks(dungeon, "rock1", 4, 2, 1, tries);
    if (errored) { return; }
    level_place_remaining_rocks(dungeon, "rock1");
    if (errored) { return; }
    level_place_dirt(dungeon);
    if (errored) { return; }
    level_place_lava(dungeon, "lava1");
    if (errored) { return; }
    level_place_chasm(dungeon, "chasm1");
    if (errored) { return; }
    level_place_water(dungeon, "water1");
    if (errored) { return; }
    level_place_deep_water(dungeon, "deep_water1");
    if (errored) { return; }
    //fluid_init();
    level_place_random_blood(dungeon);

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (dungeon->is_entrance_at(x, y)) {
                auto t = thing_new("player1", fpoint(x, y));
                auto w = thing_new("sword1", fpoint(x, y));
                t->carry(w);
                level->cursor = thing_new("cursor", fpoint(x, y));
                level->map_follow_player = true;
                level->mouse = -1;
                level->mouse_old = -1;
                level->minimap_valid = false;
            }
        }
    }
    if (errored) { return; }

    level_place_monst(dungeon);
    if (errored) { return; }
    level_place_food(dungeon);
    if (errored) { return; }
    level_place_blood(dungeon);
    if (errored) { return; }
    level_place_keys(dungeon);
    if (errored) { return; }
    game_mark_dungeon_tiles(dungeon);
    if (errored) { return; }

    thing_map_scroll_to_player();
    if (errored) { return; }

    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("created, seed %u", seed);
    log("-");

    update_map();
    game->started = true;
}

static void level_place_walls (Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    auto tp = tp_random_wall();
    if (!tp) {
        ERR("level_place_walls failed");
        return;
    }
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
                if (level->is_wall(X, Y)) {
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
                level->set_wall(X, Y);

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
            }
        }
    }
}

static void level_place_floors (Dungeonp d,
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

                if (level->is_floor(x, y)) {
                    can_place_here = false;
                    continue;
                }

                /*
                 * We place large blocks and avoid splatting them with
                 * smaller ones here.
                 */
                if (level->is_floor(X, Y)) {
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
                level->set_floor(X, Y);

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
                    ERR("floor tile %s not found", tilename.c_str());
                    return;
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

static void level_place_rocks (Dungeonp d,
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
                if (level->is_rock(X, Y)) {
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
                level->set_rock(X, Y);

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
                    ERR("rock tile %s not found", tilename.c_str());
                    return;
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

static void level_place_floor_under_objects (Dungeonp d,
                                            std::string what,
                                            int depth)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor_fast(x, y)) {
                continue;
            }

            if (level->is_floor(x, y)) {
                continue;
            }

            if (depth) {
                if (depth != d->get_grid_depth_at(x, y)) {
                    continue;
                }
            }

            (void) thing_new(what, fpoint(x, y));

            if (d->is_lava(x, y + 1)) {
                if (!level->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 1.0), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x, y - 1)) {
                if (!level->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 1.0), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x + 1, y)) {
                if (!level->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 1.0, y), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }
            if (d->is_lava(x - 1, y)) {
                if (!level->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 1.0, y), 2,
                                 LIGHT_QUALITY_POINT, ORANGE);
                }
            }

            color c = CYAN;
            c.a = 50;
            double light_strength = 1.0;
            if (d->is_water(x, y + 1)) {
                if (!level->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x, y - 1)) {
                if (!level->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x + 1, y)) {
                if (!level->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_water(x - 1, y)) {
                if (!level->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!level->is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!level->is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!level->is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!level->is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }

            c = DARKBLUE;
            c.a = 200;
            light_strength = 2.0;
            if (d->is_deep_water(x, y + 1)) {
                if (!level->is_floor(x, y + 1)) {
                    auto n = thing_new(what, fpoint(x, y + 1));
                    n->new_light(fpoint(x, y + 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x, y - 1)) {
                if (!level->is_floor(x, y - 1)) {
                    auto n = thing_new(what, fpoint(x, y - 1));
                    n->new_light(fpoint(x, y - 0.5),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x + 1, y)) {
                if (!level->is_floor(x + 1, y)) {
                    auto n = thing_new(what, fpoint(x + 1, y));
                    n->new_light(fpoint(x + 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }
            if (d->is_deep_water(x - 1, y)) {
                if (!level->is_floor(x - 1, y)) {
                    auto n = thing_new(what, fpoint(x - 1, y));
                    n->new_light(fpoint(x - 0.5, y),
                                 light_strength, LIGHT_QUALITY_POINT, c);
                }
            }

            if (d->is_monst(x, y + 1) ||
                d->is_food(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!level->is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!level->is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!level->is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!level->is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }
        }
    }
}

static void level_place_lava (Dungeonp d,
                             std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_lava(x, y)) {
                continue;
            }

            if (!d->is_lava(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (random_range(0, 100) < 20) {
                thing_new("smoke1", fpoint(x, y), fpoint(0.5, 0.5));
            }
        }
    }
}

static void level_place_chasm (Dungeonp d,
                              std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_chasm(x, y)) {
                continue;
            }

            if (!d->is_chasm(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (random_range(0, 1000) < 10) {
                thing_new("smoke1", fpoint(x, y), fpoint(0.5, 0.5));
            }
        }
    }
}

static void level_place_random_blood (Dungeonp d)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (level->is_blood(x, y)) {
                continue;
            }

            if (!d->is_floor(x, y) ||
                !d->is_floor(x - 1, y) ||
                !d->is_floor(x + 1, y) ||
                !d->is_floor(x, y - 1) ||
                !d->is_floor(x, y + 1) ||
                !d->is_floor(x - 1, y - 1) ||
                !d->is_floor(x + 1, y - 1) ||
                !d->is_floor(x - 1, y + 1) ||
                !d->is_floor(x + 1, y + 1)) {
                continue;
            }

            if (d->is_hazard(x, y) ||
                d->is_hazard(x - 1, y) ||
                d->is_hazard(x + 1, y) ||
                d->is_hazard(x, y - 1) ||
                d->is_hazard(x, y + 1) ||
                d->is_hazard(x - 1, y - 1) ||
                d->is_hazard(x + 1, y - 1) ||
                d->is_hazard(x - 1, y + 1) ||
                d->is_hazard(x + 1, y + 1)) {
                continue;
            }

            if (random_range(0, 1000) > 20) {
                continue;
            }

            int splatters = random_range(2, 10);
            for (int splatter = 0; splatter < splatters; splatter++) {
                auto tp = tp_random_blood();
                if (!tp) {
                    return;
                }
                (void) thing_new(tp_name(tp),
                                 fpoint(x, y),
                                 fpoint(0.25, 0.25));
            }
        }
    }
}

static void level_place_water (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_water(x, y)) {
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

static void level_place_deep_water (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_deep_water(x, y)) {
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

static void level_place_monst (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_monst(x, y)) {
                continue;
            }

            if (!d->is_monst(x, y)) {
                continue;
            }

            auto tp = tp_random_monst();
            if (!tp) {
                return;
            }

            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void level_place_food (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_food(x, y)) {
                continue;
            }

            if (!d->is_food(x, y)) {
                continue;
            }

            auto tp = tp_random_food();
            if (!tp) {
                return;
            }

            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void level_place_blood (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_blood(x, y)) {
                continue;
            }

            if (!d->is_blood(x, y)) {
                continue;
            }

            if (d->is_hazard(x, y) ||
                d->is_hazard(x - 1, y) ||
                d->is_hazard(x + 1, y) ||
                d->is_hazard(x, y - 1) ||
                d->is_hazard(x, y + 1) ||
                d->is_hazard(x - 1, y - 1) ||
                d->is_hazard(x + 1, y - 1) ||
                d->is_hazard(x - 1, y + 1) ||
                d->is_hazard(x + 1, y + 1)) {
                continue;
            }

            auto tp = tp_random_blood();
            if (!tp) {
                return;
            }

            (void) thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void level_place_keys (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_key(x, y)) {
                continue;
            }

            if (!d->is_key(x, y)) {
                continue;
            }

            auto tp = tp_random_key();
            if (!tp) {
                return;
            }

            auto t = thing_new(tp_name(tp), fpoint(x, y));
            t->bounce(0.2, 1.0, 500, 99999);
        }
    }
}

static void level_place_floor_deco (Dungeonp d)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (random_range(0, 100) < 95) {
                continue;
            }

            if (d->is_food(x, y)        ||
                d->is_door(x, y)        ||
                d->is_key(x, y)         ||
                d->is_blood(x, y)       ||
                d->is_secret_door(x, y) ||
                d->is_monst(x, y)) {
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

            if (d->is_hazard(x, y) ||
                d->is_hazard(x - 1, y) ||
                d->is_hazard(x + 1, y) ||
                d->is_hazard(x, y - 1) ||
                d->is_hazard(x, y + 1) ||
                d->is_hazard(x - 1, y - 1) ||
                d->is_hazard(x + 1, y - 1) ||
                d->is_hazard(x - 1, y + 1) ||
                d->is_hazard(x + 1, y + 1)) {
                continue;
            }

            auto tp = tp_random_deco();
            if (!tp) {
                return;
            }

            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void level_place_wall_deco (Dungeonp d)
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
            if (!tp) {
                return;
            }

            thing_new(tp_name(tp), fpoint(x, y));

            tp = tp_random_wall();
            thing_new(tp_name(tp), fpoint(x, y));
        }
    }
}

static void level_place_remaining_floor (Dungeonp d, std::string what)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }
            if (!level->is_floor(x, y)) {
                thing_new(what, fpoint(x, y));
            }
        }
    }
}

static void level_place_corridor (Dungeonp d, std::string what, int depth)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
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

static void level_place_dirt (Dungeonp d)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_anything_at(x, y) || d->is_dirt(x, y)) {
                auto tp = tp_random_dirt();
                if (!tp) {
                    return;
                }

                (void) thing_new(tp_name(tp), fpoint(x, y));
            }
        }
    }
}

static void level_place_entrance (Dungeonp d, std::string what)
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

static void level_place_exit (Dungeonp d, std::string what)
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

static void level_place_secret_door (Dungeonp d, std::string what)
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

static void level_place_door (Dungeonp d, std::string what)
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

static void level_place_remaining_walls (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_wall(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

static void level_place_remaining_rocks (Dungeonp d, std::string what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (level->is_rock(x, y)) {
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
                level->is_floor(x, y) ||
                level->is_corridor(x, y)) {
                level->set_dungeon(x, y);
            }
        }
    }
}
