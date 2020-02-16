//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

ThingShoved Thing::try_to_shove (Thingp it, fpoint delta)
{
    if (!is_attack_shove()) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    if (!it->is_shovable()) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    fpoint shove_delta = delta;
    fpoint shove_pos = it->mid_at + shove_delta;
    if (it->collision_check_only(shove_pos)) {
        if (is_player()) {
            MINICON("The %s cannot be shoved!", it->to_name().c_str());
        } else if (it->is_player()) {
            MINICON("The %s fails to shove you!", to_name().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (it->get_stats_strength() > get_stats_strength()) {
        if (is_player()) {
            MINICON("The %s is too strong to be shoved!", 
                    it->to_name().c_str());
        } else if (it->is_player()) {
            MINICON("The %s is too weak to shove you!", 
                    to_name().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (is_player()) {
        MINICON("You shove the %s!", it->to_name().c_str());
    } else if (it->is_player()) {
        MINICON("The %s shoves you!", to_name().c_str());
    }

    it->move_to_immediately_delta(shove_delta);
    it->msg(string_sprintf("%%fg=red$!"));
    return (THING_SHOVE_TRIED_AND_PASSED);
}

ThingShoved Thing::try_to_shove (fpoint future_pos)
{
    if (!is_attack_shove()) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    auto x = future_pos.x;
    auto y = future_pos.y;
    auto delta = fpoint(x, y) - mid_at;
    point p(future_pos.x, future_pos.y);
    FOR_ALL_INTERESTING_THINGS(world, it, p.x, p.y) {
        if (this == it) {
            continue;
        }

        if (!it->is_shovable()) {
            continue;
        }

        fpoint shove_delta = delta;
        return (try_to_shove(it, shove_delta));
    }

    return (THING_SHOVE_NEVER_TRIED);
}
