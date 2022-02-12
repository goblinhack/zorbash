//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"

bool Thing::state_sleeping(bool &do_something, bool &wait)
{
  TRACE_NO_INDENT();

  AI_LOG("Continue sleeping.");

  if (is_able_to_sleep()) {
    sleep_count_incr();
  }

  do_something = true;
  wait         = true;

  return false;
}
