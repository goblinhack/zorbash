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
  sdl_display_reset();

  //
  // Create the new level
  //
  game->init();

  auto new_level                   = new Level(biome);
  auto difficulty_depth            = 0;
  auto dungeon_walk_order_level_no = 0;

  new_level->create(world_at, grid_at, dungeon_seed, difficulty_depth, dungeon_walk_order_level_no);
  game->level = new_level;

  pcg_random_allowed++;
  game->place_player();
  game->robot_mode_requested = true;
  game->start();
  game->tick_begin_now();
  game->tick_end();
  game->tick_begin_now();
  pcg_random_allowed--;

  auto last_tick = -1;
  while (game->tick_current < 100) {
    SDL_Delay(5);
    game->level->tick();

    wid_gc_all();
    wid_display_all();

    if (game->tick_current != last_tick) {
      last_tick = game->tick_current;
      ascii_dump(! g_opt_gfx_monochrome);
    }
  }
  delete new_level;

  game->fini();

  if (! dungeon_seed--) { DIE("end of test"); }
}
