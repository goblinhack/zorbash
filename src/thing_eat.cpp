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
