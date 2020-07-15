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

bool Thing::possible_to_attack (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (!it->is_attackable()) {
        return (false);
    }

    //
    // No attacking of open doors!
    //
    if (itp->is_open) {
        return (false);
    }

    if (is_alive_monst()) {
        if (me->is_meat_eater()) {
            if (it->is_meat() || it->is_blood()) {
                log("can attack %s", itp->to_string().c_str());
                return (true);
            }
        }

        if (me->is_slime_baby_eater()) {
            if (it->is_slime_baby()) {
                log("can attack %s", itp->to_string().c_str());
                return (true);
            }
        }

        if (me->is_treasure_eater()) {
            if (it->is_treasure()) {
                log("can attack %s", itp->to_string().c_str());
                return (true);
            }
        }

        if (me->is_potion_eater()) {
            if (it->is_potion()) {
                log("can attack %s", itp->to_string().c_str());
                return (true);
            }
        }
    }

    if (is_player()) {
        log("can attack %s", itp->to_string().c_str());
        return (true);
    }

    if (is_weapon()) {
        log("can attack %s", itp->to_string().c_str());
        return (true);
    }

    if (me->is_fire() || me->is_lava()) {
        if (it->is_combustible()) {
            if (!it->is_fire() && !it->is_lava()) {
                log("can attack %s", itp->to_string().c_str());
                return (true);
            }
        }
    }

    log("ignore attack %s", itp->to_string().c_str());
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

#if 0
bool Thing::attack (Thingp it)
{
        auto damage = get_stats_attack();
        if (is_loggable_for_unimportant_stuff()) {
            log("best cand %s, damage %d", it->to_string().c_str(), damage);
        }

        if (is_player() && will_eat(it)) {
            carry(it);
            log("collect %s", it->to_string().c_str());
            ret = true;
        } else if (it->is_dead && will_eat(it)) {
            //
            // Eat the corpse!
            //
            if (eat(it)) {
                //
                // Can't kill it twice, so hide it
                //
                it->hide();
                *target_attacked = true;
                ret = true;
            }
        } else if (it->ai_hit_me_if_possible(me, damage)) {
            if (is_loggable_for_unimportant_stuff()) {
                log("collision: will hit %s for %d damage",
                    it->to_string().c_str(), damage);
            }
            if (me->is_attack_lunge()) {
                me->lunge(it->get_interpolated_mid_at());
            }
            if (me->is_attack_eater()) {
                health_boost(it->get_nutrition());
            }
            if (best->hitter_killed_on_hitting) {
                me->dead("suicide");
            }
            *target_attacked = true;
#endif
