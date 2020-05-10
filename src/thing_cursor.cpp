//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_depth.h"
#include "my_wid_console.h"
#include "my_sdl.h"
#include "my_ascii.h"
#include "my_wid.h"
#include "my_thing.h"
#include "my_dmap.h"

void Thing::cursor_hover_over_check (void)
{
    if (is_cursor_can_hover_over()) {
        if (is_blitted) {
            spoint tblit_tl = blit_tl;
            spoint tblit_br = blit_br;
            int dx = - level->pixel_map_at.x;
            int dy = - level->pixel_map_at.y;
            tblit_tl.x += dx;
            tblit_tl.y += dy;
            tblit_br.x += dx;
            tblit_br.y += dy;

            auto mx = mouse_x;
            auto my = mouse_y;
            mx /= game->config.scale_pix_width;
            my /= game->config.scale_pix_height;

            if ((mx >= tblit_tl.x) && (mx <= tblit_br.x)) {
                if ((my >= tblit_tl.y) && (my <= tblit_br.y)) {
                    level->cursor_at = mid_at;
                    level->cursor_found = true;
                }
            }
        }
    }
}
