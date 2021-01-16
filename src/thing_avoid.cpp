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
        if (avoids_water()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (avoids_acid()) {
            return true;
        }
    }

    if (level->is_poison(p)) {
        if (avoids_poison()) {
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
        if (!is_able_to_walk_through_walls()) {
            return true;
        }
    }

    int heat = level->heatmap(p);
    if (damage_doubled_from_fire()) {
        if (heat > 0) {
            if (avoids_fire()) {
                return true;
            }
        }
    } else {
	if (heat >= 4) { // this allows you to skip around lava
            if (avoids_fire()) {
                return true;
            }
        }
    }

    return false;
}

bool Thing::will_avoid (const point &p)
{_
    if (level->is_water(p)) {
        if (avoids_water()) {
            return true;
        }
    }

    if (level->is_acid(p)) {
        if (avoids_acid()) {
            return true;
        }
    }

    if (level->is_poison(p)) {
        if (avoids_poison()) {
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
        if (!is_able_to_walk_through_walls()) {
            return true;
        }
    }

    if (!is_on_fire()) {
        int heat = level->heatmap(p);
        if (damage_doubled_from_fire()) {
            if (heat > 0) {
                if (avoids_fire()) {
                    return true;
                }
            }
        } else {
            if (heat >= 4) { // this allows you to skip around lava
                if (avoids_fire()) {
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

    if (me->is_humanoid()) {
        if (it->attack_humanoid()) {
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

    if (me->avoids_acid()) {
        if (it->is_acid()) {
            return true;
        }
    }

    if (me->avoids_poison()) {
        if (it->is_poison()) {
            return true;
        }
    }

    if (!is_on_fire()) {
        if (me->avoids_fire()) {
            if (it->is_fire()) {
                return true;
            }
            if (it->is_lava()) {
                return true;
            }
        }
    }

    if (me->avoids_water()) {
        if (it->is_water()) {
            return true;
        }
    }
    return false;
}
