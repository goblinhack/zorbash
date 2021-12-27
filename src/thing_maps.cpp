//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::check_all_carried_maps(void)
{
  TRACE_NO_INDENT();
  treasure_map_check();
  beast_map_check();
}
