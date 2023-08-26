//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

bool Thing::wake(const std::string &reason)
{
  if (is_dead || is_dying) {
    return false;
  }

  if (! is_sleeping) {
    return true;
  }

  dbg("Wake %s", reason.c_str());
  TRACE_AND_INDENT();

  //
  // I think if trapped in a spell of holding and asleep, you stay asleep. Forever...
  //
  if (level->is_spell_of_holding(curr_at)) {
    dbg("Wake %s; no, stay asleep in the magical holding", reason.c_str());
    return false;
  }

  //
  // I think if trapped in ice and asleep, you stay asleep. Forever...
  //
  if (level->is_block_of_ice(curr_at)) {
    dbg("Wake %s; no, stay asleep in the ice", reason.c_str());
    return false;
  }

  //
  // This should call awake() below now
  //
  change_state(MONST_STATE_IDLE, "wake up: " + reason);

  auto followers = all_followers_get();
  for (auto f : followers) {
    f->wake("leader is awake");
  }

  return true;
}

//
// Called at the end of the waking state transition.
//
void Thing::awake(void)
{
  if (is_dead || is_dying) {
    return;
  }

  dbg("Awake");
  TRACE_AND_INDENT();

  msg("%s wakes!", text_The().c_str());

  //
  // To avoid immediate attacks upon waking.
  //
  infop()->tick_last_awoke = game->tick_current;

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
