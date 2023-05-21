//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

void Game::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();

  //
  // Game is afoot.
  //
  started = {};

  //
  // Things in this tick are still moving. Only really used in pixel art mode.
  //
  things_are_moving = {};

  //
  // Player ready to see console messages
  //
  player_is_ready_for_messages = {};

  //
  // Something has requested a game tick.
  //
  tick_requested = "";

  //
  // Which tile in the mini map are we over.
  //
  map_mini_over = point(-1, -1);

  //
  // How many moves the player has made
  //
  player_move_count_in_this_snapshot = {};

  //
  // Game tick progression.
  //
  tick_completed = 1;
  tick_current   = 1;

  //
  // Temporary. Robot mode settings.
  //
  robot_mode                = {};
  robot_mode_requested      = {};
  robot_mode_tick_requested = {};

  //
  // Temporary. Player wants to play.
  //
  player_requested_to_start_the_game = {};

  //
  // Temporary. Used for timesteps within a game tick for smooth thing movement.
  //
  tick_dt = {};

  //
  // Temporary. This is used to try and speed up animations if in the midst of a slime storm
  //
  tick_current_is_too_slow = {};
  prev_tick_was_too_slow   = {};

  //
  // Temporary. Is the selected position ok for throwing?
  //
  request_destination_ok = {};

  //
  // Temporary. Used by the robot to change levels
  //
  request_to_choose_level = {};

  // begin sort marker3 {
  currently_saving_snapshot                       = {};
  request_player_move_down                        = {};
  request_player_move_left                        = {};
  request_player_move_right                       = {};
  request_player_move_up                          = {};
  request_player_to_ascend_level                  = {};
  request_player_to_descend_level                 = {};
  request_player_to_wait_or_collect               = {};
  request_recreate_cursor_path                    = {};
  request_reset_state_change                      = {};
  request_to_remake_actionbar                     = {};
  request_to_remake_buffbox                       = {};
  request_to_remake_debuffbox                     = {};
  request_to_remake_inventory                     = {};
  request_to_remake_rightbar                      = {};
  request_to_remake_skillbox                      = {};
  request_to_save_snapshot                        = {};
  request_to_toggle_gfx                           = {};
  request_to_update_inventory_with_thing_over     = {};
  request_to_update_inventory_with_thing_selected = {};
  request_to_update_same_level                    = {};
  // end sort marker3 }

  //
  // When the thing info was requested to be destroyed.
  //
  request_destroy_thing_info = {}; // Timestamp
  request_destroy_tp_info    = {}; // Timestamp

  //
  // When the player pressed some keys.
  //
  request_player_move = {};

  //
  // Temporary. Current thing being described in detail on screen.
  //
  current_wid_thing_info = {};
  current_wid_tp_info    = {};

  //
  // Which inventory items are we over.
  //
  request_inventory_thing_over     = {};
  request_inventory_thing_selected = {};

  //
  // Projectile or laser we're firing
  //
  request_to_use_item = {};

  //
  // Temporary. Make sure to update thing_fini.cpp to remove these pointers
  //
  request_to_throw_item = {}; // What we are throwing.

  //
  // Temporary list of popups.
  //
  popups.clear();

  //
  // Temporary. An item being moved between bags
  //
  in_transit_item = {};

  //
  // Temporary. All bags open.
  //
  bags = {};

  //
  // Temporary. Last cursor path shown.
  //
  cursor_move_path = {};
  cursor_move_end  = {};
  cursor_moved     = {};

  //
  // Temporary. Dampens mouse clicks
  //
  last_mouse_down = {};
  last_pause      = {};

  //
  // When the last tick started. Used for looking at spikes in time.
  //
  tick_begin_ms      = {};
  tick_begin_game_ms = {};

  //
  // Game is ending and levels are being destroyed.
  //
  is_being_destroyed = true;

  TRACE_NO_INDENT();
  config.fini();

  TRACE_NO_INDENT();
  world.fini();

  is_being_destroyed = false;
}
