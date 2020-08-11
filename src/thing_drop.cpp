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

    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to drop %s which is not carried", 
            what->to_string().c_str());
        return false;
    }

    if (is_player()) {
        if (target) {
            if (!actionbar_id_remove(what, target)) {
                err("failed to drop %s from actionbar", 
                    what->to_string().c_str());
                return false;
            }
        } else {
            if (!actionbar_id_remove(what)) {
                err("failed to drop %s from actionbar", 
                    what->to_string().c_str());
                return false;
            }
        }
    }

    what->hooks_remove();
    what->remove_owner();
    what->visible();
    what->move_to_immediately(mid_at);

    monstp->carrying.remove(what->id);

    //
    // Prevent too soon re-carry
    //
    what->set_tick_dropped(game->tick_current);

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
