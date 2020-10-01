//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::rest (void)
{_
    log("resting");
    stamina_boost(1);
}
