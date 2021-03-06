//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_random.h"
#include "my_room.h"
#include "my_globals.h"
#include "my_ptrcheck.h"

bool Level::create_dungeon (point3d at, int seed)
{_
    log("DUNGEON: Create dungeon at (%d,%d,%d)", at.x, at.y, at.z);
    TOPCON("Dungeon level %d is coming into being...", (at.z / 2) + 1);

    is_dungeon_level = true;

    while (true) {
        log("DUNGEON: Create dungeon");
        auto dungeon = new Dungeon(MAP_WIDTH, MAP_HEIGHT, MAP_GRID_WIDTH,
                                   MAP_GRID_HEIGHT, seed);
        if (dungeon->failed) {
            log("DUNGEON: create dungeon, failed, retry");
            seed++;
            delete dungeon;
            continue;
        }

        //
        // Check we have a dungeon start
        //
        log("DUNGEON: Look for entrance");
        {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                for (auto y = 0; y < MAP_HEIGHT; y++) {
                    if (dungeon->is_ascend_dungeon(x, y)) {
                        goto have_dungeon_start;
                    }
                }
            }
            ERR("Did not find dungeon entrance");
            return false;
        }
have_dungeon_start:

        //
        // The grid is the basis of all reality.
        //
        log("DUNGEON: Place the grid");
        place_the_grid();
        if (g_errored) { return false; }
#if 0
        //
        // Static level
        //
        auto dungeon = new Dungeon(0);
        if (g_errored) { return false; }
#endif
        auto tries = 1000;

        auto wall_type = tp_random_wall_dungeon();
        if (!wall_type) {
            DIE("No dungeon walls found");
        }

        log("DUNGEON: Place random walls");
        create_dungeon_place_walls(dungeon, wall_type, 1, 6, 6, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 2, 6, 6, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 6, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 3, 6, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 3, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 2, 3, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 2, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 3, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 2, 1, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 2, 2, 1, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 1, 1, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_walls(dungeon, wall_type, 2, 1, 2, tries);
        if (g_errored) { return false; }

        log("DUNGEON: Place random floors");
        {
            auto floor_type = random_range_inclusive(1, 11);

            int nloops = 100;
            auto s = "floor";

            while (nloops--) {
                auto tries = 20;
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 6, 6, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 6, 6, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 6, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 6, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 3, 6, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 3, 6, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 3, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 3, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 3, 3, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 4, 3, 3, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 3, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 4, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 5, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 6, 2, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 3, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 4, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 5, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 6, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 7, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 8, 2, 1, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 1, 1, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 2, 1, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 3, 1, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, 4, 1, 2, tries);
                if (g_errored) { return false; }
                create_dungeon_place_floors(dungeon, s, floor_type, random_range_inclusive(1, 38), 1, 1, tries);
                if (g_errored) { return false; }
            }

            create_dungeon_place_remaining_floor(dungeon, s + std::to_string(floor_type));
            if (g_errored) { return false; }
        }

        log("DUNGEON: Place corridors");
        create_dungeon_place_corridor(dungeon, "corridor1", 0);
        if (g_errored) { return false; }

        log("DUNGEON: Place bridges");
        create_dungeon_place_bridge(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place rocks");
        create_dungeon_place_rocks(dungeon, 1, 6, 6, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 6, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 3, 6, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 3, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 2, 3, 3, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 2, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 3, 2, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 2, 1, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 2, 2, 1, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 1, 1, 2, tries);
        if (g_errored) { return false; }
        create_dungeon_place_rocks(dungeon, 2, 1, 2, tries);
        if (g_errored) { return false; }

        log("DUNGEON: Place remaining rocks");
        create_dungeon_place_remaining_rocks(dungeon, "rock1");
        if (g_errored) { return false; }

        log("DUNGEON: Place remaining walls");
        create_dungeon_place_remaining_walls(dungeon, wall_type->name());
        if (g_errored) { return false; }

        log("DUNGEON: Place dirt");
        place_dirt(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place chasms");
        create_dungeon_place_chasm(dungeon, "chasm1");
        if (g_errored) { return false; }

        log("DUNGEON: Place deep water");
        create_dungeon_place_deep_water(dungeon, "deep_water1");
        if (g_errored) { return false; }

        log("DUNGEON: Place shallow water");
        create_dungeon_place_place_shallow_water(dungeon, "water1");
        if (g_errored) { return false; }

        log("DUNGEON: Place lava");
        create_dungeon_place_lava(dungeon, "lava1");
        if (g_errored) { return false; }

        //
        // Place braziers first and then update the heatmap
        //
        log("DUNGEON: Place braziers");
        create_dungeon_place_braziers(dungeon, "brazier1");
        if (g_errored) { return false; }

        //
        // Update the heatmap to avoid placing monsts next to lava
        //
        log("DUNGEON: Update heatmap");
        update_heatmap();

        //
        // Place the player if we do not have one.
        //
        if (!game->level) {
            log("DUNGEON: Place player");
            for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
                for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
                    if (dungeon->is_ascend_dungeon(x, y)) {
                        auto t = thing_new("player2", fpoint(x, y));

#if 0
                        auto w = thing_new("scythe", fpoint(x, y));
                        t->carry(w);
#endif

                        auto w3 = thing_new("axe_basic", fpoint(x, y));
                        t->carry(w3);

                        auto w2 = thing_new("sword_basic", fpoint(x, y));
                        t->carry(w2);

                        auto b = thing_new("bag_small", fpoint(x, y));
                        t->carry(b);

                        {
                            auto b = thing_new("bag_small", fpoint(x, y));
                            t->carry(b);
                        }

                        {
                            auto b = thing_new("food_frog", fpoint(x, y));
                            t->carry(b);
                        }

#if 0
                        {
                            auto b = thing_new("chest1", fpoint(x, y));
                            t->carry(b);
                        }

                        {
                            auto f = thing_new("enchantstone", fpoint(x, y));
                            t->carry(f);
                        }

                        {
                            auto f = thing_new("skillstone", fpoint(x, y));
                            t->carry(f);
                        }

                        {
                            auto f = thing_new("skillstone", fpoint(x, y));
                            t->carry(f);
                        }

                        {
                            auto p = thing_new("potion_health", fpoint(x, y));
                            t->carry(p);
                        }

                        {
                            auto p = thing_new("potion_health", fpoint(x, y));
                            t->carry(p);
                        }

                        {
                            auto W = thing_new("wand_descent", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("wand_energy", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("wand_lightning", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("wand_fire", fpoint(x, y));
                            t->carry(W);
                        }
#endif

                        {
                            auto W = thing_new("key", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("key", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("torch", fpoint(x, y));
                            t->carry(W);
                        }

                        {
                            auto W = thing_new("torch", fpoint(x, y));
                            t->carry(W);
                        }

#if 0
                        auto s = thing_new("skill_devoted_thrust", fpoint(x, y));
                        t->skill_add(s);
#endif

#if 0
                        {
                            auto i = thing_new("thunderstone", fpoint(x, y));
                            t->carry(i);
                        }
#endif

                        goto placed_player;
                    }
                }
            }
        }

placed_player:
        //
        // Items that have no special placement rules
        //
        log("DUNGEON: Place items");
        create_dungeon_place_objects_with_normal_placement_rules(dungeon);
        if (g_errored) { return false; }

        //
        // Scary non essential stuff
        //
        log("DUNGEON: Place blood");
        create_dungeon_place_random_blood(dungeon);
        if (g_errored) { return false; }

        //
        // Less important stuff
        //
        log("DUNGEON: Place smoke");
        create_dungeon_place_lava_smoke(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place floor deco");
        place_floor_deco(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place random floor deco");
        create_dungeon_place_random_floor_deco(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place sewer pipes");
        create_dungeon_place_sewer_pipes(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Mark dungeon tiles");
        create_dungeon_game_mark_dungeon_tiles(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place grass");
        place_dry_grass(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place foilage");
        place_foilage(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place spiderweb");
        place_spiderweb(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Place random treasure");
        place_random_treasure(dungeon);
        if (g_errored) { return false; }

        log("DUNGEON: Scroll to player");
        scroll_map_to_player();
        if (g_errored) { return false; }

        break;
    }

    log("DUNGEON: Done");
    return true;
}

void Level::create_dungeon_place_walls (Dungeonp d, Tpp tp, int variant, 
                                        int block_width, int block_height, int tries)
{_
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
                    ERR("Wall tile %s not found", tilename.c_str());
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

void Level::create_dungeon_place_rocks (Dungeonp d, int variant, 
                                        int block_width, int block_height, int tries)
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

void Level::create_dungeon_place_floors (Dungeonp d, std::string what, int floor_type,
                                         int variant, int block_width,
                                         int block_height, int tries)
{_
    while (tries--) {
        auto x = random_range(MAP_BORDER_ROCK, 
                              MAP_WIDTH - MAP_BORDER_ROCK - block_width + 1);
        auto y = random_range(MAP_BORDER_ROCK, 
                              MAP_HEIGHT - MAP_BORDER_ROCK - block_height + 1);

        //
        // Place bridges instead of floor, if we have multiple bridge
        // neighbors. This allows items to be placed on bridges.
        //
        auto bridge_count = 0;
        if ((block_width == 1) && (block_height == 1)) {
            bridge_count += d->is_bridge(x - 1, y);
            bridge_count += d->is_bridge(x + 1, y);
            bridge_count += d->is_bridge(x, y - 1);
            bridge_count += d->is_bridge(x, y + 1);
        }

        auto can_place_here = true;
        for (auto dx = 0; dx < block_width; dx++) {
            auto X = x + dx;
            for (auto dy = 0; dy < block_height; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
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

        if (bridge_count > 1) {
            if ((block_width == 1) && (block_height == 1)) {
                if (bridge_count > 2) {
                    (void) thing_new("bridge_x", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
                    (void) thing_new("bridge_ud", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
                    (void) thing_new("bridge_lr", fpoint(x, y));
                    continue;
                }
            }
        }

        auto cnt = 1;
        for (auto dy = 0; dy < block_height; dy++) {
            auto Y = y + dy;
            for (auto dx = 0; dx < block_width; dx++) {
                auto X = x + dx;
                set_is_floor(X, Y);

                auto new_thing = what + std::to_string(floor_type);
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
                    ERR("Floor tile %s not found", tilename.c_str());
                    return;
                }
                t->tile_curr = tile->global_index;
            }
        }
    }
}

void Level::create_dungeon_place_objects_with_normal_placement_rules (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            Tpp tp {};
            //
            // Reset the seed for each cell to increase the chances
            // of repeatability if other small things change in the
            // game
            //
            mysrand(seed + x + (y * MAP_WIDTH));

            point p(x, y);

            if (d->is_blood(x, y))            { tp = tp_random_blood(); }
            if (d->is_door(x, y))             { tp = tp_random_door(); }
            if (d->is_ascend_dungeon(x, y))   { tp = tp_random_ascend_dungeon(); }
            if (d->is_descend_dungeon(x, y))  { tp = tp_random_descend_dungeon(); }
            if (d->is_food(x, y))             { tp = tp_random_food(); }
            if (d->is_gold(x, y))             { tp = tp_random_gold(); }
            if (d->is_key(x, y))              { tp = tp_random_key(); }
            if (d->is_potion(x, y))           { tp = tp_random_potion(); }
            if (d->is_wand(x, y))             { tp = tp_random_wand(); }
            if (d->is_secret_door(x, y))      { tp = tp_random_secret_door(); }

            if (d->is_monst_easy(x, y)) { 
                if (random_range(0, 100) < 75) {
                    tp = tp_random_monst_easy(p);
                }
            }

            if (d->is_monst_hard(x, y)) { 
                tp = tp_random_monst_hard(p); 
            }

            //
            // If a hard monst room then always give treasure
            //
            auto r = d->getr(x, y);
            bool always_give_treasure = false;
            if (r) {
                always_give_treasure = r->contains(MAP_DEPTH_OBJ, Charmap::MONST_HARD) ||
                                       r->contains(MAP_DEPTH_WATER, Charmap::DOOR);
            }

            //
            // If surrounded by hazards then choose an ethereal generator
            //
            if (d->is_hazard(x - 1, y) &&
                d->is_hazard(x + 1, y) &&
                d->is_hazard(x, y - 1) &&
                d->is_hazard(x, y + 1) &&
                d->is_hazard(x - 1, y - 1) &&
                d->is_hazard(x + 1, y - 1) &&
                d->is_hazard(x - 1, y + 1) &&
                d->is_hazard(x + 1, y + 1)) {

                if (d->is_minion_generator_easy(x, y) || d->is_minion_generator_hard(x, y)) {
                    tp = tp_random_ethereal_minion_generator(); 
                }
            } else {
                //
                // Else choose a normal generator
                //
                if (d->is_minion_generator_easy(x, y)) {
                    if (always_give_treasure) {
                        tp = tp_random_minion_generator_easy(p); 
                    } else {
                        if (random_range(0, 100) < 50) {
                            tp = tp_random_minion_generator_easy(p); 
                        }
                    }
                } else if (d->is_minion_generator_hard(x, y)) {
                    tp = tp_random_minion_generator_hard(p); 
                }
            }

            if (d->is_barrel(x, y)) {
                tp = tp_random_barrel();
            }

            if (d->is_treasure(x, y)) { 
                if (always_give_treasure) {
                    tp = tp_random_treasure(); 
                } else {
                    if (random_range(0, 100) < 50) {
                        tp = tp_random_treasure(); 
                    }
                }
            }

            if (r && r->is_secret) {
                //
                // For secret rooms, be generous and place the good stuff first.
                // We enchant this later after placing.
                //
                if (d->is_treasure_class_a(x, y) ||
                    d->is_treasure_class_b(x, y) ||
                    d->is_treasure_class_c(x, y)) { 
                    if (random_range(0, 100) < 80) {
                        tp = tp_random_item_class_c(); 
                    } else if (random_range(0, 100) < 80) {
                        tp = tp_random_item_class_b(); 
                    } else {
                        tp = tp_random_item_class_a(); 
                    }
                }
            } else {
                if (d->is_treasure_class_a(x, y)) { 
                    if (always_give_treasure) {
                        tp = tp_random_item_class_a(); 
                    } else {
                        if (random_range(0, 100) < 50) {
                            tp = tp_random_item_class_a(); 
                        }
                    }
                }

                if (d->is_treasure_class_b(x, y)) { 
                    if (always_give_treasure) {
                        tp = tp_random_item_class_b(); 
                    } else {
                        if (random_range(0, 100) < 50) {
                            tp = tp_random_item_class_b(); 
                        }
                    }
                }

                if (d->is_treasure_class_c(x, y)) { 
                    if (always_give_treasure) {
                        tp = tp_random_item_class_c(); 
                    } else {
                        if (random_range(0, 100) < 50) {
                            tp = tp_random_item_class_c(); 
                        }
                    }
                }
            }

            if (d->is_enchantstone(x, y)) { 
                tp = tp_random_enchantstone(); 
            }

            if (d->is_skillstone(x, y)) { 
                tp = tp_random_skillstone(); 
            }

            if (!tp) {
                continue;
            }

            //
            // Don't place items where they would catch fire immediately.
            //
            if (heatmap(x, y)) {
                if (tp->is_very_combustible()) {
                    continue;
                }
            }

            if (heatmap(x, y) > 2) {
                if (tp->is_combustible()) {
                    continue;
                }
            }

            log("DUNGEON: Creating %s", tp->name().c_str());
            auto t = thing_new(tp->name(), fpoint(x, y));
            if (t) {
                if (t->is_treasure()) {
                    if (r && r->is_secret) {
                        t->enchant_randomly();
                    }
                    con("DUNGEON: Placed %s", t->short_text_capitalized().c_str());
                }
            }
        }
    }
}

void Level::create_dungeon_place_lava (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (is_lava(x, y)) {
                continue;
            }

            if (!d->is_lava(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_lava_smoke (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!is_lava(x, y)) {
                continue;
            }

            //
            // Place smoke over lava but not if next to water as it will
            // just boil off anyway
            //
            if (random_range(0, 100) < 20) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        if (is_shallow_water(x + dx, y + dy)) {
                            goto next;
                        }
                        if (is_deep_water(x + dx, y + dy)) {
                            goto next;
                        }
                    }
                }
                thing_new("smoke", fpoint(x, y));
            }
next:
            continue;
        }
    }
}

void Level::create_dungeon_place_chasm (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
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

void Level::create_dungeon_place_braziers (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (is_brazier(x, y)) {
                continue;
            }

            if (!d->is_brazier(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_random_blood (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
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

            if (random_range(0, 1000) > 20) {
                continue;
            }

            auto tp = tp_random_blood();
            (void) thing_new(tp->name(), fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_place_shallow_water (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (is_shallow_water(x, y)) {
                continue;
            }

            if (!d->is_shallow_water(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));

            if (!d->is_floor(x, y)) {
                (void) thing_new("dirt2", fpoint(x, y));
            }
        }
    }
}

void Level::create_dungeon_place_deep_water (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
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
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (!d->is_floor_deco_at(x, y)) {
                continue;
            }

            if (d->is_food(x, y)                 ||
                d->is_blood(x, y)                ||
                d->is_door(x, y)                 ||
                d->is_ascend_dungeon(x, y)       ||
                d->is_descend_dungeon(x, y)      ||
                d->is_minion_generator_any(x, y) ||
                d->is_key(x, y)                  ||
                d->is_potion(x, y)               ||
                d->is_barrel(x, y)               ||
                d->is_wand(x, y)                 ||
                d->is_secret_door(x, y)          ||
                d->is_treasure(x, y)             ||
                d->is_treasure_class_a(x, y)     ||
                d->is_treasure_class_b(x, y)     ||
                d->is_treasure_class_c(x, y)     ||
                d->is_monst_any(x, y)) {
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

void Level::create_dungeon_place_random_floor_deco (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (d->is_floor_deco_at(x, y)) {
                continue;
            }

            if (random_range(0, 100) < 99) {
                continue;
            }

            if (d->is_food(x, y)                 ||
                d->is_blood(x, y)                ||
                d->is_door(x, y)                 ||
                d->is_ascend_dungeon(x, y)       ||
                d->is_descend_dungeon(x, y)      ||
                d->is_minion_generator_any(x, y) ||
                d->is_key(x, y)                  ||
                d->is_potion(x, y)               ||
                d->is_barrel(x, y)               ||
                d->is_wand(x, y)                 ||
                d->is_secret_door(x, y)          ||
                d->is_treasure(x, y)             ||
                d->is_treasure_class_a(x, y)     ||
                d->is_treasure_class_b(x, y)     ||
                d->is_treasure_class_c(x, y)     ||
                d->is_monst_any(x, y)) {
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

            //
            // Don't place items where they would catch fire immediately.
            //
            if (heatmap(x, y)) {
                if (tp->is_very_combustible()) {
                    continue;
                }
            }

            if (heatmap(x, y) > 2) {
                if (tp->is_combustible()) {
                    continue;
                }
            }

            thing_new(tp->name(), fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_sewer_pipes (Dungeonp d)
{_
    //
    // Sometimes we have sewer pipes
    //
    auto r = random_range(0, 100);
    if (r < 80) {
        return;
    }

    int sewer_count = 0;
    int min_sewer_dist = 10;
    int sewer_count_target = 2 + random_range(0, 5);
    auto tries = 10000;

    while (sewer_count < sewer_count_target) {
redo:
        if (!tries--) {
            return;
        }

        auto x = random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
        auto y = random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

        if (d->is_wall(x, y)) {
            continue;
        }

        if (d->is_rock(x, y)) {
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

        if (d->is_ascend_dungeon(x, y) ||
            d->is_ascend_dungeon(x - 1, y) ||
            d->is_ascend_dungeon(x + 1, y) ||
            d->is_ascend_dungeon(x, y - 1) ||
            d->is_ascend_dungeon(x, y + 1) ||
            d->is_ascend_dungeon(x - 1, y - 1) ||
            d->is_ascend_dungeon(x + 1, y - 1) ||
            d->is_ascend_dungeon(x - 1, y + 1) ||
            d->is_ascend_dungeon(x + 1, y + 1)) {
            continue;
        }

        if (d->is_descend_dungeon(x, y) ||
            d->is_descend_dungeon(x - 1, y) ||
            d->is_descend_dungeon(x + 1, y) ||
            d->is_descend_dungeon(x, y - 1) ||
            d->is_descend_dungeon(x, y + 1) ||
            d->is_descend_dungeon(x - 1, y - 1) ||
            d->is_descend_dungeon(x + 1, y - 1) ||
            d->is_descend_dungeon(x - 1, y + 1) ||
            d->is_descend_dungeon(x + 1, y + 1)) {
            continue;
        }

        for (auto dx = -min_sewer_dist; dx < min_sewer_dist; dx++) {
            auto X = x + dx;
            for (auto dy = -min_sewer_dist; dy < min_sewer_dist; dy++) {
                auto Y = y + dy;

                if (d->is_oob(X, Y)) {
                    continue;
                }

                if (is_descend_sewer(X, Y)) {
                    goto redo;
                }
            }
        }

        //
        // Reset the seed for each cell to increase the chances
        // of repeatability if other small things change in the
        // game
        //
        mysrand(seed + x + (y * MAP_WIDTH));

        auto tp = tp_random_descend_sewer();
        if (!tp) {
            return;
        }

        thing_new(tp->name(), fpoint(x, y));
        sewer_count++;
    }
}

void Level::create_dungeon_place_remaining_floor (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_floor(x, y)) {
                continue;
            }

            if (is_floor(x, y)) {
                continue;
            }

            //
            // Place bridges instead of floor, if we have multiple bridge
            // neighbors. This allows items to be placed on bridges.
            //
            auto bridge_count = 0;
            bridge_count += d->is_bridge(x - 1, y);
            bridge_count += d->is_bridge(x + 1, y);
            bridge_count += d->is_bridge(x, y - 1);
            bridge_count += d->is_bridge(x, y + 1);

            if (bridge_count > 1) {
                if (bridge_count > 2) {
                    (void) thing_new("bridge_x", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
                    (void) thing_new("bridge_ud", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
                    (void) thing_new("bridge_lr", fpoint(x, y));
                    continue;
                }
            }

            thing_new(what, fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_corridor (Dungeonp d, const std::string what, int floor_type)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_corridor(x, y) &&
                !d->is_secret_corridor_at(x, y)) {
                continue;
            }

            (void) thing_new(what, fpoint(x, y));
        }
    }
}

void Level::create_dungeon_place_bridge (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (d->is_bridge(x, y)) {
                auto bridge_count = 0;
                bridge_count += d->is_bridge(x - 1, y);
                bridge_count += d->is_bridge(x + 1, y);
                bridge_count += d->is_bridge(x, y - 1);
                bridge_count += d->is_bridge(x, y + 1);

                if (bridge_count > 2) {
                    (void) thing_new("bridge_x", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x, y - 1) || d->is_bridge(x, y + 1)) {
                    (void) thing_new("bridge_ud", fpoint(x, y));
                    continue;
                }

                if (d->is_bridge(x - 1, y) || d->is_bridge(x + 1, y)) {
                    (void) thing_new("bridge_lr", fpoint(x, y));
                    continue;
                }
            }
        }
    }
}

void Level::place_dirt (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
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

void Level::place_random_treasure (Dungeonp d)
{_
    int tries = 1000;
    int treasure_max = random_range(1, 10);

    while (tries--) {
        auto x = random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK);
        auto y = random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK);

        if (d->is_dirt(x, y) || 
            d->is_deep_water(x, y) || 
            d->is_spiderweb(x, y) ||
            d->is_foilage(x, y)) {
            auto tp = tp_random_treasure();
            if (!tp) {
                return;
            }

            if (tp->is_torch()) {
                if (d->is_deep_water(x, y) ||
                    d->is_foilage(x, y)) {
                    continue;
                }
            }

            //
            // Be nice and enchant this lost treasure.
            //
            auto t = thing_new(tp->name(), fpoint(x, y));
            t->enchant_randomly();

            //
            // Double enchant swords in lakes :)
            //
            if (t->is_sword()) {
                if (d->is_deep_water(x, y)) {
                    t->enchant_randomly();
                }
            }

            if (treasure_max-- < 0) {
                return;
            }
        }
    }
}

void Level::place_dry_grass (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_anything_at(x, y) || d->is_dry_grass(x, y)) {
                auto tp = tp_random_dry_grass();
                if (!tp) {
                    return;
                }

                if (heatmap(x, y)) {
                    continue;
                }

                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

void Level::place_foilage (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_anything_at(x, y) || d->is_foilage(x, y)) {
                auto tp = tp_random_foilage();
                if (!tp) {
                    return;
                }

                if (heatmap(x, y)) {
                    continue;
                }

                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

void Level::place_spiderweb (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (!d->is_anything_at(x, y) || d->is_spiderweb(x, y)) {
                auto tp = tp_random_spiderweb();
                if (!tp) {
                    return;
                }

                if (heatmap(x, y)) {
                    continue;
                }

                (void) thing_new(tp->name(), fpoint(x, y));
            }
        }
    }
}

void Level::create_dungeon_place_remaining_walls (Dungeonp d, const std::string &what)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (is_rock(x, y) || is_wall(x, y)) {
                continue;
            }

            if (!d->is_rock(x, y) && !d->is_wall(x, y)) {
                continue;
            }

            if (random_range(0, 100) < 50) {
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

void Level::create_dungeon_place_remaining_rocks (Dungeonp d, const std::string &what)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (is_rock(x, y) || is_wall(x, y)) {
                continue;
            }

            if (!d->is_rock(x, y) && !d->is_wall(x, y)) {
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

//
// Keep track of which tiles were part of the original dungeon so we can
// display things like just the walls without all the hidden stuff like rock
//
void Level::create_dungeon_game_mark_dungeon_tiles (Dungeonp d)
{_
    for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
        for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
            if (d->is_floor(x, y)    ||
                d->is_corridor(x, y) ||
                d->is_bridge(x, y)   ||
                d->is_wall(x, y)     ||
                is_floor(x, y)       ||
                is_corridor(x, y)    ||
                is_bridge(x, y)) {
                set_is_dungeon(x, y);
            }
        }
    }
}
