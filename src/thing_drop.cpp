//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"

bool Thing::drop (Thingp what, Thingp target)
{_
    if (target) {
        log("drop %s at %s", what->to_string().c_str(),
            target->to_string().c_str());
    } else {
        log("drop %s", what->to_string().c_str());
    }

    auto existing_owner = what->get_immediate_owner();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    if (is_player()) {
        if (target) {
            inventory_id_remove(what, target);
        } else {
            inventory_id_remove(what);
        }
    }

    what->hooks_remove();
    what->remove_owner();

    //
    // Hide as the particle drop will reveal it
    //
    if (is_player()) {
        what->hide();
    } else {
        what->visible();
    }

    if (target) {
        what->move_to_immediately(target->mid_at);
    } else {
        what->move_to_immediately(mid_at);
    }

    monstp->carrying.remove(what->id);

    //
    // Prevent too soon re-carry
    //
    set_where_i_dropped_an_item_last(make_point(mid_at));

    if (is_player()) {
        wid_inventory_init();
        wid_thing_info_fini();
    }

    log("dropped %s", what->to_string().c_str());

    return true;
}

//
// An item in between bags
//
bool Thing::drop_into_ether (Thingp what)
{_
    log("drop %s into the ether", what->to_string().c_str());

    auto existing_owner = what->get_immediate_owner();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    Thingp top_owner;
    if (is_player()) {
        top_owner = this;
    } else {
        top_owner = get_top_owner();
    }

    if (top_owner) {
        if (what == top_owner->weapon_get()) {
            top_owner->unwield("moved into ether");
        }

        if (top_owner->is_player()) {
            top_owner->inventory_id_remove(what);
        }
    } else {
        err("has no top owner");
    }

    what->remove_owner();

    monstp->carrying.remove(what->id);

    log("dropped %s", what->to_string().c_str());

    return true;
}

bool Thing::drop (Thingp what)
{_
    return drop(what, nullptr);
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
