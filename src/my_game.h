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

#if 0
typedef std::map< fpoint3d, Thingp > display_sorted_things;

struct game_ {
    std::vector<Thingp> the_map[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];

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
    Thingp player;

    uint32_t tick;


    int fps_counter = false;
    int fps_count = true;

    int display_sync = true;
    int full_screen = false;

    /*
     * Where we're looking in the map
     */
    fpoint map_at;
    fpoint map_wanted_at;
};
#endif

class Map {
public:
    Things             all_things;
  
    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("all_things",      all_things));
    }
};

class State {
public:
    uint32_t           fps_count                    = {};
    Map                map;

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("map",             map));
    }
};

class Config {
public:
    bool               fps_counter                  = {};
    uint32_t           sound_volume                 = {};
    uint32_t           music_volume                 = {};
    bool               display_sync                 = true;
    bool               full_screen                  = false;
    int32_t            video_pix_width              = {};
    int32_t            video_pix_height             = {};
    double             video_gl_width               = {};
    double             video_gl_height              = {};
    int32_t            drawable_gl_width            = {};
    int32_t            drawable_gl_height           = {};
    uint32_t           sdl_delay                    = 5;

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("fps_counter",        fps_counter),
                cereal::make_nvp("sound_volume",       sound_volume),
                cereal::make_nvp("music_volume",       music_volume),
                cereal::make_nvp("display_sync",       display_sync),
                cereal::make_nvp("full_screen",        full_screen),
                cereal::make_nvp("video_pix_width",    video_pix_width),
                cereal::make_nvp("video_pix_height",   video_pix_height),
                cereal::make_nvp("video_gl_width",     video_gl_width),
                cereal::make_nvp("video_gl_height",    video_gl_height),
                cereal::make_nvp("drawable_gl_width",  drawable_gl_width),
                cereal::make_nvp("drawable_gl_height", drawable_gl_height),
                cereal::make_nvp("sdl_delay",          sdl_delay));
    }
};

class Game {
public:
    Config             config;
    State              state;
  
    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("config",          config),
                cereal::make_nvp("state",           state));
    }
};


extern class Game game;

extern uint8_t
game_mouse_motion(int32_t x, int32_t y,
                  int32_t wheelx, int32_t wheely);

extern void
game_mouse_over(int32_t x, int32_t yu,
                int32_t wheelx, int32_t wheely);

extern uint8_t
game_mouse_down(int32_t x, int32_t y, uint32_t button);

extern uint8_t
game_key_down(const struct SDL_KEYSYM *key);

#endif
