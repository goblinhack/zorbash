//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include <SDL.h>
#include <vector>

#include "my_hiscore.hpp"
#include "my_world.hpp"

class WidBag;
class WidPopup;

using Config = class Config_
{
public:
  std::string version = "" MYVER "";

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

  bool debug_mode              = {};
  bool disable_player_warnings = {};
  bool fps_counter             = {};
  bool gfx_allow_highdpi       = {};
  bool gfx_borderless          = {};
  bool gfx_fullscreen          = {};
  bool gfx_fullscreen_desktop  = {};
  bool gfx_inverted            = {};
  bool gfx_monochrome          = {};
  bool gfx_show_hidden         = {};
  bool gfx_vsync_enable        = {};
  bool gfx_vsync_locked        = {};

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

  // begin sort marker1 {
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
  SDL_Keysym key_ascend          = {};
  SDL_Keysym key_attack          = {};
  SDL_Keysym key_console         = {};
  SDL_Keysym key_descend         = {};
  SDL_Keysym key_drop            = {};
  SDL_Keysym key_eat             = {};
  SDL_Keysym key_gfx_toggle      = {};
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
  SDL_Keysym key_spell0          = {};
  SDL_Keysym key_spell1          = {};
  SDL_Keysym key_spell2          = {};
  SDL_Keysym key_spell3          = {};
  SDL_Keysym key_spell4          = {};
  SDL_Keysym key_spell5          = {};
  SDL_Keysym key_spell6          = {};
  SDL_Keysym key_spell7          = {};
  SDL_Keysym key_spell8          = {};
  SDL_Keysym key_spell9          = {};
  SDL_Keysym key_throw           = {};
  SDL_Keysym key_unused1         = {};
  SDL_Keysym key_unused10        = {};
  SDL_Keysym key_unused11        = {};
  SDL_Keysym key_unused12        = {};
  SDL_Keysym key_unused13        = {};
  SDL_Keysym key_unused14        = {};
  SDL_Keysym key_unused15        = {};
  SDL_Keysym key_unused16        = {};
  SDL_Keysym key_unused17        = {};
  SDL_Keysym key_unused18        = {};
  SDL_Keysym key_unused19        = {};
  SDL_Keysym key_unused2         = {};
  SDL_Keysym key_unused20        = {};
  SDL_Keysym key_unused3         = {};
  SDL_Keysym key_unused4         = {};
  SDL_Keysym key_unused5         = {};
  SDL_Keysym key_unused6         = {};
  SDL_Keysym key_unused7         = {};
  SDL_Keysym key_unused8         = {};
  SDL_Keysym key_unused9         = {};
  SDL_Keysym key_use             = {};
  SDL_Keysym key_wait_or_collect = {};
  SDL_Keysym key_zoom_in         = {};
  SDL_Keysym key_zoom_out        = {};
  // end sort marker1 }

  uint8_t tile_height = {};
  uint8_t tile_width  = {};

  //
  // Ok, not really config...
  //
  HiScores hiscores;

  //
  // Preferred bodyparts
  //
  std::array< std::string, BODYPART_MAX > player_bodyparts = {};

  void fini(void);
  void final_init(void);
  void reset(void);
};

class Skill
{
public:
  //
  // Current skill
  //
  std::string skill_alias;
  //
  // Populated when the menu is made.
  //
  Tpp tpp = {};
  //
  // Next skills in the tree
  //
  Skillp skill_down  = {};
  Skillp skill_up    = {};
  Skillp skill_left  = {};
  Skillp skill_right = {};
};

bool skill_has_precursor(Skillp);
bool skill_is_available(Skillp);

class Spell
{
public:
  //
  // Current spell
  //
  std::string spell_alias;
  //
  // Populated when the menu is made.
  //
  Tpp tpp = {};
  //
  // Next spells in the tree
  //
  Spellp spell_down  = {};
  Spellp spell_up    = {};
  Spellp spell_left  = {};
  Spellp spell_right = {};
};

bool spell_has_precursor(Spellp);
bool spell_is_available(Spellp);

class Game
{
public:
  //
  // Save file name, contains the date and other useful save slot info
  //
  std::string version = "" MYVER "";

  //
  // Used to check for changes in the size of this struct.
  //
  uint32_t serialized_size {};

  //
  // If this was a saved game, which slot does it use.
  //
  int save_slot {};

  //
  // Title and seed name.
  //
  std::string save_meta;

  //
  // Saved file for this game.
  //
  std::string save_file;

  //
  // Appdata dir for saving logs.
  //
  std::string appdata;

  //
  // Save dir for saving games.
  //
  std::string saved_dir;

  //
  // User configuration.
  //
  Config config;

  //
  // The entire world, levels and all.
  //
  World world;

  //
  // Current displayed level.
  //
  Levelp level {};

  //
  // Current level being created.
  //
  Levelp level_being_created {};

  //
  // Game is afoot.
  //
  bool started {};

  //
  // Things in this tick are still moving. Only really used in pixel art mode.
  //
  bool things_are_moving {};

  //
  // Player ready to see console messages
  //
  bool player_is_ready_for_messages {};

  //
  // All randomness jumps off of this.
  //
  uint32_t seed {};

  //
  // Human readable version of the above seed.
  //
  std::string seed_name {};

  //
  // Something has requested a game tick.
  //
  std::string tick_requested {};

  //
  // Which tile in the mini map are we over.
  //
  point map_mini_over;

  //
  // Where the player is in the world map.
  //
  point3d current_level;

  //
  // How many moves the player has made
  //
  uint32_t player_move_count_in_this_snapshot {};

  //
  // FPS settings.
  //
  uint32_t frame_count {0};
  //
  // Current framerate
  //
  uint32_t fps_value = {};

  //
  // Game tick progression.
  //
  int tick_completed {1};
  int tick_current {1};

  //
  // What the player has highlighted in the inventory.
  //
  uint8_t inventory_highlight_slot {};
  uint8_t previous_slot {};
  uint8_t skillbox_highlight_slot {};
  uint8_t spellbox_highlight_slot {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Player warnings on moving onto bad terrain.
  //
  point warning_popup_exists_for_move_confirm = point(-1, -1);

  //
  // Game is paused choosing a level? Prrvents the level tick from running.
  //
  bool paused {};

  //
  // Game is ending and levels are being destroyed.
  //
  bool is_being_destroyed {};

  //
  // Temporary. Robot mode settings.
  //
  bool     robot_mode {};
  uint32_t robot_mode_requested {};
  uint32_t robot_mode_tick_requested {};

  //
  // Temporary. Player wants to play.
  //
  uint32_t player_requested_to_start_the_game {};

  //
  // Temporary. Used for timesteps within a game tick for smooth thing movement.
  //
  float tick_dt {0};

  //
  // Temporary. How long the last tick took
  //
  int tick_duration {};

  //
  // Temporary. This is used to try and speed up animations if in the midst of a slime storm
  //
  bool tick_current_is_too_slow {};
  bool prev_tick_was_too_slow {};

  //
  // Temporary. Global states
  //
  enum {
    STATE_NORMAL,
    STATE_INVENTORY,        // Currently managing inventory
    STATE_COLLECTING_ITEMS, // Collecting en masse from the level
    STATE_ENCHANTING_ITEMS, // Upgrading items
    STATE_CHOOSING_SKILLS,  // Choosing skills
    STATE_CHOOSING_SPELLS,  // Choosing spells
    STATE_CHOOSING_TARGET,  // Looking to somewhere to throw at
    STATE_CHOOSING_LEVEL,   // Choosing the next level
    STATE_KEYBOARD_MENU,    // Keyboard optionds
    STATE_LOAD_MENU,        // Loading a game
    STATE_SAVE_MENU,        // Saving a game
    STATE_QUIT_MENU,        // Pondering quitting
  };
  int state {STATE_NORMAL};

  //
  // Moving speed when you have a cursor path
  //
  int fast_move_speed {THING_MOVE_SPEED_FAST_MS};

  //
  // Normal speed of all things
  //
  int slow_move_speed {THING_MOVE_SPEED_SLOW_MS};

  //
  // Current thing move speed.
  //
  int current_move_speed {THING_MOVE_SPEED_SLOW_MS};

  //
  // Temporary. Is the selected position ok for throwing?
  //
  bool request_destination_ok {};

  //
  // Temporary. Used by the robot to change levels
  //
  Widp request_to_choose_level {};

  // begin sort marker3 {
  bool currently_saving_snapshot {};
  bool request_player_move_down {};
  bool request_player_move_left {};
  bool request_player_move_right {};
  bool request_player_move_up {};
  bool request_player_to_ascend_level {};
  bool request_player_to_descend_level {};
  bool request_player_to_wait_or_collect {};
  bool request_recreate_cursor_path {};
  bool request_reset_state_change {};
  bool request_to_remake_actionbar {};
  bool request_to_remake_buffbox {};
  bool request_to_remake_debuffbox {};
  bool request_to_remake_inventory {};
  bool request_to_remake_rightbar {};
  bool request_to_remake_skillbox {};
  bool request_to_remake_spellbox {};
  bool request_to_save_snapshot {}; // Something has requested a game snapshot
  bool request_to_toggle_gfx {};
  bool request_to_update_inventory_with_thing_over {};
  bool request_to_update_inventory_with_thing_selected {};
  bool request_to_update_same_level {};
  // end sort marker3 }

  //
  // When the thing info was requested to be destroyed.
  //
  uint32_t request_destroy_thing_info {}; // Timestamp
  uint32_t request_destroy_tp_info {};    // Timestamp

  //
  // When the player pressed some keys.
  //
  uint32_t request_player_move {};

  //
  // Temporary. Current thing being described in detail on screen.
  //
  Thingp current_wid_thing_info {};
  Tpp    current_wid_tp_info {};

  //
  // Which inventory items are we over.
  //
  Thingp request_inventory_thing_over {};
  Thingp request_inventory_thing_selected {};

  //
  // Projectile or laser we're firing
  //
  Thingp request_to_use_item {};

  //
  // Temporary. Make sure to update thing_fini.cpp to remove these pointers
  //
  Thingp request_to_throw_item {}; // What we are throwing.

  //
  // Temporary list of popups.
  //
  std::list< Thingp > popups;

  //
  // Temporary. An item being moved between bags
  //
  class Wid *in_transit_item {};

  //
  // Temporary. All bags open.
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
  std::array< std::array< Tilep, GAME_MONST_HEALTH_BAR_STEPS + 1 >, 2 > tile_cache_health = {};

  //
  // Skill tree
  //
  std::map< std::string, std::string > skill_aliases;
  //
  // The key is the type of skill tree, e.g. martial, magical, healing, diabolic
  //
  std::map< std::string, std::array< std::array< Skillp, SKILL_TREE_DOWN >, SKILL_TREE_ACROSS > > skill_tree {};

  //
  // Spell tree
  //
  std::map< std::string, std::string > spell_aliases;
  //
  // The key is the type of spell tree, e.g. martial, magical, healing, diabolic
  //
  std::map< std::string, std::array< std::array< Spellp, SPELL_TREE_DOWN >, SPELL_TREE_ACROSS > > spell_tree {};

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
  // All possible jump paths a thing can traverse. This is auto generated at startup.
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

  Game(std::string appdata);
  Game(void) = default;

  Levelp get_current_level(void);

  Thingp thing_find(const ThingId id);
  Thingp thing_find_optional(const ThingId id);

  WidPopup *wid_thing_info_create_popup(Thingp t, point tl, point be);
  WidPopup *wid_thing_info_create_popup_compact(const std::vector< Thingp > &);

  WidPopup *wid_tp_info_create_popup(Tpp t, point tl, point be);
  WidPopup *wid_tp_info_create_popup_compact(const std::vector< Tpp > &);

  std::string load_config(void);

  bool init_level(point3d world_at, point grid_at, int difficulty_depth, int dungeon_walk_order_level_no);
  bool load(std::string save_file, class Game &target);
  bool player_tick(bool left, bool right, bool up, bool down, bool attack, bool wait, bool jump);
  bool player_tick_(bool left, bool right, bool up, bool down, bool attack, bool wait, bool jump);
  bool save(std::string save_file);
  bool tick_end();
  bool wid_bag_move_item(Thingp t);
  bool wid_thing_info_create_list(std::vector< Thingp > &ts);
  bool wid_thing_info_create(Thingp, bool when_hovering_over = false);
  bool wid_thing_info_push_popup(Thingp t);
  bool wid_tp_info_create_list(std::vector< Tpp > &ts);
  bool wid_tp_info_create(Tpp, bool when_hovering_over = false);
  bool wid_tp_info_push_popup(Tpp t);

  // begin sort marker2 {
  void change_state(int state, const std::string &);
  void display(void);
  void dump(std::string prefix);
  void dump(std::string prefix, std::ostream &out);
  void fini(void);
  void init_jump_paths(void);
  void init(void);
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
  void set_currently_saving_snapshot(void);
  void set_meta_data(Levelp);
  void set_request_reset_state_change(void);
  void set_request_to_remake_actionbar(void);
  void set_request_to_remake_buffbox(void);
  void set_request_to_remake_debuffbox(void);
  void set_request_to_remake_inventory(void);
  void set_request_to_remake_rightbar(void);
  void set_request_to_remake_skillbox(void);
  void set_request_to_remake_spellbox(void);
  void set_request_to_save_snapshot(void);
  void set_request_to_update_inventory_with_thing_over(void);
  void set_request_to_update_inventory_with_thing_selected(void);
  void set_request_to_update_same_level(void);
  void set_seed(void);
  void start(void);
  void tick_begin(const std::string &);
  void tick_begin_now(void);
  void tick_set_speed(void);
  void tick_update(void);
  void unset_currently_saving_snapshot(void);
  void unset_request_reset_state_change(void);
  void unset_request_to_remake_actionbar(void);
  void unset_request_to_remake_buffbox(void);
  void unset_request_to_remake_debuffbox(void);
  void unset_request_to_remake_inventory(void);
  void unset_request_to_remake_rightbar(void);
  void unset_request_to_remake_skillbox(void);
  void unset_request_to_remake_spellbox(void);
  void unset_request_to_save_snapshot(void);
  void unset_request_to_update_inventory_with_thing_over(void);
  void unset_request_to_update_inventory_with_thing_selected(void);
  void unset_request_to_update_same_level(void);
  void wid_choose_avatar_select(void);
  void wid_choose_from_skill_tree(std::string tree_name);
  void wid_choose_from_spell_tree(std::string tree_name);
  void wid_choose_initial_dungeons(void);
  void wid_choose_next_dungeons(Levelp, bool is_ascending, bool is_descending);
  void wid_choose_player_name_select(void);
  void wid_choose_seed_select(void);
  void wid_choose_skill(void);
  void wid_choose_spell(void);
  void wid_collect_create(const std::list< ThingId > items);
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
  void wid_thing_info_add_carry_info(WidPopup *w, Thingp t);
  void wid_thing_info_add_charge_count(WidPopup *w, Thingp t);
  void wid_thing_info_add_crit_chance(WidPopup *w, Thingp t);
  void wid_thing_info_add_danger_level(WidPopup *w, Thingp t);
  void wid_thing_info_add_dmg_acid(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_bite(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_claw(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_cold(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_crush(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmgd_chance(WidPopup *w, Thingp t);
  void wid_thing_info_add_dmg_digest(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_drown(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_energy(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_fire(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_heat(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_impact(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_lightning(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_magic(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_melee(WidPopup *w, Thingp t);
  void wid_thing_info_add_dmg_missile(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_nat_att(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_necrosis(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_negation(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_poison(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_dmg_stamina(WidPopup *w, Thingp t, int index);
  void wid_thing_info_add_enchant(WidPopup *w, Thingp t);
  void wid_thing_info_add_general_info(WidPopup *w, Thingp t);
  void wid_thing_info_add_gold_value(WidPopup *w, Thingp t);
  void wid_thing_info_add_health(WidPopup *w, Thingp t);
  void wid_thing_info_add_immunity(WidPopup *w, Thingp t);
  void wid_thing_info_add_jump_distance(WidPopup *w, Thingp t);
  void wid_thing_info_add_move_speed(WidPopup *w, Thingp t);
  void wid_thing_info_add_noise(WidPopup *w, Thingp t);
  void wid_thing_info_add_nutrition(WidPopup *w, Thingp t);
  void wid_thing_info_add_shove_strength(WidPopup *w, Thingp t);
  void wid_thing_info_add_spell_cost(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_att_penalties(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_att(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_con(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_def_penalties(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_def(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_dex(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_int(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_luck(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_psi(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_str(WidPopup *w, Thingp t);
  void wid_thing_info_add_stat_thv(WidPopup *w, Thingp t);
  void wid_thing_info_clear_popup(void);
  void wid_thing_info_destroy_deferred(void);
  void wid_thing_info_destroy_immediate(void);
  void wid_tp_info_add_crit_chance(WidPopup *w, Tpp t);
  void wid_tp_info_add_dmg_acid(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_bite(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_claw(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_cold(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_crush(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmgd_chance(WidPopup *w, Tpp t);
  void wid_tp_info_add_dmg_digest(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_drown(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_energy(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_fire(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_heat(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_impact(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_lightning(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_magic(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_melee(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_missile(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_nat_att(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_necrosis(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_negation(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_poison(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_dmg_stamina(WidPopup *w, Tpp t, int index);
  void wid_tp_info_add_enchant(WidPopup *w, Tpp t);
  void wid_tp_info_add_general_info(WidPopup *w, Tpp t);
  void wid_tp_info_add_gold_value(WidPopup *w, Tpp t);
  void wid_tp_info_add_health(WidPopup *w, Tpp t);
  void wid_tp_info_add_jump_distance(WidPopup *w, Tpp t);
  void wid_tp_info_add_move_speed(WidPopup *w, Tpp t);
  void wid_tp_info_add_nutrition(WidPopup *w, Tpp t);
  void wid_tp_info_add_shove_strength(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_att(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_con(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_def(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_dex(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_int(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_luck(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_psi(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_str(WidPopup *w, Tpp t);
  void wid_tp_info_add_stat_thv(WidPopup *w, Tpp t);
  void wid_tp_info_clear_popup(void);
  void wid_tp_info_destroy_deferred(void);
  void wid_tp_info_destroy_immediate(void);
  // end sort marker2 }
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
