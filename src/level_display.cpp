//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_level.h"
#include "my_thing.h"

void Level::display (void)
{_
    if (map_changed) {
        static int last_done;
        if (time_have_x_secs_passed_since(1, last_done)) {
            map_changed = false;
            last_done = time_get_time_ms_cached();
            update_map();
        }
    }

    thing_render_all();
}
