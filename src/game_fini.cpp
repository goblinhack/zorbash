//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Config::fini (void)
{_
}

void Game::fini (void)
{_
    fps_value = 0;
    started = false;

    config.fini();

    world.fini();

    if (player_dmap) {
        delete player_dmap;
        player_dmap = nullptr;
    }
}
