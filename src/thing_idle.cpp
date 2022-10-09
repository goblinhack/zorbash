//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"

//
// Roll the dice and see if we do anything
//
bool Thing::idle_check(void)
{
  TRACE_NO_INDENT();

  if (! std::empty(on_idle_tick_freq_dice_str())) {
    auto roll = on_idle_tick_freq();
    // con("%d %d roll %d", game->tick_current, tick_last_did_something(), roll);
    if (game->tick_current - tick_last_did_something() >= (unsigned int) roll) {
      // con("%d %d roll %d tick", game->tick_current, tick_last_did_something(), roll);
      auto d   = on_idle_tick_freq_dice();
      auto mod = d.python_mod;

      if (mod == "me") {
        mod = name();
      }

      py_call_void_fn(mod.c_str(), d.python_func.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
      tick_last_did_something_set(game->tick_current);
      return true;
    }
  }
  return false;
}

int Thing::idle_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->idle_count);
  }
  return 0;
}

int Thing::idle_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count = v);
}

int Thing::idle_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count -= v);
}

int Thing::idle_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count += v);
}

int Thing::idle_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count--);
}

int Thing::idle_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count++);
}
