//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_array_bounds_check.hpp"
#include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_math.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_player.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_template.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_ai.hpp"
// REMOVED #include "my_thing_template.hpp"
// REMOVED #include "my_wid_actionbar.hpp"
// REMOVED #include "my_wid_inventory.hpp"
// REMOVED #include "my_wid_popup.hpp"
// REMOVED #include "my_wid_thing_info.hpp"

bool Thing::state_open_inventory(void)
{
  TRACE_NO_INDENT();
  AI_LOG("Open inventory.");

  //
  // Wait for the inventory to be remade
  //
  if (is_player()) {
    if (game->request_remake_rightbar) {
      AI_LOG("Wait on inventory.");
      return true;
    }
  }

  //
  // Then close it. This is really just visual feedback.
  //
  if (is_player()) {
    change_state(MONST_STATE_REPACK_INVENTORY, "repack inventory");
    game->tick_begin("Robot finished collecting");
  } else {
    change_state(MONST_STATE_IDLE, "close inventory");
  }

  return true;
}

bool Thing::state_repack_inventory(void)
{
  TRACE_NO_INDENT();

  //
  // Compress the bag?
  //
  if (bag_compress()) {
    while (bag_compress()) {
    }
    AI_LOG("Repacked inventory.");
  }
  if (is_player()) {
    game->tick_begin("repacked bag");
  }

  //
  // Need to go back to reseting, as this resets failed jumps once fully rested
  // and we may have came here due to eating food when resting.
  //
  change_state(MONST_STATE_RESTING, "finished repacking");

  return true;
}
