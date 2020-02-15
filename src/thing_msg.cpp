//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::msg (std::string const &m)
{
    auto msg = thing_new("msg", mid_at);
    msg->set_msg(m);
    msg->fadeup(4.0, 0.05, 2000);
}
