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
    //
    // Don't try to pick up goblins carrying gold
    //
    if (!it->is_collectable()) {
        dbg2("Is not worth collecting: %s", it->to_string().c_str());
        return -1;
    }

    //
    // I'd need to implement this support :)
    //
    if (game->robot_mode) {
        if (it->is_bag()) {
            dbg2("Is not worth collecting: %s", it->to_string().c_str());
            return -1;
        }
    }

    //
    // Don't pick up things we dropped
    //
    if (game->tick_current < it->get_tick_last_dropped() + 1) {
        dbg2("Is not worth collecting (dropped location): %s", it->to_string().c_str());
        return -1;
    }

    *would_need_to_drop = nullptr;

    int value = get_item_value(it);
    if (value < 0) {
        dbg2("Is not worth collecting (no value): %s", it->to_string().c_str());
        return value;
    }

    //
    // If this is a weapon, is it better than the worst carried weapon?
    //
    if (it->is_weapon()) {
        Thingp worst_weapon = nullptr;
        if (value > get_carried_weapon_least_value(&worst_weapon)){
            if (it->is_bag_item()) {
                if (bag_add_test(it)) {
                    //
                    // We can carry this weapon.
                    //
                    if (get_carried_weapon_count() > 1) {
                        //
                        // Carrying too many weapons? Drop the worst.
                        //
                        *would_need_to_drop = worst_weapon;
                    }
                } else {
                    //
                    // No space. Try dropping the worst weapon.
                    //
                    if (!worst_weapon) {
                        //
                        // If there is no worst weapon, then ignore
                        //
                        return false;
                    } else if (value <= get_item_value(worst_weapon)) {
                        //
                        // If this is worse than the worst weapon then no way
                        // collect this!
                        //
                        return false;
                    }
                    *would_need_to_drop = worst_weapon;
                }
            }
        }
    }

    //
    // If this is a wand, is it better than the worst carried wand?
    //
    if (it->is_wand()) {
        Thingp worst_wand = nullptr;
        if (value > get_carried_wand_least_value(&worst_wand)){
            if (it->is_bag_item()) {
                if (bag_add_test(it)) {
                    //
                    // We can carry this wand.
                    //
                    if (get_carried_wand_count() > 4) {
                        //
                        // Carrying too many wands? Drop the worst.
                        //
                        *would_need_to_drop = worst_wand;
                    }
                } else {
                    //
                    // No space. Try dropping the worst wand.
                    //
                    if (!worst_wand) {
                        //
                        // If there is no worst wand, then ignore
                        //
                        return false;
                    } else if (value <= get_item_value(worst_wand)) {
                        //
                        // If this is worse than the worst wand then no way
                        // collect this!
                        //
                        return false;
                    }
                    *would_need_to_drop = worst_wand;
                }
            }
        }
    }

    //
    // If this is a food, is it better than the worst carried food?
    //
    if (it->is_food()) {
        Thingp worst_food = nullptr;
        if (value > get_carried_food_least_value(&worst_food)){
            if (it->is_bag_item()) {
                if (bag_add_test(it)) {
                    //
                    // We can carry this food.
                    //
                } else {
                    //
                    // No space. Try dropping the worst food.
                    //
                    if (!worst_food) {
                        //
                        // If there is no worst food, then ignore
                        //
                        return false;
                    } else if (value <= get_item_value(worst_food)) {
                        //
                        // If this is worse than the worst food then no way
                        // collect this!
                        //
                        return false;
                    }
                    *would_need_to_drop = worst_food;
                }
            }
        }
    }

    return value;
}

int Thing::worth_collecting (Thingp it)
{_
    Thingp would_need_to_drop;
    return worth_collecting (it, &would_need_to_drop);
}
