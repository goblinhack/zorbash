//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"
#include "my_random.h"
#include "my_thing_template.h"

bool Thing::try_to_escape (void)
{
    if (is_jumper()) {
        auto health_max = get_health_max();
        auto health = get_health();

        if (health > health_max / 2) {
            return false;
        }

        //
        // Don't try and escape too often else the player can never kill the
        // monst!
        //
        if (game->tick_current - get_tick_last_escape() < 20) {
            return false;
        }

        if ((int)pcq_random_range(0, 1000) <
                tp()->is_jumper_on_low_hp_chance_d1000()) {
            if (try_to_jump_away_from_player()) {
                set_tick_last_escape(game->tick_current);
                return true;
            }
        }
    }

    return false;
}
