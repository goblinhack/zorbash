//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_random.h"

void Level::create (point3d at, int seed)
{_
    is_starting = true;
    clear();

    this->seed = seed;
    world_at = at;
    mysrand(seed);

    log("-");
    log("Creating, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    if (at.z & 1) {
        create_dungeon(at, seed);
    } else {
        create_sewer(at, seed);
    }

    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("Created, seed %u", seed);
    log("-");

    update_map();

    game->started = true;
    is_starting = false;

    timestamp_fade_in_begin = time_get_time_ms_cached();
}

void Level::place_the_grid (Dungeonp d)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            (void) thing_new("the_grid", fpoint(x, y));
            if (g_errored) {
                ERR("Could not create level");
                return;
            }
        }
    }
}

