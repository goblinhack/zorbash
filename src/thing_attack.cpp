//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

bool Thing::possible_to_attack (const Thingp it)
{_
    auto me = tp();

    auto owner = get_top_owner();

    if (owner && owner->is_player()) {
        if (it->is_attackable_by_player()) {
            log("Owned by player");
        } else {
            log("Owned by player; not is_attackable by player");
        }
    }

    if (owner && owner->is_monst() && it->is_attackable_by_monst()) {
        // monst weapn, continue
    } else if (is_monst() && it->is_attackable_by_monst()) {
        // continue
    } else if (is_player() && it->is_attackable_by_player()) {
        // continue
    } else if (owner && owner->is_player() && it->is_attackable_by_player()) {
        // continue
    } else {
        if (g_opt_debug3) { // very noisy
            log("Cannot attack %s", it->to_string().c_str());
        }
        return false;
    }

    log("Is possible to attack %s?", it->to_string().c_str());
_
    //
    // Fire attacks via tick so it can get you when you fall or jump into it.
    //
    if (is_fire()) {
        log("Cannot attack %s, it's fire", it->to_string().c_str());
        return false;
    }

    if (me->is_meat_eater() || me->attack_meat()) {
        //
        // Meat eaters eat you when you are dead!
        //
    } else {
        if (it->is_dead) {
            log("Cannot attack %s, it's dead", it->to_string().c_str());
            return false;
        }
    }

    //
    // No attacking of open doors!
    //
    if (it->is_open) {
        log("Cannot attack %s, it's open", it->to_string().c_str());
        return false;
    }

    if (is_alive_monst() || is_resurrected) {
        if (me->is_jelly_baby_eater()) {
            if (it->is_jelly_baby()) {
                log("Can attack %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->is_treasure_eater()) {
            if (it->is_treasure()) {
                log("Can attack %s", it->to_string().c_str());
                return true;
            }
            if (it->is_carrying_treasure()) {
                log("Can steal from %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->is_potion_eater()) {
            if (it->is_potion()) {
                log("Can attack %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->is_meat_eater() || me->attack_meat()) {
            if (!it->is_attackable_by_monst()) {
                log("No, cannot attack %s, not is_attackable by meat eating monst",
                    it->to_string().c_str());
                return false;
            }
            if (it->is_meat() || it->is_blood()) {
                log("Can attack meat or blood: %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->attack_humanoid()) {
            if (it->is_humanoid()) {
                log("Can attack humanoid: %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->attack_living()) {
            if (it->is_living()) {
                log("Can attack living: %s", it->to_string().c_str());
                return true;
            }
        }

        if (me->is_food_eater()) {
            if (!it->is_attackable_by_monst()) {
                log("No, cannot attack %s, not is_attackable by food eating monst",
                    it->to_string().c_str());
                return false;
            }
            if (it->is_food()) {
                log("Can attack food: %s", it->to_string().c_str());
                return true;
            }
        }
    }

    if (is_player()) {
        //
        // If player is attacking with bare fists, allow an attack
        // Else if it is a weapon, the weapon will attack
        //
        if (!weapon_get()) {
            if (!it->is_attackable_by_player()) {
                log("No, cannot attack %s, not is_attackable", it->to_string().c_str());
                return false;
            }
            log("Can attack %s", it->to_string().c_str());
            return true;
        }
    }

    if (is_weapon()) {
        auto o = get_immediate_owner();
        if (o) {
            if (o->is_monst()) {
                if (!it->is_attackable_by_monst()) {
                    // Too noisy
                    // log("Cannot weapon attack %s, not is_attackable by monst",
                    //     it->to_string().c_str());
                    return false;
                }
                log("Can attack %s", it->to_string().c_str());
                return true;
            } else {
                if (!it->is_attackable_by_player()) {
                    log("Cannot weapon attack %s, not is_attackable by player",
                        it->to_string().c_str());
                    return false;
                }
                log("Can attack %s", it->to_string().c_str());
                return true;
            }
        }
    }

    if (me->is_fire() || me->is_lava()) {
        if (it->is_combustible()) {
            if (!it->is_fire() && !it->is_lava()) {
                log("Can attack %s", it->to_string().c_str());
                return true;
            }
        }
    }

    if (is_enemy(it)) {
        log("Can attack enemy %s", it->to_string().c_str());
        return true;
    }

    log("Cannot attack %s, ignore", it->to_string().c_str());
    return false;
}

bool Thing::attack (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = true;
    bool idle   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, idle, true));
}

bool Thing::attack (Thingp it)
{_
    log("Attack %s", it->to_string().c_str());
_
    //
    // Carry to eat later. Monsts attack their food.
    //
    auto owner = get_top_owner();
    if (owner) {
        //
        // We hit this path for swords. We don't really want the sword to
        // do the eating, so pass control to the owner.
        //
       
        //
        // Owner eat food?
        //
        if (owner->can_eat(it)) {
            //
            // Eat corpse?
            //
            if (it->is_dead) {
                if (owner->eat(it)) {
                    //
                    // Can't kill it twice, so hide it
                    //
                    owner->log("Eat corpse %s", it->to_string().c_str());
                    it->hide();
                    return true;
                }
            } else if (owner->is_player()) {
                owner->log("Carry %s", it->to_string().c_str());
                if (owner->try_to_carry(it)) {
                    return true;
                }
                return false;
            }
        }
    } else {
        //
        // As above, but not for owner.
        //
        if (can_eat(it)) {
            //
            // Eat corpse?
            //
            if (it->is_dead) {
                if (eat(it)) {
                    //
                    // Can't kill it twice, so hide it
                    //
                    log("Eat corpse %s", it->to_string().c_str());
                    it->hide();
                    it->gc();
                    return true;
                }
            } else if (is_player()) {
                log("Don't attack, try to carry %s", it->to_string().c_str());
                if (try_to_carry(it)) {
                    return true;
                }
                return false;
            }
        }
    }

    if (!possible_to_attack(it)) {
	log("Attack failed, not possible tp attack %s", it->to_string().c_str());
        return false;
    }

    if (is_stamina_check()) {
        if (!get_stamina()) {
            if (is_player()) {
                TOPCON("You are too tired to attack. You need to rest.");
            }
            return false;
        }
    }

    if (weapon_get()) {
        auto delta = it->mid_at- mid_at;
        move_set_dir_from_delta(delta);
        use_weapon();
        return true;
    }

    auto att_mod = modifier_to_bonus(get_modifier_strength()) +
                   modifier_to_bonus(get_modifier_attack());
    if (owner) {
        att_mod += modifier_to_bonus(owner->get_modifier_strength());
        att_mod += modifier_to_bonus(owner->get_modifier_attack());
    }

    auto def_mod = modifier_to_bonus(it->get_modifier_defence());
    auto it_owner = get_top_owner();
    if (it_owner) {
        def_mod = modifier_to_bonus(it_owner->get_modifier_defence());
    }

    bool crit = false;
    bool fumble = false;

    //
    // See if we can bypass its defences
    //
    if (!it->is_always_hit()) {
        //it->topcon("att_mod %d def_mod %d", att_mod, def_mod);
        if (!d20roll(att_mod, def_mod, fumble, crit)) {
            if (is_player() || (owner && owner->is_player())) {
                TOPCON("You miss %s.", it->text_the().c_str());
                msg("!");
            } else if (it->is_player()) {
                if (owner) {
                    TOPCON("%s misses with %s.", 
                           owner->text_The().c_str(),
                           text_The().c_str());
                } else {
                    TOPCON("%s misses.", text_The().c_str());
                }
            } else {
                log("The attack missed (att %d, def %d) on %s",
                    att_mod, def_mod, it->to_string().c_str());
            }

            if (attack_lunge()) {
                lunge(it->get_interpolated_mid_at());
            }

            //
            // We tried to attack, so do not move
            //
            return true;
        }
    }

    //
    // We hit. See how much damage.
    //
    auto damage = get_damage_melee();
    auto total_damage = damage + att_mod;

    //
    // Bite?
    //
    auto bite = false;
    auto bite_damage = get_damage_bite();
    if (bite_damage) {
        if (random_range(0, 100) < 50) {
            total_damage = bite_damage;
            bite = true;
        }
    }

    if (total_damage <= 0) {
        total_damage = 1;
    }

    if (it->is_hit_by(this, crit, bite, total_damage)) {
        log("The attack succeeded (dmg %d att, def %d) on %s",
            att_mod, def_mod, it->to_string().c_str());

        if (attack_lunge()) {
            lunge(it->get_interpolated_mid_at());
        }
        if (attack_eater()) {
            health_boost(it->get_nutrition());
        }
        if (is_killed_on_hitting() || is_killed_on_hit_or_miss()) {
            dead("suicide");
        }

        decr_stamina();
        return true;
    }

    it->on_miss(this);

    //
    // Missiles?
    //
    if (is_killed_on_hit_or_miss()) {
        if (is_loggable_for_unimportant_stuff()) {
            log("Attack missed %s", it->to_string().c_str());
        }
        if (attack_lunge()) {
            lunge(it->get_interpolated_mid_at());
        }
        dead("suicide");
        return true;
    }

    return false;
}
