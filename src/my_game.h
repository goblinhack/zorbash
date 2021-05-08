//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_world.h"
#include "my_hiscore.h"
#include <list>

class WidBag;
class WidPopup;

#define GAME_MONST_HEALTH_BAR_STEPS  16
#define GAME_DEFAULT_PIX_ZOOM        4
#define GAME_MAX_PIX_ZOOM            5
#define GAME_MIN_PIX_ZOOM            1
#define GAME_DEFAULT_UI_ZOOM         2

typedef class Config_ {
public:
    uint32_t           header_size                  = {};
    //
    // Keep flags int size so the header size will change on a new flag.
    // It does not always for new bools.
    //
    float              game_pix_scale_height        = {};
    float              game_pix_scale_width         = {};
    float              game_pix_zoom                = GAME_DEFAULT_PIX_ZOOM;
    float              one_pixel_height             = {};
    float              one_pixel_width              = {};
    float              tile_pix_height              = {};
    float              tile_pix_width               = {};
    float              tile_pixel_height            = {};
    float              tile_pixel_width             = {};
    float              ui_pix_scale_height          = {};
    float              ui_pix_scale_width           = {};
    float              ui_pix_zoom                  = GAME_DEFAULT_UI_ZOOM;
    float              video_w_h_ratio              = {};
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
    int32_t            config_pix_height            = {};
    int32_t            config_pix_width             = {};
    int32_t            game_pix_height              = {};
    int32_t            game_pix_width               = {};
    int32_t            ui_pix_height                = {};
    int32_t            ui_pix_width                 = {};
    int32_t            window_pix_height            = {};
    int32_t            window_pix_width             = {};
    uint16_t           ascii_gl_height              = {};
    uint16_t           ascii_gl_width               = {};
    uint32_t           key_action0                  = {};
    uint32_t           key_action1                  = {};
    uint32_t           key_action2                  = {};
    uint32_t           key_action3                  = {};
    uint32_t           key_action4                  = {};
    uint32_t           key_action5                  = {};
    uint32_t           key_action6                  = {};
    uint32_t           key_action7                  = {};
    uint32_t           key_action8                  = {};
    uint32_t           key_action9                  = {};
    uint32_t           key_attack                   = {};
    uint32_t           key_console                  = {};
    uint32_t           key_drop                     = {};
    uint32_t           key_eat                      = {};
    uint32_t           key_help                     = {};
    uint32_t           key_inventory                = {};
    uint32_t           key_jump                     = {};
    uint32_t           key_load                     = {};
    uint32_t           key_map_down                 = {};
    uint32_t           key_map_left                 = {};
    uint32_t           key_map_right                = {};
    uint32_t           key_map_up                   = {};
    uint32_t           key_move_down                = {};
    uint32_t           key_move_left                = {};
    uint32_t           key_move_right               = {};
    uint32_t           key_move_up                  = {};
    uint32_t           key_pause                    = {};
    uint32_t           key_quit                     = {};
    uint32_t           key_save                     = {};
    uint32_t           key_screenshot               = {};
    uint32_t           key_throw                    = {};
    uint32_t           key_unused3                  = {};
    uint32_t           key_unused4                  = {};
    uint32_t           key_unused5                  = {};
    uint32_t           key_use                      = {};
    uint32_t           key_wait_or_collect          = {};
    uint32_t           key_zoom_in                  = {};
    uint32_t           key_zoom_out                 = {};
    uint32_t           music_volume                 = {};
    uint32_t           sdl_delay                    = {};
    uint32_t           sound_volume                 = {};
    uint8_t            tile_height                  = {};
    uint8_t            tile_width                   = {};

    //
    // Ok, not really config...
    //
    HiScores hiscores;

    void fini(void);
    void reset(void);
    void dump(std::string prefix, std::ostream &out);
    void dump(std::string prefix);
} Config;
std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my);
std::istream& operator>>(std::istream &in, Bits<Config &> my);

class Game {
public:
    Game(std::string appdata);
    Game(void) {}
    Thingp thing_find(const ThingId id);
    WidPopup *wid_thing_info_create_popup(Thingp t, point tl, point be);
    WidPopup *wid_thing_info_create_popup_compact(const std::vector<Thingp> &);
    bool load(std::string save_file, class Game &target);
    bool paused(void);
    bool save(std::string save_file);
    bool wid_thing_info_push_popup(Thingp t);
    void config_gfx_select(void);
    void hiscore_select(void);
    void config_keyboard_select(void);
    void config_other_select(void);
    void config_sound_select(void);
    void config_top_select(void);
    void choose_seed_select(void);
    void choose_player_name_select(void);
    void credits_select(void);
    void dead_select(const char *reason);
    void display(void);
    void fini(void);
    void hard_pause(void);
    void hard_unpause(void);
    void help_select(void);
    void init(void);
    void init_level(point3d);
    void init_levels(void);
    void load(int slot);
    void load(void);
    void load_config(void);
    void load_select(void);
    void main_menu_select(void);
    void new_game(void);
    void pause_select(void);
    void quit_select(void);
    void save(int slot);
    void save(void);
    void save_config(void);
    void save_select(void);
    void soft_pause(void);
    void soft_unpause(void);
    void tick_begin(const std::string &);
    void tick_end();
    void wid_thing_collect_create(const std::list<Thingp> &items);
    void wid_thing_collect_destroy(void);
    void wid_thing_info_add_attack(WidPopup *w, Thingp t);
    void wid_thing_info_add_bite_damage(WidPopup *w, Thingp t);
    void wid_thing_info_add_charge_count(WidPopup *w, Thingp t);
    void wid_thing_info_add_constitution(WidPopup *w, Thingp t);
    void wid_thing_info_add_danger_level(WidPopup *w, Thingp t);
    void wid_thing_info_add_defence(WidPopup *w, Thingp t);
    void wid_thing_info_add_gold_value(WidPopup *w, Thingp t);
    void wid_thing_info_add_health(WidPopup *w, Thingp t);
    void wid_thing_info_add_item_rarity(WidPopup *w, Thingp t);
    void wid_thing_info_add_melee_damage(WidPopup *w, Thingp t);
    void wid_thing_info_add_monst_rarity(WidPopup *w, Thingp t);
    void wid_thing_info_add_nutrition(WidPopup *w, Thingp t);
    void wid_thing_info_add_strength(WidPopup *w, Thingp t);
    void wid_thing_info_clear_popup(void);
    void wid_thing_info_create(Thingp, bool when_hovering_over = false);
    void wid_thing_info_create(const std::vector<Thingp> &ts);
    void wid_thing_info_create_when_hovering_over(Thingp);
    void wid_thing_info_create_when_hovering_over(const std::vector<Thingp> &);
    void wid_thing_info_destroy_deferred(void);
    void wid_thing_info_destroy_immediate(void);

    //
    //Save file name, contains the date and other useful save slot info
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
    uint32_t           skillbox_highlight_slot {};
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
    enum {
        STATE_NORMAL,
        STATE_MOVING_ITEMS,     // Currently managing inventory
        STATE_COLLECTING_ITEMS, // Collecting en masse from the level
        STATE_ENCHANTING_ITEMS, // Upgrading items
        STATE_CHOOSING_TARGET,  // Looking to somewhere to throw at
    };
    int                state {STATE_NORMAL};

    //
    // Make sure to update thing_fini.cpp to remove these pointers
    //
    Thingp             request_to_throw_item {}; // What we are throwing.
    Thingp             request_to_fire_item {};  // Projectile or laser we're firing

    //
    // Temporary. Global requests
    //
    bool               request_remake_inventory {};
    bool               request_remake_skillbox {};
    bool               request_destroy_bags {};   // Finished emptying temporary bag
    bool               request_update_rightbar {};
    bool               request_update_same_level {};
    uint32_t           request_destroy_thing_info {}; // Timestamp

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
    std::array<Tilep, GAME_MONST_HEALTH_BAR_STEPS + 1>  tile_cache_health;

    //
    // Temporary. Dampens mouse clicks
    //
    timestamp_t        last_mouse_down {};
    timestamp_t        last_pause {};

    //
    // When the last tick started. Used for looking at spikes in time.
    //
    timestamp_t        tick_begin_ms {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    friend std::ostream& operator<<(std::ostream &out, Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
    void dump(std::string prefix);
    void change_state(int state);
};

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_motion(int32_t x, int32_t y,
                                 int32_t relx, int32_t rely,
                                 int32_t wheelx, int32_t wheely);
extern void game_main_menu_hide(void);
extern void game_main_menu_destroy(void);
extern void game_display_flames(void);
extern uint32_t csum(char *mem, uint32_t len);

extern class Game *game;

#endif
