//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.h"
#include "my_game.h"
#include "my_level.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_actionbar.h"

void Game::save_snapshot_check(void)
{
  TRACE_AND_INDENT();
  //
  // Periodic snapshot saves
  //
  static int move_count;
  if (game->request_snapshot || (move_count++ > ENABLE_SAVE_SNAPSHOT_FREQ)) {
    move_count             = 0;
    game->request_snapshot = false;
    game->saving_snapshot  = true;
    game->save_snapshot();
    game->saving_snapshot = false;
    g_saved_snapshot      = true;
  }
}
