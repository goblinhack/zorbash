/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"

class Thing;
class Light;

typedef class Thing* Thingp;
typedef std::unordered_map< uint32_t, Thingp > Things;

typedef class Light* Lightp;
typedef std::unordered_map< uint32_t, Lightp > Lights;

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_EXIT,
    MAP_DEPTH_ITEM,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH_WALLS,
    MAP_DEPTH,
};

#include <list>

class Map {
public:
    Lights                     all_lights;
    std::unordered_map<uint32_t, Lightp> 
                               lights[MAP_WIDTH][MAP_HEIGHT];
    Things                     all_things;
    std::unordered_map<uint32_t, Thingp> 
                               things[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];
    uint8_t                    is_wall[MAP_WIDTH][MAP_HEIGHT] = {};
    uint8_t                    is_floor[MAP_WIDTH][MAP_HEIGHT] = {};
    uint8_t                    is_corridor[MAP_WIDTH][MAP_HEIGHT] = {};
  
    bool is_wall_at(const point &p);
    bool is_wall_at(const int x, const int y);
    bool is_floor_at(const point &p);
    bool is_floor_at(const int x, const int y);
    bool is_corridor_at(const point &p);
    bool is_corridor_at(const int x, const int y);
    bool is_oob(const int x, const int y, const int z);
    bool is_oob(const int x, const int y);
    bool is_oob(const fpoint);
    bool is_oob(const point);

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("all_things",      all_things),
                cereal::make_nvp("things",          things),
                cereal::make_nvp("all_lights",      all_lights),
                cereal::make_nvp("lights",          lights));
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
    double             movement_min_speed           = {};
    double             movement_max_speed           = {};
    double             movement_accel_step          = {};
    double             movement_accel_run           = {};
    double             movement_friction            = {};

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
extern void game_init(void);
extern void game_fini(void);

#endif
