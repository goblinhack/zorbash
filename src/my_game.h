/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"

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

    int fps_counter;
    int fps_count;

    int sound_volume;
    int music_volume;
    int display_sync;
    int full_screen;

    /*
     * Where we're looking in the map
     */
    fpoint map_at;
    fpoint map_wanted_at;

    double zzz1;
    double zzz2;
    double zzz3;
    double zzz4;
    double zzz5;
    double zzz6;
    double zzz7;
    double zzz8;
    double zzz9;
    double zzz10;
    double zzz11;
    double zzz12;
    double zzz13;
    double zzz14;
    double zzz15;
    double zzz16;
    double zzz17;
    double zzz18;
    double zzz19;
    double zzz20;
    double zzz21;
    double zzz22;
    double zzz23;
    double zzz24;
    double zzz25;
    double zzz26;
    double zzz27;
    double zzz28;
    double zzz29;
    double zzz30;
    double zzz31;
    double zzz32;
    double zzz33;
    double zzz34;
    double zzz35;
    double zzz36;
    double zzz37;
    double zzz38;
    double zzz39;
    double zzz40;
    double zzz41;
    double zzz42;
    double zzz43;
    double zzz44;
    double zzz45;
    double zzz46;
    double zzz47;
    double zzz48;
    double zzz49;
    double zzz50;
    double zzz51;
    double zzz52;
    double zzz53;
    double zzz54;
    double zzz55;
    double zzz56;
    double zzz57;
    double zzz58;
    double zzz59;
    double zzz60;
    double zzz61;
    double zzz62;
    double zzz63;
    double zzz64;
    double zzz65;
    double zzz66;
    double zzz67;
    double zzz68;
    double zzz69;
    double zzz70;
    double zzz71;
    double zzz72;
    double zzz73;
    double zzz74;
    double zzz75;
    double zzz76;
    double zzz77;
    int sdl_delay;
};

extern struct game_ game;
extern void game_map_create(void);
extern void game_map_created(void);
extern void game_map_destroy(void);
extern void game_display(void);

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
