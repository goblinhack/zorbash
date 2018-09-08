/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_game.h"

class Game game;

void game_display (void)
{_
    static int first = true;
    if (first) {
        auto t = thing_new("player1");
        t->move_to(fpoint(5, 4));

        for (auto x = 0; x < 20; x++) {
            t = thing_new("monst1");
            t->move_to(fpoint(x, x));
        }
    }
    first = false;

    /*
     * thing_render_all must come before thing_move_all as it populates
     * all the things into the map for collisions.
     */
    thing_render_all();

#if 0
    if (!game.editor_mode) {
        thing_move_all();
    }
#endif
}

uint8_t
game_mouse_motion (int32_t x, int32_t y,
                   int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
    return (false);
}

void
game_mouse_over (int32_t x, int32_t y,
                 int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
}

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
CON("TBD %s", __FUNCTION__);
    return (false);
}

uint8_t
game_key_down (const struct SDL_KEYSYM *key)
{_
CON("TBD %s", __FUNCTION__);
    return (false);
}
