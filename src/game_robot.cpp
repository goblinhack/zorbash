//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_wid_popup.h"

void Game::robot_mode_tick (void)
{_
    if (!level) {
        return;
    }

    if (!level->player) {
        return;
    }

    level->player->robot_tick();
}
