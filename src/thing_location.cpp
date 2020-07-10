//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"

//
// True on something bad - level change or death
//
bool Thing::location_check (void)
{
    torch_tick();
    if (is_dead) {
        return (false);
    }
    water_tick();
    if (is_dead) {
        return (false);
    }
    chasm_tick();
    if (is_dead) {
        return (false);
    }
    lava_tick();
    if (is_dead) {
        return (false);
    }
    acid_tick();
    if (is_dead) {
        return (false);
    }
    if (exit_tick()) {
        return (false);
    }
    if (entrance_tick()) {
        return (false);
    }
    return (true);
}
