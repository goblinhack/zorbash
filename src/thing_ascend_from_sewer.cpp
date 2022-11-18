//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

bool Thing::ascend_sewer_tick(void)
{
  if (! level->is_ascend_sewer(curr_at.x, curr_at.y)) {
    return false;
  }

  dbg("Ascend sewer tick");
  TRACE_AND_INDENT();

  if (game->request_player_to_ascend_level) {
    //
    // User has pressed a button, forcing the change
    //
  } else if (game->tick_current - tick_last_level_change() <= 1) {
    if (is_player()) {
      dbg("Location check, ascend, no too soon");
    }

    return false;
  }

  if (is_player()) {
    if (! g_opt_ascii) {
      level->ts_fade_out_begin = time_ms_cached();
      level->fbo_light         = sdl_fbo_save(FBO_PIXELART_FULLMAP_LIGHT);
    }
    is_waiting_to_ascend_sewer = true;
    return true;
  }
  return ascend_sewer();

  return false;
}

bool Thing::ascend_sewer(void)
{
  if (is_changing_level || is_hidden || is_falling || is_waiting_to_descend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_leave_level_has_completed_fall || is_jumping) {
    dbg("Ascend sewer; no");
    return false;
  }

  if (! maybe_infop()) {
    return false;
  }

  dbg("Ascend sewer");
  TRACE_AND_INDENT();

  auto next_level = level->world_at + point3d(0, 0, -1);

  auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
  if (! l) {
    if (is_player()) {
      msg("The entrance is permanently blocked!");
    }
    return false;
  }

  if (is_player()) {
    game->current_level = next_level;
  }

  int x = curr_at.x;
  int y = curr_at.y;

  if (is_player()) {
    game->level = l;
    msg("You ascend out of the wriggling filthy sewer.");
  }

  dbg("Move to previous level exit");
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
    // Make sure all monsters on the new level are at the
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
  dbg("Moved to previous level sewer entrance");
  if (is_player()) {
    level->ts_fade_in_begin = time_ms_cached();
    level->update_new_level();

    if (game->robot_mode) {
      game->tick_begin("Begin exploring the new level");
    }
  }

  return true;
}
