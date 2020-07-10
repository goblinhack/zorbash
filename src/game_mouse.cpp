//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_wid.h"

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
    if (wid_find_under_mouse()) {
        return (false);
    }

    if (!game || !game->started) {
        return (false);
    }

    auto level = game->level;
    if (!level) {
        return (false);
    }

    auto player = level->player;
    if (!player) {
        return (false);
    }

    if (player->is_dead) {
        return true;
    }

    //
    // If mid air, we're done. Let other things move.
    //
    if (player->is_jumping) {
        return true;
    }

    player->log("mouse move");

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    player->cursor_path_pop_first_move();
    if (player->is_jumping) {
        return true;
    }

    //
    // Have we moved close enough to attack?
    //
    if (level->cursor) {_
        if ((std::abs(player->mid_at.x - level->cursor->mid_at.x) <= 1) &&
            (std::abs(player->mid_at.y - level->cursor->mid_at.y) <= 1)) {
            int x = level->cursor->mid_at.x;
            int y = level->cursor->mid_at.y;
            FOR_ALL_INTERESTING_THINGS(level, t, x, y) {
                if (t->is_monst()) {
                    if (t != level->player) {
                        level->player->attack(level->cursor->mid_at);
                        return (true);
                    }
                }
            }
            FOR_ALL_THINGS_END()
        }
    }
    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    if (wid_find_under_mouse()) {
        return (false);
    }

    return (false);
}
