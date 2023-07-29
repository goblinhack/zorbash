//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

int Thing::paralysis_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) { return 0; }

  if (maybe_aip()) { return (aip()->paralysis_count); }
  return 0;
}

int Thing::paralysis_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->paralysis_count = v);
}

int Thing::paralysis_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->paralysis_count -= v);
}

int Thing::paralysis_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->paralysis_count += v);
}

int Thing::paralysis_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->paralysis_count--);
}

int Thing::paralysis_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->paralysis_count++);
}
