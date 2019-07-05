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

//
// Use map as walk order is maintained, instead of unordered map where it is
// not. Think of unordered_map as a hash table.
//
typedef std::vector< Tpp > Tpmap_create_order;

#include "my_tile_info.h"
#include "my_dice.h"

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

    std::string name;
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

    int ai_delay_after_moving_ms {};
    int ai_scent_distance {};
    int collision_box {};
    int collision_circle {};
    int collision_hit_priority {};
    double collision_radius {};
    int gfx_animated {};
    int gfx_animated_can_vflip {};
    int gfx_animated_no_dir {};
    int gfx_bounce_on_move {};
    int gfx_can_hflip {};
    int gfx_is_an_animation_only {};
    int gfx_is_floor_deco {};
    int gfx_is_wall_deco {};
    int gfx_is_weapon_carry_anim {};
    int gfx_is_weapon_use_anim {};
    int gfx_large_shadow_caster {};
    int gfx_outlined {};
    int gfx_oversized_but_sitting_on_the_ground {};
    int gfx_small_shadow_caster {};
    int hunger_at_health_pct {};
    int hunger_clock_freq_ms {};
    int hunger_initial_health_at {};
    int hunger_starving_at_health_pct {};
    int internal_has_dir_anim {};
    int internal_has_hp_anim {};
    int is_active {};
    int is_bleeder {};
    int is_blood {};
    int does_nothing {};
    int is_combustable {};
    int is_corpse_on_death {};
    int is_corridor {};
    int is_deep_water {};
    int is_dirt {};
    int is_grass {};
    int is_door {};
    int is_entrance {};
    int is_exit {};
    int is_explosion {};
    int is_floor {};
    int is_key {};
    int is_lava {};
    int is_light_strength {};
    int is_made_of_meat {};
    int is_meat_eater {};
    int is_monst {};
    int is_movable {};
    int is_movement_blocking {};
    int is_player {};
    int is_projectile {};
    int is_ripple {};
    int is_rrr1 {};
    int is_rrr10 {};
    int is_attackable {};
    int is_food {};
    int hates_water {};
    int hunger_constant {};
    int is_undead {};
    int is_rock {};
    std::string nutrition_hd {};
    Dice nutrition;
    std::string bite_damage_hd {};
    Dice bite_damage;
    int is_rrr2 {};
    int collision_check {};
    int attack_on_collision {};
    int is_water_dweller {};
    int is_rrr3 {};
    int is_rrr4 {};
    int is_rrr5 {};
    int is_rrr6 {};
    int is_rrr7 {};
    int is_rrr8 {};
    int is_obstacle {};
    int is_wall {};
    int is_water {};
    int is_weapon {};
    int move_speed_ms {};
    int weapon_damage {};
    int weapon_use_delay_hundredths {};
    int weapon_use_distance {};

    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
Tpp tp_load(int id, std::string file);
void tp_update(Tpp tp);
Tpp tp_find(uint32_t id);
Tpp tp_find_name(std::string name);
void tp_init_after_loading(void);
Tpp tp_random_monst(void);
Tpp tp_random_food(void);
Tpp tp_random_dirt(void);
Tpp tp_random_grass(void);
Tpp tp_random_ripple(void);
Tpp tp_random_key(void);
Tpp tp_random_blood(void);
Tpp tp_random_wall(void);
Tpp tp_random_floor(void);
Tpp tp_random_deco(void);
Tpp tp_random_wall_deco(void);

static inline int32_t tp_blit_top_off (Tpp &t)
{
    return (t->blit_top_off);
}

static inline int32_t tp_blit_bot_off (Tpp &t)
{
    return (t->blit_bot_off);
}

static inline int32_t tp_blit_left_off (Tpp &t)
{
    return (t->blit_left_off);
}

static inline int32_t tp_blit_right_off (Tpp &t)
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

static inline int tp_is_food (Tpp t)
{
    return (t->is_food);
}

static inline int tp_is_player (Tpp t)
{
    return (t->is_player);
}

static inline int tp_gfx_is_an_animation_only (Tpp t)
{
    return (t->gfx_is_an_animation_only);
}

static inline int tp_gfx_animated (Tpp t)
{
    return (t->gfx_animated);
}

static inline int tp_gfx_animated_no_dir (Tpp t)
{
    return (t->gfx_animated_no_dir);
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

static inline int tp_is_obstacle (Tpp t)
{
    return (t->is_obstacle);
}

static inline int tp_is_rrr10 (Tpp t)
{
    return (t->is_rrr10);
}

static inline int tp_is_attackable (Tpp t)
{
    return (t->is_attackable);
}

static inline int tp_hates_water (Tpp t)
{
    return (t->hates_water);
}

static inline int tp_hunger_constant (Tpp t)
{
    return (t->hunger_constant);
}

static inline int tp_is_undead (Tpp t)
{
    return (t->is_undead);
}

static inline int tp_is_rock (Tpp t)
{
    return (t->is_rock);
}

static inline std::string tp_nutrition_hd (Tpp t)
{
    return (t->nutrition_hd);
}

static inline std::string tp_bite_damage_hd (Tpp t)
{
    return (t->bite_damage_hd);
}

static inline int tp_collision_check (Tpp t)
{
    return (t->collision_check);
}

static inline int tp_attack_on_collision (Tpp t)
{
    return (t->attack_on_collision);
}

static inline int tp_is_water_dweller (Tpp t)
{
    return (t->is_water_dweller);
}

static inline int tp_collision_hit_priority (Tpp t)
{
    return (t->collision_hit_priority);
}

static inline double tp_collision_radius (Tpp t)
{
    return (t->collision_radius);
}

static inline int tp_ai_delay_after_moving_ms (Tpp t)
{
    return (t->ai_delay_after_moving_ms);
}

static inline int tp_gfx_bounce_on_move (Tpp t)
{
    return (t->gfx_bounce_on_move);
}

static inline int tp_is_corpse_on_death (Tpp t)
{
    return (t->is_corpse_on_death);
}

static inline int tp_is_bleeder (Tpp t)
{
    return (t->is_bleeder);
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

static inline int tp_hunger_starving_at_health_pct (Tpp t)
{
    return (t->hunger_starving_at_health_pct);
}

static inline int tp_hunger_initial_health_at (Tpp t)
{
    return (t->hunger_initial_health_at);
}

static inline int tp_hunger_at_health_pct (Tpp t)
{
    return (t->hunger_at_health_pct);
}

static inline int tp_hunger_clock_freq_ms (Tpp t)
{
    return (t->hunger_clock_freq_ms);
}

static inline int tp_ai_scent_distance (Tpp t)
{
    return (t->ai_scent_distance);
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

static inline int tp_is_grass (Tpp t)
{
    return (t->is_grass);
}

static inline int tp_is_blood (Tpp t)
{
    return (t->is_blood);
}

static inline int tp_gfx_animated_can_vflip (Tpp t)
{
    return (t->gfx_animated_can_vflip);
}

static inline int tp_gfx_small_shadow_caster (Tpp t)
{
    return (t->gfx_small_shadow_caster);
}

static inline int tp_is_corridor (Tpp t)
{
    return (t->is_corridor);
}

static inline int tp_gfx_oversized_but_sitting_on_the_ground (Tpp t)
{
    return (t->gfx_oversized_but_sitting_on_the_ground);
}

static inline int tp_does_nothing (Tpp t)
{
    return (t->does_nothing);
}

static inline int tp_is_exit (Tpp t)
{
    return (t->is_exit);
}

static inline int tp_is_entrance (Tpp t)
{
    return (t->is_entrance);
}

static inline int tp_gfx_is_floor_deco (Tpp t)
{
    return (t->gfx_is_floor_deco);
}

static inline int tp_gfx_is_wall_deco (Tpp t)
{
    return (t->gfx_is_wall_deco);
}

static inline int tp_move_speed_ms (Tpp t)
{
    return (t->move_speed_ms);
}

static inline int tp_weapon_use_delay_hundredths (Tpp t)
{
    return (t->weapon_use_delay_hundredths);
}

static inline int tp_collision_box (Tpp t)
{
    return (t->collision_box);
}

static inline int tp_collision_circle (Tpp t)
{
    return (t->collision_circle);
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

static inline int tp_weapon_use_distance (Tpp t)
{
    return (t->weapon_use_distance);
}

static inline int tp_gfx_is_weapon_carry_anim (Tpp t)
{
    return (t->gfx_is_weapon_carry_anim);
}

static inline int tp_gfx_is_weapon_use_anim (Tpp t)
{
    return (t->gfx_is_weapon_use_anim);
}

static inline int tp_is_weapon (Tpp t)
{
    return (t->is_weapon);
}

static inline int tp_gfx_outlined (Tpp t)
{
    return (t->gfx_outlined);
}

static inline int tp_gfx_large_shadow_caster (Tpp t)
{
    return (t->gfx_large_shadow_caster);
}

static inline int tp_gfx_can_hflip (Tpp t)
{
    return (t->gfx_can_hflip);
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
    return (t->name);
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

static inline Tileinfomap *tp_tiles (Tpp t)
{
    return (&t->tiles);
}

static inline Tileinfomap *tp_left_tiles (Tpp t)
{
    return (&t->left_tiles);
}

static inline Tileinfomap *tp_right_tiles (Tpp t)
{
    return (&t->right_tiles);
}

static inline Tileinfomap *tp_top_tiles (Tpp t)
{
    return (&t->top_tiles);
}

static inline Tileinfomap *tp_bot_tiles (Tpp t)
{
    return (&t->bot_tiles);
}

static inline Tileinfomap *tp_tl_tiles (Tpp t)
{
    return (&t->tl_tiles);
}

static inline Tileinfomap *tp_tr_tiles (Tpp t)
{
    return (&t->tr_tiles);
}

static inline Tileinfomap *tp_bl_tiles (Tpp t)
{
    return (&t->bl_tiles);
}

static inline Tileinfomap *tp_br_tiles (Tpp t)
{
    return (&t->br_tiles);
}

static inline Tileinfomap *tp_horiz_tiles (Tpp t)
{
    return (&t->horiz_tiles);
}

static inline Tileinfomap *tp_vert_tiles (Tpp t)
{
    return (&t->vert_tiles);
}

static inline Tileinfomap *tp_l90_tiles (Tpp t)
{
    return (&t->l90_tiles);
}

static inline Tileinfomap *tp_l180_tiles (Tpp t)
{
    return (&t->l180_tiles);
}

static inline Tileinfomap *tp_l_tiles (Tpp t)
{
    return (&t->l_tiles);
}

static inline Tileinfomap *tp_l270_tiles (Tpp t)
{
    return (&t->l270_tiles);
}

static inline Tileinfomap *tp_t_tiles (Tpp t)
{
    return (&t->t_tiles);
}

static inline Tileinfomap *tp_t90_tiles (Tpp t)
{
    return (&t->t90_tiles);
}

static inline Tileinfomap *tp_t180_tiles (Tpp t)
{
    return (&t->t180_tiles);
}

static inline Tileinfomap *tp_t270_tiles (Tpp t)
{
    return (&t->t270_tiles);
}

static inline Tileinfomap *tp_x_tiles (Tpp t)
{
    return (&t->x_tiles);
}

Tilep tp_first_tile(Tpp tp);

Tpp string2tp(const char **s);
Tpp string2tp(std::string &s, int *len);
Tpp string2tp(std::wstring &s, int *len);

extern Tpmap tp_map;

//
// Find an existing thing.
//
static inline Tpp tp_find (std::string name)
{_
    auto result = tp_map.find(name);

    if (result == tp_map.end()) {
        return (0);
    }

    return (result->second);
}

#endif /* THING_TEMPLATE_H */
