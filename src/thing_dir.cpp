/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_math_util.h"

void thing::set_dir_none (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_NONE) {
        t->dir = THING_DIR_NONE;
    }
}

uint8_t thing::is_dir_none (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_NONE);
}

void thing::set_dir_down (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_DOWN) {
        t->dir = THING_DIR_DOWN;
    }
}

uint8_t thing::is_dir_down (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_DOWN);
}

void thing::set_dir_up (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_UP) {
        t->dir = THING_DIR_UP;
    }
}

uint8_t thing::is_dir_up (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_UP);
}

void thing::set_dir_left (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_LEFT) {
        t->dir = THING_DIR_LEFT;
    }
}

uint8_t thing::is_dir_left (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_LEFT);
}

void thing::set_dir_right (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_RIGHT) {
        t->dir = THING_DIR_RIGHT;
    }
}

uint8_t thing::is_dir_right (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_RIGHT);
}

void thing::set_dir_tl (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_TL) {
        t->dir = THING_DIR_TL;
    }
}

uint8_t thing::is_dir_tl (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_TL);
}

void thing::set_dir_bl (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_BL) {
        t->dir = THING_DIR_BL;
    }
}

uint8_t thing::is_dir_bl (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_BL);
}

void thing::set_dir_tr (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_TR) {
        t->dir = THING_DIR_TR;
    }
}

uint8_t thing::is_dir_tr (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_TR);
}

void thing::set_dir_br (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_BR) {
        t->dir = THING_DIR_BR;
    }
}

uint8_t thing::is_dir_br (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_BR);
}

void thing_dir (thingp t, double *dx, double *dy)
{_
    *dx = 0;
    *dy = 0;

    if (t->is_dir_down()) {
        *dy = 1.0;
    }

    if (t->is_dir_up()) {
        *dy = -1.0;
    }

    if (t->is_dir_right()) {
        *dx = 1.0;
    }

    if (t->is_dir_left()) {
        *dx = -1.0;
    }

    if (t->is_dir_tl()) {
        *dx = -1.0;
        *dy = -1.0;
    }

    if (t->is_dir_tr()) {
        *dx = 1.0;
        *dy = -1.0;
    }

    if (t->is_dir_bl()) {
        *dx = -1.0;
        *dy = 1.0;
    }

    if (t->is_dir_br()) {
        *dx = 1.0;
        *dy = 1.0;
    }
}

int thing_angle_to_dir (double dx, double dy)
{_
    fpoint r;
    r.x = dx;
    r.y = -dy;

    int segment = ((int)(round(radians2angle(anglerot(r)) / 45.0))) % 8;

    switch (segment) {
        case 2:
            return (THING_DIR_UP);
        case 1:
            return (THING_DIR_TR);
        case 0:
            return (THING_DIR_RIGHT);
        case 7:
            return (THING_DIR_BR);
        case 6:
            return (THING_DIR_DOWN);
        case 5:
            return (THING_DIR_BL);
        case 4:
            return (THING_DIR_LEFT);
        case 3:
            return (THING_DIR_TL);
    }

    DIE("thing_angle_to_dir bug");
}
