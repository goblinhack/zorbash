//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_config_other_window;
static bool      config_changed;

static void wid_config_other_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_config_other_window;
  wid_config_other_window = nullptr;
  config_changed          = false;
}

static uint8_t wid_config_other_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (config_changed) {
    config_changed = false;
    game->load_config();
    sdl_config_update_all();
  }
  wid_config_other_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_other_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game->save_config();
  wid_config_other_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_other_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_other_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_debug_mode_toggle(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Toggle debug_mode");
  game->config.debug_mode = ! game->config.debug_mode;
  CON("INF: Save config");
  game->save_config();
  g_need_restart = true;
  return true;
}

static uint8_t wid_config_other_sdl_delay_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Increment sdl_delay");
  game->config.sdl_delay++;
  game->wid_config_other_select();
  return true;
}

static uint8_t wid_config_other_sdl_delay_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Decrement sdl_delay");
  game->config.sdl_delay--;
  game->wid_config_other_select();
  return true;
}

static uint8_t wid_config_other_snapshot_freq_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Increment snapshot_freq");
  game->config.snapshot_freq++;
  game->wid_config_other_select();
  return true;
}

static uint8_t wid_config_other_snapshot_freq_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Decrement snapshot_freq");
  game->config.snapshot_freq--;
  game->wid_config_other_select();
  return true;
}

static uint8_t wid_config_other_key_up(Widp w, const struct SDL_Keysym *key)
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
              case 'c': wid_config_other_cancel(nullptr, 0, 0, 0); return true;
              case 's': wid_config_other_save(nullptr, 0, 0, 0); return true;
              case 'b':
              case SDLK_ESCAPE: wid_config_other_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_other_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_config_other_select(void)
{
  TRACE_AND_INDENT();
  if (wid_config_other_window) {
    wid_config_other_destroy();
  }

  auto box_style           = UI_WID_STYLE_HORIZ_SCROLL_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_SCROLL_LIGHT;
  auto m                   = TERM_WIDTH / 2;
  auto h                   = TERM_HEIGHT / 2;

  point tl    = make_point(m - 20, h - 6);
  point br    = make_point(m + 20, h + 6);
  auto  width = br.x - tl.x - 2;

  wid_config_other_window = new WidPopup("Config other select", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_config_other_window->wid_popup_container;
    wid_set_on_key_up(w, wid_config_other_key_up);
    wid_set_on_key_down(w, wid_config_other_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
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
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, wid_config_other_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 15, y_at);
    point br = make_point(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_config_other_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 8, y_at);
    point br = make_point(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_config_other_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  //////////////////////////////////////////////////////////////////////
  // Debug mode
  //////////////////////////////////////////////////////////////////////
  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "debug mode");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Debug (restart)");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "debug mode value");

    point tl = make_point(width / 2 + 6, y_at);
    point br = make_point(width / 2 + 12, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_debug_mode_toggle);

    if (game->config.debug_mode) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  //////////////////////////////////////////////////////////////////////
  // snapshot_freq
  //////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Snapshot turn freq");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Snapshot turn freq");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Snapshot save freq value");

    point tl = make_point(width / 2 + 6, y_at);
    point br = make_point(width / 2 + 12, y_at);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.snapshot_freq));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Snapshot save freq +");

    point tl = make_point(width / 2 + 13, y_at);
    point br = make_point(width / 2 + 15, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_other_snapshot_freq_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Snapshot save freq -");

    point tl = make_point(width / 2 + 16, y_at);
    point br = make_point(width / 2 + 18, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_other_snapshot_freq_decr);
    wid_set_text(w, "-");
  }

  //////////////////////////////////////////////////////////////////////
  // delay
  //////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Delay ms per frame");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Delay ms per frame");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL: delay value");

    point tl = make_point(width / 2 + 6, y_at);
    point br = make_point(width / 2 + 12, y_at);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.sdl_delay));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL: delay value +");

    point tl = make_point(width / 2 + 13, y_at);
    point br = make_point(width / 2 + 15, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_other_sdl_delay_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL: delay value -");

    point tl = make_point(width / 2 + 16, y_at);
    point br = make_point(width / 2 + 18, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, wid_config_other_sdl_delay_decr);
    wid_set_text(w, "-");
  }

  wid_update(wid_config_other_window->wid_text_area->wid_text_area);
}
