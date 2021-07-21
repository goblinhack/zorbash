//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_tile.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_sprintf.h"

bool Thing::is_enemy (Thingp attacker) const
{_
    if (unlikely(!monstp)) {
        return false;
    }

    auto enemy = attacker->id;
    for (const auto& e : monstp->enemies) {
        if (e == enemy) {
            return true;
        }
    }
    return false;
}

void Thing::add_enemy (Thingp attacker)
{_
    if (unlikely(!attacker->is_monst())) {
        return;
    }

    if (unlikely(!monstp)) {
        return;
    }

    if (is_enemy(attacker)) {
        return;
    }

    if (unlikely(is_player())) {
        //
        // Allow the robot to make enemies
        //
        if (game->robot_mode) {
            CON("Robo: add enemy: %s", attacker->to_string().c_str());
        }
    } else if (unlikely(!is_monst())) {
        //
        // Only monsts make enemies
        //
        return;
    }

    if (monstp->enemies.size() > 10) {
        monstp->enemies.clear();
    }

    auto enemy = attacker->id;
    monstp->enemies.push_back(enemy);
    dbg("Add enemy %s", attacker->to_string().c_str());
}
