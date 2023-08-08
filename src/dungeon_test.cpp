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

  //
  // Use a random biome
  //
  auto difficulty_depth = game->seed % DUNGEONS_MAX_DIFFICULTY_LEVEL;
  auto biome            = get_biome(difficulty_depth);
  biome                 = get_biome(0);
  point3d world_at;
  point   grid_at(0, 1);

  //
  // Needed to set the terminal size
  //
  g_opt_ascii = true;

  //
  // No monster sounds when testin
  //
  g_opt_silent = true;

  TRACE_NO_INDENT();
  sdl_display_reset();

  //
  // Create the new level
  //
  TRACE_NO_INDENT();
  game->init();

  auto new_level                   = new Level(biome);
  auto dungeon_walk_order_level_no = 1;

  TRACE_NO_INDENT();
  new_level->create(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no);
  new_level->dungeon_walk_order_level_no = grid_at.y;
  game->level                            = new_level;

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

    if (player && player->is_waiting_to_descend_dungeon) {
      TRACE_AND_INDENT();
      player->con("player needs to descend a level");

      world_at += point3d(0, 0, 2);
      grid_at += point(0, 1);

      TRACE_AND_INDENT();
      player->con("create the next level");
      auto old_level = game->level;
      new_level      = new Level(biome);
      new_level->create(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no);
      new_level->dungeon_walk_order_level_no = grid_at.y;
      game->level                            = new_level;
      game->things_are_moving                = false;

      TRACE_AND_INDENT();
      player->con("player change level");
      player->level_change(new_level);
      if (! player->level) {
        DIE("Player has no level");
      }

      player->con("player needs to delete the old level");
      TRACE_AND_INDENT();
      delete old_level;

      TRACE_AND_INDENT();
      player->con("player has joined the new level");

      if (player->is_waiting_to_descend_dungeon) {
        DIE("Player failed to descend");
      }

      TRACE_NO_INDENT();
      wid_choose_next_dungeons_destroy(nullptr);

      {
        TRACE_NO_INDENT();
        game->tick_begin("explore new level");
      }
    }

    if (g_errored) {
      DIE("An error occurred");
    }
  }

  CON("End of test, level depth: %u", grid_at.y);
  CON("End of test, move count: %u", player->move_count());
  CON("End of test, score: %u", player->score());

  TRACE_NO_INDENT();
  delete new_level;

  TRACE_NO_INDENT();
  game->fini();

  exit(0);
}
