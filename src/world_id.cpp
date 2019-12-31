//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"

void World::put_thing (int x, int y, uint32_t id)
{_
    auto t = thing_find(id);
    if (!id) {
        t->die("null id at (%d,%d)", x, y);
    }

    if (!t) {
        t->die("oob at (%d,%d) for put of ID %08X", x, y, id);
    }

    if (is_oob(x, y)) {
        t->die("oob at (%d,%d) for put of ID %08X", x, y, id);
    }

    int free_slot = -1;
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (*idp == id) {
#ifdef ENABLE_THING_ID_LOGS
            t->log("found ID %08X at %u,%u slot %u", id, x, y, slot);
#endif
            return;
        }

        if ((!*idp) && (free_slot == -1)) {
            free_slot = slot;
        }
    }

    if (free_slot != -1) {
        auto idp = &getref(all_thing_ids_at, x, y, free_slot);
#ifdef ENABLE_THING_ID_LOGS
        t->log("put thing ID %08X at %u,%u slot %u", id, x, y, free_slot);
#endif
        *idp = id;
        return;
    }

    t->log("out of thing slots at (%d,%d) for put of ID %08X, see below:",
           x, y, id);

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        LOG("- slot %u ID %08X", slot, *idp);
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (*idp) {
            auto t = thing_find(*idp);
            t->log("- slot %u", slot);
        } else {
            t->log("- empty slot %u", slot);
        }
    }
    t->die("out of thing slots at (%d,%d) for put of ID %08X", x, y, id);
}

void World::put_thing (point p, uint32_t id)
{_
    put_thing(p.x, p.y, id);
}

void World::remove_thing (int x, int y, uint32_t id)
{_
    auto t = thing_find(id);
    if (!t) {
        DIE("oob at (%d,%d) for remove of ID %08X", x, y, id);
    }

    if (is_oob(x, y)) {
        t->die("oob at (%d,%d) for remove of ID %08X", x, y, id);
        return;
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (*idp == id) {
            *idp = 0;
#ifdef ENABLE_THING_ID_LOGS
            t->log("rem thing ID %08X at %u,%u slot %u", id, x, y, slot);
#endif
            return;
        }
    }
    t->die("did not find thing in any slot at (%d,%d) for remove of ID %08X",
           x, y, id);
}

void World::remove_thing (point p, uint32_t id)
{_
    remove_thing(p.x, p.y, id);
}
