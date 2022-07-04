//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include <SDL_mixer.h>

WidPopup *wid_config_top_window;

void Config::fini(void) { TRACE_AND_INDENT(); }

void Config::reset(void)
{
  TRACE_AND_INDENT();
  debug_mode             = false;
  fps_counter            = false;
  game_pix_scale_height  = {};
  game_pix_scale_width   = {};
  game_pix_zoom          = GAME_DEFAULT_PIX_ZOOM;
  gfx_allow_highdpi      = false;
  gfx_borderless         = true;
  gfx_fullscreen         = false;
  one_pixel_height       = {};
  one_pixel_width        = {};
  tile_pixel_height      = {};
  tile_pixel_width       = {};
  tile_pix_height        = {};
  tile_pix_width         = {};
  ui_pix_zoom            = GAME_DEFAULT_UI_ZOOM;
  ui_ascii_term_height   = {TERM_ASCII_HEIGHT_DEF};
  ui_ascii_term_width    = {TERM_ASCII_WIDTH_DEF};
  ui_gfx_term_height     = {TERM_GFX_HEIGHT_DEF};
  ui_gfx_term_width      = {TERM_GFX_WIDTH_DEF};
  video_w_h_ratio        = {};
  gfx_fullscreen_desktop = true;
  gfx_inverted           = false;
  gfx_show_hidden        = false;
  gfx_vsync_enable       = true;
  gfx_vsync_locked       = false;
  mouse_wheel_lr_negated = false;
  mouse_wheel_ud_negated = false;
  config_pix_height      = {};
  config_pix_width       = {};
  game_pix_height        = {};
  game_pix_width         = {};
  ui_pix_height          = {};
  ui_pix_width           = {};
  window_pix_height      = {};
  window_pix_width       = {};
  ascii_gl_height        = {};
  ascii_gl_width         = {};

  key_action0.sym         = SDLK_0;
  key_action1.sym         = SDLK_1;
  key_action2.sym         = SDLK_2;
  key_action3.sym         = SDLK_3;
  key_action4.sym         = SDLK_4;
  key_action5.sym         = SDLK_5;
  key_action6.sym         = SDLK_6;
  key_action7.sym         = SDLK_7;
  key_action8.sym         = SDLK_8;
  key_action9.sym         = SDLK_9;
  key_skill0.sym          = SDLK_0;
  key_skill0.mod          = KMOD_SHIFT;
  key_skill1.sym          = SDLK_1;
  key_skill1.mod          = KMOD_SHIFT;
  key_skill2.sym          = SDLK_2;
  key_skill2.mod          = KMOD_SHIFT;
  key_skill3.sym          = SDLK_3;
  key_skill3.mod          = KMOD_SHIFT;
  key_skill4.sym          = SDLK_4;
  key_skill4.mod          = KMOD_SHIFT;
  key_skill5.sym          = SDLK_5;
  key_skill5.mod          = KMOD_SHIFT;
  key_skill6.sym          = SDLK_6;
  key_skill6.mod          = KMOD_SHIFT;
  key_skill7.sym          = SDLK_7;
  key_skill7.mod          = KMOD_SHIFT;
  key_skill8.sym          = SDLK_8;
  key_skill8.mod          = KMOD_SHIFT;
  key_skill9.sym          = SDLK_9;
  key_skill9.mod          = KMOD_SHIFT;
  key_attack.sym          = SDLK_SPACE;
  key_drop.sym            = SDLK_BACKSPACE;
  key_eat.sym             = SDLK_e;
  key_help.sym            = SDLK_h;
  key_jump.sym            = SDLK_j;
  key_load.sym            = SDLK_F11;
  key_map_down.sym        = SDLK_DOWN;
  key_map_left.sym        = SDLK_LEFT;
  key_map_right.sym       = SDLK_RIGHT;
  key_map_up.sym          = SDLK_UP;
  key_move_down.sym       = SDLK_s;
  key_move_left.sym       = SDLK_a;
  key_move_right.sym      = SDLK_d;
  key_move_up.sym         = SDLK_w;
  key_quit.sym            = SDLK_q;
  key_save.sym            = SDLK_F12;
  key_screenshot.sym      = SDLK_F10;
  key_throw.sym           = SDLK_t;
  key_inventory.sym       = SDLK_i;
  key_console.sym         = SDLK_TAB;
  key_console.mod         = KMOD_SHIFT;
  key_robot_mode.sym      = SDLK_r;
  key_gfx_toggle.sym      = SDLK_TAB;
  key_descend.sym         = SDLK_GREATER;
  key_ascend.sym          = SDLK_LESS;
  key_use.sym             = SDLK_u;
  key_wait_or_collect.sym = SDLK_PERIOD;
  key_zoom_in.sym         = SDLK_z;
  key_zoom_out.sym        = SDLK_x;
  music_volume            = {MIX_MAX_VOLUME / 3};
  sdl_delay               = 1;
  snapshot_freq           = ENABLE_SAVE_SNAPSHOT_FREQ;
  sound_volume            = {MIX_MAX_VOLUME / 2};
}

static void wid_config_top_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_config_top_window;
  wid_config_top_window = nullptr;
}

static uint8_t wid_config_top_gfx(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_top_mouse(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_config_mouse_select();
  return true;
}

static uint8_t wid_config_top_keyboard(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_config_keyboard_select();
  return true;
}

static uint8_t wid_config_top_sound(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_config_sound_select();
  return true;
}

static uint8_t wid_config_top_other(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_config_other_select();
  return true;
}

static uint8_t wid_config_top_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_top_destroy();
  game->wid_main_menu_select();
  return true;
}

static uint8_t wid_config_top_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL:
    case KMOD_RCTRL:
    default:
      switch (key->sym) {
        default:
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'g': wid_config_top_gfx(nullptr, 0, 0, 0); return true;
              case 'm': wid_config_top_mouse(nullptr, 0, 0, 0); return true;
              case 's': wid_config_top_sound(nullptr, 0, 0, 0); return true;
              case 'k': wid_config_top_keyboard(nullptr, 0, 0, 0); return true;
              case 'o': wid_config_top_other(nullptr, 0, 0, 0); return true;
              case 'b':
              case SDLK_ESCAPE: wid_config_top_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_top_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_config_top_menu(void)
{
  TRACE_AND_INDENT();
  CON("Config menu");

  if (wid_config_top_window) {
    wid_config_top_destroy();
  }
  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini("confg top menu");

  auto box_height          = g_opt_ascii ? 0 : 2;
  auto box_step            = g_opt_ascii ? 2 : 3;
  auto box_style           = g_opt_ascii ? UI_WID_STYLE_HORIZ_DARK : UI_WID_STYLE_NORMAL;
  auto box_highlight_style = g_opt_ascii ? UI_WID_STYLE_HORIZ_LIGHT : UI_WID_STYLE_NORMAL;

  point tl = make_point(TERM_WIDTH / 2 - UI_WID_POPUP_WIDTH_NORMAL / 2, TERM_HEIGHT / 2 - 4);
  point br = make_point(TERM_WIDTH / 2 + UI_WID_POPUP_WIDTH_NORMAL / 2 - 1, TERM_HEIGHT / 2 + 15);
  if (g_opt_ascii) {
    tl = make_point(TERM_WIDTH / 2 - UI_WID_POPUP_WIDTH_NORMAL / 2, TERM_HEIGHT / 2 - 4);
    br = make_point(TERM_WIDTH / 2 + UI_WID_POPUP_WIDTH_NORMAL / 2 - 1, TERM_HEIGHT / 2 + 8);
  }
  auto width = br.x - tl.x - 2;

  if (g_opt_ascii) {
    wid_config_top_window = new WidPopup("Config menu", tl, br, nullptr, "", false, false);
  } else {
    wid_config_top_window = new WidPopup("Config menu", tl, br, nullptr, "nothing", false, false);
  }

  {
    TRACE_AND_INDENT();
    Widp w = wid_config_top_window->wid_popup_container;
    wid_set_on_key_up(w, wid_config_top_key_up);
    wid_set_on_key_down(w, wid_config_top_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "gfx");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_gfx);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$G%%fg=reset$raphics");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "mouse");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_mouse);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$M%%fg=reset$ouse");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "sound");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_sound);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ound and music");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "keyboard");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_keyboard);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$K%%fg=reset$eyboard");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Other stuffs");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_other);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$O%%fg=reset$ther stuffs");
  }
  y_at += box_step;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_top_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + box_height);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_config_top_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }

  wid_update(wid_config_top_window->wid_text_area->wid_text_area);
}
