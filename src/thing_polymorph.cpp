//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_polymorphed(void)
{
  TRACE_NO_INDENT();
  auto on_polymorphed = tp()->on_polymorphed_do();
  if (std::empty(on_polymorphed)) {
    return;
  }

  auto t = split_tokens(on_polymorphed, '.');
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

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_polymorphed call [%s] expected mod:function, got %d elems", on_polymorphed.c_str(),
        (int) on_polymorphed.size());
  }
}

void Thing::polymorph(Tpp into)
{
  verify(MTYPE_THING, this);
  log("Polymorgh into: %s", into->name().c_str());

  tp_id = into->id;
  mytp  = nullptr;
  tp_or_update();

  //
  // Make sure we have the ability to carry items.
  //
  if (is_player() || is_monst() || is_item() || is_cursor()) {
    new_infop();
  }

  if (is_player() || is_monst() || is_item()) {
    new_itemp();
  }

  if (is_player() || is_monst() || is_cursor()) {
    new_aip();
  }

  if (! is_item_collector()) {
    drop_all();
  }

  //
  // Init the z depth
  //
  level_pop();
  z_depth = tp()->z_depth;
  level_push();

  update();

  on_polymorphed();
  log("Polymorphed into: %s", into->name().c_str());

  on_born();
  check_all_carried_items_are_owned();
}
