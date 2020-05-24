//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::lava_tick (void)
{_
    if (!is_combustible()) {
        return;
    }

    if (level->is_lava(mid_at.x, mid_at.y)) {
        set_on_fire();
        if (is_player()) {
            MINICON("%%fg=red$The lava burns!%%fg=reset$");
        }
    }
}
