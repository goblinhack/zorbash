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

Thingp Level::test_thing_ptr (uint32_t id)
{_
    auto index = id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        return (nullptr);
    }

    if (unlikely(p->id != id)) {
        ERR("invalid thing ptr, index %u, %08X != %08X", index, id, p->id);
    }

    verify(p->ptr);
    return (p->ptr);
}

Thingp Level::find_thing_ptr (uint32_t id)
{_
    auto index = id % MAX_THINGS;
    auto p = &all_thing_ptrs[index];
    if (unlikely(!p->ptr)) {
        ERR("thing ptr not found, index %u, %08X", index, id);
    }

    if (unlikely(p->id != id)) {
        ERR("invalid thing ptr, index %u, %08X != %08X",
            index, id, p->id);
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
    ERR("out of thing indexes, hit max of %u", MAX_THINGS);
}

void Level::free_thing_id (Thingp t)
{_
    uint32_t index = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (!p->ptr) {
        t->err("double free for thing %08X", t->id);
    }

    if (p->ptr != t) {
        t->err("wrong owner trying to free thing %08X", t->id);
    }

    if (p->id != t->id) {
        t->err("stale owner trying to free thing %08X", t->id);
    }

#ifdef ENABLE_THING_ID_LOGS
    t->log("free index %u, %p, %08X", index, t, t->id);
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

    uint32_t index = t->id & MAX_THINGS_MASK;
    auto p = getptr(all_thing_ptrs, index);
    if (p->ptr) {
        if (p->ptr == t) {
            t->err("index in use, cannot be realloc'd for same thing %08X",
                   t->id);
        } else {
            t->err("index in use by another thing %p, cannot be realloc'd by %p, %08X",
                   p->ptr, t, t->id);
            p->ptr->err("realloc failed for ID, this is the current owner");
        }
    }

    p->ptr = t;
    p->id = t->id;
#ifdef ENABLE_THING_ID_LOGS
    t->log("realloc id, index %u", index);
#endif
}
