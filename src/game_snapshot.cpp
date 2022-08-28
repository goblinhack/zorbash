//
// Copyright Neil McGill, goblinhack@gmail.com
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

  if (! level) {
    return;
  }

  if (! level->player) {
    return;
  }

  if (level->player->is_dead) {
    return;
  }

  //
  // Periodic snapshot saves
  //
  if (game->request_to_save_snapshot || (move_count++ > game->config.snapshot_freq)) {
    move_count = 0;
    game->unset_request_to_save_snapshot();
    game->set_currently_saving_snapshot();
    game->save_snapshot();
    game->unset_currently_saving_snapshot();
    g_saved_snapshot = true;
  }
}
