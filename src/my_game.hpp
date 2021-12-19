//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include "my_hiscore.hpp"
#include "my_world.hpp"
#include <list>

class WidBag;
class WidPopup;

#define GAME_MONST_HEALTH_BAR_STEPS 16
#define GAME_MOST_ZOOMED_IN         5
#define GAME_MOST_ZOOMED_OUT        1
#define GAME_DEFAULT_UI_ZOOM        2
#define GAME_DEFAULT_PIX_ZOOM       4

typedef class Config_
{
public:
  uint32_t header_size = {};
  //
  // Keep flags int size so the header size will change on a new flag.
  // It does not always for new bools.
  //
  float game_pix_scale_height = {};
  float game_pix_scale_width  = {};
  float game_pix_zoom         = GAME_DEFAULT_PIX_ZOOM;
  float one_pixel_height      = {};
  float one_pixel_width       = {};
  float tile_pix_height       = {};
  float tile_pix_width        = {};
  float tile_pixel_height     = {};
  float tile_pixel_width      = {};
  float ui_pix_scale_height   = {};
  float ui_pix_scale_width    = {};
  float ui_pix_zoom           = GAME_DEFAULT_UI_ZOOM;
  float video_w_h_ratio       = {};

  int debug_mode             = false;
  int fps_counter            = false;
  int gfx_allow_highdpi      = false;
  int gfx_borderless         = true;
  int gfx_fullscreen         = false;
  int gfx_fullscreen_desktop = true;
  int gfx_inverted           = false;
  int gfx_lights             = true;
  int gfx_minimap            = true;
  int gfx_show_hidden        = false;
  int gfx_vsync_enable       = true;
  int gfx_vsync_locked       = false;

  int32_t config_pix_height = {};
  int32_t config_pix_width  = {};
  int32_t game_pix_height   = {};
  int32_t game_pix_width    = {};
  int32_t ui_pix_height     = {};
  int32_t ui_pix_width      = {};
  int32_t window_pix_height = {};
  int32_t window_pix_width  = {};

  uint16_t ascii_gl_height     = {};
  uint16_t ascii_gl_width      = {};
  uint32_t key_action0         = {};
  uint32_t key_action1         = {};
  uint32_t key_action2         = {};
  uint32_t key_action3         = {};
  uint32_t key_action4         = {};
  uint32_t key_action5         = {};
  uint32_t key_action6         = {};
  uint32_t key_action7         = {};
  uint32_t key_action8         = {};
  uint32_t key_action9         = {};
  uint32_t key_attack          = {};
  uint32_t key_console         = {};
  uint32_t key_drop            = {};
  uint32_t key_eat             = {};
  uint32_t key_help            = {};
  uint32_t key_inventory       = {};
  uint32_t key_jump            = {};
  uint32_t key_load            = {};
  uint32_t key_map_down        = {};
  uint32_t key_map_left        = {};
  uint32_t key_map_right       = {};
  uint32_t key_map_up          = {};
  uint32_t key_move_down       = {};
  uint32_t key_move_left       = {};
  uint32_t key_move_right      = {};
  uint32_t key_move_up         = {};
  uint32_t key_quit            = {};
  uint32_t key_robot_mode      = {};
  uint32_t key_save            = {};
  uint32_t key_screenshot      = {};
  uint32_t key_throw           = {};
  uint32_t key_unused4         = {};
  uint32_t key_unused5         = {};
  uint32_t key_use             = {};
  uint32_t key_wait_or_collect = {};
  uint32_t key_zoom_in         = {};
  uint32_t key_zoom_out        = {};
  uint32_t music_volume        = {};
  uint32_t sdl_delay           = {};
  uint32_t sound_volume        = {};

  uint8_t tile_height = {};
  uint8_t tile_width  = {};

  //
  // Ok, not really config...
  //
  HiScores hiscores;

  void fini(void);
  void reset(void);
  void dump(std::string prefix, std::ostream &out);
  void dump(std::string prefix);
} Config;
std::ostream &operator<<(std::ostream &out, Bits< const Config & > const my);
std::istream &operator>>(std::istream &in, Bits< Config & > my);

class Game
{
public:
  Game(std::string appdata);
  Game(void) {}

  Levelp get_current_level(void);

  Thingp thing_find(const ThingId id);
  Thingp thing_find_optional(const ThingId id);

  WidPopup *wid_thing_info_create_popup(Thingp t, point tl, point be);
  WidPopup *wid_thing_info_create_popup_compact(const std::vector< Thingp > &);

  bool load(std::string save_file, class Game &target);
  bool paused(void);
  bool save(std::string save_file);
  bool wid_thing_info_push_popup(Thingp t);
  bool tick_end();
  bool wid_bag_move_item(Thingp t);

  void config_gfx_select(void);
  void choose_player_name_select(void);
  void choose_seed_select(void);
  void config_keyboard_select(void);
  void config_other_select(void);
  void config_sound_select(void);
  void config_top_select(void);
  void credits_select(void);
  void dead_select(const char *reason);
  void display(void);
  void fini(void);
  void help_select(void);
  void hiscore_select(void);
  void init_jump_paths(void);
  void init_level(point3d);
  void init_levels(void);
  void init(void);
  void load_config(void);
  void load(int slot);
  void load_select(void);
  void load_snapshot(void);
  void load(void);
  void main_menu_select(void);
  void new_game(void);
  void quit_select(void);
  void robot_mode_tick();
  void save_config(void);
  void save(int slot);
  void save_select(void);
  void save_snapshot_check();
  void save_snapshot(void);
  void save(void);
  void tick_begin(const std::string &);
  void tick_begin_now(void);
  void tick_set_speed(void);
  void tick_update(void);
  void wid_collect_create(const std::list< Thingp > items);
  void wid_enchant_an_item(void);
  void wid_items_options_create(Widp w, Thingp chosen, bool came_from_inventory);
  void wid_skill_choose(void);
  void wid_thing_info_add_attack(WidPopup *w, Thingp t);
  void wid_thing_info_add_carry_info(WidPopup *w, Thingp t);
  void wid_thing_info_add_charge_count(WidPopup *w, Thingp t);
  void wid_thing_info_add_constitution(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_bite(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_digest(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_melee(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_necrosis(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_poison(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_future1(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_future2(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_future3(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_future4(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_fire(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_crush(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_lightning(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_energy(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_acid(WidPopup *w, Thingp t);
  void wid_thing_info_add_danger_level(WidPopup *w, Thingp t);
  void wid_thing_info_add_defence(WidPopup *w, Thingp t);
  void wid_thing_info_add_dexterity(WidPopup *w, Thingp t);
  void wid_thing_info_add_enchant(WidPopup *w, Thingp t);
  void wid_thing_info_add_gold_value(WidPopup *w, Thingp t);
  void wid_thing_info_add_health(WidPopup *w, Thingp t);
  void wid_thing_info_add_nutrition(WidPopup *w, Thingp t);
  void wid_thing_info_add_rarity(WidPopup *w, Thingp t);
  void wid_thing_info_add_strength(WidPopup *w, Thingp t);
  void wid_thing_info_clear_popup(void);
  void wid_thing_info_create_list(const std::vector< Thingp > &ts);
  void wid_thing_info_create(Thingp, bool when_hovering_over = false);
  void wid_thing_info_create_when_hovering_over_list(const std::vector< Thingp > &);
  void wid_thing_info_create_when_hovering_over(Thingp);
  void wid_thing_info_destroy_deferred(void);
  void wid_thing_info_destroy_immediate(void);

  //
  // Save file name, contains the date and other useful save slot info
  //
  std::string version = "" MYVER "";
  uint32_t    header_size {};
  int         save_slot {};
  std::string save_meta;
  std::string save_file;
  std::string appdata;
  std::string saved_dir;
  Config      config;
  World       world;
  Levelp      level {}; // Current displayed level
  Levelp      level_being_created {};

  //
  // Keep all in order:
  //
  bool started {}; // Game is afoot
  bool things_are_moving {};
  // fpoint      mouse_over;        // Mouse cursor
  point       minimap_over;      // Which tile in the minimap
  int         seed {};           // All randomness jumps off of this
  std::string tick_requested {}; // Something has requested a game tick
  std::string seed_name {};      // Human readable version of the above
  point3d     current_level;     // Where we are in the world.
  uint16_t    frame_count {0};   // Used to know if things have been displayed
  uint32_t    fps_value = {};    // Current framerate
  uint32_t    tick_completed {1};
  uint32_t    tick_current {1};
  uint8_t     inventory_highlight_slot {};
  uint8_t     previous_slot {};
  uint8_t     robot_mode {};
  uint8_t     skillbox_highlight_slot {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Temporary
  //
  uint32_t robot_mode_requested {};
  uint32_t robot_mode_tick_requested {};

  //
  // Used for timesteps within a game tick for smooth thing movement
  //
  float tick_dt {0};

  //
  // How long the last tick took
  //
  uint32_t tick_duration {};

  //
  // This is used to try and speed up animations if in the midst of a jelly storm
  //
  bool tick_current_is_too_slow {};
  bool prev_tick_was_too_slow {};

  //
  // Temporary. Global states
  //
  enum {
    STATE_NORMAL,
    STATE_OPTIONS_FOR_ITEM_MENU, // Drop, throw etc and item
    STATE_INVENTORY,             // Currently managing inventory
    STATE_COLLECTING_ITEMS,      // Collecting en masse from the level
    STATE_ENCHANTING_ITEMS,      // Upgrading items
    STATE_CHOOSING_SKILLS,       // Choosing skills
    STATE_CHOOSING_TARGET,       // Looking to somewhere to throw at
    STATE_LOAD_MENU,
    STATE_SAVE_MENU,
    STATE_QUIT_MENU,
  };
  int state {STATE_NORMAL};
  int fast_move_speed {THING_MOVE_SPEED_FAST_MS};    // Robot and/or move via cursor
  int slow_move_speed {THING_MOVE_SPEED_SLOW_MS};    // Normal speed of all things
  int current_move_speed {THING_MOVE_SPEED_SLOW_MS}; // Current speed

  //
  // Make sure to update thing_fini.cpp to remove these pointers
  //
  Thingp request_to_throw_item {}; // What we are throwing.
  Thingp request_to_fire_item {};  // Projectile or laser we're firing
  Thingp current_wid_thing_info {};

  //
  // Temporary. Global requests
  //
  bool request_remake_rightbar {};
  bool request_remake_inventory {};
  bool request_remake_actionbar {};
  bool request_remake_skillbox {};
  bool request_remake_debuffbox {};
  bool request_remake_buffbox {};
  bool request_update_rightbar {};
  bool request_update_same_level {};
  bool request_snapshot {}; // Something has requested a game snapshot
  bool saving_snapshot {};
  bool request_inventory_thing_over_do {};
  bool request_inventory_thing_selected_do {};

  uint32_t request_destroy_thing_info {}; // Timestamp
  uint32_t request_player_move {};        // Player pressed some keys
  bool     request_player_up {};
  bool     request_player_down {};
  bool     request_player_left {};
  bool     request_player_right {};

  Thingp request_inventory_thing_over {};
  Thingp request_inventory_thing_selected {};

  //
  // An item being moved between bags
  //
  class Wid *in_transit_item {};

  //
  // All bags open.
  //
  std::list< class WidBag * > bags;

  //
  // Temporary. Last cursor path shown.
  //
  std::vector< point > cursor_move_path;

  //
  // Temporary for the status bar
  //
  std::array< Tilep, GAME_MONST_HEALTH_BAR_STEPS + 1 > tile_cache_health;

  //
  // Temporary. Dampens mouse clicks
  //
  ts_t last_mouse_down {};
  ts_t last_pause {};

  //
  // When the last tick started. Used for looking at spikes in time.
  //
  ts_t tick_begin_ms {};

  //
  // Auto generated
  //
  struct JumpPath {
  public:
    point                begin;
    point                end;
    std::vector< point > path;
  };
  std::vector< JumpPath > jump_paths;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  friend std::ostream &operator<<(std::ostream &out, Bits< const class Game & > const my);
  friend std::istream &operator>>(std::istream &in, Bits< class Game & > my);
  void                 dump(std::string prefix, std::ostream &out);
  void                 dump(std::string prefix);
  void                 change_state(int state);
  int                  get_move_speed(void);
  void                 set_meta_data(Levelp);
};

extern uint8_t  game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t  game_mouse_up(int32_t x, int32_t y, uint32_t button);
extern uint8_t  game_mouse_motion(int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
extern void     game_main_menu_hide(void);
extern void     game_main_menu_destroy(void);
extern void     game_display_flames(void);
extern uint32_t csum(char *mem, uint32_t len);

extern class Game *game;

#endif
