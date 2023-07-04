//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

//
// Periodic updates
//
void Level::update(void)
{
  dbg("Level update");
  TRACE_NO_INDENT();

  if (is_map_changed) {
    is_map_changed = false;
    update_map();
  }

  if (game->request_reset_state_change) {
    game->change_state(Game::STATE_NORMAL, "level update");
    game->unset_request_reset_state_change();
  }

  if (game->request_to_update_same_level) {
    game->unset_request_to_update_same_level();
    update_same_level();
  }
}

//
// Get the bounds. Needs to be a bit off-map for reflections.
//
void Level::display_map_set_bounds(void)
{
  TRACE_NO_INDENT();

  int border = MAP_BORDER_ROCK + 2;
  minx       = std::max(0, (int) map_at.x - border);
  maxx       = std::min(MAP_WIDTH, (int) minx + TILES_VISIBLE_ACROSS + (border * 2));

  miny = std::max(0, (int) map_at.y - border);
  maxy = std::min(MAP_HEIGHT, (int) miny + TILES_VISIBLE_DOWN + (border * 2));

  if (g_opt_ascii) {
    minx = map_at.x;
    miny = map_at.y;
  }

  map_tl = point(minx, miny);
  map_br = point(maxx, maxy);

  scroll_map_set_target();
  scroll_map();
}

bool Level::should_display_map(void)
{
  switch (game->state) {
    case Game::STATE_NORMAL : return true;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU : // Drop, throw etc and item
      return true;
    case Game::STATE_INVENTORY : // Currently managing inventory
      return true;
    case Game::STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      return true;
    case Game::STATE_ENCHANTING_ITEMS : // Upgrading items
      return true;
    case Game::STATE_CHOOSING_SKILLS : // Choosing skills
      return true;
    case Game::STATE_CHOOSING_SPELLS : // Choosing spells
      return true;
    case Game::STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      return true;
    case Game::STATE_CHOOSING_LEVEL : // Choosing the next level
      return false;
    case Game::STATE_KEYBOARD_MENU : // Keyboard optionds
      return false;
    case Game::STATE_LOAD_MENU : // Loading a game
      return false;
    case Game::STATE_SAVE_MENU : // Saving a game
      return false;
    case Game::STATE_QUIT_MENU : // Pondering quitting
      return false;
    default : err("Unhandled game state"); return false;
  }

  return false;
}
