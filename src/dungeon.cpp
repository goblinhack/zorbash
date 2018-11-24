/*
 * Copyright (C) 2018 goblinhack@gmail.com
 * See the LICENSE file for license.
 */

#include "my_dungeon.h"

class Dungeon *dungeon_test (void)
{
#if 0
    auto x = 1000 ;
    while (x--) {
        //
        // smaller node numbers mean larger rooms
        //
        mysrand(x);
        new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH, GRID_HEIGHT, x);
    }

    return (nullptr);
#else
int x = 663;
//x = myrand();
CON("seed: %d", x);
mysrand(x);
    auto d = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH, GRID_HEIGHT, x);

    return (d);
#endif
}
