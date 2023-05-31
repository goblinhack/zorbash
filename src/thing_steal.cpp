//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_rightbar.hpp"

//
// Python callback upon being stealing
//
void Thing::on_stealing(Thingp from, Thingp what)
{
  TRACE_NO_INDENT();
  auto on_stealing = tp()->on_stealing_do();
  if (std::empty(on_stealing)) {
    return;
  }

  auto t = split_tokens(on_stealing, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg2("Call %s.%s(%s %s %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), from->to_short_string().c_str(),
         what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, from->id.id, what->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_stealing call [%s] expected mod:function, got %d elems", on_stealing.c_str(),
        (int) on_stealing.size());
  }
}

bool Thing::steal_treasure_from(Thingp it)
{
  TRACE_NO_INDENT();
  if (d1000() > tp()->chance_d1000_steal_item()) {
    return false;
  }

  dbg("Steal treasure from %s", it->to_short_string().c_str());
  TRACE_NO_INDENT();
  auto cands = it->treasure_vector();
  if (! cands.size()) {
    dbg("No, nothing to steal");
    return false;
  }
  auto chosen = cands[ pcg_random_range(0, cands.size()) ];

  dbg("Steal treasure %s", chosen->to_string().c_str());
  {
    DropOptions drop_options;
    drop_options.is_being_stolen = true;
    if (! it->drop(chosen, this, drop_options)) {
      return false;
    }
  }

  {
    CarryOptions carry_options;
    carry_options.is_being_stolen = true;
    if (! it->is_dead) {
      carry(chosen, carry_options);
    }
  }
  chosen->hide();

  if (it->is_player()) {
    if (chosen->is_able_to_be_equipped()) {
      it->popup(string_sprintf("%%fg=white$Where's my equipment?!"));
      it->msg("%%fg=orange$You feel naked...%%fg=reset$");
    } else {
      it->popup(string_sprintf("%%fg=white$Where's my money?!"));
      it->msg("%%fg=orange$You feel less wealthy somehow...%%fg=reset$");
    }
  }

  if (is_able_to_run_away_after_stealing()) {
    add_avoid(it);
  }

  on_stealing(it, chosen);

  return true;
}

bool Thing::steal_item_from(Thingp it)
{
  TRACE_NO_INDENT();
  dbg("Try to steal item from %s?", it->to_short_string().c_str());
  TRACE_NO_INDENT();

  if (d1000() > tp()->chance_d1000_steal_item()) {
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

  DropOptions drop_options;
  drop_options.is_being_stolen = true;
  it->drop(chosen, this, drop_options);

  if (! chosen->is_dead) {
    CarryOptions carry_options;
    carry_options.is_being_stolen = true;
    carry(chosen, carry_options);
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
