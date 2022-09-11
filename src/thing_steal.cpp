//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_rightbar.hpp"

bool Thing::steal_treasure_from(Thingp it)
{
  TRACE_NO_INDENT();
  if (d1000() > tp()->is_steal_item_chance_d1000()) {
    return false;
  }

  dbg("Steal treasure from %s", it->to_short_string().c_str());
  TRACE_NO_INDENT();
  auto cands = treasure_vector();
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
    it->popup(string_sprintf("%%fg=white$Where's my money?!"));
    it->msg("%%fg=orange$You feel less wealthy somehow...%%fg=reset$");
  }
  return true;
}

bool Thing::steal_item_from(Thingp it)
{
  TRACE_NO_INDENT();
  dbg("Try to steal item from %s?", it->to_short_string().c_str());
  TRACE_NO_INDENT();

  if (d1000() > tp()->is_steal_item_chance_d1000()) {
    dbg("No");
    return false;
  }
  TRACE_NO_INDENT();
  dbg("Yes, steal out of this list:");
  auto cands = it->carried_item_only_vector();
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

  if (it->is_player()) {
    it->popup(string_sprintf("%%fg=white$Where's my stuff?!"));
    it->msg("%%fg=orange$You feel lighter somehow...%%fg=reset$");
  }

  //
  // Update the inventory
  //
  wid_rightbar_init();
  return true;
}
