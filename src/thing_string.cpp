//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_main.h"
#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"

std::string Thing::to_string (void) const
{_
    auto tpp = tp();
    verify(this);

    if (unlikely(!level)) {
        return (string_sprintf("<not in level> %" PRIx32 "(<no tp>%s%s%s%s%s%s @%g,%g)",
                               id,
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    }

    if (unlikely(!tpp)) {_
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(<no tp>%s%s%s%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id,
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    } else if (get_health_max() || is_tickable() || is_interesting()) {_
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s%s%s%s%s%s%s%s%s%s T%u @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               is_changing_level             ? "/chg-level" : "",
                               is_waiting_to_ascend_dungeon  ? "/asc-dung" : "",
                               is_waiting_to_descend_dungeon ? "/des-dung" : "",
                               is_waiting_to_descend_sewer   ? "/des-sewer" : "",
                               is_waiting_to_ascend_sewer    ? "/asc-sewer" : "",
                               game->tick_current,
                               mid_at.x, mid_at.y));
    } else {_
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s%s%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    }
}

std::string Thing::to_short_string (void) const
{_
    auto tpp = tp();
    verify(this);

    if (unlikely(!level)) {
        return (string_sprintf("<not in level> (<no tp>%s%s%s%s%s%s @%g,%g)",
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    }

    if (unlikely(!tpp)) {_
        return (string_sprintf("L%d,%d,%d (<no tp>%s%s%s%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    } else if (get_health_max() || is_tickable() || is_interesting()) {_
        return (string_sprintf("L%d,%d,%d (%s%s%s%s%s%s%s%s%s%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               tpp->name().c_str(),
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               is_changing_level             ? "/chg-level" : "",
                               is_waiting_to_ascend_dungeon  ? "/asc-dung" : "",
                               is_waiting_to_descend_dungeon ? "/des-dung" : "",
                               is_waiting_to_descend_sewer   ? "/des-sewer" : "",
                               is_waiting_to_ascend_sewer    ? "/asc-sewer" : "",
                               mid_at.x, mid_at.y));
    } else {_
        return (string_sprintf("L%d,%d,%d (%s%s%s%s%s%s%s @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead                       ? "/dead" : "",
                               is_on_fire()                  ? "/onfire" : "",
                               is_hidden                     ? "/hidden" : "",
                               is_jumping                    ? "/jumping" : "",
                               is_moving                     ? "/moving" : "",
                               is_falling                    ? "/falling" : "",
                               mid_at.x, mid_at.y));
    }
}
