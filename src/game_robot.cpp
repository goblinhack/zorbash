//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_player.h"

void Game::robot_mode_tick (void)
{
    static uint32_t last_tick;
    if (!time_have_x_ms_passed_since(game->robot_delay_ms, last_tick)) {
        return;
    }

    last_tick = time_get_time_ms_cached();

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool attack = false;
    bool wait = false;
    bool jump = false;

    wait = true;

    player_tick(left, right, up, down, attack, wait, jump);
}
