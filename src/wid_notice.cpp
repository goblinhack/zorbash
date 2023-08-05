//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_notice_window;

void wid_notice_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_notice_window;
  wid_notice_window = nullptr;
}

static uint8_t wid_notice_ok(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_notice_destroy();
  return false;
}

static uint8_t wid_notice_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_notice_ok(nullptr, 0, 0, 0);
  return true;
}

static uint8_t wid_notice_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

void wid_notice(std::string s)
{
  TRACE_AND_INDENT();
  if (wid_notice_window) {
    wid_notice_destroy();
  }

  auto  m  = TERM_WIDTH / 2;
  auto  n  = TERM_HEIGHT / 2;
  point tl = make_point(0, 0);
  point br = make_point(s.size() + 3, 8);
  point offset(m, n);
  offset.x -= s.size() / 2;
  tl += offset;
  br += offset;

  auto width = br.x - tl.x;

  wid_notice_window = new WidPopup("Game notice", tl, br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_notice_window->wid_popup_container;
    wid_set_on_key_up(w, wid_notice_key_up);
    wid_set_on_key_down(w, wid_notice_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "notice");

    point tl = make_point(0, y_at);
    point br = make_point(width - 1, y_at + 1);
    wid_set_shape_none(w);
    wid_set_on_mouse_up(w, wid_notice_ok);
    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    wid_set_style(w, UI_WID_STYLE_GREEN);
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_notice_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "ok");

    point tl = make_point(width / 2 - 4, y_at);
    point br = make_point(width / 2 + 4, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(w, wid_notice_ok);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Ok!");
  }

  wid_update(wid_notice_window->wid_text_area->wid_text_area);
}
