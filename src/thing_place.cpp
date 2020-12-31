//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::place (const std::string& what, const point &p)
{_
    level->thing_new(what, fpoint(p.x, p.y));

    return true;
}
