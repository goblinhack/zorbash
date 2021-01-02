//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_thing.h"

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
            if (is_water(x, y) || is_deep_water(x, y)) {
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
            if (is_water(x, y) || is_deep_water(x, y)) {
                for (auto dx = -2; dx <= 2; dx++) {
                    for (auto dy = -2; dy <= 2; dy++) {
                        if (is_lava(x + dx, y + dy)) {
                            FOR_ALL_THINGS(this, t, x, y) {
                                if (t->is_water()) {
                                    t->dead("Next to lava");
                                    if (!is_smoke(x, y)) {
                                        auto smoke = thing_new("smoke1", fpoint(x, y));
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
            if (is_water(x, y) || is_lava(x, y)) {
                for (auto dx = -1; dx <= 1; dx++) {
                    for (auto dy = -1; dy <= 1; dy++) {
                        if (is_chasm(x + dx, y + dy)) {
                            FOR_ALL_THINGS(this, t, x, y) {
                                if (t->is_falling) {
                                    continue;
                                }
                                if (t->is_water() || t->is_lava()) {
                                    t->log("Over a chasm");
                                    t->fall(1, 750);
                                }
                            } FOR_ALL_THINGS_END()
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
    update_hazard_tile_map();
}
