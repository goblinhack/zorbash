//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_sprintf.h"

int Thing::ai_hit_actual (Thingp hitter,      // an arrow / monst /...
                          Thingp real_hitter, // who fired the arrow?
                          int damage)
{_
    auto delta = mid_at - hitter->mid_at;

    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        return (false);
    }

    if (!damage) {
        return (false);
    }

    //
    // Keep hitting until all damage is used up or the thing is dead.
    //
    if (this == hitter) {
        die("hitting thyself");
        return (false);
    }

    //
    // If hit by something then abort following any path
    //
    cursor_path_stop();

    if (tp_gfx_bounce_on_move(real_hitter->tp())) {
        real_hitter->bounce(0.5, 0.1, 100, 3);
        real_hitter->move_set_dir_from_delta(delta);
    }

    //
    // Try to push the thing into a hazard if we can just to be sneaky
    //
    switch (hitter->try_to_shove_into_hazard(this, delta)) {
        case THING_SHOVE_TRIED_AND_FAILED:
            return (true);
        case THING_SHOVE_TRIED_AND_PASSED:
            return (true);
        case THING_SHOVE_NEVER_TRIED:
            break;
    }

    if (is_player()) {
        MINICON("%%fg=yellow$%s hits for %d damage!%%fg=reset$",
                real_hitter->The().c_str(), damage);
    } else {
        add_enemy(real_hitter);
    }

    //
    // Visible hit indication
    //
    if (is_player()) {
        msg(string_sprintf("%%fg=red$-%d", damage));
    } else if (is_monst()) {
        msg(string_sprintf("%%fg=white$-%d", damage));
    }

    //
    // Blood splat
    //
    thing_new(tp_name(tp_random_blood_splatter()), mid_at);

    //
    // Visible claw attack?
    //
    if (is_monst() || is_player()) {
        auto claws = tp_weapon_use_anim(real_hitter->tp());
        if (claws != "") {
            auto claw_attack = thing_new(claws, mid_at);
            claw_attack->bounce(0.1, 0.1, 100, 3);
            claw_attack->move_set_dir_from_delta(delta);
        }
    }

    auto h = decr_stats_health(damage);
    if (h <= 0) {
        h = set_stats_health(0);

        //
        // Record who dun it.
        //
        log("is killed by (%s) for %u, health now %d",
            real_hitter->to_string().c_str(), damage, h);
        std::string killer = real_hitter->a_or_an();
        auto reason = "Killed by " + killer;
        dead(hitter, reason);
    } else {
        log("is hit by (%s) for %u, health now %d",
            real_hitter->to_string().c_str(), damage, h);
    }

    return (true);
}

//
// Returns true on the target being dead.
//
int Thing::ai_hit_if_possible (Thingp hitter, int damage)
{_
    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        return (false);
    }

    log("possible attack by (%s) for %u", 
        hitter->to_string().c_str(), damage);

    //
    // If an arrow, who really fired it?
    //
    Thingp real_hitter = nullptr;

    if (hitter) {
        real_hitter = hitter->owner_get();
        if (!real_hitter) {
            real_hitter = hitter;
        }
    }

    Thingp weapon = nullptr;

    if (hitter) {
        verify(hitter);

        //
        // Don't attack more than allowed
        //
        if (!time_have_x_tenths_passed_since(
                hitter->get_stats_attack_rate_tenths(),
                hitter->get_timestamp_last_attack())) {
            log(" ignore, too-frequent attack");
            return (false);
        }
        hitter->set_timestamp_last_attack(time_get_time_ms_cached());
    }

    if (hitter && hitter->is_dead) {
        //
        // This case is hit if a ghost runs into a player. The ghost takes
        // damage. We don't want the player to keep absorbing hits when
        // already dead though.
        //
        log(" ignore, attacker is dead");
        return (false);
    }

    //
    // Check to see if this is a thing that can be damaged by the hitter.
    //
    if (hitter) {
        //
        // Walls and doors and other solid object are not damaged by poison
        // or similar effects. Limit it to explosions and the like.
        //
        auto hitter_tp = hitter->tp();
        if (is_door() || is_wall()) {
            if (!tp_is_explosion(hitter_tp)     &&
                !tp_is_projectile(hitter_tp)    &&
                !tp_gfx_is_attack_anim(hitter_tp)) {
                //
                // Not something that typically damages walls.
                //
                log(" ignore weapon, immune");
                return (false);
            }
        }

        if (tp_gfx_is_attack_anim(hitter_tp)) {
            //
            // Get the player using the weapon as the hitter.
            //
            hitter = hitter->owner_get();
            if (!hitter) {
                log(" ignore weapon, no owner");
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                log(" ignore weapon, no weapon");
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon->tp());
            }

        } else if (hitter->owner_get()) {
            //
            // Get the player firing the weapon as the hitter.
            //
            hitter = hitter->owner_get();
            if (!hitter) {
                log(" ignore hitter, no owner");
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                log(" ignore hitter, no weapon");
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon->tp());
            }
        }

        //
        // Don't let our own potion hit ourselves!
        //
        if (hitter == this) {
            log(" ignore, do not hit self");
            return (false);
        }
    }

    int hit_and_killed;

    hit_and_killed = ai_hit_actual(real_hitter, hitter, damage);

    return (hit_and_killed);
}

int Thing::ai_hit_if_possible (Thingp hitter)
{_
    return (ai_hit_if_possible(hitter, 0));
}
