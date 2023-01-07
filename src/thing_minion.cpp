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
    return (int) infop()->minions.size();
  }
  return 0;
}
