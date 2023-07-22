//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::state_resting(bool &do_something, bool &wait)
{
  TRACE_NO_INDENT();

  AI_LOG("Resting state.");

  //
  // If attacked, we should be kicked out of resting
  //
  // If resting, check if we are rested enough.
  //
  if ((health() >= (health_max() / 4) * 3) && (stamina() >= (stamina_max() / 4) * 3)) {
    AI_LOG("Rested enough. Back to work.");
    if (is_player()) { game->tick_begin("Robot has rested enough"); }
    change_state(MONST_STATE_IDLE, "rested enough");
    return true;
  }

  //
  // Check for food first, before abandoning resting
  //
  if (eat_something()) {
    AI_LOG("Ate an item.");
    if (is_player()) { game->tick_begin("Robot ate an item"); }
    change_state(MONST_STATE_OPEN_INVENTORY, "eat something");
    return true;
  }

  AI_LOG("Wait and rest.");

  //
  // Able to sleep?
  //
  if (is_able_to_sleep()) {
    if (game->tick_current - tick_last_i_was_attacked() > 20) { sleep(); }
  }

  do_something = true;
  wait         = true;

  return false;
}
