//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::create(point3d at, uint32_t seed, int difficulty_depth)
{
  TRACE_AND_INDENT();
  pcg_srand(game->seed + at.z);

  is_starting = true;
  clear();

  is_level_type_dungeon = false;
  is_level_type_sewer   = false;

  this->seed             = seed;
  this->difficulty_depth = difficulty_depth;
  world_at               = at;

  //
  // Setup the various chances of things appearing.
  //
  set_chances_of_creating();

  IF_DEBUG2
  {
    log("-");
    log("Creating, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v");
  }

  //
  // Must set the level pointer so for e.g. spiders can spawn webs when born
  //
  game->level_being_created = this;

  bool ret;
  if (at.z & 1) {
    ret = create_dungeon(at, seed);
  } else {
    ret = create_sewer(at, seed);
  }

  game->level_being_created = nullptr;

  IF_DEBUG2
  {
    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("Created, seed %u", seed);
    log("-");
  }

  if (! ret) {
    err("Failed to create level");
  }

  update_map();

  game->started = true;
  is_starting   = false;

  ts_fade_in_begin = time_get_time_ms_cached();

  things_gc_force();

  if (! cursor && player) {
    cursor = thing_new("cursor", player->curr_at);
    cursor->hide();
  }

  created();
}

void Level::created(void)
{
  TRACE_AND_INDENT();

  assign_leaders_and_followers();
}

void Level::place_the_grid(void)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      (void) thing_new("the_grid", point(x, y));
      if (g_errored) {
        ERR("Could not create level");
        return;
      }
    }
  }
}
