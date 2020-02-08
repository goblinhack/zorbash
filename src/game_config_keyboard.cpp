//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_ascii.h"
#include "my_game_notice.h"

static WidPopup *game_config_keyboard_window;

//
// Check for saving keys to config can fit
//
static_assert(sizeof(SDL_Scancode) <= sizeof(game->config.key_left));

static void game_config_keyboard_destroy (void)
{
    if (game_config_keyboard_window) {
        delete game_config_keyboard_window;
        game_config_keyboard_window = nullptr;
    }
    game->soft_unpause();
}

uint8_t game_config_keyboard_cancel (Widp w, int32_t x, int32_t y, uint32_t button)
{
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
{
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
{
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

static void game_config_key_left_set (SDL_Scancode code)
{
    game->config.key_left = code;
    game->config_keyboard_select();
}

static void game_config_key_right_set (SDL_Scancode code)
{
    game->config.key_right = code;
    game->config_keyboard_select();
}

static void game_config_key_up_set (SDL_Scancode code)
{
    game->config.key_up = code;
    game->config_keyboard_select();
}

static void game_config_key_down_set (SDL_Scancode code)
{
    game->config.key_down = code;
    game->config_keyboard_select();
}

static void game_config_key_attack_set (SDL_Scancode code)
{
    game->config.key_attack = code;
    game->config_keyboard_select();
}

static void game_config_key_wait_set (SDL_Scancode code)
{
    game->config.key_wait = code;
    game->config_keyboard_select();
}

static void game_config_key_save_set (SDL_Scancode code)
{
    game->config.key_save = code;
    game->config_keyboard_select();
}

static void game_config_key_load_set (SDL_Scancode code)
{
    game->config.key_load = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_in_set (SDL_Scancode code)
{
    game->config.key_zoom_in = code;
    game->config_keyboard_select();
}

static void game_config_key_zoom_out_set (SDL_Scancode code)
{
    game->config.key_zoom_out = code;
    game->config_keyboard_select();
}

static void game_config_key_pause_set (SDL_Scancode code)
{
    game->config.key_pause = code;
    game->config_keyboard_select();
}

static void game_config_key_help_set (SDL_Scancode code)
{
    game->config.key_help = code;
    game->config_keyboard_select();
}

static void grab_key (void) 
{
    game_notice("Press any key");
    sdl_grab_next_key = true;
}

uint8_t game_config_key_left (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_left_set;
    return (true);
}

uint8_t game_config_key_right (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_right_set;
    return (true);
}

uint8_t game_config_key_up (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_up_set;
    return (true);
}

uint8_t game_config_key_down (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_down_set;
    return (true);
}

uint8_t game_config_key_attack (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_attack_set;
    return (true);
}

uint8_t game_config_key_wait (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_wait_set;
    return (true);
}

uint8_t game_config_key_save (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_save_set;
    return (true);
}

uint8_t game_config_key_load (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_load_set;
    return (true);
}

uint8_t game_config_key_zoom_in (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_in_set;
    return (true);
}

uint8_t game_config_key_zoom_out (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_zoom_out_set;
    return (true);
}

uint8_t game_config_key_pause (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_pause_set;
    return (true);
}

uint8_t game_config_key_help (Widp w, int32_t x, int32_t y, uint32_t button)
{
    grab_key();
    on_sdl_key_grab = game_config_key_help_set;
    return (true);
}

uint8_t game_config_keyboard_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                        game_config_keyboard_cancel(nullptr, 0, 0, 0);
                        return (true);
                }
            }
        }
    }

    return (false);
}

uint8_t game_config_keyboard_key_down (Widp w, const struct SDL_KEYSYM *key)
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

void Game::config_keyboard_select (void)
{_
    game_notice_destroy();

    if (game_config_keyboard_window) {
        game_config_keyboard_destroy();
    }
    game->soft_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDEST / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDEST / 2, ITEMBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    game_config_keyboard_window =
                    new WidPopup(tl, br, nullptr, "ui_popup_widest");
    {
        Widp w = game_config_keyboard_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_keyboard_key_up);
        wid_set_on_key_down(w, game_config_keyboard_key_down);
    }

    int y_at = 0;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "The keys of mighty power");

        point tl = {0, y_at};
        point br = {width - 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "The keys of mighty power");
    }

    y_at = 3;
    {
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
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Save");

        point tl = {width - 16, y_at};
        point br = {width - 11, y_at + 2};
        wid_set_style(w, WID_STYLE_GREEN);
        wid_set_on_mouse_up(w, game_config_keyboard_save);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "Save");
    }
    {
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
    // left
    ///////////////////////////////////////////////////////////////////////
    y_at += 4;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move left");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move left");
    }
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_left));
        wid_set_on_mouse_up(w, game_config_key_left);
    }
    ///////////////////////////////////////////////////////////////////////
    // right
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move right");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move right");
    }
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_right));
        wid_set_on_mouse_up(w, game_config_key_right);
    }
    ///////////////////////////////////////////////////////////////////////
    // up
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move up");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move up");
    }
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_up));
        wid_set_on_mouse_up(w, game_config_key_up);
    }
    ///////////////////////////////////////////////////////////////////////
    // down
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Move down");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move down");
    }
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "value");

        point tl = {width / 2 + 8, y_at};
        point br = {width / 2 + 22, y_at + 2};
        wid_set_style(w, WID_STYLE_DARK);
        wid_set_pos(w, tl, br);
        wid_set_text(w,
          SDL_GetScancodeName((SDL_Scancode)game->config.key_down));
        wid_set_on_mouse_up(w, game_config_key_down);
    }
    ///////////////////////////////////////////////////////////////////////
    // attack
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Attack");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move attack");
    }
    {
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
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Wait");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Move wait");
    }
    {
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
    // save
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Save game");
    }
    {
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
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "load");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Load game");
    }
    {
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
    // zoom_in
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_in");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom in");
    }
    {
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
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "zoom_out");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Zoom out");
    }
    {
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
    // pause
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "pause");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "Pause game");
    }
    {
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
    // help
    ///////////////////////////////////////////////////////////////////////
    y_at += 3;
    {
        auto p = game_config_keyboard_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "help");

        point tl = {0, y_at};
        point br = {width / 2, y_at + 2};
        wid_set_shape_none(w);
        wid_set_pos(w, tl, br);
        wid_set_text_lhs(w, true);
        wid_set_text(w, "This help");
    }
    {
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
