//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing_template.h"
#include "my_depth.h"
#include "my_tile.h"
#include "my_dice.h"
#include "my_random.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_thing.h"

void tp_fixup (void)
{_
    for (auto& tp : tp_id_map) {
        if (tp->stamina()) {
            tp->set_is_stamina_check(true);
        }

        if (tp->is_tickable()) {
            tp->set_is_interesting(true);
        }

        if (tp->is_very_combustible()) {
            tp->set_is_combustible(true);
        }

        if (tp->is_able_to_fire_at()) {
            if (!tp->ai_vision_distance()) {
                DIE("Tp %s needs vision distance if it is able to fire at things",
                    tp->name().c_str());
            }
        }

        if (tp->is_interesting()) {
            if (tp->is_tmp_thing()) {
                DIE("Tp %s cannot be both interesting and temporary",
                    tp->name().c_str());
            }
        }
    }

    for (auto& tp : tp_name_map) {
        auto tpp = tp.second;
        if (!tpp->lifespan_dice_str().empty()) {
            if (!tpp->is_tickable()) {
                DIE("Thing template must be set to be is_tickable [%s] for lifespan tick to work", tp.first.c_str());
            }
        }
    }
}
