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

bool Thing::possible_to_attack (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (!it->is_attackable()) {
        return (false);
    }

    if (is_alive_monst()) {
        if (me->is_meat_eater()) {
            if (it->is_made_of_meat() || it->is_blood()) {
                dbg("possible attack %s", itp->to_string().c_str());
                return (true);
            }
        }
    } else if (is_player()) {
        if (itp->is_monst()) {
            dbg("possible attack %s", itp->to_string().c_str());
            return (true);
        }
    }
    if (me->is_fire() || me->is_lava()) {
        if (it->is_combustible()) {
            if (!it->is_fire() && !it->is_lava()) {
                dbg("possible attack %s", itp->to_string().c_str());
                return (true);
            }
        }
    }

    return (false);
}

bool Thing::will_avoid (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_made_of_meat()) {
        if (it->is_meat_eater()) {
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

    return (false);
}
