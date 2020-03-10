//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Level::put_thing (int x, int y, uint32_t id)
{_
    auto t = thing_find(id);
    if (!id) {
        t->err("null id at (%d,%d)", x, y);
    }

    if (!t) {
        t->err("oob at (%d,%d) for put of %08X", x, y, id);
    }

    if (is_oob(x, y)) {
        t->err("oob at (%d,%d) for put of %08X", x, y, id);
    }

    int free_slot = -1;
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (*idp == id) {
#ifdef ENABLE_THING_ID_LOGS
            if (t->is_loggable()) {
                t->log("found %08X at %u,%u slot %u", id, x, y, slot);
            }
#endif
            return;
        }

        if ((!*idp) && (free_slot == -1)) {
            free_slot = slot;
        }
    }

    if (free_slot != -1) {
        auto idp = &getref(all_thing_ids_at, x, y, free_slot);
        auto t_p = &getref(all_thing_ptrs_at, x, y, free_slot);
#ifdef ENABLE_THING_ID_LOGS
        if (t->is_loggable()) {
            t->log("put thing %08X at %u,%u slot %u", id, x, y, free_slot);
        }
#endif
        *idp = id;
        *t_p = t;
        return;
    }

    t->log("out of thing slots at (%d,%d) for put of %08X, see below:",
           x, y, id);

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        LOG("- slot %u %08X", slot, *idp);
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
    t->err("out of thing slots at (%d,%d) for put of %08X", x, y, id);
}

void Level::put_thing (point p, uint32_t id)
{_
    put_thing(p.x, p.y, id);
}

void Level::remove_thing (int x, int y, uint32_t id)
{_
    auto t = thing_find(id);
    if (!t) {
        ERR("oob at (%d,%d) for remove of %08X", x, y, id);
    }

    if (is_oob(x, y)) {
        t->err("oob at (%d,%d) for remove of %08X", x, y, id);
        return;
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto idp = &getref(all_thing_ids_at, x, y, slot);
        if (*idp == id) {
            auto t_p = &getref(all_thing_ptrs_at, x, y, slot);
            *idp = 0;
            *t_p = 0;
#ifdef ENABLE_THING_ID_LOGS
            if (t->is_loggable()) {
                t->log("rem thing %08X at %u,%u slot %u", id, x, y, slot);
            }
#endif
            return;
        }
    }
    t->err("did not find thing in any slot at (%d,%d) for remove of %08X",
           x, y, id);
}

void Level::remove_thing (point p, uint32_t id)
{_
    remove_thing(p.x, p.y, id);
}
