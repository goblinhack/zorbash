//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"
#include "my_game_status.h"

static WidPopup *game_config_top_window;

static void game_config_top_destroy (void)
{
    if (game_config_top_window) {
        delete game_config_top_window;
        game_config_top_window = nullptr;
    }
}

uint8_t game_config_top_graphics (Widp w, int32_t x, int32_t y, uint32_t button)
{
    return (true);
}

uint8_t game_config_top_sound (Widp w, int32_t x, int32_t y, uint32_t button)
{
    return (true);
}

uint8_t game_config_top_other (Widp w, int32_t x, int32_t y, uint32_t button)
{
    game_config_top_destroy();
    game->config_other_select();
    return (true);
}

uint8_t game_config_top_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case SDLK_ESCAPE:
                        game_config_top_destroy();
                        game->main_menu_select();
                        return (true);
                    case 'g':
                        game_config_top_graphics(nullptr, 0, 0, 0);
                        return (true);
                    case 's':
                        game_config_top_sound(nullptr, 0, 0, 0);
                        return (true);
                    case 'o':
                        game_config_top_other(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_top_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_top_select (void)
{_
    CON("Main menu");

    if (game_config_top_window) {
        game_config_top_destroy();
    }
    game_status_fini();

    point tl = {ASCII_WIDTH / 2 - WID_POPUP_WIDTH_NORMAL / 2,
                ASCII_HEIGHT / 2 - 5};
    point br = {ASCII_WIDTH / 2 + WID_POPUP_WIDTH_NORMAL / 2 - 1,
                ASCII_HEIGHT / 2 + 7};
    auto width = br.x - tl.x - 2;

    game_config_top_window = new WidPopup(tl, br, nullptr, "");
    {
        Widp w = game_config_top_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_top_key_up);
        wid_set_on_key_down(w, game_config_top_key_down);
    }

    int y_at = 0;
    {
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "New Game");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_graphics);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$G%%fg=reset$raphics");
    }
    y_at += 3;
    {
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Load Game");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_sound);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ound");
    }
    y_at += 3;
    {
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Other");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_other);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$ther");
    }

    wid_update(game_config_top_window->wid_text_area->wid_text_area);
}
