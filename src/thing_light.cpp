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
        new_light(mid_at, TILE_WIDTH, col);

        float d1 = 0.2;
        float d2 = 0.15;
        new_light(mid_at, fpoint(d1, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d1, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(d2, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d1, -d2), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, -d1), TILE_WIDTH, col);
        new_light(mid_at, fpoint(-d2, -d2), TILE_WIDTH, col);

        has_light = true;
        log("player created");
    } else {
        if (unlikely(is_light_strength())) {
            std::string l = light_color();
            bool add_light = true;
            if (is_lava()) {
                if (random_range(0, 100) < 50) {
                    add_light = false;
                }
            }
            if (add_light) {
                color c = string2color(l);
                new_light(mid_at, (double) is_light_strength(), c);
                has_light = true;
            }
        }
    }

    update_light();
}
