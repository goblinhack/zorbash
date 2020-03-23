//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::lifespan_tick (void)
{_
    if (!get_lifespan_count()) {
        return;
    }

    decr_lifespan_count();

    if (!get_lifespan_count()) {
        dead("ran out of life");
        return;
    }
}
