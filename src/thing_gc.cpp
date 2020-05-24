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

void thing_gc (void)
{_
    if (!level) {
        return;
    }

    for (;;) {
        auto i = level->all_gc_things.begin();
        if (i == level->all_gc_things.end()) {
            break;
        }
        auto id = i->first;
        level->all_gc_things.erase(i);

        auto t = thing_find(id);
        if (!t) {
            ERR("thing %08X not found to garbage collect", id);
            continue;
        }

        if (t->is_loggable()) {
            t->log("garbage collect");
        }
        delete t;
    }

    level->all_gc_things.clear();
}
