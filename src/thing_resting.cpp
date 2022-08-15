//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_resting(void)
{
  TRACE_NO_INDENT();

  auto on_resting = tp()->on_resting_do();
  if (std::empty(on_resting)) {
    return;
  }

  auto t = split_tokens(on_resting, '.');
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
    ERR("Bad on_resting call [%s] expected mod:function, got %d elems", on_resting.c_str(), (int) on_resting.size());
  }
}

void Thing::resting(void)
{
  dbg("Resting");
  TRACE_AND_INDENT();

  if (game->robot_mode) {
    //
    // Ok, cheating a bit. But otherwise it slows down robot mode too much.
    //
    health_boost(1);
    stamina_boost(1);
  } else {
    if ((int) pcg_random_range(0, 200) < stat_str()) {
      health_boost(1);
    }

    if (d20() < stat_con()) {
      stamina_boost(1);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_resting_do().empty()) {
        iter->resting();
      }
    }
  }

  on_resting();
}
