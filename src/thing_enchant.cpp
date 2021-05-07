//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_dmap.h"
#include "my_monst.h"
#include "my_python.h"
#include "my_string.h"

//
// Python callback upon being enchant
//
void Thing::on_enchant (void)
{_
    auto on_enchant = tp()->on_enchant_do();
    if (std::empty(on_enchant)) {
        return;
    }

    auto t = split_tokens(on_enchant, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s)", mod.c_str(), fn.c_str(),
            to_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id,
                        (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
        ERR("Bad on_enchant call [%s] expected mod:function, got %d elems",
            on_enchant.c_str(), (int)on_enchant.size());
    }
}

bool Thing::enchant (void)
{_
    log("Enchant");

    on_enchant();

    return true;
}
