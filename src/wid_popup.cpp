//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_popup.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_wid_popup.h"

WidPopup::~WidPopup()
{
    wid_destroy(&wid_popup_container);
    wid_destroy(&wid_popup_vert_scroll);
    wid_destroy(&wid_popup_horiz_scroll);
    wid_destroy(&wid_popup_input_line);
    wid_destroy(&wid_popup_window);
}

WidPopup::WidPopup (point tl, point br) : tl(tl), br(br)
{_
    int w = br.x - tl.x;
    int h = br.y - tl.y;

    width = w;
    height = h;
    scroll_height = h * 2;
    line_count = 0;

    {
        wid_popup_window = wid_new_square_window("wid_popup");
        wid_set_pos(wid_popup_window, tl, br);
        wid_set_shape_box(wid_popup_window);
        wid_set_style(wid_popup_window, 1);
    }

    {
        point tl = {1, 1};
        point br = {w - 1, h - 1};

        wid_popup_container = wid_new_square_button(wid_popup_window,
                                                    "wid popup container");
        wid_set_pos(wid_popup_container, tl, br);
        wid_set_style(wid_popup_container, 2);
    }

    {
        int32_t row;
        int row_bottom = h - 1;

        Widp child = 0;
        Widp prev = 0;

        for (row = 0; row < scroll_height; row++) {
            row_bottom --;
            point tl = { 0, row_bottom, };
            point br = { w - 2, row_bottom, };

            child = wid_new_container(wid_popup_container, "");
            children.push_back(child);

            wid_set_shape_none(child);
            wid_set_pos(child, tl, br);
            wid_set_text_lhs(child, true);

            wid_set_prev(child, prev);
            prev = child;

            if (row == 0) {
                wid_popup_input_line = child;
            }

            wid_set_color(child, WID_COLOR_TEXT, POPUP_TEXT_COLOR);
            wid_set_name(child, "popup output");
        }

        wid_raise(wid_popup_input_line);
    }

    wid_popup_vert_scroll =
        wid_new_vert_scroll_bar(wid_popup_window, "", wid_popup_container);
    wid_popup_horiz_scroll =
        wid_new_horiz_scroll_bar(wid_popup_window, "", wid_popup_container);

    wid_hide(wid_get_parent(wid_popup_vert_scroll));
    wid_hide(wid_get_parent(wid_popup_horiz_scroll));

    wid_update(wid_popup_window);
}

//
// Get the wid on the bottom of the list/screen.
//
void WidPopup::log_ (std::wstring str)
{_
    Widp tmp;

    if (line_count < scroll_height) {
        wid_set_text(get(children, scroll_height - line_count - 1), str);
    } else {
        wid_scroll_text(wid_popup_input_line);
        tmp = wid_get_head(wid_popup_input_line);
        if (tmp) {
            wid_set_text(tmp, str);
        }
    }
    wid_move_to_top(wid_popup_vert_scroll);
    line_count++;
}

//
// Log a message to the popup
//
void WidPopup::log (std::string s)
{_
    int chars_per_line = wid_get_width(wid_popup_window) - 1;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            log_(string_to_wstring(c));
        }
    }
}

//
// Log a message to the popup
//
void WidPopup::log (std::wstring s)
{_
    int chars_per_line = wid_get_width(wid_popup_window) - 1;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            log_(c);
        }
    }
}
