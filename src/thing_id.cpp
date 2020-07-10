//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_world.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_thing.h"

Thingp World::test_thing_ptr (ThingId id)
{_
    auto f = all_thing_ptrs.find(id);
    if (f == all_thing_ptrs.end()) {
        return nullptr;
    }

    return (f->second);
}

Thingp World::find_thing_ptr (ThingId id)
{_
    auto f = all_thing_ptrs.find(id);
    if (f == all_thing_ptrs.end()) {
        ERR("thing ptr not found for id, %" PRIx32 "", id.id);
        return nullptr;
    }

    return (f->second);
}

void World::alloc_thing_id (Thingp t)
{_
    for (;;) {
        auto id = myrand();
        if (test_thing_ptr(id)) {
            continue;
        }

        t->id = id;
        all_thing_ptrs[id] = t;
        return;
    }
}

void World::free_thing_id (Thingp t)
{_
    auto f = all_thing_ptrs.find(t->id);
    if (f == all_thing_ptrs.end()) {
        t->err("unknown id for thing %" PRIx32 "", t->id.id);
        return;
    }

    if (f->second != t) {
        t->err("mismatch id for thing %" PRIx32 "", t->id.id);
        return;
    }

    t->id = 0;
    all_thing_ptrs.erase(f);
}

void World::realloc_thing_id (Thingp t)
{_
    all_thing_ptrs[t->id] = t;
}
