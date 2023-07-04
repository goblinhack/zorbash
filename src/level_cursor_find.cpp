//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_warning.hpp"

void Level::cursor_find_on_visible_things(const int16_t minx, const int16_t miny, const int16_t maxx,
                                          const int16_t maxy)
{
  TRACE_NO_INDENT();

  //
  // If we are over the left bar looking at a thing and then move the mouse, do not
  // try to find the cursor as that then removes the popup.
  //
  if (wid_over) {
    return;
  }

  switch (game->state) {
    case Game::STATE_NORMAL : break;
    case Game::STATE_OPTIONS_FOR_ITEM_MENU : // Drop, throw etc and item
      return;
    case Game::STATE_INVENTORY : // Currently managing inventory
      return;
    case Game::STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      return;
    case Game::STATE_ENCHANTING_ITEMS : // Upgrading items
      return;
    case Game::STATE_CHOOSING_SKILLS : // Choosing skills
      return;
    case Game::STATE_CHOOSING_SPELLS : // Choosing spells
      return;
    case Game::STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      break;
    case Game::STATE_CHOOSING_LEVEL : // Choosing the next level
      return;
    case Game::STATE_KEYBOARD_MENU : // Keyboard optionds
      return;
    case Game::STATE_LOAD_MENU : // Loading a game
      return;
    case Game::STATE_SAVE_MENU : // Saving a game
      return;
    case Game::STATE_QUIT_MENU : // Pondering quitting
      return;
    default : err("Unhandled game state"); return;
  }

  if (wid_find_under_mouse()) {
    return;
  }

  //
  // If move confirmation is present, do not recreate the cursor
  //
  if (wid_warning_window) {
    return;
  }

  dbg3("Cursor find on visible things");
  TRACE_AND_INDENT();
  pcg_random_allowed++;

  if (! g_opt_ascii && ((game->map_mini_over.x > 0) && (game->map_mini_over.y > 0))) {
    //
    // Don't move onto lava unless double click
    //
    auto to = game->map_mini_over;
    if (! wid_mouse_two_clicks) {
      if (cursor) {
        FOR_ALL_NON_INTERNAL_THINGS(this, t, to.x, to.y)
        {
          if (t->is_cursor_can_hover_over_needs_confirm()) {
            goto done;
          }
        }
        FOR_ALL_THINGS_END()
      }
    }
    if (cursor) {
      cursor->curr_at = to;
    }
  } else {
    //
    // What tile are we over?
    //
    auto old        = is_cursor_found;
    is_cursor_found = false;
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        FOR_ALL_GRID_THINGS(this, t, x, y)
        {
          t->cursor_hover_over_check();
          if (is_cursor_found) {
            goto done;
          }
        }
        FOR_ALL_THINGS_END();
      }
    }
    is_cursor_found = old;
  }

done:
  pcg_random_allowed--;
  return;
}
