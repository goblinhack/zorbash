//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Thing::carry (Thingp what)
{_
    auto existing_owner = what->owner_get();
    if (existing_owner) {
        if (existing_owner == this) {
            return;
        }
        existing_owner->drop(what);
    }

    new_monst();
    for (auto item : monst->carrying) {
        if (item == what->id) {
            return;
        }
    }
    monst->carrying.push_front(what->id);
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
    if (!monst) {
        return;
    }
    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", what->to_string().c_str());
        return;
    }

    what->remove_owner();
    what->visible();

    monst->carrying.remove(what->id);
    log("dropped %s", what->to_string().c_str());
}

void Thing::drop_all (void)
{_
    if (!monst) {
        return;
    }

    while (!monst->carrying.empty()) {
        auto id = *monst->carrying.begin();
        return (drop(thing_find(id)));
    }
}
