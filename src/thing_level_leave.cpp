//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_sdl.h"
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

    if (is_interesting()) {
        //
        // If doing a walk, we must be careful and cannot modify the map
        //
        if (level->all_interesting_things_walk_in_progress) {
            level->pending_add_all_interesting_things.erase(id);
            level->pending_remove_all_interesting_things.insert(std::pair(id, this));
        } else {
            level->all_interesting_things.erase(id);
        }
    }

    game->request_update_rightbar = true;
}
