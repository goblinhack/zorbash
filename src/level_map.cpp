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

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
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

void Level::update_map (void)
{
    update_hazard_tile_map();
}
