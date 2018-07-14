/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include <SDL.h>

#include "my_main.h"
#include "my_sdl.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_glapi.h"
#include "my_tile.h"
#include "my_game.h"
#include "my_time_util.h"
#include "my_python.h"
#include "my_ascii.h"

struct game_ game;

uint8_t
game_mouse_motion (int32_t tx, int32_t ty,
                   int32_t x, int32_t y,
                   int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
    return (false);
}

void
game_mouse_over (int32_t tx, int32_t ty,
                 int32_t x, int32_t y,
                 int32_t wheelx, int32_t wheely)
{_
//    int mouse_held = mouse_down &&
//        time_have_x_tenths_passed_since(1, mouse_down_when);

CON("TBD %s", __FUNCTION__);
}

uint8_t
game_mouse_down (int32_t tx, int32_t ty,
                 int32_t x, int32_t y, uint32_t button)
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
