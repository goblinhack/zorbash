//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"

std::string Level::to_string (void)
{_
    return (world_at.to_string());
}

const char * Level::to_cstring (void)
{_
    return (to_string().c_str());
}
