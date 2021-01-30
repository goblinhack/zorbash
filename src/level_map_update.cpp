//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_random.h"

void Level::update_hazard_tile_map (void)
{
    //
    // The water tiles are twice the size of normal tiles, so work out
    // where to draw them to avoid overlaps
    //
    lava_tile_map = {};
    chasm_tile_map = {};
    water_tile_map = {};
    deep_water_tile_map = {};

    for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
        for (auto x = 2; x < MAP_WIDTH - 2; x++) {
            if (is_shallow_water(x, y) || is_deep_water(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        incr(water_tile_map, x+dx, y+dy, (uint8_t)1);
                        if (is_deep_water(x, y)) {
                            incr(deep_water_tile_map, x+dx, y+dy, (uint8_t)1);
                        }
                    }
                }
            }

            if (is_lava(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        incr(lava_tile_map, x+dx, y+dy, (uint8_t)1);
                    }
                }
            }

            if (is_chasm(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        incr(chasm_tile_map, x+dx, y+dy, (uint8_t)1);
                    }
                }
            }
        }
    }
}

void Level::update_water_next_to_lava (void)
{
    for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
        for (auto x = 2; x < MAP_WIDTH - 2; x++) {
            if (is_shallow_water(x, y) || is_deep_water(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        if (is_lava(x + dx, y + dy)) {
                            FOR_ALL_THINGS(this, t, x, y) {
                                if (t->is_shallow_water()) {
                                    t->dead("Next to lava");
                                    if (!is_smoke(x, y)) {
                                        auto smoke = thing_new("smoke", fpoint(x, y));
                                        smoke->set_lifespan(random_range(1, 10));
                                    }
                                }
                            } FOR_ALL_THINGS_END()
                        }
                    }
                }
            }
        }
    }
}

void Level::update_things_next_to_a_chasm (void)
{
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            //
            // Things on the edge of a chasm fall in
            //
            if (is_shallow_water(x, y) || is_deep_water(x, y) || is_lava(x, y)) {
                for (auto dx = -1; dx <= 1; dx++) {
                    for (auto dy = -1; dy <= 1; dy++) {
                        if (is_chasm(x + dx, y + dy)) {
                            bool create_dungeon_place_place_shallow_water = false;

                            FOR_ALL_THINGS(this, t, x, y) {
                                if (t->is_falling) {
                                    continue;
                                }

                                //
                                // Deep water next to a chasm changes to
                                // regular water
                                //
                                if (t->is_deep_water()) {
                                    create_dungeon_place_place_shallow_water = true;
                                }

                                if (t->is_shallow_water() || t->is_deep_water() || t->is_lava()) {
                                    t->log("Over a chasm");
                                    t->fall(1, 750);
                                }
                            } FOR_ALL_THINGS_END()

                            if (create_dungeon_place_place_shallow_water) {
                                thing_new("water1", fpoint(x, y));
                            }
                        }
                    }
                }
            }
        }
    }
}

void Level::update_deep_water (void)
{
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            //
            // Deep water must be surrounded by water
            //
            if (is_deep_water(x, y)) {
                if (is_shallow_water(x, y)) {
                    FOR_ALL_THINGS(this, t, x, y) {
                        if (t->is_shallow_water()) {
                            t->dead("Reduce water depth");
                        }
                    } FOR_ALL_THINGS_END()
                }

                int nebs = 0;
                for (auto dx = -1; dx <= 1; dx++) {
                    for (auto dy = -1; dy <= 1; dy++) {
                        //
                        // Deep water next to a wall is ok
                        //
                        if (is_wall(x, y) || is_rock(x, y)) {
                            nebs ++;
                        } else {
                            nebs += is_shallow_water(x + dx, y + dy) ? 1 : 0;
                            nebs += is_deep_water(x + dx, y + dy) ? 1 : 0;
                        }
                    }
                }

                if (nebs < 9) {
                    bool removed_deep_water = false;

                    FOR_ALL_THINGS(this, t, x, y) {
                        if (t->is_deep_water()) {
                            t->dead("Too shallow");
                            removed_deep_water = true;
                        }
                    } FOR_ALL_THINGS_END()

                    //
                    // Replace with shallow water
                    //
                    if (removed_deep_water) {
                        thing_new("water1", fpoint(x, y));
                    }

                    if (g_opt_debug2) {
                        if (is_deep_water(x, y)) {
                            FOR_ALL_THINGS(this, t, x, y) {
                                if (t->is_deep_water()) {
                                    t->err("Still present; should be removed");
                                }
                            } FOR_ALL_THINGS_END()

                            DIE("deep water still present after removal");
                        }
                    }
                }
            }
        }
    }
}

void Level::update_map (void)
{
    update_hazard_tile_map();
    update_water_next_to_lava();
    update_things_next_to_a_chasm();
    update_deep_water();
    update_hazard_tile_map();
}
