//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

bool Thing::try_to_shove (fpoint future_pos)
{
    auto x = future_pos.x;
    auto y = future_pos.y;
    auto delta = fpoint(x, y) - mid_at;

    if (!is_attack_shove()) {
        return (false);
    }

    point p(future_pos.x, future_pos.y);
    FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
        if (!it->is_shovable()) {
            continue;
        }

        fpoint shove_delta = delta;
        fpoint shove_pos = it->mid_at + shove_delta;
        if (it->collision_check_only(shove_pos)) {
            MINICON("The %s cannot be shoved!", it->to_name().c_str());
            return (false);
        }

        if (it->get_stats_strength() > get_stats_strength()) {
            MINICON("The %s resists being shoved and pushes back!", 
                    it->to_name().c_str());
            return (false);
        }

        MINICON("You shove the %s!", it->to_name().c_str());
        it->move_to_immediately_delta(shove_delta);
        it->msg(string_sprintf("%%fg=red$!"));
        return (true);
    }
    return (false);
}
