//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_monst.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

//
// E.g. for secret doors, is it visible?
//
bool Thing::discovered(void) { return is_discovered; }

//
// E.g. for secret doors, is it visible?
//
void Thing::discovered_set(bool val)
{
  TRACE_AND_INDENT();

  is_discovered = val;
}

void Thing::discovered_set(Thingp what, bool val)
{
  TRACE_AND_INDENT();

  if (val == what->is_discovered) {
    return;
  }

  what->is_discovered = val;

  if (is_player()) {
    if (what->is_discovered) {
      msg("You can see a secret door!");
    }
  }
}
