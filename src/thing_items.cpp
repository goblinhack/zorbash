//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::move_carried_items (void)
{
    //
    // Light source follows the thing.
    //
    update_light();

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim()) {
        auto w = thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    if (get_weapon_id_use_anim()) {
        auto w = thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (level->is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x, mid_at.y);
            if (random_range(0, 1000) > 500) {
                thing_new(tp_name(tp_random_ripple()), at);
            }
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id) {
        auto w = thing_find(on_fire_anim_id);
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        } else {
        }
    }
}
