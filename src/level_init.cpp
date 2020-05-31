//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

static void level_place_walls(Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries);
static void level_place_rocks(Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries);
static void level_place_floors(Dungeonp d,
                               const std::string what,
                               int depth,
                               int variant,
                               int block_width,
                               int block_height,
                               int tries);
static void level_place_floor_under_objects(Dungeonp d,
                                            const std::string what,
                                            int depth);
static void level_place_lava(Dungeonp d, const std::string &what);
static void level_place_normal_placement_rules(Dungeonp d);
static void level_place_chasm(Dungeonp d, const std::string &what);
static void level_place_random_blood(Dungeonp d);
static void level_place_water(Dungeonp d, const std::string &what);
static void level_place_deep_water(Dungeonp d, const std::string &what);
static void level_place_floor_deco(Dungeonp d);
static void level_place_wall_deco(Dungeonp d);
static void level_place_remaining_floor(Dungeonp d, const std::string &what);
static void level_place_corridor(Dungeonp d, const std::string what, int depth);
static void level_place_dirt(Dungeonp d);
static void level_place_remaining_walls(Dungeonp d, const std::string &what);
static void level_place_remaining_rocks(Dungeonp d, const std::string &what);
static void game_mark_dungeon_tiles(Dungeonp d);

void Level::clear (void)
{_
    _is_blood = {};
    _is_chasm = {};
    _is_corpse = {};
    _is_corridor = {};
    _is_deep_water = {};
    _is_dirt = {};
    _is_door = {};
    _is_dungeon = {};
    _fade_in_map = {};
    _is_floor = {};
    _is_food = {};
    _is_large = {};
    _is_lava = {};
    _is_monst = {};
    _is_rock = {};
    _is_visited = {};
    _is_wall = {};
    _is_water = {};

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
    if (g_errored) { return; }
#if 0
    //
    // Static level
    //
    auto dungeon = new Dungeon(0);
    if (g_errored) { return; }
#endif

    auto tries = 10000;

    level_place_walls(dungeon, 1, 6, 6, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 2, 6, 6, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 6, 3, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 3, 6, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 3, 3, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 2, 3, 3, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 2, 2, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 2, 2, 2, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 3, 2, 2, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 2, 1, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 2, 2, 1, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 1, 1, 2, tries);
    if (g_errored) { return; }
    level_place_walls(dungeon, 2, 1, 2, tries);
    if (g_errored) { return; }

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
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor2", 2);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor3", 3);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor4", 4);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor5", 5);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor6", 6);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor7", 7);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor8", 8);
    if (g_errored) { return; }
    level_place_floor_under_objects(dungeon, "floor9", 9);
    if (g_errored) { return; }
    level_place_remaining_walls(dungeon, "wall1");
    if (g_errored) { return; }
    level_place_remaining_floor(dungeon, "floor1");
    if (g_errored) { return; }
    level_place_corridor(dungeon, "corridor1", 0);
    if (g_errored) { return; }

    level_place_rocks(dungeon, 1, 6, 6, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 2, 6, 6, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 6, 3, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 3, 6, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 3, 3, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 2, 3, 3, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 2, 2, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 2, 2, 2, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 3, 2, 2, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 2, 1, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 2, 2, 1, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 1, 1, 2, tries);
    if (g_errored) { return; }
    level_place_rocks(dungeon, 2, 1, 2, tries);
    if (g_errored) { return; }

    level_place_remaining_rocks(dungeon, "rock1");
    if (g_errored) { return; }
    level_place_dirt(dungeon);
    if (g_errored) { return; }
    level_place_lava(dungeon, "lava1");
    if (g_errored) { return; }
    level_place_chasm(dungeon, "chasm1");
    if (g_errored) { return; }
    level_place_water(dungeon, "water1");
    if (g_errored) { return; }
    level_place_deep_water(dungeon, "deep_water1");
    if (g_errored) { return; }

    //
    // Items that have no special placement rules
    //
    level_place_normal_placement_rules(dungeon);
    if (g_errored) { return; }

    //
    // Place the player
    //
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (dungeon->is_entrance(x, y)) {
                auto t = thing_new("player1", fpoint(x, y));
                auto w = thing_new("sword1", fpoint(x, y));
                t->carry(w);
                level->cursor = thing_new("cursor", fpoint(x, y));
                level->map_follow_player = true;
                level->mouse = -1;
                level->mouse_old = -1;
                level->minimap_valid = false;
                goto placed_player;
            }
        }
    }
placed_player:
    if (g_errored) { return; }

    //
    // Scary non essential stuff
    //
    level_place_random_blood(dungeon);
    if (g_errored) { return; }

    //
    // Less important stuff
    //
    level_place_floor_deco(dungeon);
    if (g_errored) { return; }
    level_place_wall_deco(dungeon);
    if (g_errored) { return; }
    game_mark_dungeon_tiles(dungeon);
    if (g_errored) { return; }
    scroll_map_to_player();
    if (g_errored) { return; }

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
    auto what = tp->name();

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

                if (!d->is_wall_no_check(X, Y)) {
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
                level->set_is_wall(X, Y);

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

static void level_place_rocks (Dungeonp d,
                              int variant,
                              int block_width,
                              int block_height,
                              int tries)
{_
    auto tp = tp_random_rock();
    if (!tp) {
        ERR("level_place_rocks failed");
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
                level->set_is_rock(X, Y);

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
                level->set_is_floor(X, Y);

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

static void level_place_floor_under_objects (Dungeonp d,
                                             std::string what,
                                             int depth)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor_no_check(x, y)) {
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

static void level_place_normal_placement_rules (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            Tpp tp {};

            if (d->is_entrance(x, y)) {
                tp = tp_random_entrance();
            }
            if (d->is_exit(x, y)) {
                tp = tp_random_exit();
            }
            if (d->is_monst(x, y)) {
                tp = tp_random_monst();
            }
            if (d->is_food(x, y)) {
                tp = tp_random_food();
            }
            if (d->is_blood(x, y)) {
                tp = tp_random_blood();
            }
            if (d->is_key(x, y)) {
                tp = tp_random_key();
            }
            if (d->is_torch(x, y)) {
                tp = tp_random_torch();
            }
            if (d->is_door(x, y)) {
                tp = tp_random_door();
            }
            if (d->is_secret_door(x, y)) {
                tp = tp_random_secret_door();
            }
            if (tp) {
                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

static void level_place_lava (Dungeonp d,
                              const std::string &what)
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
                thing_new("smoke1", fpoint(x, y));
            }
        }
    }
}

static void level_place_chasm (Dungeonp d,
                               const std::string &what)
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

            if (d->is_entrance(x, y) ||
                d->is_entrance(x - 1, y) ||
                d->is_entrance(x + 1, y) ||
                d->is_entrance(x, y - 1) ||
                d->is_entrance(x, y + 1) ||
                d->is_entrance(x - 1, y - 1) ||
                d->is_entrance(x + 1, y - 1) ||
                d->is_entrance(x - 1, y + 1) ||
                d->is_entrance(x + 1, y + 1)) {
                continue;
            }

            if (d->is_exit(x, y) ||
                d->is_exit(x - 1, y) ||
                d->is_exit(x + 1, y) ||
                d->is_exit(x, y - 1) ||
                d->is_exit(x, y + 1) ||
                d->is_exit(x - 1, y - 1) ||
                d->is_exit(x + 1, y - 1) ||
                d->is_exit(x - 1, y + 1) ||
                d->is_exit(x + 1, y + 1)) {
                continue;
            }

            if (d->is_exit(x, y) ||
                d->is_exit(x - 1, y) ||
                d->is_exit(x + 1, y) ||
                d->is_exit(x, y - 1) ||
                d->is_exit(x, y + 1) ||
                d->is_exit(x - 1, y - 1) ||
                d->is_exit(x + 1, y - 1) ||
                d->is_exit(x - 1, y + 1) ||
                d->is_exit(x + 1, y + 1)) {
                continue;
            }

            if (random_range(0, 1000) > 20) {
                continue;
            }

            auto tp = tp_random_blood();
            (void) thing_new(tp->name(), fpoint(x, y));
        }
    }
}

static void level_place_water (Dungeonp d, const std::string &what)
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

static void level_place_deep_water (Dungeonp d, const std::string &what)
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

            thing_new(tp->name(), fpoint(x, y));
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

            thing_new(tp->name(), fpoint(x, y));

            tp = tp_random_wall();
            thing_new(tp->name(), fpoint(x, y));
        }
    }
}

static void level_place_remaining_floor (Dungeonp d, const std::string &what)
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

static void level_place_corridor (Dungeonp d, const std::string what, int depth)
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

                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

static void level_place_remaining_walls (Dungeonp d, const std::string &what)
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

static void level_place_remaining_rocks (Dungeonp d, const std::string &what)
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
