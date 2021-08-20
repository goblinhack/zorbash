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
        return (string_sprintf("<not in level> %08" PRIx32 "(<no tp>%s%s%s%s%s%s @%g,%g)",
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
        return (string_sprintf("L%d,%d,%d %08" PRIx32 "(<no tp>%s%s%s%s%s%s @%g,%g)",
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
        return (string_sprintf("L%d,%d,%d %08" PRIx32 "(%s%s%s%s%s%s%s%s%s%s%s%s @%g,%g)",
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
                               mid_at.x, mid_at.y));
    } else {_
        return (string_sprintf("L%d,%d,%d %08" PRIx32 "(%s%s%s%s%s%s%s @%g,%g)",
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

std::string Thing::to_dbg_string (void) const
{_
    verify(this);

    return (string_sprintf("L%d,%d,%d %08" PRIx32 " %s (@%g,%g)%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s)",
                            level->world_at.x,
                            level->world_at.y,
                            level->world_at.z,
                            id,
                            tp() ? tp()->name().c_str() : "notp",
                            mid_at.x, mid_at.y,
                            has_ever_moved                  ?  ", has_ever_moved" : "",
                            has_external_particle           ?  ", has_external_particle" : "",
                            has_internal_particle           ?  ", has_internal_particle" : "",
                            has_laser                       ?  ", has_laser" : "",
                            has_light                       ?  ", has_light" : "",
                            has_projectile                  ?  ", has_projectile" : "",
                            is_activated                    ?  ", is_activated" : "",
                            is_attached                     ?  ", is_attached" : "",
                            is_being_destroyed              ?  ", is_being_destroyed" : "",
                            is_bouncing                     ?  ", is_bouncing" : "",
                            is_changing_level               ?  ", is_changing_level" : "",
                            is_dead                         ?  ", is_dead" : "",
                            is_scheduled_for_death               ?  ", is_scheduled_for_death" : "",
                            is_dying                        ?  ", is_dying" : "",
                            is_facing_left                  ?  ", is_facing_left" : "",
                            is_fadeup                       ?  ", is_fadeup" : "",
                            is_falling                      ?  ", is_falling" : "",
                            is_hidden                       ?  ", is_hidden" : "",
                            is_hungry                       ?  ", is_hungry" : "",
                            is_in_lava                      ?  ", is_in_lava" : "",
                            is_in_water                     ?  ", is_in_water" : "",
                            is_jumping                      ?  ", is_jumping" : "",
                            is_moving                       ?  ", is_moving" : "",
                            is_offscreen                    ?  ", is_offscreen" : "",
                            is_open                         ?  ", is_open" : "",
                            is_resurrected                  ?  ", is_resurrected" : "",
                            is_resurrecting                 ?  ", is_resurrecting" : "",
                            is_resurrection_blocked         ?  ", is_resurrection_blocked" : "",
                            is_sleeping                     ?  ", is_sleeping" : "",
                            is_starving                     ?  ", is_starving" : "",
                            is_the_grid                     ?  ", is_the_grid" : "",
                            is_waiting_to_ascend_dungeon    ?  ", is_waiting_to_ascend_dungeon" : "",
                            is_waiting_to_ascend_sewer      ?  ", is_waiting_to_ascend_sewer" : "",
                            is_waiting_to_descend_dungeon   ?  ", is_waiting_to_descend_dungeon" : "",
                            is_waiting_to_descend_sewer     ?  ", is_waiting_to_descend_sewer" : "",
                            is_waiting_to_fall              ?  ", is_waiting_to_fall" : "",
                            i_set_gfx_water                 ?  ", i_set_gfx_water" : "",
                            i_set_is_acid                   ?  ", i_set_is_acid" : "",
                            i_set_is_ascend_dungeon         ?  ", i_set_is_ascend_dungeon" : "",
                            i_set_is_ascend_sewer           ?  ", i_set_is_ascend_sewer" : "",
                            i_set_is_barrel                 ?  ", i_set_is_barrel" : "",
                            i_set_is_blood                  ?  ", i_set_is_blood" : "",
                            i_set_is_brazier                ?  ", i_set_is_brazier" : "",
                            i_set_is_bridge                 ?  ", i_set_is_bridge" : "",
                            i_set_is_chasm                  ?  ", i_set_is_chasm" : "",
                            i_set_is_corpse                 ?  ", i_set_is_corpse" : "",
                            i_set_is_corridor               ?  ", i_set_is_corridor" : "",
                            i_set_is_deep_water             ?  ", i_set_is_deep_water" : "",
                            i_set_is_descend_dungeon        ?  ", i_set_is_descend_dungeon" : "",
                            i_set_is_descend_sewer          ?  ", i_set_is_descend_sewer" : "",
                            i_set_is_dirt                   ?  ", i_set_is_dirt" : "",
                            i_set_is_door                   ?  ", i_set_is_door" : "",
                            i_set_is_dry_grass              ?  ", i_set_is_dry_grass" : "",
                            i_set_is_enchantstone           ?  ", i_set_is_enchantstone" : "",
                            i_set_is_extreme_hazard         ?  ", i_set_is_extreme_hazard" : "",
                            i_set_is_fire                   ?  ", i_set_is_fire" : "",
                            i_set_is_floor                  ?  ", i_set_is_floor" : "",
                            i_set_is_foilage                ?  ", i_set_is_foilage" : "",
                            i_set_is_food                   ?  ", i_set_is_food" : "",
                            i_set_is_gold                   ?  ", i_set_is_gold" : "",
                            i_set_is_hazard                 ?  ", i_set_is_hazard" : "",
                            i_set_is_key                    ?  ", i_set_is_key" : "",
                            i_set_is_lava                   ?  ", i_set_is_lava" : "",
                            i_set_is_light_blocker          ?  ", i_set_is_light_blocker" : "",
                            i_set_is_minion_generator       ?  ", i_set_is_minion_generator" : "",
                            i_set_is_monst                  ?  ", i_set_is_monst" : "",
                            i_set_is_movement_blocking_hard ?  ", i_set_is_movement_blocking_hard" : "",
                            i_set_is_movement_blocking_soft ?  ", i_set_is_movement_blocking_soft" : "",
                            i_set_is_poison                 ?  ", i_set_is_poison" : "",
                            i_set_is_potion                 ?  ", i_set_is_potion" : "",
                            i_set_is_ripple                 ?  ", i_set_is_ripple" : "",
                            i_set_is_rock                   ?  ", i_set_is_rock" : "",
                            i_set_is_secret_door            ?  ", i_set_is_secret_door" : "",
                            i_set_is_shallow_water          ?  ", i_set_is_shallow_water" : "",
                            i_set_is_skillstone             ?  ", i_set_is_skillstone" : "",
                            i_set_is_smoke                  ?  ", i_set_is_smoke" : "",
                            i_set_is_spiderweb              ?  ", i_set_is_spiderweb" : "",
                            i_set_is_sticky                 ?  ", i_set_is_sticky" : "",
                            i_set_is_treasure_class_a       ?  ", i_set_is_treasure_class_a" : "",
                            i_set_is_treasure_class_b       ?  ", i_set_is_treasure_class_b" : "",
                            i_set_is_treasure_class_c       ?  ", i_set_is_treasure_class_c" : "",
                            i_set_is_treasure_type          ?  ", i_set_is_treasure_type" : "",
                            i_set_is_wall                   ?  ", i_set_is_wall" : "",
                            i_set_is_wand                   ?  ", i_set_is_wand" : ""
                ));
}
