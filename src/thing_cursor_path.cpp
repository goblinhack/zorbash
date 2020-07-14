//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_wid_console.h"
#include "my_sdl.h"
#include "my_ascii.h"
#include "my_wid.h"
#include "my_thing.h"
#include "my_dmap.h"

bool Thing::cursor_path_pop_next_and_move (void)
{_
    if (monstp && monstp->move_path.size()) {
        auto to = monstp->move_path[0];
        auto future_pos = fpoint(to.x, to.y);
        FOR_ALL_CURSOR_PATH_THINGS(level, t, to.x, to.y) {
            t->dead("end of life");
        } FOR_ALL_THINGS_END()
        monstp->move_path.erase(monstp->move_path.begin());
        if (!move_no_shove(future_pos)) {
            cursor_path_stop();
            return (false);
        } else {
            return (true);
        }
    } else {
        return (false);
    }
}

void Thing::cursor_path_pop_first_move (void)
{_
    if (game->cursor_move_path.size()) {
        //
        // A path to the target exists.
        //
        new_monst();
        monstp->move_path = game->cursor_move_path;
        game->cursor_move_path.clear();
        cursor_path_pop_next_and_move();
    } else if (level->cursor) {
#if 0
        level->cursor_path_create();
        if (game->cursor_move_path.size()) {
            //
            // A path to the target exists.
            //
            new_monst();
            monstp->move_path = game->cursor_move_path;
            game->cursor_move_path.clear();
            cursor_path_pop_next_and_move();
        } else 
#endif
        if (level->cursor) {
            //
            // A path to the target does not exist. Jump?
            //
            point p = make_point(level->cursor->mid_at.x,
                                 level->cursor->mid_at.y);
            if (try_to_jump(p)) {
                game->tick_begin();
            }
        }
    }
}

void Thing::cursor_path_stop (void)
{_
    new_monst();
    monstp->move_path.clear();
}
