//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::unset_on_fire (void)
{_
    auto id = get_on_fire_anim_id();
    if (!id) {
        return;
    }

    auto fire_anim = thing_find(id);
    if (fire_anim) {
        log("unset on fire");
        fire_anim->dead("remove fire");
        set_on_fire_anim_id(0);
    }
}

void Thing::set_on_fire (void)
{_
    if (get_on_fire_anim_id()) {
        return;
    }

    log("set on fire");
    auto on_fire_anim = thing_new("fire", this);
    set_on_fire_anim_id(on_fire_anim->id);
    on_fire_anim->set_owner(this);
    move_carried_items();
}

void Thing::on_fire_tick (void)
{_
    auto id = get_on_fire_anim_id();
    if (!id) {
        return;
    }

    auto fire_anim = thing_find(id);
    if (!fire_anim) {
        return;
    }

    if (level->is_water(mid_at.x, mid_at.y)) {
        decr_on_fire_count();
        auto id = get_on_fire_anim_id();
        if (!id) {
            if (is_player()) {
                MINICON("%%fg=yellow$You extinguish the flames!%%fg=reset$");
            }
            auto smoke = thing_new("smoke1", fpoint((int)mid_at.x, (int)mid_at.y));
            smoke->set_lifespan_count(4);
            return;
        }
    }

    auto damage = fire_anim->get_stats_attack();
    if (is_player()) {
        MINICON("%%fg=yellow$You take %d fire damage!%%fg=reset$", damage);
    }

    //
    // Visible hit indication
    //
    msg(string_sprintf("%%fg=yellow$-%d ON FIRE!", damage));

    decr_stats_health(damage);

    if (get_stats_health() <= 1) {
        //
        // starvation is just annoying for players
        //
        dead("burned to death");
    }
}
