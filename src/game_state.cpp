//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "my_wid_tp_info.hpp"

std::string gama_state_to_string(int state)
{
  switch (state) {
    case Game::STATE_NORMAL : return "NORMAL";
    case Game::STATE_INVENTORY : return "INVENTORY";
    case Game::STATE_COLLECTING_ITEMS : return "COLLECTING_ITEMS";
    case Game::STATE_ENCHANTING_ITEMS : return "ENCHANTING_ITEMS";
    case Game::STATE_CHOOSING_SKILLS : return "CHOOSING_SKILLS";
    case Game::STATE_CHOOSING_SPELLS : return "CHOOSING_SPELLS";
    case Game::STATE_CHOOSING_TARGET : return "CHOOSING_TARGET";
    case Game::STATE_CHOOSING_LEVEL : return "CHOOSING_LEVEL";
    case Game::STATE_KEYBOARD_MENU : return "KEYBOARD_MENU";
    case Game::STATE_LOAD_MENU : return "LOAD_MENU";
    case Game::STATE_SAVE_MENU : return "SAVE_MENU";
    case Game::STATE_QUIT_MENU : return "QUIT_MENU";
    default : ERR("Unhandled game state"); return "?";
  }
}

void Game::change_state(int new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  if (game->state == new_state) {
    return;
  }

  //
  // Check we are in the game loop. If not, do the reset later.
  //
  if (new_state == STATE_NORMAL) {
    if (! pcg_random_allowed) {
      LOG("Defer changing state to STATE_NORMAL");
      game->set_request_reset_state_change();
      return;
    }
  }

  //
  // Hide the cursor path if over a popup
  //
  if (wid_over) {
    if (game->level) {
      game->level->cursor_path_clear();
    }
  }

  auto old_state = state;

  //
  // Set here to stop recursion.
  //
  state = new_state;

  //
  // Why oh why change state
  //
  IF_DEBUG2
  {
    CON("Game state change: %s -> %s, reason %s", gama_state_to_string(old_state).c_str(),
        gama_state_to_string(new_state).c_str(), why.c_str());
    backtrace_dump();
  }
  else
  {
    DBG("Game state change: %s -> %s, reason %s", gama_state_to_string(old_state).c_str(),
        gama_state_to_string(new_state).c_str(), why.c_str());
  }
  TRACE_AND_INDENT();

  //
  // Actions for the new state
  //
  switch (new_state) {
    case STATE_NORMAL :
      wid_thing_info_fini("change state");
      wid_tp_info_fini("change state");
      wid_collect_destroy();
      wid_enchant_destroy();
      wid_choose_skill_destroy();
      wid_choose_spell_destroy();
      wid_load_destroy();
      wid_save_destroy();
      wid_inventory_fini();
      wid_quit_destroy();
      wid_actionbar_init();
      break;
    case STATE_INVENTORY : // Currently managing inventory
      wid_actionbar_init();
      break;
    case STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      wid_thing_info_fini("change state");
      wid_tp_info_fini("change state");
      wid_collect_destroy();
      wid_actionbar_init();
      break;
    case STATE_ENCHANTING_ITEMS :
      wid_enchant_destroy();
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_SKILLS :
      wid_choose_skill_destroy();
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_SPELLS :
      wid_choose_spell_destroy();
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      wid_thing_info_fini("change state");
      wid_tp_info_fini("change state");
      wid_actionbar_init();
      break;
    case STATE_CHOOSING_LEVEL : // Looking to change level
      wid_actionbar_close_all_popups();
      wid_hide(wid_topcon_window);
      wid_rightbar_fini();
      wid_leftbar_fini();
      wid_actionbar_fini();
      wid_thing_info_fini("change state");
      wid_tp_info_fini("change state");
      request_to_remake_rightbar  = false;
      request_to_remake_inventory = false;
      request_to_remake_actionbar = false;
      request_to_remake_skillbox  = false;
      request_to_remake_spellbox  = false;
      request_to_remake_debuffbox = false;
      request_to_remake_buffbox   = false;
      break;
    case STATE_LOAD_MENU :
    case STATE_KEYBOARD_MENU :
    case STATE_SAVE_MENU :
    case STATE_QUIT_MENU :
      wid_thing_info_fini("change state");
      wid_tp_info_fini("change state");
      break;
  }

  //
  // In case some cleanup above changed state
  //
  state = new_state;

  request_destination_ok = false;
  request_to_throw_item  = nullptr;
  if (request_to_use_item) {
    if (request_to_use_item->is_spell()) {
      if (level->player) {
        level->player->spell_deactivate(request_to_use_item);
      }
    }
  }
  request_to_use_item = nullptr;

  switch (old_state) {
    case STATE_NORMAL :
      if (pcg_random_allowed) {
        if (level) {
          level->cursor_recreate();
          if (level->cursor) {
            level->cursor->clear_move_path("Game state change");
          }
        }
      }
      break;
    case STATE_INVENTORY :        // Currently managing inventory
    case STATE_COLLECTING_ITEMS : // Collecting en masse from the level
    case STATE_ENCHANTING_ITEMS :
    case STATE_CHOOSING_SKILLS :
    case STATE_CHOOSING_SPELLS :
    case STATE_CHOOSING_LEVEL : break;
    case STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
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
