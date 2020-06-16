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
    // No respawn onto lava or things like that if we don't like that.
    //
    if (is_less_preferred_terrain(make_point(mid_at))) {
        return;
    }

    //
    // Succeed on crit
    //
    auto crit_roll = get_resurrect_success();
    if (!crit_roll) {
        return;
    }

    //
    // Resurrect, but weaker
    //
    if (!is_resurrecting) {
        auto v = get_stats_health_max() / 2;
        if (v > 0) {
            is_resurrecting = true;
            tile_curr = 0;
            UI_MINICON("%%fg=red$%s rises from the grave!",
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
