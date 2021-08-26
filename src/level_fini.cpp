//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_main.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

Level::~Level (void)
{_
    log("Delete level");
    if (game->level == this) {
        log("Delete current game level");
        game->level = nullptr;
    }
    oldptr(this);
}

void Level::fini (void)
{_
    log("-");
    log("Destroying, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    is_being_destroyed = true;

    //
    // Destroying all things should detach them from all other places they
    // are referred to.
    //
    log("Destroy all things");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_things_id_at, x, y, z);
                if (id.ok()) {
#ifdef ENABLE_THING_ID_LOGS
                    LOG("Clean thing %08" PRIx32 " at %d,%d", id.id, x, y);
#endif
                    auto t = thing_find(id);
                    if (!t) {
                        continue;
                    }
#ifdef ENABLE_THING_ID_LOGS
                    t->log("Call delete");
#endif
                    delete t;
                }
            }
        }
    }

    log("Garbage collection of things still on the map:");
    things_gc_force();

    //
    // Check all things were fully detached
    //
    log("Check all things are detached");
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_things_id_at, x, y, z);
                if (id.ok()) {
                    err("Level fini: Did not detach thing id %08" PRIx32 " at %d,%d,%d", id.id, x, y, z);
                    auto t = thing_find(id);
                    if (!t) {
                        continue;
                    }
                    t->err("Level fini: Did not detach thing id from all_things_id_at");
                }
            }
        }
    }

    //
    // And finally the player
    //
    if (player) {
        err("Level fini: Did not detach player, player %p still set on level", player);
    }

    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    log("Destroyed, seed %u", seed);
    log("-");
}
