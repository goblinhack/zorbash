//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "game_levels_grid.hpp"
#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_sys.hpp"
#include "my_world.hpp"

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

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

void Game::init_level(point3d p)
{
  LOG("Game init level %d,%d,%d", p.x, p.y, p.z);
  TRACE_AND_INDENT();

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

void Game::init_levels(void)
{
  LOG("Game init levels");
  TRACE_AND_INDENT();

  IF_DEBUG2
  {
    game_levels_grid_init();
    return;
  }

  //
  // Increase this to create more levels in advance
  //
  for (auto z = 0; z <= 0; z++) {
    auto level_at = current_level;
    level_at.z += z;
    init_level(level_at);
  }
}
