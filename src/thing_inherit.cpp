//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_thing.hpp"
#include <algorithm>
#include <set>

void Thing::inherit_from(Thingp it)
{
  if (it->is_on_fire()) {
    on_fire_set("owner is on fire");
  }
}
