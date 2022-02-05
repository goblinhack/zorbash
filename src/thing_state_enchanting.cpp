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
#include "my_wid_actionbar.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_thing_info.hpp"

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
