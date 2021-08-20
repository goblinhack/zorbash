//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Level::things_gc (bool force)
{
    if (all_gc_things.empty()) {
        return;
    }

    if (force) {
        dbg("Begin forced thing garbage collection");
    } else {
        dbg("Begin thing garbage collection");
    }
_
    for (auto it = all_gc_things.cbegin(), next_it = it;
         it != all_gc_things.cend(); it = next_it) {
	++next_it;

        auto id = it->first;
        auto t = thing_find(id);
        if (!t) {
            ERR("Thing %08" PRIx32 " not found to garbage collect", id.id);
            continue;
        }

        if (!force) {
            //
            // Allow the particles to finish
            //
            if (t->has_internal_particle) {
                if (DEBUG1) {
                    t->log("Thing garbage collect delayed due to internal particle");
                }
                continue;
            }

            if (t->has_external_particle) {
                if (DEBUG1) {
                    t->log("Thing garbage collect delayed due to external particle");
                }
                continue;
            }

            if (t->has_laser) {
                if (DEBUG1) {
                    t->log("Thing garbage collect delayed due to laser");
                }
                continue;
            }

            if (t->has_projectile) {
                if (DEBUG1) {
                    t->log("Thing garbage collect delayed due to projectile");
                }
                continue;
            }
	}

	all_gc_things.erase(it);

        if (t->is_monst()) {
            monst_count--;
        }

        if (DEBUG1) {
            t->log("Thing garbage collect");
        }

        delete t;
    }

    dbg("End thing garbage collection");
}

void Level::things_gc_force (void)
{_
    things_gc(true);
}

void Level::things_gc_if_possible (void)
{_
    things_gc(false);
}
