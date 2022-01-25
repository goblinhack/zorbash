//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"

void Game::save_snapshot_check(void)
{
  TRACE_AND_INDENT();
  //
  // Periodic snapshot saves
  //
  if (game->request_snapshot || (move_count++ > game->config.snapshot_freq)) {
    move_count             = 0;
    game->request_snapshot = false;
    game->saving_snapshot  = true;
    game->save_snapshot();
    game->saving_snapshot = false;
    g_saved_snapshot      = true;
  }
}
