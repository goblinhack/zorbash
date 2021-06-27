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
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

static WidPopup *wid_item_options_window;
static Thingp chosen_thing;

static void wid_item_options_destroy (void)
{_
    delete wid_item_options_window;
    wid_item_options_window = nullptr;
}

static uint8_t wid_item_options_use (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    game->config_gfx_select();
    return true;
}

static uint8_t wid_item_options_eat (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    TOPCON("eat");
    return true;
}

static uint8_t wid_item_options_throw (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    TOPCON("throw");
    return true;
}

static uint8_t wid_item_options_drop (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    TOPCON("drio");
    return true;
}

static uint8_t wid_item_options_move (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    TOPCON("move");
    return true;
}

static uint8_t wid_item_options_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_item_options_destroy();
    game->main_menu_select();
    return true;
}

static uint8_t wid_item_options_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
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
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

void Game::wid_items_options_create (Thingp chosen)
{_
    CON("Config menu");

    wid_thing_info_fini();
    change_state(Game::STATE_ITEM_OPTIONS);

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

    chosen_thing = chosen;

    if (wid_item_options_window) {
        wid_item_options_destroy();
    }

    point tl = make_point(
                TERM_WIDTH / 2 - UI_WID_POPUP_WIDTH_NORMAL / 2,
                TERM_HEIGHT / 2 - 4);
    point br = make_point(
                TERM_WIDTH / 2 + UI_WID_POPUP_WIDTH_NORMAL / 2 - 1,
                TERM_HEIGHT / 2 + 14);
    auto width = br.x - tl.x - 2;

    wid_item_options_window = new WidPopup("Item option",
                                          tl, br, nullptr, "nothing", false, false);
    {_
        Widp w = wid_item_options_window->wid_popup_container;
        wid_set_on_key_up(w, wid_item_options_key_up);
        wid_set_on_key_down(w, wid_item_options_key_down);
    }

    int y_at = 0;

    if (chosen_thing->is_usable()) {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "use");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_use);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$U%%fg=reset$se");
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
    }
    {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "drop");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_drop);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$rop");
    }
    y_at += 3;
    {_
        auto p = wid_item_options_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "move");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, wid_item_options_move);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$M%%fg=reset$ove");
    }
    y_at += 3;
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
