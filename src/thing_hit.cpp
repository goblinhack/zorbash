/*
 * Copyright (C) 2011-2017 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

int Thing::thing_hit_actual (Thingp orig_hitter, 
                             Thingp real_hitter, 
                             Thingp hitter, 
                             int damage)
{
    /*
     * Cruel to let things keep on hitting you when you're dead
     */
    if (is_dead) {
        return (false);
    }

    if (!damage) {
        /*
         * Could be a spider silkball
         */
        return (false);
    }

    /*
     * Protect player from multiple impact - landing hard on a spike.
     */
    if (is_player) {
        if (!time_have_x_tenths_passed_since(10, timestamp_last_i_was_hit)) {
            return (false);
        }
        timestamp_last_i_was_hit = time_get_time_ms();
    }

    if (hitter) {
        if (tp_is_spikes(hitter->tp)) {
            /*
             * Spikes only hurt if you land on them!
             */
            if (fall_speed < 0.05) {
                return (false);
            }

            if (tp_is_monst(tp) ||
                tp_is_player(tp)) {
                hitter->is_bloodied = true;
            }
        }
    }

    /*
     * Keep hitting until all damage is used up or the thing is dead.
     */
    log("Is hit! hp %d, damage %d", hp, damage);

    if (this == orig_hitter) {
        die("hitting thyself");
        return (false);
    }

    hp -= damage;
    if (hp <= 0) {
        hp = 0;

        /*
         * Record who dun it.
         */
        log("Is hit terminally, hp %d, damage %d, now dead", hp, damage);
        dead(orig_hitter, "%s", real_hitter->logname().c_str());
    } else {
        log("Is hit by (%s) for %u, hp now %d",
            orig_hitter->logname().c_str(), damage, hp);
    }

    return (true);
}

/*
 * Returns true on the target being dead.
 */
int Thing::thing_hit_possible (Thingp hitter, int damage)
{
    Thingp orig_hitter = hitter;

    /*
     * If an arrow, who really fired it?
     */
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

    /*
     * Cruel to let things keep on hitting you when you're dead
     */
    if (is_dead) {
        return (false);
    }

    if (hitter && hitter->is_dead) {
        /*
         * This case is hit if a ghost runs into a player. The ghost takes
         * damage. We don't want the player to keep absorbing hits when
         * already dead though.
         */
        return (false);
    }

    /*
     * Explosions are only dangerous in the intitial blast.
     */
    if (hitter && tp_is_explosion(hitter->tp)) {
        if (time_have_x_tenths_passed_since(10, hitter->timestamp_born)) {
            return (false);
        }
    }

    /*
     * Check to see if this is a thing that can be damaged by the hitter.
     */
    if (hitter) {
        /*
         * Walls and doors and other solid object are not damaged by poison
         * or similar effects. Limit it to explosions and the like.
         */
        if (tp_is_door(tp) || tp_is_wall(tp)) {

            if (!tp_is_explosion(hitter->tp)     &&
                !tp_is_projectile(hitter->tp)    &&
                !tp_is_weapon_swing_effect(hitter->tp)) {
                /*
                 * Not something that typically damages walls.
                 */
                return (false);
            }
        }

        if (tp_is_weapon_swing_effect(hitter->tp)) {
            /*
             * Get the player swinging the weapon as the hitter.
             */
            hitter = hitter->get_owner();
            if (!hitter) {
                return (false);
            }

            verify(hitter);

            /*
             * Get the damage from the weapon being used to swing.
             */
            weapon = hitter->get_weapon();
            if (!weapon) {
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon);
            }

        } else if (hitter->get_owner()) {
            /*
             * Get the player firing the weapon as the hitter.
             */
            hitter = hitter->get_owner();
            if (!hitter) {
                return (false);
            }

            verify(hitter);

            /*
             * Get the damage from the weapon being used to swing.
             */
            weapon = hitter->get_weapon();
            if (!weapon) {
                return (false);
            }

            if (!damage) {
                damage = tp_weapon_damage(weapon);
            }
        }

        /*
         * Don't let our own potion hit ourselves!
         */
        if (hitter == this) {
            return (false);
        }
    }

    int hit_and_killed;

    hit_and_killed = thing_hit_actual(orig_hitter, real_hitter, hitter, damage);

    return (hit_and_killed);
}
