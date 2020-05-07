//
// Copyright goblinhack@gmail.com
// See the README file for license info.
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
            t->dead("eol");
        } FOR_ALL_THINGS_END()
        monstp->move_path.erase(monstp->move_path.begin());
        return (move(future_pos));
    } else {
        return (false);
    }
}

void Thing::cursor_path_pop_first_move (void)
{_
    if (game->cursor_move_path.size()) {
        new_monst();
        monstp->move_path = game->cursor_move_path;
        game->cursor_move_path.clear();
        cursor_path_pop_next_and_move();
    }
}

void Thing::cursor_path_stop (void)
{_
    new_monst();
    monstp->move_path.clear();
}
