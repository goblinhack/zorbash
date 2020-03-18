//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include <list>

std::string Thing::to_string (void)
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return (string_sprintf("%08X(<no tp>%s hp %d/%d @%g,%g)",
                               id,
                               is_dead ? "/dead" : "",
                               get_stats_health(),
                               get_stats_health_max(),
                               mid_at.x, mid_at.y));
    } else if (get_stats_health_max()) {
        return (string_sprintf("%08X(%s%s hp %d/%d @%g,%g)",
                               id, tpp->name.c_str(),
                               is_dead ? "/dead" : "",
                               get_stats_health(),
                               get_stats_health_max(),
                               mid_at.x, mid_at.y));
    } else {
        return (string_sprintf("%08X(%s%s @%g,%g)",
                               id, tpp->name.c_str(),
                               is_dead ? "/dead" : "",
                               mid_at.x, mid_at.y));
    }
}

std::string Thing::to_name (void)
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no tp>");
    }

    std::string real_name = "";

    if (is_undead()) {
        if (is_dead) {
            real_name += "inanimate ";
        } else {
            real_name += "undead ";
        }
    } else {
        if (is_dead) {
            real_name += "dead ";
        }
    }

    real_name += tpp->real_name;

    return (real_name);
}

const char * Thing::to_cstring (void)
{_
    return (to_string().c_str());
}
