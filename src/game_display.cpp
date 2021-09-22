//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"

void Game::display(void) {
  TRACE_AND_INDENT();
  if (! level) {
    return;
  }

  level->display();
}
