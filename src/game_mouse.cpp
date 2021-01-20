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
        return false;
    }

    if (wid_find_under_mouse()) {
        return false;
    }

    if (!game || !game->started) {
        return false;
    }

    auto level = game->level;
    if (!level) {
        return false;
    }

    auto player = level->player;
    if (!player) {
        return false;
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

    if (!level->cursor) {_
        return false;
    }

    if (game->state == Game::STATE_CHOOSING_TARGET) {
        player->log("Chosen target");
        auto what = game->request_to_throw_item;
        player->throw_at(what, level->cursor);
        return true;
    }

    player->log("Mouse move");

    //
    // Have we moved close enough to attack? Do this prior to checking for
    // double click so we can attack monsts sitting in lava
    //
    if ((std::abs(player->mid_at.x - level->cursor->mid_at.x) <= 1) &&
        (std::abs(player->mid_at.y - level->cursor->mid_at.y) <= 1)) {
        int x = level->cursor->mid_at.x;
        int y = level->cursor->mid_at.y;
        FOR_ALL_INTERESTING_THINGS(level, t, x, y) {
            if (t == level->player) {
                continue;
            }
            if (t->is_alive_monst() || t->is_generator()) {
                player->log("Close enough to attack");
                player->attack(level->cursor->mid_at);
                return true;
            }
        }
        FOR_ALL_THINGS_END()
    }

    //
    // If hovering over a double click thing then don't jump in unless
    // the user really means it.
    //
    if (!wid_mouse_double_click) {
        auto to = level->cursor->mid_at;
        FOR_ALL_THINGS(level, t, to.x, to.y) {
            if (t->is_cursor_can_hover_over_but_needs_double_click()) {
                player->log("Needs double click");
                return true;
            }
        } FOR_ALL_THINGS_END()
    }

    //
    // Have we moved close enough to collect? Do this after the double
    // click check so we do not try to collect things in lava.
    //
    if ((std::abs(player->mid_at.x - level->cursor->mid_at.x) <= 1) &&
        (std::abs(player->mid_at.y - level->cursor->mid_at.y) <= 1)) {
        int x = level->cursor->mid_at.x;
        int y = level->cursor->mid_at.y;
        FOR_ALL_INTERESTING_THINGS(level, t, x, y) {
            if (t == level->player) {
                continue;
            }
            if (t->is_food() || t->is_potion()) {
                player->log("Close enough to collect");
                player->try_to_carry(t);
                return true;
            }
        }
        FOR_ALL_THINGS_END()
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    if (player->cursor_path_pop_first_move()) {
        return true;
    }

    return false;
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{
    return false;
}

uint8_t game_mouse_motion (int32_t x, int32_t y,
                           int32_t relx, int32_t rely,
                           int32_t wheelx, int32_t wheely)
{_
    auto level = game->level;
    if (!level) {
        return false;
    }

    if (level->timestamp_dungeon_created &&
      time_have_x_tenths_passed_since(10, level->timestamp_dungeon_created)) {
        if (level->cursor) {_
            if (level->player && !level->player->is_dead) {
                level->cursor->visible();
            }
        }
    }

    return true;
}
