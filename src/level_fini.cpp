//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

Level::~Level(void)
{
  log("Delete level");
  TRACE_AND_INDENT();

  if (game->level == this) {
    log("Delete current game level");
    game->level = nullptr;
  }
  oldptr(MTYPE_LEVEL, this);
}

void Level::fini(void)
{
  TRACE_NO_INDENT();

  pcg_random_allowed++;

  IF_DEBUG2
  {
    log("-");
    log("Destroying, seed %u", seed);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v");
    TRACE_AND_INDENT();
  }

  is_being_destroyed = true;

  //
  // Destroying all things should detach them from all other places they
  // are referred to.
  //
  dbg("Destroy all things");

  {
    for (auto x = 0; x < MAP_WIDTH; ++x) {
      for (auto y = 0; y < MAP_HEIGHT; ++y) {
        for (auto z = 0; z < MAP_SLOTS; ++z) {
          auto id = get(all_things_id_at, x, y, z);
          if (id.ok()) {
#ifdef ENABLE_THING_ID_LOGS
            LOG("Clean thing %" PRIX32 " at %d,%d", id.id, x, y);
#endif
            auto t = thing_find(id);
            if (unlikely(! t)) {
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
  }
  dbg("Destroyed all things");

  dbg("Garbage collection of things still on the map:");
  things_gc_force();

  //
  // Check all things were fully detached
  //
  dbg("Check all things are detached");
  {
    for (auto x = 0; x < MAP_WIDTH; ++x) {
      for (auto y = 0; y < MAP_HEIGHT; ++y) {
        for (auto z = 0; z < MAP_SLOTS; ++z) {
          auto id = get(all_things_id_at, x, y, z);
          if (id.ok()) {
            err("Level fini: Did not detach thing id %" PRIX32 " at %d,%d,%d", id.id, x, y, z);
            auto t = thing_find(id);
            if (unlikely(! t)) {
              continue;
            }
            t->err("Level fini: Did not detach thing id from all_things_id_at");
          }
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

  IF_DEBUG2
  {
    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("Destroyed, seed %u", seed);
    log("-");
  }

  if (game->request_reset_state_change) {
    LOG("Handle deferred state to STATE_NORMAL");
    game->change_state(Game::STATE_NORMAL, "level fini, handle deferred state");
    game->unset_request_reset_state_change();
  }

  pcg_random_allowed--;
}
