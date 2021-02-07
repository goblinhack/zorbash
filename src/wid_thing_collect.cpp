//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_collect.h"
#include "my_tile.h"
#include "my_wid_console.h"
#include "my_wid_bag.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_monst.h"

WidPopup *wid_thing_collect_window;

void wid_thing_collect_fini (void)
{_
    LOG("Thing collect fini");

    if (game->bag_primary) {
        delete game->bag_primary;
        game->bag_primary = nullptr;
    }

    if (game->bag_secondary) {
        delete game->bag_secondary;
        game->bag_secondary = nullptr;
    }

    delete wid_thing_collect_window;
    wid_thing_collect_window = nullptr;
}

uint8_t wid_thing_collect_init (void)
{_
    return true;
}

void Game::wid_thing_collect_destroy (void)
{_
    LOG("Thing collect destroy");

    if (game->request_remake_inventory) {
        //
        // Continue
        //
    } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
        return;
    }

    wid_thing_collect_fini();
}

void Game::wid_thing_collect_create (const std::list<Thingp> &items)
{_
    LOG("Thing collect create");
_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
        LOG("Remake thing collect");
    } else if (game->state == Game::STATE_COLLECTING_ITEMS) {
        LOG("Ignore, already moving items");
        return;
    }

    if (game->in_transit_item) {
        LOG("Ignore, already in transit item0");
        return;
    }

    if (wid_console_window && wid_console_window->visible) {
        LOG("Console visible");
        return;
    }

    if (wid_thing_collect_window) {
        LOG("Destroy window");
        wid_thing_collect_destroy();
    }

    auto player = game->level->player;
    if (!player){
        ERR("No player");
        return;
    }

    LOG("Thing collect create bags");

    point mid(TERM_WIDTH / 2, TERM_HEIGHT - 1);

    if (bag_primary) {
        delete bag_primary;
        bag_primary = nullptr;
    }

    if (bag_secondary) {
        delete bag_secondary;
        bag_secondary = nullptr;
    }

    state = Game::STATE_COLLECTING_ITEMS;

    //
    // bag_primary
    //
    {
        point tl = mid - point(player->bag_width() + 5, player->bag_height() + 1);
        point br = tl +  point(player->bag_width(), player->bag_height());
        bag_primary = new WidBag(player, tl, br, "Inventory");
    }

    //
    // bag_secondary
    //
    {
        auto volume = bag_estimate_volume(items);
        auto height = sqrt(volume);
        if (height >= MAX_BAG_WIDTH) {
            height = MAX_BAG_WIDTH;
            ERR("Bag size is too large");
        }

        if (height < sizeof("Items found")) {
            height = sizeof("Items found");
        }

        point tl = mid + point(0, - (height + 1));
        point br = tl +  point(height, height);

        auto temporary_bag = level->thing_new("bag_items", fpoint(-1, -1));
        temporary_bag->new_monst();
        temporary_bag->monstp->bag_width = height;
        temporary_bag->monstp->bag_height = height;
        temporary_bag->try_to_carry(items);

        bag_secondary = new WidBag(temporary_bag, tl, br, "Items found");
    }
}
