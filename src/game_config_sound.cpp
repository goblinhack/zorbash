//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_music.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_ui.h"
#include "my_wid_popup.h"
#include <SDL_mixer.h>

static WidPopup *game_config_sound_window;

static void game_config_sound_destroy(void)
{
  TRACE_AND_INDENT();
  delete game_config_sound_window;
  game_config_sound_window = nullptr;
}

static uint8_t game_config_sound_cancel(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Reload config");
  game->load_config();
  game_config_sound_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_sound_save(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Save config");
  game->save_config();
  game_config_sound_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_sound_back(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game_config_sound_destroy();
  game->config_top_select();
  return true;
}

static uint8_t game_config_sound_effects_volume_incr(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Increment sound_volume");
  game->config.sound_volume++;
  if (game->config.sound_volume > MIX_MAX_VOLUME) {
    game->config.sound_volume = MIX_MAX_VOLUME;
  }
  game->config_sound_select();
  return true;
}

static uint8_t game_config_sound_effects_volume_decr(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Decrement sound_volume");
  if (game->config.sound_volume > 0) {
    game->config.sound_volume--;
  } else {
    game->config.sound_volume = 0;
  }
  game->config_sound_select();
  return true;
}

static uint8_t game_config_sound_music_volume_incr(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Increment music_volume");
  game->config.music_volume++;
  if (game->config.music_volume > MIX_MAX_VOLUME) {
    game->config.music_volume = MIX_MAX_VOLUME;
  }
  game->config_sound_select();
  music_update_volume();
  return true;
}

static uint8_t game_config_sound_music_volume_decr(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("PLAYER: Decrement music_volume");
  if (game->config.music_volume > 0) {
    game->config.music_volume--;
  } else {
    game->config.music_volume = 0;
  }
  game->config_sound_select();
  music_update_volume();
  return true;
}

static uint8_t game_config_sound_key_up(Widp w, const struct SDL_Keysym *key)
{
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
              case 'c' : game_config_sound_cancel(nullptr, 0, 0, 0); return true;
              case 's' : game_config_sound_save(nullptr, 0, 0, 0); return true;
              case 'b' :
              case SDLK_ESCAPE : game_config_sound_cancel(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t game_config_sound_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

void Game::config_sound_select(void)
{
  TRACE_AND_INDENT();
  if (game_config_sound_window) {
    game_config_sound_destroy();
  }

  auto  m     = TERM_WIDTH / 2;
  point tl    = make_point(m - UI_WID_POPUP_WIDTH_WIDEST / 2, UI_TOPCON_VIS_HEIGHT + 2);
  point br    = make_point(m + UI_WID_POPUP_WIDTH_WIDEST / 2, UI_ACTIONBAR_TL_Y - 2);
  auto  width = br.x - tl.x;

  game_config_sound_window = new WidPopup("Config sound select", tl, br, nullptr, "");
  {
    TRACE_AND_INDENT();
    Widp w = game_config_sound_window->wid_popup_container;
    wid_set_on_key_up(w, game_config_sound_key_up);
    wid_set_on_key_down(w, game_config_sound_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
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
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Back");

    point tl = make_point(0, y_at);
    point br = make_point(5, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_on_mouse_up(w, game_config_sound_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Save");

    point tl = make_point(width - 17, y_at);
    point br = make_point(width - 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_OK);
    wid_set_on_mouse_up(w, game_config_sound_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Cancel");

    point tl = make_point(width - 10, y_at);
    point br = make_point(width - 3, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_HIGHLIGHTED);
    wid_set_on_mouse_up(w, game_config_sound_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects volume");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Effects volume");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects volume value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.sound_volume));
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects value +");

    point tl = make_point(width / 2 + 7, y_at);
    point br = make_point(width / 2 + 9, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, game_config_sound_effects_volume_incr);
    wid_set_on_mouse_held(w, game_config_sound_effects_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Effects value -");

    point tl = make_point(width / 2 + 10, y_at);
    point br = make_point(width / 2 + 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, game_config_sound_effects_volume_decr);
    wid_set_on_mouse_held(w, game_config_sound_effects_volume_decr);
    wid_set_text(w, "-");
  }

  y_at += 3;
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music volume");

    point tl = make_point(0, y_at);
    point br = make_point(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Music volume");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music volume value");

    point tl = make_point(width / 2, y_at);
    point br = make_point(width / 2 + 6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game->config.music_volume));
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music value +");

    point tl = make_point(width / 2 + 7, y_at);
    point br = make_point(width / 2 + 9, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, game_config_sound_music_volume_incr);
    wid_set_on_mouse_held(w, game_config_sound_music_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = game_config_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Music value -");

    point tl = make_point(width / 2 + 10, y_at);
    point br = make_point(width / 2 + 12, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(w, game_config_sound_music_volume_decr);
    wid_set_on_mouse_held(w, game_config_sound_music_volume_decr);
    wid_set_text(w, "-");
  }

  wid_update(game_config_sound_window->wid_text_area->wid_text_area);
}
