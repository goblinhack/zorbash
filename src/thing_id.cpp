//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include <list>

Thingp World::find_thing_ptr (uint32_t id)
{_
    auto slot = id % MAX_THINGS;
    auto p = &all_thing_ptrs[slot];
    if (unlikely(!p->ptr)) {
        DIE("thing ptr not found, slot %u, id %08X", slot, id);
    }

    if (unlikely(p->id != id)) {
        DIE("invalid thing ptr, slot %u, id %08X != %08X",
            slot, id, p->id);
    }

    verify(p->ptr);
    return (p->ptr);
}

void World::alloc_thing_id (Thingp t)
{_
    for (uint32_t slot = 1; slot < MAX_THINGS; slot++) {
        auto p = getptr(all_thing_ptrs, slot);
        if (!p->ptr) {
            p->ptr = t;
            uint32_t idx = (myrand() & ~MAX_THINGS_MASK) | slot;
            t->id = idx;
            p->id = idx;
            // t->log("alloc id");
            return;
        }
    }
    DIE("out of thing slots, hit max of %u", MAX_THINGS);
}

void World::free_thing_id (Thingp t)
{_
    uint32_t slot = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, slot);
    if (!p->ptr) {
        t->die("double free for thing ID %08X", t->id);
    }

    if (p->ptr != t) {
        t->die("wrong owner trying to free thing ID %08X", t->id);
    }

    if (p->id != t->id) {
        t->die("stale owner trying to free thing ID %08X", t->id);
    }

    // t->log("free id");
    p->ptr = nullptr;
    p->id = 0;
    t->id = 0;
}

void World::realloc_thing_id (Thingp t)
{_
    if (!t->id) {
        t->die("trying to realloc when thing has no ID");
    }

    uint32_t slot = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, slot);
    if (p->ptr) {
        if (p->ptr == t) {
            t->die("slot in use, cannot be realloc'd for same thing ID %08X",
                   t->id);
        } else {
            t->err("slot in use by another thing, cannot be realloc'd by %08X",
                   t->id);
            p->ptr->die("this is the current owner");
        }
    }

    p->ptr = t;
    p->id = t->id;
    // t->log("realloc id");
}
