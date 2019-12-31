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
{
    LOG("-");
    CON("DUNGEON: destroying dungeon, seed %u", seed);
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    fps_count = 0;
    started = false;

    config.fini();
    world.fini();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: destroyed dungeon, seed %u", seed);
    LOG("-");
}
