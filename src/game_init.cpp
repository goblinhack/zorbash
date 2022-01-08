//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_game_dungeons.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_sys.hpp"
#include "my_world.hpp"

void Game::pre_init(void)
{
  TRACE_AND_INDENT();

  set_seed();

  current_level = point3d(0, 0, 0);
  level         = nullptr;

  world.clear();
}

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  pre_init();

  CON("Creating level, name '%s', seed %u", seed_name.c_str(), seed);

  // init_levels();
  init_jump_paths();

  // auto l = get(world.levels, current_level.x, current_level.y, current_level.z);
  // if (! l) {
  // return;
  //}
  // level = l;
}

void Game::set_seed(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(sizeof("4294967295") - 1);
  }
  seed = string_to_hash(seed_name);
  pcg_srand(seed);
}

void Game::init_level(point3d p)
{
  DBG("Game init level %d,%d,%d", p.x, p.y, p.z);
  TRACE_AND_INDENT();

  auto level_seed = seed + p.x + p.y + p.z;
  TRACE_AND_INDENT();
  auto l = get(world.levels, p.x, p.y, p.z);
  TRACE_AND_INDENT();
  if (! l) {
    DBG("Create new level at: %d,%d,%d", p.x, p.y, p.z);
    world.new_level_at(p, level_seed);
    l = get(world.levels, p.x, p.y, p.z);
    if (! l) {
      ERR("No level created at: %d,%d,%d", game->current_level.x, game->current_level.y, game->current_level.z);
    }
  } else {
    LOG("Level already exists: %d,%d,%d", p.x, p.y, p.z);
  }
}

void Game::init_levels(void)
{
  LOG("Game init levels");
  TRACE_AND_INDENT();

#if 0
  IF_DEBUG2
  {
    game_dungeons_init();
    return;
  }
#endif

  //
  // Increase this to create more levels in advance
  //
  for (auto z = 0; z <= 0; z++) {
    auto level_at = current_level;
    level_at.z += z;
    init_level(level_at);
  }
}
