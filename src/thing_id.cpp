//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_thing.h"

Thingp World::test_thing_ptr (uint32_t id)
{_
    auto index = id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        return (nullptr);
    }

    if (unlikely(p->id != id)) {
        DIE("invalid thing ptr, index %u, ID %08X != ID %08X",
            index, id, p->id);
    }

    verify(p->ptr);
    return (p->ptr);
}

Thingp World::find_thing_ptr (uint32_t id)
{_
    auto index = id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        DIE("thing ptr not found, index %u, ID %08X", index, id);
    }

    if (unlikely(p->id != id)) {
        DIE("invalid thing ptr, index %u, ID %08X != ID %08X",
            index, id, p->id);
    }

    verify(p->ptr);
    return (p->ptr);
}

void World::alloc_thing_id (Thingp t)
{_
    static uint32_t index = 1;

    for (uint32_t tries = 1; tries < MAX_THINGS; tries++) {
        if (!index) {
            index = 1;
        }
        if (index >= MAX_THINGS) {
            index = 1;
        }
        auto p = getptr(all_thing_ptrs, index);
        if (!p->ptr) {
            p->ptr = t;
            uint32_t idx = (myrand() & ~MAX_THINGS_MASK) | index;
            t->id = idx;
            p->id = idx;

#ifdef ENABLE_THING_ID_LOGS
            t->log("alloc index %u", index);
#endif
            index++;
            return;
        }
        index++;
    }
    DIE("out of thing indexes, hit max of %u", MAX_THINGS);
}

void World::free_thing_id (Thingp t)
{_
    uint32_t index = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (!p->ptr) {
        t->die("double free for thing ID %08X", t->id);
    }

    if (p->ptr != t) {
        t->die("wrong owner trying to free thing ID %08X", t->id);
    }

    if (p->id != t->id) {
        t->die("stale owner trying to free thing ID %08X", t->id);
    }

#ifdef ENABLE_THING_ID_LOGS
    t->log("free index %u", index);
#endif
    p->ptr = nullptr;
    p->id = 0;
    t->id = 0;
}

void World::realloc_thing_id (Thingp t)
{_
    if (!t->id) {
        t->die("trying to realloc when thing has no ID");
    }

    uint32_t index = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (p->ptr) {
        if (p->ptr == t) {
            t->die("index in use, cannot be realloc'd for same thing ID %08X",
                   t->id);
        } else {
            t->err("index in use by another thing, cannot be realloc'd by ID %08X",
                   t->id);
            p->ptr->die("realloc failed for ID, this is the current owner");
        }
    }

    p->ptr = t;
    p->id = t->id;
#ifdef ENABLE_THING_ID_LOGS
    t->log("realloc id, index %u", index);
#endif
}
