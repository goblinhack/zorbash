//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_level.h"
#include "my_thing.h"

void Thing::used (Thingp what, point used_where)
{_
    if (is_player()) {
        if (!actionbar_id_remove(what, used_where)) {
            return;
        }
    }

    if (!monstp) {
        return;
    }

    auto existing_owner = what->owner_get();
    if (existing_owner != this) {
        err("attempt to use %s which is not carried", what->to_string().c_str());
        return;
    }

    what->remove_owner();
    what->visible();

    monstp->carrying.remove(what->id);
    log("used %s", what->to_string().c_str());
    what->detach();
    what->dead("used");
}
