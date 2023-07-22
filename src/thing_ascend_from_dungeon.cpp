//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"

bool Thing::ascend_dungeon_tick(void)
{
  if (! level->is_ascend_dungeon(curr_at.x, curr_at.y)) { return false; }

  dbg("Ascend dungeon tick");
  TRACE_AND_INDENT();

  if (game->request_player_to_ascend_level) {
    //
    // User has pressed a button, forcing the change
    //
  } else if (game->tick_current - tick_last_level_change() <= 1) {
    if (is_player()) { dbg("Location check, ascend, no too soon"); }

    return false;
  }

  if (is_player()) {
    //
    // Robot only goes down
    //
    if (game->robot_mode) { return false; }
    dbg("Location check, ascend");
  }

  if (level->dungeon_walk_order_level_no > 1) {
    if (is_player()) {
      if (! g_opt_ascii) {
        level->ts_fade_out_begin = time_ms_cached();
        level->fbo_light         = sdl_fbo_save(FBO_PIXELART_FULLMAP_LIGHT);
      }
      is_waiting_to_ascend_dungeon = true;

      if (is_player()) { dbg("Location check, is now waiting to ascend"); }
      return true;
    }
    return ascend_dungeon();
  }

  if (is_player()) { msg("The exit is blocked. You are stuck here!"); }

  return false;
}

bool Thing::ascend_dungeon(bool force, point3d next_level)
{
  TRACE_NO_INDENT();

  if (! force) {
    if (is_changing_level || is_hidden || is_falling || is_waiting_to_descend_dungeon || is_waiting_to_descend_sewer
        || is_waiting_to_leave_level_has_completed_fall || is_jumping) {
      dbg("Ascend dungeon, no");
      return false;
    }
  }

  if (! maybe_infop()) { return false; }

  dbg("Ascend dungeon");
  TRACE_AND_INDENT();

  if (! force) {
    if (is_player()) {
      game->wid_choose_next_dungeons(level, true, false);
      return true;
    }
  }

  if (next_level == point3d(0, 0, 0)) { next_level = level->world_at + point3d(0, 0, -2); }

  auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
  if (! l) {
    if (is_player()) { msg("The entrance is permanently blocked!"); }
    return false;
  }

  if (is_player()) { game->current_level = next_level; }

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (l->is_descend_dungeon(x, y)) {
        if (is_player()) {
          game->level = l;
          msg("You ascend.");
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

        if (is_player() && level->cursor) { level->cursor->move_to_immediately(curr_at); }

        is_changing_level = false;
        dbg("Moved to previous level exit");
        if (is_player()) {
          level->ts_fade_in_begin = time_ms_cached();
          level->update_new_level();

          if (game->robot_mode) { game->tick_begin("Begin exploring the new level"); }
        }
        return true;
      }
    }
  }

  return false;
}
