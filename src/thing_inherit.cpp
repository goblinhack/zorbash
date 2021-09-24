//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dmap.h"
#include "my_level.h"
#include "my_math.h"
#include "my_sys.h"
#include "my_thing.h"
#include <algorithm>
#include <set>

void Thing::inherit_from(Thingp it)
{
  if (it->is_on_fire()) {
    set_on_fire("owner is on fire");
  }
}
