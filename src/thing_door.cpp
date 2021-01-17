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
    if (is_on_fire()) {
        if (!it->is_on_fire()) {
            if (is_player()) {
                MINICON("The door is ablaze!");
            }
            it->set_on_fire("opened flaming door");
        }
    }

    if (!it->is_door()) {
        return false;
    }

    if (it->is_open) {
        return false;
    }

    if (it->is_dead) {
        return false;
    }

    if (get_keys()) {
        decr_keys();
        it->log("Open");
        it->level_pop();
        it->is_open = true;
        it->level_push();

        if (is_player()) {
            MINICON("The door creaks open");
        }
        update_light();
        return true;
    }

    if (is_player()) {
        MINICON("You need a key");
    }

    return false;
}
