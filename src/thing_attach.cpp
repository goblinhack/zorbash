//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

void Thing::attach (void)
{_
    detach();

    world->put_thing((int)mid_at.x, (int)mid_at.y, id);

    if (is_active()) {
        update_interpolated_position();
    }

    is_attached = true;
    last_attached = mid_at;
//log("attached at %d %d %d", (int)last_attached.x, (int)last_attached.y,
//depth);
}

void Thing::detach (void)
{_
    if (!is_attached) {
        return;
    }
    is_attached = false;

//log("detach from %d %d %d", (int)last_attached.x, (int)last_attached.y,
//depth);

    world->remove_thing((int)last_attached.x, (int)last_attached.y, id);
}
