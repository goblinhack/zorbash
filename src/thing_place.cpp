//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::place (const std::string& what, const point &p)
{_
    log("place");

    level->thing_new(what, fpoint(p.x, p.y));

    //
    // Just in case something is now on top of a chasm or lava
    //
    log("do location checks");
    FOR_ALL_THINGS(level, t, p.x, p.y) {
        t->location_check();
    } FOR_ALL_THINGS_END()

    return true;
}
