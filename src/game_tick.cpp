//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"

void Game::tick_begin (void)
{_
    //
    // Move when all things are done moving
    //
    game->tick_current++;
    LOG("-");
    LOG("game tick %d begin", game->tick_current);
}

void Game::tick_end (void)
{_
    //
    // Move when all things are done moving
    //
    if (game->tick_completed == game->tick_current) {
        return;
    }
    game->tick_completed = game->tick_current;
}
