//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"

bool Thing::carry (Thingp what)
{_
    if (is_player()) {
        if (!actionbar_id_insert(what)) {
            return false;
        }
    }

    if (!monstp) {
        return false;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner) {
        if (existing_owner == this) {
            return false;
        }
        existing_owner->drop(what);
    }

    for (const auto& item : monstp->carrying) {
        if (item == what->id) {
            return false;
        }
    }

    monstp->carrying.push_front(what->id);
    what->set_owner(this);
    what->hide();

    log("is now carrying %s", what->to_string().c_str());

    //
    // If we have no weapon, wield it
    //
    if (is_weapon_wielder()) {
        if (what->is_weapon() && !get_weapon_id()) {
            wield(what);
        }
    }

    return true;
}

bool Thing::try_to_carry (Thingp what)
{_
    if (get_tick() - get_tick_last_level_change() <= 1) {
        return false;
    }
    return carry(what);
}
