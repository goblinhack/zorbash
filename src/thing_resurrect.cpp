//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::resurrect_tick (void)
{_
    //
    // Roll a 0 treat as success.
    //
    auto crit_roll = get_resurrect_crit_roll();
    if (crit_roll) {
        //
        // Resurrect, but weaker
        //
        if (!is_resurrecting) {
            auto v = get_stats_health_max() / 2;
            if (v > 0) {
                is_resurrecting = true;
                tile_curr = 0;
                MINICON("%%fg=red$%s rises from the grave!",
                        text_The().c_str());
                set_stats_health(v);
                set_stats_health_max(v);

                //
                // Catch up on ticks
                //
                set_tick_last_did_something(game->tick_current);
                set_tick(game->tick_current);
            }
        }
    }
}
