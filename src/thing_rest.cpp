//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::rest(void)
{
  TRACE_AND_INDENT();
  dbg("Resting");
  stamina_boost(1);
}
