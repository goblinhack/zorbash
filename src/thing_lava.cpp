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
            static auto lava = tp_find("lava1");
            MINICON("%%fg=red$The %s %s!%%fg=reset$",
                    lava->text_name().c_str(),
                    lava->text_hits().c_str());
        }
    }
}
