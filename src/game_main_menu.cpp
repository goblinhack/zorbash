//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
// REMOVED #include "my_wid_console.h"
#include "my_wid_popup.h"
// REMOVED #include "my_ascii.h"
// REMOVED #include "my_time.h"
#include "my_game_status.h"
#include "my_gl.h"

static WidPopup *game_main_menu_window;

static void game_main_menu_destroy (void)
{_
    delete game_main_menu_window;
    game_main_menu_window = nullptr;
}

void game_main_menu_hide (void)
{_
    wid_hide(game_main_menu_window->wid_text_area->wid_text_area);
}

uint8_t game_main_menu_new_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_main_menu_destroy();
    game->init();
    game_status_fini();
    game_status_wid_init();
    wid_minicon_fini();
    wid_minicon_init();
    wid_visible(wid_minicon_window);
    MINICON("Welcome to the lair of %%fg=red$Zorbash%%fg=reset$. Stay awhile, stay forever...");
    return (false);
}

uint8_t game_main_menu_load_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->load_select();
    return (false);
}

uint8_t game_main_menu_config (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config_top_select();
    game_main_menu_hide();
    return (false);
}

uint8_t game_main_menu_quit_game (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->quit_select();
    return (false);
}

uint8_t game_main_menu_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                    case 'n':
                        game_main_menu_new_game(nullptr, 0, 0, 0);
                        return (true);
                    case 'l':
                        game_main_menu_load_game(nullptr, 0, 0, 0);
                        return (true);
                    case 'o':
                        game_main_menu_config(nullptr, 0, 0, 0);
                        return (true);
                    case 'q':
                        game_main_menu_quit_game(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_main_menu_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void game_main_menu_tick (Widp w)
{_
    static int frame = 1;
    static timestamp_t ts;

    if (time_have_x_tenths_passed_since(1, ts)) {
        frame++;
        if (frame > 64) {
            frame = 1;
        }
        ts = time_get_time_ms_cached();
    }
    std::string t = "title" + std::to_string(frame);
    blit_init();
    tile_blit(tile_find_mand(t.c_str()),
              spoint(0,0),
              spoint(game->config.outer_pix_width,
                     game->config.outer_pix_height));
    blit_flush();

    ascii_putf(1, ASCII_HEIGHT - 2, GREEN, BLACK, L"Version " VERSION);

    if (game->started) {
        game_main_menu_destroy();
    }
}

void Game::main_menu_select (void)
{_
    CON("Main menu");

    if (game_main_menu_window) {
        game_main_menu_destroy();
    }
    game_status_fini();

    point tl = {ASCII_WIDTH - WID_POPUP_WIDTH_NORMAL - 1, ASCII_HEIGHT - 16};
    point br = {ASCII_WIDTH - 7, ASCII_HEIGHT - 1};
    auto width = br.x - tl.x - 2;

    game_main_menu_window = new WidPopup(tl, br, nullptr, "");
    {_
        Widp w = game_main_menu_window->wid_popup_container;
        wid_set_on_key_up(w, game_main_menu_key_up);
        wid_set_on_key_down(w, game_main_menu_key_down);
        wid_set_on_tick(w, game_main_menu_tick);
    }

    int y_at = 0;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "New Game");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_new_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$N%%fg=reset$ew game");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Load Game");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_load_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$L%%fg=reset$oad game");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Options");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_config);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$ptions");
    }
    y_at += 3;
    {_
        auto p = game_main_menu_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Quit Game");

        point tl = {0, y_at};
        point br = {width, y_at + 2};
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_main_menu_quit_game);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$Q%%fg=reset$uit Game");
    }

    wid_update(game_main_menu_window->wid_text_area->wid_text_area);
}

void Game::new_game (void)
{_
    game_main_menu_new_game(nullptr, 0, 0, 0);
}
