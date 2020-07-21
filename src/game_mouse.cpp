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
    if (wid_find_under_mouse_when_scrolling()) {
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
    // If hovering over a double click thing then don't jump in unless
    // the user really means it.
    //
    if (!wid_mouse_double_click) {
        if (level->cursor) {_
            auto to = level->cursor->mid_at;
            FOR_ALL_THINGS(level, t, to.x, to.y) {
                if (t->is_cursor_can_hover_over_but_needs_double_click()) {
                    return true;
                }
            } FOR_ALL_THINGS_END()
        }
    }

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
                if (t == level->player) {
                    continue;
                }
                if (t->is_food() || t->is_potion()) {
                    player->log("close enough to collect");
                    player->carry(t);
                    return (true);
                } else if (t->is_monst() || t->is_generator()) {
                    player->log("close enough to attack");
                    player->attack(level->cursor->mid_at);
                    return (true);
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
    return (false);
}
