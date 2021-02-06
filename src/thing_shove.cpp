//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_ptrcheck.h"

ThingShoved Thing::try_to_shove (Thingp it, fpoint delta)
{_
    if (!attack_shove()) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    if (!it->is_shovable()) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    //
    // Sanity check
    //
    if ((fabs(delta.x) > 1) || (fabs(delta.y) > 1)) {
        return (THING_SHOVE_NEVER_TRIED);
    }

    if (!is_player()) {
        if ((int)random_range(0, 1000) > tp()->attack_shove_chance_d1000()) {
            return (THING_SHOVE_NEVER_TRIED);
        }
    }

    bool was_dead = it->is_dead;

    //
    // If I'm on fire. set it on fire too!
    //
    if (get_on_fire_anim_id().ok()) {
        it->set_on_fire("I am on fire, set it on fire too");
    }

    //
    // Annoy the thing being pushed
    //
    it->add_enemy(this);

    fpoint shove_delta = delta;
    fpoint shove_pos = it->mid_at + shove_delta;

    if (it->monst_size() - monst_size() > 1) {
        if (is_player()) {
            MINICON("%s is too large to be shoved!", it->text_The().c_str());
        } else if (it->is_player()) {
            MINICON("%s fails to shove you!", text_The().c_str());
        }
        return (THING_SHOVE_TRIED_AND_FAILED);
    }

    if (!it->is_torch()) {
        if (it->collision_check_only(shove_pos)) {
            if (is_player()) {
                MINICON("%s cannot be shoved!", it->text_The().c_str());
            } else if (it->is_player()) {
                MINICON("%s fails to shove you!", text_The().c_str());
            }
            return (THING_SHOVE_TRIED_AND_FAILED);
        }
    }

    if (!it->is_dead) {
        log("Shove: it strength %d vs me %d",
            it->get_modifier_strength(), get_modifier_strength());

        if (!d20roll(get_modifier_strength(), it->get_modifier_strength())) {
            if (is_player()) {
                MINICON("%s shoves you back!", it->text_The().c_str());
            } else if (it->is_player()) {
                MINICON("%s fails to shove you!", text_The().c_str());
            }
            return (THING_SHOVE_TRIED_AND_FAILED);
        }

        if (is_player()) {
            if (it->is_torch()) {
                MINICON("You knock over %s!", it->text_the().c_str());
            } else {
                MINICON("You shove %s!", it->text_the().c_str());
            }
        } else if (it->is_player()) {
            MINICON("%s shoves you!", text_The().c_str());
        }

        if (it->is_monst()) {
            it->msg(string_sprintf("%%fg=orange$!"));
        }
    }

    //
    // If pushed into a chasm, move the thing first and then
    // let it spawn dead things
    //
    log("Make the shoved thing fall first");
    if (it->collision_check_only(shove_pos)) {
        if (is_player()) {
            if (it->is_torch()) {
                if (!it->is_dead) {
                    MINICON("The torch falls back on you!");
                }
            }
            it->move_to(mid_at, 100);
        }
    } else {
        it->move_to(shove_pos, 100);
    }

    if (!it->is_dead) {
        if (it->is_dead_on_shove()) {
            log("Shove and kill");
            it->dead("shoved");
            auto spawn_what = it->spawn_on_shoved();
            if (spawn_what != "") {
                auto spawn_at = it->mid_at;
                if (spawn_at.x > mid_at.x) {
                    it->dir_set_left();
                } else {
                    it->dir_set_right();
                }
                auto n = level->thing_new(spawn_what, spawn_at);
                n->location_check();
            }
        }
    }

    log("Handle location for shoved thing");
    it->location_check();

    //
    // If shoving something on fire! set yourself on fire!
    //
    if (!was_dead) {
        if (it->is_flammable()) {
            if (random_range(0, 100) < 5) {
                if (is_player()) {
                    if (set_on_fire("set youtself on fire")) {
                        MINICON("%%fg=red$Clumsy! You set yourself on fire!%%fg=reset$");
                    }
                }
            } else {
                if (is_player()) {
                    MINICON("%%fg=orange$It burns as you shove it, but you avoid the flames");
                }
            }
        }
    }

    return (THING_SHOVE_TRIED_AND_PASSED);
}

ThingShoved Thing::try_to_shove (fpoint future_pos)
{
    if (!attack_shove()) {
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
    if (attack_shove()) {
        auto shoved_to_position = it->mid_at + delta;
        if (level->is_hazard((int)shoved_to_position.x,
                             (int)shoved_to_position.y)) {
            return (try_to_shove(it, delta));
        }
    }
    return (THING_SHOVE_NEVER_TRIED);
}
