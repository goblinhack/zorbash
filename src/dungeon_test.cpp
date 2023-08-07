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
  // smaller node numbers mean larger rooms
  //
  auto    biome = get_biome(0);
  point3d world_at;
  point   grid_at;

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
  auto difficulty_depth            = 0;
  auto dungeon_walk_order_level_no = 0;

  TRACE_NO_INDENT();
  new_level->create(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no);
  game->level = new_level;

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
    SDL_Delay(5);

    TRACE_NO_INDENT();
    game->level->tick();

    TRACE_NO_INDENT();
    wid_gc_all();

    TRACE_NO_INDENT();
    wid_display_all();

    if (player && player->is_waiting_to_descend_dungeon) {
      TRACE_NO_INDENT();
      world_at += point3d(0, 0, 2);
      grid_at += point(0, 1);
      delete new_level;

      new_level = new Level(biome);

      TRACE_NO_INDENT();
      new_level->create(world_at, grid_at, difficulty_depth, dungeon_walk_order_level_no);
      game->level = new_level;

      TRACE_NO_INDENT();
      player->level_change(new_level);

      TRACE_NO_INDENT();
      wid_choose_next_dungeons_destroy(nullptr);
    }
  }

  CON("End of test, move count: %u", player->move_count());

  TRACE_NO_INDENT();
  delete new_level;

  TRACE_NO_INDENT();
  game->fini();

  exit(0);
}
