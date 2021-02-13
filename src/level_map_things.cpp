//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_ptrcheck.h"
#include "my_array_bounds_check.h"
// REMOVED #include "my_vector_bounds_check.h"

void Level::put_thing (int x, int y, ThingId id)
{_
    auto t = thing_find(id);
    if (!t) {
        return;
    }

    if (!id.id) {
        t->err("Null id at map (%d,%d)", x, y);
        return;
    }

    if (!t) {
        t->err("Oob at map (%d,%d) for put of %" PRIx32 "", x, y, id.id);
        return;
    }

    if (is_oob(x, y)) {
        t->err("Oob at map (%d,%d) for put of %" PRIx32 "", x, y, id.id);
        return;
    }

    int free_slot;
    int retry = 0;
do_retry:
    free_slot = -1;
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id == id.id) {
            if (g_opt_debug3) {
                t->log("Found %" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
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

        if (g_opt_debug3) {
            t->log("Put thing %p %" PRIx32 " at %u,%u slot %u", t, id.id, x, y, free_slot);
        }

        *idp = id;
        return;
    }

    //
    // Try to clean up some slots
    //
    if (retry < MAP_SLOTS) {
        t->log("Out of thing slots at map (%d,%d) for put of %" PRIx32 ", try to cleanup", x, y, id.id);
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            auto idp = &getref(all_thing_ids_at, x, y, slot);
            if (idp->id) {
                auto t = thing_find(*idp);
                if (!t) {
                    continue;
                }
                t->log("- slot %u", slot);
                if (t->is_removeable_if_out_of_slots()) {
                    t->dead("out of slots");
                    t->level_pop();
                    retry++;
                    goto do_retry;
                }
            }
        }
    }

    t->log("Out of thing slots at map (%d,%d) for put of %" PRIx32 ", see below:", x, y, id.id);

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        LOG("- slot %u %" PRIx32 "", slot, idp->id);
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id) {
            auto t = thing_find(*idp);
            if (!t) {
                continue;
            }
            t->log("- slot %u", slot);
        } else {
            t->log("- empty slot %u", slot);
        }
    }
    t->err("Out of thing slots at map (%d,%d) for put of %" PRIx32 "", x, y, id.id);
}

void Level::put_thing (point p, ThingId id)
{_
    put_thing(p.x, p.y, id);
}

void Level::remove_thing (int x, int y, ThingId id)
{_
    auto t = thing_find(id);
    if (!t) {
        ERR("Oob at map (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
        return;
    }

    if (is_oob(x, y)) {
        t->err("Oob at map (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
        return;
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (idp->id == id.id) {
            idp->id = 0;
            auto v = &all_thing_ptrs_at[x][y];
            auto b = v->begin();
            auto e = v->end();

            if (g_opt_debug3) {
                t->log("Rem thing %p %" PRIx32 " at %u,%u slot %u", t, id.id, x, y, slot);
            }

#ifdef SLOWER_BUT_USES_FANCY_STL
            auto r = std::remove_if(b, e, [t /* pass t by value */](Thingp x) { return (x == t); });
            v->erase(r, e);
#else
            bool found = false;
            for (auto i = b; i < e; i++) {
                if (*i == t) {
                    v->erase(i);
                    found = true;
                    break;
                }
            }

            if (!found) {
                // This happens when loading a fresh level
                //
                // t->err("Failed to remove thing %" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
#endif

#ifdef ENABLE_THING_ID_SANITY
            {
                for (auto x = 0; x < MAP_WIDTH; x++) {
                    for (auto y = 0; y < MAP_HEIGHT; y++) {
                        auto v = &all_thing_ptrs_at[x][y];
                        auto b = v->begin();
                        auto e = v->end();

                        for (auto i = b; i < e; i++) {
                            if (*i == t) {
                                t->err("Thing ptr still exists after removal %" PRIx32 " at %u,%u slot %u", 
                                    id.id, x, y, slot);
                            }
                        }
                    }
                }
            }
#endif
            return;
        }
    }
    t->err("Did not find thing in any slot at map (%d,%d) for remove of %" PRIx32 "", x, y, id.id);
}

void Level::remove_thing (point p, ThingId id)
{_
    remove_thing(p.x, p.y, id);
}
