//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_wid_collect.h"
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_wid_bag.h"

void Game::change_state (int new_state)
{
    if (game->state == new_state) {
        return;
    }

    auto old_state = state;

    switch (new_state) {
        case STATE_NORMAL:
            LOG("State changed to STATE_NORMAL");
            break;
        case STATE_MOVING_ITEMS:     // Currently managing inventory
            LOG("State changed to STATE_MOVING_ITEMS");
            break;
        case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
            LOG("State changed to STATE_COLLECTING_ITEMS");
            break;
        case STATE_ENCHANTING_ITEMS:
            LOG("State changed to STATE_ENCHANTING_ITEMS");
            break;
        case STATE_CHOOSING_SKILLS:
            LOG("State changed to STATE_CHOOSING_SKILLS");
            break;
        case STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
            LOG("State changed to STATE_CHOOSING_TARGET");
            break;
    }

    wid_collect_fini();
    wid_thing_info_fini();

    if (game->in_transit_item) {
        if (wid_in_transit_item_drop()) {
            game->tick_begin("drop in transit item");
        }
        wid_destroy(&game->in_transit_item);
    }

    request_to_throw_item = nullptr;
    request_to_fire_item = nullptr;
    state = new_state;

    switch (old_state) {
        case STATE_NORMAL:
        case STATE_MOVING_ITEMS:     // Currently managing inventory
        case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
        case STATE_ENCHANTING_ITEMS:
        case STATE_CHOOSING_SKILLS:
            if (level) {
                level->cursor_recreate();
                level->cursor->cursor_path_stop();
            }
            break;
        case STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
            //
            // Don't create the cursor right after selecting. Wait until
            // we move again.
            //
            if (level) {
                level->cursor_recreate();
                level->cursor_path_clear();
            }
            break;
    }


    wid_inventory_init();
}
