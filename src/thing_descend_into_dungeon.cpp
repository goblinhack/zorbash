//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"

bool Thing::descend_dungeon_tick(void)
{
  if (! level->is_descend_dungeon(curr_at.x, curr_at.y)) {
    return false;
  }

  dbg("Descend dungeon tick");
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
  }

  if (is_player()) {
    if (! g_opt_ascii) {
      level->ts_fade_out_begin = time_ms_cached();
      level->fbo_light         = sdl_fbo_save(FBO_PIXELART_FULLMAP_LIGHT);
    }
    is_waiting_to_descend_dungeon = true;
    dbg("Player is waiting to descend");
    return true;
  }
  return descend_dungeon();
}

bool Thing::descend_dungeon(bool force, point3d next_level)
{
  TRACE_NO_INDENT();

  if (! force) {
    if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer
        || is_waiting_to_leave_level_has_completed_fall || is_jumping) {
      dbg("Descend dungeon, no");
      return false;
    }
  }

  if (! maybe_infop()) {
    return false;
  }

  dbg("Descend dungeon");
  TRACE_AND_INDENT();

  if (is_monst()) {
    if (level->player) {
      //
      // Don't descend if player is on the same level
      //
      return false;
    }
  }

  if (! force) {
    if (is_player()) {
      game->wid_choose_next_dungeons(level, false, true);
      return true;
    }
  }

  if (next_level == point3d(0, 0, 0)) {
    next_level = level->world_at + point3d(0, 0, 2);
  }

  if (next_level.z >= LEVELS_DEEP) {
    fall_into_the_void();
    return false;
  }

  dbg("Is trying to descend");
  auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
  if (! l) {
    if (! game->init_level(next_level, level->grid_at + point(0, 1), level->difficulty_depth,
                           level->dungeon_walk_order_level_no + 1)) {
      if (is_player()) {
        msg("The exit is permanently blocked!");
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

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (l->is_ascend_dungeon(x, y)) {
        if (is_player()) {
          game->level = l;
          msg("You bravely descend.");
        }

        dbg("Move to next level entrance");
        is_changing_level = true;

        //
        // Need to do this prior to level change as level_change will update the lighting; and we don't want to do
        // that at the old position.
        //
        dbg("Level change move to destination");
        move_to_immediately(point(x, y));

        dbg("Level change and enter");
        level_change(l);
        tick_last_level_change_set(game->tick_current);

        dbg("Level change move carried items");
        move_carried_items_immediately();

        if (is_player()) {
          l->player = this;
          dbg("Level change scroll map");
          l->scroll_map_to_player();
          l->update_new_level();
          //
          // Make sure all monsters on the new level are at the
          // same tick or they will get lots of free attacks
          //
          l->update_all_ticks();
        }

        dbg("Level change finish move");
        move_finish();

        dbg("Level change update interpolated position");
        interpolated_at_set(make_fpoint(curr_at));
        update_interpolated_position();

        dbg("Level change location check");
        location_check_me();
        update_light();

        if (is_player() && level->cursor) {
          level->cursor->move_to_immediately(curr_at);
        }

        is_changing_level = false;
        dbg("Moved to next level entrance");
        if (is_player()) {
          level->ts_fade_in_begin = time_ms_cached();
          level->update_new_level();

          if (game->robot_mode) {
            game->tick_begin("Begin exploring the new level");
          }
        }

        //
        // Followers, follow you! Not sure if they should ascend also.
        // I'm also not sure if we should preserver the beholdenship or release them.
        // Currently they are released and as magic resets each level, you need to redo the spell.
        //
        if (maybe_infop()) {
          if (infop()->followers.size()) {
            dbg("Move followers to next level");
            auto followers = infop()->followers;
            for (auto fid : followers) {
              auto f = game->thing_find(fid);
              if (f) {
                f->descend_dungeon(force, next_level);
              }
            }
          }
        }

        return true;
      }
    }
  }

  return false;
}
