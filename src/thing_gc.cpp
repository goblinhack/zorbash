//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

void Level::things_gc (void)
{_
    if (all_gc_things.empty()) {
        return;
    }

    log("Begin thing garbage collection");
_
    for (auto it = all_gc_things.cbegin(), next_it = it; 
         it != all_gc_things.cend(); it = next_it) {
	++next_it;

        auto id = it->first;
        auto t = thing_find(id);
        if (!t) {
            ERR("Thing %" PRIx32 " not found to garbage collect", id.id);
            continue;
        }

	//
	// Allow the particles to finish
	//
	if (t->has_internal_particle) {
            t->log("Thing garbage collect delayed due to internal particle");
	    continue;
	}

	if (t->has_external_particle) {
            t->log("Thing garbage collect delayed due to external particle");
	    continue;
	}

	all_gc_things.erase(it);

        if (t->is_monst()) {
            monst_count--;
        }

        t->log("Thing garbage collect");

        delete t;
    }
}

void Thing::gc (void)
{_
    auto result = level->all_gc_things.insert(std::pair(id, this));
    if (result.second == false) {
        err("Failed to insert into gc thing map");
    }
}

