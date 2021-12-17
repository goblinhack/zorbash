//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_lifespan_tick(Thingp what)
{
  auto on_lifespan_tick = what->tp()->on_lifespan_tick_do();
  if (std::empty(on_lifespan_tick)) {
    return;
  }

  auto t = split_tokens(on_lifespan_tick, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), what->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_lifespan_tick call [%s] expected mod:function, got %d elems", on_lifespan_tick.c_str(),
        (int) on_lifespan_tick.size());
  }
}

void Thing::lifespan_tick(void)
{
  TRACE_AND_INDENT();

  //
  // Torches only tick when carried
  //
  auto owner = get_immediate_owner();
  if (is_torch() && ! owner) {
    return;
  }

  if (! get_lifespan()) {
    return;
  }

  decr_lifespan();

  if (get_lifespan()) {
    return;
  }

  auto top_owner = get_top_owner();
  if (top_owner) {
    top_owner->on_lifespan_tick(this);
  }

  //
  // This is for torches
  //
  if (get_charge_count()) {
    decr_charge_count();
    if (get_charge_count()) {
      dbg("Lifespan expired (but has %d charges left)", get_charge_count());
      game->request_remake_rightbar = true;
      set_lifespan(tp()->lifespan());
      return;
    }
  }

  dead("by ran out of life");
}
