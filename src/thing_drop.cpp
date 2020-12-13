//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"

bool Thing::drop (Thingp what, Thingp target)
{_
    if (target) {
        log("drop %s at %s", what->to_string().c_str(),
            target->to_string().c_str());
    } else {
        log("drop %s", what->to_string().c_str());
    }

    auto existing_owner = what->get_owner();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    if (is_player()) {
        if (target) {
            if (!inventory_id_remove(what, target)) {
                err("failed to drop %s from inventory", 
                    what->to_string().c_str());
                return false;
            }
        } else {
            if (!inventory_id_remove(what)) {
                err("failed to drop %s from inventory", 
                    what->to_string().c_str());
                return false;
            }
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
