//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *wid_config_window;

static void wid_config_destroy (void)
{
    if (wid_config_window) {
        delete wid_config_window;
        wid_config_window = nullptr;
    }
    game->soft_unpause();
}

uint8_t wid_config_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{
    wid_config_destroy();
    return (false);
}

uint8_t wid_config_save (Widp w, int32_t x, int32_t y, uint32_t button)
{
    wid_config_destroy();
    return (false);
}

uint8_t wid_config_key_up (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case 'c':
                        wid_config_cancel(nullptr, 0, 0, 0);
                        return (true);
                    case 's':
                        wid_config_save(nullptr, 0, 0, 0);
                        return (true);
                    case SDLK_ESCAPE:
                        wid_config_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t wid_config_key_down (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
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

void Game::config_select (void)
{_
    if (wid_config_window) {
        wid_config_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ITEMBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    wid_config_window = new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {
        Widp w = wid_config_window->wid_popup_container;
        wid_set_on_key_up(w, wid_config_key_up);
        wid_set_on_key_down(w, wid_config_key_down);
    }

    int y_at = 0;
    {
        auto p = wid_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "configuration");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Configuration");
    }

    y_at = 3;
    {
        auto p = wid_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = {width - 16, y_at};
        point br = {width - 11, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, wid_config_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
    }
    {
        auto p = wid_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Cancel");

        point tl = {width - 9, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_config_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
    }

    y_at += 3;
    {
        auto p = wid_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Debug mode");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Debug mode");
    }
    {
        auto p = wid_config_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = {width / 2 , y_at};
        point br = {width / 2 + 6, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "False");
    }

    wid_update(wid_config_window->wid_text_area->wid_text_area);
}
