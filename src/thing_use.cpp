//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_python.h"

void Thing::used (Thingp what, Thingp target)
{_
    if (is_player()) {
        if (!inventory_id_remove(what, target)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->get_top_owner();
    if (existing_owner != this) {
        err("Attempt to use %s which is not carried", what->to_string().c_str());
        return;
    }

    what->remove_owner();
    what->visible();

    monstp->carrying.remove(what->id);
    log("Used %s", what->to_string().c_str());
    what->level_pop();
    what->dead("used");
}

bool Thing::use (Thingp what)
{_
    auto on_use = what->tp()->on_use_do();
    if (!std::empty(on_use)) {
        auto t = split_tokens(on_use, '.');
        if (t.size() == 2) {
            auto mod = t[0];
            auto fn = t[1];
            std::size_t found = fn.find("()");
            if (found != std::string::npos) {
                fn = fn.replace(found, 2, "");
            }

            what->log("call %s.%s()", mod.c_str(), fn.c_str());
            py_call_void_fn(mod.c_str(), fn.c_str(),
                            id.id, (int)mid_at.x, (int)mid_at.y);
        } else {
            ERR("Bad on_use call [%s] expected mod:function, got %d elems",
                on_use.c_str(), (int)on_use.size());
        }
    }

    if (what->is_weapon()) {
        MINICON("You wield the %s", what->text_the().c_str());
        game->tick_begin("player used an item");
    } else if (what->is_food()) {
        eat(what);
        used(what, this);
        game->tick_begin("player ate an item");
    } else if (what->is_potion()) {
        MINICON("You quaff the %s", what->text_the().c_str());
        game->tick_begin("player drunk an item");
    } else if (!what->is_usable()) {
        if (is_player()) {
            MINICON("I don't know how to use %s", what->text_the().c_str());
        }
        game->tick_begin("player tried to use something they could not");
    }
    return true;
}
