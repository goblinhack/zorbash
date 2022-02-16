//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_main.hpp"
#include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::rest(void)
{
  dbg("Resting");
  TRACE_AND_INDENT();

  if ((int) pcg_random_range(0, 200) < stat_str()) {
    health_boost(1);
  }

  if (d20() < stat_con()) {
    stamina_boost(1);
  }
}
