//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_random_name.hpp"

void Game::pre_init(void)
{
  TRACE_AND_INDENT();

  pcg_random_allowed++;
  set_seed();

  current_level = point3d(0, 0, 0);
  level         = nullptr;

  world.clear();
  pcg_random_allowed--;
}

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  pre_init();

  CON("Creating level, name '%s', seed %u", seed_name.c_str(), seed);

  init_jump_paths();
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
