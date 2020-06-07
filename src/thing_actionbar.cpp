//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_thing.h"
#include "my_game_status.h"

int Thing::actionbar_insert (Thingp what)
{_
    if (!is_player()) {
        return -1;
    }

    if (!monstp) {
        return -1;
    }

    for (auto i = 0; i < ACTIONBAR_ITEMS; i++) {
        auto a = monstp->actionbar[i];
        if (!a) {
            continue;
        }
        auto t = thing_find(a);
        if (t->tp() == what->tp()) {
            game_status_wid_init();
            return i;
        }
    }

    for (auto i = 0; i < ACTIONBAR_ITEMS; i++) {
        auto a = monstp->actionbar[i];
        if (a) {
            continue;
        }
        monstp->actionbar[i] = what->id;
        game_status_wid_init();
        return i;
    }
    MINICON("No space to carry %s which is not carried",
            what->text_The().c_str());
    return -1;
}

int Thing::actionbar_remove (Thingp what)
{_
    if (!is_player()) {
        return -1;
    }

    if (!monstp) {
        return -1;
    }

    for (auto i = 0; i < ACTIONBAR_ITEMS; i++) {
        auto a = monstp->actionbar[i];
        if (!a) {
            continue;
        }
        auto t = thing_find(a);
        if (t->tp() == what->tp()) {
            monstp->actionbar[i] = 0;
            game_status_wid_init();
            return i;
        }
    }
    return -1;
}
