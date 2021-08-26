//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::gc (void)
{_
    int group = get_group();
    auto result = level->all_things_to_be_destroyed[group].insert(std::pair(id, this));
    if (result.second == false) {
        //
        // Is this a problem?
        //
        dbg("Failed to insert into gc thing map");
    }
}
