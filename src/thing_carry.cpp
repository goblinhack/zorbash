//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_wid_inventory.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::carry (Thingp it)
{_
    dbg("Try to carry %s", it->to_string().c_str());
_
    if (!monstp) {
        dbg("No; not a monst");
        return false;
    }

    if (game->state == Game::STATE_COLLECTING_ITEMS) {
        //
        // Avoid carry checks
        //
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        //
        // Avoid carry checks
        //
    } else {
        //
        // Stop fast loops in collecting things
        //
        if (particle_anim_exists()) {
            dbg("No; particle anim exists");
            return false;
        }

        if (get_where_i_dropped_an_item_last() == make_point(mid_at)) {
            dbg("No; was dropped here recently");
            return false;
        }
    }

    if (is_monst()) {
        //
        // Always carry
        //
    } else if (bag_add(it)) {
        dbg("Added to bag at %d,%d", 
            it->monstp->bag_position.x, it->monstp->bag_position.y);
    } else {
        dbg("No; cannot store in a bag");
        set_where_i_failed_to_collect_last(make_point(it->mid_at));

        if (is_player()) {
            TOPCON("No space to carry %s.", it->text_the().c_str());
        }
        return false;
    }

    auto existing_owner = it->get_immediate_owner();
    if (existing_owner) {
        if (existing_owner == this) {
            dbg("No; same owner");
            return false;
        }
        existing_owner->drop(it);
    }

    for (const auto& item : monstp->carrying) {
        if (item == it->id) {
            dbg("No; already carried");
            return false;
        }
    }

    if (is_player()) {
        if (!inventory_id_insert(it)) {
            dbg("No; no space in inventory");
            return false;
        }
    }

    monstp->carrying.push_front(it->id);
    it->set_owner(this);
    it->hide();

    if (is_player()) {
        TOPCON("You carry %s.", it->text_the().c_str());
    }

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
    dbg("Try to carry: %s", it->to_string().c_str());
    return carry(it);
}

std::list<Thingp> Thing::anything_to_carry (void)
{_
    std::list<Thingp> items;

    FOR_ALL_THINGS(level, t, mid_at.x, mid_at.y) {
        if (t->is_dead) {
            dbg("Potential item to carry, no, is dead: %s",
                t->to_string().c_str());
            continue;
        }

        if (t->get_immediate_owner()) {
            dbg("Potential item to carry, no, has owner: %s",
                t->to_string().c_str());
            continue;
        }

        if (!t->is_collectable()) {
            dbg("Potential item to carry, no, not collectable: %s",
                t->to_string().c_str());
            continue;
        }

        if (t->is_hidden) {
            dbg("Potential item to carry, no, is hidden: %s",
                t->to_string().c_str());
            continue;
        }

        dbg("Potential item to carry: %s", t->to_string().c_str());
        items.push_back(t);

        if (t->is_item_container()) {
            for (const auto& item : t->monstp->carrying) {
                auto t = level->thing_find(item.id);
                if (t) {
                    items.push_back(t);
                }
            }
        }
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

        if (t->is_auto_collect_item()) {
            carry(t);
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
