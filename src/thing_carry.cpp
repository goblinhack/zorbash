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
    if (!it) {
        err("No thing to carry");
        return false;
    }

    dbg("Try to carry %s", it->to_string().c_str());

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
        dbg("Monsts always carry items");
    } else if (it->is_bag_item_container() && bag_add(it)) {
        //
        // Bag being carried
        //
        dbg("Added bag to bag at %d,%d",
            it->monstp->bag_position.x, it->monstp->bag_position.y);
    } else if (!it->is_bag_item()) {
        //
        // A key for example, does not go in a bag
        //
        dbg("Non item not added to bag");
    } else if (bag_add(it)) {
        dbg("Added to bag at %d,%d",
            it->monstp->bag_position.x, it->monstp->bag_position.y);
    } else {
        dbg("No; cannot store in a bag");
        set_where_i_failed_to_collect_last(make_point(it->mid_at));

        if (is_player()) {
            TOPCON("%%fg=red$No space to carry %s.%%fg=reset$", it->text_the().c_str());
        }
        return false;
    }

    auto existing_owner = it->get_immediate_owner();
    if (existing_owner) {
        if (existing_owner == this) {
            dbg("No; same owner");
            return false;
        }

        //
        // Can't use drop as that can cause things to interact with
        // the level. If this is moving between bags, this is safer.
        //
        dbg("Drop from existing owner");
        existing_owner->drop_into_ether(it);
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

        if (it->is_collected_as_gold()) {
            return true;
        }

        if (it->is_collect_as_keys()) {
            return true;
        }
    }

    monstp->carrying.push_front(it->id);
    it->set_owner(this);
    it->hide();

    if (game->state == Game::STATE_MOVING_ITEMS) {
        //
        // Avoid dup message
        //
    } else {
        if (is_player()) {
            if (!level->is_starting) {
                TOPCON("You carry %s.", it->text_the().c_str());
            }
        }
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

    //
    // Auto carry items in the bag? like keys?
    //
    if (it->is_bag_item_container()) {
        auto carrying_copy = it->monstp->carrying;
        for (const auto& item : carrying_copy) {
            auto t = level->thing_find(item.id);
            if (t) {
                log("Carrying %s that contains: %s",
                    it->to_string().c_str(),
                    t->to_string().c_str());
            }
        }

        for (const auto& item : carrying_copy) {
            auto t = level->thing_find(item.id);
            if (t) {
                if (!t->is_bag_item()) {
                    if (!carry(t)) {
                        err("Could not auto carry %s's non item: %s",
                            it->to_string().c_str(),
                            t->to_string().c_str());
                    }
                }
            }
        }
    }

    return true;
}

bool Thing::try_to_carry (Thingp it)
{_
    dbg("Try to carry: %s", it->to_string().c_str());
    return carry(it);
}

std::list<Thingp> Thing::anything_to_carry_at (fpoint at)
{_
    std::list<Thingp> items;

    FOR_ALL_THINGS(level, t, at.x, at.y) {
        if (t->is_hidden) {
            continue;
        }

        if (!t->is_collectable()) {
            continue;
        }

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

        dbg("Potential item to carry: %s", t->to_string().c_str());
        items.push_back(t);

        if (t->is_bag_item_container()) {
            //
            // Open chests etc...
            //
            open(t);

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

std::list<Thingp> Thing::anything_to_carry (void)
{_
    return anything_to_carry_at(mid_at);
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
