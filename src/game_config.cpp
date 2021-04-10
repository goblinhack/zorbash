//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_game.h"
#include "my_game.h"
#include "my_wid_popup.h"
#include "my_wid_rightbar.h"
#include "my_wid_leftbar.h"
#include "my_wid_inventory.h"
#include "my_wid_skillbox.h"
#include "my_wid_thing_info.h"
#include "my_wid_thing_collect.h"
#include "my_sdl.h"
#include "my_wid.h"
#include "my_ui.h"

static WidPopup *game_config_top_window;

void Config::fini (void)
{_
}

void Config::reset (void)
{_
    game_pix_scale_height        = {};
    game_pix_scale_width         = {};
    game_pix_zoom                = GAME_DEFAULT_PIX_ZOOM;
    one_pixel_height             = {};
    one_pixel_width              = {};
    tile_pix_height              = {};
    tile_pix_width               = {};
    tile_pixel_height            = {};
    tile_pixel_width             = {};
    ui_pix_scale_height          = {};
    ui_pix_scale_width           = {};
    ui_pix_zoom                  = GAME_DEFAULT_UI_ZOOM;
    video_w_h_ratio              = {};
    debug_mode                   = false;
    fps_counter                  = false;
    gfx_allow_highdpi            = false;
    gfx_borderless               = true;
    gfx_fullscreen               = false;
    gfx_fullscreen_desktop       = true;
    gfx_inverted                 = false;
    gfx_lights                   = true;
    gfx_minimap                  = true;
    gfx_show_hidden              = false;
    gfx_vsync_enable             = true;
    config_pix_height            = {};
    config_pix_width             = {};
    game_pix_height              = {};
    game_pix_width               = {};
    ui_pix_height                = {};
    ui_pix_width                 = {};
    window_pix_height            = {};
    window_pix_width             = {};
    ascii_gl_height              = {};
    ascii_gl_width               = {};

    key_action0                  = {SDL_SCANCODE_0};
    key_action1                  = {SDL_SCANCODE_1};
    key_action2                  = {SDL_SCANCODE_2};
    key_action3                  = {SDL_SCANCODE_3};
    key_action4                  = {SDL_SCANCODE_4};
    key_action5                  = {SDL_SCANCODE_5};
    key_action6                  = {SDL_SCANCODE_6};
    key_action7                  = {SDL_SCANCODE_7};
    key_action8                  = {SDL_SCANCODE_8};
    key_action9                  = {SDL_SCANCODE_9};
    key_attack                   = {SDL_SCANCODE_SPACE};
#ifdef __APPLE__
    //
    // Delete on mac seems to map to backspace...
    //
    key_drop                     = {SDL_SCANCODE_BACKSPACE};
#else
    key_drop                     = {SDL_SCANCODE_DELETE};
#endif
    key_eat                      = {SDL_SCANCODE_E};
    key_help                     = {SDL_SCANCODE_H};
    key_jump                     = {SDL_SCANCODE_J};
    key_load                     = {SDL_SCANCODE_F11};
    key_map_down                 = {SDL_SCANCODE_DOWN};
    key_map_left                 = {SDL_SCANCODE_LEFT};
    key_map_right                = {SDL_SCANCODE_RIGHT};
    key_map_up                   = {SDL_SCANCODE_UP};
    key_move_down                = {SDL_SCANCODE_S};
    key_move_left                = {SDL_SCANCODE_A};
    key_move_right               = {SDL_SCANCODE_D};
    key_move_up                  = {SDL_SCANCODE_W};
    key_pause                    = {SDL_SCANCODE_P};
    key_quit                     = {SDL_SCANCODE_Q};
    key_save                     = {SDL_SCANCODE_F12};
    key_screenshot               = {SDL_SCANCODE_F10};
    key_throw                    = {SDL_SCANCODE_T};
    key_inventory                = {SDL_SCANCODE_I};
    key_console                  = {SDL_SCANCODE_TAB};
    key_unused3                  = 0;
    key_unused4                  = 0;
    key_unused5                  = 0;
    key_use                      = {SDL_SCANCODE_U};
    key_wait_or_collect          = {SDL_SCANCODE_PERIOD};
    key_zoom_in                  = {SDL_SCANCODE_Z};
    key_zoom_out                 = {SDL_SCANCODE_X};
    music_volume                 = {MIX_MAX_VOLUME / 3};
    sdl_delay                    = 1;
    sound_volume                 = {MIX_MAX_VOLUME / 2};
}

static void game_config_top_destroy (void)
{_
    delete game_config_top_window;
    game_config_top_window = nullptr;
}

static uint8_t game_config_top_graphics (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_gfx_select();
    return true;
}

static uint8_t game_config_top_keyboard (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_keyboard_select();
    return true;
}

static uint8_t game_config_top_sound (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_sound_select();
    return true;
}

static uint8_t game_config_top_other (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->config_other_select();
    return true;
}

static uint8_t game_config_top_back (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    game_config_top_destroy();
    game->main_menu_select();
    return true;
}

static uint8_t game_config_top_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case 'g':
                        game_config_top_graphics(nullptr, 0, 0, 0);
                        return true;
                    case 's':
                        game_config_top_sound(nullptr, 0, 0, 0);
                        return true;
                    case 'k':
                        game_config_top_keyboard(nullptr, 0, 0, 0);
                        return true;
                    case 'o':
                        game_config_top_other(nullptr, 0, 0, 0);
                        return true;
                    case 'b':
                    case SDLK_ESCAPE:
                        game_config_top_back(nullptr, 0, 0, 0);
                        return true;
                }
            }
        }
    }

    return false;
}

static uint8_t game_config_top_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    return true;
}

void Game::config_top_select (void)
{_
    CON("Main menu");

    if (game_config_top_window) {
        game_config_top_destroy();
    }
    wid_rightbar_fini();
    wid_leftbar_fini();
    wid_inventory_fini();
    wid_skillbox_fini();
    wid_thing_info_fini();
    wid_thing_collect_fini();

    point tl = make_point(
                TERM_WIDTH / 2 - UI_WID_POPUP_WIDTH_NORMAL / 2,
                TERM_HEIGHT / 2 - 4);
    point br = make_point(
                TERM_WIDTH / 2 + UI_WID_POPUP_WIDTH_NORMAL / 2 - 1,
                TERM_HEIGHT / 2 + 14);
    auto width = br.x - tl.x - 2;

    game_config_top_window = new WidPopup("Main menu",
                                          tl, br, nullptr, "nothing", false, false);
    {_
        Widp w = game_config_top_window->wid_popup_container;
        wid_set_on_key_up(w, game_config_top_key_up);
        wid_set_on_key_down(w, game_config_top_key_down);
    }

    int y_at = 0;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "graphics");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_graphics);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$G%%fg=reset$raphics");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "sound");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_sound);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$S%%fg=reset$ound and music");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "keyboard");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_keyboard);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$K%%fg=reset$eyboard");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Other stuffs");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_other);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$O%%fg=reset$ther stuffs");
    }
    y_at += 3;
    {_
        auto p = game_config_top_window->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "Back");

        point tl = make_point(0, y_at);
        point br = make_point(width, y_at + 2);
        wid_set_style(w, UI_WID_STYLE_NORMAL);
        wid_set_on_mouse_up(w, game_config_top_back);
        wid_set_pos(w, tl, br);
        wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
    }

    wid_update(game_config_top_window->wid_text_area->wid_text_area);
}
