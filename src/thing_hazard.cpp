//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_thing_template.h"

int Thing::is_hazardous_to_me (point p)
{
    if (level->is_chasm(p)) {
        if (!is_floating()) {
            return true;
        }
    }

    if (level->is_lava(p)) {
        if (hates_fire()) {
            return true;
        }
    }

    int heat = level->heatmap(p);
    if (heat >= 10) {
        if (hates_fire()) {
            return true;
        }
    }

    if (level->is_shallow_water(p) || level->is_deep_water(p)) {
        if (hates_water()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (hates_acid()) {
            return true;
        }
    }

    return false;
}
