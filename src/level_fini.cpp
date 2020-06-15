//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_level.h"
#include "my_thing.h"

void Level::fini (void)
{_
    log("-");
    log("destroying, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    //
    // Destroying all things should detach them from all other places they
    // are referred to.
    //
    log("destroy all things");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id.ok()) {
#ifdef ENABLE_THING_ID_LOGS
                    LOG("clean thing %" PRIx64 " at %u,%u", id, x, y);
#endif
                    auto t = thing_find(id);
                    delete t;
                }
            }
        }
    }

    log("garbage collection of things still on the map:");
    things_gc();

    //
    // Check all things were fully detached
    //
    log("check all things are detached");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id.ok()) {
                    err("level fini: did not detach thing id %" PRIx64 " at %d,%d,%d", id.id, x, y, z);
                    auto t = thing_find(id);
                    t->err("level fini: did not detach thing id from all_thing_ids_at");
                }
            }
        }
    }

    //
    // Check for pointers too
    //
    log("check all things ids are released");
    for (auto slot = 0; slot < MAX_THINGS; slot++) {
        auto p = get(all_thing_ptrs, slot);
        if (p.ptr) {
            err("level fini: did not detach thing %p/%" PRIx64 "", p.ptr, p.id.id);
            auto t = p.ptr;
            verify(t);
            t->err("level fini: did not detach thing from all_thing_ptrs_at");
        }
    }

    //
    // And finally the player
    //
    if (player) {
        err("level fini: did not detach player");
    }

    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("destroyed, seed %u", seed);
    log("-");
}
