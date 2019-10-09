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
    wid_destroy(&wid_text_inner_area);
    wid_destroy(&wid_vert_scroll);
    wid_destroy(&wid_horiz_scroll);
    wid_destroy(&wid_text_last);
    wid_destroy(&wid_text_area);
}

WidPopup::WidPopup (point tl, point br, Tilep title_tile) : 
    tl(tl), br(br), title_tile(title_tile)
{_
    int outer_w = br.x - tl.x;
    int outer_h = br.y - tl.y;
    width = outer_w;
    height = outer_h;

    point inner_tl = point(0, 0);
    point inner_br = point(width, height);
    int inner_w = inner_br.x - inner_tl.x;
    int inner_h = inner_br.y - inner_tl.y;
    int tile_size = 4;
    if (title_tile) {
        inner_h -= tile_size;
        inner_tl.y += tile_size;
    }

    scroll_height = inner_h * 2;
    line_count = 0;

    {
        wid_popup_container = wid_new_square_window("wid_popup");
        wid_set_pos(wid_popup_container, tl, br);
        wid_set_shape_box(wid_popup_container);
        wid_set_style(wid_popup_container, 1);
    }

    if (title_tile) {
        wid_title = wid_new_square_button(wid_popup_container,
                                          "wid title");
        auto title_x = (outer_w - tile_size) / 2;
        wid_set_fg_tile(wid_title, title_tile);
        wid_set_pos(wid_title, 
                    point(title_x, 0),
                    point(title_x + tile_size - 1, tile_size - 1));
        wid_set_shape_box(wid_title);
        wid_set_style(wid_title, 3);
    }

    {
        wid_text_area = wid_new_square_button(wid_popup_container,
                                              "wid text area");
        wid_set_pos(wid_text_area, inner_tl, inner_br);
        wid_set_shape_none(wid_text_area);
    }

    {
        point tl = {1, 1};
        point br = {inner_w - 1, inner_h - 1};

        wid_text_inner_area = wid_new_square_button(wid_text_area,
                                                    "wid text inner area");
        wid_set_pos(wid_text_inner_area, tl, br);
        wid_set_shape_none(wid_text_inner_area);
    }

    {
        int32_t row;
        int row_bottom = inner_h - 1;

        Widp child = 0;
        Widp prev = 0;

        for (row = 0; row < scroll_height; row++) {
            row_bottom --;
            point tl = { 0, row_bottom, };
            point br = { inner_w - 2, row_bottom, };

            child = wid_new_container(wid_text_inner_area, "");
            children.push_back(child);

            wid_set_shape_none(child);
            wid_set_pos(child, tl, br);
            wid_set_text_lhs(child, true);

            wid_set_prev(child, prev);
            prev = child;

            if (row == 0) {
                wid_text_last = child;
            }

            wid_set_color(child, WID_COLOR_TEXT, POPUP_TEXT_COLOR);
            wid_set_name(child, "popup output");
        }

        wid_raise(wid_text_last);
    }

    wid_vert_scroll =
        wid_new_vert_scroll_bar(wid_text_area, "", wid_text_inner_area);
    wid_horiz_scroll =
        wid_new_horiz_scroll_bar(wid_text_area, "", wid_text_inner_area);

    wid_hide(wid_get_parent(wid_vert_scroll));
    wid_hide(wid_get_parent(wid_horiz_scroll));

    wid_update(wid_popup_container);
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
        wid_visible(wid_get_parent(wid_vert_scroll));
        wid_visible(wid_get_parent(wid_horiz_scroll));

        wid_scroll_text(wid_text_last);
        tmp = wid_get_head(wid_text_last);
        if (tmp) {
            wid_set_text(tmp, str);
        }
    }
    wid_move_to_top(wid_vert_scroll);
    line_count++;
}

//
// Log a message to the popup
//
void WidPopup::log (std::string s)
{_
    int chars_per_line = wid_get_width(wid_text_area) - 1;

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
    int chars_per_line = wid_get_width(wid_text_area) - 1;

    auto d = split(s, chars_per_line);

    if (d) {
        for (auto c : *d) {
            log_(c);
        }
    }
}
