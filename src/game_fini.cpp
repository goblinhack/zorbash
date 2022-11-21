//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_sys.hpp"

void Game::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();

  fps_value          = 0;
  started            = false;
  things_are_moving  = false;
  tick_completed     = 1;
  tick_current       = 1;
  move_count         = 0;
  is_being_destroyed = true;
  TRACE_NO_INDENT();
  config.fini();
  TRACE_NO_INDENT();
  world.fini();
  TRACE_NO_INDENT();
  is_being_destroyed = false;
}
