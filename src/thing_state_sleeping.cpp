//
// Copyright goblinhack@gmail.com
//

#include "my_thing.hpp"

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
