//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"

void Game::fini (void)
{_
    fps_value = 0;
    started = false;
    things_are_moving = false;
    tick_completed = 1;
    tick_current = 1;
    config.fini();
    world.fini();
}
