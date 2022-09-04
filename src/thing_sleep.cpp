//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::sleep(void)
{
  change_state(MONST_STATE_SLEEPING, "time to sleep");
  auto followers = all_followers_get();
  for (auto f : followers) {
    f->sleep();
  }
}

bool Thing::is_state_sleeping(void) { return is_sleeping; }

int Thing::is_asleep_initially(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_asleep_initially());
}

int Thing::is_able_to_sleep(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_sleep());
}

////////////////////////////////////////////////////////////////////////////
// sleep_count
////////////////////////////////////////////////////////////////////////////
int Thing::sleep_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->sleep_count);
  } else {
    return 0;
  }
}

int Thing::sleep_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count = v);
}

int Thing::sleep_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count -= v);
}

int Thing::sleep_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count += v);
}

int Thing::sleep_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count--);
}

int Thing::sleep_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count++);
}
