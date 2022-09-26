//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::descend_sewer_tick(void)
{
  if (! level->is_descend_sewer(curr_at.x, curr_at.y)) {
    return false;
  }

  dbg("Descend sewer tick");
  TRACE_AND_INDENT();

  if (game->request_player_to_descend_level) {
    //
    // User has pressed a button, forcing the change
    //
  } else if (game->tick_current - tick_last_level_change() <= 1) {
    if (is_player()) {
      dbg("Location check, descend, no too soon");
    }

    return false;
  } else if (game->tick_current - tick_last_i_attacked() <= 1) {
    //
    // If this is the robot and we attack something next to a sewer, don't automatically descend.
    //
    if (is_player()) {
      dbg("Location check, descend, no busy attacking");
    }

    return false;
  }

  if (is_player()) {
    if (level->world_at.z & 1) {
      dbg("Descending sewer");
      if (! g_opt_ascii) {
        level->ts_fade_out_begin = time_ms_cached();
        level->fbo_light         = sdl_fbo_save(FBO_PIXELART_FULLMAP_LIGHT);
      }
      is_waiting_to_descend_sewer = true;
      move_finish();
      dbg("Descend sewer on move finish");
      return true;
    }
  } else {
    //
    // Not sure if monsts should do this as they crawl out of sewers
    //
    dbg("ThingInfo cannot descend sewer");
    return false;
  }

  dbg("Cannot descend sewer");
  return false;
}

bool Thing::descend_sewer(void)
{
  TRACE_NO_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_leave_level_has_completed_fall ||
      is_waiting_to_ascend_dungeon || is_waiting_to_ascend_sewer || is_jumping) {
    dbg("Descend sewer, no");
    return false;
  }

  dbg("Descend sewer");
  TRACE_AND_INDENT();

  if (! maybe_infop()) {
    dbg("Descend sewer; cannot descend, no infop");
    return false;
  }

  auto player = level->player;
  if (is_monst()) {
    if (player) {
      //
      // Don't descend if player is on the same level
      //
      dbg("Descend sewer; no, player is on same level");
      return false;
    }
  }

  auto next_level = level->world_at + point3d(0, 0, 1);

  if (next_level.z >= LEVELS_DEEP) {
    fall_into_the_void();
    dbg("Descend sewer; no, fell off the end reality");
    return false;
  }

  dbg("Is trying to descend to the sewer");
  auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
  if (! l) {
    if (! game->init_level(next_level, level->grid_at + point(0, 1), level->difficulty_depth + 1,
                           level->dungeon_walk_order_level_no + 1)) {
      if (is_player()) {
        msg("The sewer is permanently blocked!");
      }
      return false;
    }

    l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (! l) {
      err("No level");
      return false;
    }
  }

  if (is_player()) {
    game->current_level = next_level;
  }

  int x = player->curr_at.x;
  int y = player->curr_at.y;

  if (is_player()) {
    game->level = l;
    msg("You descend into the sewer. Why though?");
  }

  dbg("Move to next level sewer entrance");
  is_changing_level = true;

  level_change(l);
  tick_last_level_change_set(game->tick_current);
  move_to_immediately(point(x, y));
  move_carried_items_immediately();
  if (is_player()) {
    l->player = this;
    l->scroll_map_to_player();
    l->update_new_level();
    //
    // Make sure all monsts on the new level are at the
    // same tick or they will get lots of free attacks
    //
    l->update_all_ticks();
  }

  move_finish();
  interpolated_at_set(make_fpoint(curr_at));
  update_interpolated_position();
  location_check_me();
  update_light();

  if (is_player() && level->cursor) {
    level->cursor->move_to_immediately(curr_at);
  }

  is_changing_level = false;
  dbg("Moved to next level sewer");
  if (is_player()) {
    level->ts_fade_in_begin = time_ms_cached();
    level->update_new_level();

    if (game->robot_mode) {
      game->tick_begin("Begin exploring the new level");
    }
  }

  return true;
}
