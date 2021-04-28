//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_sprintf.h"

bool Thing::eat (Thingp it)
{_
    //
    // Does the attacker feast on success?
    //
    if (is_player()) {
        TOPCON("You munch the %s.", it->text_the().c_str());
        health_boost(it->get_nutrition());
        return true;
    } else {
        if (attack_eater()) {
            if ((is_jelly_eater()    && it->is_jelly())    ||
                (is_meat_eater()     && it->is_meat())     ||
                (is_food_eater()     && it->is_food())     ||
                (is_treasure_eater() && it->is_treasure()) ||
                (is_wand_eater()     && it->is_wand())     ||
                (is_potion_eater()   && it->is_potion())) {

                log("Eats %s", it->text_the().c_str());
                //
                // For treasure what should the boost be?
                //
                health_boost(it->get_nutrition());
                it->dead("by being eaten");
                return true;
            }
        }
    }
    return false;
}

bool Thing::can_eat (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat_eater()) {
        if (it->is_meat() || it->is_blood()) {
            return true;
        }
    }
    if (me->is_food_eater()) {
        if (it->is_food() || it->is_blood()) {
            return true;
        }
    }
    if (me->is_treasure_eater()) {
        if (it->is_treasure()) {
            return true;
        }
    }
    if (me->is_potion_eater()) {
        if (it->is_potion()) {
            return true;
        }
    }
    if (me->is_wand_eater()) {
        if (it->is_wand()) {
            return true;
        }
    }
    if (me->is_jelly_baby_eater()) {
        if (it->is_jelly_baby()) {
            return true;
        }
    }
    if (is_player()) {
        if (it->is_food()) {
            return true;
        }
        if (it->is_collectable()) {
            return true;
        }
    }
    return false;
}
