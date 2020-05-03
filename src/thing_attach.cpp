//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"

void Thing::attach (void)
{_
    detach();
    level->put_thing((int)mid_at.x, (int)mid_at.y, id);
    auto mx = (int16_t)(int)mid_at.x;
    auto my = (int16_t)(int)mid_at.y;
    is_attached = true;
    last_attached = spoint(mx, my);
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;
    level->remove_thing((int)last_attached.x, (int)last_attached.y, id);
}
