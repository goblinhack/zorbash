//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_thing.h"
#include "my_game_status.h"

int Thing::actionbar_id_insert (Thingp what)
{_
    if (!is_player()) {
        return -1;
    }

    if (!monstp) {
        return -1;
    }

    for (auto i = 0; i < ACTIONBAR_ITEMS; i++) {
        auto a = monstp->actionbar_id[i];
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
        auto a = monstp->actionbar_id[i];
        if (a) {
            continue;
        }
        monstp->actionbar_id[i] = what->id;
        game_status_wid_init();
        return i;
    }
    MINICON("No space to carry %s which is not carried",
            what->text_The().c_str());
    return -1;
}

int Thing::actionbar_id_remove (Thingp what)
{_
    if (!is_player()) {
        return -1;
    }

    if (!monstp) {
        return -1;
    }

    for (auto i = 0; i < ACTIONBAR_ITEMS; i++) {
        auto a = monstp->actionbar_id[i];
        if (!a) {
            continue;
        }
        auto t = thing_find(a);
        if (t->tp() == what->tp()) {
            monstp->actionbar_id[i] = 0;
            game_status_wid_init();
            return i;
        }
    }
    return -1;
}

int Thing::actionbar_id_slot_count (const int slot)
{_
    auto a = monstp->actionbar_id[slot];
    if (!a) {
        return 0;
    }

    if (!monstp) {
        return 0;
    }

    auto t = thing_find(a);
    if (!t) {
        return 0;
    }

    auto count = 0;
    for (auto oid : monstp->carrying) {
        auto o = thing_find(oid);
        if (o->tp() == t->tp()) {
            count++;
        }
    }

    return count;
}
