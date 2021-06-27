//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_wid_bag.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ui.h"
#include "my_monst.h"
#include "my_thing.h"
#include "my_sdl.h"

void wid_inventory_fini (void)
{_
    LOG("Inventory: fini");
}

uint8_t wid_inventory_init (void)
{_
    return true;
}

void wid_inventory_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
{_
    LOG("Inventory: begin over inventory");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_ITEM_OPTIONS ||
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_CHOOSING_SKILLS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        LOG("Inventory: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("Inventory: in transit item; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("Inventory: no level; ignore");
        return;
    }

    auto slot = wid_get_int_context(w);

    LOG("Inventory: begin over inventory slot %d", slot);
_
    if (!level->inventory_over(slot)) {
        LOG("Inventory: not over anything");
        return;
    }

    level->inventory_describe(slot);

    auto t = level->inventory_get(slot);
    if (t) {
        game->wid_thing_info_create(t);
    }
}

void wid_inventory_mouse_over_e (Widp w)
{_
    LOG("Inventory: end over inventory");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_ITEM_OPTIONS ||
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_CHOOSING_SKILLS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        LOG("Inventory: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("Inventory: in transit item; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("Inventory: no level; ignore");
        return;
    }

    auto slot = wid_get_int_context(w);

    LOG("Inventory: over inventory slot %d", slot);
_
    if (!level->inventory_over(slot)) {
        return;
    }

    game->wid_thing_info_destroy_deferred();

    //
    // Do not create new wids in here
    //
}

uint8_t wid_inventory_item_mouse_up_on_bag (Widp w,
                                            int32_t x,
                                            int32_t y,
                                            uint32_t button)
{_
    LOG("Inventory: mouse up over bag");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_ITEM_OPTIONS ||
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_CHOOSING_SKILLS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        return true;
    }

    if (game->in_transit_item) {
        return wid_in_transit_item_place(w, x, y, button);
    }

    BOTCON("Press %%fg=red$ESCAPE%%fg=reset$ when done moving items around.");
    game->change_state(Game::STATE_MOVING_ITEMS);

    auto level = game->level;
    if (!level) {
        return true;
    }

    auto slot = wid_get_int_context(w);
    if (!level->inventory_chosen(slot)) {
        return true;
    }

    auto t = level->inventory_get(slot);
    if (t) {
        game->wid_thing_info_create(t);
    }

    return true;
}

uint8_t wid_inventory_item_mouse_up (Widp w,
                                     int32_t x,
                                     int32_t y,
                                     uint32_t button)
{_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_ITEM_OPTIONS ||
        game->state == Game::STATE_COLLECTING_ITEMS ||
        game->state == Game::STATE_CHOOSING_SKILLS ||
        game->state == Game::STATE_ENCHANTING_ITEMS) {
        LOG("Inventory: moving items; ignore");
        return true;
    }

    if (game->state == Game::STATE_MOVING_ITEMS) {
        wid_thing_info_fini();
    }

    if (game->in_transit_item) {
        return wid_in_transit_item_place(w, x, y, button);
    }

    auto level = game->level;
    if (!level) {
        return true;
    }

    auto slot = wid_get_int_context(w);
    if (!level->inventory_chosen(slot)) {
        return true;
    }

    if (game->state == Game::STATE_MOVING_ITEMS) {
        level->inventory_describe(slot);
        auto t = level->inventory_get(slot);
        if (t) {
            game->wid_thing_info_create(t);
        }
    }

    return true;
}
