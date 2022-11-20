//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_sdl_proto.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_progress_bar.hpp"

static int progress_steps = 32;

WidPopup *wid_progress_bar_window;

void wid_progress_bar_destroy(void)
{
  TRACE_NO_INDENT();
  delete wid_progress_bar_window;
  wid_progress_bar_window = nullptr;
}

void wid_progress_bar(const std::string &title, float pct)
{
  DBG("Progress bar");
  TRACE_AND_INDENT();

  if (wid_progress_bar_window) {
    wid_progress_bar_destroy();
  }

  int tile_num;
  tile_num = progress_steps * pct;
  if (tile_num > progress_steps) {
    tile_num = progress_steps;
  }
  if (tile_num < 1) {
    tile_num = 1;
  }

  std::string tilename = "progress_bar.pixelart." + std::to_string(tile_num);
  if (g_opt_ascii) {
    tilename = "progress_bar.ascii." + std::to_string(tile_num);
  }

  auto  m  = TERM_WIDTH / 2;
  auto  n  = TERM_HEIGHT / 2;
  point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2, n - 3);
  point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2, n + 4);

  wid_progress_bar_window = new WidPopup("Progress bar", tl, br, nullptr, "", false, false);

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_progress_bar_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Title");

    point tl = make_point(0, y_at);
    point br = make_point(UI_WID_POPUP_WIDTH_WIDE, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, title);
  }

  y_at = 2;
  {
    TRACE_NO_INDENT();
    auto p = wid_progress_bar_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Progress");

    int x_at = UI_WID_POPUP_WIDTH_WIDE - progress_steps;
    x_at /= 2;
    point tl = make_point(x_at, y_at);
    point br = make_point(x_at + progress_steps - 1, y_at + 3);
    wid_set_pos(w, tl, br);
    wid_set_style(w, UI_WID_STYLE_DARK);
    wid_set_fg2_tilename(w, tilename);
  }

  wid_update(wid_progress_bar_window->wid_text_area->wid_text_area);

  sdl_flush_display(true /* force */);
}
