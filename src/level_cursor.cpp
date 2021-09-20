//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_thing_info.h"
#include "my_wid_inventory.h"
#include "my_wid_bag.h"
#include "my_globals.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"
#include "my_sdl.h"
//#include "my_traceback.h"

void Level::cursor_check_if_scroll_needed (void)
{_
  //
  // Not sure why I have this and what it does :)
  //
  if (map_follow_player) {
    if (cursor) {
      if (player) {
        auto d = distance(player->mid_at, cursor->mid_at);
        if (d > std::min(TILES_ACROSS, TILES_DOWN)) {
          cursor->move(player->mid_at);
        }
      }
    }
  }
}

//
// Move the cursor to whatever thing it is now over
//
void Level::cursor_move (void)
{_
  if (game->robot_mode) {
    return;
  }

  if (is_mouse_over_any_bag()) {
    return;
  }

  if (wid_find_under_mouse()) {
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
    float z = GAME_MOST_ZOOMED_IN - game->config.game_pix_zoom;
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
  if (timestamp_dungeon_created &&
    time_have_x_tenths_passed_since(2, timestamp_dungeon_created)) {
    mouse_at = mouse_tick;
    if (mouse_at > mouse_old) {
      mouse_old = mouse_at;
      cursor_found = false;
    }
  } else {
    mouse_at = mouse_tick;
    mouse_old = mouse_at;
    map_follow_player = true;
  }

  if (cursor) {_
    verify(cursor);
    if (cursor_at != cursor_old) {
      cursor_old = cursor_at;
      cursor->move(cursor_at);
      cursor_recreate();

      //
      // If we've moved, likely we want to look at something else
      // But only do this if it is the result of a real mouse move
      // and not just the level auto scrolling.
      //
      if (time_have_x_tenths_passed_since(10, timestamp_dungeon_created)) {
        if (!time_have_x_tenths_passed_since(10, wid_last_mouse_motion)) {
          wid_thing_info_fini();
          cursor_describe();
        }
      }
    }
  }
}

void Level::cursor_recreate (void)
{_
//traceback_dump();
  //
  // Player might be on another level
  //
  if (!cursor) {
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

  auto mid_at = cursor->mid_at;

  auto what = game->request_to_throw_item;
  if (!what) {
    what = game->request_to_fire_item;
  }

  cursor->dead("update");
  if (what && (game->state == Game::STATE_CHOOSING_TARGET)) {
    bool too_far = false;
    auto dist = DISTANCE(player->mid_at.x, player->mid_at.y,
               mid_at.x, mid_at.y);
    if (what->get_throw_distance()) {
      too_far = dist > player->get_throw_distance();
    } else if (what->range_max()) {
      too_far = dist > what->range_max();
    }

    if (too_far) {
      cursor = thing_new("cursor_select_fail", mid_at);
    } else {
      cursor = thing_new("cursor_select", mid_at);
    }
  } else {
    cursor = thing_new("cursor", mid_at);
  }

  //
  // Why hide it? When scrolling to a new position it's nice to see
  // the cursor pop up,
  //
  //cursor->hide();
  cursor_path_create();
}
