//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_game.h"

void Thing::msg (std::string const &m)
{
    static float last_at;
    float dy;

    //
    // Stop msgs piling up in the same tick
    //
    if (last_at == mid_at.y) {
        dy = 2.0;
    } else {
        dy = 0.0;
    }

    last_at = mid_at.y - dy;

    auto msg = level->thing_new("msg", mid_at - fpoint(0, dy));
    msg->set_msg(m);
    msg->fadeup(6.0, 0.05, 3000);
}
