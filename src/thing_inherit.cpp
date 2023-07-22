//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"

void Thing::inherit_from(Thingp it)
{
  if (it->is_on_fire()) { on_fire_set("owner is on fire"); }
}
