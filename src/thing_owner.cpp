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

Thingp Thing::owner_get (void) const
{_
    auto id = get_owner_id();
    if (id.ok()) {
        auto i = level->thing_find(id);
        if (!i) {
            return nullptr;
        }
        if (i->get_owner_id().ok()) {
            return i->owner_get();
        }
        return i;
    } else {
        return nullptr;
    }
}

void Thing::set_owner (Thingp owner)
{_
    if (owner) {
        verify(owner);
    }

    auto old_owner = owner_get();
    if (old_owner) {
        if (old_owner == owner) {
            return;
        }

        if (tp()->is_loggable_for_important_stuff()) {
            if (owner) {
                log("set owner change %s->%s", old_owner->to_string().c_str(),
                    owner->to_string().c_str());
            } else {
                log("remove owner %s", old_owner->to_string().c_str());
            }
        }
    } else {
        if (tp()->is_loggable_for_important_stuff()) {
            if (owner) {
                log("set owner %s", owner->to_string().c_str());
            }
        }
    }

    if (owner) {
        set_owner_id(owner->id);
        owner->incr_owned_count();
    } else {
        set_owner_id(0);
        if (old_owner) {
            old_owner->decr_owned_count();
        }
    }
}

void Thing::remove_owner (void)
{_
    auto old_owner = owner_get();
    if (!old_owner) {
        return;
    }

    if (tp()->is_loggable_for_important_stuff()) {
        log("remove owner %s", old_owner->to_string().c_str());
    }

    set_owner_id(0);
    old_owner->decr_owned_count();
}
