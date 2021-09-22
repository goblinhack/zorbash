//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"
#include "my_random.h"
#include "my_globals.h"

void Level::create(point3d at, int seed) {
  TRACE_AND_INDENT();
  pcg_srand(game->seed + at.z);

  is_starting = true;
  clear();

  is_level_type_dungeon = false;
  is_level_type_sewer   = false;

  this->seed = seed;
  world_at   = at;

  log("-");
  log("Creating, seed %u", seed);
  log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
  log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

  bool ret;
  if (at.z & 1) {
    ret = create_dungeon(at, seed);
  } else {
    ret = create_sewer(at, seed);
  }

  log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
  log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
  log("Created, seed %u", seed);
  log("-");

  if (! ret) {
    err("Failed to create level");
  }

  update_map();

  game->started = true;
  is_starting   = false;

  ts_fade_in_begin = time_get_time_ms_cached();

  things_gc_force();

  if (! cursor && player) {
    cursor = thing_new("cursor", player->mid_at);
    cursor->hide();
  }
}

void Level::place_the_grid(void) {
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      (void) thing_new("the_grid", fpoint(x, y));
      if (g_errored) {
        ERR("Could not create level");
        return;
      }
    }
  }
}
