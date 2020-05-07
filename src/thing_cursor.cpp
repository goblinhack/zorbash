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
            fpoint blit_tl = tl;
            fpoint blit_br = br;
            float dx = - level->pixel_map_at.x;
            float dy = - level->pixel_map_at.y;
            blit_tl.x += dx;
            blit_tl.y += dy;
            blit_br.x += dx;
            blit_br.y += dy;

            auto mx = mouse_x;
            auto my = mouse_y;
            mx /= game->config.scale_pix_width;
            my /= game->config.scale_pix_height;

            if ((mx >= blit_tl.x) && (mx <= blit_br.x)) {
                if ((my >= blit_tl.y) && (my <= blit_br.y)) {
                    level->cursor_at = mid_at;
                    level->cursor_found = true;
                }
            }
        }
    }
}
