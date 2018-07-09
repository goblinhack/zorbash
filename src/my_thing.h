/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#pragma once

#ifndef _MY_THING_H
#define _MY_THING_H

#include "my_config.h"
#include "my_thing_template.h"
#include "my_time_util.h"
#include <stdlib.h>
#include <math.h>
#include <Python.h>

uint8_t thing_init(void);
void thing_fini(void);
thingp thing_new(std::string name, long int thing_id, std::string tp_name);
thingp thing_find(std::string name);

enum {
    THING_DIR_NONE,
    THING_DIR_DOWN,
    THING_DIR_UP,
    THING_DIR_LEFT,
    THING_DIR_RIGHT,
    THING_DIR_TL,
    THING_DIR_BL,
    THING_DIR_TR,
    THING_DIR_BR,
};

class thing
{
private:

public:
    thing (void)
    {
        newptr(this, "thing");
    }

    ~thing (void)
    {
        oldptr(this);
    }

    std::string name; /* key */

    /*
     * Grid coordinates.
     */
    fpoint3d at;

    /*
     * Allocated in python
     */
    long int thing_id {};

    /*
     * Pointer to common settings for this thing.
     */
    tpp tp;

    /*
     * Last anim frame position. To be able to detect moving things.
     */
    fpoint3d last_anim_at;

    /*
     * Previous hop where we were. We use this to interpolate the real
     * position when moving.
     */
    fpoint3d last_at;

    /*
     * Used for animating the steps.
     */
    uint32_t last_move {};
    uint32_t end_move {};

    /*
     * Animation
     */
    tilep tile;
    tilep top_tile;
    tilep bot_tile;
    tilep left_tile;
    tilep right_tile;
    tilep tl_tile;
    tilep tr_tile;
    tilep bl_tile;
    tilep br_tile;
    tilep node_tile;
    tilep horiz_tile;
    tilep vert_tile;
    tilep l90_tile;
    tilep l180_tile;
    tilep l_tile;
    tilep l270_tile;
    tilep t_tile;
    tilep t90_tile;
    tilep t180_tile;
    tilep t270_tile;
    tilep x_tile;

    tilep first_tile;

    uint32_t timestamp_change_to_next_frame {};
    uint8_t dir {};
    thing_tilep current_tile;

    /*
     * Only used for display purposes.
     */
    int score {};
    int gold {};
    int hp {};

    /*
     * Debugging this thing?
     */
    bool debug {};
    bool is_on_map {};
    bool is_dead {};
    bool is_sleeping {};
    bool is_moving {};
    bool has_ever_moved {};
    bool is_open {};
    
    /*
     * Interpolated move for display.
     */
    fpoint3d curr_at (void)
    {
        auto now = time_get_time_ms_cached();
        if (now >= end_move) {
            return (at);
        }

        double move_time = end_move - last_move;
        auto dx = (at.x - last_at.x) / move_time;
        auto dy = (at.y - last_at.y) / move_time;

        double step = (time_get_time_ms_cached() - last_move) / move_time;

        return (fpoint3d(at.x + dx * step, at.y + dy * step, 0));
    }

    uint8_t is_monst (void)
    {
        return (tp_is_monst(tp));
    }

    uint8_t is_door (void)
    {
        return (tp_is_door(tp));
    }

    uint8_t is_wall (void)
    {
        return (tp_is_wall(tp));
    }

    uint8_t is_player (void)
    {
        return (tp_is_player(tp));
    }

    uint8_t is_movable (void)
    {
        return (tp_is_movable(tp));
    }

    PyObject *push(fpoint3d);
    bool can_move_delta(fpoint3d delta);
    std::string logname(void);
    std::string short_name(void);
    uint8_t is_dir_bl(void);
    uint8_t is_dir_br(void);
    uint8_t is_dir_down(void);
    uint8_t is_dir_left(void);
    uint8_t is_dir_none(void);
    uint8_t is_dir_right(void);
    uint8_t is_dir_tl(void);
    uint8_t is_dir_tr(void);
    uint8_t is_dir_up(void);
    void animate();
    void dead(thingp killer, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
    void destroyed(std::string reason);
    void move_delta(fpoint3d);
    void move_to(fpoint3d to);
    void pop(void);
    void set_dir_bl(void);
    void set_dir_br(void);
    void set_dir_down(void);
    void set_dir_left(void);
    void set_dir_none(void);
    void set_dir_right(void);
    void set_dir_tl(void);
    void set_dir_tr(void);
    void set_dir_up(void);
    void set_is_dead(uint8_t val);

    void set_bl_tilename(std::string tilename);
    void set_bot_tilename(std::string tilename);
    void set_br_tilename(std::string tilename);
    void set_horiz_tilename(std::string tilename);
    void set_l180_tilename(std::string tilename);
    void set_l270_tilename(std::string tilename);
    void set_l90_tilename(std::string tilename);
    void set_l_tilename(std::string tilename);
    void set_left_tilename(std::string tilename);
    void set_node_tilename(std::string tilename);
    void set_right_tilename(std::string tilename);
    void set_t180_tilename(std::string tilename);
    void set_t270_tilename(std::string tilename);
    void set_t90_tilename(std::string tilename);
    void set_t_tilename(std::string tilename);
    void set_tilename(std::string tilename);
    void set_tl_tilename(std::string tilename);
    void set_top_tilename(std::string tilename);
    void set_tr_tilename(std::string tilename);
    void set_vert_tilename(std::string tilename);
    void set_x_tilename(std::string tilename);

    thing_tiles get_bl_tiles(void);
    thing_tiles get_bot_tiles(void);
    thing_tiles get_br_tiles(void);
    thing_tiles get_horiz_tiles(void);
    thing_tiles get_l180_tiles(void);
    thing_tiles get_l270_tiles(void);
    thing_tiles get_l90_tiles(void);
    thing_tiles get_l_tiles(void);
    thing_tiles get_left_tiles(void);
    thing_tiles get_right_tiles(void);
    thing_tiles get_t180_tiles(void);
    thing_tiles get_t270_tiles(void);
    thing_tiles get_t90_tiles(void);
    thing_tiles get_t_tiles(void);
    thing_tiles get_tiles(void);
    thing_tiles get_tl_tiles(void);
    thing_tiles get_top_tiles(void);
    thing_tiles get_tr_tiles(void);
    thing_tiles get_vert_tiles(void);
    thing_tiles get_x_tiles(void);

    void set_tp(std::string tp);

    void log_(const char *fmt, va_list args);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args);
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args);
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
};

#include "my_thing_template.h"

/*
 * thing_iso.c
 */
thingp get_front_thing(thingp a, thingp b);

/*
 * thing_map.c
 */
extern void thing_render_all(void);

/*
 * thing animate
 */
void thing_animate_all();

#endif /* THING_H */
