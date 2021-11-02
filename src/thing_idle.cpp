//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_console.hpp"

//
// Roll the dice and see if we do anything
//
bool Thing::idle_check(void)
{
  TRACE_AND_INDENT();
  if (! std::empty(get_on_idle_dice_str())) {
    auto roll = get_idle_tick();
    if (game->tick_current - get_tick_last_did_something() >= (unsigned int) roll) {
      auto d = get_on_idle_dice();
      py_call_void_fn(d.python_mod.c_str(), d.python_func.c_str(), id.id, (unsigned int) mid_at.x,
                      (unsigned int) mid_at.y);
      set_tick_last_did_something(game->tick_current);
      return true;
    }
  }
  return false;
}
