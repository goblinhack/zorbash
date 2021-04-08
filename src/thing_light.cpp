//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_sys.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_monst.h"

int Thing::light_strength (void) const
{_
    auto light_strength = tp()->light_strength();

    if (!monstp) {
        return light_strength;
    }

    auto torch_count = 0;
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (!o) {
            continue;
        }

        if (!o->is_torch()) {
            continue;
        }

        if (o->get_charge_count()) {
            torch_count += o->get_charge_count();
        } else {
            torch_count++;
        }
    }

    if (torch_count == 2) {
        light_strength /= 2;
    }

    if (torch_count == 1) {
        light_strength /= 2;
    }

    if (torch_count == 0) {
        light_strength = 1;
    }

    return light_strength;
}

void Thing::init_lights (void)
{_
    if (unlikely(is_player())) {
        if (level->player && (level->player != this)) {
            DIE("Player exists in multiple places on map, %f, %f and %f, %f",
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

        int strength = light_strength();
        int d1 = 1;
        int d2 = 2;

        new_light(point(0, 0), strength, col, FBO_FULLMAP_LIGHT);
        new_light(point(0, 0), strength, col, FBO_PLAYER_LIGHT);
        new_light(point(0, 0), 3, col, FBO_SMALL_LIGHTS);

        new_light(point(-d1, -d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d1, -d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point(-d1,  d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d1,  d1), strength, col, FBO_PLAYER_LIGHT);

        new_light(point(-d2, -d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d2, -d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point(-d2,  d1), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d2,  d1), strength, col, FBO_PLAYER_LIGHT);

        new_light(point(-d1, -d2), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d1, -d2), strength, col, FBO_PLAYER_LIGHT);
        new_light(point(-d1,  d2), strength, col, FBO_PLAYER_LIGHT);
        new_light(point( d1,  d2), strength, col, FBO_PLAYER_LIGHT);

        {
            d1 = 3;
            d2 = 5;

            new_light(point(-d1, -d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d1, -d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point(-d1,  d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d1,  d1), strength, col, FBO_PLAYER_LIGHT);

            new_light(point(-d2, -d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d2, -d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point(-d2,  d1), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d2,  d1), strength, col, FBO_PLAYER_LIGHT);

            new_light(point(-d1, -d2), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d1, -d2), strength, col, FBO_PLAYER_LIGHT);
            new_light(point(-d1,  d2), strength, col, FBO_PLAYER_LIGHT);
            new_light(point( d1,  d2), strength, col, FBO_PLAYER_LIGHT);
        }

        has_light = true;
        log("Player created");
    } else {
        if (unlikely(light_strength())) {
            std::string l = light_color();
            if (l.empty()) {
                l = "white";
            }
            bool add_light = true;
            if (is_lava()) {
//                if (random_range(0, 100) < 80) {
                    add_light = true;
//                }
            }
            if (add_light) {
                color c = string2color(l);
                new_light(point(0, 0), light_strength(), c, FBO_PLAYER_LIGHT);
                has_light = true;
            }
        }
    }
}

void Thing::light_update_strength (void)
{_
    auto str = light_strength();
    for (auto l : get_light()) {
        if (str != l->orig_strength) {
            l->orig_strength = str;
            l->update();
        }
    }
}
