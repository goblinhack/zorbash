/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_tile_info.h"
#include "my_game.h"

static uint32_t thing_id;

Thingp thing_new (std::string tp_name)
{_
    auto id = ++thing_id;

    auto t = std::make_shared< class Thing >();
    auto result = game.state.map.all_things.insert(std::make_pair(id, t));

    if (result.second == false) {
        DIE("thing insert [%d] failed", id);
    }

    t->id = id;
    t->tp = tp_find(tp_name);
    if (!t->tp) {
        DIE("thing [%s] not found", tp_name.c_str());
    }

    t->dir                          = THING_DIR_NONE;
    t->is_on_map                    = false;
    t->is_dead                      = false;
    t->is_sleeping                  = false;
    t->is_moving                    = false;
    t->has_ever_moved               = false;
    t->is_open                      = false;
    
    auto tiles = tp_get_left_tiles(t->tp);
    auto Tileinfo = tile_info_random(tiles);
    if (Tileinfo) {
        t->left_tile = Tileinfo->tile;
    }

    tiles = tp_get_right_tiles(t->tp);
    Tileinfo = tile_info_random(tiles);
    if (Tileinfo) {
        t->right_tile = Tileinfo->tile;
    }

//    log(t, "created");

    return (t);
}

void Thing::destroyed (std::string reason)
{_
    auto t = this;

    game.state.map.all_things.erase(t->id);
}

void Thing::pop (void)
{_
    auto t = this;

    if (unlikely(!t->is_on_map)) {
        return;
    }

    t->is_on_map = false;

    fpoint oob = { -1, -1 };
    t->at = oob;

    t->log("pop");
}

void Thing::move_to (fpoint to)
{_
    auto t = this;

    t->animate();
    t->has_ever_moved = true;
    t->is_on_map = true;

    if (!t->has_ever_moved) {
        t->last_at = to;
    } else {
        t->last_at = t->at;
    }

    /*
     * Moves are immediate, but we render the move in steps, hence keep
     * track of when we moved.
     */
    t->at = to;
    t->last_move_ms = time_get_time_ms_cached();
    t->end_move_ms = t->last_move_ms + ONESEC / 10;
}

void Thing::move_delta (fpoint delta)
{_
    auto t = this;

    /*
     * If not moving and this is the first move then break out of the
     * idle animation.
     */
    if (t->is_dir_none()) {
        t->next_frame_ms = time_get_time_ms_cached();
    }

    if (delta.x > 0) {
        t->set_dir_left();
        t->is_moving = true;
        t->has_ever_moved = true;
    }

    if (delta.x < 0) {
        t->set_dir_right();
        t->is_moving = true;
        t->has_ever_moved = true;
    }

    if (delta.y > 0) {
        t->set_dir_up();
        t->is_moving = true;
        t->has_ever_moved = true;
    }

    if (delta.y < 0) {
        t->set_dir_down();
        t->is_moving = true;
        t->has_ever_moved = true;
    }

    t->animate();
    t->move_to(t->at + delta);
}

/*
 * Find an existing thing.
 */
Thingp thing_find (uint32_t id)
{_
    auto result = game.state.map.all_things.find(id);
    if (result == game.state.map.all_things.end()) {
        return (0);
    }

    return (result->second);
}

std::string Thing::logname (void)
{_
    auto t = this;

    /*
     * Return constant strings from a small pool.
     */
    static char tmp[10][MAXSTR];
    static int loop;

    if (loop >= 10) {
        loop = 0;
    }

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "%u(%s) at (%g,%g)",
             t->id, t->tp->short_name.c_str(), t->at.x, t->at.y);

    return (tmp[loop++]);
}

void Thing::dead (Thingp killer, const char * , ...)
{_
    ERR("thing dead TBD");
}

void Thing::set_dir_none (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_NONE) {
        t->dir = THING_DIR_NONE;
    }
}

uint8_t Thing::is_dir_none (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_NONE);
}

void Thing::set_dir_down (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_DOWN) {
        t->dir = THING_DIR_DOWN;
    }
}

uint8_t Thing::is_dir_down (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_DOWN);
}

void Thing::set_dir_up (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_UP) {
        t->dir = THING_DIR_UP;
    }
}

uint8_t Thing::is_dir_up (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_UP);
}

void Thing::set_dir_left (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_LEFT) {
        t->dir = THING_DIR_LEFT;
    }
}

uint8_t Thing::is_dir_left (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_LEFT);
}

void Thing::set_dir_right (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_RIGHT) {
        t->dir = THING_DIR_RIGHT;
    }
}

uint8_t Thing::is_dir_right (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_RIGHT);
}

void Thing::set_dir_tl (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_TL) {
        t->dir = THING_DIR_TL;
    }
}

uint8_t Thing::is_dir_tl (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_TL);
}

void Thing::set_dir_bl (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_BL) {
        t->dir = THING_DIR_BL;
    }
}

uint8_t Thing::is_dir_bl (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_BL);
}

void Thing::set_dir_tr (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_TR) {
        t->dir = THING_DIR_TR;
    }
}

uint8_t Thing::is_dir_tr (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_TR);
}

void Thing::set_dir_br (void)
{_
    auto t = this;

    if (tp_is_animated_no_dir(t->tp)) {
        return;
    }

    if (t->dir != THING_DIR_BR) {
        t->dir = THING_DIR_BR;
    }
}

uint8_t Thing::is_dir_br (void)
{_
    auto t = this;

    return (t->dir == THING_DIR_BR);
}
