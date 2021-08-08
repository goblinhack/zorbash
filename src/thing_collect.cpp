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
#include "my_thing_template.h"
#include "my_sprintf.h"

//
// Return a score, higher is better for value to you
//
int Thing::worth_collecting (Thingp it)
{_
    if (it->is_treasure_type()) {
        int gold_value = it->get_gold_value();

        if (it->is_collected_as_gold()) {
            return gold_value;
        }

        if (it->is_bag_item()) {
            if (bag_add_test(it)) {
                return gold_value;
            }
        }
    }

    if (it->is_food()) {
        if (it->is_bag_item()) {
            if (bag_add_test(it)) {
                return it->get_nutrition();
            }
        }
    }

    return 0;
}
