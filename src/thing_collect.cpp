//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_sprintf.h"

//
// Return a score, higher is better for perceived value to you
//
int Thing::worth_collecting (Thingp it, Thingp *would_need_to_drop)
{_
    dbg("Is %s worth collecting?", it->to_string().c_str());
_
    //
    // Don't try to pick up goblins carrying gold
    //
    if (!it->is_collectable()) {
        dbg("Worth collecting? no, not collectable: %s", it->to_string().c_str());
        return -1;
    }

    //
    // I'd need to implement this support :)
    //
    if (game->robot_mode) {
        if (it->is_bag()) {
            dbg("Worth collecting? no, bag: %s", it->to_string().c_str());
            return -1;
        }
    }

    //
    // Don't pick up things we dropped
    //
    if (game->tick_current < it->get_tick_last_dropped() + 1) {
        dbg("Worth collecting? no, just dropped: %s", it->to_string().c_str());
        return -1;
    }

    *would_need_to_drop = nullptr;

    int value = get_item_value(it);
    if (value < 0) {
        dbg("Worth collecting? no, worthless: %s", it->to_string().c_str());
        return -1;
    }


    //
    // If this is a weapon, and we can carry it, do so. If we are out of space,
    // then is it better than the worst weapon? If so, try to drop that.
    // Finally, if we have too many weapons, after adding, drop the worst.
    //
    if (it->is_weapon()) {
        Thingp worst_weapon = nullptr;
        auto worst_weapon_value = get_carried_weapon_least_value(&worst_weapon);
        if (worst_weapon) {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    if (value > worst_weapon_value) {
                        *would_need_to_drop = worst_weapon;
                        dbg("Worth collecting? no space for %s, would need to drop %s",
                            it->to_string().c_str(),
                            worst_weapon->to_string().c_str());
                        return value;
                    }
                    dbg("Worth collecting? no space for %s, worst weapon is %s",
                        it->to_string().c_str(),
                        worst_weapon->to_string().c_str());
                    return -1;
                } else {
                    if (value > worst_weapon_value) {
                        if (get_carried_weapon_count() > 1) {
                            *would_need_to_drop = worst_weapon;
                            dbg("Worth collecting? no space for %s, too many weapons, would need to drop %s",
                                it->to_string().c_str(),
                                worst_weapon->to_string().c_str());
                        }
                    }
                    return value;
                }
            }
        } else {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    dbg("Worth collecting? no, no space: %s", it->to_string().c_str());
                    return -1;
                }
            }
            return value;
        }
    }

    if (it->is_wand()) {
        Thingp worst_wand = nullptr;
        auto worst_wand_value = get_carried_wand_least_value(&worst_wand);
        if (worst_wand) {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    if (value > worst_wand_value) {
                        *would_need_to_drop = worst_wand;
                        dbg("Worth collecting? no space for %s, would need to drop %s",
                            it->to_string().c_str(),
                            worst_wand->to_string().c_str());
                        return value;
                    }
                    dbg("Worth collecting? no space for %s, worst wand is %s",
                        it->to_string().c_str(),
                        worst_wand->to_string().c_str());
                    return -1;
                } else {
                    if (value > worst_wand_value) {
                        if (get_carried_wand_count() > 3) {
                            *would_need_to_drop = worst_wand;
                            dbg("Worth collecting? no space for %s, too many wands, would need to drop %s",
                                it->to_string().c_str(),
                                worst_wand->to_string().c_str());
                        }
                    }
                    return value;
                }
            }
        } else {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    dbg("Worth collecting? no, no space: %s", it->to_string().c_str());
                    return -1;
                }
            }
            return value;
        }
    }

    if (it->is_food()) {
        Thingp worst_food = nullptr;
        auto worst_food_value = get_carried_food_least_value(&worst_food);
        if (worst_food) {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    if (value > worst_food_value) {
                        *would_need_to_drop = worst_food;
                        dbg("Worth collecting? no space for %s, would need to drop %s",
                            it->to_string().c_str(),
                            worst_food->to_string().c_str());
                        return value;
                    }
                    dbg("Worth collecting? no space for %s, worst food is %s",
                        it->to_string().c_str(),
                        worst_food->to_string().c_str());
                    return -1;
                } else {
                    if (value > worst_food_value) {
                        if (get_carried_food_count() > 4) {
                            *would_need_to_drop = worst_food;
                            dbg("Worth collecting? no space for %s, too many foods, would need to drop %s",
                                it->to_string().c_str(),
                                worst_food->to_string().c_str());
                        }
                    }
                    return value;
                }
            }
        } else {
            if (it->is_bag_item()) {
                if (!bag_add_test(it)) {
                    dbg("Worth collecting? no, no space: %s", it->to_string().c_str());
                    return -1;
                }
            }
            return value;
        }
    }

    if (it->is_bag_item()) {
        if (!bag_add_test(it)) {
            dbg("Worth collecting? no, no space: %s", it->to_string().c_str());
            return -1;
        }
    }

    dbg("Worth collecting? yes has value %d: %s", value, it->to_string().c_str());

    return value;
}

int Thing::worth_collecting (Thingp it)
{_
    Thingp would_need_to_drop;
    return worth_collecting (it, &would_need_to_drop);
}
