//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_wid_skillbox.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::skill_add (Thingp it)
{_
    log("Try to add skill %s", it->to_string().c_str());
_
    if (!monstp) {
        log("No; not a monst");
        return false;
    }

    auto existing_owner = it->get_immediate_owner();
    if (existing_owner) {
        if (existing_owner == this) {
            log("No; same owner");
            return false;
        }
        existing_owner->drop(it);
    }

    for (const auto& item : monstp->skills) {
        if (item == it->id) {
            log("No; already carried");
            return false;
        }
    }

    if (is_player()) {
        if (!skillbox_id_insert(it)) {
            log("No; no space in skillbox");
            return false;
        }
    }

    monstp->skills.push_front(it->id);
    it->set_owner(this);
    it->hide();

    log("Add skill %s", it->to_string().c_str());

    if (is_player()) {
        wid_skillbox_init();
    }

    return true;
}

bool Thing::skill_remove (Thingp what)
{_
    log("Removing skill %s", what->to_string().c_str());
_
    auto existing_owner = what->get_immediate_owner();
    if (existing_owner != this) {
        err("Attempt to remove skill %s which is not owned", 
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
        if (top_owner->is_player()) {
            top_owner->skillbox_id_remove(what);
        }
    }

    log("Update bag with drop of: %s", what->to_string().c_str());
    bag_remove(what);
    while (bag_compress()) { }

    what->remove_owner();
    monstp->skills.remove(what->id);
    game->request_remake_skillbox = true;

    log("Dropped %s into the ether", what->to_string().c_str());

    return true;
}

void Thing::skill_remove_all (void)
{_
    if (!monstp) {
        return;
    }

    while (!monstp->skills.empty()) {
        auto id = *monstp->skills.begin();
        auto t = level->thing_find(id);
        if (!t) {
            return;
        }
        skill_remove(t);
    }
}

bool Thing::skill_use (Thingp it)
{_
    log("Try to use skill %s", it->to_string().c_str());

    auto tp = it->tp();
    TOPCON("%s", tp->text_on_use().c_str());
_
    if (!monstp) {
        log("No; not a monst");
        return false;
    }

    return true;
}
