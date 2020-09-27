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
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::update_light (void)
{_
    if (!is_player()) {
        return;
    }

    if (is_hidden) {
        return;
    }

    if (!level) {
        return;
    }

    size_t c = 0;
    for (auto l : get_light()) {
        l->cached_light_pos = point(-1, -1);
        c++;
    }
}
