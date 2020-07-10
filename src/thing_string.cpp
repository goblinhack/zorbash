//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

std::string Thing::to_string (void) const
{_
    auto tpp = tp();

    verify(this);
    verify(tpp);

    if (unlikely(!tpp)) {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(<no tp>%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id,
                               is_dead ? "/dead" : "",
                               is_falling ? "/falling" : "",
                               mid_at.x, mid_at.y));
//        return (string_sprintf("%" PRIx32 "(<no tp>%s hp %d/%d @%g,%g)",
//                               id,
//                               is_dead ? "/dead" : "",
//                               get_stats_health(),
//                               get_stats_health_max(),
//                               mid_at.x, mid_at.y));
    } else if (get_stats_health_max()) {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               is_falling ? "/falling" : "",
                               mid_at.x, mid_at.y));
//        return (string_sprintf("%" PRIx32 "(%s%s hp %d/%d @%g,%g)",
//                               id, tpp->name.c_str(),
//                               is_dead ? "/dead" : "",
//                               get_stats_health(),
//                               get_stats_health_max(),
//                               mid_at.x, mid_at.y));
    } else {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               is_falling ? "/falling" : "",
                               mid_at.x, mid_at.y));
    }
}

const char * Thing::to_cstring (void) const
{_
    return (to_string().c_str());
}
