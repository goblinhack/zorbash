//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_sprintf.h"

bool Thing::eat (Thingp it)
{_
    //
    // Does the attacker feast on success?
    //
    if (is_player()) {
        auto boost = health_boost(it->get_nutrition());
        TOPCON("You munch %s for %d health.", it->text_the().c_str(), boost);
        return true;
    }

    if (attack_eater()) {
        if ((is_jelly_eater()    && it->is_jelly())    ||
            (is_meat_eater()     && it->is_meat())     ||
            (is_food_eater()     && it->is_food())     ||
            (is_treasure_type_eater() && it->is_treasure_type()) ||
            (is_wand_eater()     && it->is_wand())     ||
            (is_potion_eater()   && it->is_potion())) {

            //
            // For treasure what should the boost be?
            //
            if (!health_boost(it->get_nutrition())) {
                dbg("No health boost from eating %s", it->text_the().c_str());
                return false;
            }

            dbg("Eats %s", it->text_the().c_str());

            if (!is_player()) {
                if (distance_to_player() < DMAP_IS_PASSABLE) {
                    if (it->is_meat()) {
                        level->thing_new(tp_random_blood_splatter()->name(), mid_at);
                    }

                    TOPCON("%s eats %s.",
                           text_The().c_str(),
                           it->text_the().c_str());
                }
            }

            it->dead("by being eaten");
            return true;
        }
    }
    return false;
}

bool Thing::worth_eating (Thingp it)
{_
    if (!can_eat(it)) {
        return false;
    }

    return health_boost_would_occur(it->get_nutrition());
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
    if (me->is_treasure_type_eater()) {
        if (it->is_treasure_type()) {
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
    }
    return false;
}

bool Thing::eat_something (void)
{_
    for (const auto& item : monstp->carrying) {
        auto t = level->thing_find(item.id);
        if (!t) {
            continue;
        }
        if (!can_eat(t)) {
            continue;
        }
        if (!worth_eating(t)) {
            continue;
        }
        if (eat(t)) {
            return true;
        }
    }
    return false;
}
