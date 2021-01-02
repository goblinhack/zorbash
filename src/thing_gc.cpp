//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::gc (void)
{_
    auto result = level->all_gc_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("Failed to insert into gc thing map");
    }
}
