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

void Level::things_gc (void)
{_
    for (;;) {
        auto i = all_gc_things.begin();
        if (i == all_gc_things.end()) {
            break;
        }
        auto id = i->first;
        all_gc_things.erase(i);

        auto t = thing_find(id);
        if (!t) {
            ERR("thing %" PRIx32 " not found to garbage collect", id.id);
            continue;
        }

        if (t->is_monst()) {
            monst_count--;
        }

        if (t->is_loggable_for_unimportant_stuff()) {
            t->log("garbage collect");
        }

        delete t;
    }

    all_gc_things.clear();
}
