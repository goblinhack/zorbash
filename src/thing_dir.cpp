//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_level.h"
#include "my_thing.h"

point Thing::dir_to_direction (void) const
{_
    if (is_dir_tl()) {
        return point(-1, -1);
    }

    if (is_dir_tr()) {
        return point(1, -1);
    }

    if (is_dir_bl()) {
        return point(-1, 1);
    }

    if (is_dir_br()) {
        return point(1, 1);
    }

    if (is_dir_down()) {
        return point(0, 1);
    }

    if (is_dir_up()) {
        return point(0, -1);
    }

    if (is_dir_right()) {
        return point(1, 0);
    }

    if (is_dir_left()) {
        return point(-1, 0);
    }
    return point(0, 0);
}
