//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

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
  if (game->request_to_save_snapshot || (player_move_count_in_this_snapshot++ > game->config.snapshot_freq)) {
    player_move_count_in_this_snapshot = 0;
    game->unset_request_to_save_snapshot();
    game->set_currently_saving_snapshot();
    game->save_snapshot();
    game->unset_currently_saving_snapshot();
    g_saved_snapshot = true;
  }
}
