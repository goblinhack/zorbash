//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"

int Thing::ai_hit_actual (Thingp orig_hitter, // e.g. an arrow or monst
                          Thingp real_hitter, // if an arrow, who fired it
                          Thingp hitter,
                          int damage)
{
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
    // Protect player from multiple impact - landing hard on a spike.
    //
    if (is_player()) {
        if (!time_have_x_tenths_passed_since(10,
                                             get_timestamp_last_i_was_hit())) {
            return (false);
        }
        set_timestamp_last_i_was_hit(time_get_time_ms_cached());
    }

    //
    // Keep hitting until all damage is used up or the thing is dead.
    //
    if (this == orig_hitter) {
        die("hitting thyself");
        return (false);
    }

    auto h = decr_health(damage);
    if (h <= 0) {
        h = set_health(0);

        //
        // Record who dun it.
        //
        // log("is hit terminally, health %d, damage %d, now dead",
        //     h, damage);
        dead(orig_hitter, "is hit terminally by %s",
             real_hitter->to_string().c_str());
    } else {
        log("is hit by (%s) for %u, health now %d",
            orig_hitter->to_string().c_str(), damage, h);
    }

    return (true);
}

//
// Returns true on the target being dead.
//
int Thing::ai_ai_hit_if_possible (Thingp hitter, int damage)
{
    Thingp orig_hitter = hitter;

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
    }

    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        return (false);
    }

    if (hitter && hitter->is_dead) {
        //
        // This case is hit if a ghost runs into a player. The ghost takes
        // damage. We don't want the player to keep absorbing hits when
        // already dead though.
        //
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
                !tp_gfx_is_weapon_use_anim(hitter_tp)) {
                //
                // Not something that typically damages walls.
                //
                return (false);
            }
        }

        if (tp_gfx_is_weapon_use_anim(hitter_tp)) {
            //
            // Get the player using the weapon as the hitter.
            //
            hitter = hitter->owner_get();
            if (!hitter) {
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
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
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
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
            return (false);
        }
    }

    int hit_and_killed;

    hit_and_killed = ai_hit_actual(orig_hitter, real_hitter, hitter, damage);

    return (hit_and_killed);
}

int Thing::ai_ai_hit_if_possible (Thingp hitter)
{
    return (ai_ai_hit_if_possible(hitter, 0));
}
