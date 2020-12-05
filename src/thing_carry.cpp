//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"

bool Thing::carry (Thingp what)
{_
    log("try to carry %s", what->to_string().c_str());
_
    if (!monstp) {
        log("no; not a monst");
        return false;
    }

    if (particle_anim_exists()) {
        log("no; particle anim exists");
        return false;
    }

    if (get_where_i_dropped_an_item_last() == make_point(mid_at)) {
        log("no; was dropped here recently");
        return false;
    }

    if (!bag_add(what)) {
        log("no; cannot store");
        return false;
    }

    if (is_player()) {
        if (!inventory_id_insert(what)) {
            log("no; no space in inventory");
            return false;
        }
    }

    auto existing_owner = what->owner_get();
    if (existing_owner) {
        if (existing_owner == this) {
            log("no; same owner");
            return false;
        }
        existing_owner->drop(what);
    }

    for (const auto& item : monstp->carrying) {
        if (item == what->id) {
            log("no; already carried");
            return false;
        }
    }

    monstp->carrying.push_front(what->id);
    what->set_owner(this);
    what->hide();

    log("yes; is now carrying %s", what->to_string().c_str());

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
    return carry(what);
}
