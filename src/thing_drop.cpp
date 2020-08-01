//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"

void Thing::drop (Thingp what)
{_
    if (is_player()) {
        if (!actionbar_id_remove(what)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", what->to_string().c_str());
        return;
    }

    what->hooks_remove();
    what->remove_owner();
    what->visible();

    monstp->carrying.remove(what->id);
    log("dropped %s", what->to_string().c_str());
}

void Thing::drop (Thingp what, Thingp target)
{_
    if (is_player()) {
        if (!actionbar_id_remove(what, target)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", what->to_string().c_str());
        return;
    }

    what->hooks_remove();
    what->remove_owner();
    what->visible();

    monstp->carrying.remove(what->id);
    log("dropped %s", what->to_string().c_str());
}

void Thing::drop_all (void)
{_
    if (!monstp) {
        return;
    }

    while (!monstp->carrying.empty()) {
        auto id = *monstp->carrying.begin();
        auto t = level->thing_find(id);
        if (!t) {
            return;
        }
        drop(t);
    }
}
