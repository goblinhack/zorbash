//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_thing.h"

Thingp Level::test_thing_ptr (ThingId id)
{_
    auto index = id.id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        return (nullptr);
    }

    if (unlikely(p->id != id)) {
        ERR("invalid thing ptr, index %u, %" PRIx64 " != %" PRIx64 "", (int)index, id.id, p->id.id);
    }

    verify(p->ptr);
    return (p->ptr);
}

Thingp Level::find_thing_ptr (ThingId id)
{_
    auto index = id.id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        ERR("thing ptr not found, index %u, %" PRIx64 "", (int)index, id.id);
    }

    if (unlikely(p->id != id)) {
        ERR("invalid thing ptr, index %u, %" PRIx64 " != %" PRIx64 "", (int)index, id.id, p->id.id);
    }

    verify(p->ptr);
    return (p->ptr);
}

void Level::alloc_thing_id (Thingp t)
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
            uint64_t idx = (myrand() & ~MAX_THINGS_MASK) | index;
            ThingId id(idx);
            t->id = id;
            p->id = id;

#ifdef ENABLE_THING_ID_LOGS
            t->log("alloc index %u", index);
#endif
            index++;
            return;
        }
        index++;
    }
    ERR("out of thing indexes, hit max of %u", MAX_THINGS);
}

void Level::free_thing_id (Thingp t)
{_
    auto index = t->id.id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (!p->ptr) {
        t->err("double free for thing %" PRIx64 "", t->id.id);
    }

    if (p->ptr != t) {
        t->err("wrong owner trying to free thing %" PRIx64 "", t->id.id);
    }

    if (p->id != t->id) {
        t->err("stale owner trying to free thing %" PRIx64 "", t->id.id);
    }

#ifdef ENABLE_THING_ID_LOGS
    t->log("free index %u, %p, %" PRIx64 "", (int)index, t, t->id.id);
#endif
    p->ptr = nullptr;
    p->id = 0;
    t->id = 0;
}

void Level::realloc_thing_id (Thingp t)
{_
    if (!t->id) {
        t->err("trying to realloc when thing has no ID");
    }

    uint32_t index = t->id.id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (p->ptr) {
        if (p->ptr == t) {
            t->err("index in use, cannot be realloc'd for same thing %" PRIx64 "", t->id.id);
        } else {
            t->err("index in use by another thing %p, cannot be realloc'd by %p, %" PRIx64 "", p->ptr, t, t->id.id);
            p->ptr->err("realloc failed for ID, this is the current owner");
        }
    }

    p->ptr = t;
    p->id = t->id;
#ifdef ENABLE_THING_ID_LOGS
    t->log("realloc id, index %u", index);
#endif
}
