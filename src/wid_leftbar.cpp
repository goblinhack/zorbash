//
// Copyleft goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_string.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"
// REMOVED #include "my_ui.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_popup.hpp"

static bool wid_leftbar_create(void);

Widp wid_leftbar {};

static WidPopup *wid_leftbar_popup;

void wid_leftbar_fini(void)
{
  TRACE_NO_INDENT();
  wid_destroy(&wid_leftbar);

  delete wid_leftbar_popup;
  wid_leftbar_popup = nullptr;

  auto level = game->get_current_level();
  if (level) {
    level->wid_leftbar_things = {};
  }
}

bool wid_leftbar_init(void)
{
  TRACE_NO_INDENT();
  return wid_leftbar_create();
}

bool wid_leftbar_create(void)
{
  TRACE_NO_INDENT();
  wid_leftbar_fini();

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }

  level->wid_leftbar_things = {};

  auto player = level->player;
  if (! player) {
    return false;
  }

  switch (game->state) {
    case Game::STATE_NORMAL: break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU: // Drop, throw etc and item
      return false;
    case Game::STATE_INVENTORY: // Currently managing inventory
      return false;
    case Game::STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      return false;
    case Game::STATE_ENCHANTING_ITEMS: // Upgrading items
      return false;
    case Game::STATE_CHOOSING_SKILLS: // Choosing skills
      return false;
    case Game::STATE_CHOOSING_TARGET: // Looking to somewhere to throw at
      break;
    case Game::STATE_CHOOSING_LEVEL: // Choosing the next level
      return false;
    case Game::STATE_KEYBOARD_MENU: // Keyboard optionds
      return false;
    case Game::STATE_LOAD_MENU: // Loading a game
      return false;
    case Game::STATE_SAVE_MENU: // Saving a game
      return false;
    case Game::STATE_QUIT_MENU: // Pondering quitting
      return false;
    default: ERR("Unhandled game state"); return false;
  }

  return wid_leftbar_display_create();
}
