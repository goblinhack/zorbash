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

bool Thing::set_on_fire (void)
{_
    if (get_on_fire_anim_id()) {
        return (false);
    }

    log("set on fire");
    auto on_fire_anim = thing_new("fire", this);
    set_on_fire_anim_id(on_fire_anim->id);
    on_fire_anim->set_owner(this);
    move_carried_items();
    return (true);
}
