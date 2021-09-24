//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_sys.h"

void Game::display(void)
{
  TRACE_AND_INDENT();
  if (! level) {
    return;
  }

  level->display();
}
