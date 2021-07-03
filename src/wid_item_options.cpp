//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_wid_inventory.h"
#include "my_wid_actionbar.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

WidPopup *wid_item_options_window;
static Thingp chosen_thing;
static Widp chosen_wid;
static bool came_from_inventory;

void wid_item_options_destroy (void)
{_
    LOG("Item options destroy");
_
    delete wid_item_options_window;
    wid_item_options_window = nullptr;
}

static uint8_t wid_item_options_use (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options use");
_
    wid_item_options_destroy();

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return false;
    }

    player->use(chosen_thing);

    game->change_state(Game::STATE_NORMAL);
    return true;
}

static uint8_t wid_item_options_eat (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options eat");
_
    wid_item_options_destroy();

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return false;
    }

    player->use(chosen_thing);

    if (came_from_inventory) {
        game->change_state(Game::STATE_NORMAL);
        return true;
    }

    if (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) {
        game->change_state(Game::STATE_MOVING_ITEMS);
        game->request_remake_inventory = true;
        game->wid_thing_info_create(game->level->player, false);
    }
    return true;
}

static uint8_t wid_item_options_throw (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options throw");
_
    wid_item_options_destroy();

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return false;
    }

    game->change_state(Game::STATE_NORMAL);
    wid_thing_info_fini(); // To remove bag or other info
    player->throw_item_choose_target(chosen_thing);

    return true;
}

static uint8_t wid_item_options_drop (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options drop");
_
    wid_item_options_destroy();

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return false;
    }

    player->drop(chosen_thing);

    if (came_from_inventory) {
        game->change_state(Game::STATE_NORMAL);
        return true;
    }

    game->change_state(Game::STATE_MOVING_ITEMS);
    game->request_remake_inventory = true;
    game->wid_thing_info_create(game->level->player, false);

    return true;
}

static uint8_t wid_item_options_move (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options move");
_
    wid_item_options_destroy();
    game->wid_bag_move_item(chosen_wid, chosen_thing);
    return true;
}

static uint8_t wid_item_options_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    LOG("Item options back");
_
    wid_item_options_destroy();

    if (came_from_inventory) {
        game->change_state(Game::STATE_NORMAL);
        wid_thing_info_fini(); // To remove bag or other info
        return true;
    }

    game->change_state(Game::STATE_MOVING_ITEMS);
    game->request_remake_inventory = true;
    game->wid_thing_info_create(game->level->player, false);
    return true;
}

static uint8_t wid_item_options_key_up (Widp w, const struct SDL_Keysym *key)
{_
    LOG("Item options key up");
_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    if (key->scancode == (SDL_Scancode)game->config.key_use) {
        wid_item_options_use(nullptr, 0, 0, 0);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_throw) {
        wid_item_options_throw(nullptr, 0, 0, 0);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_eat) {
        wid_item_options_eat(nullptr, 0, 0, 0);
        return true;
    }
    if (key->scancode == (SDL_Scancode)game->config.key_drop) {
        wid_item_options_drop(nullptr, 0, 0, 0);
        return true;
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'u':
                        wid_item_options_use(nullptr, 0, 0, 0);
                        return true;
                    case 't':
                        wid_item_options_throw(nullptr, 0, 0, 0);
                        return true;
                    case 'e':
                        wid_item_options_eat(nullptr, 0, 0, 0);
                        return true;
                    case 'd':
                        wid_item_options_drop(nullptr, 0, 0, 0);
                        return true;
                    case 'm':
                        wid_item_options_move(nullptr, 0, 0, 0);
                        return true;
                    case 'b':
                    case SDLK_ESCAPE:
                        wid_item_options_back(nullptr, 0, 0, 0);
                        return true;
                }
            }
        }
    }

    return false;
}

static uint8_t wid_item_options_key_down (Widp w, const struct SDL_Keysym *key)
{_
    LOG("Item options key down");
_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

void Game::wid_items_options_create (Widp w, Thingp t, bool source_came_from_inventory)
{_
    LOG("Item options");
_
    auto was_moving_items = (game->state == Game::STATE_MOVING_ITEMS);

    change_state(Game::STATE_OPTIONS_FOR_ITEM_MENU);

    auto player = game->level->player;
    if (!player){
        change_state(Game::STATE_NORMAL);
        ERR("No player");
        return;
    }

    //
    // In case a scancode was used to open this widget
    //
    wid_ignore_events_briefly();

    chosen_thing = t;
    chosen_wid = w;
    came_from_inventory = source_came_from_inventory;

    if (wid_item_options_window) {
        wid_item_options_destroy();
    }

    int options = 2;
    if (chosen_thing->is_throwable()) {_
        options++;
    }
    if (player->can_eat(chosen_thing)) {_
        options++;
    } else if (chosen_thing->is_usable()) {_
        options++;
    }
    if (was_moving_items) {
        options++;
    }

    int h = (options * 3) + 2;
    int top_half = h / 2;
    int bot_half = h - top_half;

    point tl = make_point(
                TERM_WIDTH / 2 - UI_WID_POPUP_WIDTH_NORMAL / 2,
                TERM_HEIGHT / 2 - top_half);
    point br = make_point(
                TERM_WIDTH / 2 + UI_WID_POPUP_WIDTH_NORMAL / 2 - 1,
                TERM_HEIGHT / 2 + bot_half - 1);
    auto width = br.x - tl.x - 2;

    wid_item_options_window = new WidPopup("Item option",
                                          tl, br, nullptr, "nothing", false, false);
    {_
        Widp w = wid_item_options_window->wid_popup_container;
        wid_set_on_key_up(w, wid_item_options_key_up);
        wid_set_on_key_down(w, wid_item_options_key_down);
        wid_set_style(w, UI_WID_STYLE_DARK);
    }

    int y_at = 0;

    if (player->can_eat(chosen_thing)) {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "eat");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_eat);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$E%%fg=reset$at");
        y_at += 3;
    } else if (chosen_thing->is_usable()) {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "use");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_use);
        wid_set_pos(w, tl, br);
        if (chosen_thing->is_weapon()) {
            wid_set_text(w, "%%fg=white$U%%fg=reset$se (wield it)");
        } else if (chosen_thing->is_potion()) {
            wid_set_text(w, "%%fg=white$U%%fg=reset$se (drink it)");
        } else if (chosen_thing->is_wand()) {
            wid_set_text(w, "%%fg=white$U%%fg=reset$se (fire it)");
        } else {
            wid_set_text(w, "%%fg=white$U%%fg=reset$se");
        }
        y_at += 3;
    }
    if (chosen_thing->is_throwable()) {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "throw");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_throw);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$T%%fg=reset$hrow");
        y_at += 3;
    }
    {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "drop");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_drop);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$D%%fg=reset$rop");
    }
    y_at += 3;
    if (was_moving_items) {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "move");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_move);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$M%%fg=reset$ove");
        y_at += 3;
    }
    {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
    }

    wid_update(wid_item_options_window->wid_text_area->wid_text_area);
}
