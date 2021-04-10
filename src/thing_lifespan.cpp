//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_game.h"
#include "my_thing_template.h"
#include "my_string.h"
#include "my_python.h"

void Thing::on_lifespan (Thingp what)
{
    auto on_lifespan = what->tp()->on_lifespan_do();
    if (std::empty(on_lifespan)) {
        return;
    }

    auto t = split_tokens(on_lifespan, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s, %s)", mod.c_str(), fn.c_str(),
            to_string().c_str(),
            what->to_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(),
                        id.id, what->id.id,
                        (int)mid_at.x, (int)mid_at.y);
    } else {
        ERR("Bad on_lifespan call [%s] expected mod:function, got %d elems",
            on_lifespan.c_str(), (int)on_lifespan.size());
    }
}

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

    decr_lifespan();

    //
    // Used so that only one torch that is carried ticks in lifespan
    //
    auto tpp = tp();
    if (owner) {
        if (owner->item_count_excluding_charges(tpp) > 1) {
            owner->update_all_carried_items_tick(tpp);
            decr_tick();
        }
    }

    if (get_lifespan()) {
        return;
    }

    auto top_owner = get_top_owner();
    if (top_owner) {
        top_owner->on_lifespan(this);
    }

    if (get_charge_count()) {
        decr_charge_count();
        if (get_charge_count()) {
            log("Lifespan expired (but has %d charges left)", get_charge_count());
            game->request_remake_inventory = true;
            set_lifespan(tpp->lifespan());
            return;
        }
    }

    dead("ran out of life");
}
