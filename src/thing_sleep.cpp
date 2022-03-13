//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"

void Thing::sleep(void)
{
  change_state(MONST_STATE_SLEEPING, "time to sleep");
  auto followers = all_followers_get();
  for (auto f : followers) {
    f->sleep();
  }
}

void Thing::wake(void)
{
  if (! is_able_to_sleep()) {
    return;
  }

  TRACE_NO_INDENT();

  dbg("Wake");
  change_state(MONST_STATE_IDLE, "wake up");

  auto followers = all_followers_get();
  for (auto f : followers) {
    f->wake();
  }
}

void Thing::awake(void)
{
  if (! is_able_to_sleep()) {
    return;
  }

  TRACE_NO_INDENT();

  dbg("Awake");
  msg("%s wakes!", text_The().c_str());

  tile_curr = 0;
  animate();

  {
    auto on_awake = on_awake_do();
    if (! std::empty(on_awake)) {
      auto t = split_tokens(on_awake, '.');
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

        dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
      } else {
        ERR("Bad on_awake call [%s] expected mod:function, got %d elems", on_awake.c_str(), (int) on_awake.size());
      }
    }
  }
}
