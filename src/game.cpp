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

void game_map_create (void)
{_
}

void game_map_created (void)
{_
}

void game_map_destroy (void)
{_
}

void game_display (void)
{_
    /*
     * thing_render_all must come before thing_move_all as it populates
     * all the things into the map for collisions.
     */
    thing_render_all();

//extern void test_display(void); test_display();
//    ascii_display();
}

uint8_t
game_mouse_motion (int32_t tx, int32_t ty,
                   int32_t x, int32_t y,
                   int32_t wheelx, int32_t wheely)
{_
    int mouse_held = mouse_down &&
        time_have_x_tenths_passed_since(1, mouse_down_when);

    py_call_void_module_ptr_iiiiiii("game",
                                    "game_mouse_over",
                                    0, 
                                    tx, ty,
                                    x, y,
                                    wheelx, wheely,
                                    mouse_held);
    return (true);
}

void
game_mouse_over (int32_t tx, int32_t ty,
                 int32_t x, int32_t y,
                 int32_t wheelx, int32_t wheely)
{_
    int mouse_held = mouse_down &&
        time_have_x_tenths_passed_since(1, mouse_down_when);

    py_call_void_module_ptr_iiiiiii("game",
                                    "game_mouse_over",
                                    0, 
                                    tx, ty,
                                    x, y,
                                    wheelx, wheely,
                                    mouse_held);
}

uint8_t
game_mouse_down (int32_t tx, int32_t ty,
                 int32_t x, int32_t y, uint32_t button)
{_
    int ret;

    game_update_player_nexthop();

    ret = py_call_int_module_ptr_iiiii("game",
                                       "game_mouse_down",
                                       0, 
                                       tx, ty,
                                       x, y,
                                       button);
    return (ret);
}

uint8_t
game_key_down (const struct SDL_KEYSYM *key)
{_
    int ret;

    ret = py_call_int_module_ptr_ii("game",
                                    "game_key_down",
                                    0,
                                    key->sym, key->mod);
    return (ret);
}

void game_update_player_nexthop (point nexthop)
{_
    std::vector<point> nexthops = { nexthop };

    game.player_mouse_path = nexthops;

    game_update_player_nexthop();
}

void game_update_player_nexthop (void)
{_
    py_call_void_module_with_list_of_points("hooks",
                                            "hook_update_player_nexthops", 
                                            game.player_mouse_path);
}
