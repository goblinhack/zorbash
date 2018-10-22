/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file.
 */

#pragma once

#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

#include <unordered_map>
#include <memory>

typedef class Tp* Tpp;
typedef std::unordered_map< std::string, Tpp > Tpmap;
typedef std::unordered_map< unsigned int, Tpp > Tpmap_create_order;

#include "my_tile_info.h"

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

class Tp
{
private:

public:
    Tp (void)
    {
        newptr(this, "Tp");
    }

    ~Tp (void)
    {
        oldptr(this);
    }

    int id {};

    /*
     * Internal description of the thing.
     */
    std::string short_name;

    /*
     * Base filename
     */
    std::string raw_name;

    std::string str_zzz1;
    std::string str_zzz2;
    std::string str_zzz3;
    std::string str_zzz4;
    std::string str_zzz5;
    std::string str_zzz6;
    std::string str_zzz7;
    std::string str_zzz8;
    std::string str_zzz9;
    std::string str_zzz10;
    std::string str_zzz11;
    std::string str_zzz12;
    std::string str_zzz13;
    std::string str_zzz14;
    std::string str_zzz15;
    std::string str_zzz16;
    std::string str_zzz17;
    std::string str_zzz18;
    std::string weapon_carry_anim;
    std::string weapon_swing_anim;

    /*
     * Animation tiles.
     */
    Tileinfomap tiles;

    /*
     * Adjacent tiles.
     */
    Tileinfomap top_tiles;
    Tileinfomap bot_tiles;
    Tileinfomap left_tiles;
    Tileinfomap right_tiles;
    Tileinfomap tl_tiles;
    Tileinfomap tr_tiles;
    Tileinfomap bl_tiles;
    Tileinfomap br_tiles;

    /*
     * Join tiles
     */
    Tileinfomap horiz_tiles;
    Tileinfomap vert_tiles;
    Tileinfomap l90_tiles;
    Tileinfomap l180_tiles;
    Tileinfomap l_tiles;
    Tileinfomap l270_tiles;
    Tileinfomap t_tiles;
    Tileinfomap t90_tiles;
    Tileinfomap t180_tiles;
    Tileinfomap t270_tiles;
    Tileinfomap x_tiles;

    int blit_off {};
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
    bool weapon_hit_priority {};
    bool weapon_swing_distance {};
    bool is_weapon_carry_anim {};
    bool is_weapon_swing_effect {};
    bool is_weapon {};
    bool is_outlined {};
    bool is_shadow_caster {};
    bool is_ladder {};
    bool is_animated_walk_flip {};
    bool is_movable {};
    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
Tpp tp_load(int id, std::string file);
void tp_update(Tpp tp);
Tpp tp_find(std::string name);
Tpp tp_find(uint32_t id);
Tpp tp_find_short_name(std::string name);
uint8_t thing_test(int argc, char *argv[]);

static inline int32_t tp_get_blit_top_off (Tpp &t)
{
    return (t->blit_top_off);
}

static inline int32_t tp_get_blit_bot_off (Tpp &t)
{
    return (t->blit_bot_off);
}

static inline int32_t tp_get_blit_left_off (Tpp &t)
{
    return (t->blit_left_off);
}

static inline int32_t tp_get_blit_right_off (Tpp &t)
{
    return (t->blit_right_off);
}

extern Tpmap tp_map;
extern Tpmap_create_order tp_create_order_map;

static inline int tp_to_id (Tpp t)
{
    return (t->id);
}

static inline uint8_t tp_is_floor (Tpp t)
{
    return (t->is_floor);
}

static inline uint8_t tp_is_wall (Tpp t)
{
    return (t->is_wall);
}

static inline uint8_t tp_is_door (Tpp t)
{
    return (t->is_door);
}

static inline uint8_t tp_is_lava (Tpp t)
{
    return (t->is_lava);
}

static inline uint8_t tp_is_water (Tpp t)
{
    return (t->is_water);
}

static inline uint8_t tp_is_monst (Tpp t)
{
    return (t->is_monst);
}

static inline uint8_t tp_is_player (Tpp t)
{
    return (t->is_player);
}

static inline uint8_t tp_is_animation (Tpp t)
{
    return (t->is_animation);
}

static inline uint8_t tp_is_animated (Tpp t)
{
    return (t->is_animated);
}

static inline uint8_t tp_is_animated_no_dir (Tpp t)
{
    return (t->is_animated_no_dir);
}

static inline uint8_t tp_is_rrr1 (Tpp t)
{
    return (t->is_rrr1);
}

static inline uint8_t tp_is_rrr2 (Tpp t)
{
    return (t->is_rrr2);
}

static inline uint8_t tp_is_rrr3 (Tpp t)
{
    return (t->is_rrr3);
}

static inline uint8_t tp_is_rrr4 (Tpp t)
{
    return (t->is_rrr4);
}

static inline uint8_t tp_is_rrr5 (Tpp t)
{
    return (t->is_rrr5);
}

static inline uint8_t tp_is_rrr6 (Tpp t)
{
    return (t->is_rrr6);
}

static inline uint8_t tp_is_rrr7 (Tpp t)
{
    return (t->is_rrr7);
}

static inline uint8_t tp_is_rrr8 (Tpp t)
{
    return (t->is_rrr8);
}

static inline uint8_t tp_is_rrr9 (Tpp t)
{
    return (t->is_rrr9);
}

static inline uint8_t tp_is_rrr10 (Tpp t)
{
    return (t->is_rrr10);
}

static inline uint8_t tp_is_rrr11 (Tpp t)
{
    return (t->is_rrr11);
}

static inline uint8_t tp_is_rrr12 (Tpp t)
{
    return (t->is_rrr12);
}

static inline uint8_t tp_is_rrr13 (Tpp t)
{
    return (t->is_rrr13);
}

static inline uint8_t tp_is_rrr14 (Tpp t)
{
    return (t->is_rrr14);
}

static inline uint8_t tp_is_rrr15 (Tpp t)
{
    return (t->is_rrr15);
}

static inline uint8_t tp_is_rrr16 (Tpp t)
{
    return (t->is_rrr16);
}

static inline uint8_t tp_is_rrr17 (Tpp t)
{
    return (t->is_rrr17);
}

static inline uint8_t tp_is_rrr18 (Tpp t)
{
    return (t->is_rrr18);
}

static inline uint8_t tp_is_rrr19 (Tpp t)
{
    return (t->is_rrr19);
}

static inline uint8_t tp_is_rrr20 (Tpp t)
{
    return (t->is_rrr20);
}

static inline uint8_t tp_is_rrr21 (Tpp t)
{
    return (t->is_rrr21);
}

static inline uint8_t tp_is_rrr22 (Tpp t)
{
    return (t->is_rrr22);
}

static inline uint8_t tp_is_rrr23 (Tpp t)
{
    return (t->is_rrr23);
}

static inline uint8_t tp_is_rrr24 (Tpp t)
{
    return (t->is_rrr24);
}

static inline uint8_t tp_is_rrr25 (Tpp t)
{
    return (t->is_rrr25);
}

static inline uint8_t tp_is_rrr26 (Tpp t)
{
    return (t->is_rrr26);
}

static inline uint8_t tp_is_rrr27 (Tpp t)
{
    return (t->is_rrr27);
}

static inline uint8_t tp_is_rrr28 (Tpp t)
{
    return (t->is_rrr28);
}

static inline uint8_t tp_is_rrr29 (Tpp t)
{
    return (t->is_rrr29);
}

static inline uint8_t tp_is_rrr30 (Tpp t)
{
    return (t->is_rrr30);
}

static inline uint8_t tp_is_rrr31 (Tpp t)
{
    return (t->is_rrr31);
}

static inline uint8_t tp_weapon_hit_priority (Tpp t)
{
    return (t->weapon_hit_priority);
}

static inline uint8_t tp_weapon_swing_distance (Tpp t)
{
    return (t->weapon_swing_distance);
}

static inline uint8_t tp_is_weapon_carry_anim (Tpp t)
{
    return (t->is_weapon_carry_anim);
}

static inline uint8_t tp_is_weapon_swing_effect (Tpp t)
{
    return (t->is_weapon_swing_effect);
}

static inline uint8_t tp_is_weapon (Tpp t)
{
    return (t->is_weapon);
}

static inline uint8_t tp_is_outlined (Tpp t)
{
    return (t->is_outlined);
}

static inline uint8_t tp_is_shadow_caster (Tpp t)
{
    return (t->is_shadow_caster);
}

static inline uint8_t tp_is_ladder (Tpp t)
{
    return (t->is_ladder);
}

static inline uint8_t tp_is_animated_walk_flip (Tpp t)
{
    return (t->is_animated_walk_flip);
}

static inline uint8_t tp_z_depth (Tpp t)
{
    return (t->z_depth);
}

static inline uint8_t tp_is_movable (Tpp t)
{
    return (t->is_movable);
}

static inline uint8_t tp_is_movement_blocking (Tpp t)
{
    return (t->is_movement_blocking);
}

static inline uint8_t tp_is_key (Tpp t)
{
    return (t->is_key);
}

static inline std::string tp_name (Tpp t)
{
    return (t->short_name);
}

static inline std::string tp_short_name (Tpp t)
{
    return (t->short_name);
}

static inline std::string tp_str_zzz1 (Tpp t)
{
    return (t->str_zzz1);
}

static inline std::string tp_str_zzz2 (Tpp t)
{
    return (t->str_zzz2);
}

static inline std::string tp_str_zzz3 (Tpp t)
{
    return (t->str_zzz3);
}

static inline std::string tp_str_zzz4 (Tpp t)
{
    return (t->str_zzz4);
}

static inline std::string tp_str_zzz5 (Tpp t)
{
    return (t->str_zzz5);
}

static inline std::string tp_str_zzz6 (Tpp t)
{
    return (t->str_zzz6);
}

static inline std::string tp_str_zzz7 (Tpp t)
{
    return (t->str_zzz7);
}

static inline std::string tp_str_zzz8 (Tpp t)
{
    return (t->str_zzz8);
}

static inline std::string tp_str_zzz9 (Tpp t)
{
    return (t->str_zzz9);
}

static inline std::string tp_str_zzz10 (Tpp t)
{
    return (t->str_zzz10);
}

static inline std::string tp_str_zzz11 (Tpp t)
{
    return (t->str_zzz11);
}

static inline std::string tp_str_zzz12 (Tpp t)
{
    return (t->str_zzz12);
}

static inline std::string tp_str_zzz13 (Tpp t)
{
    return (t->str_zzz13);
}

static inline std::string tp_str_zzz14 (Tpp t)
{
    return (t->str_zzz14);
}

static inline std::string tp_str_zzz15 (Tpp t)
{
    return (t->str_zzz15);
}

static inline std::string tp_str_zzz16 (Tpp t)
{
    return (t->str_zzz16);
}

static inline std::string tp_str_zzz17 (Tpp t)
{
    return (t->str_zzz17);
}

static inline std::string tp_str_zzz18 (Tpp t)
{
    return (t->str_zzz18);
}

static inline std::string tp_weapon_carry_anim (Tpp t)
{
    return (t->weapon_carry_anim);
}

static inline std::string tp_weapon_swing_anim (Tpp t)
{
    return (t->weapon_swing_anim);
}

static inline std::string tp_raw_name (Tpp t)
{
    return (t->raw_name);
}

static inline Tileinfomap tp_get_tiles (Tpp t)
{
    return (t->tiles);
}

static inline Tileinfomap tp_get_left_tiles (Tpp t)
{
    return (t->left_tiles);
}

static inline Tileinfomap tp_get_right_tiles (Tpp t)
{
    return (t->right_tiles);
}

static inline Tileinfomap tp_get_top_tiles (Tpp t)
{
    return (t->top_tiles);
}

static inline Tileinfomap tp_get_bot_tiles (Tpp t)
{
    return (t->bot_tiles);
}

static inline Tileinfomap tp_get_tl_tiles (Tpp t)
{
    return (t->tl_tiles);
}

static inline Tileinfomap tp_get_tr_tiles (Tpp t)
{
    return (t->tr_tiles);
}

static inline Tileinfomap tp_get_bl_tiles (Tpp t)
{
    return (t->bl_tiles);
}

static inline Tileinfomap tp_get_br_tiles (Tpp t)
{
    return (t->br_tiles);
}

static inline Tileinfomap tp_get_horiz_tiles (Tpp t)
{
    return (t->horiz_tiles);
}

static inline Tileinfomap tp_get_vert_tiles (Tpp t)
{
    return (t->vert_tiles);
}

static inline Tileinfomap tp_get_l90_tiles (Tpp t)
{
    return (t->l90_tiles);
}

static inline Tileinfomap tp_get_l180_tiles (Tpp t)
{
    return (t->l180_tiles);
}

static inline Tileinfomap tp_get_l_tiles (Tpp t)
{
    return (t->l_tiles);
}

static inline Tileinfomap tp_get_l270_tiles (Tpp t)
{
    return (t->l270_tiles);
}

static inline Tileinfomap tp_get_t_tiles (Tpp t)
{
    return (t->t_tiles);
}

static inline Tileinfomap tp_get_t90_tiles (Tpp t)
{
    return (t->t90_tiles);
}

static inline Tileinfomap tp_get_t180_tiles (Tpp t)
{
    return (t->t180_tiles);
}

static inline Tileinfomap tp_get_t270_tiles (Tpp t)
{
    return (t->t270_tiles);
}

static inline Tileinfomap tp_get_x_tiles (Tpp t)
{
    return (t->x_tiles);
}

Tilep tp_first_tile(Tpp tp);

#endif /* THING_TEMPLATE_H */
