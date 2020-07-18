//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"

void Level::put_thing (int x, int y, ThingId id)
{_
    auto t = thing_find(id);

    if (!id.id) {
        t->err("null id at (%d,%d)", x, y);
    }

    if (!t) {
        t->err("oob at (%d,%d) for put of %" PRIx32 "", x, y, id.id);
    }

    if (is_oob(x, y)) {
        t->err("oob at (%d,%d) for put of %" PRIx32 "", x, y, id.id);
    }

    int free_slot;
    int retry = 0;
do_retry:
    free_slot = -1;
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id == id.id) {
#ifdef ENABLE_THING_ID_LOGS
            if (t->is_loggable_for_unimportant_stuff()) {
                t->log("found %" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
#endif
            return;
        }

        if ((!idp->id) && (free_slot == -1)) {
            free_slot = slot;
        }
    }

    if (free_slot != -1) {
        auto idp = &getref(all_thing_ids_at, x, y, free_slot);
        all_thing_ptrs_at[x][y].push_back(t);

        sort(all_thing_ptrs_at[x][y].begin(),
             all_thing_ptrs_at[x][y].end(),
             [](const Thingp &a, const Thingp &b) -> bool {
               return a->z_prio() < b->z_prio();
             });
#ifdef ENABLE_THING_ID_LOGS
        if (t->is_loggable_for_unimportant_stuff()) {
            t->log("put thing %" PRIx32 " at %u,%u slot %u", id.id, x, y, free_slot);
        }
#endif
        *idp = id;
        return;
    }

    //
    // Try to clean up some slots
    //
    if (retry < MAP_SLOTS) {
        t->log("out of thing slots at (%d,%d) for put of %" PRIx32 ", try to cleanup", x, y, id.id);
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            auto idp = &getref(all_thing_ids_at, x, y, slot);
            if (idp->id) {
                auto t = thing_find(*idp);
                t->log("- slot %u", slot);
                if (t->is_removable_if_out_of_slots()) {
                    t->dead("out of slots");
                    t->level_pop();
                    retry++;
                    goto do_retry;
                }
            }
        }
    }

    t->log("out of thing slots at (%d,%d) for put of %" PRIx32 ", see below:", x, y, id.id);

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        LOG("- slot %u %" PRIx32 "", slot, idp->id);
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id) {
            auto t = thing_find(*idp);
            t->log("- slot %u", slot);
        } else {
            t->log("- empty slot %u", slot);
        }
    }
    t->err("out of thing slots at (%d,%d) for put of %" PRIx32 "", x, y, id.id);
}

void Level::put_thing (point p, ThingId id)
{_
    put_thing(p.x, p.y, id);
}

void Level::remove_thing (int x, int y, ThingId id)
{_
    auto t = thing_find(id);
    if (!t) {
        ERR("oob at (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
    }

    if (is_oob(x, y)) {
        t->err("oob at (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
        return;
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id == id.id) {
            idp->id = 0;
            auto v = &all_thing_ptrs_at[x][y];
            auto b = v->begin();
            auto e = v->end();

#ifdef SLOWER_BUT_USES_FANCY_STL
            auto r = std::remove_if(b, e, [t /* pass t by value */](Thingp x) { return (x == t); });
            v->erase(r, e);
#else
            for (auto i = b; i < e; i++) {
                if (*i == t) {
                    v->erase(i);
                    break;
                }
            }
#endif

#ifdef ENABLE_THING_ID_LOGS
            if (t->is_loggable_for_unimportant_stuff()) {
                t->log("rem thing %" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
#endif
            return;
        }
    }
    t->err("did not find thing in any slot at (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
}

void Level::remove_thing (point p, ThingId id)
{_
    remove_thing(p.x, p.y, id);
}
