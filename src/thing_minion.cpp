//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

int Thing::minion_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->minion_count);
  }
  return 0;
}

int Thing::minion_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count = v);
}

int Thing::minion_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count -= v);
}

int Thing::minion_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count += v);
}

int Thing::minion_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count--);
}

int Thing::minion_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count++);
}
