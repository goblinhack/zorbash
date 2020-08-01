//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.h"
#include "my_thing.h"
#include "my_sprintf.h"

bool Thing::steal_treasure_from (Thingp it)
{_
    if ((int)random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
        return false;
    }

    log("steal treasure from %s", it->to_string().c_str());
_
    auto cands = get_treasure_list();
    if (!cands.size()) {
        log("no, nothing to steal");
        return false;
    }
    auto chosen = cands[random_range(0, cands.size())];

    log("steal the %s", chosen->to_string().c_str());
    it->drop(chosen, this);
    if (!it->is_dead) {
        carry(chosen);
    }

    if (it->is_player()) {
        it->msg(string_sprintf("%%fg=orange$!!!"));
        MINICON("%%fg=orange$You feel lighter...");
    }
    return true;
}

bool Thing::steal_item_from (Thingp it)
{_
    if ((int)random_range(0, 1000) > tp()->is_steal_item_chance_d1000()) {
        return false;
    }

    log("steal item from %s", it->to_string().c_str());
_
    auto cands = it->get_item_list();
    if (!cands.size()) {
        log("no, nothing to steal");
        return false;
    }
_
    auto chosen = cands[random_range(0, cands.size())];

    log("steal the %s", chosen->to_string().c_str());
    it->drop(chosen, this);
    if (!chosen->is_dead) {
        carry(chosen);
    }

    if (it->is_player()) {
        it->msg(string_sprintf("%%fg=orange$!!!"));
        MINICON("%%fg=orange$You feel lighter...");
    }
    return true;
}
