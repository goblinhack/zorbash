//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

bool Thing::will_avoid (const Thingp itp)
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
    if (me->is_slime_baby()) {
        if (it->is_slime_parent()) {
            return (true);
        }
    }
    if (me->is_slime_baby()) {
        if (it->is_slime_baby()) {
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
        if (it->is_treasure() || it->is_blood()) {
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
