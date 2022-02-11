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
#include <algorithm>
#include <set>

void Thing::change_state(int new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  bool was_sleeping = is_sleeping;

  std::string to;
  std::string from;
  switch (new_state) {
    case MONST_STATE_IDLE :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "IDLE";
      break;
    case MONST_STATE_MOVING :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "MOVING";
      break;
    case MONST_STATE_RESTING :
      is_sleeping = false;
      to          = "RESTING";
      break;
    case MONST_STATE_OPEN_INVENTORY :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "OPEN-INVENTORY";
      break;
    case MONST_STATE_USING_ENCHANTSTONE :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "USING-ENCHANTSTONE";
      break;
    case MONST_STATE_USING_SKILLSTONE :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "USING-SKILLSTONE";
      break;
    case MONST_STATE_REPACK_INVENTORY :
      set_sleep_count(0);
      is_sleeping = false;
      to          = "REPACK";
      break;
    case MONST_STATE_SLEEPING :
      is_sleeping = true;
      to          = "SLEEPING";
      break;
  }

  if (get_infop()->monst_state == new_state) {
    dbg("Same state %s, reason: %s", to.c_str(), why.c_str());
    TRACE_AND_INDENT();
    return;
  }

  if (is_player()) {
    wid_inventory_fini();
  }

  //
  // Current state
  //
  switch (get_infop()->monst_state) {
    case MONST_STATE_IDLE : from = "IDLE"; break;
    case MONST_STATE_MOVING : from = "MOVING"; break;
    case MONST_STATE_RESTING : from = "RESTING"; break;
    case MONST_STATE_REPACK_INVENTORY : from = "REPACK"; break;
    case MONST_STATE_OPEN_INVENTORY : from = "OPEN-INVENTORY"; break;
    case MONST_STATE_USING_ENCHANTSTONE :
      from = "USING-ENCHANTSTONE";
      if (is_player()) {
        wid_enchant_destroy();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE :
      from = "USING-SKILLSTONE";
      if (is_player()) {
        wid_choose_skill_destroy();
      }
      break;
    case MONST_STATE_SLEEPING : from = "SLEEPING"; break;
  }

  dbg("State change %s -> %s, reason: %s", from.c_str(), to.c_str(), why.c_str());
  TRACE_AND_INDENT();

  get_infop()->monst_state = new_state;
  switch (new_state) {
    case MONST_STATE_IDLE : clear_move_path("State is now idle"); break;
    case MONST_STATE_MOVING : break;
    case MONST_STATE_RESTING : break;
    case MONST_STATE_REPACK_INVENTORY : break;
    case MONST_STATE_OPEN_INVENTORY :
      if (is_player()) {
        wid_inventory_init();
        game->request_remake_rightbar = true;
      }
      break;
    case MONST_STATE_USING_ENCHANTSTONE :
      if (is_player()) {
        game->wid_enchant_an_item();
      }
      break;
    case MONST_STATE_USING_SKILLSTONE :
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
