//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Level::update (void)
{_
    minimap_valid = false;
    lighting_valid = false;
    heatmap_valid = false;
}
