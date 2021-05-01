//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"

//
// Return the dmap distance. DMAP_IS_WALL if not reachable.
//
int Thing::distance_to_player (void)
{_
    auto player = game->level->player;
    if (!player) {
        return DMAP_IS_WALL;
    }

    //
    // Check we're on the same level
    if (player->level != level) {
        return DMAP_IS_WALL;
    }

    return get(&game->level->player_dmap.val, (int)mid_at.x, (int)mid_at.y);
}

void Level::player_dmap_update (void)
{_
    if (!player) {
        return;
    }

    //
    // Set up obstacles for the search
    //
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            if (is_movement_blocking_hard(point(x, y))) {
                set(player_dmap.val, x, y, DMAP_IS_WALL);
            } else {
                set(player_dmap.val, x, y, DMAP_IS_PASSABLE);
            }
        }
    }

    set(player_dmap.val, player->mid_at.x, player->mid_at.y, DMAP_IS_GOAL);

    dmap_process(&player_dmap);
    if (g_opt_debug4) {
        LOG("Player dmap:");
        dmap_print(&player_dmap);
    }
}
