//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::resurrect_tick (void)
{_
    //
    // Rise at the apointed time
    //
    if (game->tick_current < get_tick_resurrect_when()) {
        log("too soon to rise from the grave, at %d wait for %d",
            game->tick_current, get_tick_resurrect_when());
        return;
    }

    //
    // No respawn onto lava or things like that if we don't like that.
    // Or no respawn if something we don't like is standing on us!
    //
    if (is_less_preferred_terrain(make_point(mid_at))) {
        log("do not resurrect, on bad terrain");
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
            animate();

            log("%%fg=orange$%s rises from the grave!%%fg=reset$", text_The().c_str());
            set_stats_health(v);
            set_stats_health_max(v);

            //
            // Catch up on ticks
            //
            set_tick_last_did_something(game->tick_current);
            set_tick(game->tick_current);
            is_dead = false;
        } else {
            log("too weak to rise from the grave");
        }
    }
}
