//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
// REMOVED #include "my_wid_minicon.h"
// REMOVED #include "my_wid_console.h"
#include "my_wid_popup.h"
// REMOVED #include "my_ascii.h"
#include "my_game_status.h"

static WidPopup *game_config_top_window;

static void game_config_top_destroy (void)
{_
    delete game_config_top_window;
    game_config_top_window = nullptr;
}

uint8_t game_config_top_graphics (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_gfx_select();
    return (true);
}

uint8_t game_config_top_keyboard (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_keyboard_select();
    return (true);
}

uint8_t game_config_top_sound (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_sound_select();
    return (true);
}

uint8_t game_config_top_other (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_other_select();
    return (true);
}

uint8_t game_config_top_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->main_menu_select();
    return (true);
}

uint8_t game_config_top_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case 'k':
                        game_config_top_keyboard(nullptr, 0, 0, 0);
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

void Game::config_top_select (void)
{_
    CON("Main menu");

    if (game_config_top_window) {
        game_config_top_destroy();
    }
    game_status_fini();

    point tl = {ASCII_WIDTH / 2 - WID_POPUP_WIDTH_NORMAL / 2,
                ASCII_HEIGHT / 2 - 4};
    point br = {ASCII_WIDTH / 2 + WID_POPUP_WIDTH_NORMAL / 2 - 1,
                ASCII_HEIGHT / 2 + 14};
    auto width = br.x - tl.x - 2;

    game_config_top_window = new WidPopup(tl, br, nullptr, "");
    {_
        Widp w = game_config_top_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_top_key_up);
        wid_set_on_key_down(w, game_config_top_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "graphics");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_graphics);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$G%%fg=reset$raphics");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "sound");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_sound);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ound and music");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "keyboard");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_keyboard);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$K%%fg=reset$eyboard");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Other stuffs");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_other);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$ther stuffs");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
    }

    wid_update(game_config_top_window->wid_text_area->wid_text_area);
}
