//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_wid_rightbar.h"
#include "my_random.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"

bool Thing::steal_treasure_from (Thingp it)
{_
    if ((int)random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
        return false;
    }

    log("Steal treasure from %s", it->to_string().c_str());
_
    auto cands = get_treasure_list();
    if (!cands.size()) {
        log("No, nothing to steal");
        return false;
    }
    auto chosen = cands[random_range(0, cands.size())];

    log("Steal treasure %s", chosen->to_string().c_str());
    if (!it->drop(chosen, this)) {
        return false;
    }

    if (!it->is_dead) {
        carry(chosen);
    }
    chosen->hide();

    if (it->is_player()) {
        it->msg(string_sprintf("                        %%fg=white$Where's my money?!"));
        TOPCON("%%fg=orange$You feel less wealthy somehow...");
    }
    return true;
}

bool Thing::steal_item_from (Thingp it)
{_
    log("Try to steal item from %s?", it->to_string().c_str());
    if ((int)random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
        log("No");
        return false;
    }
_
    log("Yes, steal out of this list:");
    auto cands = it->get_item_list();
    if (!cands.size()) {
        log("No, nothing to steal");
        return false;
    }

    auto chosen = cands[random_range(0, cands.size())];

    log("Yes, steal: %s", chosen->to_string().c_str());

    it->drop(chosen, this);
    if (!chosen->is_dead) {
        carry(chosen);
    }
    chosen->hide();

    it->log("New carried list:");
    it->get_item_list();

    if (it->is_player()) {
        it->msg(string_sprintf("                        %%fg=white$Where's my stuff?!"));
        TOPCON("%%fg=orange$You feel lighter somehow...");
    }

    //
    // Update the inventory
    //
    wid_rightbar_init();
    return true;
}
