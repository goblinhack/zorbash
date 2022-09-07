//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_color.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include <cinttypes> // PRIX32

void Level::things_gc(bool force)
{
  if (! all_things_to_be_destroyed.empty()) {
    for (auto it = all_things_to_be_destroyed.cbegin(), next_it = it; it != all_things_to_be_destroyed.cend();
         it = next_it) {
      ++next_it;

      auto id = it->first;
      DBG3("Thing %" PRIX32 " garbage collect", id.id);

      auto t = thing_find(id);
      if (unlikely(! t)) {
        ERR("Thing %" PRIX32 " not found to garbage collect", id.id);
        continue;
      }

      if (! force) {
        //
        // Allow the particles to finish
        //
        if (t->has_internal_particle) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to internal particle"); }
          continue;
        }

        if (t->has_external_particle) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to external particle"); }
          continue;
        }

        if (t->laser_count) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to laser"); }
          continue;
        }

        if (t->has_projectile) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to projectile"); }
          continue;
        }
      }

      all_things_to_be_destroyed.erase(it);

      if (t->is_monst()) {
        monst_count--;
      }

      IF_DEBUG3 { t->log("Thing garbage collect"); }

      delete t;
    }
  }

  for (auto &i : interesting_things_pending_remove) {
    interesting_things.erase(i.first);
  }
  interesting_things_pending_remove = {};

  for (auto &i : interesting_things_pending_add) {
    interesting_things.insert(i);
  }
  interesting_things_pending_add = {};

  for (auto &i : tickable_things_pending_remove) {
    tickable_things.erase(i.first);
  }
  tickable_things_pending_remove = {};

  for (auto &i : tickable_things_pending_add) {
    tickable_things.insert(i);
  }
  tickable_things_pending_add = {};

  for (auto &i : describable_things_pending_remove) {
    describable_things.erase(i.first);
  }
  describable_things_pending_remove = {};

  for (auto &i : describable_things_pending_add) {
    describable_things.insert(i);
  }
  describable_things_pending_add = {};
}

void Level::things_gc_force(void)
{
  TRACE_AND_INDENT();
  things_gc(true);
}

void Level::things_gc_if_possible(void)
{
  TRACE_AND_INDENT();
  things_gc(false);
}
