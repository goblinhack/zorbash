//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_thing.h"

void Game::display (void)
{_
    if (level) {
        level->display();
    }

    thing_gc();
}
