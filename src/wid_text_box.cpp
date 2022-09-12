//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <SDL.h>

#include "my_backtrace.hpp"
#include "my_color.hpp"
#include "my_color_defs.hpp"
#include "my_sdl.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid.hpp"
#include "my_wid_text_box.hpp"
#include "slre.hpp"

WidTextBox::~WidTextBox()
{
  if (wid_horiz_scroll) {
    wid_destroy(&wid_horiz_scroll);
  }
  if (wid_vert_scroll) {
    wid_destroy(&wid_vert_scroll);
  }
  wid_destroy(&wid_text_last);
  wid_destroy(&wid_text_area);
}

WidTextBox::WidTextBox(point tl, point br, Widp parent, bool horiz_scroll, bool vert_scoll, int scroll_height_in)
    : scroll_height(scroll_height_in), tl(tl), br(br), wid_parent(parent)
{
  TRACE_AND_INDENT();
  int w = br.x - tl.x;
  int h = br.y - tl.y;
  width = w;

  if (scroll_height == -1) {
    if (vert_scoll) {
      scroll_height = h * 2;
    } else {
      scroll_height = h;
    }
  }

  line_count = 0;

  {
    if (parent) {
      wid_text_box_container = wid_new_square_button(parent, "wid text box");
      wid_set_shape_none(wid_text_box_container);
    } else {
      wid_text_box_container = wid_new_square_window("wid text box");
      wid_set_style(wid_text_box_container, UI_WID_STYLE_GREEN);
    }
    wid_set_pos(wid_text_box_container, tl, br);
  }

  {
    point tl = make_point(1, 1);
    point br = make_point(w - 1, h - 1);

    wid_text_area = wid_new_square_button(wid_text_box_container, "wid text inner area");
    wid_set_pos(wid_text_area, tl, br);
    wid_set_shape_none(wid_text_area);
    // wid_set_style(wid_text_area, UI_WID_STYLE_RED);

    w = br.x - tl.x;
    h = br.y - tl.y;
  }

  {
    int row;

    Widp child {};
    Widp prev {};

    int lines_of_text;
    if (vert_scoll) {
      lines_of_text = scroll_height;
    } else {
      lines_of_text = wid_get_height(wid_text_area);
    }
    int row_bottom = lines_of_text;
    height         = lines_of_text;

    for (row = 0; row < lines_of_text; row++) {
      row_bottom--;
      point tl = make_point(0, row_bottom);
      point br = make_point(w, row_bottom);

      child = wid_new_container(wid_text_area, "");
      children.push_back(child);

      wid_set_shape_none(child);
      wid_set_pos(child, tl, br);
      wid_set_text_centerx(child, true);

      wid_set_prev(child, prev);
      prev = child;

      if (row == 0) {
        wid_text_last = child;
      }

      wid_set_color(child, WID_COLOR_TEXT_FG, UI_POPUP_TEXT_COLOR);
      wid_set_name(child, "text_box output");
    }

    wid_raise(wid_text_last);
  }

  if (vert_scoll) {
    wid_vert_scroll = wid_new_vert_scroll_bar(wid_text_box_container, "text box vert scroll", wid_text_area);
  }

  if (horiz_scroll) {
    wid_horiz_scroll = wid_new_horiz_scroll_bar(wid_text_box_container, "text box horiz scroll", wid_text_area);
  }

  wid_update(wid_text_box_container);

  if (horiz_scroll) {
    wid_hide(wid_get_parent(wid_horiz_scroll));
    wid_hide(wid_horiz_scroll);
  }

  if (vert_scoll) {
    wid_visible(wid_get_parent(wid_vert_scroll));
    wid_visible(wid_vert_scroll);
  }
}

//
// Get the wid on the bottom of the list/screen.
//
void WidTextBox::log_(std::wstring str, wid_text_format format, std::string color)
{
  TRACE_AND_INDENT();
  Widp tmp {};
  Widp text_wid {};

  if (! wid_vert_scroll) {
    if (line_count < height) {
      text_wid = get(children, height - line_count - 1);
      wid_set_text(text_wid, str);
      line_count++;
      wid_update(wid_text_box_container);
    } else {
      CON("Text box overflow on [%s] height %d line_count %d", wstring_to_string(str).c_str(), height, line_count);
      backtrace_dump();
      return;
    }
  } else {
    if (line_count < scroll_height) {
      text_wid = get(children, scroll_height - line_count - 1);
      wid_set_text(text_wid, str);
    } else {
      wid_scroll_text(wid_text_last);
      tmp = wid_get_head(wid_text_last);
      if (tmp) {
        wid_set_text(tmp, str);
      }
      text_wid = tmp;
    }

    if (wid_vert_scroll) {
      wid_move_to_top(wid_vert_scroll);
    }
    line_count++;

    int show_scrollbars_at = wid_get_height(wid_text_area);
    if (line_count > show_scrollbars_at) {
      if (wid_horiz_scroll) {
        wid_visible(wid_get_parent(wid_horiz_scroll));
      }
      if (wid_vert_scroll) {
        wid_visible(wid_get_parent(wid_vert_scroll));
      }
    }
  }

  if (text_wid) {
    if (format == TEXT_FORMAT_LHS) {
      wid_set_text_lhs(text_wid, true);
    } else if (format == TEXT_FORMAT_RHS) {
      wid_set_text_rhs(text_wid, true);
    }
  }

  if (! color.empty()) {
    wid_set_color(text_wid, WID_COLOR_TEXT_FG, color_find(color.c_str()));
  }
}

//
// Log a message to the text_box
//
void WidTextBox::log(std::string s, wid_text_format format, std::string color)
{
  TRACE_AND_INDENT();
  int chars_per_line = wid_get_width(wid_text_area);

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      //
      // Handles %%fg=...$ with no text due to a split
      //
      if (length_without_format(c)) {
        log_(string_to_wstring(c), format, color);
      }
    }
  }
}

//
// Log a message to the text_box
//
void WidTextBox::log(std::wstring s, wid_text_format format, std::string color)
{
  TRACE_AND_INDENT();
  int chars_per_line = wid_get_width(wid_text_area);

  auto d = split(s, chars_per_line);

  if (d) {
    for (const auto &c : *d) {
      log_(c, format, color);
    }
  }
}
