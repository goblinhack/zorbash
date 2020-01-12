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
#include "my_wid_text_box.h"

WidPopup::~WidPopup()
{
    wid_destroy(&wid_popup_container);
}

WidPopup::WidPopup (point tl, point br, Tilep title_tile,
                    std::string background) :
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
        tile_size = 6;
    } else {
        tile_size = 0;
    }

    if (title_tile) {
        inner_h -= tile_size;
        inner_tl.y += tile_size;
    }

    {
        wid_popup_container = wid_new_square_window("wid_popup");
        wid_set_pos(wid_popup_container, tl, br);
        wid_set_style(wid_popup_container, -1);
        if (background != "") {
            wid_set_bg_tile(wid_popup_container, tile_find_mand(background));
        }
    }

    if (title_tile) {
        auto w = wid_new_square_button(wid_popup_container, "wid title");
        wid_title = w;
        auto title_x = (outer_w - tile_size) / 2;
        wid_set_pos(w,
                    point(title_x + 1, 1),
                    point(title_x + tile_size, tile_size));
        wid_set_style(w, WID_STYLE_NORMAL);
        wid_set_fg_tile(w, title_tile);
    }

    {
        point tl = {0, + tile_size + 2};
        point br = {inner_w, inner_h + tile_size};
        wid_text_area = new WidTextBox(tl, br, wid_popup_container);
    }

    wid_update(wid_popup_container);
}

//
// Log a message to the popup
//
void WidPopup::log (std::string s)
{_
    wid_text_area->log(s);
}

//
// Log a message to the popup
//
void WidPopup::log (std::wstring s)
{_
    wid_text_area->log(s);
}
