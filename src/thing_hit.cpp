//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_sprintf.h"
#include "my_string.h"
#include "my_python.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"

//
// Python callback upon being hit
//
void Thing::on_hit (Thingp hitter,      // an arrow / monst /...
                    Thingp real_hitter, // who fired the arrow?
                    bool crit,
                    bool bite,
                    int damage)
{_
    auto on_hit = tp()->on_hit_do();
    if (std::empty(on_hit)) {
        return;
    }

    auto t = split_tokens(on_hit, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s, %s, %s, crit=%d, bite=%d, damage=%d)", mod.c_str(), fn.c_str(),
            to_string().c_str(),
            hitter->to_string().c_str(),
            real_hitter->to_string().c_str(),
            crit, bite, damage);

        py_call_void_fn(mod.c_str(), fn.c_str(),
                        id.id, hitter->id.id, real_hitter->id.id,
                        (int)mid_at.x, (int)mid_at.y,
                        (int)crit,
                        (int)bite,
                        (int)damage);
    } else {
        ERR("Bad on_hit call [%s] expected mod:function, got %d elems",
            on_hit.c_str(), (int)on_hit.size());
    }
}

//
// Python callback upon being miss
//
void Thing::on_miss (Thingp hitter)
{_
    auto on_miss = tp()->on_miss_do();
    if (std::empty(on_miss)) {
        return;
    }

    auto t = split_tokens(on_miss, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s, %s)", mod.c_str(), fn.c_str(),
            to_string().c_str(), hitter->to_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id,
                        (int)mid_at.x, (int)mid_at.y);
    } else {
        ERR("Bad on_miss call [%s] expected mod:function, got %d elems",
            on_miss.c_str(), (int)on_miss.size());
    }
}

void Thing::on_claw_attack (void)
{_
    auto on_claw_attack = tp()->on_claw_attack_do();
    if (std::empty(on_claw_attack)) {
        return;
    }

    auto t = split_tokens(on_claw_attack, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s)", mod.c_str(), fn.c_str(), to_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (int)mid_at.x, (int)mid_at.y);
    } else {
        ERR("Bad on_claw_attack call [%s] expected mod:function, got %d elems",
            on_claw_attack.c_str(), (int)on_claw_attack.size());
    }
}

int Thing::ai_hit_actual (Thingp hitter,      // an arrow / monst /...
                          Thingp real_hitter, // who fired the arrow?
                          bool crit,
                          bool bite,
                          int damage)
{_
    hitter->log("Hit for damage %d", damage);

    auto delta = mid_at - hitter->mid_at;

    if (crit) {
        damage *= 2;
    }

    if (bite) {
        if (real_hitter->is_poison()) {
            TOPCON("TODO poison");
        }
    }

    if (real_hitter->is_stamina_check()) {
        if (!real_hitter->get_stamina()) {
            if (real_hitter->is_player()) {
                TOPCON("You are too tired to attack. You need to rest.");
                return false;
            }
        }
        real_hitter->decr_stamina(1);
    }

    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        hitter->log("Hit fails, it's dead");
        return false;
    }

    if (!damage) {
        hitter->log("Hit fails, no damage");
        return false;
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
                return true;
            case THING_SHOVE_TRIED_AND_PASSED:
                return true;
            case THING_SHOVE_NEVER_TRIED:
                break;
        }
    }

    if (avoids_fire()) {
        if (real_hitter->is_fire() ||
            real_hitter->is_lava()) {
            if (damage_doubled_from_fire()) {
                damage *= 2;
                log("Double damage from fire");
            }
        }
    }

    if (avoids_acid()) {
        if (real_hitter->is_acid()) {
            if (damage_doubled_from_acid()) {
                damage *= 2;
                log("Double damage from acid");
            }
        }
    }

    if (avoids_poison()) {
        if (real_hitter->is_poison()) {
            if (damage_doubled_from_poison()) {
                damage *= 2;
                log("Double damage from poison");
            }
        }
    }

    if (avoids_water()) {
        if (real_hitter->is_shallow_water() || real_hitter->is_deep_water()) {
            if (damage_doubled_from_water()) {
                damage *= 2;
                log("Double damage from water");
            }
        }
    }

    //
    // Try to steal
    //
    if (real_hitter->is_item_eater()) {
        if (is_carrying_item()) {
            if (real_hitter->steal_item_from(this)) {
                return true;
            }
        }
    }

    for (auto oid : real_hitter->monstp->skills) {
        auto skill = level->thing_find(oid);
        if (skill && skill->is_activated) {
            //
            // Allow the damage to be modified
            //
            real_hitter->set_current_damage(damage);
            real_hitter->use(skill);
            damage = real_hitter->get_current_damage();
        }
    }

    if (is_player()) {
        if (damage > THING_DAMAGE_SHAKE_ABOVE) {
            level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
            if (crit) {
                TOPCON("%%fg=red$%s CRITS you for %d damage!%%fg=reset$",
                        real_hitter->text_The().c_str(),
                        damage);
            } else {
                TOPCON("%%fg=red$%s %s you for %d damage!%%fg=reset$",
                        real_hitter->text_The().c_str(),
                        real_hitter->text_hits().c_str(),
                        damage);
            }

            if (real_hitter->is_fire() ||
                real_hitter->is_lava()) {
                if (set_on_fire("hit by fire")) {
                    TOPCON("%%fg=red$You are literally ON FIRE!%%fg=reset$");
                }
            }
        } else {
            if (bite) {
                TOPCON("%%fg=yellow$%s bites you for %d damage!%%fg=reset$",
                        real_hitter->text_The().c_str(),
                        damage);
            } else {
                TOPCON("%%fg=yellow$%s %s you for %d damage!%%fg=reset$",
                        real_hitter->text_The().c_str(),
                        real_hitter->text_hits().c_str(),
                        damage);
            }
        }

        if (is_bloodied()) {
            level->set_wobble(damage / THING_DAMAGE_SHAKE_SCALE);
        }
    } else {
        if (real_hitter->is_player()) {
            if (crit) {
                TOPCON("%%fg=red$You CRIT hit the %s for %d damage!%%fg=reset$",
                        text_the().c_str(), damage);
            } else {
                TOPCON("You hit the %s for %d damage!",
                       text_the().c_str(), damage);
            }
        }
        if (real_hitter->is_fire() ||
            real_hitter->is_lava()) {
            set_on_fire("hit by fire or lava");
        }
        add_enemy(real_hitter);
    }

    //
    // Python callback
    //
    on_hit(hitter, real_hitter, crit, bite, damage);

    //
    // Visible hit indication
    //
    if (is_player()) {
        //
        // Player being hit
        //
        msg(string_sprintf("%%fg=red$-%d", damage));
    } else if (is_monst()) {
        //
        // Monst being hit
        //
        if (hitter->is_player() || real_hitter->is_player()) {
            //
            // Monst being hit by player
            //
            msg(string_sprintf("%%fg=white$-%d", damage));
        }
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
    if (!real_hitter->get_weapon_id_carry_anim().ok()) {
        auto claws = real_hitter->tp()->gfx_anim_attack();
        if (claws != "") {
            auto claw_attack = level->thing_new(claws, mid_at);
            claw_attack->bounce(0.1, 0.1, 100, 3);
            claw_attack->move_set_dir_from_delta(delta);

            //
            // Python callback
            //
            real_hitter->on_claw_attack();
        }
    }

    auto h = decr_health(damage);
    if (h <= 0) {
        h = set_health(0);

        //
        // Record who dun it.
        //
        log("Is killed by (%s) %u damage, health now %d",
            real_hitter->to_string().c_str(), damage, h);
        std::string killer = real_hitter->text_a_or_an();

        //
        // If not a monst, e.g. a generator then don't include killed by
        //
        auto reason = "killed by " + killer;
        if (!is_monst()) {
            reason = "by " + killer;
        }

        dead(real_hitter, reason);

        //
        // Does the attacker feast on success?
        //
        if (real_hitter->can_eat(this)) {
            real_hitter->eat(this);
        }
    } else {
        log("Is hit by (%s) %u damage, health now %d",
            real_hitter->to_string().c_str(), damage, h);
    }

    return true;
}

//
// Returns true on the target being dead.
//
int Thing::is_hit_by (Thingp hitter, bool crit, bool bite, int damage)
{_
    hitter->log("Possible hit %s for %u", to_string().c_str(), damage);
_
    //
    // Cruel to let things keep on hitting you when you're dead
    //
    if (is_dead) {
        hitter->log("No, it's dead");
        return false;
    }

    if (is_resurrecting) {
        hitter->log("No, it's resurrecting");
        return false;
    }

    //
    // If an arrow, who really fired it?
    //
    Thingp real_hitter = nullptr;

    if (hitter) {
        real_hitter = hitter->get_immediate_owner();

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
        hitter->log("No, it's dead");
        return false;
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
                hitter->log("No, it's immune");
                return false;
            }
        }

        if (is_wall()) {
            if (!hitter_tp->is_explosion()     &&
                !hitter_tp->is_projectile()    &&
                !hitter_tp->gfx_attack_anim()) {
                //
                // Not something that typically damages walls.
                //
                hitter->log("No, it's immune");
                return false;
            }
        }

#if 0
        if (hitter_tp->gfx_attack_anim()) {
            //
            // Get the player using the weapon as the hitter.
            //
            hitter = hitter->get_immediate_owner();
            if (!hitter) {
                hitter->log("Ignore %s, no owner", to_string().c_str());
                return false;
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                hitter->log("Ignore %s, no weapon", to_string().c_str());
                return false;
            }

            if (!damage) {
                damage = (weapon->tp()->weapon_damage());
            }

        } else
#endif
        if (hitter->is_fire()) {
            hitter->log("Fire attack");
        }
#if 0
        } else if (hitter->get_immediate_owner()) {
            //
            // Get the player firing the weapon as the hitter.
            //
            hitter = hitter->get_immediate_owner();
            if (!hitter) {
                hitter->log("Ignore %s, no owner", to_string().c_str());
                return false;
            }

            verify(hitter);

            //
            // Get the damage from the weapon being used to use.
            //
            weapon = hitter->weapon_get();
            if (!weapon) {
                hitter->log("Ignore %s, no weapon", to_string().c_str());
                return false;
            }

            if (!damage) {
                damage = weapon->tp()->weapon_damage();
            }

            //
            // Don't let our own potion hit ourselves!
            //
            if (hitter == this) {
                hitter->log("Ignore %s, self attack", to_string().c_str());
                return false;
            }
        }
#endif
    }

    hitter->log("Hit succeeds");
    int hit_and_killed;

    hit_and_killed = ai_hit_actual(hitter, real_hitter, crit, bite, damage);

    return (hit_and_killed);
}

int Thing::is_hit_by (Thingp hitter, int damage)
{_
    return (is_hit_by(hitter, false, false, damage));
}

int Thing::is_hit_by (Thingp hitter)
{_
    return (is_hit_by(hitter, false, false, 0));
}
