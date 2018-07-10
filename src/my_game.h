/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"
#include "my_thing.h"

typedef std::map< fpoint3d, thingp > display_sorted_things;

struct game_ {
    std::vector<thingp> the_map[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];

    double tile_width;
    double tile_height;

    /*
     * Map co-ordinates, not screen co-ords.
     */
    point player_tile_at;
    point player_mouse_focus_tile_at;
    std::vector<point> player_mouse_path;

    tilep highlighted_tile = {};
    tilep selected_tile = {};

    display_sorted_things display_sorted_all_things;
    things all_things;
    thingp player;

    uint32_t tick;

    int32_t video_pix_width = {};
    int32_t video_pix_height = {};
    double video_gl_width = {};
    double video_gl_height = {};
    int32_t drawable_gl_width = {};
    int32_t drawable_gl_height = {};

    int fps_counter = false;
    int fps_count = true;

    int display_sync = true;
    int full_screen = false;

    /*
     * Where we're looking in the map
     */
    fpoint map_at;
    fpoint map_wanted_at;

    int sdl_delay;
};

extern struct game_ game;

extern uint8_t
game_mouse_motion(int32_t tx, int32_t ty,
                  int32_t x, int32_t y,
                  int32_t wheelx, int32_t wheely);

extern void
game_mouse_over(int32_t tx, int32_t ty,
                int32_t x, int32_t yu,
                int32_t wheelx, int32_t wheely);

extern uint8_t
game_mouse_down(int32_t tx, int32_t ty,
                int32_t x, int32_t y, uint32_t button);

extern uint8_t
game_key_down(const struct SDL_KEYSYM *key);

extern void game_update_player_nexthop(point nexthop);
extern void game_update_player_nexthop(void);

#endif
