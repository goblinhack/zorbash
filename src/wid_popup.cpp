//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "slre.h"
#include "my_wid_popup.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_wid_popup.h"
#include "my_wid_text_box.h"

WidPopup::~WidPopup()
{
    wid_destroy(&wid_popup_container);
    delete wid_text_area;
}

WidPopup::WidPopup (const std::string name,
                    point tl, point br, Tilep title_tile,
                    const std::string background,
                    bool horiz_scroll,
                    bool vert_scoll) :
    tl(tl), br(br),
    title_tile(title_tile),
    background(background)
{_
    int outer_w = br.x - tl.x;
    int outer_h = br.y - tl.y;
    int width = outer_w;
    int height = outer_h;

    point inner_tl = point(0, 0);
    point inner_br = point(width, height);
    int inner_w = inner_br.x - inner_tl.x;
    int inner_h = inner_br.y - inner_tl.y;

    int tile_size;
    if (title_tile) {
        tile_size = 3;
    } else {
        tile_size = 0;
    }

    if (title_tile) {
        inner_h -= tile_size;
        inner_tl.y += tile_size;
    }

    {
        wid_popup_container = wid_new_square_window("wid_popup " + name);
        wid_set_pos(wid_popup_container, tl, br);
        wid_set_style(wid_popup_container, UI_WID_STYLE_NONE);
        if (background != "") {
            wid_set_bg_tile(wid_popup_container, tile_find_mand(background));
        } else {
            wid_set_style(wid_popup_container, UI_WID_STYLE_NORMAL);
        }
    }

    if (title_tile) {
        auto w = wid_new_square_button(wid_popup_container, "wid title " + name);
        wid_title = w;
        auto title_x = (outer_w - tile_size) / 2;
        wid_set_pos(w,
                    point(title_x + 0, 1),
                    point(title_x + tile_size, tile_size));
        wid_set_style(w, UI_WID_STYLE_DARK);
        wid_set_fg_tile(w, title_tile);
    }

    {
        point tl = make_point(0, + tile_size + 0);
        point br = make_point(inner_w, inner_h + tile_size);
        wid_text_area = new WidTextBox(tl, br, wid_popup_container,
                                       horiz_scroll, vert_scoll);
    }

    wid_update(wid_popup_container);
}

//
// Log a message to the popup
//
void WidPopup::log (std::string s, bool lhs, bool rhs)
{_
    wid_text_area->log(s, lhs, rhs);
}

//
// Log a message to the popup
//
void WidPopup::log (std::wstring s, bool lhs, bool rhs)
{_
    wid_text_area->log(s, lhs, rhs);
}
