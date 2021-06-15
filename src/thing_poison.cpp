//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::poison_boost (int v)
{_
#if 0
    if (!v) {
        return;
    }

    auto old_poison = get_poison();
    auto new_poison = old_poison + v;
    auto max_poison = get_poison_max();
    new_poison = std::min(new_poison, max_poison);
    set_poison(new_poison);

    if (new_poison >= max_poison) {
        dbg("poison boost not possible, maxxed at %d", new_poison);
    } else {
        dbg("poison boost by %d from %d to %d", v, old_poison, new_poison);
    }
#endif
}
