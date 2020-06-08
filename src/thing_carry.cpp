//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_thing.h"

void Thing::carry (Thingp what)
{_
    if (is_player()) {
        if (!actionbar_id_insert(what)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner) {
        if (existing_owner == this) {
            return;
        }
        existing_owner->drop(what);
    }

    new_monst();
    for (const auto& item : monstp->carrying) {
        if (item == what->id) {
            return;
        }
    }
    monstp->carrying.push_front(what->id);
    what->set_owner(this);
    what->hide();

    log("is now carrying %s", what->to_string().c_str());

    //
    // If we have no weapon, wield it
    //
    if (what->is_weapon() && !get_weapon_id()) {
        wield(what);
    }
}

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
        return (drop(thing_find(id)));
    }
}
