//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_thing.hpp"

void Thing::gc(void)
{
  if (is_scheduled_for_gc) {
    return;
  }
  is_scheduled_for_gc = true;

  TRACE_NO_INDENT();

  auto result = level->all_things_to_be_destroyed.insert(std::pair(id, this));
  if (result.second == false) {
    //
    // Is this a problem?
    //
    err("Failed to insert into gc thing map");
  } else {
    dbg3("Inserted into gc thing map");
  }
}
