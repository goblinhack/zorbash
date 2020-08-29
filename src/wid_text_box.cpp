//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_text_box.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_wid_text_box.h"

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

WidTextBox::WidTextBox (point tl, point br, Widp parent,
                        bool horiz_scroll, bool vert_scoll) :
    tl(tl), br(br), wid_parent(parent)
{_
    int w = br.x - tl.x;
    int h = br.y - tl.y;
    width = w;
    height = h;

    scroll_height = h * 2;
    line_count = 0;

    {
        if (parent) {
            wid_text_box_container = wid_new_square_button(parent,
                                                           "wid text box");
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

        wid_text_area = wid_new_square_button(wid_text_box_container,
                                              "wid text inner area");
        wid_set_pos(wid_text_area, tl, br);
        wid_set_shape_none(wid_text_area);

        w = br.x - tl.x;
        h = br.y - tl.y;
    }

    {
        int32_t row;
        int row_bottom = h - 1;

        Widp child {};
        Widp prev {};

        for (row = 0; row < scroll_height; row++) {
            row_bottom --;
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
        wid_vert_scroll =
            wid_new_vert_scroll_bar(wid_text_box_container,
                                    "text box vert scroll", wid_text_area);
    }

    if (horiz_scroll) {
        wid_horiz_scroll =
            wid_new_horiz_scroll_bar(wid_text_box_container,
                                     "text box horiz scroll", wid_text_area);
    }

    wid_update(wid_text_box_container);

    if (horiz_scroll) {
        wid_not_visible(wid_get_parent(wid_horiz_scroll));
        wid_not_visible(wid_horiz_scroll);
    }

    if (vert_scoll) {
        wid_visible(wid_get_parent(wid_vert_scroll));
        wid_visible(wid_vert_scroll);
    }
}

//
// Get the wid on the bottom of the list/screen.
//
void WidTextBox::log_ (std::wstring str, bool lhs, bool rhs)
{_
    Widp tmp {};
    Widp text_wid {};

    if (!wid_vert_scroll) {
        if (line_count < scroll_height) {
            text_wid = get(children, height - line_count - 1);
            wid_set_text(text_wid, str);
            line_count++;
            wid_update(wid_text_box_container);
        } else {
            ERR("text box overflow");
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
        if (lhs) { wid_set_text_lhs(text_wid, true); }
        if (rhs) { wid_set_text_rhs(text_wid, true); }
    }
}

//
// Log a message to the text_box
//
void WidTextBox::log (std::string s, bool lhs, bool rhs)
{_
    int chars_per_line = wid_get_width(wid_text_area);

    auto d = split(s, chars_per_line);

    if (d) {
        for (const auto& c : *d) {
            log_(string_to_wstring(c), lhs, rhs);
        }
    }
}

//
// Log a message to the text_box
//
void WidTextBox::log (std::wstring s, bool lhs, bool rhs)
{_
    int chars_per_line = wid_get_width(wid_text_area);

    auto d = split(s, chars_per_line);

    if (d) {
        for (const auto& c : *d) {
            log_(c, lhs, rhs);
        }
    }
}
