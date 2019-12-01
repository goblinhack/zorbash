//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

#include <unordered_map>
#include <memory>

typedef class Tp* Tpp;

typedef std::vector< Tpp > Tpidmap;
typedef std::unordered_map< std::string, Tpp > Tpnamemap;

extern Tpidmap tp_id_map;
extern Tpnamemap tp_name_map;

#include "my_dice.h"
#include "my_tile.h"
#include "my_size.h"

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

    uint16_t id {};

    fsize sz;

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

    //
    // Animation tiles.
    //
    Tilemap tiles;

    //
    // Adjacent tiles.
    //
    Tilemap tile_tops;
    Tilemap tile_bots;
    Tilemap tile_lefts;
    Tilemap tile_rights;
    Tilemap tile_tls;
    Tilemap tile_trs;
    Tilemap tile_bls;
    Tilemap tile_brs;

    //
    // Join tiles
    //
    Tilemap horiz_tiles;
    Tilemap vert_tiles;
    Tilemap l90_tiles;
    Tilemap l180_tiles;
    Tilemap l_tiles;
    Tilemap l270_tiles;
    Tilemap t_tiles;
    Tilemap t90_tiles;
    Tilemap t180_tiles;
    Tilemap t270_tiles;
    Tilemap x_tiles;

    int blit_off {};
    int blit_top_off {};
    int blit_bot_off {};
    int blit_left_off {};
    int blit_right_off {};

    Dice bite_damage;
    Dice is_nutrition;
    double collision_radius {};
    int ai_delay_after_moving_ms {};
    int ai_scent_distance {};
    int collision_attack {};
    int collision_box {};
    int collision_check {};
    int collision_circle {};
    int collision_hit_priority {};
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
    int hunger_constant {};
    int hunger_initial_health_at {};
    int hunger_starving_at_health_pct {};
    int internal_has_dir_anim {};
    int internal_has_hp_anim {};
    int is_active {}; // e.g. a monst or player or something movable
    int is_attackable {};
    int is_bleeder {};
    int is_blood {};
    int is_combustable {};
    int is_corpse_on_death {};
    int is_corridor {};
    int is_deep_water {};
    int is_dirt {};
    int is_door {};
    int is_entrance {};
    int is_exit {};
    int is_explosion {};
    int is_floor {};
    int is_food {};
    int is_interesting {}; // e.g. something edible or a monst or lava
    int is_key {};
    int is_lava {};
    int is_light_strength {};
    int is_made_of_meat {};
    int is_meat_eater {};
    int is_monst {};
    int is_movable {};
    int is_movement_blocking {};
    int is_obstacle {};
    int is_player {};
    int is_projectile {};
    int is_ripple {};
    int is_rock {};
    int is_rrr1 {};
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
    int is_rrr2 {};
    int is_rrr20 {};
    int is_rrr21 {};
    int is_rrr22 {};
    int is_rrr23 {};
    int is_rrr24 {};
    int is_rrr25 {};
    int is_rrr26 {};
    int is_loggable {};
    int is_rrr28 {};
    int is_rrr29 {};
    int is_rrr3 {};
    int is_rrr30 {};
    int is_rrr31 {};
    int is_rrr32 {};
    int is_rrr33 {};
    int is_rrr34 {};
    int is_rrr35 {};
    int is_rrr36 {};
    int is_rrr37 {};
    int is_rrr38 {};
    int is_rrr39 {};
    int is_rrr4 {};
    int is_rrr41 {};
    int is_rrr42 {};
    int is_rrr43 {};
    int is_rrr44 {};
    int is_rrr45 {};
    int is_rrr46 {};
    int is_rrr47 {};
    int is_cursor_hover {};
    int is_cursor {};
    int is_rrr5 {};
    int gfx_dead_anim {};
    int is_rrr6 {};
    int is_rrr7 {};
    int is_rrr8 {};
    int is_rrr9 {};
    int is_undead {};
    int is_wall {};
    int is_water {};
    int is_water_dweller {};
    int is_water_hater {};
    int is_weapon {};
    int move_speed_ms {};
    int weapon_damage {};
    int weapon_use_delay_hundredths {};
    int weapon_use_distance {};
    std::string bite_damage_hd {};
    std::string is_nutrition_hd {};

    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
Tpp tp_load(int id, std::string file);
void tp_update(Tpp tp);
Tpp tp_find(uint32_t id);
void tp_init_after_loading(void);
Tpp tp_random_monst(void);
Tpp tp_random_food(void);
Tpp tp_random_dirt(void);
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

static inline int tp_is_loggable (Tpp t)
{
    return (t->is_loggable);
}

static inline int tp_is_rrr28 (Tpp t)
{
    return (t->is_rrr28);
}

static inline int tp_is_rrr29 (Tpp t)
{
    return (t->is_rrr29);
}

static inline int tp_is_rrr30 (Tpp t)
{
    return (t->is_rrr30);
}

static inline int tp_is_rrr31 (Tpp t)
{
    return (t->is_rrr31);
}

static inline int tp_is_rrr32 (Tpp t)
{
    return (t->is_rrr32);
}

static inline int tp_is_rrr33 (Tpp t)
{
    return (t->is_rrr33);
}

static inline int tp_is_rrr34 (Tpp t)
{
    return (t->is_rrr34);
}

static inline int tp_is_rrr35 (Tpp t)
{
    return (t->is_rrr35);
}

static inline int tp_is_rrr36 (Tpp t)
{
    return (t->is_rrr36);
}

static inline int tp_is_rrr37 (Tpp t)
{
    return (t->is_rrr37);
}

static inline int tp_is_rrr38 (Tpp t)
{
    return (t->is_rrr38);
}

static inline int tp_is_rrr39 (Tpp t)
{
    return (t->is_rrr39);
}

static inline int tp_is_bleeder (Tpp t)
{
    return (t->is_bleeder);
}

static inline int tp_is_rrr41 (Tpp t)
{
    return (t->is_rrr41);
}

static inline int tp_is_rrr42 (Tpp t)
{
    return (t->is_rrr42);
}

static inline int tp_is_rrr43 (Tpp t)
{
    return (t->is_rrr43);
}

static inline int tp_is_rrr44 (Tpp t)
{
    return (t->is_rrr44);
}

static inline int tp_is_rrr45 (Tpp t)
{
    return (t->is_rrr45);
}

static inline int tp_is_rrr46 (Tpp t)
{
    return (t->is_rrr46);
}

static inline int tp_is_rrr47 (Tpp t)
{
    return (t->is_rrr47);
}

static inline int tp_is_cursor_hover (Tpp t)
{
    return (t->is_cursor_hover);
}

static inline int tp_is_cursor (Tpp t)
{
    return (t->is_cursor);
}

static inline int tp_gfx_dead_anim (Tpp t)
{
    return (t->gfx_dead_anim);
}

static inline int tp_is_obstacle (Tpp t)
{
    return (t->is_obstacle);
}

static inline int tp_is_attackable (Tpp t)
{
    return (t->is_attackable);
}

static inline int tp_is_water_hater (Tpp t)
{
    return (t->is_water_hater);
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

static inline std::string tp_is_nutrition_hd (Tpp t)
{
    return (t->is_nutrition_hd);
}

static inline std::string tp_bite_damage_hd (Tpp t)
{
    return (t->bite_damage_hd);
}

static inline int tp_collision_check (Tpp t)
{
    return (t->collision_check);
}

static inline int tp_collision_attack (Tpp t)
{
    return (t->collision_attack);
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

static inline int tp_is_interesting (Tpp t)
{
    return (t->is_interesting);
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

static inline Tilemap *tp_tiles (Tpp t)
{
    return (&t->tiles);
}

static inline Tilemap *tp_tile_lefts (Tpp t)
{
    return (&t->tile_lefts);
}

static inline Tilemap *tp_tile_rights (Tpp t)
{
    return (&t->tile_rights);
}

static inline Tilemap *tp_tile_tops (Tpp t)
{
    return (&t->tile_tops);
}

static inline Tilemap *tp_tile_bots (Tpp t)
{
    return (&t->tile_bots);
}

static inline Tilemap *tp_tile_tls (Tpp t)
{
    return (&t->tile_tls);
}

static inline Tilemap *tp_tile_trs (Tpp t)
{
    return (&t->tile_trs);
}

static inline Tilemap *tp_tile_bls (Tpp t)
{
    return (&t->tile_bls);
}

static inline Tilemap *tp_tile_brs (Tpp t)
{
    return (&t->tile_brs);
}

static inline Tilemap *tp_horiz_tiles (Tpp t)
{
    return (&t->horiz_tiles);
}

static inline Tilemap *tp_vert_tiles (Tpp t)
{
    return (&t->vert_tiles);
}

static inline Tilemap *tp_l90_tiles (Tpp t)
{
    return (&t->l90_tiles);
}

static inline Tilemap *tp_l180_tiles (Tpp t)
{
    return (&t->l180_tiles);
}

static inline Tilemap *tp_l_tiles (Tpp t)
{
    return (&t->l_tiles);
}

static inline Tilemap *tp_l270_tiles (Tpp t)
{
    return (&t->l270_tiles);
}

static inline Tilemap *tp_t_tiles (Tpp t)
{
    return (&t->t_tiles);
}

static inline Tilemap *tp_t90_tiles (Tpp t)
{
    return (&t->t90_tiles);
}

static inline Tilemap *tp_t180_tiles (Tpp t)
{
    return (&t->t180_tiles);
}

static inline Tilemap *tp_t270_tiles (Tpp t)
{
    return (&t->t270_tiles);
}

static inline Tilemap *tp_x_tiles (Tpp t)
{
    return (&t->x_tiles);
}

Tilep tp_first_tile(Tpp tp);

Tpp string2tp(const char **s);
Tpp string2tp(std::string &s, int *len);
Tpp string2tp(std::wstring &s, int *len);

//
// Find an existing thing.
//
static inline Tpp tp_find (std::string name)
{_
    auto result = tp_name_map.find(name);

    if (unlikely(result == tp_name_map.end())) {
        return (0);
    }

    return (result->second);
}

#endif // THING_TEMPLATE_H 
