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

static void wid_skillbox_create(void);

Widp wid_skillbox_window {};

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

    wid_destroy(&wid_skillbox_window);
    if (wid_skillbox_window) {
        DIE("Wid_skillbox_window exists after destroy");
    }
}

uint8_t wid_skillbox_init (void)
{_
    wid_skillbox_create();

    return true;
}

static void wid_skillbox_mouse_over_b (Widp w, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely)
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

static void wid_skillbox_mouse_over_e (Widp w)
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

static uint8_t wid_skillbox_item_mouse_up_on_bag (Widp w,
                                                   int32_t x,
                                                   int32_t y,
                                                   uint32_t button)
{_
    LOG("Skillbox: mouse up over bag");
_
    if (game->state == Game::STATE_CHOOSING_TARGET ||
        game->state == Game::STATE_MOVING_ITEMS || 
        game->state == Game::STATE_COLLECTING_ITEMS) {
        return false;
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
    if (!level->skillbox_chosen(slot)) {
        return true;
    }

    auto t = level->skillbox_get(slot);
    if (t) {
        game->wid_thing_info_create(t);
    }

    return true;
}

static uint8_t wid_skillbox_item_mouse_up (Widp w,
                                            int32_t x,
                                            int32_t y,
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

static uint8_t wid_skillbox_mouse_up (Widp w,
                                       int32_t x,
                                       int32_t y,
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

//
// Create the test
//
static void wid_skillbox_create (void)
{_
    LOG("Skillbox: skillbox create");

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

    auto level = game->level;
    if (!level) {
        return;
    }
    auto player = level->player;
    if (!player) {
        return;
    }

    //
    // Stop this window popping on top of dialogs like when setting keys
    //
    if (game->paused()) {
        return;
    }

    static bool recursion;
    if (recursion) {
        DIE("Recursion");
    }
    recursion = true;

    wid_skillbox_fini();

    {

        {_
            auto x1 = TERM_WIDTH - UI_SIDEBAR_RIGHT_WIDTH;
            auto x2 = TERM_WIDTH - 1;
            point tl = make_point(x1, 31);
            point br = make_point(x2, 41);
            color c;

            if (wid_skillbox_window) {
                DIE("Wid_skillbox_window exists");
            }
            wid_skillbox_window = wid_new_square_window("wid skillbox");
            wid_set_ignore_scroll_events(wid_skillbox_window, true);
            wid_set_pos(wid_skillbox_window, tl, br);
            wid_set_style(wid_skillbox_window, UI_WID_STYLE_SOLID_NONE);
            wid_set_on_mouse_up(wid_skillbox_window, wid_skillbox_mouse_up);
        }
    }

    {
        auto monstp = player->monstp;
        auto skillbox_items = monstp->skillbox_id.size();
        std::vector<Widp> wid_skillbox_items;

        uint8_t item = 0;
        uint8_t y = 0;
        for (auto i = 0U; i < UI_ACTIONBAR_MAX_ITEMS; i++) {
            if (item >= skillbox_items) {
                break;
            }

            //
            // slot number
            //
            auto slot(std::to_string(i));

            if (item < monstp->skillbox_id.size()) {
                auto tp_id = get(monstp->skillbox_id, item);
                if (tp_id) {
                    auto tpp = tp_find(tp_id);
                    auto tiles = &tpp->tiles;

                    if (tiles) {
                        auto tile = tile_first(tiles);
                        if (tile) {
                            auto s = "skillbox icon" + std::to_string(i);
                            auto w = wid_new_square_button(wid_skillbox_window, s);
                            point tl = make_point(0, y);
                            point br = make_point(0, y);

                            wid_set_pos(w, tl, br);

                            wid_set_fg_tile(w, tile);
                        }
                    }
                }
            }

            {
                auto name = "skillbox slot" + slot;
                auto w = wid_new_square_button(wid_skillbox_window, name);
                point tl = make_point(1, y);
                point br = make_point(1, y);
                wid_set_pos(w, tl, br);

                if (i == game->skillbox_highlight_slot) {
                    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY60);
                } else {
                    wid_set_color(w, WID_COLOR_TEXT_FG, GRAY40);
                }

                wid_set_text(w, std::to_string(item));
            }

            {
                {
                    auto w = wid_new_square_button(wid_skillbox_window, 
                                                   "skillbox item");
                    wid_skillbox_items.push_back(w);
                    point tl = make_point(3, y);
                    point br = make_point(UI_SIDEBAR_RIGHT_WIDTH, y);

                    wid_set_pos(w, tl, br);
                    wid_set_text_lhs(w, true);

                    if (i == game->skillbox_highlight_slot) {
                        if (game->state == Game::STATE_CHOOSING_TARGET) {
                            wid_set_color(w, WID_COLOR_TEXT_FG, ORANGE);
                        } else {
                            wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
                        }
                    } else {
                        wid_set_color(w, WID_COLOR_TEXT_FG, GRAY);
                    }

                    wid_set_on_mouse_over_b(w, wid_skillbox_mouse_over_b);
                    wid_set_on_mouse_over_e(w, wid_skillbox_mouse_over_e);
                    wid_set_int_context(w, i);

                    if (item < skillbox_items) {
                        auto tp_id = monstp->skillbox_id[i];
                        if (tp_id) {
                            auto tpp = tp_find(tp_id);
                            wid_set_text(w, tpp->short_text_name());
                            if (tpp->is_bag()) {
                                wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up_on_bag);
                            } else {
                                wid_set_on_mouse_up(w, wid_skillbox_item_mouse_up);
                            }
                        }
                    } else {
                        wid_set_text(w, "-");
                    }
                }
            }
            y++;
            item++;
        }

        wid_update(wid_skillbox_window);
    }
    recursion = false;

    if (game->request_remake_skillbox) {
        if (game->state == Game::STATE_MOVING_ITEMS) {
            auto slot = game->skillbox_highlight_slot;
            LOG("Skillbox: remaking skillbox for slot %d", slot);

            auto t = level->skillbox_get(slot);
            if (t) {
                LOG("Skillbox: remaking skillbox, remake thing info too");
                game->wid_thing_info_create(t);
            } else {
                LOG("Skillbox: remaking skillbox, no thing info");
            }
        }
    }
}

bool is_mouse_over_skillbox (void)
{
    extern Widp wid_skillbox_window;

    if (!wid_skillbox_window) {
        return false;
    }

    //
    // If we are in the portion of the lower screen above the itembar
    // then do not scroll
    //
    int x = mouse_x;
    int y = mouse_y;
    pixel_to_ascii(&x, &y);

    static int tlx, tly, brx, bry, cached;
    if (cached != TERM_HEIGHT) {
        cached = TERM_HEIGHT;
    }

    wid_get_tl_x_tl_y_br_x_br_y(wid_skillbox_window, &tlx, &tly, &brx, &bry);

    //
    // Add some border
    //
    tlx -= 1;
    brx += 1;
    tly -= 1;
    bry += 1;

    if ((x >= tlx) && (x < brx) && (y >= tly)) {
        //CON("    skillbox %d %d %d", tlx, brx, x);
        return true;
    }
    //CON("NOT skillbox %d %d %d", tlx, brx, x);

    return false;
}

bool is_mouse_over_skillbox_slot (int &slot)
{
    extern Widp wid_skillbox_window;

    if (!wid_skillbox_window) {
        return false;
    }

    //
    // If we are in the portion of the lower screen above the itembar
    // then do not scroll
    //
    int x = mouse_x;
    int y = mouse_y;
    pixel_to_ascii(&x, &y);

    static int tlx, tly, brx, bry, cached;
    if (cached != TERM_HEIGHT) {
        cached = TERM_HEIGHT;
    }

    wid_get_tl_x_tl_y_br_x_br_y(wid_skillbox_window, &tlx, &tly, &brx, &bry);

    //
    // Add some border
    //
    tlx -= 1;
    brx += 1;
    tly -= 1;
    bry += 1;

    if ((x >= tlx) && (x < brx) && (y >= tly)) {
        //CON("    skillbox %d %d %d", tlx, brx, x);
        slot = y - tly;
        return true;
    }
    //CON("NOT skillbox %d %d %d", tlx, brx, x);

    return false;
}
