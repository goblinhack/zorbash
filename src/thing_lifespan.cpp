//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_game.h"

void Thing::lifespan_tick (void)
{_
    //
    // Torches only tick when carried
    //
    if (is_torch() && !get_top_owner()) {
        return;
    }

    if (!get_lifespan()) {
        return;
    }

    decr_lifespan();

    if (get_lifespan()) {
        return;
    }

    if (get_charge_count()) {
        decr_charge_count();
        if (get_charge_count()) {
            topcon("Lifespan expired %s (has %d charges left)", 
                to_string().c_str(), get_charge_count());
            game->request_remake_inventory = true;
            return;
        }
    }

    dead("ran out of life");
}
