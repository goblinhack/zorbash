//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
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
        hitter->log("hit fails, it's dead");
        return (false);
    }

    if (is_slime_baby()) {
        if (hitter->is_slime_baby()) {
            level->thing_new("slime2", mid_at);
            log("slimes combine!");
            dead(this, "combined");
            hitter->dead(hitter, "combined");
            return (true);
        }
    }

    if (!damage) {
        hitter->log("hit fails, no damage");
        return (false);
    }

    //
    // If hit by something then abort following any path
    //
    cursor_path_stop();

    if (real_hitter->tp()->gfx_bounce_on_move()) {
        real_hitter->bounce(0.5, 0.1, 100, 3);
        real_hitter->move_set_dir_from_delta(delta);
    }

    //
    // Try to push the thing into a hazard if we can just to be sneaky
    //
    if (this == hitter) {
        //
        // On fire?
        //
    } else if (hitter->is_monst()) {
        switch (hitter->try_to_shove_into_hazard(this, delta)) {
            case THING_SHOVE_TRIED_AND_FAILED:
                return (true);
            case THING_SHOVE_TRIED_AND_PASSED:
                return (true);
            case THING_SHOVE_NEVER_TRIED:
                break;
        }
    }

    if (is_fire_hater()) {
        if (real_hitter->is_fire() ||
            real_hitter->is_lava()) {
            if (is_double_damage_from_fire()) {
                damage *= 2;
                log("double damage from fire");
            }
        }
    }

    if (is_acid_hater()) {
        if (real_hitter->is_acid()) {
            if (is_double_damage_from_acid()) {
                damage *= 2;
                log("double damage from acid");
            }
        }
    }

    if (is_water_hater()) {
        if (real_hitter->is_water()) {
            if (is_double_damage_from_water()) {
                damage *= 2;
                log("double damage from water");
            }
        }
    }

    //
    // Try to steal
    //
    if (real_hitter->is_item_eater()) {
        if (is_carrying_item()) {
            if (real_hitter->steal_item_from(this)) {
                return (true);
            }
        }
    }

    if (is_player()) {
        if (real_hitter->is_fire() ||
            real_hitter->is_lava()) {
            if (set_on_fire()) {
                MINICON("%%fg=red$You are ON FIRE!%%fg=reset$");
            }
        }

        if (damage > THING_DAMAGE_SHAKE_ABOVE) {
            level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
            MINICON("%%fg=red$%s %s for %d damage!%%fg=reset$",
                    real_hitter->text_The().c_str(),
                    real_hitter->text_hits().c_str(),
                    damage);
        } else {
            MINICON("%%fg=yellow$%s %s for %d damage!%%fg=reset$",
                    real_hitter->text_The().c_str(),
                    real_hitter->text_hits().c_str(),
                    damage);
        }

        if (is_bloodied()) {
            level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
        }
    } else {
        if (real_hitter->is_player()) {
            MINICON("You hit the %s for %d damage!",
                    text_the().c_str(), damage);
        }
        if (real_hitter->is_fire() ||
            real_hitter->is_lava()) {
            set_on_fire();
        }
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
    // Don't have things like lava doing catchup ticks when you
    // run around and then stop on top of lava!
    //
    if (real_hitter->tick_catches_up_on_attack()) {
        real_hitter->set_tick_last_did_something(game->tick_current);
        real_hitter->set_tick(game->tick_current);
    }

    //
    // Blood splat
    //
    if (is_monst()) {
        level->thing_new(tp_random_blood_splatter()->name(), mid_at);
    }

    if (real_hitter->is_player() ||
        real_hitter->is_monst()) {
        wobble(90);
        bounce(0.5 /* height */, 0.1 /* fade */, 100, 1);
    }

    // 
    // Are we carrying a weapon? If not, see if we can do a claw attack
    //
    if (!real_hitter->is_player()) {
        if (!real_hitter->get_weapon_id_carry_anim().ok()) {
            auto claws = real_hitter->tp()->gfx_anim_attack();
            if (claws != "") {
                auto claw_attack = level->thing_new(claws, mid_at);
                claw_attack->bounce(0.1, 0.1, 100, 3);
                claw_attack->move_set_dir_from_delta(delta);
            }
        }
    }

    auto h = decr_stats_health(damage);
    if (h <= 0) {
        h = set_stats_health(0);

        //
        // Record who dun it.
        //
        log("is killed by (%s) %u damage, health now %d",
            real_hitter->to_string().c_str(), damage, h);
        std::string killer = real_hitter->text_a_or_an();
        auto reason = "killed by " + killer;
        dead(real_hitter, reason);

        //
        // Does the attacker feast on success?
        //
        if (real_hitter->will_eat(this)) {
            real_hitter->eat(this);
        }
    } else {
        log("is hit by (%s) %u damage, health now %d",
            real_hitter->to_string().c_str(), damage, h);
    }

    return (true);
}

//
// Returns true on the target being dead.
//
int Thing::is_hit_by (Thingp hitter, int damage)
{_
    hitter->log("possible hit %s for %u", to_string().c_str(), damage);
_
    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        hitter->log("no, it's dead");
        return (false);
    }

    if (is_resurrecting) {
        hitter->log("no, it's resurrecting");
        return (false);
    }

    //
    // If an arrow, who really fired it?
    //
    Thingp real_hitter = nullptr;

    if (hitter) {
        real_hitter = hitter->owner_get();

        //
        // If on fire, the fire is owned by the player. So don't make the
        // player the real hitter.
        //
        if (real_hitter == this) {
            real_hitter = nullptr;
        }

        if (!real_hitter) {
            real_hitter = hitter;
        }
    }

//    Thingp weapon = nullptr;

    if (hitter && hitter->is_dead) {
        //
        // This case is hit if a ghost runs into a player. The ghost takes
        // damage. We don't want the player to keep absorbing hits when
        // already dead though.
        //
        hitter->log("no, it's dead");
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
        if (is_door()) {
            if (!hitter_tp->is_explosion()     &&
                !hitter_tp->is_projectile()    &&
                !hitter_tp->is_weapon()        &&
                !hitter_tp->is_fire()          &&
                !hitter_tp->is_lava()          &&
                !hitter_tp->gfx_attack_anim()) {
                //
                // Not something that typically damages walls.
                //
                hitter->log("no, it's immune");
                return (false);
            }
        }

        if (is_wall()) {
            if (!hitter_tp->is_explosion()     &&
                !hitter_tp->is_projectile()    &&
                !hitter_tp->gfx_attack_anim()) {
                //
                // Not something that typically damages walls.
                //
                hitter->log("no, it's immune");
                return (false);
            }
        }

#if 0
        if (hitter_tp->gfx_attack_anim()) {
            //
            // Get the player using the weapon as the hitter.
            //
            hitter = hitter->owner_get();
            if (!hitter) {
                hitter->log("ignore %s, no owner", to_string().c_str());
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                hitter->log("ignore %s, no weapon", to_string().c_str());
                return (false);
            }

            if (!damage) {
                damage = (weapon->tp()->weapon_damage());
            }

        } else
#endif
        if (hitter->is_fire()) {
            hitter->log("fire attack");
        }
#if 0
        } else if (hitter->owner_get()) {
            //
            // Get the player firing the weapon as the hitter.
            //
            hitter = hitter->owner_get();
            if (!hitter) {
                hitter->log("ignore %s, no owner", to_string().c_str());
                return (false);
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                hitter->log("ignore %s, no weapon", to_string().c_str());
                return (false);
            }

            if (!damage) {
                damage = weapon->tp()->weapon_damage();
            }

            //
            // Don't let our own potion hit ourselves!
            //
            if (hitter == this) {
                hitter->log("ignore %s, self attack", to_string().c_str());
                return (false);
            }
        }
#endif
    }

    hitter->log("hit succeeds");
    int hit_and_killed;

    hit_and_killed = ai_hit_actual(hitter, real_hitter, damage);

    return (hit_and_killed);
}

int Thing::is_hit_by (Thingp hitter)
{_
    return (is_hit_by(hitter, 0));
}
