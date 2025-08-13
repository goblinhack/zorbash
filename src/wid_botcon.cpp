//
// Copyright goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_botcon.hpp"
#include <algorithm> // for std::reverse() // do not remove

static void wid_botcon_wid_create(void);

Widp wid_botcon_container {};
Widp wid_botcon_vert_scroll {};
Widp wid_botcon_input_line {};
Widp wid_botcon_window {};

static std::wstring last_msg;
static int          last_msg_count;

static std::map< unsigned int, std::wstring > wid_botcon_lines;

void wid_botcon_fini(void)
{
  TRACE_NO_INDENT();
  wid_destroy(&wid_botcon_container);
  wid_destroy(&wid_botcon_vert_scroll);
  wid_destroy(&wid_botcon_input_line);
  wid_destroy(&wid_botcon_window);
}

uint8_t wid_botcon_init(void)
{
  TRACE_NO_INDENT();
  wid_botcon_wid_create();
  wid_hide(wid_botcon_window);

  last_msg       = L"";
  last_msg_count = 0;

  return true;
}

//
// Scroll back to the bottom of the screen.
//
static void wid_botcon_reset_scroll(void)
{
  TRACE_NO_INDENT();
  if (! wid_botcon_vert_scroll) {
    return;
  }

  wid_move_to_bottom(wid_botcon_vert_scroll);
}

static void wid_botcon_scroll(Widp w, std::wstring str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  wid_scroll_text(w);

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);
  if (tmp) {
    wid_set_text(tmp, str);
  }
}

void wid_botcon_clear(void)
{
  TRACE_NO_INDENT();
  auto tmp = wid_get_head(wid_botcon_input_line);
  while (tmp) {
    wid_set_text(tmp, "");
    tmp = wid_get_next(tmp);
  }
  wid_botcon_reset_scroll();
}

//
// Log a message to the botcon
//
static void wid_botcon_log_(std::wstring s)
{
  TRACE_NO_INDENT();
  static int log_wid_botcon_buffered_lines;

  wid_botcon_reset_scroll();

  //
  // Before the botcon is ready, we buffer the logs.
  //
  if (! wid_botcon_input_line) {
    auto result = wid_botcon_lines.insert(std::make_pair(log_wid_botcon_buffered_lines++, s));

    if (! result.second) {
      DIE("Wid botcon lines insert name [%s] failed", wstring_to_string(s).c_str());
    }

    return;
  }

  //
  // Flush the logs now the botcon exists.
  //
  wid_botcon_flush();

  if (last_msg != s) {
    last_msg       = s;
    last_msg_count = 0;
    wid_botcon_scroll(wid_botcon_input_line, s);
  }
}

void wid_botcon_flush(void)
{
  TRACE_NO_INDENT();
  auto iter = wid_botcon_lines.begin();

  while (iter != wid_botcon_lines.end()) {
    wid_botcon_scroll(wid_botcon_input_line, iter->second);
    iter = wid_botcon_lines.erase(iter);
  }

  wid_botcon_reset_scroll();
}

//
// Log a message to the botcon
//
void wid_botcon_log(std::string s)
{
  TRACE_NO_INDENT();
  DBG3("BOTCON: %s", s.c_str());

  int chars_per_line = UI_BOTCON_WIDTH;

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      wid_botcon_log_(string_to_wstring(c));
    }
  }
}

//
// Log a message to the botcon
//
void wid_botcon_log(std::wstring s)
{
  TRACE_NO_INDENT();
  int chars_per_line = UI_BOTCON_WIDTH;

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      wid_botcon_log_(c);
    }
  }
}

//
// Create the botcon
//
static void wid_botcon_wid_create(void)
{
  TRACE_NO_INDENT();
  int h = UI_BOTCON_VIS_HEIGHT;

  {
    point tl = make_point(0, TERM_HEIGHT - h);
    point br = make_point(UI_BOTCON_VIS_WIDTH - 1, TERM_HEIGHT - 1);

    wid_botcon_window = wid_new_square_window("wid botcon");
    wid_set_name(wid_botcon_window, "wid botcon window");
    wid_set_pos(wid_botcon_window, tl, br);
    wid_set_ignore_events(wid_botcon_window, true);
    wid_set_ignore_scroll_events(wid_botcon_window, true);
    wid_set_shape_none(wid_botcon_window);
    // wid_set_style(wid_botcon_window, UI_WID_STYLE_GREEN);
  }

  {
    point tl = make_point(0, 0);
    point br = make_point(UI_BOTCON_VIS_WIDTH - 1, h - 1);

    wid_botcon_container = wid_new_container(wid_botcon_window, "wid botcon container");
    wid_set_pos(wid_botcon_container, tl, br);
    wid_set_shape_none(wid_botcon_container);
  }

  {
    int row;
    int row_bottom = h - 1;

    Widp child {};
    Widp prev {};

    for (row = 0; row < UI_BOTCON_HEIGHT; row++) {
      row_bottom--;
      point tl = make_point(0, row_bottom);
      point br = make_point(UI_BOTCON_WIDTH, row_bottom);

      child = wid_new_container(wid_botcon_container, "");

      wid_set_shape_none(child);
      wid_set_pos(child, tl, br);
      wid_set_text_lhs(child, true);

      wid_set_prev(child, prev);
      prev = child;

      if (row == 0) {
        wid_botcon_input_line = child;
      }

      wid_set_color(child, WID_COLOR_TEXT_FG, UI_BOTCON_TEXT_COLOR);
      wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
      wid_set_name(child, "botcon output");
    }

    wid_raise(wid_botcon_input_line);
  }

  wid_botcon_vert_scroll = wid_new_vert_scroll_bar(wid_botcon_window, "", wid_botcon_container);

  wid_hide(wid_get_parent(wid_botcon_vert_scroll));

  wid_update(wid_botcon_window);
}

std::vector< std::wstring > wid_botcon_serialize(void)
{
  TRACE_NO_INDENT();
  std::vector< std::wstring > r;
  auto                        tmp = wid_get_head(wid_botcon_input_line);
  while (tmp) {
    auto s = wid_get_text(tmp);
    if (s.size()) {
      r.push_back(wid_get_text(tmp));
    }
    tmp = wid_get_next(tmp);
  }
  std::reverse(r.begin(), r.end());
  return r;
}

void wid_botcon_deserialize(std::vector< std::wstring > r)
{
  TRACE_NO_INDENT();
  for (const auto &s : r) {
    auto tmp = wstring_to_string(s);
    if (tmp.size()) {
      BOTCON("%s", tmp.c_str());
    }
  }
}
