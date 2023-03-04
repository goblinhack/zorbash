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
void Thing::on_enter(Thingp victim)
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

    dbg2("Call %s.%s(%s %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), victim->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_stealing call [%s] expected mod:function, got %d elems", on_stealing.c_str(),
        (int) on_stealing.size());
  }
}

const std::string &Thing::on_enter_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_enter_do());
}
