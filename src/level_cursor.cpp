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
//#include "my_backtrace.hpp"

void Level::cursor_check_if_scroll_needed(void)
{
  TRACE_AND_INDENT();
  //
  // Not sure why I have this and what it does :)
  //
  if (map_follow_player) {
    if (cursor) {
      if (player) {
        auto d = distance(player->curr_at, cursor->curr_at);
        if (d > std::min(TILES_ACROSS, TILES_DOWN)) {
          cursor->move_to_immediately(player->curr_at);
        }
      }
    }
  }
}

//
// Move the cursor to whatever thing it is now over
//
void Level::cursor_move(void)
{
  TRACE_AND_INDENT();
  if (game->robot_mode) {
    return;
  }

  if (is_mouse_over_any_bag()) {
    return;
  }

  if (wid_find_under_mouse()) {
    return;
  }

  if ((game->state != Game::STATE_NORMAL) && (game->state != Game::STATE_CHOOSING_TARGET)) {
    return;
  }

  if (wid_popup_exists()) {
    return;
  }

  if ((wheel_x != 0) || (wheel_y != 0)) {
    if (wid_find_under_mouse_when_scrolling()) {
      return;
    }

    float dx = -wheel_x;
    float dy = -wheel_y;

    //
    // Move faster when more zoomed out.
    //
    float z     = GAME_MOST_ZOOMED_IN - game->config.game_pix_zoom;
    float scale = pow(z + 1, 1.2);
    dx *= scale;
    dy *= scale;

    map_wanted_at += fpoint(dx, dy);
    map_follow_player = false;
    return;
  }

  //
  // Check for dead after scrolling so we can look around when dead
  //
  if (player && player->is_dead) {
    return;
  }

  //
  // Dampen mouse moves at level start
  //
  if (ts_dungeon_created && time_have_x_tenths_passed_since(2, ts_dungeon_created)) {
    mouse_at = mouse_tick;
    if (mouse_at > mouse_old) {
      mouse_old    = mouse_at;
      cursor_found = false;
    }
  } else {
    mouse_at          = mouse_tick;
    mouse_old         = mouse_at;
    map_follow_player = true;
  }

  if (cursor) {
    TRACE_AND_INDENT();
    verify(MTYPE_THING, cursor);
    if (cursor_at != cursor_old) {
      cursor_old = cursor_at;
      cursor->move_to_immediately(cursor_at);
      cursor_recreate();

      //
      // If we've moved, likely we want to look at something else
      // But only do this if it is the result of a real mouse move
      // and not just the level auto scrolling.
      //
      if (time_have_x_tenths_passed_since(10, ts_dungeon_created)) {
        if (! time_have_x_tenths_passed_since(10, wid_last_mouse_motion)) {
          wid_thing_info_fini();
          cursor_describe();
        }
      }
    }
  }
}

void Level::cursor_recreate(void)
{
  TRACE_AND_INDENT();
  // backtrace_dump();
  //
  // Player might be on another level
  //
  if (! cursor) {
    return;
  }

  //
  // Distracting when in robot mode
  //
  if (game->robot_mode) {
    return;
  }

  if (player && player->is_dead) {
    return;
  }

  auto curr_at = cursor->curr_at;

  auto what = game->request_to_throw_item;
  if (! what) {
    what = game->request_to_fire_item;
  }

  cursor->dead("update");
  if (what && (game->state == Game::STATE_CHOOSING_TARGET)) {
    bool too_far = false;
    auto dist    = DISTANCE(player->curr_at.x, player->curr_at.y, curr_at.x, curr_at.y);

    if (player->get_distance_throw()) {
      too_far = dist > player->get_distance_throw();
    }

    if (what->range_max()) {
      too_far = too_far || dist > what->range_max();
    }

    if (too_far) {
      cursor = thing_new("cursor_select_fail", curr_at);
    } else {
      cursor = thing_new("cursor_select", curr_at);
    }
  } else {
    cursor = thing_new("cursor", curr_at);
  }

  //
  // Why hide it? When scrolling to a new position it's nice to see
  // the cursor pop up,
  //
  // cursor->hide();
  cursor_path_create();
}
