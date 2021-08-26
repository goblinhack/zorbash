//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_ptrcheck.h"
#include "my_array_bounds_check.h"

void Level::put_thing (int x, int y, ThingId id, int group)
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
        t->err("Oob at map (%d,%d) for put of %08" PRIx32 "", x, y, id.id);
        return;
    }

    if (is_oob(x, y)) {
        t->err("Oob at map (%d,%d) for put of %08" PRIx32 "", x, y, id.id);
        return;
    }

    int free_slot;
    int retry = 0;
do_retry:
    free_slot = -1;
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_things_id_at[group], x, y, slot);
        if (idp->id == id.id) {
            if (DEBUG5) {
                t->log("Found %08" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
            return;
        }

        if ((!idp->id) && (free_slot == -1)) {
            free_slot = slot;
        }
    }

    if (free_slot != -1) {
        auto idp = &getref(all_things_id_at[group], x, y, free_slot);
        all_things_ptr_at[group][x][y].push_back(t);

        sort(all_things_ptr_at[group][x][y].begin(),
             all_things_ptr_at[group][x][y].end(),
             [](const Thingp &a, const Thingp &b) -> bool {
               return a->z_prio() < b->z_prio();
             });

        if (DEBUG5) {
            t->log("Put thing %p %08" PRIx32 " at %u,%u slot %u", t, id.id, x, y, free_slot);
        }

        *idp = id;
        return;
    }

    //
    // Try to clean up some slots
    //
    if (retry < MAP_SLOTS) {
        t->log("Out of thing slots at map (%d,%d) for put of %08" PRIx32 ", try to cleanup", x, y, id.id);
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            auto idp = &getref(all_things_id_at[group], x, y, slot);
            if (idp->id) {
                auto t = thing_find(*idp);
                if (!t) {
                    continue;
                }
                t->log("- slot %u", slot);
                if (t->is_removeable_if_out_of_slots()) {
                    t->dead("by internal slot");
                    t->level_pop();
                    retry++;
                    goto do_retry;
                }
            }
        }
    }

    t->log("Out of thing slots at map (%d,%d) for put of %08" PRIx32 ", see below:", x, y, id.id);

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_things_id_at[group], x, y, slot);
        LOG("- slot %u %08" PRIx32 "", slot, idp->id);
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_things_id_at[group], x, y, slot);
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
    t->err("Out of thing slots at map (%d,%d) for put of %08" PRIx32 "", x, y, id.id);
}

void Level::put_thing (point p, ThingId id, int group)
{_
    put_thing(p.x, p.y, id, group);
}

void Level::remove_thing (int x, int y, ThingId id, int group)
{_
    auto t = thing_find(id);
    if (!t) {
        ERR("Oob at map (%d,%d) for remove of %08" PRIx32 "", x, y, id.id);
        return;
    }

    if (is_oob(x, y)) {
        t->err("Oob at map (%d,%d) for remove of %08" PRIx32 "", x, y, id.id);
        return;
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_things_id_at[group], x, y, slot);
        if (idp->id == id.id) {
            idp->id = 0;
            auto v = &all_things_ptr_at[group][x][y];
            auto b = v->begin();
            auto e = v->end();

            if (DEBUG5) {
                t->log("Rem thing %p %08" PRIx32 " at %u,%u slot %u", t, id.id, x, y, slot);
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
                // t->err("Failed to remove thing %08" PRIx32 " at %u,%u slot %u", id.id, x, y, slot);
            }
#endif

#ifdef ENABLE_THING_ID_SANITY
            {
                for (auto x = 0; x < MAP_WIDTH; x++) {
                    for (auto y = 0; y < MAP_HEIGHT; y++) {
                        auto v = &all_things_ptr_at[group][x][y];
                        auto b = v->begin();
                        auto e = v->end();

                        for (auto i = b; i < e; i++) {
                            if (*i == t) {
                                t->err("Thing ptr still exists after removal %08" PRIx32 " at %u,%u slot %u",
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
    t->err("Did not find thing in any slot at map (%d,%d) for remove of %08" PRIx32 "", x, y, id.id);
}

void Level::remove_thing (point p, ThingId id, int group)
{_
    remove_thing(p.x, p.y, id, group);
}
