//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"

std::string Level::to_string (void)
{_
    return ("L" + world_at.to_string());
}
