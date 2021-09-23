//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_thing.h"

void Thing::rest(void)
{
  TRACE_AND_INDENT();
  dbg("Resting");
  stamina_boost(1);
}
