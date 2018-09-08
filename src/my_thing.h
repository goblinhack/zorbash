/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#pragma once

#ifndef _MY_THING_H
#define _MY_THING_H

#include <map>

typedef std::shared_ptr< class Thing > Thingp;
typedef std::map< uint32_t, Thingp > Things;

#include "my_thing_template.h"
#include "my_tile_info.h"
#include "my_time_util.h"

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

class Thing
{
private:

public:
    Thing (void)
    {
        newptr(this, "thing");
    }

    ~Thing (void)
    {
        oldptr(this);
    }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(cereal::make_nvp("id",              id));
    }

    /*
     * Unique per thing.
     */
    uint32_t           id {};

    /*
     * Grid coordinates.
     */
    fpoint             at;

    /*
     * Previous hop where we were. We use this to interpolate the real
     * position when moving.
     */
    fpoint             last_at;

    /*
     * Pointer to common settings for this thing.
     */
    Tpp                tp;

    /*
     * Used for animating the steps.
     */
    uint32_t           last_move_ms {};
    uint32_t           end_move_ms {};
    uint32_t           next_frame_ms {};
    Tileinfop          current_tile;

    /*
     * For thing decorations
     */
    Tilep              top_tile;
    Tilep              bot_tile;
    Tilep              left_tile;
    Tilep              right_tile;
    Tilep              tl_tile;
    Tilep              tr_tile;
    Tilep              bl_tile;
    Tilep              br_tile;

    /*
     * Only used for display purposes.
     */
    uint16_t           gold {};
    uint16_t           hp {};

    unsigned int       dir:4;
    unsigned int       is_on_map:1;
    unsigned int       is_dead:1;
    unsigned int       is_sleeping:1;
    unsigned int       is_moving:1;
    unsigned int       has_ever_moved:1;
    unsigned int       is_open:1;
    
    std::string logname(void);
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
    void dead(Thingp killer, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
    void destroyed(std::string reason);
    void move_delta(fpoint);
    void move_to(fpoint to);
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

    void log_(const char *fmt, va_list args); // compile error without
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
};

extern Thingp thing_new(std::string tp_name);
extern Thingp thing_find(uint32_t name);
extern void thing_animate_all();

#endif /* THING_H */
