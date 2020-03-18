//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_sprintf.h"

bool Thing::is_enemy (Thingp attacker)
{_
    if (unlikely(!monst)) {
        return (false);
    }

    auto enemy = attacker->id;
    for (auto e : monst->enemies) {
        if (e == enemy) {
            return (true);
        }
    }
    return (false);
}

void Thing::add_enemy (Thingp attacker)
{_
    if (unlikely(!monst)) {
        return;
    }

    if (is_enemy(attacker)) {
        return;
    }

    auto enemy = attacker->id;
    monst->enemies.push_back(enemy);
    con("add enemy %s", attacker->to_string().c_str());
}
