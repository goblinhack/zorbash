//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"

static WidPopup *game_help_window;

static void game_help_destroy (void)
{
    if (game_help_window) {
        delete game_help_window;
        game_help_window = nullptr;
    }
    game->soft_unpause();
}

uint8_t game_help_dismiss (Widp w, int32_t x, int32_t y, uint32_t button)
{
    game_help_destroy();
    return (false);
}

uint8_t game_help_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case ' ':
                    case SDLK_ESCAPE:
                        game_help_dismiss(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_help_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::help_select (void)
{_
    if (game_help_window) {
        game_help_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    auto n = ASCII_HEIGHT / 2;
    point tl = {m - WID_POPUP_WIDTH_NORMAL / 2, n - 20};
    point br = {m + WID_POPUP_WIDTH_NORMAL / 2, n + 20};
    auto width = br.x - tl.x;

    game_help_window = new WidPopup(tl, br, nullptr, "ui_popup");
    {
        Widp w = game_help_window->wid_popup_container;
        wid_set_on_key_up(w, game_help_key_up);
        wid_set_on_key_down(w, game_help_key_down);
    }

    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log("%%fg=yellow$Arrow Keys %%fg=reset$- movement");
    game_help_window->log("%%fg=yellow$SPACE      %%fg=reset$- swing");
    game_help_window->log("%%fg=yellow$[0-9]      %%fg=reset$- use item");
    game_help_window->log("%%fg=yellow$d          %%fg=reset$- drop item");
    game_help_window->log("%%fg=yellow$o          %%fg=reset$- open/close");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log(" ");
    game_help_window->log("%%fg=red$ESCAPE    %%fg=reset$- dismiss");

    int y_at = 0;
    {
        auto p = game_help_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Help");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_shape_none(w);
        wid_set_on_mouse_up(w, game_help_dismiss);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Keyboard controls");
    }

    y_at = 32;
    {
        auto p = game_help_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Dismiss");

        point tl = {2, y_at};
        point br = {width - 3, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_help_dismiss);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Dismiss");
    }

    wid_update(game_help_window->wid_text_area->wid_text_area);
}
