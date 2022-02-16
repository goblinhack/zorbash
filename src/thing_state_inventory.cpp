//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

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
