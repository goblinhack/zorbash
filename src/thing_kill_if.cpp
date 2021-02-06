//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::kill_if (const std::string& what, const point &p)
{_
    //
    // Don't destroy the floor under critical items
    //
    if ((what == "is_floor") || (what == "is_corridor")) {
        FOR_ALL_THINGS(level, t, p.x, p.y) {
            if (t->is_critical_to_level()) {
                return true;
            }
        } FOR_ALL_THINGS_END()
    }

    FOR_ALL_THINGS(level, t, p.x, p.y) {
        if (t->match(what)) {
            t->dead(this, "killed");
        }
    } FOR_ALL_THINGS_END()

    return true;
}
