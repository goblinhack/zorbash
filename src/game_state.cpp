//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_wid_thing_collect.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_wid_bag.h"

void Game::change_state (int new_state)
{
    if (game->state == new_state) {
        return;
    }

    switch (new_state) {
        case STATE_NORMAL:
            log("State changed to STATE_NORMAL");
            break;
        case STATE_MOVING_ITEMS:     // Currently managing inventory
            log("State changed to STATE_MOVING_ITEMS");
            break;
        case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
            log("State changed to STATE_COLLECTING_ITEMS");
            break;
        case STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
            log("State changed to STATE_CHOOSING_TARGET");
            break;
    }

    wid_thing_collect_fini();
    wid_thing_info_fini();

    if (game->in_transit_item) {
        if (wid_in_transit_item_drop()) {
            game->tick_begin("drop in transit item");
        }
        wid_destroy(&game->in_transit_item);
    }

    request_to_throw_item = nullptr;
    state = new_state;

    if (level) {
        level->cursor_recreate();
        level->cursor->cursor_path_stop();
    }

    wid_inventory_init();
}
