//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

//
// Python callback upon being tick
//
bool Thing::on_tick_when_deactivated(void)
{
  auto on_tick_when_deactivated = tp()->on_tick_when_deactivated_do();
  if (std::empty(on_tick_when_deactivated)) {
    return false;
  }

  if (! is_skill()) {
    return false;
  }

  if (is_activated) {
    return false;
  }

  auto t = split_tokens(on_tick_when_deactivated, '.');
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

    auto owner = top_owner();
    dbg("Call %s.%s(owner=%s, item=%s, %d, %d)", mod.c_str(), fn.c_str(),
         owner ? owner->to_short_string().c_str() : "<>", to_string().c_str(), (unsigned int) curr_at.x,
         (unsigned int) curr_at.y);
    return py_call_bool_fn(mod.c_str(), fn.c_str(), owner ? owner->id.id : 0, id.id, (unsigned int) curr_at.x,
                           (unsigned int) curr_at.y);
  }

  ERR("Bad on_tick_when_deactivated call [%s] expected mod:function, got %d elems", on_tick_when_deactivated.c_str(),
      (int) on_tick_when_deactivated.size());
  return false;
}
