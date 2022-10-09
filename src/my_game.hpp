//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include <array>
#include <list>
#include <vector>

#include "my_game_defs.hpp"
#include "my_hiscore.hpp"
#include "my_sdl.hpp"
#include "my_thing_defs.hpp"
#include "my_world.hpp"

class WidBag;
class WidPopup;

typedef class Config_
{
public:
  uint32_t serialized_size = {};
  //
  // Keep flags int size so the header size will change on a new flag.
  // It does not always for new bools.
  //
  float game_pix_scale_height = {};
  float game_pix_scale_width  = {};
  float game_pix_zoom         = GAME_DEFAULT_PIX_ZOOM;
  float one_pixel_height      = {};
  float one_pixel_width       = {};
  float tile_pixel_height     = {};
  float tile_pixel_width      = {};
  float tile_pix_height       = {};
  float tile_pix_width        = {};
  float ui_pix_zoom           = GAME_DEFAULT_UI_ZOOM;
  float video_w_h_ratio       = {};

  uint32_t ui_ascii_term_height = {};
  uint32_t ui_ascii_term_width  = {};
  uint32_t ui_gfx_term_height   = {};
  uint32_t ui_gfx_term_width    = {};

  bool debug_mode             = {};
  bool fps_counter            = {};
  bool gfx_allow_highdpi      = {};
  bool gfx_borderless         = {};
  bool gfx_fullscreen         = {};
  bool gfx_fullscreen_desktop = {};
  bool gfx_inverted           = {};
  bool gfx_show_hidden        = {};
  bool gfx_vsync_enable       = {};
  bool gfx_vsync_locked       = {};

  bool mouse_wheel_lr_negated = {};
  bool mouse_wheel_ud_negated = {};

  int config_pix_height = {};
  int config_pix_width  = {};
  int game_pix_height   = {};
  int game_pix_width    = {};
  int ui_pix_height     = {};
  int ui_pix_width      = {};
  int window_pix_height = {};
  int window_pix_width  = {};

  uint16_t ascii_gl_height = {};
  uint16_t ascii_gl_width  = {};
  uint32_t music_volume    = {};
  uint32_t sdl_delay       = {};
  uint32_t snapshot_freq   = {};
  uint32_t sound_volume    = {};

  // begin sort marker1
  SDL_Keysym key_action0         = {};
  SDL_Keysym key_action1         = {};
  SDL_Keysym key_action2         = {};
  SDL_Keysym key_action3         = {};
  SDL_Keysym key_action4         = {};
  SDL_Keysym key_action5         = {};
  SDL_Keysym key_action6         = {};
  SDL_Keysym key_action7         = {};
  SDL_Keysym key_action8         = {};
  SDL_Keysym key_action9         = {};
  SDL_Keysym key_skill0          = {};
  SDL_Keysym key_skill1          = {};
  SDL_Keysym key_skill2          = {};
  SDL_Keysym key_skill3          = {};
  SDL_Keysym key_skill4          = {};
  SDL_Keysym key_skill5          = {};
  SDL_Keysym key_skill6          = {};
  SDL_Keysym key_skill7          = {};
  SDL_Keysym key_skill8          = {};
  SDL_Keysym key_skill9          = {};
  SDL_Keysym key_attack          = {};
  SDL_Keysym key_console         = {};
  SDL_Keysym key_drop            = {};
  SDL_Keysym key_eat             = {};
  SDL_Keysym key_help            = {};
  SDL_Keysym key_inventory       = {};
  SDL_Keysym key_jump            = {};
  SDL_Keysym key_load            = {};
  SDL_Keysym key_map_down        = {};
  SDL_Keysym key_map_left        = {};
  SDL_Keysym key_map_right       = {};
  SDL_Keysym key_map_up          = {};
  SDL_Keysym key_move_down       = {};
  SDL_Keysym key_move_left       = {};
  SDL_Keysym key_move_right      = {};
  SDL_Keysym key_move_up         = {};
  SDL_Keysym key_quit            = {};
  SDL_Keysym key_robot_mode      = {};
  SDL_Keysym key_save            = {};
  SDL_Keysym key_screenshot      = {};
  SDL_Keysym key_throw           = {};
  SDL_Keysym key_descend         = {};
  SDL_Keysym key_gfx_toggle      = {};
  SDL_Keysym key_ascend          = {};
  SDL_Keysym key_use             = {};
  SDL_Keysym key_wait_or_collect = {};
  SDL_Keysym key_zoom_in         = {};
  SDL_Keysym key_zoom_out        = {};
  // end sort marker1

  uint8_t tile_height = {};
  uint8_t tile_width  = {};

  //
  // Ok, not really config...
  //
  HiScores hiscores;

  void fini(void);
  void reset(void);
} Config;

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

  bool init_level(point3d world_at, point grid_at, int difficulty_depth, int dungeon_walk_order_level_no);
  bool load(std::string save_file, class Game &target);
  bool save(std::string save_file);
  bool tick_end();
  bool wid_bag_move_item(Thingp t);
  bool wid_thing_info_create_list(std::vector< Thingp > &ts);
  bool wid_thing_info_create(Thingp, bool when_hovering_over = false);
  bool wid_thing_info_push_popup(Thingp t);

  // begin sort marker2
  void display(void);
  void fini(void);
  void init_jump_paths(void);
  void init(void);
  void load_config(void);
  void load(int slot);
  void load_snapshot(void);
  void load(void);
  void new_game(void);
  void place_player(void);
  void pre_init(void);
  void quit_select(void);
  void robot_mode_tick();
  void save_config(void);
  void save(int slot);
  void save_snapshot_check();
  void save_snapshot(void);
  void save(void);
  void set_seed(void);
  void start(void);
  void tick_begin(const std::string &);
  void tick_begin_now(void);
  void tick_set_speed(void);
  void tick_update(void);
  void wid_choose_initial_dungeons(void);
  void wid_choose_next_dungeons(Levelp, bool is_ascending, bool is_descending);
  void wid_choose_player_name_select(void);
  void wid_choose_seed_select(void);
  void wid_choose_skill(void);
  void wid_collect_create(const std::list< Thingp > items);
  void wid_config_gfx_select(void);
  void wid_config_keyboard_select(void);
  void wid_config_mouse_select(void);
  void wid_config_other_select(void);
  void wid_config_sound_select(void);
  void wid_config_top_menu(void);
  void wid_credits_select(void);
  void wid_dead_select(const char *reason);
  void wid_enchant_an_item(void);
  void wid_help_select(void);
  void wid_hiscores_show(void);
  void wid_items_options_create(Widp w, Thingp chosen, bool came_from_inventory);
  void wid_load_select(void);
  void wid_main_menu_select(void);
  void wid_save_select(void);
  void wid_thing_info_add_attack(WidPopup *w, Thingp t);
  void wid_thing_info_add_carry_info(WidPopup *w, Thingp t);
  void wid_thing_info_add_charge_count(WidPopup *w, Thingp t);
  void wid_thing_info_add_crit_chance(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_acid(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_cold(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_crush(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damaged_chance(WidPopup *w, Thingp t);
  void wid_thing_info_add_damage_digest(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_draining(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_energy(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_fire(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_future1(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_bite(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_claw(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_lightning(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_melee(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_nat_att(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_necrosis(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_damage_poison(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_danger_level(WidPopup *w, Thingp t);
  void wid_thing_info_add_enchant(WidPopup *w, Thingp t);
  void wid_thing_info_add_general_info(WidPopup *w, Thingp t);
  void wid_thing_info_add_gold_value(WidPopup *w, Thingp t);
  void wid_thing_info_add_health(WidPopup *w, Thingp t);
  void wid_thing_info_add_jump_distance(WidPopup *w, Thingp t);
  void wid_thing_info_add_move_speed(WidPopup *w, Thingp t);
  void wid_thing_info_add_noise(WidPopup *w, Thingp t);
  void wid_thing_info_add_nutrition(WidPopup *w, Thingp t);
  void wid_thing_info_add_shove_strength(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_con(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_def(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_dex(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_luck(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_str(WidPopup *w, Thingp t);
  void wid_thing_info_clear_popup(void);
  void wid_thing_info_destroy_deferred(void);
  void wid_thing_info_destroy_immediate(void);
  // end sort marker2

  //
  // Save file name, contains the date and other useful save slot info
  //
  std::string version = "" MYVER "";

  uint32_t serialized_size {};
  int      save_slot {};

  std::string save_meta;
  std::string save_file;
  std::string appdata;
  std::string saved_dir;

  Config config;

  World world;

  Levelp level {}; // Current displayed level
  Levelp level_being_created {};

  //
  // Keep all in order:
  //
  bool started {}; // Game is afoot
  bool things_are_moving {};
  bool robot_mode {};

  point map_mini_over; // Which tile in the map_mini

  uint32_t seed {}; // All randomness jumps off of this

  std::string tick_requested {}; // Something has requested a game tick
  std::string seed_name {};      // Human readable version of the above

  point3d current_level; // Where we are in the world.

  uint32_t move_count {};   // How many moves the player has made
  uint16_t frame_count {0}; // Used to know if things have been displayed
  uint32_t fps_value = {};  // Current framerate
  uint32_t tick_completed {1};
  uint32_t tick_current {1};

  uint8_t inventory_highlight_slot {};
  uint8_t previous_slot {};
  uint8_t skillbox_highlight_slot {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Temporary
  //
  bool paused {};             // Game is paused choosing a level?
  bool is_being_destroyed {}; // Game is ending

  uint32_t robot_mode_requested {};
  uint32_t robot_mode_tick_requested {};
  uint32_t start_requested {};

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
    STATE_CHOOSING_LEVEL,        // Choosing the next level
    STATE_KEYBOARD_MENU,         // Keyboard optionds
    STATE_LOAD_MENU,             // Loading a game
    STATE_SAVE_MENU,             // Saving a game
    STATE_QUIT_MENU,             // Pondering quitting
  };
  int state {STATE_NORMAL};
  int fast_move_speed {THING_MOVE_SPEED_FAST_MS};    // Moving when you have a cursor path
  int slow_move_speed {THING_MOVE_SPEED_SLOW_MS};    // Normal speed of all things
  int current_move_speed {THING_MOVE_SPEED_SLOW_MS}; // Current speed

  //
  // Make sure to update thing_fini.cpp to remove these pointers
  //
  Thingp request_to_throw_item {}; // What we are throwing.
  Thingp request_to_use_item {};   // Projectile or laser we're firing

  //
  // Current thing being described in detail on screen.
  //
  Thingp current_wid_thing_info {};

  /////////////////////////////////////////////////////////////////////////
  // Temporary. Global requests
  /////////////////////////////////////////////////////////////////////////

  //
  // Is the selected position ok for throwing?
  //
  bool request_destination_ok {};

  //
  // Used by the robot to change levels
  //
  Widp request_to_choose_level {};

  // begin sort marker3
  bool currently_saving_snapshot {};
  bool request_player_move_down {};
  bool request_player_move_left {};
  bool request_player_move_right {};
  bool request_player_move_up {};
  bool request_player_to_ascend_level {};
  bool request_player_to_descend_level {};
  bool request_player_to_wait_or_collect {};
  bool request_reset_state_change {};
  bool request_to_remake_actionbar {};
  bool request_to_remake_buffbox {};
  bool request_to_remake_debuffbox {};
  bool request_to_remake_inventory {};
  bool request_to_remake_rightbar {};
  bool request_to_remake_skillbox {};
  bool request_to_save_snapshot {}; // Something has requested a game snapshot
  bool request_to_toggle_gfx {};
  bool request_to_update_inventory_with_thing_over {};
  bool request_to_update_inventory_with_thing_selected {};
  bool request_to_update_same_level {};
  // end sort marker3

  uint32_t request_destroy_thing_info {}; // Timestamp
  uint32_t request_player_move {};        // Player pressed some keys

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
  point                cursor_move_end;
  bool                 cursor_moved {};

  //
  // Temporary for the status bar
  //
  std::array< std::array< Tilep, GAME_MONST_HEALTH_BAR_STEPS + 1 >, 2 > tile_cache_health;

  //
  // Temporary. Dampens mouse clicks
  //
  ts_t last_mouse_down {};
  ts_t last_pause {};

  //
  // When the last tick started. Used for looking at spikes in time.
  //
  ts_t tick_begin_ms {};
  ts_t tick_begin_game_ms {};

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

  int get_move_speed(void);

  void change_state(int state, const std::string &);
  void set_meta_data(Levelp);
  void dump(std::string prefix, std::ostream &out);
  void dump(std::string prefix);

  void set_request_reset_state_change(void);
  void set_request_to_remake_rightbar(void);
  void set_request_to_remake_inventory(void);
  void set_request_to_remake_actionbar(void);
  void set_request_to_remake_skillbox(void);
  void set_request_to_remake_debuffbox(void);
  void set_request_to_remake_buffbox(void);
  void set_request_to_update_same_level(void);
  void set_request_to_save_snapshot(void);
  void set_currently_saving_snapshot(void);
  void set_request_to_update_inventory_with_thing_over(void);
  void set_request_to_update_inventory_with_thing_selected(void);

  void unset_request_reset_state_change(void);
  void unset_request_to_remake_rightbar(void);
  void unset_request_to_remake_inventory(void);
  void unset_request_to_remake_actionbar(void);
  void unset_request_to_remake_skillbox(void);
  void unset_request_to_remake_debuffbox(void);
  void unset_request_to_remake_buffbox(void);
  void unset_request_to_update_same_level(void);
  void unset_request_to_save_snapshot(void);
  void unset_currently_saving_snapshot(void);
  void unset_request_to_update_inventory_with_thing_over(void);
  void unset_request_to_update_inventory_with_thing_selected(void);
};

extern uint8_t game_mouse_down(int x, int y, uint32_t button);
extern uint8_t game_mouse_up(int x, int y, uint32_t button);
extern uint8_t game_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely);

extern void wid_main_menu_hide(void);
extern void wid_main_menu_destroy(void);
extern void game_display_flames(void);

extern uint32_t csum(char *mem, uint32_t len);

extern std::string gama_state_to_string(int state);

extern class Game *game;

#endif
