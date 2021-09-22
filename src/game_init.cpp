//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_random.h"
#include "my_random_name.h"
#include "my_array_bounds_check.h"
#include "my_globals.h"

void Game::init(void) {
  TRACE_AND_INDENT();
  LOG("Game init");

  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(sizeof("4294967295") - 1);
  }
  seed = string_to_hash(seed_name);
  CON("Creating level, name '%s', seed %u", seed_name.c_str(), seed);

  current_level = point3d(LEVELS_ACROSS / 2, LEVELS_DOWN / 2, 1);
  level         = nullptr;

  world.clear();
  init_levels();
  init_jump_paths();

  auto l = get(world.levels, current_level.x, current_level.y, current_level.z);
  if (! l) {
    return;
  }
  level = l;
}

void Game::init_level(point3d p) {
  TRACE_AND_INDENT();
  LOG("Game init level %d,%d,%d", p.x, p.y, p.z);

  auto level_seed = seed + p.x + p.y + p.z;
  auto l          = get(world.levels, p.x, p.y, p.z);
  if (! l) {
    world.new_level_at(p, level_seed);
    l = get(world.levels, p.x, p.y, p.z);
    if (! l) {
      ERR("No level created at %d,%d,%d", game->current_level.x, game->current_level.y, game->current_level.z);
    }
  }
}

void Game::init_levels(void) {
  TRACE_AND_INDENT();
  LOG("Game init levels");

  //
  // Increase this to create more levels in advance
  //
  for (auto z = 0; z <= 0; z++) {
    auto level_at = current_level;
    level_at.z += z;
    init_level(level_at);
  }
}
