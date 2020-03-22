//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *wid_dead_window;

static void wid_dead_destroy (void)
{_
    if (wid_dead_window) {
        delete wid_dead_window;
        wid_dead_window = nullptr;
    }
    game->soft_unpause();
    game->fini();
    game->main_menu_select();
    wid_hide(wid_minicon_window);
}

uint8_t wid_dead_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case SDLK_ESCAPE: {_
                        wid_dead_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_dead_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                }
            }
        }
    }

    return (true);
}

uint8_t wid_dead_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_dead_destroy();
    return (true);
}

void Game::dead_select (const char *reason)
{_
    if (wid_dead_window) {
        wid_dead_destroy();
    }
    game->soft_pause();

    point tl = {0, ASCII_HEIGHT - 24};
    point br = {WID_POPUP_WIDTH_NORMAL, ASCII_HEIGHT - 1};
    auto width = br.x - tl.x - 1;

    wid_dead_window = new WidPopup(tl, br, nullptr, "ui_dead");
    wid_set_on_key_up(
      wid_dead_window->wid_popup_container, wid_dead_key_up);
    wid_set_on_key_down(
      wid_dead_window->wid_popup_container, wid_dead_key_down);

    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(" ");
    wid_dead_window->log(reason);

    {_
        auto p = wid_dead_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "dead");

        point tl = {3, 7};
        point br = {width - 4, 9};

        wid_set_shape_none(w);
        wid_set_on_mouse_up(w, wid_dead_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "Reason of demise");
    }

    {_
        auto p = wid_dead_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "dead");

        point tl = {4, 16};
        point br = {width - 5, 18};

        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_dead_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "CONTINUE");
    }

    wid_update(wid_dead_window->wid_text_area->wid_text_area);
}
