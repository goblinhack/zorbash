//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_wid_thing_collect.h"
#include "my_wid_bag.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ui.h"
#include "my_monst.h"
#include "my_thing.h"
#include "my_sdl.h"

void wid_skillbox_fini (void)
{_
    LOG("Skillbox: fini");

    if (game->request_remake_skillbox) {
        //
        // continue
        //
    } else {
        if (game->state == Game::STATE_CHOOSING_TARGET ||
            game->state == Game::STATE_MOVING_ITEMS || 
            game->state == Game::STATE_COLLECTING_ITEMS) {
            return;
        }
    }
}

uint8_t wid_skillbox_init (void)
{_
    return true;
}

void wid_skillbox_mouse_over_b (Widp w, 
                                int32_t relx, int32_t rely, 
                                int32_t wheelx, int32_t wheely)
{_
    LOG("Skillbox: begin over skillbox");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        LOG("Skillbox: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("Skillbox: in transit item; ignore");
        return;
    }

    if (game->paused()) {
        LOG("Skillbox: game paused; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("Skillbox: no level; ignore");
        return;
    }

    auto slot = wid_get_int_context(w);

    LOG("Skillbox: begin over skillbox slot %d", slot);
_
    if (!level->skillbox_over(slot)) {
        LOG("Skillbox: not over anything");
        return;
    }

    level->skillbox_describe(slot);

    auto t = level->skillbox_get(slot);
    if (t) {
        game->wid_thing_info_create(t);
    }
}

void wid_skillbox_mouse_over_e (Widp w)
{_
    LOG("Skillbox: end over skillbox");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        LOG("Skillbox: moving items; ignore");
        return;
    }

    if (game->in_transit_item) {
        LOG("Skillbox: in transit item; ignore");
        return;
    }

    if (game->paused()) {
        LOG("Skillbox: paused; ignore");
        return;
    }

    auto level = game->level;
    if (!level) {
        LOG("Skillbox: no level; ignore");
        return;
    }

    auto slot = wid_get_int_context(w);

    LOG("Skillbox: over skillbox slot %d", slot);
_
    if (!level->skillbox_over(slot)) {
        return;
    }

    game->wid_thing_info_destroy();

    //
    // Do not create new wids in here
    //
}

uint8_t wid_skillbox_item_mouse_up (Widp w, int32_t x, int32_t y,
                                    uint32_t button)
{_
    if (game->state == Game::STATE_MOVING_ITEMS) {
        wid_thing_info_fini();
    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
        wid_thing_collect_fini();
    }

    if (game->in_transit_item) {
        return wid_in_transit_item_place(w, x, y, button);
    }

    if (game->paused()) {
        return false;
    }

    auto level = game->level;
    if (!level) {
        return true;
    }

    auto slot = wid_get_int_context(w);
    if (!level->skillbox_chosen(slot)) {
        return true;
    }

    if (game->state == Game::STATE_MOVING_ITEMS) {
        level->skillbox_describe(slot);
        auto t = level->skillbox_get(slot);
        if (t) {
            game->wid_thing_info_create(t);
        }
    }

    return true;
}

uint8_t wid_skillbox_mouse_up (Widp w, int32_t x, int32_t y,
                               uint32_t button)
{_
    if (game->state == Game::STATE_MOVING_ITEMS) {
        wid_thing_info_fini();
    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
        wid_thing_collect_fini();
    }

    if (game->in_transit_item) {
        return wid_in_transit_item_place(w, x, y, button);
    }

    return false;
}
