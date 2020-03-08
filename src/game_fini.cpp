//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"

void Config::fini (void)
{_
}

void Game::fini (void)
{_
    fps_value = 0;
    tick_current = 0;
    tick_completed = 0;
    things_are_moving = false;
    started = false;

    config.fini();
    world.fini();

    if (player_dmap) {
        delete player_dmap;
    }
}
