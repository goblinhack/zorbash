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

    FOR_ALL_THING_GROUPS(group) {
        auto f = level->all_things[group].find(id);
        if (f != level->all_things[group].end()) {
            level->all_things[group].erase(f);
        }
    }

    if (is_interesting()) {
        //
        // If doing a walk, we must be careful and cannot modify the map
        //
        int group = get_group();
        if (level->all_things_of_interest_walk_in_progress) {
            level->all_things_of_interest_pending_add[group].erase(id);
            level->all_things_of_interest_pending_remove[group].insert(std::pair(id, this));
        } else {
            level->all_things_of_interest[group].erase(id);
        }
    }

    if (gfx_animated()) {
        //
        // If doing a walk, we must be careful and cannot modify the map
        //
        int group = get_group();
        if (level->all_animated_things_walk_in_progress) {
            level->all_animated_things_pending_add[group].erase(id);
            level->all_animated_things_pending_remove[group].insert(std::pair(id, this));
        } else {
            level->all_animated_things[group].erase(id);
        }
    }

    game->request_update_rightbar = true;
}
