//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::msg (std::string const &m)
{
    auto msg = level->thing_new("msg", mid_at);
    msg->set_msg(m);
    msg->fadeup(6.0, 0.05, 3000);
}
