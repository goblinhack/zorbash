//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
  if (all_things_to_be_destroyed.empty()) {
    return;
  }

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

  {
    for (auto &i : all_things_of_interest_pending_remove) {
      all_things_of_interest.erase(i.first);
    }
    all_things_of_interest_pending_remove = {};

    for (auto &i : all_things_of_interest_pending_add) {
      all_things_of_interest.insert(i);
    }
    all_things_of_interest_pending_add = {};
  }
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
