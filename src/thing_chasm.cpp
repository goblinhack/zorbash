//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_globals.h"

void Thing::chasm_tick (void)
{_
    if (is_floating() || is_ethereal()) {
        if (is_player()) {
            log("Chasm tick: no is floating");
        }
        return;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        log("Over a chasm");
        fall(1, 750);
    }
}
