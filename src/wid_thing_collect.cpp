//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_collect.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_wid_console.h"
#include "my_wid_bag.h"
#include "my_level.h"
#include "my_thing.h"

WidPopup *wid_thing_collect_window;

void wid_thing_collect_fini (void)
{_
    LOG("thing collect fini");

    if (game->bag1) {
        delete game->bag1;
        game->bag1 = nullptr;
    }

    if (game->bag2) {
        delete game->bag2;
        game->bag2 = nullptr;
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
    LOG("thing collect destroy");

    if (game->remake_inventory) {
        //
        // Continue
        //
    } else if (game->moving_items) {
        return;
    }

    wid_thing_collect_fini();
}

void Game::wid_thing_collect_create (const std::list<Thingp> &items)
{_
    LOG("thing collect create");
_
    if (game->remake_inventory) {
        //
        // Continue
        //
        LOG("remake thing collect");
    } else if (game->moving_items) {
        LOG("ignore, already moving items");
        return;
    }

    if (game->in_transit_item) {
        LOG("ignore, already in transit item0");
        return;
    }

    if (wid_console_window && wid_console_window->visible) {
        LOG("console visible");
        return;
    }

    if (wid_thing_collect_window) {
        LOG("destroy window");
        wid_thing_collect_destroy();
    }

    auto player = game->level->player;
    if (!player){
        game->moving_items = false;
        ERR("no player");
        return;
    }


    LOG("thing collect create bags");

    point mid(TERM_WIDTH / 2, TERM_HEIGHT - 1);

    if (bag1) {
        delete bag1;
        bag1 = nullptr;
    }

    if (bag2) {
        delete bag2;
        bag2 = nullptr;
    }

    {
        point tl = mid - point(player->bag_width() + 5, player->bag_height() + 1);
        point br = tl +  point(player->bag_width(), player->bag_height());
        bag1 = new WidBag(player, tl, br, "Inventory");
    }

    auto volume = bag_estimate_volume(items);
    auto height = sqrt(volume);
    if (height >= MAX_BAG_WIDTH) {
        height = MAX_BAG_WIDTH;
        ERR("bag size is too large");
    }

    point tl = mid + point(0, - (height + 1));
    point br = tl +  point(height, height);


    auto virtual_bag = level->thing_new("bag_items", fpoint(-1, -1));
    virtual_bag->monstp->bag_width = height;
    virtual_bag->monstp->bag_height = height;
    virtual_bag->try_to_carry(items);

    bag2 = new WidBag(virtual_bag, tl, br, "Items found");

    int utilized = wid_thing_collect_window->wid_text_area->line_count;
    wid_move_delta(wid_thing_collect_window->wid_popup_container, 0, 
                   height - utilized + 2);
    wid_resize(wid_thing_collect_window->wid_popup_container, -1, utilized - 2);

    wid_update(wid_thing_collect_window->wid_text_area->wid_text_area);
}
