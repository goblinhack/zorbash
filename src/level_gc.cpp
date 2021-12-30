//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_backtrace.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::things_gc(bool force)
{
  FOR_ALL_THING_GROUPS(group)
  {
    if (all_things_to_be_destroyed[ group ].empty()) {
      continue;
    }

    for (auto it = all_things_to_be_destroyed[ group ].cbegin(), next_it = it;
         it != all_things_to_be_destroyed[ group ].cend(); it = next_it) {
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

        if (t->has_laser) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to laser"); }
          continue;
        }

        if (t->has_projectile) {
          IF_DEBUG2 { t->log("Thing garbage collect delayed due to projectile"); }
          continue;
        }
      }

      all_things_to_be_destroyed[ group ].erase(it);

      if (t->is_monst()) {
        monst_count--;
      }

      IF_DEBUG3 { t->log("Thing garbage collect"); }

      delete t;
    }
  }

  FOR_ALL_THING_GROUPS(group)
  {
    for (auto &i : all_things_of_interest_pending_remove[ group ]) {
      all_things_of_interest[ group ].erase(i.first);
    }
    all_things_of_interest_pending_remove[ group ] = {};

    for (auto &i : all_things_of_interest_pending_add[ group ]) {
      all_things_of_interest[ group ].insert(i);
    }
    all_things_of_interest_pending_add[ group ] = {};
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
