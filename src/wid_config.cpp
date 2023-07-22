//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_spellbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_tp_info.hpp"
#include <SDL_mixer.h>

WidPopup *wid_config_top_window;

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
  if (sdlk_eq(*key, game->config.key_console)) { return false; }

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
              case 'g' : wid_config_top_gfx(nullptr, 0, 0, 0); return true;
              case 'm' : wid_config_top_mouse(nullptr, 0, 0, 0); return true;
              case 's' : wid_config_top_sound(nullptr, 0, 0, 0); return true;
              case 'k' : wid_config_top_keyboard(nullptr, 0, 0, 0); return true;
              case 'o' : wid_config_top_other(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : wid_config_top_back(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_top_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) { return false; }

  return true;
}

void Game::wid_config_top_menu(void)
{
  TRACE_AND_INDENT();
  CON("INF: Config menu");

  if (wid_config_top_window) { wid_config_top_destroy(); }
  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_spellbox_fini();
  wid_thing_info_fini("confg top menu");
  wid_tp_info_fini("confg top menu");

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
