//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_sdl.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

bool Thing::descend_dungeon_tick(void)
{
  TRACE_AND_INDENT();
  if (! is_able_to_change_levels()) {
    return false;
  }

  if (! level->is_descend_dungeon(curr_at.x, curr_at.y)) {
    return false;
  }

  if (is_player()) {
    dbg("Location check, descend");
  }

#if 0
  if (get_tick() - get_tick_last_level_change() < 1) {
    if (is_player()) {
      dbg("Location check, descend, no too soon");
    }
    return false;
  }
#endif

  if (is_player()) {
    level->ts_fade_out_begin      = time_get_time_ms_cached();
    level->fbo_light              = sdl_fbo_save(FBO_FULLMAP_LIGHT);
    is_waiting_to_descend_dungeon = true;
    return true;
  } else {
    return descend_dungeon();
  }
}

bool Thing::descend_dungeon(void)
{
  TRACE_AND_INDENT();
  dbg("Descend dungeon");
  TRACE_AND_INDENT();

  if (is_changing_level || is_hidden || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_leave_level_has_completed_fall || is_jumping) {
    dbg("Descend dungeon, no");
    return false;
  }

  if (! maybe_infop()) {
    return false;
  }

  if (is_monst()) {
    if (level->player) {
      //
      // Don't descend if player is on the same level
      //
      return false;
    }
  }

  auto next_level = level->world_at + point3d(0, 0, 2);
  game->init_level(next_level);

  if (is_player()) {
    game->current_level = next_level;
  }

  dbg("Is trying to descend");

  auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
  if (! l) {
    if (is_player()) {
      TOPCON("The exit is permanently blocked!");
    }
    return false;
  }

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (l->is_ascend_dungeon(x, y)) {
        if (is_player()) {
          game->level = l;
          TOPCON("You bravely descend.");
        }

        dbg("Move to next level entrance");
        is_changing_level = true;

        dbg("Level change");
        level_change(l);
        set_tick_last_level_change(game->tick_current);

        dbg("Level change move to destination");
        move_to_immediately(point(x, y));

        dbg("Level change move carried items");
        move_carried_items_immediately();

        if (is_player()) {
          l->player = this;
          dbg("Level change scroll map");
          l->scroll_map_to_player();
          l->update_new_level();
          //
          // Make sure all monsts on the new level are at the
          // same tick or they will get lots of free attacks
          //
          l->update_all_ticks();
        }

        dbg("Level change finish move");
        move_finish();

        dbg("Level change update interpolated position");
        set_interpolated_at(make_fpoint(curr_at));
        update_interpolated_position();

        dbg("Level change location check");
        location_check();
        update_light();

        if (is_player() && level->cursor) {
          level->cursor->move_to_immediately(curr_at);
        }

        is_changing_level = false;
        dbg("Moved to next level entrance");
        if (is_player()) {
          level->ts_fade_in_begin = time_get_time_ms_cached();
          level->update_new_level();

          if (game->robot_mode) {
            game->tick_begin("Begin exploring the new level");
          }
        }

        return true;
      }
    }
  }

  return false;
}
