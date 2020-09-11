//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_gl.h"

void Thing::init_lights (void)
{_
    if (unlikely(is_player())) {
        if (level->player && (level->player != this)) {
            DIE("player exists in multiple places on map, %f, %f and %f, %f",
                level->player->mid_at.x, level->player->mid_at.y, 
                mid_at.x, mid_at.y);
            return;
        }
        level->player = this;

        set_last_lit_at(point(-1, -1));

        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        color col = WHITE;

        float strength = TILE_WIDTH;
        float ostrength = TILE_WIDTH;
        float d1 = (1.0 / (float)TILE_WIDTH) * 1;
        float d2 = (1.0 / (float)TILE_WIDTH) * 2;

        new_light(mid_at, ostrength, col, FBO_FULLMAP_LIGHT);
        new_light(mid_at, strength, col, FBO_LIGHT);

        new_light(mid_at, fpoint(-d1, -d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d1, -d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint(-d1,  d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d1,  d1), strength, col, FBO_LIGHT);

        new_light(mid_at, fpoint(-d2, -d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d2, -d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint(-d2,  d1), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d2,  d1), strength, col, FBO_LIGHT);

        new_light(mid_at, fpoint(-d1, -d2), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d1, -d2), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint(-d1,  d2), strength, col, FBO_LIGHT);
        new_light(mid_at, fpoint( d1,  d2), strength, col, FBO_LIGHT);

        has_light = true;
        log("player created");
    } else {
        if (unlikely(is_light_strength())) {
            std::string l = light_color();
            if (l.empty()) {
                l = "white";
            }
            bool add_light = true;
            if (is_lava()) {
                if (random_range(0, 100) < 50) {
                    add_light = false;
                }
            }
            if (add_light) {
                color c = string2color(l);
                new_light(mid_at, (double) is_light_strength(), c, FBO_LIGHT);
                has_light = true;
            }
        }
    }

    update_light();
}
