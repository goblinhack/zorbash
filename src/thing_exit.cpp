//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

bool Thing::open_exit (Thingp it)
{_
    if (!it->is_exit()) {
        return false;
    }

    game->current_level += point3d(0, 0, 1);
    game->init_levels();
#if 0
    for (const auto& item : monstp->carrying) {
        auto k = level->thing_find(item);
        if (k->is_key()) {
            used(k, it);
            it->detach();
            it->is_open = true;
            it->attach();
            MINICON("The door opens");
            if (get_light_count()) {
                update_light();
            }
            return true;
        }
    }
#endif
    MINICON("You bravely descend");
    return true;
}
