//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_sprintf.h"

bool Thing::is_enemy (Thingp attacker) const
{_
    if (unlikely(!monstp)) {
        return (false);
    }

    auto enemy = attacker->id;
    for (const auto& e : monstp->enemies) {
        if (e == enemy) {
            return (true);
        }
    }
    return (false);
}

void Thing::add_enemy (Thingp attacker)
{_
    if (unlikely(!is_monst())) {
        return;
    }

    if (unlikely(!monstp)) {
        return;
    }

    if (is_enemy(attacker)) {
        return;
    }

    auto enemy = attacker->id;
    monstp->enemies.push_back(enemy);
    log("add enemy %s", attacker->to_string().c_str());
}
