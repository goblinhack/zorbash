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

    if (monstp->enemies.find(attacker->id) != monstp->enemies.end()) {
        return true;
    }
    return false;
}

//
// Timeout enemies so we don't resent them forever.
//
void Thing::enemies_tick (void)
{_
    if (!monstp) {
        return;
    }

    for (auto &p : monstp->enemies) {
        if (--p.second <= 0) {
            monstp->enemies.erase(p.first);
            if (is_player()) {
                if (game->robot_mode) {
                    auto attacker = level->thing_find_optional(p.first);
                    if (attacker) {
                        CON("Robot: remove enemy: %s", attacker->to_string().c_str());
                    }
                }
            }
            return;
        }
    }
}

void Thing::add_enemy (Thingp attacker)
{_
    if (unlikely(!attacker->is_monst())) {
        return;
    }

    if (unlikely(!monstp)) {
        return;
    }

    if (!ai_enemy_memory()) {
        return;
    }

    if (unlikely(is_player())) {
        //
        // Allow the robot to make enemies
        //
    } else if (unlikely(!is_monst())) {
        //
        // Only monsts make enemies
        //
        return;
    }

    if (!monstp->enemies[attacker->id]) {
        if (is_player() && game->robot_mode) {
            CON("Robot: Add new enemy %s", attacker->to_string().c_str());
        } else {
            dbg("Add new enemy %s", attacker->to_string().c_str());
        }
        monstp->enemies[attacker->id] = ai_enemy_memory();
    } else {
        if (is_player() && game->robot_mode) {
            CON("Robot: Increment old enemy %s", attacker->to_string().c_str());
        } else {
            dbg("Increment old enemy %s", attacker->to_string().c_str());
        }
        monstp->enemies[attacker->id]++;
    }
}
