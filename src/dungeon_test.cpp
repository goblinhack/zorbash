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
#include "my_wid_console.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

void dungeon_test(void)
{
  static int dungeon_seed = 10000;

  TRACE_NO_INDENT();
  CON("Test dungeon seed: %d", dungeon_seed);

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
  // Useful to see what is going on
  //
  g_opt_debug1 = true;

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
  new_level->create(world_at, grid_at, dungeon_seed, difficulty_depth, dungeon_walk_order_level_no);
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

  while (! game->level->player->is_dead) {
    TRACE_NO_INDENT();
    SDL_Delay(5);

    TRACE_NO_INDENT();
    game->level->tick();

    TRACE_NO_INDENT();
    wid_gc_all();

    TRACE_NO_INDENT();
    wid_display_all();
  }

  TRACE_NO_INDENT();
  delete new_level;

  TRACE_NO_INDENT();
  game->fini();
  DIE("x");

  if (! dungeon_seed--) {
    DIE("end of test");
  }
}
