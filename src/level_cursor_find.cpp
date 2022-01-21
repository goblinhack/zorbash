//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_thing_info.hpp"

void Level::cursor_find_on_visible_things(const int16_t minx, const int16_t miny, const int16_t maxx,
                                          const int16_t maxy)
{
  TRACE_AND_INDENT();
  if ((game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_ENCHANTING_ITEMS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_QUIT_MENU) || (game->state == Game::STATE_CHOOSING_SKILLS)) {
    return;
  }

  if (wid_find_under_mouse()) {
    return;
  }

  dbg3("Cursor find on visible things");
  TRACE_AND_INDENT();
  if ((game->map_mini_over.x > 0) && (game->map_mini_over.y > 0)) {
    //
    // Don't move onto lava unless double click
    //
    auto to = game->map_mini_over;
    if (! wid_mouse_two_clicks) {
      if (cursor) {
        TRACE_AND_INDENT();
        FOR_ALL_THINGS(this, t, to.x, to.y)
        {
          if (t->is_cursor_can_hover_over_x2_click()) {
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
  game->wid_thing_info_destroy_deferred();
}
