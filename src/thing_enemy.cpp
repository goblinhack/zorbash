//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::add_enemy (Thingp attacker)
{_
    if (!monst) {
        return;
    }

    auto enemy = attacker->id;
    for (auto e : monst->enemies) {
        if (e == enemy) {
            return;
        }
    }
    monst->enemies.push_back(enemy);
    con("add enemy %s", attacker->to_string().c_str());
}
