//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_array_bounds_check.hpp"
// REMOVED #include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_math.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_player.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_template.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_ai.hpp"
// REMOVED #include "my_thing_template.hpp"

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
