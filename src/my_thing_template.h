/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
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
    std::string str_light_color;
    std::string weapon_carry_anim;
    std::string weapon_use_anim;

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

    int has_dir_anim {};
    int is_animated {};
    int is_animated_no_dir {};
    int is_animation {};
    int is_door {};
    int is_floor {};
    int is_key {};
    int is_lava {};
    int is_monst {};
    int is_movement_blocking {};
    int is_player {};
    int is_wall {};
    int is_rock {};
    int is_water {};
    int is_deep_water {};
    int is_rrr1 {};
    int is_rrr2 {};
    int is_rrr3 {};
    int is_rrr4 {};
    int is_rrr5 {};
    int is_rrr6 {};
    int is_rrr7 {};
    int is_rrr8 {};
    int is_rrr9 {};
    int is_rrr10 {};
    int is_rrr11 {};
    int is_rrr12 {};
    int is_rrr13 {};
    int is_rrr14 {};
    int is_rrr15 {};
    int is_rrr16 {};
    int is_rrr17 {};
    int is_rrr18 {};
    int is_rrr19 {};
    int is_rrr20 {};
    int is_rrr21 {};
    int is_rrr22 {};
    int is_rrr23 {};
    int is_rrr24 {};
    int is_rrr25 {};
    int is_rrr26 {};
    int is_rrr27 {};
    int is_rrr28 {};
    int is_meat_eater {};
    int is_made_of_meat {};
    int is_active {};
    int has_initial_health {};
    int is_starving_at_health_pct {};
    int is_hungry_at_health_pct {};
    int has_hunger_tick_every_rounds {};
    int scent_distance {};
    int is_ripple {};
    int is_light_strength {};
    int is_dirt {};
    int is_blood {};
    int is_animated_can_vflip {};
    int is_blit_y_offset {};
    int is_small_shadow_caster {};
    int is_corridor {};
    int is_blitted_as_sitting_on_the_ground {};
    int is_boring {};
    int is_exit {};
    int is_entrance {};
    int is_floor_deco {};
    int is_wall_deco {};
    int move_delay_hundredths {};
    int weapon_use_delay_hundredths {};
    int for_collision_use_box {};
    int for_collision_use_circle {};
    int weapon_damage {};
    int is_projectile {};
    int is_explosion {};
    int is_combustable {};
    int is_spikes {};
    int collision_priority {};
    int weapon_use_distance {};
    int is_weapon_carry_anim {};
    int is_weapon_use_effect {};
    int is_weapon {};
    int is_outlined {};
    int is_shadow_caster {};
    int is_animated_can_hflip {};
    int is_movable {};
    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
Tpp tp_load(int id, std::string file);
void tp_update(Tpp tp);
Tpp tp_find(std::string name);
Tpp tp_find(uint32_t id);
Tpp tp_find_short_name(std::string name);
void tp_init_after_loading(void);
Tpp tp_get_random_monst(void);
Tpp tp_get_random_ripple(void);
Tpp tp_get_random_key(void);
Tpp tp_get_random_floor(void);
Tpp tp_get_random_deco(void);
Tpp tp_get_random_wall_deco(void);

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

static inline int tp_to_id (Tpp t)
{
    return (t->id);
}

static inline int tp_is_floor (Tpp t)
{
    return (t->is_floor);
}

static inline int tp_is_wall (Tpp t)
{
    return (t->is_wall);
}

static inline int tp_is_rock (Tpp t)
{
    return (t->is_rock);
}

static inline int tp_is_door (Tpp t)
{
    return (t->is_door);
}

static inline int tp_is_lava (Tpp t)
{
    return (t->is_lava);
}

static inline int tp_is_water (Tpp t)
{
    return (t->is_water);
}

static inline int tp_is_deep_water (Tpp t)
{
    return (t->is_deep_water);
}

static inline int tp_is_monst (Tpp t)
{
    return (t->is_monst);
}

static inline int tp_is_player (Tpp t)
{
    return (t->is_player);
}

static inline int tp_is_animation (Tpp t)
{
    return (t->is_animation);
}

static inline int tp_is_animated (Tpp t)
{
    return (t->is_animated);
}

static inline int tp_is_animated_no_dir (Tpp t)
{
    return (t->is_animated_no_dir);
}

static inline int tp_is_rrr1 (Tpp t)
{
    return (t->is_rrr1);
}

static inline int tp_is_rrr2 (Tpp t)
{
    return (t->is_rrr2);
}

static inline int tp_is_rrr3 (Tpp t)
{
    return (t->is_rrr3);
}

static inline int tp_is_rrr4 (Tpp t)
{
    return (t->is_rrr4);
}

static inline int tp_is_rrr5 (Tpp t)
{
    return (t->is_rrr5);
}

static inline int tp_is_rrr6 (Tpp t)
{
    return (t->is_rrr6);
}

static inline int tp_is_rrr7 (Tpp t)
{
    return (t->is_rrr7);
}

static inline int tp_is_rrr8 (Tpp t)
{
    return (t->is_rrr8);
}

static inline int tp_is_rrr9 (Tpp t)
{
    return (t->is_rrr9);
}

static inline int tp_is_rrr10 (Tpp t)
{
    return (t->is_rrr10);
}

static inline int tp_is_rrr11 (Tpp t)
{
    return (t->is_rrr11);
}

static inline int tp_is_rrr12 (Tpp t)
{
    return (t->is_rrr12);
}

static inline int tp_is_rrr13 (Tpp t)
{
    return (t->is_rrr13);
}

static inline int tp_is_rrr14 (Tpp t)
{
    return (t->is_rrr14);
}

static inline int tp_is_rrr15 (Tpp t)
{
    return (t->is_rrr15);
}

static inline int tp_is_rrr16 (Tpp t)
{
    return (t->is_rrr16);
}

static inline int tp_is_rrr17 (Tpp t)
{
    return (t->is_rrr17);
}

static inline int tp_is_rrr18 (Tpp t)
{
    return (t->is_rrr18);
}

static inline int tp_is_rrr19 (Tpp t)
{
    return (t->is_rrr19);
}

static inline int tp_is_rrr20 (Tpp t)
{
    return (t->is_rrr20);
}

static inline int tp_is_rrr21 (Tpp t)
{
    return (t->is_rrr21);
}

static inline int tp_is_rrr22 (Tpp t)
{
    return (t->is_rrr22);
}

static inline int tp_is_rrr23 (Tpp t)
{
    return (t->is_rrr23);
}

static inline int tp_is_rrr24 (Tpp t)
{
    return (t->is_rrr24);
}

static inline int tp_is_rrr25 (Tpp t)
{
    return (t->is_rrr25);
}

static inline int tp_is_rrr26 (Tpp t)
{
    return (t->is_rrr26);
}

static inline int tp_is_rrr27 (Tpp t)
{
    return (t->is_rrr27);
}

static inline int tp_is_rrr28 (Tpp t)
{
    return (t->is_rrr28);
}

static inline int tp_is_meat_eater (Tpp t)
{
    return (t->is_meat_eater);
}

static inline int tp_is_made_of_meat (Tpp t)
{
    return (t->is_made_of_meat);
}

static inline int tp_is_active (Tpp t)
{
    return (t->is_active);
}

static inline int tp_is_starving_at_health_pct (Tpp t)
{
    return (t->is_starving_at_health_pct);
}

static inline int tp_has_initial_health (Tpp t)
{
    return (t->has_initial_health);
}

static inline int tp_is_hungry_at_health_pct (Tpp t)
{
    return (t->is_hungry_at_health_pct);
}

static inline int tp_has_hunger_tick_every_rounds (Tpp t)
{
    return (t->has_hunger_tick_every_rounds);
}

static inline int tp_scent_distance (Tpp t)
{
    return (t->scent_distance);
}

static inline int tp_is_ripple (Tpp t)
{
    return (t->is_ripple);
}

static inline int tp_is_light_strength (Tpp t)
{
    return (t->is_light_strength);
}

static inline int tp_is_dirt (Tpp t)
{
    return (t->is_dirt);
}

static inline int tp_is_blood (Tpp t)
{
    return (t->is_blood);
}

static inline int tp_is_animated_can_vflip (Tpp t)
{
    return (t->is_animated_can_vflip);
}

static inline int tp_is_blit_y_offset (Tpp t)
{
    return (t->is_blit_y_offset);
}

static inline int tp_is_small_shadow_caster (Tpp t)
{
    return (t->is_small_shadow_caster);
}

static inline int tp_is_corridor (Tpp t)
{
    return (t->is_corridor);
}

static inline int tp_is_blitted_as_sitting_on_the_ground (Tpp t)
{
    return (t->is_blitted_as_sitting_on_the_ground);
}

static inline int tp_is_boring (Tpp t)
{
    return (t->is_boring);
}

static inline int tp_is_exit (Tpp t)
{
    return (t->is_exit);
}

static inline int tp_is_entrance (Tpp t)
{
    return (t->is_entrance);
}

static inline int tp_is_floor_deco (Tpp t)
{
    return (t->is_floor_deco);
}

static inline int tp_is_wall_deco (Tpp t)
{
    return (t->is_wall_deco);
}

static inline int tp_move_delay_hundredths (Tpp t)
{
    return (t->move_delay_hundredths);
}

static inline int tp_get_weapon_use_delay_hundredths (Tpp t)
{
    return (t->weapon_use_delay_hundredths);
}

static inline int tp_for_collision_use_box (Tpp t)
{
    return (t->for_collision_use_box);
}

static inline int tp_for_collision_use_circle (Tpp t)
{
    return (t->for_collision_use_circle);
}

static inline int tp_weapon_damage (Tpp t)
{
    return (t->weapon_damage);
}

static inline int tp_is_projectile (Tpp t)
{
    return (t->is_projectile);
}

static inline int tp_is_explosion (Tpp t)
{
    return (t->is_explosion);
}

static inline int tp_is_combustable (Tpp t)
{
    return (t->is_combustable);
}

static inline int tp_is_spikes (Tpp t)
{
    return (t->is_spikes);
}

static inline int tp_collision_priority (Tpp t)
{
    return (t->collision_priority);
}

static inline int tp_weapon_use_distance (Tpp t)
{
    return (t->weapon_use_distance);
}

static inline int tp_is_weapon_carry_anim (Tpp t)
{
    return (t->is_weapon_carry_anim);
}

static inline int tp_is_weapon_use_effect (Tpp t)
{
    return (t->is_weapon_use_effect);
}

static inline int tp_is_weapon (Tpp t)
{
    return (t->is_weapon);
}

static inline int tp_is_outlined (Tpp t)
{
    return (t->is_outlined);
}

static inline int tp_is_shadow_caster (Tpp t)
{
    return (t->is_shadow_caster);
}

static inline int tp_is_animated_can_hflip (Tpp t)
{
    return (t->is_animated_can_hflip);
}

static inline int tp_z_depth (Tpp t)
{
    return (t->z_depth);
}

static inline int tp_is_movable (Tpp t)
{
    return (t->is_movable);
}

static inline int tp_is_movement_blocking (Tpp t)
{
    return (t->is_movement_blocking);
}

static inline int tp_is_key (Tpp t)
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

static inline std::string tp_str_light_color (Tpp t)
{
    return (t->str_light_color);
}

static inline std::string tp_weapon_carry_anim (Tpp t)
{
    return (t->weapon_carry_anim);
}

static inline std::string tp_weapon_use_anim (Tpp t)
{
    return (t->weapon_use_anim);
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
