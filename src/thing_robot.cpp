//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_player.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_wid_popup.h"

void Thing::robot_tick (void)
{_
    if (!monstp) {
        return;
    }

    static uint32_t last_tick;
    if (!time_have_x_ms_passed_since(game->robot_delay_ms, last_tick)) {
        return;
    }

    last_tick = time_get_time_ms_cached();

    if (is_dead) {
        return;
    }

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool attack = false;
    bool wait = false;
    bool jump = false;
    bool do_something = false;

    switch (monstp->robot_state) {
        case ROBOT_STATE_WANDER:
        {
        }
        break;
    }


    if (do_something) {
        if (is_player()) {
            player_tick(left, right, up, down, attack, wait, jump);
        }
    } else {
        if (is_player()) {
            TOPCON("Nothing to do.");
        }
    }
}
