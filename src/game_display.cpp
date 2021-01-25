//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_thing.h"

void Game::display (void)
{_
    if (!level) {
        return;
    }

    level->display();
    level->things_gc_if_possible();
}
