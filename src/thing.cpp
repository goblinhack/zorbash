/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_tile.h"
#include "my_thing_tile.h"
#include "my_python.h"
#include "my_config.h"
#include "my_math_util.h"
#include "my_time_util.h"
#include "my_thing.h"
#include "my_thing_tile.h"
#include "my_string.h"
#include "my_game.h"

thingp thing_new (std::string name,
                  long int thing_id,
                  std::string tp_name)
{_
#ifdef ENABLE_THING_SANITY
    if (thing_find(name)) {
        ERR("thing name [%s] already used", name.c_str());
    }
#endif

    auto t = std::make_shared< class thing >();
    auto result = game.all_things.insert(std::make_pair(name, t));

    if (result.second == false) {
        DIE("thing insert name [%s] failed", name.c_str());
    }

    t->name = name;
    t->thing_id = thing_id;
    t->tp = tp_find(tp_name);
    if (!t->tp) {
        t->err("thing [%s] not found", tp_name.c_str());
    }

    {
        auto tiles = t->get_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_left_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_left_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_right_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_right_tilename(thing_tile_name(tile));
        }
    }
    {
        auto tiles = t->get_top_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_top_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_bot_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_bot_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_tl_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_tl_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_tr_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_tr_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_br_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_br_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_bl_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_bl_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_horiz_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_horiz_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_vert_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_vert_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_l90_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_l90_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_l180_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_l180_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_l_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_l_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_l270_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_l270_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_t_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_t_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_t90_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_t90_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_t180_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_t180_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_t270_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_t270_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_x_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_x_tilename(thing_tile_name(tile));
        }
    }

    {
        auto tiles = t->get_tiles();
        auto tile = thing_tile_random(tiles);
        if (tile) {
            t->set_node_tilename(thing_tile_name(tile));
        }
    }

//    log(t, "created");

    return (t);
}

void thing::destroyed (std::string reason)
{_
    auto t = this;

    /*
     * Too slow with level changes.
     */
//    log(t, "Destroyed thing");

    game.all_things.erase(t->name);
}

void thing::set_tp (std::string tp_name)
{_
    auto t = this;

    t->tp = tp_find(tp_name);
    if (!t->tp) {
        t->err("thing [%s] not found", tp_name.c_str());
    }
}

#if 0
PyObject *thing::push (fpoint3d p)
{_
    auto t = this;

    if (unlikely(t->is_on_map)) {
        t->pop();
        Py_RETURN_NONE;
    }

    t->move_to(p);
//    log(t, "push");

    Py_RETURN_NONE;
}
#endif

void thing::pop (void)
{_
    auto t = this;

    if (unlikely(!t->is_on_map)) {
        return;
    }

    t->is_on_map = false;

    fpoint3d oob = { -1, -1, -1 };
    t->at = oob;

    t->log("pop");
}

void thing::move_to (fpoint3d to)
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
    t->last_move = time_get_time_ms_cached();
    t->end_move = t->last_move + ONESEC / 10;
}

void thing::move_delta (fpoint3d delta)
{_
    auto t = this;

    /*
     * If not moving and this is the first move then break out of the
     * idle animation.
     */
    if (t->is_dir_none()) {
        t->timestamp_change_to_next_frame = time_get_time_ms_cached();
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

void thing::set_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find thing tile %s", name.c_str());
    }

    t->tile = tile;
    if (!t->first_tile) {
        t->first_tile = tile;
    }
}

void thing::set_left_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find left tile %s", name.c_str());
    }

    t->left_tile = tile;
}

void thing::set_right_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find right tile %s", name.c_str());
    }

    t->right_tile = tile;
}

void thing::set_top_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find top tile %s", name.c_str());
    }

    t->top_tile = tile;
}

void thing::set_bot_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find bot tile %s", name.c_str());
    }

    t->bot_tile = tile;
}

void thing::set_tl_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find tl tile %s", name.c_str());
    }

    t->tl_tile = tile;
}

void thing::set_tr_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find tr tile %s", name.c_str());
    }

    t->tr_tile = tile;
}

void thing::set_bl_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find bl tile %s", name.c_str());
    }

    t->bl_tile = tile;
}

void thing::set_br_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find br tile %s", name.c_str());
    }

    t->br_tile = tile;
}

void thing::set_node_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find node tile %s", name.c_str());
    }

    t->node_tile = tile;
}

void thing::set_l90_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find l90 tile %s", name.c_str());
    }

    t->l90_tile = tile;
}

void thing::set_l180_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find l180 tile %s", name.c_str());
    }

    t->l180_tile = tile;
}

void thing::set_l_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find l tile %s", name.c_str());
    }

    t->l_tile = tile;
}

void thing::set_l270_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find l270 tile %s", name.c_str());
    }

    t->l270_tile = tile;
}

void thing::set_t_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find t tile %s", name.c_str());
    }

    t->t_tile = tile;
}

void thing::set_t90_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find t90 tile %s", name.c_str());
    }

    t->t90_tile = tile;
}

void thing::set_t180_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find t180 tile %s", name.c_str());
    }

    t->t180_tile = tile;
}

void thing::set_t270_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find t270 tile %s", name.c_str());
    }

    t->t270_tile = tile;
}

void thing::set_x_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find x tile %s", name.c_str());
    }

    t->x_tile = tile;
}

void thing::set_horiz_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find horiz tile %s", name.c_str());
    }

    t->horiz_tile = tile;
}

void thing::set_vert_tilename (std::string name)
{_
    auto t = this;

    tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find vert tile %s", name.c_str());
    }

    t->vert_tile = tile;
}

/*
 * Find an existing thing.
 */
thingp thing_find (std::string name)
{_
    if (name == "") {
        DIE("no name for thing find");
    }

    auto result = game.all_things.find(name);

    if (result == game.all_things.end()) {
        return (0);
    }

    return (result->second);
}

std::string thing::logname (void)
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

    snprintf(tmp[loop], sizeof(tmp[loop]) - 1, "%s at (%g,%g,%g)",
             t->name.c_str(),
             t->at.x, t->at.y, t->at.z);

    return (tmp[loop++]);
}

thing_tiles thing::get_left_tiles (void)
{_
    auto t = this;

    return (tp_get_left_tiles(t->tp));
}

thing_tiles thing::get_right_tiles (void)
{_
    auto t = this;

    return (tp_get_right_tiles(t->tp));
}

thing_tiles thing::get_top_tiles (void)
{_
    auto t = this;

    return (tp_get_top_tiles(t->tp));
}

thing_tiles thing::get_bot_tiles (void)
{_
    auto t = this;

    return (tp_get_bot_tiles(t->tp));
}

thing_tiles thing::get_tl_tiles (void)
{_
    auto t = this;

    return (tp_get_tl_tiles(t->tp));
}

thing_tiles thing::get_tr_tiles (void)
{_
    auto t = this;

    return (tp_get_tr_tiles(t->tp));
}

thing_tiles thing::get_br_tiles (void)
{_
    auto t = this;

    return (tp_get_br_tiles(t->tp));
}

thing_tiles thing::get_bl_tiles (void)
{_
    auto t = this;

    return (tp_get_bl_tiles(t->tp));
}

thing_tiles thing::get_horiz_tiles (void)
{_
    auto t = this;

    return (tp_get_horiz_tiles(t->tp));
}

thing_tiles thing::get_vert_tiles (void)
{_
    auto t = this;

    return (tp_get_vert_tiles(t->tp));
}

thing_tiles thing::get_l90_tiles (void)
{_
    auto t = this;

    return (tp_get_l90_tiles(t->tp));
}

thing_tiles thing::get_l180_tiles (void)
{_
    auto t = this;

    return (tp_get_l180_tiles(t->tp));
}

thing_tiles thing::get_l_tiles (void)
{_
    auto t = this;

    return (tp_get_l_tiles(t->tp));
}

thing_tiles thing::get_l270_tiles (void)
{_
    auto t = this;

    return (tp_get_l270_tiles(t->tp));
}

thing_tiles thing::get_t_tiles (void)
{_
    auto t = this;

    return (tp_get_t_tiles(t->tp));
}

thing_tiles thing::get_t90_tiles (void)
{_
    auto t = this;

    return (tp_get_t90_tiles(t->tp));
}

thing_tiles thing::get_t180_tiles (void)
{_
    auto t = this;

    return (tp_get_t180_tiles(t->tp));
}

thing_tiles thing::get_t270_tiles (void)
{_
    auto t = this;

    return (tp_get_t270_tiles(t->tp));
}

thing_tiles thing::get_x_tiles (void)
{_
    auto t = this;

    return (tp_get_x_tiles(t->tp));
}

void thing::set_is_dead (uint8_t val)
{_
    auto t = this;

    t->is_dead = val;
}

thing_tiles thing::get_tiles (void)
{_
    auto t = this;

    return (tp_get_tiles(t->tp));
}

void thing::dead (thingp killer, const char * , ...)
{_
    ERR("thing dead TBD");
}

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
