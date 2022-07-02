//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

static std::string state_to_string(int state)
{
  switch (state) {
    case Game::STATE_NORMAL: return "NORMAL";
    case Game::STATE_OPTIONS_FOR_ITEM_MENU: return "OPTIONS_FOR_ITEM_MENU";
    case Game::STATE_INVENTORY: return "INVENTORY";
    case Game::STATE_COLLECTING_ITEMS: return "COLLECTING_ITEMS";
    case Game::STATE_ENCHANTING_ITEMS: return "ENCHANTING_ITEMS";
    case Game::STATE_CHOOSING_SKILLS: return "CHOOSING_SKILLS";
    case Game::STATE_CHOOSING_TARGET: return "CHOOSING_TARGET";
    case Game::STATE_CHOOSING_LEVEL: return "CHOOSING_LEVEL";
    case Game::STATE_KEYBOARD_MENU: return "KEYBOARD_MENU";
    case Game::STATE_LOAD_MENU: return "LOAD_MENU";
    case Game::STATE_SAVE_MENU: return "SAVE_MENU";
    case Game::STATE_QUIT_MENU: return "QUIT_MENU";
    default: ERR("Unhandled game state"); return "?";
  }
}

void Game::change_state(int new_state)
{
  //
  // Check we are in the game loop. If not, do the reset later.
  //
  if (new_state == STATE_NORMAL) {
    if (! pcg_random_allowed) {
      CON("Defer changing state to STATE_NORMAL");
      game->request_reset_state = true;
      return;
    }
  }

  if (wid_over) {
    if (game->level) {
      game->level->cursor_path_clear();
    }
  }

  if (game->state == new_state) {
    return;
  }
  TRACE_AND_INDENT();
  auto old_state = state;

  //
  // Set here to stop recursion.
  //
  state = new_state;

  CON("Game state change: %s -> %s", state_to_string(old_state).c_str(), state_to_string(new_state).c_str());
  switch (new_state) {
    case STATE_NORMAL:
      // backtrace_dump();
      wid_thing_info_fini("change state");
      wid_collect_destroy();
      wid_enchant_destroy();
      wid_choose_skill_destroy();
      wid_load_destroy();
      wid_save_destroy();
      wid_inventory_fini();
      wid_quit_destroy();
      wid_actionbar_init();
      break;
    case STATE_OPTIONS_FOR_ITEM_MENU: break;
    case STATE_INVENTORY: // Currently managing inventory
      wid_actionbar_init();
      break;
    case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      wid_thing_info_fini("change state");
      wid_collect_destroy();
      wid_actionbar_init();
      break;
    case STATE_ENCHANTING_ITEMS:
      wid_enchant_destroy();
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_SKILLS:
      wid_choose_skill_destroy();
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_TARGET: // Looking to somewhere to throw at
      wid_thing_info_fini("change state");
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_LEVEL: // Looking to change level
      wid_actionbar_close_all_popups();
      wid_hide(wid_topcon_window);
      wid_rightbar_fini();
      wid_leftbar_fini();
      wid_actionbar_fini();
      wid_thing_info_fini("change state");
      request_remake_rightbar  = false;
      request_remake_inventory = false;
      request_remake_actionbar = false;
      request_remake_skillbox  = false;
      request_remake_debuffbox = false;
      request_remake_buffbox   = false;
      request_remake_rightbar  = false;
      break;
    case STATE_LOAD_MENU:
    case STATE_KEYBOARD_MENU:
    case STATE_SAVE_MENU:
    case STATE_QUIT_MENU: wid_thing_info_fini("change state"); break;
  }

  //
  // In case some cleanup above changed state
  //
  state = new_state;

  request_destination_ok = false;
  request_to_throw_item  = nullptr;
  request_to_use_item    = nullptr;

  switch (old_state) {
    case STATE_NORMAL:
    case STATE_INVENTORY:        // Currently managing inventory
    case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
    case STATE_ENCHANTING_ITEMS:
    case STATE_CHOOSING_SKILLS:
      if (level) {
        level->cursor_recreate();
        if (level->cursor) {
          level->cursor->clear_move_path("Game state change");
        }
      }
      break;
    case STATE_CHOOSING_LEVEL:
    case STATE_CHOOSING_TARGET: // Looking to somewhere to throw at
      //
      // Don't create the cursor right after selecting. Wait until
      // we move again.
      //
      if (level) {
        level->cursor_recreate();
        level->cursor_path_clear();
      }
      break;
  }
}
