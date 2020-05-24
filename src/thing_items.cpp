//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::move_carried_items (void)
{_
    //
    // Light source follows the thing.
    //
    update_light();
_
    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim()) {_
        auto w = thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }
_
    if (get_weapon_id_use_anim()) {_
        auto w = thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }
_
    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {_
        if (level->is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x, mid_at.y);
            if (random_range(0, 1000) > 500) {
                thing_new(tp_random_ripple()->name(), at);
            }
        }
    }
_
    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id) {_
        auto w = thing_find(on_fire_anim_id);
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        } else {
        }
    }
}
