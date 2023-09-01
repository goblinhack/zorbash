//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_thing.hpp"

bool Thing::repulse(Thingp target)
{
  TRACE_NO_INDENT();

  auto points = ::line(curr_at, target->curr_at, 0 /* max_elems*/);

  if (points.size() < 2) {
    dbg("Repulse: %s too close", target->to_short_string().c_str());
    return false;
  }

  auto dest = points[ points.size() - 2 ];

  dbg("Repulse: %s", target->to_short_string().c_str());
  target->move_delta(target->curr_at - dest);

  return true;
}
