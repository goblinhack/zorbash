//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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

  if (val == is_discovered) {
    return;
  }

  is_discovered = val;

  if (is_player()) {
    if (is_discovered) {
      msg("You can see a secret door!");
    }
  }
}
