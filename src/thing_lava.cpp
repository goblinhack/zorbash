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

    if (level->is_lava(at.x, at.y)) {
        incr_on_fire_count();
        auto id = get_on_fire_anim_id();
        if (!id) {
            if (is_player()) {
                MINICON("%%fg=red$The lava burns!%%fg=reset$");
            }
            return;
        }
    }
}
