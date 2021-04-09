//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_game.h"
#include "my_thing_template.h"

void Thing::lifespan_tick (void)
{_
    //
    // Torches only tick when carried
    //
    auto owner = get_immediate_owner();
    if (is_torch() && !owner) {
        return;
    }

    if (!get_lifespan()) {
        return;
    }
    if (is_torch() && owner) {
con("lifespan %d tick %d", get_lifespan(), get_tick());
    }

    decr_lifespan();

    //
    // Used so that only one torch that is carried ticks in lifespan
    //
    auto tpp = tp();
    if (owner) {
        if (owner->item_count_excluding_charges(tpp) > 1) {
            owner->update_all_carried_items_tick(tpp);
        }
    }

    if (get_lifespan()) {
        return;
    }

    if (is_torch() && owner) {
        con("total %d tick T%d has %d charges left",
            owner->item_count_excluding_charges(tpp),
            get_tick(), get_charge_count());
    }
    if (get_charge_count()) {
        decr_charge_count();
        if (get_charge_count()) {
            con("Lifespan expired (but has %d charges left)",
                   get_charge_count());
            game->request_remake_inventory = true;
            set_lifespan(tpp->lifespan());
            return;
        }
    }

    dead("ran out of life");
}
