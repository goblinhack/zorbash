//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

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

bool Thing::state_using_spellbook(void)
{
  TRACE_NO_INDENT();

  //
  // Choose a spell
  //
  learn_random_spell();
  if (is_player()) {
    change_state(MONST_STATE_REPACK_INVENTORY, "added spell");
    game->tick_begin("Robot finished adding spells");
  } else {
    change_state(MONST_STATE_IDLE, "added spell");
  }

  return true;
}
