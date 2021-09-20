//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"

void Game::display (void)
{_
  if (!level) {
    return;
  }

  level->display();
}
