//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.h"
#include "my_game.h"
#include "my_globals.h"
#include "my_python.h"
#include "my_random.h"
#include "my_string.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_console.h"

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
