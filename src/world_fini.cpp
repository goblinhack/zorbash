/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

void World::fini (void)
{_
    //
    // Destroying all things should detach them from all other places they
    // are referred to.
    //
    LOG("world fini: destroy all things");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id) {
#ifdef ENABLE_THING_ID_LOGS
                    LOG("clean thing ID %08X at %u,%u", id, x, y);
#endif
                    auto t = thing_find(id);

                    //
                    // If already dead, then we will clean this up in thing_gc
                    //
                    if (!t->is_pending_gc) {
                        delete t;
                    }
                }
            }
        }
    }

    LOG("world fini: thing garbage collection:");
    thing_gc();

    //
    // Check all things were fully detached
    //
    LOG("world fini: check all things are detached");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id) {
                    auto t = thing_find(id);
                    t->die("world fini: did not detach thing id from all_thing_ids_at");
                }
            }
        }
    }

    //
    // Check for pointers too
    //
    LOG("world fini: check all things ids are released");
    for (auto slot = 0; slot < MAX_THINGS; slot++) {
        auto p = get(all_thing_ptrs, slot);
        if (p.ptr) {
            ERR("world fini: did not detach thing %p/ID %08X", p.ptr, p.id);
            auto t = p.ptr;
            verify(t);
            t->die("world fini: did not detach thing from all_thing_ptrs_at");
        }
    }

    //
    // And finally the player
    //
    if (player) {
        DIE("world fini: did not detach player");
    }
}
