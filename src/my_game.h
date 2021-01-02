//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_world.h"
#include <list>

class WidBag;

typedef class Config_ {
public:
    uint32_t           header_size                  = {};
    //
    // Keep flags int size so the header size will change on a new flag.
    // It does not always for new bools.
    //
    float              ascii_gl_height              = {};
    float              ascii_gl_width               = {};
    float              gfx_zoom                     = 3;
    float              one_pixel_height             = {};
    float              one_pixel_width              = {};
    float              scale_pix_height             = {};
    float              scale_pix_width              = {};
    float              tile_pix_height              = {};
    float              tile_pix_width               = {};
    float              tile_pixel_height            = {};
    float              tile_pixel_width             = {};
    float              video_w_h_ratio              = {};
    int                ascii_mode                   = false;
    int                debug_mode                   = false;
    int                fps_counter                  = false;
    int                gfx_allow_highdpi            = false;
    int                gfx_borderless               = true;
    int                gfx_fullscreen               = false;
    int                gfx_fullscreen_desktop       = true;
    int                gfx_inverted                 = false;
    int                gfx_lights                   = true;
    int                gfx_minimap                  = true;
    int                gfx_show_hidden              = false;
    int                gfx_vsync_enable             = true;
    int                tile_height                  = {};
    int                tile_width                   = {};
    int32_t            inner_pix_height             = {};
    int32_t            inner_pix_width              = {};
    int32_t            outer_pix_height             = {};
    int32_t            outer_pix_width              = {};
    int32_t            config_pix_height            = {};
    int32_t            config_pix_width             = {};
    uint32_t           key_action0                  = {SDL_SCANCODE_0};
    uint32_t           key_action1                  = {SDL_SCANCODE_1};
    uint32_t           key_action2                  = {SDL_SCANCODE_2};
    uint32_t           key_action3                  = {SDL_SCANCODE_3};
    uint32_t           key_action4                  = {SDL_SCANCODE_4};
    uint32_t           key_action5                  = {SDL_SCANCODE_5};
    uint32_t           key_action6                  = {SDL_SCANCODE_6};
    uint32_t           key_action7                  = {SDL_SCANCODE_7};
    uint32_t           key_action8                  = {SDL_SCANCODE_8};
    uint32_t           key_action9                  = {SDL_SCANCODE_9};
    uint32_t           key_attack                   = {SDL_SCANCODE_SPACE};
#ifdef __APPLE__
    //
    // Delete on mac seems to map to backspace...
    //
    uint32_t           key_drop                     = {SDL_SCANCODE_BACKSPACE};
#else
    uint32_t           key_drop                     = {SDL_SCANCODE_DELETE};
#endif
    uint32_t           key_eat                      = {SDL_SCANCODE_E};
    uint32_t           key_help                     = {SDL_SCANCODE_H};
    uint32_t           key_jump                     = {SDL_SCANCODE_J};
    uint32_t           key_load                     = {SDL_SCANCODE_F11};
    uint32_t           key_map_down                 = {SDL_SCANCODE_DOWN};
    uint32_t           key_map_left                 = {SDL_SCANCODE_LEFT};
    uint32_t           key_map_right                = {SDL_SCANCODE_RIGHT};
    uint32_t           key_map_up                   = {SDL_SCANCODE_UP};
    uint32_t           key_move_down                = {SDL_SCANCODE_S};
    uint32_t           key_move_left                = {SDL_SCANCODE_A};
    uint32_t           key_move_right               = {SDL_SCANCODE_D};
    uint32_t           key_move_up                  = {SDL_SCANCODE_W};
    uint32_t           key_pause                    = {SDL_SCANCODE_P};
    uint32_t           key_quit                     = {SDL_SCANCODE_Q};
    uint32_t           key_save                     = {SDL_SCANCODE_F12};
    uint32_t           key_screenshot               = {SDL_SCANCODE_F10};
    uint32_t           key_throw                    = {SDL_SCANCODE_T};
    uint32_t           key_unused99                 = {SDL_SCANCODE_TAB};
    uint32_t           key_console                  = {SDL_SCANCODE_BACKSLASH};
    uint32_t           key_unused3                  = 0;
    uint32_t           key_unused4                  = 0;
    uint32_t           key_unused5                  = 0;
    uint32_t           key_use                      = {SDL_SCANCODE_U};
    uint32_t           key_wait_or_collect          = {SDL_SCANCODE_PERIOD};
    uint32_t           key_zoom_in                  = {SDL_SCANCODE_Z};
    uint32_t           key_zoom_out                 = {SDL_SCANCODE_X};
    uint32_t           music_volume                 = {MIX_MAX_VOLUME / 2};
    uint32_t           sdl_delay                    = 1;
    uint32_t           sound_volume                 = {MIX_MAX_VOLUME / 2};

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
    void tick_begin(const std::string &);
    void tick_end();
    bool paused(void);
    bool save(std::string save_file);
    void config_gfx_select(void);
    void config_other_select(void);
    void config_sound_select(void);
    void config_keyboard_select(void);
    void config_top_select(void);
    void dead_select(const char *reason);
    void wid_thing_info_create(Thingp, bool when_hovering_over = false);
    void wid_thing_info_create_when_hovering_over(Thingp);
    void wid_thing_info_destroy(void);
    void wid_thing_collect_create(const std::list<Thingp> &items);
    void wid_thing_collect_destroy(void);
    void credits_select(void);
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
    uint32_t           header_size {};
    int                save_slot {};
    std::string        save_meta;
    std::string        save_file;
    std::string        appdata;
    std::string        saved_dir;
    Config             config;
    World              world;
    Levelp             level {};            // Current displayed level

    //
    // Keep all in order:
    //
    bool               hard_paused {};      // Hard is when a menu is on screen
    bool               soft_paused {};      // Soft pause is user initiated
    bool               started {};          // Game is afoot
    bool               things_are_moving {};
    fpoint             mouse_over;          // Mouse cursor
    point              minimap_over;        // Which tile in the minimap
    int                seed {};             // All randomness jumps off of this
    std::string        seed_name {};        // Human readable version of the above
    point3d            current_level;       // Where we are in the world.
    uint32_t           inventory_highlight_slot {};
    uint32_t           previous_slot {};
    uint32_t           fps_value = {};      // Current framerate
    uint32_t           tick_completed {1};
    uint32_t           tick_current {1};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////

    //
    // Temporary
    //

    //
    // Temporary. Global states
    //
    bool               state_moving_items {};     // Currently managing inventory
    bool               state_collecting_items {}; // Collecting en masse from the level

    //
    // Temporary. Global requests
    //
    bool               request_remake_inventory {};
    bool               request_destroy_bags {};   // Finished emptying temporary bag

    //
    // An item being moved between bags
    //
    class Wid *        in_transit_item {};

    //
    // Temporary. Tied to bag moving, so not saved
    //
    std::list<class WidBag *> bags; // The below bags
    class WidBag       *bag_primary {};   // The players inventory
    class WidBag       *bag_secondary {}; // A bag being carried, or a temp bag for collecting

    //
    // Temporary. Last cursor path shown.
    //
    std::vector<point> cursor_move_path;

    //
    // Temporary for the status bar
    //
    std::array<Tilep, THING_TICK_MAX_MOVES_AHEAD + 1> tile_cache_moves_ahead;
    std::array<Tilep, UI_MONST_HEALTH_BAR_STEPS + 1>  tile_cache_health;

    //
    // Temporary. Dampens mouse clicks
    //
    timestamp_t        last_mouse_down {};
    timestamp_t        last_pause {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    friend std::ostream& operator<<(std::ostream &out, Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
};

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_motion(int32_t x, int32_t y,
                                 int32_t relx, int32_t rely,
                                 int32_t wheelx, int32_t wheely);
extern void game_main_menu_hide(void);
extern void game_main_menu_destroy(void);
extern void game_display_flames(void);

#endif
