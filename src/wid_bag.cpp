//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_slre.h"
#include "my_wid_bag.h"
#include "my_ttf.h"
#include "my_string.h"
#include "my_wid.h"
#include "my_ascii.h"
#include "my_wid_popup.h"

WidBag::~WidBag()
{
    wid_destroy(&wid_popup_container);
}

WidBag::WidBag (point tl, point br) : tl(tl), br(br)
{_
#if 0
    int outer_w = br.x - tl.x;
    int outer_h = br.y - tl.y;
    int width = outer_w;
    int height = outer_h;

    point inner_tl = point(0, 0);
    point inner_br = point(width, height);
    int inner_w = inner_br.x - inner_tl.x;
    int inner_h = inner_br.y - inner_tl.y;
#endif

    {
        wid_popup_container = wid_new_square_window("wid_popup");
        wid_set_pos(wid_popup_container, tl, br);
        wid_set_style(wid_popup_container, -1);
        wid_set_style(wid_popup_container, UI_WID_STYLE_BAG);
    }

    wid_update(wid_popup_container);
}
