//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_THING_TEMPLATE_H
#define _MY_THING_TEMPLATE_H

#include <unordered_map>
#include <memory>

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
    std::string real_name;
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
    std::string a_or_an;
    std::string light_color;
    std::string weapon_carry_anim;
    std::string weapon_use_anim;

    //
    // Animation tiles.
    //
    Tilemap tiles;

    //
    // Adjacent tiles.
    //
    Tilemap top1_tiles;
    Tilemap bot1_tiles;
    Tilemap left1_tiles;
    Tilemap right1_tiles;
    Tilemap tl1_tiles;
    Tilemap tr1_tiles;
    Tilemap bl1_tiles;
    Tilemap br1_tiles;

    //
    // Lower level adjacent tiles (for shadows)
    //
    Tilemap top2_tiles;
    Tilemap bot2_tiles;
    Tilemap left2_tiles;
    Tilemap right2_tiles;
    Tilemap tl2_tiles;
    Tilemap tr2_tiles;
    Tilemap bl2_tiles;
    Tilemap br2_tiles;

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

    //
    // For water ripples
    //
    Tilemap outline_tiles;

    int blit_off {};
    int blit_top_off {};
    int blit_bot_off {};
    int blit_left_off {};
    int blit_right_off {};

    Dice attack_damage;
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
    int gfx_animated_can_hflip {};
    int gfx_dead_anim {};
    int gfx_is_an_animation_only {};
    int is_floor_deco {};
    int is_wall_deco {};
    int gfx_is_weapon_carry_anim {};
    int gfx_is_attack_anim {};
    int gfx_large_shadow {};
    int gfx_oversized_but_sitting_on_the_ground {};
    int gfx_show_outlined {};
    int gfx_small_shadow_caster {};
    int hunger_clock_freq_ms {};
    int internal_has_dir_anim {};
    int internal_has_hp_anim {};
    int is_active {}; // e.g. a monst or player or something movable
    int is_attackable {};
    int is_bleeder {};
    int is_blood {};
    int is_corpse_on_death {};
    int is_corridor {};
    int is_cursor {};
    int is_cursor_can_hover_over {};
    int is_deep_water {};
    int is_dirt {};
    int is_door {};
    int is_entrance {};
    int is_exit {};
    int is_explosion {};
    int is_floor {};
    int is_food {};
    int is_hunger_insatiable {};
    int is_interesting {}; // e.g. something edible or a monst or lava
    int is_key {};
    int is_lava {};
    int is_chasm {};
    int is_light_strength {};
    int is_loggable {};
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
    int is_rrr28 {};
    int is_rrr29 {};
    int is_rrr3 {};
    int is_rrr30 {};
    int is_rrr31 {};
    int is_combustible {};
    int gfx_is_on_fire_anim {};
    int is_attack_shove_chance_d1000 {};
    int is_hazard {};
    int is_attack_shove {};
    int is_shovable {};
    int is_cursor_path {};
    int is_rrr4 {};
    int is_blood_splatter {};
    int is_no_tile {};
    int is_msg {};
    int is_attack_lunge {};
    int is_rrr5 {};
    int is_rrr6 {};
    int is_rrr7 {};
    int is_rrr8 {};
    int is_rrr9 {};
    int is_secret_door {};
    int is_undead {};
    int is_wall {};
    int is_water {};
    int is_water_dweller {};
    int is_water_hater {};
    int is_weapon {};
    int stats01 {};
    int stats02 {};
    int stats03 {};
    int stats04 {};
    int stats05 {};
    int stats06 {};
    int stats07 {};
    int stats08 {};
    int stats09 {};
    int stats10 {};
    int stats11 {};
    int stats12 {};
    int stats13 {};
    int stats14 {};
    int stats15 {};
    int stats16 {};
    int stats17 {};
    int stats18 {};
    int stats19 {};
    int stats_strength {};
    int stats_attack {};
    int stats_attack_rate_tenths {};
    int lifespan_count {};
    int stats_defence {};
    int stats_health_hunger_pct {};
    int stats_health_initial {};
    int stats_health_starving_pct {};
    int stats_move_speed_ms {};
    int weapon_damage {};
    int weapon_use_delay_hundredths {};
    int weapon_use_distance {};
    std::string stats_attack_hd {};
    std::string is_nutrition_hd {};

    uint8_t z_depth {};
};

uint8_t tp_init(void);
void tp_fini(void);
Tpp tp_load(int id, std::string const& file, std::string const& real_name);
void tp_update(Tpp tp);
Tpp tp_find(uint32_t id);
void tp_init_after_loading(void);
Tpp tp_random_monst(void);
Tpp tp_random_food(void);
Tpp tp_random_dirt(void);
Tpp tp_random_ripple(void);
Tpp tp_random_blood_splatter(void);
Tpp tp_random_key(void);
Tpp tp_random_blood(void);
Tpp tp_random_wall(void);
Tpp tp_random_rock(void);
Tpp tp_random_floor(void);
Tpp tp_random_deco(void);
Tpp tp_random_wall_deco(void);

static inline int32_t tp_blit_top_off (Tpp &t)
{_
    return (t->blit_top_off);
}

static inline int32_t tp_blit_bot_off (Tpp &t)
{_
    return (t->blit_bot_off);
}

static inline int32_t tp_blit_left_off (Tpp &t)
{_
    return (t->blit_left_off);
}

static inline int32_t tp_blit_right_off (Tpp &t)
{_
    return (t->blit_right_off);
}

static inline int tp_to_id (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return -1; }
    return (t->id);
}

static inline int tp_is_floor (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_floor);
}

static inline int tp_is_wall (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_wall);
}

static inline int tp_is_door (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_door);
}

static inline int tp_is_lava (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_lava);
}

static inline int tp_is_chasm (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_chasm);
}

static inline int tp_is_water (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_water);
}

static inline int tp_is_deep_water (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_deep_water);
}

static inline int tp_is_monst (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_monst);
}

static inline int tp_is_food (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_food);
}

static inline int tp_is_player (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_player);
}

static inline int tp_gfx_is_an_animation_only (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_is_an_animation_only);
}

static inline int tp_gfx_animated (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_animated);
}

static inline int tp_gfx_animated_no_dir (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_animated_no_dir);
}

static inline int tp_is_rrr1 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr1);
}

static inline int tp_is_rrr2 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr2);
}

static inline int tp_is_rrr3 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr3);
}

static inline int tp_is_rrr4 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr4);
}

static inline int tp_is_rrr5 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr5);
}

static inline int tp_is_rrr6 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr6);
}

static inline int tp_is_rrr7 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr7);
}

static inline int tp_is_rrr8 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr8);
}

static inline int tp_is_rrr9 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr9);
}

static inline int tp_is_rrr10 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr10);
}

static inline int tp_is_rrr11 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr11);
}

static inline int tp_is_rrr12 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr12);
}

static inline int tp_is_rrr13 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr13);
}

static inline int tp_is_rrr14 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr14);
}

static inline int tp_is_rrr15 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr15);
}

static inline int tp_is_rrr16 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr16);
}

static inline int tp_is_rrr17 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr17);
}

static inline int tp_is_rrr18 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr18);
}

static inline int tp_is_rrr19 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr19);
}

static inline int tp_is_rrr20 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr20);
}

static inline int tp_is_rrr21 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr21);
}

static inline int tp_is_rrr22 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr22);
}

static inline int tp_is_rrr23 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr23);
}

static inline int tp_is_rrr24 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr24);
}

static inline int tp_is_rrr25 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr25);
}

static inline int tp_is_rrr26 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr26);
}

static inline int tp_is_loggable (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_loggable);
}

static inline int tp_is_rrr28 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr28);
}

static inline int tp_is_rrr29 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr29);
}

static inline int tp_is_rrr30 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr30);
}

static inline int tp_is_rrr31 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rrr31);
}

static inline int tp_is_combustible (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_combustible);
}

static inline int tp_gfx_is_attack_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_is_attack_anim);
}

static inline int tp_is_attack_shove_chance_d1000 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_attack_shove_chance_d1000);
}

static inline int tp_is_hazard (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_hazard);
}

static inline int tp_is_attack_shove (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_attack_shove);
}

static inline int tp_is_shovable (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_shovable);
}

static inline int tp_is_cursor_path (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_cursor_path);
}

static inline int tp_is_bleeder (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_bleeder);
}

static inline int tp_is_blood_splatter (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_blood_splatter);
}

static inline int tp_is_no_tile (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_no_tile);
}

static inline int tp_is_msg (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_msg);
}

static inline int tp_is_attack_lunge (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_attack_lunge);
}

static inline int tp_stats_defence (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats_defence);
}

static inline int tp_stats_attack (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats_attack);
}

static inline int tp_stats_attack_rate_tenths (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats_attack_rate_tenths);
}

static inline int tp_lifespan_count (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->lifespan_count);
}

static inline int tp_stats01 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats01);
}

static inline int tp_stats02 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats02);
}

static inline int tp_stats03 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats03);
}

static inline int tp_stats04 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats04);
}

static inline int tp_stats05 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats05);
}

static inline int tp_stats06 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats06);
}

static inline int tp_stats07 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats07);
}

static inline int tp_stats08 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats08);
}

static inline int tp_stats09 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats09);
}

static inline int tp_stats10 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats10);
}

static inline int tp_stats11 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats11);
}

static inline int tp_stats12 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats12);
}

static inline int tp_stats13 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats13);
}

static inline int tp_stats14 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats14);
}

static inline int tp_stats15 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats15);
}

static inline int tp_stats16 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats16);
}

static inline int tp_stats17 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats17);
}

static inline int tp_stats18 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats18);
}

static inline int tp_stats19 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats19);
}

static inline int tp_stats_strength (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->stats_strength);
}

static inline int tp_is_secret_door (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_secret_door);
}

static inline int tp_is_cursor_can_hover_over (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_cursor_can_hover_over);
}

static inline int tp_is_cursor (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_cursor);
}

static inline int tp_gfx_dead_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return 0; }
    return (t->gfx_dead_anim);
}

static inline int tp_is_obstacle (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_obstacle);
}

static inline int tp_is_attackable (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_attackable);
}

static inline int tp_is_water_hater (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_water_hater);
}

static inline int tp_is_hunger_insatiable (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_hunger_insatiable);
}

static inline int tp_is_undead (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_undead);
}

static inline int tp_is_rock (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_rock);
}

static inline std::string tp_is_nutrition_hd (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->is_nutrition_hd);
}

static inline std::string tp_stats_attack_hd (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->stats_attack_hd);
}

static inline int tp_collision_check (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_check);
}

static inline int tp_collision_attack (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_attack);
}

static inline int tp_is_water_dweller (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_water_dweller);
}

static inline int tp_collision_hit_priority (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_hit_priority);
}

static inline double tp_collision_radius (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_radius);
}

static inline int tp_ai_delay_after_moving_ms (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->ai_delay_after_moving_ms);
}

static inline int tp_gfx_bounce_on_move (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_bounce_on_move);
}

static inline int tp_is_corpse_on_death (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_corpse_on_death);
}

static inline int tp_is_meat_eater (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_meat_eater);
}

static inline int tp_is_made_of_meat (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_made_of_meat);
}

static inline int tp_is_active (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_active);
}

static inline int tp_stats_health_starving_pct (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->stats_health_starving_pct);
}

static inline int tp_stats_health_initial (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->stats_health_initial);
}

static inline int tp_stats_health_hunger_pct (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->stats_health_hunger_pct);
}

static inline int tp_hunger_clock_freq_ms (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->hunger_clock_freq_ms);
}

static inline int tp_ai_scent_distance (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->ai_scent_distance);
}

static inline int tp_is_ripple (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_ripple);
}

static inline int tp_is_light_strength (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_light_strength);
}

static inline int tp_is_dirt (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_dirt);
}

static inline int tp_is_blood (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_blood);
}

static inline int tp_gfx_animated_can_vflip (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_animated_can_vflip);
}

static inline int tp_gfx_small_shadow_caster (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_small_shadow_caster);
}

static inline int tp_is_corridor (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_corridor);
}

static inline int tp_gfx_oversized_but_sitting_on_the_ground (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_oversized_but_sitting_on_the_ground);
}

static inline int tp_is_interesting (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_interesting);
}

static inline int tp_is_exit (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_exit);
}

static inline int tp_is_entrance (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_entrance);
}

static inline int tp_is_floor_deco (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_floor_deco);
}

static inline int tp_is_wall_deco (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_wall_deco);
}

static inline int tp_stats_move_speed_ms (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->stats_move_speed_ms);
}

static inline int tp_weapon_use_delay_hundredths (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->weapon_use_delay_hundredths);
}

static inline int tp_collision_box (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_box);
}

static inline int tp_collision_circle (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->collision_circle);
}

static inline int tp_weapon_damage (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->weapon_damage);
}

static inline int tp_is_projectile (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_projectile);
}

static inline int tp_is_explosion (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_explosion);
}

static inline int tp_weapon_use_distance (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->weapon_use_distance);
}

static inline int tp_gfx_is_weapon_carry_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_is_weapon_carry_anim);
}

static inline int tp_gfx_is_on_fire_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_is_on_fire_anim);
}

static inline int tp_is_weapon (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_weapon);
}

static inline int tp_gfx_show_outlined (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_show_outlined);
}

static inline int tp_gfx_large_shadow (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_large_shadow);
}

static inline int tp_gfx_animated_can_hflip (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->gfx_animated_can_hflip);
}

static inline int tp_z_depth (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->z_depth);
}

static inline int tp_is_movable (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_movable);
}

static inline int tp_is_movement_blocking (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_movement_blocking);
}

static inline int tp_is_key (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return false; }
    return (t->is_key);
}

static inline std::string tp_name (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return "<no tp>"; }
    return (t->name);
}

static inline std::string tp_str_zzz1 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz1);
}

static inline std::string tp_str_zzz2 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz2);
}

static inline std::string tp_str_zzz3 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz3);
}

static inline std::string tp_str_zzz4 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz4);
}

static inline std::string tp_str_zzz5 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz5);
}

static inline std::string tp_str_zzz6 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz6);
}

static inline std::string tp_str_zzz7 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz7);
}

static inline std::string tp_str_zzz8 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz8);
}

static inline std::string tp_str_zzz9 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz9);
}

static inline std::string tp_str_zzz10 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz10);
}

static inline std::string tp_str_zzz11 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz11);
}

static inline std::string tp_str_zzz12 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz12);
}

static inline std::string tp_str_zzz13 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz13);
}

static inline std::string tp_str_zzz14 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz14);
}

static inline std::string tp_str_zzz15 (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->str_zzz15);
}

static inline std::string tp_a_or_an (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->a_or_an);
}

static inline std::string tp_real_name (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->real_name);
}

static inline std::string tp_light_color (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->light_color);
}

static inline std::string tp_weapon_carry_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->weapon_carry_anim);
}

static inline std::string tp_weapon_use_anim (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return ""; }
    return (t->weapon_use_anim);
}

static inline Tilemap *tp_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->tiles);
}

static inline Tilemap *tp_left1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->left1_tiles);
}

static inline Tilemap *tp_right1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->right1_tiles);
}

static inline Tilemap *tp_top1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->top1_tiles);
}

static inline Tilemap *tp_bot1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->bot1_tiles);
}

static inline Tilemap *tp_tl1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->tl1_tiles);
}

static inline Tilemap *tp_tr1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->tr1_tiles);
}

static inline Tilemap *tp_bl1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->bl1_tiles);
}

static inline Tilemap *tp_br1_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->br1_tiles);
}

static inline Tilemap *tp_left2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->left2_tiles);
}

static inline Tilemap *tp_right2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->right2_tiles);
}

static inline Tilemap *tp_top2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->top2_tiles);
}

static inline Tilemap *tp_bot2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->bot2_tiles);
}

static inline Tilemap *tp_tl2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->tl2_tiles);
}

static inline Tilemap *tp_tr2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->tr2_tiles);
}

static inline Tilemap *tp_bl2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->bl2_tiles);
}

static inline Tilemap *tp_br2_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->br2_tiles);
}

static inline Tilemap *tp_outline_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->outline_tiles);
}

static inline Tilemap *tp_horiz_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->horiz_tiles);
}

static inline Tilemap *tp_vert_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->vert_tiles);
}

static inline Tilemap *tp_l90_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->l90_tiles);
}

static inline Tilemap *tp_l180_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->l180_tiles);
}

static inline Tilemap *tp_l_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->l_tiles);
}

static inline Tilemap *tp_l270_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->l270_tiles);
}

static inline Tilemap *tp_t_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->t_tiles);
}

static inline Tilemap *tp_t90_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->t90_tiles);
}

static inline Tilemap *tp_t180_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->t180_tiles);
}

static inline Tilemap *tp_t270_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
    return (&t->t270_tiles);
}

static inline Tilemap *tp_x_tiles (Tpp t)
{_
    if (unlikely(!t)) { ERR("no tp"); return nullptr; }
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

#endif // THING_TEMPLATE_H
