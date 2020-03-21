//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

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
