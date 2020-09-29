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

        //
        // keep the light strength half the tiles drawn or we get artifacts
        // at the edges of the fbo
        //
        color col = WHITE;

        int strength = is_light_strength();
        int d1 = 1;
        int d2 = 2;

        new_light(point(0, 0), strength, col, FBO_FULLMAP_LIGHT);
        new_light(point(0, 0), strength, col, FBO_LIGHT);

        new_light(point(-d1, -d1), strength, col, FBO_LIGHT);
        new_light(point( d1, -d1), strength, col, FBO_LIGHT);
        new_light(point(-d1,  d1), strength, col, FBO_LIGHT);
        new_light(point( d1,  d1), strength, col, FBO_LIGHT);

        new_light(point(-d2, -d1), strength, col, FBO_LIGHT);
        new_light(point( d2, -d1), strength, col, FBO_LIGHT);
        new_light(point(-d2,  d1), strength, col, FBO_LIGHT);
        new_light(point( d2,  d1), strength, col, FBO_LIGHT);

        new_light(point(-d1, -d2), strength, col, FBO_LIGHT);
        new_light(point( d1, -d2), strength, col, FBO_LIGHT);
        new_light(point(-d1,  d2), strength, col, FBO_LIGHT);
        new_light(point( d1,  d2), strength, col, FBO_LIGHT);

        d1 = 3;
        d2 = 5;

        new_light(point(-d1, -d1), strength, col, FBO_LIGHT);
        new_light(point( d1, -d1), strength, col, FBO_LIGHT);
        new_light(point(-d1,  d1), strength, col, FBO_LIGHT);
        new_light(point( d1,  d1), strength, col, FBO_LIGHT);

        new_light(point(-d2, -d1), strength, col, FBO_LIGHT);
        new_light(point( d2, -d1), strength, col, FBO_LIGHT);
        new_light(point(-d2,  d1), strength, col, FBO_LIGHT);
        new_light(point( d2,  d1), strength, col, FBO_LIGHT);

        new_light(point(-d1, -d2), strength, col, FBO_LIGHT);
        new_light(point( d1, -d2), strength, col, FBO_LIGHT);
        new_light(point(-d1,  d2), strength, col, FBO_LIGHT);
        new_light(point( d1,  d2), strength, col, FBO_LIGHT);

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
                new_light(point(0, 0), is_light_strength(), c, FBO_LIGHT);
                has_light = true;
            }
        }
    }
}
