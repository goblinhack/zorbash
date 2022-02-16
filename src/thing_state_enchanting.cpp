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

bool Thing::state_using_enchantstone(void)
{
  TRACE_NO_INDENT();

  //
  // Enchant a random item.
  //
  enchant_random_item_with_stone();
  if (is_player()) {
    change_state(MONST_STATE_REPACK_INVENTORY, "enchanted");
    game->tick_begin("Robot finished enchanting");
  } else {
    change_state(MONST_STATE_IDLE, "enchanted");
  }

  return true;
}

bool Thing::state_using_skillstone(void)
{
  TRACE_NO_INDENT();

  //
  // Choose a skill
  //
  learn_random_skill();
  if (is_player()) {
    change_state(MONST_STATE_REPACK_INVENTORY, "added skill");
    game->tick_begin("Robot finished adding skills");
  } else {
    change_state(MONST_STATE_IDLE, "added skill");
  }

  return true;
}
