//
// Copyright goblinhack@gmail.com
// See the README file for license info.
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
        return (string_sprintf("%" PRIx32 "(<no tp>%s @%g,%g)",
                               id,
                               is_dead ? "/dead" : "",
                               mid_at.x, mid_at.y));
//        return (string_sprintf("%" PRIx32 "(<no tp>%s hp %d/%d @%g,%g)",
//                               id,
//                               is_dead ? "/dead" : "",
//                               get_stats_health(),
//                               get_stats_health_max(),
//                               mid_at.x, mid_at.y));
    } else if (get_stats_health_max()) {
        return (string_sprintf("%" PRIx32 "(%s%s @%g,%g)",
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               mid_at.x, mid_at.y));
//        return (string_sprintf("%" PRIx32 "(%s%s hp %d/%d @%g,%g)",
//                               id, tpp->name.c_str(),
//                               is_dead ? "/dead" : "",
//                               get_stats_health(),
//                               get_stats_health_max(),
//                               mid_at.x, mid_at.y));
    } else {
        return (string_sprintf("%" PRIx32 "(%s%s @%g,%g)",
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               mid_at.x, mid_at.y));
    }
}

const char * Thing::to_cstring (void)
{_
    return (to_string().c_str());
}
