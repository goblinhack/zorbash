/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <sstream>
#include "minilzo.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_game_error.h"
#include "my_traceback.h"

static WidPopup *wid_error_window;

static void wid_error_destroy (void)
{
    if (wid_error_window) {
        delete wid_error_window;
        wid_error_window = nullptr;
    }
    game->hard_unpause();
}

uint8_t wid_error_key_up (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case '\n':
                    case SDLK_ESCAPE: {
                        wid_error_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_error_key_down (Widp w, const struct SDL_KEYSYM *key)
{
    return (true);
}

uint8_t wid_error_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{
    wid_error_destroy();
    return (true);
}

void wid_error (std::string error)
{_
    ERR("%s", error.c_str());
    wid_toggle_hidden(wid_console_window);

    if (wid_error_window) {
        wid_error_destroy();
    }
    game->hard_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ITEMBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    wid_error_window =
      new WidPopup(tl, br, tile_find_mand("bug"), "ui_popup_widest");
    wid_set_on_key_up(
      wid_error_window->wid_popup_container, wid_error_key_up);
    wid_set_on_key_down(
      wid_error_window->wid_popup_container, wid_error_key_down);

    wid_error_window->log("ERROR: %%fg=red$" + error);
    wid_error_window->log(" ");
    wid_error_window->log("Press ESCAPE to dismiss this window");
    wid_error_window->log(" ");
    wid_error_window->log(" ");
    wid_error_window->log(" ");
    wid_error_window->log(" ");
    wid_error_window->log(" ");
    wid_error_window->log("If a bug, send a screenshot to %%fg=white$goblinhack@gmail.com");
    wid_error_window->log(" ");

    {
        auto tb = new Traceback();
        tb->init();
        auto s = tb->to_string();
            wid_error_window->log(s);
    }

    {
        auto p = wid_error_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "dismiss");

        point tl = {1, 4};
        point br = {width - 3, 6};

        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, wid_error_mouse_up);

        wid_set_pos(w, tl, br);
        wid_set_text(w, "ok");
    }

    wid_update(wid_error_window->wid_text_area->wid_text_area);
}
