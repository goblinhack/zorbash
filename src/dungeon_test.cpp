//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_dmap.hpp"
#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_static.hpp"
#include "my_player.hpp"
#include "my_room.hpp"
#include "my_sdl_proto.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_choose_level.hpp"
#include "my_wid_console.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

void dungeon_test(void)
{
  TRACE_NO_INDENT();

  point3d world_at(0, 0, 1);
  point   grid_at(0, 1);
  auto    dungeon_walk_order_level_no = 1;
  auto    difficulty_depth            = game->seed % DUNGEONS_MAX_DIFFICULTY_LEVEL;

  //
  // Needed to set the terminal size
  //
  g_opt_ascii = true;

  //
  // No monster sounds when testing
  //
  g_opt_silent = true;

  TRACE_NO_INDENT();
  sdl_display_reset();

  TRACE_NO_INDENT();
  game->init();

  //
  // Create the new level
  //
  TRACE_NO_INDENT();
  if (! game->init_level(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no++)) {
    DIE("Failed to create level");
  }

  game->level = get(game->world.levels, world_at.x, world_at.y, world_at.z);
  if (! game->level) {
    DIE("Failed to find game level");
  }

  //
  // Make the next level(s) so we can fall into them
  //
  while (grid_at.y < DUNGEONS_GRID_CHUNK_HEIGHT - 1) {
    TRACE_NO_INDENT();
    world_at += point3d(0, 0, 2);
    grid_at += point(0, 2);
    if (! game->init_level(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no++)) {
      DIE("Failed to create level");
    }
  }

  {
    pcg_random_allowed++;

    game->robot_mode_requested = true;

    TRACE_NO_INDENT();
    game->start();

    TRACE_NO_INDENT();
    game->tick_begin_now();

    TRACE_NO_INDENT();
    game->tick_end();

    TRACE_NO_INDENT();
    game->tick_begin_now();

    pcg_random_allowed--;
  }

  auto player = game->level->player;

  while (! player->is_dead) {
    TRACE_NO_INDENT();
    game->level->tick();

    TRACE_NO_INDENT();
    wid_gc_all();

    TRACE_NO_INDENT();
    wid_display_all();

    if (player) {
      player->log("Tick");

      if (player->is_waiting_to_leave_level_has_completed_fall) {
        player->log("Waiting to leave level after fall");
      }

      if (player->is_waiting_to_descend_dungeon) {
        player->log("Waiting to descend dungeon");
        player->descend_dungeon(true, game->level->world_at + point3d(0, 0, 2));
      }

      if (player->is_waiting_to_descend_sewer) {
        player->log("Waiting to descend sewer");
        if (! player->descend_sewer()) {
          player->err("Failed to descend sewer");
        }
      }

      if (player->is_waiting_to_ascend_sewer) {
        player->log("Waiting to ascend sewer");
        if (! player->ascend_sewer()) {
          player->err("Failed to ascend sewer");
        }
      }

      //
      // The robot can get stuck and oscillate in paths, so put a limit on the test.
      //
      if (player->move_count() > 1000) {
        pcg_random_allowed++;
        player->dead("End of test");
        pcg_random_allowed--;
        break;
      }

      if (player->is_waiting_to_descend_dungeon) {
        DIE("Player failed to descend");
      }
    }

    if (g_errored) {
      DIE("An error occurred");
    }
  }

  CON("End of test, level depth: %u", player->level->dungeon_walk_order_level_no);
  CON("End of test, move count: %u", player->move_count());
  CON("End of test, score: %u", player->score());

  TRACE_NO_INDENT();
  game->fini();

  quit();
  exit(0);
}
