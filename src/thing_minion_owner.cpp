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

Thingp Thing::get_top_minion_owner (void) const
{_
    auto id = get_immediate_minion_owner_id();
    if (likely(id.ok())) {
        auto i = level->thing_find(id);
        if (unlikely(!i)) {
            return nullptr;
        }
        if (unlikely(i->get_immediate_minion_owner_id().ok())) {
            return i->get_immediate_minion_owner();
        }
        return i;
    } else {
        return nullptr;
    }
}

Thingp Thing::get_immediate_minion_owner (void) const
{_
    auto id = get_immediate_minion_owner_id();
    if (likely(id.ok())) {
        auto i = level->thing_find(id);
        if (unlikely(!i)) {
            return nullptr;
        }
        return i;
    } else {
        return nullptr;
    }
}

void Thing::set_minion_owner (Thingp minion_owner)
{_
    if (minion_owner) {
        verify(minion_owner);
    }

    auto old_minion_owner = get_immediate_minion_owner();
    if (old_minion_owner) {
        if (old_minion_owner == minion_owner) {
            return;
        }

        if (tp()->is_loggable_for_important_stuff()) {
            if (minion_owner) {
                log("Will change minion_owner %s->%s", old_minion_owner->to_string().c_str(),
                    minion_owner->to_string().c_str());
            } else {
                log("Will remove minion_owner %s", old_minion_owner->to_string().c_str());
            }
        }
    } else {
        if (tp()->is_loggable_for_important_stuff()) {
            if (minion_owner) {
                log("Will set minion_owner to %s", minion_owner->to_string().c_str());
            }
        }
    }

    if (minion_owner) {
        set_minion_owner_id(minion_owner->id);
        minion_owner->incr_spawned_count();
    } else {
        set_minion_owner_id(0);
        if (old_minion_owner) {
            old_minion_owner->decr_spawned_count();
        }
    }
}

void Thing::remove_minion_owner (void)
{_
    auto old_minion_owner = get_immediate_minion_owner();
    if (!old_minion_owner) {
        return;
    }

    if (tp()->is_loggable_for_important_stuff()) {
        log("Remove minion_owner %s", old_minion_owner->to_string().c_str());
    }

    set_minion_owner_id(0);
    old_minion_owner->decr_spawned_count();

    //
    // If this was fire and it had an minion_owner (the thing it set on fire)
    // and that minion_owner is now dead, the fire is free to fall into a chasm
    //
    location_check();
}
