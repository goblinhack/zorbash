//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_popup.h"
#include "my_sys.h"
#include "my_game_notice.h"
#include "my_ui.h"
#include "my_sdl.h"

static WidPopup *game_notice_window;

void game_notice_destroy(void)
{
  TRACE_AND_INDENT();
  delete game_notice_window;
  game_notice_window = nullptr;
}

static uint8_t game_notice_ok(Widp w, int32_t x, int32_t y, uint32_t button)
{
  TRACE_AND_INDENT();
  game_notice_destroy();
  return false;
}

static uint8_t game_notice_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  game_notice_ok(nullptr, 0, 0, 0);
  return true;
}

static uint8_t game_notice_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  if (sdl_shift_held) {
    if (key->scancode == (SDL_Scancode) game->config.key_console) {
      return false;
    }
  }

  return true;
}

void game_notice(std::string s)
{
  TRACE_AND_INDENT();
  if (game_notice_window) {
    game_notice_destroy();
  }

  auto  m     = TERM_WIDTH / 2;
  auto  n     = TERM_HEIGHT / 2;
  int   w     = (s.size() / 2) + 3;
  point tl    = make_point(m - w, n - 2);
  point br    = make_point(m + w - 1, n + 2);
  auto  width = br.x - tl.x;

  game_notice_window = new WidPopup("Game notice", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = game_notice_window->wid_popup_container;
    wid_set_on_key_up(w, game_notice_key_up);
    wid_set_on_key_down(w, game_notice_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = game_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "notice");

    point tl = make_point(0, y_at);
    point br = make_point(width, y_at + 1);
    wid_set_shape_none(w);
    wid_set_on_mouse_up(w, game_notice_ok);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = game_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "ok");

    point tl = make_point(width / 2 - 4, y_at);
    point br = make_point(width / 2 + 4, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, game_notice_ok);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "ok!");
  }

  wid_update(game_notice_window->wid_text_area->wid_text_area);
}
