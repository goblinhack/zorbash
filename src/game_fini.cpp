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
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = all_thing_ids_at[x][y][z];
                if (id) {
                    auto t = thing_find(id);
                    verify(t);
                    delete t;
                }
            }
        }
    }

    //
    // Check all things were fully detached
    //
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = all_thing_ids_at[x][y][z];
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
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto t = all_thing_ptrs_at[x][y][z];
                if (t) {
                    t->die("world fini: did not detach thing from all_thing_ptrs_at");
                }
            }
        }
    }

    //
    // Check all lights were removed
    //
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto p : lights[x][y]) {
                auto l = p.second;
                verify(l);
                l->die("world fini: did not detach light %u", l->id);
            }
        }
    }

    //
    // And finally the player
    //
    if (player) {
        DIE("world fini: did not detach player");
    }
}

void Config::fini (void)
{_
}

void Game::fini (void)
{
    fps_count = 0;
    config.fini();
    world.fini();
}
