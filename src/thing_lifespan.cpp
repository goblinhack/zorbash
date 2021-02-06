//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::lifespan_tick (void)
{_
    if (!get_lifespan()) {
        return;
    }

    decr_lifespan();

    if (!get_lifespan()) {
        dead("ran out of life");
        return;
    }
}
