/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#pragma once

#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

typedef std::shared_ptr< class thing_template > tpp;
typedef std::map< std::string, tpp > thing_templates;
typedef std::map< unsigned int, tpp > thing_templates_create_order;

#include "my_thing_tile.h"

enum {
    IS_JOIN_HORIZ,
    IS_JOIN_VERT,
    IS_JOIN_NODE,
    IS_JOIN_LEFT,
    IS_JOIN_RIGHT,
    IS_JOIN_TOP,
    IS_JOIN_BOT,
    IS_JOIN_L90,
    IS_JOIN_L180,
    IS_JOIN_L,
    IS_JOIN_L270,
    IS_JOIN_T,
    IS_JOIN_T90,
    IS_JOIN_T180,
    IS_JOIN_T270,
    IS_JOIN_X,
    IS_JOIN_MAX,
};

class thing_template
{
private:

public:
    thing_template (void)
    {
        newptr(this, "thing_template");
    }

    ~thing_template (void)
    {
        oldptr(this);
    }

    int tp_id {};

    /*
     * Internal description of the thing.
     */
    std::string short_name;

    /*
     * Base filename
     */
    std::string raw_name;

    /*
     * Animation tiles.
     */
    thing_tiles tiles;

    /*
     * Adjacent tiles.
     */
    thing_tiles top_tiles;
    thing_tiles bot_tiles;
    thing_tiles left_tiles;
    thing_tiles right_tiles;
    thing_tiles tl_tiles;
    thing_tiles tr_tiles;
    thing_tiles bl_tiles;
    thing_tiles br_tiles;

    /*
     * Join tiles
     */
    thing_tiles horiz_tiles;
    thing_tiles vert_tiles;
    thing_tiles l90_tiles;
    thing_tiles l180_tiles;
    thing_tiles l_tiles;
    thing_tiles l270_tiles;
    thing_tiles t_tiles;
    thing_tiles t90_tiles;
    thing_tiles t180_tiles;
    thing_tiles t270_tiles;
    thing_tiles x_tiles;

    int blit_top_off {};
    int blit_bot_off {};
    int blit_left_off {};
    int blit_right_off {};

    bool has_dir_anim {};
    bool is_animated {};
    bool is_animated_no_dir {};
    bool is_animation {};
    bool is_door {};
    bool is_floor {};
    bool is_key {};
    bool is_lava {};
    bool is_monst {};
    bool is_movement_blocking {};
    bool is_player {};
    bool is_wall {};
    bool is_water {};
    bool is_rrr1 {};
    bool is_rrr2 {};
    bool is_rrr3 {};
    bool is_rrr4 {};
    bool is_rrr5 {};
    bool is_rrr6 {};
    bool is_rrr7 {};
    bool is_rrr8 {};
    bool is_rrr9 {};
    bool is_rrr10 {};
    bool is_rrr11 {};
    bool is_rrr12 {};
    bool is_rrr13 {};
    bool is_rrr14 {};
    bool is_rrr15 {};
    bool is_rrr16 {};
    bool is_rrr17 {};
    bool is_rrr18 {};
    bool is_rrr19 {};
    bool is_rrr20 {};
    bool is_rrr21 {};
    bool is_rrr22 {};
    bool is_rrr23 {};
    bool is_rrr24 {};
    bool is_rrr25 {};
    bool is_rrr26 {};
    bool is_rrr27 {};
    bool is_rrr28 {};
    bool is_rrr29 {};
    bool is_rrr30 {};
    bool is_rrr31 {};
    bool is_rrr32 {};
    bool is_rrr33 {};
    bool is_rrr34 {};
    bool is_rrr35 {};
    bool is_rrr36 {};
    bool is_rrr37 {};
    bool is_rrr38 {};
    bool is_rrr39 {};
    bool is_rrr40 {};
    bool is_rrr41 {};
    bool is_animated_walk_flip {};
    bool is_movable {};
    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
tpp tp_load(int id, std::string file);
void tp_update(tpp tp);
tpp tp_find(std::string name);
tpp tp_find_short_name(std::string name);
uint8_t thing_test(int argc, char *argv[]);

std::string tp_name(tpp);
std::string tp_short_name(tpp);
std::string tp_raw_name(tpp);

static inline int32_t tp_get_blit_top_off (tpp t)
{
    return (t->blit_top_off);
}

static inline int32_t tp_get_blit_bot_off (tpp t)
{
    return (t->blit_bot_off);
}

static inline int32_t tp_get_blit_left_off (tpp t)
{
    return (t->blit_left_off);
}

static inline int32_t tp_get_blit_right_off (tpp t)
{
    return (t->blit_right_off);
}

extern thing_tiles tp_get_tiles(tpp);
extern thing_tiles tp_get_left_tiles(tpp);
extern thing_tiles tp_get_right_tiles(tpp);
extern thing_tiles tp_get_top_tiles(tpp);
extern thing_tiles tp_get_bot_tiles(tpp);
extern thing_tiles tp_get_tl_tiles(tpp);
extern thing_tiles tp_get_tr_tiles(tpp);
extern thing_tiles tp_get_bl_tiles(tpp);
extern thing_tiles tp_get_br_tiles(tpp);
extern thing_tiles tp_get_horiz_tiles(tpp);
extern thing_tiles tp_get_vert_tiles(tpp);
extern thing_tiles tp_get_l90_tiles(tpp);
extern thing_tiles tp_get_l180_tiles(tpp);
extern thing_tiles tp_get_l_tiles(tpp);
extern thing_tiles tp_get_l270_tiles(tpp);
extern thing_tiles tp_get_t_tiles(tpp);
extern thing_tiles tp_get_t90_tiles(tpp);
extern thing_tiles tp_get_t180_tiles(tpp);
extern thing_tiles tp_get_t270_tiles(tpp);
extern thing_tiles tp_get_x_tiles(tpp);
extern thing_templates thing_templates_map;
extern thing_templates_create_order thing_templates_create_order_map;

static inline int tp_to_id (tpp t)
{
    return (t->tp_id);
}

static inline uint8_t tp_is_floor (tpp t)
{
    return (t->is_floor);
}

static inline uint8_t tp_is_wall (tpp t)
{
    return (t->is_wall);
}

static inline uint8_t tp_is_door (tpp t)
{
    return (t->is_door);
}

static inline uint8_t tp_is_lava (tpp t)
{
    return (t->is_lava);
}

static inline uint8_t tp_is_water (tpp t)
{
    return (t->is_water);
}

static inline uint8_t tp_is_monst (tpp t)
{
    return (t->is_monst);
}

static inline uint8_t tp_is_player (tpp t)
{
    return (t->is_player);
}

static inline uint8_t tp_is_animation (tpp t)
{
    return (t->is_animation);
}

static inline uint8_t tp_is_animated (tpp t)
{
    return (t->is_animated);
}

static inline uint8_t tp_is_animated_no_dir (tpp t)
{
    return (t->is_animated_no_dir);
}

static inline uint8_t tp_is_rrr1 (tpp t)
{
    return (t->is_rrr1);
}

static inline uint8_t tp_is_rrr2 (tpp t)
{
    return (t->is_rrr2);
}

static inline uint8_t tp_is_rrr3 (tpp t)
{
    return (t->is_rrr3);
}

static inline uint8_t tp_is_rrr4 (tpp t)
{
    return (t->is_rrr4);
}

static inline uint8_t tp_is_rrr5 (tpp t)
{
    return (t->is_rrr5);
}

static inline uint8_t tp_is_rrr6 (tpp t)
{
    return (t->is_rrr6);
}

static inline uint8_t tp_is_rrr7 (tpp t)
{
    return (t->is_rrr7);
}

static inline uint8_t tp_is_rrr8 (tpp t)
{
    return (t->is_rrr8);
}

static inline uint8_t tp_is_rrr9 (tpp t)
{
    return (t->is_rrr9);
}

static inline uint8_t tp_is_rrr10 (tpp t)
{
    return (t->is_rrr10);
}

static inline uint8_t tp_is_rrr11 (tpp t)
{
    return (t->is_rrr11);
}

static inline uint8_t tp_is_rrr12 (tpp t)
{
    return (t->is_rrr12);
}

static inline uint8_t tp_is_rrr13 (tpp t)
{
    return (t->is_rrr13);
}

static inline uint8_t tp_is_rrr14 (tpp t)
{
    return (t->is_rrr14);
}

static inline uint8_t tp_is_rrr15 (tpp t)
{
    return (t->is_rrr15);
}

static inline uint8_t tp_is_rrr16 (tpp t)
{
    return (t->is_rrr16);
}

static inline uint8_t tp_is_rrr17 (tpp t)
{
    return (t->is_rrr17);
}

static inline uint8_t tp_is_rrr18 (tpp t)
{
    return (t->is_rrr18);
}

static inline uint8_t tp_is_rrr19 (tpp t)
{
    return (t->is_rrr19);
}

static inline uint8_t tp_is_rrr20 (tpp t)
{
    return (t->is_rrr20);
}

static inline uint8_t tp_is_rrr21 (tpp t)
{
    return (t->is_rrr21);
}

static inline uint8_t tp_is_rrr22 (tpp t)
{
    return (t->is_rrr22);
}

static inline uint8_t tp_is_rrr23 (tpp t)
{
    return (t->is_rrr23);
}

static inline uint8_t tp_is_rrr24 (tpp t)
{
    return (t->is_rrr24);
}

static inline uint8_t tp_is_rrr25 (tpp t)
{
    return (t->is_rrr25);
}

static inline uint8_t tp_is_rrr26 (tpp t)
{
    return (t->is_rrr26);
}

static inline uint8_t tp_is_rrr27 (tpp t)
{
    return (t->is_rrr27);
}

static inline uint8_t tp_is_rrr28 (tpp t)
{
    return (t->is_rrr28);
}

static inline uint8_t tp_is_rrr29 (tpp t)
{
    return (t->is_rrr29);
}

static inline uint8_t tp_is_rrr30 (tpp t)
{
    return (t->is_rrr30);
}

static inline uint8_t tp_is_rrr31 (tpp t)
{
    return (t->is_rrr31);
}

static inline uint8_t tp_is_rrr32 (tpp t)
{
    return (t->is_rrr32);
}

static inline uint8_t tp_is_rrr33 (tpp t)
{
    return (t->is_rrr33);
}

static inline uint8_t tp_is_rrr34 (tpp t)
{
    return (t->is_rrr34);
}

static inline uint8_t tp_is_rrr35 (tpp t)
{
    return (t->is_rrr35);
}

static inline uint8_t tp_is_rrr36 (tpp t)
{
    return (t->is_rrr36);
}

static inline uint8_t tp_is_rrr37 (tpp t)
{
    return (t->is_rrr37);
}

static inline uint8_t tp_is_rrr38 (tpp t)
{
    return (t->is_rrr38);
}

static inline uint8_t tp_is_rrr39 (tpp t)
{
    return (t->is_rrr39);
}

static inline uint8_t tp_is_rrr40 (tpp t)
{
    return (t->is_rrr40);
}

static inline uint8_t tp_is_rrr41 (tpp t)
{
    return (t->is_rrr41);
}

static inline uint8_t tp_is_animated_walk_flip (tpp t)
{
    return (t->is_animated_walk_flip);
}

static inline uint8_t tp_z_depth (tpp t)
{
    return (t->z_depth);
}

static inline uint8_t tp_is_movable (tpp t)
{
    return (t->is_movable);
}

static inline uint8_t tp_is_movement_blocking (tpp t)
{
    return (t->is_movement_blocking);
}

static inline uint8_t tp_is_key (tpp t)
{
    return (t->is_key);
}

tilep tp_first_tile(tpp tp);

#endif /* THING_TEMPLATE_H */
