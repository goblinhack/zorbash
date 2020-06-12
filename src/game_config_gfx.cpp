//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_popup.h"

static WidPopup *game_config_gfx_window;
static bool local_g_need_restart = false;

static void game_config_gfx_destroy (void)
{_
    delete game_config_gfx_window;
    game_config_gfx_window = nullptr;
    game->soft_unpause();
}

uint8_t game_config_gfx_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: reload config");
    game->load_config();
    config_update_all();
    game_config_gfx_destroy();
    game->config_top_select();
    return (true);
}

uint8_t game_config_gfx_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: save config");
    game->save_config();
    game_config_gfx_destroy();
    game->config_top_select();

    if (local_g_need_restart) {
        g_need_restart = true;
    }
    return (true);
}

uint8_t game_config_gfx_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_gfx_destroy();
    game->config_top_select();
    return (true);
}

uint8_t game_config_gfx_vsync_enable_toggle (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: toggle vsync");
    game->config.gfx_vsync_enable = !game->config.gfx_vsync_enable;
    config_gfx_vsync_update();
    game->config_gfx_select();
    return (true);
}

uint8_t game_config_gfx_fullscreen_toggle (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: toggle fullscreen");
    game->config.fullscreen = !game->config.fullscreen;
    game->config_gfx_select();
    local_g_need_restart = true;
    return (true);
}

uint8_t game_config_gfx_allow_highdpi_toggle (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: toggle allow_highdpi");
    game->config.allow_highdpi = !game->config.allow_highdpi;
    game->config_gfx_select();
    local_g_need_restart = true;
    return (true);
}

uint8_t game_config_gfx_inverted_toggle (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: toggle inverted");
    game->config.gfx_inverted = !game->config.gfx_inverted;
    game->config_gfx_select();
    return (true);
}

uint8_t game_config_gfx_resolution_incr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: incr resolution");
    auto res = std::to_string(game->config.outer_pix_width) + "x" +
               std::to_string(game->config.outer_pix_height);
    auto n = SDL_GetNumDisplayModes(0);
    int chosen = 0;
    for (int i = 0; i < n; ++i) {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(0, i, &mode);
        auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
        CON(" - candidate: %s", cand.c_str());
        if (res == cand) {
            chosen = i - 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        SDL_DisplayMode mode;
        if (i == chosen) {
            SDL_GetDisplayMode(0, i, &mode);
            auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
            CON(" - chosen: %s", cand.c_str());
            game->config.outer_pix_width = mode.w;
            game->config.outer_pix_height = mode.h;
            local_g_need_restart = true;
        }
    }
    game_config_gfx_save(nullptr, 0, 0, 0);
    config_update_all();
    game->config_gfx_select();
    return (true);
}

uint8_t game_config_gfx_resolution_decr (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: decr resolution");
    auto res = std::to_string(game->config.outer_pix_width) + "x" +
               std::to_string(game->config.outer_pix_height);
    auto n = SDL_GetNumDisplayModes(0);
    int chosen = 0;
    for (int i = 0; i < n; ++i) {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(0, i, &mode);
        auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
        CON(" - candidate: %s", cand.c_str());
        if (res == cand) {
            chosen = i + 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        SDL_DisplayMode mode;
        if (i == chosen) {
            SDL_GetDisplayMode(0, i, &mode);
            auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
            CON(" - chosen: %s", cand.c_str());
            game->config.outer_pix_width = mode.w;
            game->config.outer_pix_height = mode.h;
            local_g_need_restart = true;
        }
    }
    game_config_gfx_save(nullptr, 0, 0, 0);
    config_update_all();
    game->config_gfx_select();
    return (true);
}

//uint8_t game_config_gfx_zoom_in (Widp w, int32_t x, int32_t y, uint32_t button)
//{_
//    config_gfx_zoom_in();
//    local_g_need_restart = true;
//    game_config_gfx_save(nullptr, 0, 0, 0);
//    game->config_gfx_select();
//    return (true);
//}
//
//uint8_t game_config_gfx_zoom_out (Widp w, int32_t x, int32_t y, uint32_t button)
//{_
//    config_gfx_zoom_out();
//    local_g_need_restart = true;
//    game_config_gfx_save(nullptr, 0, 0, 0);
//    game->config_gfx_select();
//    return (true);
//}

uint8_t game_config_gfx_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                        game_config_gfx_back(nullptr, 0, 0, 0);
                        return (true);
                    case 'c':
                        game_config_gfx_cancel(nullptr, 0, 0, 0);
                        return (true);
                    case 's':
                        game_config_gfx_save(nullptr, 0, 0, 0);
                        return (true);
                    case SDLK_ESCAPE:
                        game_config_gfx_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_gfx_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_gfx_select (void)
{_
    if (game_config_gfx_window) {
        game_config_gfx_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = make_point(m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT - 2);
    point br = make_point(m + WID_POPUP_WIDTH_WIDEST / 2, ACTIONBAR_TL_Y - 2);
    auto width = br.x - tl.x - 2;

    game_config_gfx_window = new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {_
        Widp w = game_config_gfx_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_gfx_key_up);
        wid_set_on_key_down(w, game_config_gfx_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "configuration");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Configuration");
    }

    y_at = 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = make_point(0, y_at);
        point br = make_point(5, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_gfx_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = make_point(width - 14, y_at);
        point br = make_point(width - 9, y_at + 2);
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_config_gfx_save);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Cancel");

        point tl = make_point(width - 7, y_at);
        point br = make_point(width - 0, y_at + 2);
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_config_gfx_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
    }

    y_at += 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Vertical sync");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Vertical sync");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Vertical sync value");

        point tl = make_point(width / 2 , y_at);
        point br = make_point(width / 2 + 6, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_vsync_enable_toggle);

        if (game->config.gfx_vsync_enable) {
            wid_set_text(w, "True");
        } else {
            wid_set_text(w, "False");
        }
    }

    y_at += 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Full screen");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Full screen (restart)");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Full screen value");

        point tl = make_point(width / 2 , y_at);
        point br = make_point(width / 2 + 6, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_fullscreen_toggle);

        if (game->config.fullscreen) {
            wid_set_text(w, "True");
        } else {
            wid_set_text(w, "False");
        }
    }

    y_at += 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "High DPI");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Allow high DPI (restart)");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "High DPI value");

        point tl = make_point(width / 2 , y_at);
        point br = make_point(width / 2 + 6, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_allow_highdpi_toggle);

        if (game->config.allow_highdpi) {
            wid_set_text(w, "True");
        } else {
            wid_set_text(w, "False");
        }
    }

    y_at += 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inverted graphics");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Inverted graphics");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Inverted graphics value");

        point tl = make_point(width / 2 , y_at);
        point br = make_point(width / 2 + 6, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_inverted_toggle);

        if (game->config.gfx_inverted) {
            wid_set_text(w, "True");
        } else {
            wid_set_text(w, "False");
        }
    }

    y_at += 3;
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Resolution");

        point tl = make_point(0, y_at);
        point br = make_point(width / 2, y_at + 2);
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Resolution");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Resolution value");

        point tl = make_point(width / 2 , y_at);
        point br = make_point(width / 2 + 12, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);

        auto res = std::to_string(game->config.outer_pix_width) + "x" +
                   std::to_string(game->config.outer_pix_height);
        wid_set_text(w, res);
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Resolution value +");

        point tl = make_point(width / 2 + 13 , y_at);
        point br = make_point(width / 2 + 15, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_resolution_incr);
        wid_set_text(w, "+");
    }
    {_
        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Resolution value -");

        point tl = make_point(width / 2 + 16 , y_at);
        point br = make_point(width / 2 + 18, y_at + 2);
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_on_mouse_up(w, game_config_gfx_resolution_decr);
        wid_set_text(w, "-");
    }

//    y_at += 3;
//    {_
//        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
//        auto w = wid_new_square_button(p, "Zoom");
//
//        point tl = make_point(0, y_at);
//        point br = make_point(width / 2, y_at + 2);
//        wid_set_shape_none(w);
//        wid_set_pos(w, tl, br);
//        wid_set_text_lhs(w, true);
//        wid_set_text(w, "Zoom");
//    }
//    {_
//        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
//        auto w = wid_new_square_button(p, "Zoom value");
//
//        point tl = make_point(width / 2 , y_at);
//        point br = make_point(width / 2 + 6, y_at + 2);
//        wid_set_style(w, WID_STYLE_DARK);
//        wid_set_pos(w, tl, br);
//        wid_set_text(w, std::to_string(game->config.gfx_zoom));
//    }
//    {_
//        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
//        auto w = wid_new_square_button(p, "Zoom out");
//
//        point tl = make_point(width / 2 + 7 , y_at);
//        point br = make_point(width / 2 + 9, y_at + 2);
//        wid_set_style(w, WID_STYLE_DARK);
//        wid_set_pos(w, tl, br);
//        wid_set_on_mouse_up(w, game_config_gfx_zoom_in);
//        wid_set_text(w, "+");
//    }
//    {_
//        auto p = game_config_gfx_window->wid_text_area->wid_text_area;
//        auto w = wid_new_square_button(p, "Zoom in");
//
//        point tl = make_point(width / 2 + 10 , y_at);
//        point br = make_point(width / 2 + 12, y_at + 2);
//        wid_set_style(w, WID_STYLE_DARK);
//        wid_set_pos(w, tl, br);
//        wid_set_on_mouse_up(w, game_config_gfx_zoom_out);
//        wid_set_text(w, "-");
//    }

    wid_update(game_config_gfx_window->wid_text_area->wid_text_area);
}
