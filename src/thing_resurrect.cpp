//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::resurrect_tick (void)
{_
    //
    // Rise at the apointed time
    //
    if (game->tick_current < get_tick_resurrect_when()) {
        dbg("Too soon to rise from the grave, at %d wait for %d",
            game->tick_current, get_tick_resurrect_when());
        return;
    }

    //
    // No respawn onto lava or things like that if we don't like that.
    // Or no respawn if something we don't like is standing on us!
    //
    if (get_terrain_cost(make_point(mid_at)) >= DMAP_LESS_PREFERRED_TERRAIN) {
        dbg("Do not resurrect, on bad terrain");
        return;
    }

    //
    // Resurrect, but weaker
    //
    if (!is_resurrecting) {
        auto v = get_health_max() / 2;
        if (v > 0) {
            is_resurrecting = true;
            tile_curr = 0;
            animate();

            dbg("%%fg=orange$%s rises from the grave!%%fg=reset$", text_The().c_str());
            set_health(v);
            set_health_max(v);

            //
            // Catch up on ticks
            //
            set_tick_last_did_something(game->tick_current);
            is_dead = false;
        } else {
            dbg("Too weak to rise from the grave");
        }
    }
}
