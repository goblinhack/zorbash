//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
// REMOVED #include "my_wid_minicon.h"
// REMOVED #include "my_wid_console.h"
#include "my_wid_popup.h"
// REMOVED #include "my_ascii.h"

static WidPopup *game_config_sound_window;

static void game_config_sound_destroy (void)
{_
    if (game_config_sound_window) {
        delete game_config_sound_window;
        game_config_sound_window = nullptr;
    }
    game->soft_unpause();
}

uint8_t game_config_sound_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: reload config");
    game->load_config();
    game_config_sound_destroy();
    game->config_top_select();
    return (true);
}

uint8_t game_config_sound_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: save config");
    game->save_config();
    game_config_sound_destroy();
    game->config_top_select();
    return (true);
}

uint8_t game_config_sound_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_sound_destroy();
    game->config_top_select();
    return (true);
}

uint8_t game_config_sound_effects_volume_incr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: incr sound_volume");
    game->config.sound_volume++;
    game->config_sound_select();
    return (true);
}

uint8_t game_config_sound_effects_volume_decr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: incr sound_volume");
    game->config.sound_volume--;
    game->config_sound_select();
    return (true);
}

uint8_t game_config_sound_music_volume_incr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: incr music_volume");
    game->config.music_volume++;
    game->config_sound_select();
    return (true);
}

uint8_t game_config_sound_music_volume_decr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: incr music_volume");
    game->config.music_volume--;
    game->config_sound_select();
    return (true);
}

uint8_t game_config_sound_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case 'b':
                        game_config_sound_back(nullptr, 0, 0, 0);
                        return (true);
                    case 'c':
                        game_config_sound_cancel(nullptr, 0, 0, 0);
                        return (true);
                    case 's':
                        game_config_sound_save(nullptr, 0, 0, 0);
                        return (true);
                    case SDLK_ESCAPE:
                        game_config_sound_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_sound_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_sound_select (void)
{_
    if (game_config_sound_window) {
        game_config_sound_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ACTIONBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    game_config_sound_window = new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {_
        Widp w = game_config_sound_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_sound_key_up);
        wid_set_on_key_down(w, game_config_sound_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "configuration");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Configuration");
    }

    y_at = 3;
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = {1, y_at};
        point br = {6, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_sound_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = {width - 16, y_at};
        point br = {width - 11, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_config_sound_save);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Cancel");

        point tl = {width - 9, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_config_sound_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
    }

    y_at += 3;
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Effects volume");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Effects volume");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Effects volume value");

        point tl = {width / 2 , y_at};
        point br = {width / 2 + 6, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w, std::to_string(game->config.sound_volume));
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Effects value +");

        point tl = {width / 2 + 7 , y_at};
        point br = {width / 2 + 9, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_sound_effects_volume_incr);
        wid_set_text(w, "+");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Effects value -");

        point tl = {width / 2 + 10 , y_at};
        point br = {width / 2 + 12, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_sound_effects_volume_decr);
        wid_set_text(w, "-");
    }

    y_at += 3;
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Music volume");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Music volume");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Music volume value");

        point tl = {width / 2 , y_at};
        point br = {width / 2 + 6, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w, std::to_string(game->config.music_volume));
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Music value +");

        point tl = {width / 2 + 7 , y_at};
        point br = {width / 2 + 9, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_sound_music_volume_incr);
        wid_set_text(w, "+");
    }
    {_
        auto p = game_config_sound_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Music value -");

        point tl = {width / 2 + 10 , y_at};
        point br = {width / 2 + 12, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_sound_music_volume_decr);
        wid_set_text(w, "-");
    }

    wid_update(game_config_sound_window->wid_text_area->wid_text_area);
}
