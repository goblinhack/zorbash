/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_python.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_thing_tile.h"
#include "my_tex.h"

void thing_render_all (void)
{_
#if 0
    double mx = game.video_pix_width / 2;
    double my = game.video_pix_width / 4;
    my += game.video_pix_width / 16;

    double tw = game.tile_width;
    double th = game.tile_height;

    tw /= 8;
    th /= 8;
    tw *= 5;
    th *= 5;

    double tw2 = tw / 2;
    double th2 = th / 2;

    size_t i;

    for (i = 0; i < things_draw_list_count; i++) {
	thingp t = things_draw_list[i];

        if (tp_is_animated(thing_tp(t))) {
            thing_animate(t);
        }
    }

    blit_init();

    for (i = 0; i < things_draw_list_count; i++) {
	thingp t = things_draw_list[i];

        double X = t->at.x;
        double Y = t->at.y;
        double Z = t->at.z;

        double x = mx - X * (tw / 2);
        double y = my + X * (th / 4);

        x += Y * (tw / 2);
        y += Y * (th / 4);
        y -= Z * (th / 2);

        fpoint tl;
        fpoint br;

        tl.x = x - tw2;
        tl.y = y - th2;
        br.x = x + tw2;
        br.y = y + th2;

        tpp tp = thing_tp(t);

        if (!t->tile) {
            LOG("no tile for %s", tp_name(tp));
            continue;
        }

        tile_blit_fat(tp, t->tile, 0, &tl, &br);
    }

    blit_flush();
#endif
}
