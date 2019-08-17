//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"

void Thing::dir_set_none (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    is_facing_left = true;

    if (dir != THING_DIR_NONE) {
        dir = THING_DIR_NONE;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_none (void)
{
    return (dir == THING_DIR_NONE);
}

void Thing::dir_set_down (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_DOWN) {
        dir = THING_DIR_DOWN;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_down (void)
{
    return (dir == THING_DIR_DOWN);
}

void Thing::dir_set_up (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_UP) {
        dir = THING_DIR_UP;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_up (void)
{
    return (dir == THING_DIR_UP);
}

void Thing::dir_set_left (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_LEFT) {
        dir = THING_DIR_LEFT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_left (void)
{
    return (dir == THING_DIR_LEFT);
}

void Thing::dir_set_right (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_RIGHT) {
        dir = THING_DIR_RIGHT;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_right (void)
{
    return (dir == THING_DIR_RIGHT);
}

void Thing::dir_set_tl (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_TL) {
        dir = THING_DIR_TL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tl (void)
{
    return (dir == THING_DIR_TL);
}

void Thing::dir_set_bl (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_BL) {
        dir = THING_DIR_BL;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_bl (void)
{
    return (dir == THING_DIR_BL);
}

void Thing::dir_set_tr (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_TR) {
        dir = THING_DIR_TR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_tr (void)
{
    return (dir == THING_DIR_TR);
}

void Thing::dir_set_br (void)
{
    if (tp_gfx_animated_no_dir(tp())) {
        return;
    }

    if (dir != THING_DIR_BR) {
        dir = THING_DIR_BR;
        move_carried_items();
    }
}

uint8_t Thing::is_dir_br (void)
{
    return (dir == THING_DIR_BR);
}
