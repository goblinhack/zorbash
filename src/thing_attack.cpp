//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <set>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"

bool Thing::possible_to_attack (const Thingp it)
{_
    auto me = tp();

    //
    // No attacking of open doors!
    //
    if (it->is_open) {
        log("cannot attack %s, its open", it->to_string().c_str());
        return (false);
    }

    if (is_alive_monst() || is_resurrected) {
        if (me->is_slime_baby_eater()) {
            if (it->is_slime_baby()) {
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
        }

        if (me->is_treasure_eater()) {
            if (it->is_treasure()) {
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
            if (it->is_carrying_treasure()) {
                log("can steal from %s", it->to_string().c_str());
                return (true);
            }
        }

        if (me->is_potion_eater()) {
            if (it->is_potion()) {
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
        }

        if (me->is_meat_eater()) {
            if (!it->is_attackable_by_monst()) {
                log("cannot attack %s, not attackable", it->to_string().c_str());
                return (false);
            }
            if (it->is_meat() || it->is_blood()) {
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
        }
    }

    if (is_player()) {
        if (!it->is_attackable_by_player()) {
            log("cannot attack %s, not attackable", it->to_string().c_str());
            return (false);
        }
        log("can attack %s", it->to_string().c_str());
        return (true);
    }

    if (is_weapon()) {
        auto o = owner_get();
        if (o) {
            if (o->is_monst()) {
                if (!it->is_attackable_by_monst()) {
                    log("cannot weapon attack %s, not attackable", it->to_string().c_str());
                    return (false);
                }
                log("can attack %s", it->to_string().c_str());
                return (true);
            } else {
                if (!it->is_attackable_by_player()) {
                    log("cannot weapon attack %s, not attackable", it->to_string().c_str());
                    return (false);
                }
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
        }
    }

    if (me->is_fire() || me->is_lava()) {
        if (it->is_combustible()) {
            if (!it->is_fire() && !it->is_lava()) {
                log("can attack %s", it->to_string().c_str());
                return (true);
            }
        }
    }

    log("ignore attack %s", it->to_string().c_str());
    return (false);
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
    log("attack %s", it->to_string().c_str());
_
    //
    // Carry to eat later. Monsts attack their food.
    //
    auto owner = owner_get();
    if (owner) {
        //
        // We hit this path for swords. We don't really want the sword to
        // do the eating, so pass control to the owner.
        //
       
        //
        // Owner eat food?
        //
        if (owner->will_eat(it)) {
            //
            // Eat corpse?
            //
            if (it->is_dead) {
                if (owner->eat(it)) {
                    //
                    // Can't kill it twice, so hide it
                    //
                    owner->log("eat corpse %s", it->to_string().c_str());
                    it->hide();
                    return true;
                }
            } else if (owner->is_player()) {
                owner->log("carry to eat later %s", it->to_string().c_str());
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
        if (will_eat(it)) {
            //
            // Eat corpse?
            //
            if (it->is_dead) {
                if (eat(it)) {
                    //
                    // Can't kill it twice, so hide it
                    //
                    log("eat corpse %s", it->to_string().c_str());
                    it->hide();
                    return true;
                }
            } else if (is_player()) {
                log("carry to eat later %s", it->to_string().c_str());
                if (try_to_carry(it)) {
                    return true;
                }
                return false;
            }
        }
    }

    log("check is possible to attack %s", it->to_string().c_str());
    if (!possible_to_attack(it)) {
        return false;
    }

    auto damage = get_stats_attack();
    if (it->is_hit_by(this, damage)) {
        if (is_loggable_for_unimportant_stuff()) {
            log("the attack hit %s for %d", it->to_string().c_str(), damage);
        }
        if (is_attack_lunge()) {
            lunge(it->get_interpolated_mid_at());
        }
        if (is_attack_eater()) {
            health_boost(it->get_nutrition());
        }
        if (is_killed_on_hitting() || is_killed_on_hit_or_miss()) {
            dead("suicide");
        }
        return true;
    }

    //
    // Missiles?
    //
    if (is_killed_on_hit_or_miss()) {
        if (is_loggable_for_unimportant_stuff()) {
            log("attack missed %s", it->to_string().c_str());
        }
        if (is_attack_lunge()) {
            lunge(it->get_interpolated_mid_at());
        }
        dead("suicide");
        return true;
    }

    return false;
}
