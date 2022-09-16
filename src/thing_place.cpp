//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_thing.hpp"

bool Thing::place(const std::string &what, const point p)
{
  dbg("place");
  TRACE_AND_INDENT();

  level->thing_new(what, p);

  //
  // Check if we are newly spawned over a chasm
  // Or if something we spawned at needs to react to us
  //
  location_check_all_things_at();

  return true;
}
