//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
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

bool Thing::is_carrying_treasure (void)
{_
    if (!monstp) {
        return false;
    }

    for (const auto& item : monstp->carrying) {
        auto t = level->thing_find(item.id);
        if (t->is_treasure()) {
            return true;
        }
        if (t->monstp && t->monstp->carrying.size()) {
            if (t->is_carrying_treasure()) {
                return true;
            }
        }
    }

    auto owner = owner_get();
    if (owner) {
        return owner->is_carrying_treasure();
    }

    return false;
}

std::vector<Thingp> Thing::get_treasure_list (void)
{
    std::vector<Thingp> tr;

    if (!monstp) {
        return tr;
    }

    for (const auto& item : monstp->carrying) {
        auto t = level->thing_find(item.id);

        if (t->monstp && t->monstp->carrying.size()) {
            auto tr2 = t->get_treasure_list();
            std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
        }

        if (t->is_treasure()) {
            tr.push_back(t);
        }
    }

    auto owner = owner_get();
    if (owner) {
        auto tr2 = owner->get_treasure_list();
        std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
    }

    return tr;
}

bool Thing::is_carrying_item (void)
{_
    if (!monstp) {
        return false;
    }

    if (monstp->carrying.size()){
        return true;
    }

    auto owner = owner_get();
    if (owner) {
        return owner->is_carrying_item();
    }

    return false;
}

std::vector<Thingp> Thing::get_item_list (void)
{
    std::vector<Thingp> tr;

    if (!monstp) {
        return tr;
    }

    for (const auto& item : monstp->carrying) {
        auto t = level->thing_find(item.id);

        if (t->monstp && t->monstp->carrying.size()) {
            auto tr2 = t->get_item_list();
            std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
        }

        if (t->is_item()) {
            tr.push_back(t);
        }
    }

    auto owner = owner_get();
    if (owner) {
        auto tr2 = owner->get_item_list();
        std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
    }

    return tr;
}
