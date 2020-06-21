//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_main.h"
#include "my_sdl.h"
#include "my_point.h"
#include "my_world.h"
#include "my_dmap.h"

typedef class Config_ {
public:
    bool               fps_counter                  = true;
#ifdef ENABLE_GFX_INVERSE_COLORS
    bool               gfx_inverted                 = true;
#else
    bool               gfx_inverted                 = false;
#endif
    bool               gfx_minimap                  = true;
    bool               gfx_show_hidden              = false;
    bool               gfx_lights                   = true;
    uint32_t           gfx_zoom                     = 4;
    bool               gfx_vsync_enable             = true;
    bool               debug_mode                   = false;
    uint32_t           sound_volume                 = {MIX_MAX_VOLUME / 2};
    uint32_t           music_volume                 = {MIX_MAX_VOLUME / 2};
    bool               fullscreen                   = false;
    bool               allow_highdpi                = false;
    //
    // This is the window size.
    //
    int32_t            outer_pix_width              = {};
    int32_t            outer_pix_height             = {};
    //
    // This is the virtual size of the game within the above window.
    //
    int32_t            inner_pix_width              = {};
    int32_t            inner_pix_height             = {};
    //
    // The ratiou of outer to inner
    //
    int32_t            scale_pix_width              = {};
    int32_t            scale_pix_height             = {};
    double             video_w_h_ratio              = {};
    double             tile_pix_width               = {};
    double             tile_pix_height              = {};
    double             one_pixel_width              = {};
    double             one_pixel_height             = {};
    double             ascii_gl_width               = {};
    double             ascii_gl_height              = {};
    double             tile_pixel_width             = {};
    double             tile_pixel_height            = {};
    uint32_t           sdl_delay                    = 1;
    uint32_t           key_map_up                   = {SDL_SCANCODE_UP};
    uint32_t           key_map_down                 = {SDL_SCANCODE_DOWN};
    uint32_t           key_map_left                 = {SDL_SCANCODE_LEFT};
    uint32_t           key_map_right                = {SDL_SCANCODE_RIGHT};
    uint32_t           key_move_up                  = {SDL_SCANCODE_W};
    uint32_t           key_move_down                = {SDL_SCANCODE_S};
    uint32_t           key_move_left                = {SDL_SCANCODE_A};
    uint32_t           key_move_right               = {SDL_SCANCODE_D};
    uint32_t           key_attack                   = {SDL_SCANCODE_SPACE};
    uint32_t           key_wait                     = {SDL_SCANCODE_PERIOD};
    uint32_t           key_load                     = {SDL_SCANCODE_F11};
    uint32_t           key_save                     = {SDL_SCANCODE_F12};
    uint32_t           key_zoom_in                  = {SDL_SCANCODE_Z};
    uint32_t           key_zoom_out                 = {SDL_SCANCODE_X};
    uint32_t           key_pause                    = {SDL_SCANCODE_P};
    uint32_t           key_help                     = {SDL_SCANCODE_H};
    uint32_t           key_quit                     = {SDL_SCANCODE_Q};

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
} Config;
std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my);
std::istream& operator>>(std::istream &in, Bits<Config &> my);

class Game {
public:
    Game (void) {}
    Game (std::string appdata);
    bool load(std::string save_file, class Game &target);
    void tick_begin();
    void tick_end();
    bool paused(void);
    bool save(std::string save_file);
    void config_gfx_select(void);
    void config_other_select(void);
    void config_sound_select(void);
    void config_keyboard_select(void);
    void config_top_select(void);
    void dead_select(const char *reason);
    void display(void);
    void fini(void);
    void hard_pause(void);
    void hard_unpause(void);
    void init(void);
    void init_levels(void);
    void init_level(point3d);
    void load(int slot);
    void load(void);
    void load_config(void);
    void load_select(void);
    void main_menu_select(void);
    void new_game(void);
    void pause_select(void);
    void quit_select(void);
    void help_select(void);
    void save(int slot);
    void save(void);
    void save_config(void);
    void save_select(void);
    void soft_pause(void);
    void soft_unpause(void);

    //
    // Save file name, contains the date and other useful save slot info
    //
    std::string        version = "" VERSION "";
    int                save_slot {};
    std::string        save_meta;
    std::string        save_file;
    std::string        appdata;
    std::string        saved_dir;
    Config             config;
    World              world;
    Levelp             level {};            // Current displayed level

    bool               hard_paused {};      // Hard is when a menu is on screen
    bool               soft_paused {};      // Soft pause is user initiated
    bool               started {};          // Game is afoot
    fpoint             mouse_over;          // Mouse cursor
    int                seed {};             // All randomness jumps off of this
    point3d            current_level;       // Where we are in the world.
    timestamp_t        last_pause {};
    uint32_t           fps_value = {};      // Current framerate
    uint32_t           things_are_moving {};
    uint32_t           tick_completed {};
    uint32_t           tick_current {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////

    //
    // Last cursor path shown.
    //
    std::vector<point> cursor_move_path;

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    friend std::ostream& operator<<(std::ostream &out,
                                    Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in,
                                    Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
};

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);
extern void game_main_menu_hide(void);

#endif
