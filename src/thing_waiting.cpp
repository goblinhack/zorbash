//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_waiting(void)
{
  TRACE_NO_INDENT();

  auto on_waiting = tp()->on_waiting_do();
  if (std::empty(on_waiting)) { return; }

  auto t = split_tokens(on_waiting, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) { fn = fn.replace(found, 2, ""); }

    if (mod == "me") { mod = name(); }

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_waiting call [%s] expected mod:function, got %d elems", on_waiting.c_str(), (int) on_waiting.size());
  }
}

void Thing::waiting(void)
{
  dbg("Waiting");
  TRACE_AND_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_waiting_do().empty()) { iter->waiting(); }
    }
  }

  on_waiting();
}
