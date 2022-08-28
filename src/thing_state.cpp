//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popups.hpp"
#include <set>

void Thing::change_state(int new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  if (infop()->monst_state == new_state) {
    return;
  }

  bool was_sleeping = is_sleeping;

  std::string to;
  std::string from;
  switch (new_state) {
    case MONST_STATE_IDLE:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-IDLE";
      break;
    case MONST_STATE_MOVING:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-MOVING";
      break;
    case MONST_STATE_RESTING:
      is_sleeping = false;
      to          = "MONST-RESTING";
      break;
    case MONST_STATE_OPEN_INVENTORY:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-OPEN-INVENTORY";
      break;
    case MONST_STATE_USING_ENCHANTSTONE:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-USING-ENCHANTSTONE";
      break;
    case MONST_STATE_USING_SKILLSTONE:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-USING-SKILLSTONE";
      break;
    case MONST_STATE_REPACK_INVENTORY:
      sleep_count_set(0);
      is_sleeping = false;
      to          = "MONST-REPACK";
      break;
    case MONST_STATE_SLEEPING:
      is_sleeping = true;
      to          = "MONST-SLEEPING";
      break;
  }

  if (is_player()) {
    wid_inventory_fini();
  }

  //
  // Current state
  //
  switch (infop()->monst_state) {
    case MONST_STATE_IDLE: from = "MONST-IDLE"; break;
    case MONST_STATE_MOVING: from = "MONST-MOVING"; break;
    case MONST_STATE_RESTING: from = "MONST-RESTING"; break;
    case MONST_STATE_REPACK_INVENTORY: from = "MONST-REPACK"; break;
    case MONST_STATE_OPEN_INVENTORY: from = "MONST-OPEN-INVENTORY"; break;
    case MONST_STATE_USING_ENCHANTSTONE:
      from = "MONST-USING-ENCHANTSTONE";
      if (is_player()) {
        wid_enchant_destroy();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE:
      from = "MONST-USING-SKILLSTONE";
      if (is_player()) {
        wid_choose_skill_destroy();
      }
      break;
    case MONST_STATE_SLEEPING: from = "MONST-SLEEPING"; break;
  }

  dbg2("Monst state change %s -> %s, reason: %s", from.c_str(), to.c_str(), why.c_str());
  TRACE_AND_INDENT();

  infop()->monst_state = new_state;
  switch (new_state) {
    case MONST_STATE_IDLE: clear_move_path("State is now idle"); break;
    case MONST_STATE_MOVING: break;
    case MONST_STATE_RESTING: break;
    case MONST_STATE_REPACK_INVENTORY: break;
    case MONST_STATE_OPEN_INVENTORY:
      if (is_player()) {
        wid_inventory_init();
        game->set_request_to_remake_rightbar();
      }
      break;
    case MONST_STATE_USING_ENCHANTSTONE:
      if (is_player()) {
        game->wid_enchant_an_item();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE:
      if (is_player()) {
        game->wid_choose_skill();
      }
      break;
  }

  if (is_sleeping != was_sleeping) {
    if (! is_sleeping) {
      awake();
    }
  }
}
