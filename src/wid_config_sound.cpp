//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_music.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"
#include <SDL_mixer.h>

static WidPopup *wid_config_sound_window;
static bool      config_changed;

static void wid_config_sound_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_config_sound_window;
  wid_config_sound_window = nullptr;
  config_changed          = false;
}

static uint8_t wid_config_sound_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (config_changed) {
    config_changed = false;
    game->load_config();
    sdl_config_update_all();
  }
  wid_config_sound_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_sound_save(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game->save_config();
  wid_config_sound_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_sound_back(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_config_sound_destroy();
  game->wid_config_top_menu();
  return true;
}

static uint8_t wid_config_sound_effects_volume_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Increment sound volume");
  game->config.sound_volume++;
  if (game->config.sound_volume > MIX_MAX_VOLUME) {
    game->config.sound_volume = MIX_MAX_VOLUME;
  }
  game->wid_config_sound_select();
  return true;
}

static uint8_t wid_config_sound_effects_volume_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Decrement sound volume");
  if (game->config.sound_volume > 0) {
    game->config.sound_volume--;
  } else {
    game->config.sound_volume = 0;
  }
  game->wid_config_sound_select();
  return true;
}

static uint8_t wid_config_sound_music_volume_incr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Increment music volume");
  game->config.music_volume++;
  if (game->config.music_volume > MIX_MAX_VOLUME) {
    game->config.music_volume = MIX_MAX_VOLUME;
  }
  game->wid_config_sound_select();
  music_update_volume();
  return true;
}

static uint8_t wid_config_sound_music_volume_decr(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  config_changed = true;
  CON("INF: Decrement music volume");
  if (game->config.music_volume > 0) {
    game->config.music_volume--;
  } else {
    game->config.music_volume = 0;
  }
  game->wid_config_sound_select();
  music_update_volume();
  return true;
}

static uint8_t wid_config_sound_key_up(Widp w, const struct SDL_Keysym *key)
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
              case 'c' : wid_config_sound_cancel(nullptr, 0, 0, 0); return true;
              case 's' : wid_config_sound_save(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : wid_config_sound_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_config_sound_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void Game::wid_config_sound_select(void)
{
  TRACE_AND_INDENT();
  if (wid_config_sound_window) {
    wid_config_sound_destroy();
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point tl = make_point(m - 16, TERM_HEIGHT / 2 - 5);
  point br = make_point(m + 16, TERM_HEIGHT / 2 + 6);

  auto width = br.x - tl.x - 2;

  wid_config_sound_window = new WidPopup("Config sound select", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_config_sound_window->wid_popup_container;
    wid_set_on_key_up(w, wid_config_sound_key_up);
    wid_set_on_key_down(w, wid_config_sound_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
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
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(1, y_at);
    point br = make_point(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, wid_config_sound_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 15, y_at);
    point br = make_point(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_config_sound_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 8, y_at);
    point br = make_point(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(w, wid_config_sound_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects volume");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Effects volume");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects volume value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 8, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.sound_volume));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects value +");

    point tl = make_point(width / 2 + 9, y_at);
    point br = make_point(width / 2 + 11, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, wid_config_sound_effects_volume_incr);
    wid_set_on_mouse_held(w, wid_config_sound_effects_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects value -");

    point tl = make_point(width / 2 + 12, y_at);
    point br = make_point(width / 2 + 14, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, wid_config_sound_effects_volume_decr);
    wid_set_on_mouse_held(w, wid_config_sound_effects_volume_decr);
    wid_set_text(w, "-");
  }

  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music volume");

    point tl = make_point(1, y_at);
    point br = make_point(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Music volume");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music volume value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 8, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.music_volume));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music value +");

    point tl = make_point(width / 2 + 9, y_at);
    point br = make_point(width / 2 + 11, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, wid_config_sound_music_volume_incr);
    wid_set_on_mouse_held(w, wid_config_sound_music_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music value -");

    point tl = make_point(width / 2 + 12, y_at);
    point br = make_point(width / 2 + 14, y_at);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, wid_config_sound_music_volume_decr);
    wid_set_on_mouse_held(w, wid_config_sound_music_volume_decr);
    wid_set_text(w, "-");
  }

  wid_update(wid_config_sound_window->wid_text_area->wid_text_area);
}
