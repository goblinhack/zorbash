//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::kill_if (const std::string& what, const point &p)
{_
    FOR_ALL_THINGS(level, t, p.x, p.y) {
        if (t->match(what)) {
            t->dead(this, "killed");
        }
    } FOR_ALL_THINGS_END()

    return true;
}
