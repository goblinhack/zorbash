//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
// REMOVED #include "my_globals.h"
// REMOVED #include "my_level.h"
#include "my_thing.h"

void Game::display (void)
{_
    if (level) {
        level->display();
    }

    thing_gc();
}
