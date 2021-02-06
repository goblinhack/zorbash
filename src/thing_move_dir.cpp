//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_thing.h"
#include "my_thing_template.h"

void Thing::dir_set_none (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    is_facing_left = true;

    if (dir != THING_DIR_NONE) {
        dir = THING_DIR_NONE;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_none (void) const
{_
    return (dir == THING_DIR_NONE);
}

void Thing::dir_set_down (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_DOWN) {
        dir = THING_DIR_DOWN;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_down (void) const
{_
    return (dir == THING_DIR_DOWN);
}

void Thing::dir_set_up (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_UP) {
        dir = THING_DIR_UP;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_up (void) const
{_
    return (dir == THING_DIR_UP);
}

void Thing::dir_set_left (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_LEFT) {
        dir = THING_DIR_LEFT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_left (void) const
{_
    return (dir == THING_DIR_LEFT);
}

void Thing::dir_set_right (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_RIGHT) {
        dir = THING_DIR_RIGHT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_right (void) const
{_
    return (dir == THING_DIR_RIGHT);
}

void Thing::dir_set_tl (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_TL) {
        dir = THING_DIR_TL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tl (void) const
{_
    return (dir == THING_DIR_TL);
}

void Thing::dir_set_bl (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_BL) {
        dir = THING_DIR_BL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_bl (void) const
{_
    return (dir == THING_DIR_BL);
}

void Thing::dir_set_tr (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_TR) {
        dir = THING_DIR_TR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tr (void) const
{_
    return (dir == THING_DIR_TR);
}

void Thing::dir_set_br (void)
{_
    if (tp()->gfx_animated_no_dir()) {
        return;
    }

    if (dir != THING_DIR_BR) {
        dir = THING_DIR_BR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_br (void) const
{_
    return (dir == THING_DIR_BR);
}
