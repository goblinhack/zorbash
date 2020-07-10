//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

bool Thing::will_avoid (point p) const
{_
    if (level->is_water(p)) {
        if (is_water_hater()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (is_acid_hater()) {
            return true;
        }
    }

    if (!is_floating()) {
        if (level->is_chasm(p)) {
            return true;
        }
    }

    if (level->is_corpse(p)) {
        if (level->is_monst(p) > 1) {
            return true;
        }
    } else {
        if (level->is_monst(p) > 0) {
            return true;
        }
    }

    if (level->is_door(p)                            ||
        level->is_secret_door(p)                     ||
        level->is_generator(p)                       ||
        level->is_movement_blocking(p)               ||
        level->is_rock(p)                            ||
        level->is_wall(p)) {
        return true;
    }

    int heat = level->heatmap(p);
    if (heat > 1) {
        if (is_fire_hater()) {
            return true;
        }
    }

    return false;
}

bool Thing::will_avoid (const Thingp itp) const
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat()) {
        if (it->is_meat_eater()) {
            return (true);
        }
    }
    if (me->is_treasure()) {
        if (it->is_treasure_eater()) {
            return (true);
        }
    }
    if (me->is_potion()) {
        if (it->is_potion_eater()) {
            return (true);
        }
    }
    if (me->is_slime_baby()) {
        //
        // But allow baby slimes to attack each other!
        //
        if (it->is_slime_parent()) {
            return (true);
        }
    }
    if (me->is_acid_hater()) {
        if (it->is_acid()) {
            return (true);
        }
    }
    if (me->is_fire_hater()) {
        if (it->is_fire()) {
            return (true);
        }
        if (it->is_lava()) {
            return (true);
        }
    }
    if (me->is_water_hater()) {
        if (it->is_water()) {
            return (true);
        }
    }
    return (false);
}

bool Thing::will_eat (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat_eater()) {
        if (it->is_meat() || it->is_blood()) {
            return (true);
        }
    }
    if (me->is_treasure_eater()) {
        if (it->is_treasure()) {
            return (true);
        }
    }
    if (me->is_potion_eater()) {
        if (it->is_potion()) {
            return (true);
        }
    }
    if (me->is_slime_baby_eater()) {
        if (it->is_slime_baby()) {
            return (true);
        }
    }
    if (is_player()) {
        if (it->is_collectable()) {
            return (true);
        }
    }
    return (false);
}
