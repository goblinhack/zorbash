//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_popup.h"
#include "my_sdl.h"
#include "my_globals.h"
#include "my_wid.h"
#include "my_ui.h"

static WidPopup *game_config_other_window;

static void game_config_other_destroy(void) {
  TRACE_AND_INDENT();
  delete game_config_other_window;
  game_config_other_window = nullptr;
}

static uint8_t game_config_other_cancel(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  CON("USR: Reload config");
  game->load_config();
  game_config_other_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_other_save(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  CON("USR: Save config");
  game->save_config();
  game_config_other_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_other_back(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  game_config_other_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_debug_mode_toggle(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  CON("USR: Toggle debug_mode");
  game->config.debug_mode = ! game->config.debug_mode;
  CON("USR: Save config");
  game->save_config();
  g_need_restart = true;
  return true;
}

static uint8_t game_config_other_sdl_delay_incr(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  CON("USR: Increment sdl_delay");
  game->config.sdl_delay++;
  game->config_other_select();
  return true;
}

static uint8_t game_config_other_sdl_delay_decr(Widp w, int32_t x, int32_t y, uint32_t button) {
  TRACE_AND_INDENT();
  CON("USR: Decrement sdl_delay");
  game->config.sdl_delay--;
  game->config_other_select();
  return true;
}

static uint8_t game_config_other_key_up(Widp w, const struct SDL_Keysym *key) {
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
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
              case 'c' : game_config_other_cancel(nullptr, 0, 0, 0); return true;
              case 's' : game_config_other_save(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : game_config_other_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t game_config_other_key_down(Widp w, const struct SDL_Keysym *key) {
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

void Game::config_other_select(void) {
  TRACE_AND_INDENT();
  if (game_config_other_window) {
    game_config_other_destroy();
  }

  auto  m     = TERM_WIDTH / 2;
  point tl    = make_point(m - UI_WID_POPUP_WIDTH_WIDEST / 2, UI_TOPCON_VIS_HEIGHT + 2);
  point br    = make_point(m + UI_WID_POPUP_WIDTH_WIDEST / 2, UI_ACTIONBAR_TL_Y - 2);
  auto  width = br.x - tl.x - 2;

  game_config_other_window = new WidPopup("Config other select", tl, br, nullptr, "");
  {
    TRACE_AND_INDENT();
    Widp w = game_config_other_window->wid_popup_container;
    wid_set_on_key_up(w, game_config_other_key_up);
    wid_set_on_key_down(w, game_config_other_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "configuration");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Configuration");
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(0, y_at);
    point br = make_point(5, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, game_config_other_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 15, y_at);
    point br = make_point(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, game_config_other_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 8, y_at);
    point br = make_point(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, game_config_other_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  //////////////////////////////////////////////////////////////////////
  // Debug mode
  //////////////////////////////////////////////////////////////////////
  y_at += 3;
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "debug mode");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Debug mode (restart)");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "debug mode value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_config_debug_mode_toggle);

    if (game->config.debug_mode) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  //////////////////////////////////////////////////////////////////////
  // delay
  //////////////////////////////////////////////////////////////////////
  y_at += 3;
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Delay ms per frame");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Delay ms per frame");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL delay value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.sdl_delay));
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL delay value +");

    point tl = make_point(width / 2 + 7, y_at);
    point br = make_point(width / 2 + 9, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_config_other_sdl_delay_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_other_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "SDL delay value -");

    point tl = make_point(width / 2 + 10, y_at);
    point br = make_point(width / 2 + 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(w, game_config_other_sdl_delay_decr);
    wid_set_text(w, "-");
  }

  wid_update(game_config_other_window->wid_text_area->wid_text_area);
}
