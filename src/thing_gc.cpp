//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::gc(void)
{
  TRACE_AND_INDENT();
  int  group  = get_group();
  auto result = level->all_things_to_be_destroyed[ group ].insert(std::pair(id, this));
  if (result.second == false) {
    //
    // Is this a problem?
    //
    err("Failed to insert into gc thing map");
  } else {
    dbg("Inserted into gc thing map");
  }
}
