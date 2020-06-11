//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Thing::update_light (void)
{_
    //
    // Light source follows the thing.
    //
    auto lc = get_light_count();
    size_t c = 0;
    for (auto l : get_light()) {
        fpoint mid_at = l->owner->get_interpolated_mid_at();
        l->at = mid_at;
        l->calculate(c == lc - 1);
        c++;
    }
}

void Thing::update_all (void)
{_
    for (auto slot = 0; slot < MAX_THINGS; slot++) {
        auto p = getptr(level->all_thing_ptrs, slot);
        auto t = p->ptr;
        if (t) {
            verify(t);
            t->update_light();
        }
    }
}
