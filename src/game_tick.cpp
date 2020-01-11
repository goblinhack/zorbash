//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"

void Game::tick_begin (void)
{
    //
    // Move when all things are done moving
    //
    game->tick_current++;
CON(" ");
CON(" ");
CON("GAME TICK BEGIN tick_current %d tick_completed %d",
    game->tick_current,
    game->tick_completed);
}

void Game::tick_end (void)
{
    //
    // Move when all things are done moving
    //
    if (game->tick_completed == game->tick_current) {
        return;
    }
    game->tick_completed = game->tick_current;
CON("GAME TICK END tick_current %d tick_completed %d",
    game->tick_current,
    game->tick_completed);
CON(" ");
CON(" ");
}

