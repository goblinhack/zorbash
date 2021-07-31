//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_globals.h"
#include "my_thing_template.h"

void Thing::fire_tick (void)
{_
    fpoint at = get_interpolated_mid_at();
    if (is_burnable() || is_combustible() || is_very_combustible()) {
        //
        // Keep going
        //
    } else if (!hates_fire()) {
        if (unlikely(g_opt_debug4)) {
            dbg("No, is not fire avoider");
        }
        return;
    }

    bool hit = false;

    if (is_on_fire()) {
        //
        // Give the player a chance
        //
        if (!level->is_smoke(at.x, at.y)) {
            hit = ((int)pcq_random_range(0, 100) < 90);
            if (!hit) {
                if (is_player()) {
                    TOPCON("%%fg=green$You feel a brief cool breeze and reprieve from the flames!%%fg=reset$");

                    //
                    // Smoke ensures a reprieve.
                    //
                    if (!level->is_smoke(at.x, at.y)) {
                        auto smoke = level->thing_new("smoke", at);
                        smoke->set_lifespan(pcq_random_range(1, 10));
                    }
                }
            }
        } else {
            hit = false;
        }
    } else if (is_very_combustible() && level->heatmap(at.x, at.y)) {
        //
        // Too close to the flames
        //
        hit = true;
    } else if (is_combustible() && (level->heatmap(at.x, at.y) > 2)) {
        //
        // Too close to the flames
        //
        hit = ((int)pcq_random_range(0, 100) < 70);
    } else if (level->is_fire(at.x, at.y)) {
        //
        // Give the player a chance
        //
        if (!level->is_smoke(at.x, at.y)) {
            auto smoke = level->thing_new("smoke", at);
            smoke->set_lifespan(pcq_random_range(1, 10));

            hit = ((int)pcq_random_range(0, 100) < 20);
            if (hit) {
                if (is_player()) {
                    TOPCON("%%fg=red$The flames wrap around you!%%fg=reset$");
                }
            } else {
                if (is_player()) {
                    TOPCON("%%fg=red$You dodge the flames.%%fg=reset$");
                }
            }
        } else {
            hit = false;
        }
    }

    if (hit) {
        if (!is_on_fire()) {
            set_on_fire("caught fire");
        }

        auto fire = tp_find("fire");
        auto damage = fire->get_damage_melee();

        if (hates_fire()) {
            damage *= 2;
        }

        auto h = decr_health(damage);
        if (is_player()) {
            TOPCON("%%fg=red$You take %u burn damage!%%fg=reset$", damage);
        }

        if (h <= 0) {
            h = set_health(0);
            dead("by burning");
        }

        if (!level->is_smoke(at.x, at.y)) {
            auto smoke = level->thing_new("smoke", at);
            smoke->set_lifespan(pcq_random_range(1, 10));
        }
    }
}
