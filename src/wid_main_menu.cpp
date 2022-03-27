//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_music.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

static WidPopup *wid_main_menu_window;

void wid_main_menu_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_main_menu_window;
  wid_main_menu_window = nullptr;
}

void wid_main_menu_hide(void)
{
  TRACE_AND_INDENT();
  wid_hide(wid_main_menu_window->wid_text_area->wid_text_area);
}

static uint8_t wid_main_menu_load_game(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->wid_load_select();
  return false;
}

static uint8_t wid_main_menu_config(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->wid_config_top_menu();
  wid_main_menu_hide();
  return false;
}

static uint8_t game_menu_new_game(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_main_menu_hide();
  wid_main_menu_destroy();
  game->wid_choose_initial_dungeons();
  return false;
}

static uint8_t wid_choose_player_name(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->wid_choose_player_name_select();
  wid_main_menu_destroy();
  return false;
}

static uint8_t wid_main_menu_credits_game(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->wid_credits_select();
  wid_main_menu_destroy();
  return false;
}

static uint8_t wid_main_menu_quit_game(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->quit_select();
  wid_main_menu_destroy();
  return false;
}

static uint8_t wid_main_menu_hiscores(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->wid_hiscores_show();
  return false;
}

static uint8_t wid_main_menu_key_up(Widp w, const struct SDL_Keysym *key)
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
              case SDLK_RETURN:
              case ' ':
              case 'n': game_menu_new_game(nullptr, 0, 0, 0); return true;
              case 'l': wid_main_menu_load_game(nullptr, 0, 0, 0); return true;
              case 'o': wid_main_menu_config(nullptr, 0, 0, 0); return true;
              case 'c': wid_main_menu_credits_game(nullptr, 0, 0, 0); return true;
              case 'h': wid_main_menu_hiscores(nullptr, 0, 0, 0); return true;
              case 'q': wid_main_menu_quit_game(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static uint8_t wid_main_menu_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static void game_display_title_bg(void)
{
  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_bg";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void game_display_title_fg1(void)
{
  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg1_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void game_display_title_fg2(void)
{
  TRACE_AND_INDENT();
  static color fg    = WHITE;
  static int   delta = 10;
  static int   red   = 255;

  if (non_pcg_random_range(0, 100) < 50) {
    red += delta;
    if (red > 255) {
      delta = -delta;
      red   = 255;
    } else if (red < 200) {
      delta = -delta;
      red   = 200;
    }
  }

  fg.g = red;
  fg.b = red;
  glcolor(fg);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg2_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static uint8_t clamp(float v) // define a function to bound and round the input float value to 0-255
{
  if (v < 0)
    return 0;
  if (v > 255)
    return 255;
  return (uint8_t) v;
}

// https://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color#8509802
static color color_change_hue(const color &in, const float fHue)
{
  color       out;
  const float cosA = cos(fHue * 3.14159265f / 180); // convert degrees to radians
  const float sinA = sin(fHue * 3.14159265f / 180); // convert degrees to radians
  // calculate the rotation matrix, only depends on Hue
  float matrix[ 3 ][ 3 ] = {
      {cosA + (1.0f - cosA) / 3.0f, 1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA,
       1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA},
      {1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA, cosA + 1.0f / 3.0f * (1.0f - cosA),
       1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA},
      {1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA,
       1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA, cosA + 1.0f / 3.0f * (1.0f - cosA)}};
  // Use the rotation matrix to convert the RGB directly
  out.r = clamp(in.r * matrix[ 0 ][ 0 ] + in.g * matrix[ 0 ][ 1 ] + in.b * matrix[ 0 ][ 2 ]);
  out.g = clamp(in.r * matrix[ 1 ][ 0 ] + in.g * matrix[ 1 ][ 1 ] + in.b * matrix[ 1 ][ 2 ]);
  out.b = clamp(in.r * matrix[ 2 ][ 0 ] + in.g * matrix[ 2 ][ 1 ] + in.b * matrix[ 2 ][ 2 ]);
  return out;
}

static void game_display_title_fg3(void)
{
  TRACE_AND_INDENT();
  static color fg  = RED;
  static int   hue = 0;

  hue = 1;
  if (hue > 255) {
    hue = 0;
  }

  fg   = color_change_hue(fg, hue);
  fg.a = 255;

  if (fg.r + fg.g + fg.b < 100) {
    fg = RED;
  }

  float bright = 1.01;
  int   r      = (float) fg.r * bright;
  if (r > 255) {
    r = 255;
  }
  fg.r  = r;
  int g = (float) fg.g * bright;
  if (g > 255) {
    g = 255;
  }
  fg.g  = g;
  int b = (float) fg.b * bright;
  if (b > 255) {
    b = 255;
  }
  fg.b = b;

  glcolor(fg);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg3_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void game_display_title_fg4(void)
{
  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  static int  frame = 1;
  static ts_t ts;

  if (time_have_x_tenths_passed_since(5, ts)) {
    frame++;
    if (frame > 64) {
      frame = 1;
    }
    ts = time_get_time_ms_cached();
  }

  std::string t = "title_fg4_" + std::to_string(frame);
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

static void wid_main_menu_tick(Widp w)
{
  TRACE_AND_INDENT();
  game_display_title_bg();
  game_display_flames();
  game_display_title_fg1();
  game_display_title_fg2();
  game_display_title_fg3();
  game_display_title_fg4();

  ascii_putf(1, TERM_HEIGHT - 2, GREEN, BLACK, L"Version " MYVER);

  if (game->started) {
    wid_main_menu_destroy();
  }

  if (! g_opt_player_name.empty()) {
    auto player_name = "Player name: '" + g_opt_player_name + "'";
    ascii_putf(1, TERM_HEIGHT - 4, YELLOW, BLACK, string_to_wstring(player_name));
  }

  if (! g_opt_seed_name.empty()) {
    auto seed_name = "Seed: '" + g_opt_seed_name + "'";
    ascii_putf(1, TERM_HEIGHT - 6, YELLOW, BLACK, string_to_wstring(seed_name));
  }
}

void Game::wid_main_menu_select(void)
{
  TRACE_AND_INDENT();
  LOG("Main menu");

  py_call_void_fn("events", "on_main_menu_select", 0);

  if (wid_main_menu_window) {
    wid_main_menu_destroy();
  }
  wid_rightbar_fini();
  wid_inventory_fini();
  wid_skillbox_fini();
  wid_thing_info_fini("main menu select");
  wid_actionbar_fini();
  wid_topcon_fini();

  game->wid_thing_info_destroy_immediate();

  point tl    = make_point(TERM_WIDTH - UI_WID_POPUP_WIDTH_NORMAL - 1, TERM_HEIGHT - 23);
  point br    = make_point(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto  width = br.x - tl.x - 2;

  wid_main_menu_window = new WidPopup("Main menu", tl, br, nullptr, "nothing", false, false);
  {
    TRACE_NO_INDENT();
    Widp w = wid_main_menu_window->wid_popup_container;
    wid_set_on_key_up(w, wid_main_menu_key_up);
    wid_set_on_key_down(w, wid_main_menu_key_down);
    wid_set_on_tick(w, wid_main_menu_tick);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "New Game");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, game_menu_new_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$N%%fg=reset$ew game%%fg=reset$");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Choose player name");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_choose_player_name);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_COLOR_STR "$Choose player name");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Load Game");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_main_menu_load_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$L%%fg=" UI_TEXT_COLOR_STR "$oad game");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Options");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_main_menu_config);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$O%%fg=" UI_TEXT_COLOR_STR "$ptions");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Credits");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_main_menu_credits_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$C%%fg=" UI_TEXT_COLOR_STR "$redits");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Hiscores");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_main_menu_hiscores);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$H%%fg=" UI_TEXT_COLOR_STR "$iscores");
  }
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Quit Game");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_main_menu_quit_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Q%%fg=" UI_TEXT_COLOR_STR "$uit Game");
  }

  wid_update(wid_main_menu_window->wid_text_area->wid_text_area);
}

void Game::new_game(void)
{
  TRACE_NO_INDENT();
  game->wid_choose_initial_dungeons();
}
