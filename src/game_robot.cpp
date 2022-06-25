//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

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
