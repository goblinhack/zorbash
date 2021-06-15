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
    dbg("place");

    level->thing_new(what, fpoint(p.x, p.y));

    //
    // Check if we are newly spawned over a chasm
    // Or if something we spawned at needs to react to us
    //
    location_check_forced_all_things_at();

    return true;
}
