//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_wid_popup.h"

void Game::robot_mode_tick (void)
{_
    if (!game->robot_mode) {
        return;
    }

    if (!level) {
        return;
    }

    auto player = level->player;
    if (!player) {
        return;
    }

    if ((player->monstp->robot_state != ROBOT_STATE_IDLE) &&
        (player->monstp->robot_state != ROBOT_STATE_RESTING)) {
        return;
    }

    player->robot_tick();
}
