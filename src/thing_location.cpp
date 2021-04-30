//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_ptrcheck.h"
#include "my_array_bounds_check.h"

//
// This is called if we move onto or fall onto a new location
//
// It is also called at the end of all moves for the current tick
// to handle things that do not move but something has happened to
// like they caught on fire
//
// True on something bad - level change or death
//
bool Thing::location_check_forced (void)
{_
    //
    // Prevent interactions that might generate things like smoke.
    //
    if (level->is_being_destroyed) {
        return false;
    }

    if (is_being_destroyed) {
        return false;
    }

    if (is_hidden) {
        return false;
    }

    //
    // Put chasm checks first as you can still fall when dead!
    //
    chasm_tick();
    if (is_dead) {
        return false;
    }
    brazier_tick();
    if (is_dead) {
        return false;
    }
    water_tick();
    if (is_dead) {
        return false;
    }
    lava_tick();
    if (is_dead) {
        return false;
    }
    acid_tick();
    if (is_dead) {
        return false;
    }
    fire_tick();
    if (is_dead) {
        return false;
    }

    if (descend_dungeon_tick()) {
        return false;
    }
    if (ascend_dungeon_tick()) {
        return false;
    }
    if (descend_sewer_tick()) {
        return false;
    }
    if (ascend_sewer_tick()) {
        return false;
    }

    return true;
}

bool Thing::location_check (void)
{_
    if (get_tick_last_location_check() == game->tick_current) {
        return false;
    }

    set_tick_last_location_check(game->tick_current);

    return location_check_forced();
}

//
// Check all things at this location
//
void Thing::location_check_all_things_at (void)
{_
    log("Do location checks");
    FOR_ALL_INTERESTING_THINGS(level, t, mid_at.x, mid_at.y) {_
        t->log("Do location check");
        t->location_check_forced();
    } FOR_ALL_THINGS_END()
}
