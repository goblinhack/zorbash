//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_popup.h"
#include "my_game_notice.h"

static WidPopup *game_config_keyboard_window;

//
// Check for saving keys to config can fit
//
static_assert(sizeof(SDL_Scancode) <= sizeof(game->config.key_move_left));

static void game_config_keyboard_destroy (void)
{_
    delete game_config_keyboard_window;
    game_config_keyboard_window = nullptr;
    game->soft_unpause();
}

uint8_t game_config_keyboard_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: reload config");
    game->load_config();
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

uint8_t game_config_keyboard_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    CON("USERCFG: save config");
    game->save_config();
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

uint8_t game_config_keyboard_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_keyboard_destroy();
    if (game->started) {
        //
        // Back to the game
        //
    } else {
        game->config_top_select();
    }
    return (true);
}

static void game_config_key_move_left_set (SDL_Scancode code)
{_
    game->config.key_move_left = code;
    game->config_keyboard_select();
}

static void game_config_key_move_right_set (SDL_Scancode code)
{_
    game->config.key_move_right = code;
    game->config_keyboard_select();
}

static void game_config_key_move_up_set (SDL_Scancode code)
{_
    game->config.key_move_up = code;
    game->config_keyboard_select();
}

static void game_config_key_move_down_set (SDL_Scancode code)
{_
    game->config.key_move_down = code;
    game->config_keyboard_select();
}

static void game_config_key_map_left_set (SDL_Scancode code)
{_
    game->config.key_map_left = code;
    game->config_keyboard_select();
}

static void game_config_key_map_right_set (SDL_Scancode code)
{_
    game->config.key_map_right = code;
    game->config_keyboard_select();
}

static void game_config_key_map_up_set (SDL_Scancode code)
{_
    game->config.key_map_up = code;
    game->config_keyboard_select();
}

static void game_config_key_map_down_set (SDL_Scancode code)
{_
    game->config.key_map_down = code;
    game->config_keyboard_select();
}

static void game_config_key_attack_set (SDL_Scancode code)
{_
    game->config.key_attack = code;
    game->config_keyboard_select();
}

static void game_config_key_wait_set (SDL_Scancode code)
{_
    game->config.key_wait = code;
    game->config_keyboard_select();
}

static void game_config_key_save_set (SDL_Scancode code)
{_
    game->config.key_save = code;
    game->config_keyboard_select();
}

static void game_config_key_load_set (SDL_Scancode code)
{_
    game->config.key_load = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_in_set (SDL_Scancode code)
{_
    game->config.key_zoom_in = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_out_set (SDL_Scancode code)
{_
    game->config.key_zoom_out = code;
    game->config_keyboard_select();
}

static void game_config_key_pause_set (SDL_Scancode code)
{_
    game->config.key_pause = code;
    game->config_keyboard_select();
}

static void game_config_key_help_set (SDL_Scancode code)
{_
    game->config.key_help = code;
    game->config_keyboard_select();
}

static void game_config_key_quit_set (SDL_Scancode code)
{_
    game->config.key_quit = code;
    game->config_keyboard_select();
}

static void grab_key (void) 
{_
    game_notice("Press any key");
    g_grab_next_key = true;
}

uint8_t game_config_keyboard_profile_arrow_keys (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_UP;
    game->config.key_move_left  = SDL_SCANCODE_LEFT;
    game->config.key_move_down  = SDL_SCANCODE_DOWN;
    game->config.key_move_right = SDL_SCANCODE_RIGHT;
    game->config.key_map_up     = SDL_SCANCODE_W;
    game->config.key_map_left   = SDL_SCANCODE_A;
    game->config.key_map_down   = SDL_SCANCODE_S;
    game->config.key_map_right  = SDL_SCANCODE_D;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_keyboard_profile_wasd (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game->config.key_move_up    = SDL_SCANCODE_W;
    game->config.key_move_left  = SDL_SCANCODE_A;
    game->config.key_move_down  = SDL_SCANCODE_S;
    game->config.key_move_right = SDL_SCANCODE_D;
    game->config.key_map_up     = SDL_SCANCODE_UP;
    game->config.key_map_left   = SDL_SCANCODE_LEFT;
    game->config.key_map_down   = SDL_SCANCODE_DOWN;
    game->config.key_map_right  = SDL_SCANCODE_RIGHT;
    game->config_keyboard_select();

    return (true);
}

uint8_t game_config_key_move_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_left_set;
    return (true);
}

uint8_t game_config_key_move_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_right_set;
    return (true);
}

uint8_t game_config_key_move_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_up_set;
    return (true);
}

uint8_t game_config_key_move_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_move_down_set;
    return (true);
}

uint8_t game_config_key_map_left (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_left_set;
    return (true);
}

uint8_t game_config_key_map_right (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_right_set;
    return (true);
}

uint8_t game_config_key_map_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_up_set;
    return (true);
}

uint8_t game_config_key_map_down (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_map_down_set;
    return (true);
}

uint8_t game_config_key_attack (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_attack_set;
    return (true);
}

uint8_t game_config_key_wait (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_wait_set;
    return (true);
}

uint8_t game_config_key_save (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_save_set;
    return (true);
}

uint8_t game_config_key_load (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_load_set;
    return (true);
}

uint8_t game_config_key_zoom_in (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_in_set;
    return (true);
}

uint8_t game_config_key_zoom_out (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_out_set;
    return (true);
}

uint8_t game_config_key_pause (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_pause_set;
    return (true);
}

uint8_t game_config_key_help (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_help_set;
    return (true);
}

uint8_t game_config_key_quit (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    grab_key();
    on_sdl_key_grab = game_config_key_quit_set;
    return (true);
}

uint8_t game_config_keyboard_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                        game_config_keyboard_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_keyboard_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_keyboard_select (void)
{_
    game_notice_destroy();

    if (game_config_keyboard_window) {
        game_config_keyboard_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ACTIONBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    game_config_keyboard_window =
                    new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {_
        Widp w = game_config_keyboard_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_keyboard_key_up);
        wid_set_on_key_down(w, game_config_keyboard_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "The keys of mighty power");

        point tl = {0, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "The keys of mighty power");
    }

    y_at = 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = {1, y_at};
        point br = {8, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_back);
        wid_set_pos(w, tl, br);
        if (started) {
            wid_set_text(w, "Resume");
        } else {
            wid_set_text(w, "Back");
        }
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = {width - 16, y_at};
        point br = {width - 11, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_config_keyboard_save);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Save");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Cancel");

        point tl = {width - 9, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_style(w, WID_STYLE_RED);
        wid_set_on_mouse_up(w, game_config_keyboard_cancel);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Cancel");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = {0, y_at};
        point br = {46, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_wasd);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use W,A,S,D for moving, arrow keys for map");
    }
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "");

        point tl = {0, y_at};
        point br = {46, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_on_mouse_up(w, game_config_keyboard_profile_arrow_keys);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Use arrow keys for moving, W,A,S,D for map");
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Move up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move up");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_up));
        wid_set_on_mouse_up(w, game_config_key_move_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move left
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move left");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_left));
        wid_set_on_mouse_up(w, game_config_key_move_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move down
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move down");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_down));
        wid_set_on_mouse_up(w, game_config_key_move_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Move right
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move right");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_move_right));
        wid_set_on_mouse_up(w, game_config_key_move_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // Map up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map up");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map up");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_up));
        wid_set_on_mouse_up(w, game_config_key_map_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map left
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map left");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map left");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_left));
        wid_set_on_mouse_up(w, game_config_key_map_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map down
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map down");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map down");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_down));
        wid_set_on_mouse_up(w, game_config_key_map_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // Map right
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Map right");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Map right");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_map_right));
        wid_set_on_mouse_up(w, game_config_key_map_right);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // attack
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Attack");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Attack");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_attack));
        wid_set_on_mouse_up(w, game_config_key_attack);
    }
    ///////////////////////////////////////////////////////////////////////
    // wait
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Wait");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Wait / pass time");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_wait));
        wid_set_on_mouse_up(w, game_config_key_wait);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // save
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Save game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_save));
        wid_set_on_mouse_up(w, game_config_key_save);
    }
    ///////////////////////////////////////////////////////////////////////
    // load
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "load");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Load game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_load));
        wid_set_on_mouse_up(w, game_config_key_load);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // zoom_in
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_in");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom in");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_zoom_in));
        wid_set_on_mouse_up(w, game_config_key_zoom_in);
    }
    ///////////////////////////////////////////////////////////////////////
    // zoom_out
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_out");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom out");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_zoom_out));
        wid_set_on_mouse_up(w, game_config_key_zoom_out);
    }

    ///////////////////////////////////////////////////////////////////////
    y_at++;
    ///////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    // pause
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "pause");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Pause game");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_pause));
        wid_set_on_mouse_up(w, game_config_key_pause);
    }
    ///////////////////////////////////////////////////////////////////////
    // quit
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "quit");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Quit");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_quit));
        wid_set_on_mouse_up(w, game_config_key_quit);
    }
    ///////////////////////////////////////////////////////////////////////
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "help");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "This help");
    }
    {_
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_help));
        wid_set_on_mouse_up(w, game_config_key_help);
    }

    wid_update(game_config_keyboard_window->wid_text_area->wid_text_area);
}
