//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Level::update_all_things (void)
{_
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            FOR_ALL_THINGS(this, t, x, y) {
                t->update_light(true);
            } FOR_ALL_THINGS_END();
        }
    }
}

void Level::update (void)
{_
    minimap_valid = false;
    update_all_things();
}
