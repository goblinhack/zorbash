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
    //
    // Put chasm checks first as you can still fall when dead!
    //
    chasm_tick();
    if (is_dead) {
        return (false);
    }
    torch_tick();
    if (is_dead) {
        return (false);
    }
    water_tick();
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

    auto ret = true;
    if (exit_tick()) {
        ret = false;
    } else if (entrance_tick()) {
        ret = false;
    }
    return (ret);
}
