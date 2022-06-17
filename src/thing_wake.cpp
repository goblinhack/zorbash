//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"

void Thing::wake(const std::string &reason)
{
  if (is_dead || is_dying) {
    return;
  }

  if (! is_sleeping) {
    return;
  }

  dbg("Wake %s", reason.c_str());
  TRACE_AND_INDENT();

  //
  // This should call awake() below now
  //
  change_state(MONST_STATE_IDLE, "wake up: " + reason);

  auto followers = all_followers_get();
  for (auto f : followers) {
    f->wake("leader is awake");
  }
}

void Thing::awake(void)
{
  if (is_dead || is_dying) {
    return;
  }

  dbg("Awake");
  TRACE_AND_INDENT();

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
