//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"
// REMOVED #include <set>

void Thing::inherit_from(Thingp it)
{
  if (it->is_on_fire()) {
    on_fire_set("owner is on fire");
  }
}
