//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_ascii.h"
#include "my_depth.h"
#include "my_dmap.h"
#include "my_game.h"
#include "my_wid_inventory.h"
#include "my_wid_rightbar.h"
#include "my_sdl.h"
#include "my_thing.h"
#include "my_wid.h"
#include "my_wid_console.h"
#include "my_wid_bag.h"

void Thing::cursor_hover_over_check (void)
{
    if (!is_blitted) {
        return;
    }

    point tblit_tl = last_blit_tl;
    point tblit_br = last_blit_br;

    auto mx = mouse_x;
    auto my = mouse_y;
    mx /= game->config.game_pix_scale_width;
    my /= game->config.game_pix_scale_height;

    if ((mx >= tblit_tl.x) && (mx <= tblit_br.x)) {
        if ((my >= tblit_tl.y) && (my <= tblit_br.y)) {
            if (is_mouse_over_rightbar()) {
                return;
            }

            if (is_mouse_over_any_bag()) {
                return;
            }

            level->cursor_at = mid_at;
            level->cursor_found = true;
        }
    }
}
