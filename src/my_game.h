/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"
#include "my_thing.h"

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_ITEMS,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WALLS,
    MAP_DEPTH,
};

class Map {
public:
    Things              all_things;
    std::vector<Thingp> things[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];
    uint8_t             is_wall[MAP_WIDTH][MAP_HEIGHT] = {};
    uint8_t             is_ladder[MAP_WIDTH][MAP_HEIGHT] = {};
    bool                lit_now_by_player[MAP_WIDTH][MAP_HEIGHT] = {};
    bool                lit_earlier_by_player[MAP_WIDTH][MAP_HEIGHT] = {};
  
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

    /*
     * Where we're looking in the map
     */
    fpoint             map_at;
    fpoint             map_wanted_at;
    point              map_tile_over;
    Thingp             player;

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("map",             map),
                cereal::make_nvp("map_at",          map_at),
                cereal::make_nvp("map_wanted_at",   map_wanted_at),
                cereal::make_nvp("map_tile_over",   map_tile_over));
    }
};

class Config {
public:
    bool               fps_counter                  = true;
    uint32_t           sound_volume                 = {};
    uint32_t           music_volume                 = {};
    bool               vsync_enable                 = true;
    bool               full_screen                  = false;
    int32_t            video_pix_width              = {};
    int32_t            video_pix_height             = {};
    double             video_gl_width               = {};
    double             video_gl_height              = {};
    double             video_w_h_ratio              = {};
    int32_t            drawable_gl_width            = {};
    int32_t            drawable_gl_height           = {};
    double             tile_gl_width                = {};
    double             tile_gl_height               = {};
    double             ascii_gl_width               = {};
    double             ascii_gl_height              = {};
    double             tile_pixel_width             = {};
    double             tile_pixel_height            = {};
    uint32_t           sdl_delay                    = 5;
    bool               editor_mode                  = false;

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("fps_counter",        fps_counter),
                cereal::make_nvp("sound_volume",       sound_volume),
                cereal::make_nvp("music_volume",       music_volume),
                cereal::make_nvp("vsync_enable",       vsync_enable),
                cereal::make_nvp("full_screen",        full_screen),
                cereal::make_nvp("video_pix_width",    video_pix_width),
                cereal::make_nvp("video_w_h_ratio",    video_w_h_ratio),
                cereal::make_nvp("video_pix_height",   video_pix_height),
                cereal::make_nvp("video_gl_width",     video_gl_width),
                cereal::make_nvp("video_gl_height",    video_gl_height),
                cereal::make_nvp("tile_gl_width",      tile_gl_width),
                cereal::make_nvp("tile_gl_height",     tile_gl_height),
                cereal::make_nvp("ascii_gl_width",     ascii_gl_width),
                cereal::make_nvp("ascii_gl_height",    ascii_gl_height),
                cereal::make_nvp("drawable_gl_width",  drawable_gl_width),
                cereal::make_nvp("drawable_gl_height", drawable_gl_height),
                cereal::make_nvp("tile_pixel_width",   tile_pixel_width),
                cereal::make_nvp("tile_pixel_height",  tile_pixel_height),
                cereal::make_nvp("sdl_delay",          sdl_delay),
                cereal::make_nvp("editor_mode",        editor_mode));
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

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_key_down(const struct SDL_KEYSYM *key);
extern void game_display(void);

#endif
