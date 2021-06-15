//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_thing.h"

void Thing::rest (void)
{_
    dbg("Resting");
    stamina_boost(1);
}
