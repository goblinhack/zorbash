//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"

bool Thing::state_moving(void)
{
  TRACE_NO_INDENT();

  auto aip = aip_get();

  //
  // Finished the move?
  //
  if (aip->move_path.empty()) {
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
  path_pop_next_move();

  return true;
}
