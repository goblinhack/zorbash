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

void Thing::level_enter (void)
{_
    auto result = level->all_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("Failed to insert into thing map");
    }

    if (is_active()) {
        auto result = level->all_active_things.insert(std::pair(id, this));
        if (result.second == false) {
            err("Failed to insert into active thing map");
        }
    }

    //
    // If this is the player create a new cursor for us.
    // If this is something else, do not, else the cursor winds up
    // following whatever fell in.
    //
    if (is_player()) {
        if (!level->cursor) {
            if (!is_cursor()) {
                level->cursor = level->thing_new("cursor", mid_at);
                level->cursor->hide();
            }
        }

        //
        // Flush the persistent light map
        // 
        blit_fbo_bind(FBO_FULLMAP_LIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        level->_is_lit = {};
    }
    level_push();

    if (is_player() || is_monst()) {
        set_where_i_dropped_an_item_last(point(-1, -1));
        set_where_i_failed_to_collect_last(point(-1, -1));
    }

    //
    // Make sure the light is refreshed.
    //
    if (is_player()) {
        update_light();
    }

    //
    // Blit location is now invalid
    //
    is_blitted = false;

    //
    // Can be shown on screen again.
    //
    is_changing_level             = false;
    is_waiting_to_ascend_dungeon  = false;
    is_waiting_to_descend_sewer   = false;
    is_waiting_to_descend_dungeon = false;
    is_waiting_to_ascend_sewer    = false;
    is_waiting_to_fall            = false;

    game->update_rightbar = true;
}
