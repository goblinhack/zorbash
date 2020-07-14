//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_sprintf.h"

bool Thing::eat (Thingp it)
{_
    //
    // Does the attacker feast on success?
    //
    if (is_player()) {
        MINICON("You munch the %s", it->text_the().c_str());
        health_boost(it->get_nutrition());
        return (true);
    } else {
        if (is_attack_eater()) {
            if ((is_slime_eater()    && it->is_slime())    ||
                (is_meat_eater()     && it->is_meat())     ||
                (is_treasure_eater() && it->is_treasure()) ||
                (is_potion_eater()   && it->is_potion())) {

                log("eats %s", it->text_the().c_str());
                //
                // For treasure what should the boost be?
                //
                health_boost(it->get_nutrition());
                return (true);
            }
        }
    }
    return (false);
}

bool Thing::will_eat (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat_eater()) {
        if (it->is_meat() || it->is_blood()) {
            return (true);
        }
    }
    if (me->is_treasure_eater()) {
        if (it->is_treasure()) {
            return (true);
        }
    }
    if (me->is_potion_eater()) {
        if (it->is_potion()) {
            return (true);
        }
    }
    if (me->is_slime_baby_eater()) {
        if (it->is_slime_baby()) {
            return (true);
        }
    }
    if (is_player()) {
        if (it->collectable()) {
            return (true);
        }
    }
    return (false);
}
