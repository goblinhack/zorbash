//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

void Thing::inherit_from (Thingp it)
{
    if (it->is_on_fire()) {
        set_on_fire("owner is on fire");
    }
}
