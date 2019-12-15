//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include <list>

static_assert(MAP_WIDTH  <= (1 << World::x_bits), "MAP_WIDTH overflow");
static_assert(MAP_HEIGHT <= (1 << World::y_bits), "MAP_HEIGHT overflow");
static_assert(MAP_SLOTS  <= (1 << World::slots_bits), "MAP_SLOTS overflow");

void World::put_thing_ptr (uint16_t x, uint16_t y, Thingp t)
{
    auto r = world->next_thing_id;

    if (unlikely(is_oob(x, y))) {
        t->die("oob at %d %d", x, y);
    }

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        auto p = &getref(all_thing_ptrs_at, x, y, slot);
        if (*p == nullptr) {
            *p = t;
            t->id = x | (y << y_shift) | (slot << slots_shift) | ++r << r_shift;
            return;
        }
    }
    t->die("out of thing slots at %d %d", x, y);
}

void World::remove_thing_ptr (Thingp t)
{
    uint32_t x = t->id & x_mask;
    uint32_t y = (t->id & y_mask) >> y_shift;
    uint32_t slot = (t->id & slots_mask) >> slots_shift;

    auto p = &getref(all_thing_ptrs_at, x, y, slot);
    if (unlikely(!*p)) {
        t->die("thing ptr not found at x %u y %u slot %u", x, y, slot);
    }

    if (unlikely(*p != t)) {
        t->die("thing mismatch at x %u y %u slot %u", x, y, slot);
    }
    *p = nullptr;
    t->id = 0;
}
