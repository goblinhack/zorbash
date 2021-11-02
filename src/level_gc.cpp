//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_traceback.hpp"

void Level::things_gc(bool force)
{
  if (force) {
    dbg("Begin forced thing garbage collection");
  } else {
    dbg("Begin thing garbage collection");
  }

  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
    if (all_things_to_be_destroyed[ group ].empty()) {
      continue;
    }

    for (auto it = all_things_to_be_destroyed[ group ].cbegin(), next_it = it;
         it != all_things_to_be_destroyed[ group ].cend(); it = next_it) {
      ++next_it;

      auto id = it->first;
      LOG("Thing %08" PRIx32 " garbage collect", id.id);

      auto t = thing_find(id);
      if (! t) {
        ERR("Thing %08" PRIx32 " not found to garbage collect", id.id);
        continue;
      }

      if (! force) {
        //
        // Allow the particles to finish
        //
        if (t->has_internal_particle) {
          IF_DEBUG3 { t->log("Thing garbage collect delayed due to internal particle"); }
          continue;
        }

        if (t->has_external_particle) {
          IF_DEBUG3 { t->log("Thing garbage collect delayed due to external particle"); }
          continue;
        }

        if (t->has_laser) {
          IF_DEBUG3 { t->log("Thing garbage collect delayed due to laser"); }
          continue;
        }

        if (t->has_projectile) {
          IF_DEBUG3 { t->log("Thing garbage collect delayed due to projectile"); }
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

  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
    for (auto &i : all_things_of_interest_pending_remove[ group ]) {
      all_things_of_interest[ group ].erase(i.first);
    }
    all_things_of_interest_pending_remove[ group ] = {};

    for (auto &i : all_things_of_interest_pending_add[ group ]) {
      all_things_of_interest[ group ].insert(i);
    }
    all_things_of_interest_pending_add[ group ] = {};
  }

  dbg("End thing garbage collection");
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
