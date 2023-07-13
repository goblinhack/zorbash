//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_thing.hpp"
#include "my_wid_bag.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_warning.hpp"

void Level::cursor_warp_check(void)
{
  TRACE_AND_INDENT();

  if (is_map_follow_player) {
    if (cursor) {
      if (player) {
        auto d = distance(player->curr_at, cursor->curr_at);
        if (d > std::min(TILES_VISIBLE_ACROSS, TILES_VISIBLE_DOWN)) {
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
  TRACE_NO_INDENT();

  if (is_mouse_over_any_bag()) {
    return;
  }

  if (wid_find_under_mouse()) {
    return;
  }

  if (game->robot_mode) {
    return;
  }

  if ((game->state != Game::STATE_NORMAL) && (game->state != Game::STATE_CHOOSING_TARGET)) {
    return;
  }

  if (wid_popup_exists()) {
    return;
  }

  if ((sdl.wheel_x != 0) || (sdl.wheel_y != 0)) {
    if (wid_find_under_mouse_when_scrolling()) {
      return;
    }

    float dx = -sdl.wheel_x;
    float dy = -sdl.wheel_y;

    //
    // Move faster when more zoomed out.
    //
    float z     = GAME_MOST_ZOOMED_IN - game->config.game_pix_zoom;
    float scale = pow(z + 1, 1.2);
    dx *= scale;
    dy *= scale;

    if (g_opt_ascii) {
      if (dx < 0) {
        dx = -1;
      } else if (dx > 0) {
        dx = 1;
      }
      if (dy < 0) {
        dy = -1;
      } else if (dy > 0) {
        dy = 1;
      }
    }

    if (g_opt_ascii) {
      map_at += fpoint(dx, dy);
      map_wanted_at = map_at;
      display_map_set_bounds();
    } else {
      map_wanted_at += fpoint(dx, dy);
    }
    // TOPCON("(%f,%f d %f,%f)", map_wanted_at.x, map_wanted_at.y, dx, dy);
    is_map_follow_player = false;
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
  if (ts_entered && time_have_x_tenths_passed_since(2, ts_entered)) {
    mouse_at = sdl.mouse_tick;
    if (mouse_at > mouse_old) {
      mouse_old       = mouse_at;
      is_cursor_found = false;
    }
  } else {
    mouse_at             = sdl.mouse_tick;
    mouse_old            = mouse_at;
    is_map_follow_player = true;
  }

  if (cursor) {
    TRACE_AND_INDENT();
    verify(MTYPE_THING, cursor);
    if ((cursor_at != cursor_old) || (cursor->curr_at != cursor_at)) {
      dbg("cursor move to %d,%d", cursor_at.x, cursor_at.y);

      cursor_old = cursor_at;
      cursor->move_to_immediately(cursor_at);

      TRACE_AND_INDENT();

      game->cursor_moved = true;

      cursor_recreate();
      wid_thing_info_fini("auto clear");
      cursor_describe();
    }
  }
}

void Level::cursor_recreate(point curr_at)
{
  dbg("Recreate cursor");
  TRACE_AND_INDENT();

  //
  // Player might be on another level
  //
  if (! player) {
    dbg("Recreate cursor; no player");
    return;
  }

  if (player->is_dead) {
    dbg("Recreate cursor; player dead");
    return;
  }

  //
  // If move confirmation is present, do not recreate the cursor
  //
  if (wid_warning_window) {
    return;
  }

  if (game->robot_mode) {
    return;
  }

  auto what = game->request_to_throw_item;
  if (! what) {
    what = game->request_to_use_item;
  }

  if (cursor) {
    if (curr_at == point(-1, -1)) {
      curr_at = cursor->curr_at;
    }
    cursor->dead("update");
  } else {
    curr_at = player->curr_at;
  }

  if (what && (game->state == Game::STATE_CHOOSING_TARGET)) {
    bool too_far = false;
    auto dist    = DISTANCE(player->curr_at.x, player->curr_at.y, curr_at.x, curr_at.y);

    if (player->distance_throw_get()) {
      too_far = dist > player->distance_throw_get();
    }

    if (what->range_max()) {
      too_far = too_far || dist > what->range_max();
    }

    if (too_far) {
      cursor                       = thing_new("cursor_select_fail", curr_at);
      game->request_destination_ok = false;
    } else {
      cursor                       = thing_new("cursor_select", curr_at);
      game->request_destination_ok = true;
    }
  } else {
    cursor                       = cursor_thing_new(curr_at);
    game->request_destination_ok = true;
  }

  //
  // Update the minimap for the new cursor location.
  //
  is_map_mini_valid = false;

  //
  // Why hide it? When scrolling to a new position it's nice to see the cursor pop up,
  //
  // cursor->hide();

  cursor_path_create(player);
}
