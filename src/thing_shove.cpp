//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
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

    if (!is_player()) {
        if ((int)random_range(0, 1000) > tp()->is_attack_shove_chance_d1000()) {
            return (THING_SHOVE_NEVER_TRIED);
        }
    }

    fpoint shove_delta = delta;
    fpoint shove_pos = it->mid_at + shove_delta;
    if (it->collision_check_only(shove_pos)) {
        if (is_player()) {
            MINICON("%s cannot be shoved!", it->The().c_str());
        } else if (it->is_player()) {
            MINICON("%s fails to shove you!", The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (it->get_stats_strength() > get_stats_strength()) {
        if (is_player()) {
            MINICON("%s is too strong to be shoved!", it->The().c_str());
        } else if (it->is_player()) {
            MINICON("%s is too weak to shove you!", The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (is_player()) {
        MINICON("You shove %s!", it->the().c_str());
    } else if (it->is_player()) {
        MINICON("%s shoves you!", The().c_str());
    }

    if (it->is_dead_on_shove()) {
        it->dead("shoved");
        if (it->spawn_on_death() != "") {
            thing_new(it->spawn_on_death(), this);
        }
    }

    it->move_to_immediately_delta(shove_delta);
    if (it->is_monst()) {
        it->msg(string_sprintf("%%fg=red$!"));
    }

    if (it->is_flammable()) {
        set_on_fire();
    }
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
    FOR_ALL_INTERESTING_THINGS(level, it, p.x, p.y) {
        if (this == it) {
            continue;
        }

        if (!it->is_shovable()) {
            continue;
        }

        fpoint shove_delta = delta;
        return (try_to_shove(it, shove_delta));
    } FOR_ALL_THINGS_END()

    return (THING_SHOVE_NEVER_TRIED);
}

ThingShoved Thing::try_to_shove_into_hazard (Thingp it, fpoint delta)
{
    if (is_attack_shove()) {
        auto shoved_to_position = it->mid_at + delta;
        if (level->is_hazard((int)shoved_to_position.x,
                             (int)shoved_to_position.y)) {
            return (try_to_shove(it, delta));
        }
    }
    return (THING_SHOVE_NEVER_TRIED);
}
