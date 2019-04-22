//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

int Thing::hit_actual (Thingp orig_hitter,
                       Thingp real_hitter,
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
    if (is_player) {
        if (!time_have_x_tenths_passed_since(10, timestamp_last_i_was_hit)) {
            return (false);
        }
        timestamp_last_i_was_hit = time_get_time_ms_cached();
    }

    //
    // Keep hitting until all damage is used up or the thing is dead.
    //
    log("is hit! health %d, damage %d", health, damage);

    if (this == orig_hitter) {
        die("hitting thyself");
        return (false);
    }

    health -= damage;
    if (health <= 0) {
        health = 0;

        //
        // Record who dun it.
        //
        log("is hit terminally, health %d, damage %d, now dead",
            health, damage);
        dead(orig_hitter, "%s", real_hitter->to_string().c_str());
    } else {
        log("is hit by (%s) for %u, health now %d",
            orig_hitter->to_string().c_str(), damage, health);
    }

    return (true);
}

//
// Returns true on the target being dead.
//
int Thing::hit_if_possible (Thingp hitter, int damage)
{
    Thingp orig_hitter = hitter;

    //
    // If an arrow, who really fired it?
    //
    Thingp real_hitter = nullptr;

    if (hitter) {
        real_hitter = hitter->get_owner();
        if (!real_hitter) {
            real_hitter = hitter;
        }
    }

    Tpp weapon = nullptr;

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
    // Explosions are only dangerous in the intitial blast.
    //
    if (hitter && tp_is_explosion(hitter->tp)) {
        if (time_have_x_tenths_passed_since(10, hitter->timestamp_born)) {
            return (false);
        }
    }

    //
    // Check to see if this is a thing that can be damaged by the hitter.
    //
    if (hitter) {
        //
        // Walls and doors and other solid object are not damaged by poison
        // or similar effects. Limit it to explosions and the like.
        //
        if (tp_is_door(tp) || tp_is_wall(tp)) {

            if (!tp_is_explosion(hitter->tp)     &&
                !tp_is_projectile(hitter->tp)    &&
                !tp_gfx_is_weapon_use_anim(hitter->tp)) {
                //
                // Not something that typically damages walls.
                //
                return (false);
            }
        }

        if (tp_gfx_is_weapon_use_anim(hitter->tp)) {
            //
            // Get the player using the weapon as the hitter.
            //
            hitter = hitter->get_owner();
            if (!hitter) {
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->get_weapon();
            if (!weapon) {
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon);
            }

        } else if (hitter->get_owner()) {
            //
            // Get the player firing the weapon as the hitter.
            //
            hitter = hitter->get_owner();
            if (!hitter) {
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->get_weapon();
            if (!weapon) {
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon);
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

    hit_and_killed = hit_actual(orig_hitter, real_hitter, hitter, damage);

    return (hit_and_killed);
}

int Thing::hit_if_possible (Thingp hitter)
{
    return (hit_if_possible(hitter, 0));
}
