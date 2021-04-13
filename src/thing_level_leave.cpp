//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"

void Thing::level_leave (void)
{_
    level_pop();

    //
    // Remove minions if they stay behind on the old level
    //
    unleash_minions();
    unleash_spawners_things();

    {
        auto it = get_immediate_minion_owner();
        if (it) {
            remove_minion_owner();
        }
    }

    {
        auto it = get_immediate_spawned_owner();
        if (it) {
            remove_spawner_owner();
        }
    }

    {
        auto f = level->all_things.find(id);
        if (f != level->all_things.end()) {
            level->all_things.erase(f);
        }
    }

    if (is_active()) {
        auto f = level->all_active_things.find(id);
        if (f != level->all_active_things.end()) {
            level->all_active_things.erase(f);
        }
    }

    game->request_update_rightbar = true;
}
