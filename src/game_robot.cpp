//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_popup.h"

void Game::robot_mode_tick(void)
{
  TRACE_AND_INDENT();
  if (! game->robot_mode) {
    return;
  }

  if (! level) {
    return;
  }

  auto player = level->player;
  if (! player) {
    return;
  }

  player->ai_tick();
}
