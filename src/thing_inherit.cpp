//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_math.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include <algorithm>
#include <set>

void Thing::inherit_from(Thingp it)
{
  if (it->is_on_fire()) {
    set_on_fire("owner is on fire");
  }
}
