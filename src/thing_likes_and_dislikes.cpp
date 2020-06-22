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

    if (me->is_made_of_meat()) {
        if (it->is_meat_eater()) {
            return (true);
        }
    }
    if (me->is_baby_slime()) {
        if (it->is_parent_slime()) {
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
        if (it->is_made_of_meat() || it->is_blood()) {
            return (true);
        }
    }
    if (me->is_baby_slime_eater()) {
        if (it->is_baby_slime()) {
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
