//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_wid_inventory.h"

bool Thing::carry (Thingp it)
{_
    log("try to carry %s", it->to_string().c_str());
_
    if (!monstp) {
        log("no; not a monst");
        return false;
    }

    if (game->moving_items) {
        //
        // Avoid carry checks
        //
    } else {
        //
        // Stop fast loops in collecting things
        //
        if (particle_anim_exists()) {
            log("no; particle anim exists");
            return false;
        }

        if (get_where_i_dropped_an_item_last() == make_point(mid_at)) {
            log("no; was dropped here recently");
            return false;
        }
    }

    if (!bag_add(it)) {
        log("no; cannot store");
        set_where_i_failed_to_collect_last(make_point(it->mid_at));

        if (is_player()) {
            MINICON("No space to carry %s", it->text_the().c_str());
        }
        return false;
    }

    if (is_player()) {
        if (!inventory_id_insert(it)) {
            log("no; no space in inventory");
            return false;
        }
    }

    auto existing_owner = it->get_immediate_owner();
    if (existing_owner) {
        if (existing_owner == this) {
            log("no; same owner");
            return false;
        }
        existing_owner->drop(it);
    }

    for (const auto& item : monstp->carrying) {
        if (item == it->id) {
            log("no; already carried");
            return false;
        }
    }

    monstp->carrying.push_front(it->id);
    it->set_owner(this);
    it->hide();

    log("yes; is now carrying %s", it->to_string().c_str());

    //
    // If we have no weapon, wield it
    //
    if (is_weapon_wielder()) {
        if (it->is_weapon() && !get_weapon_id()) {
            wield(it);
        }
    }

    if (is_player()) {
        wid_inventory_init();
    }

    return true;
}

bool Thing::try_to_carry (Thingp it)
{_
    log("try to carry: %s", it->to_string().c_str());
    return carry(it);
}

std::list<Thingp> Thing::anything_to_carry (void)
{
    std::list<Thingp> items;

    FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
        if (t->is_dead) {
            continue;
        }

        if (t->is_hidden) {
            continue;
        }

        if (t->get_immediate_owner()) {
            continue;
        }

        if (!t->is_collectable()) {
            continue;
        }

        log("potential item to carry: %s", t->to_string().c_str());
        items.push_back(t);
    } FOR_ALL_THINGS_END()

    return items;
}

bool Thing::check_anything_to_carry (void)
{
    FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
        if (t->is_dead) {
            continue;
        }

        if (t->is_hidden) {
            continue;
        }

        if (t->get_immediate_owner()) {
            continue;
        }

        if (!t->is_collectable()) {
            continue;
        }

        return true;
    } FOR_ALL_THINGS_END()

    return false;
}

void Thing::try_to_carry (const std::list<Thingp> &items)
{
    for (auto item : items) {
        try_to_carry(item);
    }
}
