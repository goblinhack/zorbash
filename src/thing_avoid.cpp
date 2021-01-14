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

bool Tp::will_avoid (Levelp level, point p) const
{_
    if (level->is_water(p)) {
        if (avoider_of_water()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (avoider_of_acid()) {
            return true;
        }
    }

    if (level->is_poison(p)) {
        if (avoider_of_poison()) {
            return true;
        }
    }

    if (!is_floating()) {
        if (level->is_chasm(p)) {
            return true;
        }
    }

    if (level->is_corpse(p)) {
        if (level->is_monst(p) > 1) {
            return true;
        }
    } else {
        if (level->is_monst(p) > 0) {
            return true;
        }
    }

    if (level->is_movement_blocking_soft(p) ||
        level->is_movement_blocking_hard(p)) {
        return true;
    }

    int heat = level->heatmap(p);
    if (damage_doubled_from_fire()) {
        if (heat > 0) {
            if (avoider_of_fire()) {
                return true;
            }
        }
    } else {
	if (heat >= 4) { // this allows you to skip around lava
            if (avoider_of_fire()) {
                return true;
            }
        }
    }

    return false;
}

bool Thing::will_avoid (const point &p)
{_
    if (level->is_water(p)) {
        if (avoider_of_water()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (avoider_of_acid()) {
            return true;
        }
    }

    if (level->is_poison(p)) {
        if (avoider_of_poison()) {
            return true;
        }
    }

    if (!is_floating()) {
        if (level->is_chasm(p)) {
            return true;
        }
    }

    if (level->is_corpse(p)) {
        if (level->is_monst(p) > 1) {
            return true;
        }
    } else {
        if (level->is_monst(p) > 0) {
            return true;
        }
    }

    if (level->is_movement_blocking_soft(p) ||
        level->is_movement_blocking_hard(p)) {
        return true;
    }

    if (!is_on_fire()) {
        int heat = level->heatmap(p);
        if (damage_doubled_from_fire()) {
            if (heat > 0) {
                if (avoider_of_fire()) {
                    return true;
                }
            }
        } else {
            if (heat >= 4) { // this allows you to skip around lava
                if (avoider_of_fire()) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Thing::will_avoid (const fpoint &p)
{_
    return will_avoid(point(p.x, p.y));
}

bool Thing::will_avoid (const Thingp itp)
{_
    auto me = tp();
    auto it = itp->tp();

    if (me->is_meat()) {
        if (it->is_meat_eater() || it->attack_meat()) {
            if (is_dangerous(itp)) {
                return true;
            }
        }
    }

    if (me->is_food()) {
        if (it->is_food_eater()) {
            return true;
        }
    }

    if (me->is_treasure()) {
        if (it->is_treasure_eater()) {
            return true;
        }
    }

    if (me->is_potion()) {
        if (it->is_potion_eater()) {
            return true;
        }
    }

    if (me->is_jelly_baby()) {
        //
        // But allow baby slimes to attack each other!
        //
        if (it->is_jelly_parent()) {
            return true;
        }
    }

    if (me->avoider_of_acid()) {
        if (it->is_acid()) {
            return true;
        }
    }

    if (me->avoider_of_poison()) {
        if (it->is_poison()) {
            return true;
        }
    }

    if (!is_on_fire()) {
        if (me->avoider_of_fire()) {
            if (it->is_fire()) {
                return true;
            }
            if (it->is_lava()) {
                return true;
            }
        }
    }

    if (me->avoider_of_water()) {
        if (it->is_water()) {
            return true;
        }
    }
    return false;
}
