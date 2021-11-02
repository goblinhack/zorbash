//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_sys.hpp"

void Game::fini(void)
{
  TRACE_AND_INDENT();
  fps_value         = 0;
  started           = false;
  things_are_moving = false;
  tick_completed    = 1;
  tick_current      = 1;
  TRACE_AND_INDENT();
  config.fini();
  TRACE_AND_INDENT();
  world.fini();
  TRACE_AND_INDENT();
}
