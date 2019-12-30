/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *wid_paused_window;

static void wid_paused_destroy (void)
{
    if (wid_paused_window) {
        delete wid_paused_window;
        wid_paused_window = nullptr;
    }
    game->soft_paused = false;
}

uint8_t wid_paused_key_up (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
#if 0
                    case ' ': // not safe as used for sword swipe
#endif
                    case '\n':
                    case SDLK_ESCAPE: {
                        wid_paused_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_paused_key_down (Widp w, const struct SDL_KEYSYM *key)
{
    return (true);
}

uint8_t wid_paused_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{
    wid_paused_destroy();
    return (true);
}

void Game::pause (void)
{_
    if (wid_paused_window) {
        wid_paused_destroy();
    }
    game->soft_paused = true;

    auto m = ASCII_WIDTH / 2;
    auto n = ASCII_HEIGHT / 2;
    point tl = {m - WID_POPUP_WIDTH_NORMAL / 2, n - 7};
    point br = {m + WID_POPUP_WIDTH_NORMAL / 2, n + 7};
    auto width = br.x - tl.x;

    wid_paused_window =
      new WidPopup(tl, br, tile_find_mand("pause"), "ui_popup");
    wid_set_on_key_up(
      wid_paused_window->wid_popup_container, wid_paused_key_up);
    wid_set_on_key_down(
      wid_paused_window->wid_popup_container, wid_paused_key_down);

    wid_paused_window->log("Game is paused. Relax.");

    {
        auto p = wid_paused_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "PAUSED");

        point tl = {1, 2};
        point br = {width - 3, 4};

        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_paused_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "RESUME");
    }

    wid_update(wid_paused_window->wid_text_area->wid_text_area);
}
