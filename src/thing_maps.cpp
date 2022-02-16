//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_main.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::check_all_carried_maps(void)
{
  TRACE_NO_INDENT();
  map_treasure_check();
  map_beast_check();
}
