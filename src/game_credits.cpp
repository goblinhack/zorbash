//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"

static WidPopup *wid_credits_window;

static void wid_credits_destroy (void)
{_
    delete wid_credits_window;
    wid_credits_window = nullptr;
    game->soft_unpause();
    game->fini();
    game->main_menu_select();
    wid_not_visible(wid_minicon_window);
    wid_not_visible(wid_botcon_window);
}

uint8_t wid_credits_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case 'b':
                    case SDLK_ESCAPE: {_
                        wid_credits_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_credits_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
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

uint8_t wid_credits_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    wid_credits_destroy();
    return (true);
}

void Game::credits_select (void)
{_
    CON("Credits");

    if (wid_credits_window) {
        wid_credits_destroy();
    }
    game->soft_pause();

    point tl = make_point(0, 0);
    point br = make_point(ASCII_WIDTH - 1, ASCII_HEIGHT - 1);
    auto width = br.x - tl.x;

    wid_credits_window = new WidPopup(tl, br, nullptr, "ui_credits");
    wid_set_on_key_up(
      wid_credits_window->wid_popup_container, wid_credits_key_up);
    wid_set_on_key_down(
      wid_credits_window->wid_popup_container, wid_credits_key_down);

    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log(" ");
    wid_credits_window->log("Development and bad graphics");
    wid_credits_window->log("%%fg=cyan$Neil McGill (goblinhack@gmail.com)");
    wid_credits_window->log(" ");
    wid_credits_window->log("Graphics");
    wid_credits_window->log("%%fg=green$Oryx tileset https://www.oryxdesignlab.com/");
    wid_credits_window->log(" ");
    wid_credits_window->log("Sound");
    wid_credits_window->log("%%fg=purple$Markus Heichelbech (deceased senior technician) http://nosoapradio.us");
    wid_credits_window->log(" ");
    wid_credits_window->log("Testing");
    wid_credits_window->log("%%fg=red$Stuicy");

    {_
        auto p = wid_credits_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "credits");

        point tl = make_point(24, 24);
        point br = make_point(width - 25, 26);

        wid_set_style(w, UI_WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_credits_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "BACK");
    }

    wid_update(wid_credits_window->wid_text_area->wid_text_area);
}
