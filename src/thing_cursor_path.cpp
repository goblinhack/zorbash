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
        if (move_no_shove(future_pos)) {
            return (true);
        }
    }
    return false;
}

void Thing::cursor_path_pop_first_move (void)
{_
    auto cursor = level->cursor;

    if (game->cursor_move_path.size()) {
        //
        // A path to the target exists.
        //
        new_monst();
        monstp->move_path = game->cursor_move_path;
        game->cursor_move_path.clear();
        if (cursor_path_pop_next_and_move()) {
            if (!game->cursor_move_path.size()) {
                level->cursor_path_create();
            }
            return;
        }
    }

    //
    // A path to the target does not exist. Jump?
    //
    point future_pos = make_point(cursor->mid_at.x,
                                  cursor->mid_at.y);

    //
    // If adjacent, try to move there. There may be no path
    // because perhaps a monster just moved but now we can
    // step there.
    //
    if ((fabs(future_pos.x - mid_at.x) <= 1) &&
        (fabs(future_pos.y - mid_at.y) <= 1)) {
        log("target is adjacent, attack or move to %f,%F",
            cursor->mid_at.x, cursor->mid_at.y);
        attack(cursor->mid_at);
        level->cursor_path_create();
        return;
    }

    //
    // If not adjacent, try and jump.
    //
    if (try_to_jump(future_pos)) {
        game->tick_begin("player tried to jump");
        return;
    }

    game->tick_begin("player move popped off cursor path");
}

void Thing::cursor_path_stop (void)
{_
    new_monst();
    monstp->move_path.clear();
}
