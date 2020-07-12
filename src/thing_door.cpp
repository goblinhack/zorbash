//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

bool Thing::open_door (Thingp it)
{_
    if (!it->is_door()) {
        return false;
    }

    if (it->is_open) {
        return false;
    }

    if (it->is_dead) {
        return false;
    }

    for (const auto& item : monstp->carrying) {
        auto k = level->thing_find(item);
        if (k->is_key()) {
            used(k, it);
            it->level_pop();
            it->is_open = true;
            it->level_push();
            MINICON("The door opens");
            if (get_light_count()) {
                update_light();
            }
            return true;
        }
    }
    MINICON("You need a key");
    return false;
}
