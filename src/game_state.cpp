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
#include "my_wid_thing_info.hpp"

void Game::change_state(int new_state)
{
  //
  // Check we are in the game loop. If not, do the reset later.
  //
  if (new_state == STATE_NORMAL) {
    if (! pcg_random_allowed) {
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

  switch (new_state) {
    case STATE_NORMAL:
      // backtrace_dump();
      LOG("State changing to STATE_NORMAL");
      wid_thing_info_fini("change state");
      wid_collect_destroy();
      wid_enchant_destroy();
      wid_choose_skill_destroy();
      wid_load_destroy();
      wid_save_destroy();
      wid_inventory_fini();
      wid_quit_destroy();
      LOG("State changed to STATE_NORMAL");
      break;
    case STATE_OPTIONS_FOR_ITEM_MENU: LOG("State changed to STATE_OPTIONS_FOR_ITEM_MENU"); break;
    case STATE_INVENTORY: // Currently managing inventory
      LOG("State changed to STATE_INVENTORY");
      break;
    case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      LOG("State changing to STATE_COLLECTING_ITEMS");
      wid_thing_info_fini("change state");
      wid_collect_destroy();
      LOG("State changed to STATE_COLLECTING_ITEMS");
      break;
    case STATE_ENCHANTING_ITEMS:
      LOG("State changing to STATE_ENCHANTING_ITEMS");
      wid_enchant_destroy();
      LOG("State changed to STATE_ENCHANTING_ITEMS");
      break;
    case STATE_CHOOSING_SKILLS:
      LOG("State changing to STATE_CHOOSING_SKILLS");
      wid_choose_skill_destroy();
      LOG("State changed to STATE_CHOOSING_SKILLS");
      break;
    case STATE_CHOOSING_TARGET: // Looking to somewhere to throw at
      LOG("State changing to STATE_CHOOSING_TARGET");
      wid_thing_info_fini("change state");
      LOG("State changed to STATE_CHOOSING_TARGET");
      break;
    case STATE_LOAD_MENU:
    case STATE_SAVE_MENU:
    case STATE_QUIT_MENU: wid_thing_info_fini("change state"); break;
  }

  //
  // In case some cleanup above changed state
  //
  state = new_state;
  wid_actionbar_init();

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
          level->cursor->clear_move_path("State change");
        }
      }
      break;
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
