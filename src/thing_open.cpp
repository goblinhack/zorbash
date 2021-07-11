//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_string.h"
#include "my_thing_template.h"
#include "my_python.h"

void Thing::on_open (void)
{
    auto on_open = tp()->on_open_do();
    if (std::empty(on_open)) {
        return;
    }

    auto t = split_tokens(on_open, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }
        py_call_void_fn(mod.c_str(), fn.c_str(),
                        id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
        ERR("Bad on_open call [%s] expected mod:function, got %d elems",
            on_open.c_str(), (int)on_open.size());
    }
}

bool Thing::open (Thingp it)
{_
    if (!is_monst() && !is_player()) {
        return false;
    }

    if (!it->is_openable()) {
        return false;
    }

    if (it->is_open) {
        return false;
    }

    if (it->is_dead) {
        return false;
    }

    if (unlikely(g_opt_debug1)) {
        it->log("Open");
    }

    it->level_pop();
    it->is_open = true;
    it->level_push();

    it->on_open();
    update_light();
    level->dmap_to_player_update();

    return true;
}
