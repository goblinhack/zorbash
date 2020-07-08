//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

Level::Level (void)
{_
    newptr(this, "level");
}

void Level::clear (void)
{_
    _fade_in_map = {};
    _heatmap = {};
    _is_blood = {};
    _is_chasm = {};
    _is_corpse = {};
    _is_corridor = {};
    _is_deep_water = {};
    _is_dirt = {};
    _is_door = {};
    _is_dungeon = {};
    _is_entrance = {};
    _is_exit = {};
    _is_fire = {};
    _is_floor = {};
    _is_food = {};
    _is_gold = {};
    _is_lava = {};
    _is_acid = {};
    _is_light_blocker = {};
    _is_movement_blocking = {};
    _is_monst = {};
    _is_rock = {};
    _is_smoke = {};
    _is_treasure = {};
    _is_mundane_item = {};
    _is_visited = {};
    _is_lit = {};
    _is_wall = {};
    _is_water = {};

    timestamp_dungeon_created = time_get_time_ms();
    timestamp_dungeon_saved = 0;
}

void Level::init (point3d at, int seed)
{_
    is_starting = true;
    clear();

    this->seed = seed;
    world_at = at;
    mysrand(seed);

    log("-");
    log("creating, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    while (true) {
        auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH,
                                   GRID_HEIGHT, seed);
        if (dungeon->failed) {
            seed++;
            delete dungeon;
            continue;
        }

        if (g_errored) { return; }
#if 0
        //
        // Static level
        //
        auto dungeon = new Dungeon(0);
        if (g_errored) { return; }
#endif
        auto tries = 10000;

        place_walls(dungeon, 1, 6, 6, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 2, 6, 6, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 6, 3, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 3, 6, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 3, 3, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 2, 3, 3, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 2, 2, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 2, 2, 2, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 3, 2, 2, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 2, 1, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 2, 2, 1, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 1, 1, 2, tries);
        if (g_errored) { return; }
        place_walls(dungeon, 2, 1, 2, tries);
        if (g_errored) { return; }

        for (auto d = 1; d < 3; d++) {
            int nloops = 10;
            while (nloops--) {
                auto s = "floor";

                int tries = 100;
                switch (random_range(0, 5)) {
                    case 0: place_floors(dungeon, s, d, 1, 3, 3, tries); break;
                    case 1: place_floors(dungeon, s, d, 2, 3, 3, tries); break;
                    case 2: place_floors(dungeon, s, d, 1, 2, 2, tries); break;
                    case 3: place_floors(dungeon, s, d, 2, 2, 2, tries); break;
                    case 4: place_floors(dungeon, s, d, 3, 2, 2, tries); break;
                }
            }
        }

        place_floor_under_objects(dungeon, "floor1", 1);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor2", 2);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor3", 3);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor4", 4);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor5", 5);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor6", 6);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor7", 7);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor8", 8);
        if (g_errored) { return; }
        place_floor_under_objects(dungeon, "floor9", 9);
        if (g_errored) { return; }
        place_remaining_walls(dungeon, "wall1");
        if (g_errored) { return; }
        place_remaining_floor(dungeon, "floor1");
        if (g_errored) { return; }
        place_corridor(dungeon, "corridor1", 0);
        if (g_errored) { return; }

        place_rocks(dungeon, 1, 6, 6, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 6, 3, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 3, 6, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 3, 3, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 2, 3, 3, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 2, 2, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 2, 2, 2, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 3, 2, 2, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 2, 1, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 2, 2, 1, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 1, 1, 2, tries);
        if (g_errored) { return; }
        place_rocks(dungeon, 2, 1, 2, tries);
        if (g_errored) { return; }

        place_remaining_rocks(dungeon, "rock1");
        if (g_errored) { return; }
        place_dirt(dungeon);
        if (g_errored) { return; }
        place_lava(dungeon, "lava1");
        if (g_errored) { return; }
        place_chasm(dungeon, "chasm1");
        if (g_errored) { return; }
        place_water(dungeon, "water1");
        if (g_errored) { return; }
        place_deep_water(dungeon, "deep_water1");
        if (g_errored) { return; }

        //
        // Items that have no special placement rules
        //
        place_normal_placement_rules(dungeon);
        if (g_errored) { return; }

        //
        // Place the player if we do not have one.
        //
        if (!game->level) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                for (auto y = 0; y < MAP_HEIGHT; y++) {
                    if (dungeon->is_entrance(x, y)) {
                        auto t = thing_new("player1", fpoint(x, y));

                        auto w = thing_new("sword1", fpoint(x, y));
                        t->carry(w);

                        auto b = thing_new("bag_small", fpoint(x, y));
                        t->carry(b);

                        goto placed_player;
                    }
                }
            }
        }

placed_player:
        if (g_errored) { return; }

        //
        // Scary non essential stuff
        //
        place_random_blood(dungeon);
        if (g_errored) { return; }

        //
        // Less important stuff
        //
        place_floor_deco(dungeon);
        if (g_errored) { return; }
        place_random_floor_deco(dungeon);
        if (g_errored) { return; }
        place_wall_deco(dungeon);
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
        is_starting = false;

        break;
    }
}

void Level::place_walls (Dungeonp d, int variant, int block_width,
                         int block_height, int tries)
{_
    auto tp = tp_random_wall();
    if (!tp) {
        ERR("place_walls failed");
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
            }
        }
    }
}

void Level::place_rocks (Dungeonp d, int variant, int block_width,
                         int block_height, int tries)
{_
    auto tp = tp_random_rock();
    if (!tp) {
        ERR("place_rocks failed");
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
                    ERR("rock tile %s not found", tilename.c_str());
                    return;
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

void Level::place_floors (Dungeonp d, std::string what, int depth,
                          int variant, int block_width,
                          int block_height, int tries)
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

                if (is_floor(x, y)) {
                    can_place_here = false;
                    continue;
                }

                //
                // We place large blocks and avoid splatting them with
                // smaller ones here.
                //
                if (is_floor(X, Y)) {
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
                set_is_floor(X, Y);

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

void Level::place_floor_under_objects (Dungeonp d, std::string what, int depth)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor_no_check(x, y)) {
                continue;
            }

            if (is_floor(x, y)) {
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
                d->is_treasure(x, y + 1) ||
                d->is_mundane_item(x, y + 1) ||
                d->is_potion(x, y + 1) ||
                d->is_key(x, y + 1)) {
                if (!is_floor(x, y + 1)) {
                    thing_new(what, fpoint(x, y + 1));
                }
            }
            if (d->is_monst(x, y - 1) ||
                d->is_food(x, y - 1) ||
                d->is_treasure(x, y - 1) ||
                d->is_mundane_item(x, y - 1) ||
                d->is_potion(x, y - 1) ||
                d->is_key(x, y - 1)) {
                if (!is_floor(x, y - 1)) {
                    thing_new(what, fpoint(x, y - 1));
                }
            }
            if (d->is_monst(x + 1, y) ||
                d->is_food(x + 1, y) ||
                d->is_treasure(x + 1, y) ||
                d->is_mundane_item(x + 1, y) ||
                d->is_potion(x + 1, y) ||
                d->is_key(x + 1, y)) {
                if (!is_floor(x + 1, y)) {
                    thing_new(what, fpoint(x + 1, y));
                }
            }
            if (d->is_monst(x - 1, y) ||
                d->is_food(x - 1, y) ||
                d->is_treasure(x - 1, y) ||
                d->is_mundane_item(x - 1, y) ||
                d->is_potion(x - 1, y) ||
                d->is_key(x - 1, y)) {
                if (!is_floor(x - 1, y)) {
                    thing_new(what, fpoint(x - 1, y));
                }
            }
        }
    }
}

void Level::place_normal_placement_rules (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            Tpp tp {};
            //
            // Reset the seed for each cell to increase the chances
            // of repeatability if other small things change in the
            // game
            //
            mysrand(seed + x + (y * MAP_WIDTH));

            if (d->is_blood(x, y))        { tp = tp_random_blood(); }
            if (d->is_door(x, y))         { tp = tp_random_door(); }
            if (d->is_entrance(x, y))     { tp = tp_random_entrance(); }
            if (d->is_exit(x, y))         { tp = tp_random_exit(); }
            if (d->is_food(x, y))         { tp = tp_random_food(); }
            if (d->is_gold(x, y))         { tp = tp_random_gold(); }
            if (d->is_key(x, y))          { tp = tp_random_key(); }
            if (d->is_potion(x, y))       { tp = tp_random_potion(); }
            if (d->is_monst(x, y))        { tp = tp_random_monst(); }
            if (d->is_secret_door(x, y))  { tp = tp_random_secret_door(); }
            if (d->is_generator(x, y))    { tp = tp_random_generator(); }
            if (d->is_torch(x, y))        { tp = tp_random_torch(); }
            if (d->is_treasure(x, y))     { tp = tp_random_treasure(); }
            if (d->is_mundane_item(x, y)) { tp = tp_random_mundane_item(); }
            if (tp) {
                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

void Level::place_lava (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_lava(x, y)) {
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

void Level::place_chasm (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_chasm(x, y)) {
                continue;
            }

            if (!d->is_chasm(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void Level::place_random_blood (Dungeonp d)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (is_blood(x, y)) {
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

void Level::place_water (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_water(x, y)) {
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

void Level::place_deep_water (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_deep_water(x, y)) {
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

void Level::place_floor_deco (Dungeonp d)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (!d->is_floor_deco_at(x, y)) {
                continue;
            }

            //
            // Reset the seed for each cell to increase the chances
            // of repeatability if other small things change in the
            // game
            //
            mysrand(seed + x + (y * MAP_WIDTH));

            auto tp = tp_random_deco();
            if (!tp) {
                return;
            }

            thing_new(tp->name(), fpoint(x, y));
        }
    }
}

void Level::place_random_floor_deco (Dungeonp d)
{_
    for (auto x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        for (auto y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (d->is_floor_deco_at(x, y)) {
                continue;
            }

            if (random_range(0, 100) < 95) {
                continue;
            }

            if (d->is_food(x, y)         ||
                d->is_blood(x, y)        ||
                d->is_door(x, y)         ||
                d->is_entrance(x, y)     ||
                d->is_exit(x, y)         ||
                d->is_generator(x, y)    ||
                d->is_key(x, y)          ||
                d->is_potion(x, y)       ||
                d->is_secret_door(x, y)  ||
                d->is_treasure(x, y)     ||
                d->is_mundane_item(x, y) ||
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

            //
            // Reset the seed for each cell to increase the chances
            // of repeatability if other small things change in the
            // game
            //
            mysrand(seed + x + (y * MAP_WIDTH));

            auto tp = tp_random_deco();
            if (!tp) {
                return;
            }

            thing_new(tp->name(), fpoint(x, y));
        }
    }
}

void Level::place_wall_deco (Dungeonp d)
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

            //
            // Reset the seed for each cell to increase the chances
            // of repeatability if other small things change in the
            // game
            //
            mysrand(seed + x + (y * MAP_WIDTH));

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

void Level::place_remaining_floor (Dungeonp d, const std::string &what)
{_
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
        for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }
            if (!is_floor(x, y)) {
                thing_new(what, fpoint(x, y));
            }
        }
    }
}

void Level::place_corridor (Dungeonp d, const std::string what, int depth)
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

void Level::place_dirt (Dungeonp d)
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

void Level::place_remaining_walls (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_wall(x, y)) {
                continue;
            }

            if (!d->is_wall(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void Level::place_remaining_rocks (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_rock(x, y)) {
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
void Level::game_mark_dungeon_tiles (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (d->is_floor(x, y) ||
                d->is_corridor(x, y) ||
                d->is_wall(x, y) ||
                is_floor(x, y) ||
                is_corridor(x, y)) {
                set_dungeon(x, y);
            }
        }
    }
}
