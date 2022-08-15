//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::state_moving(void)
{
  TRACE_NO_INDENT();

  auto ai = aip();

  //
  // Finished the move?
  //
  if (ai->move_path.empty()) {
    AI_LOG("Move finished.");
    if (is_player()) {
      game->tick_begin("Robot move finished");
    }
    change_state(MONST_STATE_IDLE, "move finished");
    if (is_player()) {
      game->request_remake_actionbar = true;
    }
    return true;
  }

  //
  // Keep on moving.
  //
  AI_LOG("Keep on moving");
  if (is_player()) {
    game->tick_begin("Robot move");
  }
  path_pop_next_move(THING_MOVE_REASON_AI);

  return true;
}
