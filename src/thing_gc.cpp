//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::gc (void)
{ TRACE_AND_INDENT();
  int group = get_group();
  auto result = level->all_things_to_be_destroyed[group].insert(std::pair(id, this));
  if (result.second == false) {
    //
    // Is this a problem?
    //
    err("Failed to insert into gc thing map");
  } else {
    dbg("Inserted into gc thing map");
  }
}
