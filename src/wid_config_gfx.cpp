//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_config_gfx_window;
static bool      local_g_need_restart = false;
static bool      config_changed;

static void wid_config_gfx_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_config_gfx_window;
  wid_config_gfx_window = nullptr;
  config_changed        = false;
}

static uint8_t wid_config_gfx_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (config_changed) {
    config_changed = false;
    game->load_config();
    sdl_config_update_all();
  }
  wid_config_gfx_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_gfx_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game->save_config();
  wid_config_gfx_destroy();
  game->wid_config_top_menu();
  if (local_g_need_restart) {
    g_need_restart = true;
  }
  return true;
}

static uint8_t wid_config_gfx_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_gfx_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_gfx_vsync_enable_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle vsync");
  game->config.gfx_vsync_enable = ! game->config.gfx_vsync_enable;
  config_gfx_vsync_update();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_ascii_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle gfx");
  g_opt_ascii = ! g_opt_ascii;
  sdl_display_reset();
  game->wid_config_gfx_select();

  return true;
}

static uint8_t wid_config_gfx_fullscreen_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle gfx fullscreen");
  game->config.gfx_fullscreen = ! game->config.gfx_fullscreen;
  if (game->config.gfx_fullscreen) {
    game->config.gfx_fullscreen_desktop = false;
  }
  game->wid_config_gfx_select();
  local_g_need_restart = true;
  return true;
}

static uint8_t wid_config_gfx_fullscreen_desktop_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle gfx fullscreen desktop");
  game->config.gfx_fullscreen_desktop = ! game->config.gfx_fullscreen_desktop;
  if (game->config.gfx_fullscreen_desktop) {
    game->config.gfx_fullscreen = false;
  }
  game->wid_config_gfx_select();
  local_g_need_restart = true;
  return true;
}

static uint8_t wid_config_gfx_allow_highdpi_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle gfx allow highdpi");
  game->config.gfx_allow_highdpi = ! game->config.gfx_allow_highdpi;
  game->wid_config_gfx_select();
  local_g_need_restart = true;
  return true;
}

static uint8_t wid_config_gfx_borderless_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle gfx borderless");
  game->config.gfx_borderless = ! game->config.gfx_borderless;
  game->wid_config_gfx_select();
  local_g_need_restart = true;
  return true;
}

static uint8_t wid_config_gfx_inverted_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle inverted");
  game->config.gfx_inverted = ! game->config.gfx_inverted;
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_other_fps_counter_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle fps counter");
  game->config.fps_counter = ! game->config.fps_counter;
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_resolution_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Increment resolution");
  auto res    = std::to_string(game->config.window_pix_width) + "x" + std::to_string(game->config.window_pix_height);
  auto n      = SDL_GetNumDisplayModes(0);
  int  chosen = 0;
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
      game->config.window_pix_width  = mode.w;
      game->config.window_pix_height = mode.h;
      local_g_need_restart           = true;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_resolution_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Decrement resolution");
  auto res    = std::to_string(game->config.window_pix_width) + "x" + std::to_string(game->config.window_pix_height);
  auto n      = SDL_GetNumDisplayModes(0);
  int  chosen = 0;
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
      game->config.window_pix_width  = mode.w;
      game->config.window_pix_height = mode.h;
      local_g_need_restart           = true;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_term_width_size_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;

  CON("INF: Decrement term width");
  if (g_opt_ascii) {
    game->config.ui_ascii_term_width--;
    if (game->config.ui_ascii_term_width < 1) {
      sound_play("bonk");
      game->config.ui_ascii_term_width = 1;
    }
  } else {
    game->config.ui_gfx_term_width--;
    if (game->config.ui_gfx_term_width < 1) {
      sound_play("bonk");
      game->config.ui_gfx_term_width = 1;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_term_width_size_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;

  CON("INF: Decrement term width");
  if (g_opt_ascii) {
    game->config.ui_ascii_term_width++;
    if (game->config.ui_ascii_term_width > TERM_WIDTH_MAX) {
      sound_play("bonk");
      game->config.ui_ascii_term_width = TERM_WIDTH_MAX;
    }
  } else {
    game->config.ui_gfx_term_width++;
    if (game->config.ui_gfx_term_width > TERM_WIDTH_MAX) {
      sound_play("bonk");
      game->config.ui_gfx_term_width = TERM_WIDTH_MAX;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_term_height_size_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;

  CON("INF: Decrement term height");
  if (g_opt_ascii) {
    game->config.ui_ascii_term_height--;
    if (game->config.ui_ascii_term_height < 1) {
      sound_play("bonk");
      game->config.ui_ascii_term_height = 1;
    }
  } else {
    game->config.ui_gfx_term_height--;
    if (game->config.ui_gfx_term_height < 1) {
      sound_play("bonk");
      game->config.ui_gfx_term_height = 1;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_term_height_size_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;

  CON("INF: Decrement term height");
  if (g_opt_ascii) {
    game->config.ui_ascii_term_height++;
    if (game->config.ui_ascii_term_height > TERM_WIDTH_MAX) {
      sound_play("bonk");
      game->config.ui_ascii_term_height = TERM_WIDTH_MAX;
    }
  } else {
    game->config.ui_gfx_term_height++;
    if (game->config.ui_gfx_term_height > TERM_WIDTH_MAX) {
      sound_play("bonk");
      game->config.ui_gfx_term_height = TERM_WIDTH_MAX;
    }
  }
  wid_config_gfx_save(nullptr, 0, 0, 0);
  sdl_config_update_all();
  game->wid_config_gfx_select();
  return true;
}

static uint8_t wid_config_gfx_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'c' : wid_config_gfx_cancel(nullptr, 0, 0, 0); return true;
              case 's' : wid_config_gfx_save(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : wid_config_gfx_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_gfx_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_config_gfx_select(void)
{
  TRACE_AND_INDENT();
  if (wid_config_gfx_window) {
    wid_config_gfx_destroy();
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point tl = make_point(m - 20, TERM_HEIGHT / 2 - 10);
  point br = make_point(m + 20, TERM_HEIGHT / 2 + 11);

  auto width = br.x - tl.x - 2;

  wid_config_gfx_window = new WidPopup("Gfx select", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_config_gfx_window->wid_popup_container;
    wid_set_on_key_up(w, wid_config_gfx_key_up);
    wid_set_on_key_down(w, wid_config_gfx_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "configuration");

    point tl = make_point(1, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Configuration");
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, wid_config_gfx_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 15, y_at);
    point br = make_point(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_config_gfx_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 8, y_at);
    point br = make_point(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_config_gfx_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  /////////////////////////////////////////////////////////////////////////
  // resolution
  /////////////////////////////////////////////////////////////////////////
  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Resolution");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Resolution");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Resolution value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 12, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto res = std::to_string(game->config.window_pix_width) + "x" + std::to_string(game->config.window_pix_height);
    wid_set_text(w, res);
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Resolution value +");

    point tl = make_point(width / 2 + 13, y_at);
    point br = make_point(width / 2 + 15, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_resolution_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Resolution value -");

    point tl = make_point(width / 2 + 16, y_at);
    point br = make_point(width / 2 + 18, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_resolution_decr);
    wid_set_text(w, "-");
  }

  /////////////////////////////////////////////////////////////////////////
  // terminal width
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term width");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Term width");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term size value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 7, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    if (g_opt_ascii) {
      auto res = std::to_string(game->config.ui_ascii_term_width);
      wid_set_text(w, res);
    } else {
      auto res = std::to_string(game->config.ui_gfx_term_width);
      wid_set_text(w, res);
    }
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term width value +");

    point tl = make_point(width / 2 + 13, y_at);
    point br = make_point(width / 2 + 15, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_term_width_size_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term width value -");

    point tl = make_point(width / 2 + 16, y_at);
    point br = make_point(width / 2 + 18, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_term_width_size_decr);
    wid_set_text(w, "-");
  }

  /////////////////////////////////////////////////////////////////////////
  // terminal height
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term height");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Term height");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term size value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 7, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    if (g_opt_ascii) {
      auto res = std::to_string(game->config.ui_ascii_term_height);
      wid_set_text(w, res);
    } else {
      auto res = std::to_string(game->config.ui_gfx_term_height);
      wid_set_text(w, res);
    }
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term height value +");

    point tl = make_point(width / 2 + 13, y_at);
    point br = make_point(width / 2 + 15, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_term_height_size_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Term height value -");

    point tl = make_point(width / 2 + 16, y_at);
    point br = make_point(width / 2 + 18, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_term_height_size_decr);
    wid_set_text(w, "-");
  }

  /////////////////////////////////////////////////////////////////////////
  // ASCII
  /////////////////////////////////////////////////////////////////////////
  y_at += 2;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Ascii mode");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Ascii mode");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Ascii mode");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_ascii_toggle);

    if (g_opt_ascii) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // fullscreen
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Fullscreen");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Fullscreen video");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Fullscreen value");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_fullscreen_toggle);

    if (game->config.gfx_fullscreen) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // fullscreen desktop
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Fullscreen desktop");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Fullscreen desktop");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Fullscreen value");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_fullscreen_desktop_toggle);

    if (game->config.gfx_fullscreen_desktop) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // fullscreen desktop
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "High DPI res");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "High DPI resolution");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "High DPI value");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_allow_highdpi_toggle);

    if (game->config.gfx_allow_highdpi) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // borderless
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Borderless");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Borderless window");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Borderless");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_borderless_toggle);

    if (game->config.gfx_borderless) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  if (! game->config.gfx_vsync_locked) {
    /////////////////////////////////////////////////////////////////////////
    // vsync
    /////////////////////////////////////////////////////////////////////////
    y_at++;
    {
      TRACE_AND_INDENT();
      auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "Vertical sync");

      point tl = make_point(1, y_at);
      point br = make_point(width / 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, "Vertical sync");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "Vertical sync value");

      point tl = make_point(29, y_at);
      point br = make_point(37, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(w, wid_config_gfx_vsync_enable_toggle);

      if (game->config.gfx_vsync_enable) {
        wid_set_text(w, "True");
      } else {
        wid_set_text(w, "False");
      }
    }
  } else {
    /////////////////////////////////////////////////////////////////////////
    // vsync cannot be changed
    /////////////////////////////////////////////////////////////////////////
    y_at++;
    {
      TRACE_AND_INDENT();
      auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "Vertical sync");

      point tl = make_point(1, y_at);
      point br = make_point(width / 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, "Vertical sync");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(p, "Vertical sync value");

      point tl = make_point(29, y_at);
      point br = make_point(37, y_at);
      wid_set_mode(w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);

      wid_set_text(w, "True");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Inverted graphics
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inverted graphics");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Inverted graphics");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Inverted graphics value");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_gfx_inverted_toggle);

    if (game->config.gfx_inverted) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  //////////////////////////////////////////////////////////////////////
  // fps
  //////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "FPS counter");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "FPS counter");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "FPS counter value");

    point tl = make_point(29, y_at);
    point br = make_point(37, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_other_fps_counter_toggle);

    if (game->config.fps_counter) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  wid_update(wid_config_gfx_window->wid_text_area->wid_text_area);
}
