//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::wake(void)
{
  TRACE_NO_INDENT();

  change_state(MONST_STATE_IDLE, "wake up");
}

void Thing::awake(void)
{
  TRACE_NO_INDENT();

  msg("%s wakes!", text_The().c_str());
}
