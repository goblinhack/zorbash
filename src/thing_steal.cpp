//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_ptrcheck.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_rightbar.h"

bool Thing::steal_treasure_from(Thingp it)
{
  TRACE_AND_INDENT();
  if ((int) pcg_random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
    return false;
  }

  dbg("Steal treasure from %s", it->to_string().c_str());
  TRACE_AND_INDENT();
  auto cands = get_treasure_list();
  if (! cands.size()) {
    dbg("No, nothing to steal");
    return false;
  }
  auto chosen = cands[ pcg_random_range(0, cands.size()) ];

  dbg("Steal treasure %s", chosen->to_string().c_str());
  if (! it->drop(chosen, this, true /* stolen */)) {
    return false;
  }

  if (! it->is_dead) {
    carry(chosen);
  }
  chosen->hide();

  if (it->is_player()) {
    it->msg(string_sprintf("                        %%fg=white$Where's my money?!"));
    TOPCON("%%fg=orange$You feel less wealthy somehow...%%fg=reset$");
  }
  return true;
}

bool Thing::steal_item_from(Thingp it)
{
  TRACE_AND_INDENT();
  dbg("Try to steal item from %s?", it->to_string().c_str());
  if ((int) pcg_random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
    dbg("No");
    return false;
  }
  TRACE_AND_INDENT();
  dbg("Yes, steal out of this list:");
  auto cands = it->get_item_list();
  if (! cands.size()) {
    dbg("No, nothing to steal");
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];

  dbg("Yes, steal: %s", chosen->to_string().c_str());

  it->drop(chosen, this);
  if (! chosen->is_dead) {
    carry(chosen);
  }
  chosen->hide();

  IF_DEBUG2 { it->log("New carried list:"); }
  it->get_item_list();

  if (it->is_player()) {
    it->msg(string_sprintf("                        %%fg=white$Where's my stuff?!"));
    TOPCON("%%fg=orange$You feel lighter somehow...%%fg=reset$");
  }

  //
  // Update the inventory
  //
  wid_rightbar_init();
  return true;
}
