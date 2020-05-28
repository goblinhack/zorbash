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

class Tp {
public:
    //
    // Used a lot, so avoid the cost of an accessor.
    //
    uint16_t id {};
    uint8_t z_depth {};
    uint8_t z_prio {};
    //
    // Modified on tile loading; easier to leave public
    //
    Tilemap bl1_tiles;
    Tilemap bl2_tiles;
    Tilemap bot1_tiles;
    Tilemap bot2_tiles;
    Tilemap br1_tiles;
    Tilemap br2_tiles;
    Tilemap horiz_tiles;
    Tilemap l180_tiles;
    Tilemap l270_tiles;
    Tilemap l90_tiles;
    Tilemap l_tiles;
    Tilemap left1_tiles;
    Tilemap left2_tiles;
    Tilemap outline_tiles; // For water ripples
    Tilemap right1_tiles;
    Tilemap right2_tiles;
    Tilemap t180_tiles;
    Tilemap t270_tiles;
    Tilemap t90_tiles;
    Tilemap t_tiles;
    Tilemap tiles; // Animation tiles.
    Tilemap tl1_tiles;
    Tilemap tl2_tiles;
    Tilemap top1_tiles; // Adjacent tiles.
    Tilemap top2_tiles;
    Tilemap tr1_tiles;
    Tilemap tr2_tiles;
    Tilemap vert_tiles;
    Tilemap x_tiles;
private:
    //
    // Dice
    //
    Dice _nutrition_dice {};
    Dice _spawn_on_idle_dice {};
    Dice _stats_attack_dice {};
    std::string _stats_attack_dice_str;
    std::string _nutrition_dice_str;
    std::string _spawn_on_idle_dice_str;

    float _collision_radius {};
    fsize _sz;
    int _ai_delay_after_moving_ms {};
    int _ai_obstacle {};
    int _ai_scent_distance {};
    int _blit_bot_off {};
    int _blit_left_off {};
    int _blit_off {};
    int _blit_right_off {};
    int _blit_top_off {};
    int _collision_attack {};
    int _collision_box {};
    int _collision_check {};
    int _collision_circle {};
    int _collision_hit_priority {};
    int _hunger_clock_freq_ms {};
    int _internal_has_dir_anim {};
    int _internal_has_hp_anim {};
    int _is_active {}; // e.g. a monst or player or something movable
    int _is_attack_lunge {};
    int _is_attack_shove {};
    int _is_attack_shove_chance_d1000 {};
    int _is_attackable {};
    int _is_bleeder {};
    int _is_blood {};
    int _is_blood_splatter {};
    int _is_chasm {};
    int _is_combustible {};
    int _is_corpse_on_death {};
    int _is_corridor {};
    int _is_cursor {};
    int _is_cursor_can_hover_over {};
    int _is_cursor_path {};
    int _is_dead_on_shove {};
    int _is_deep_water {};
    int _is_dirt {};
    int _is_door {};
    int _is_entrance {};
    int _is_exit {};
    int _is_explosion {};
    int _is_flammable {};
    int _is_floor {};
    int _is_floor_deco {};
    int _is_food {};
    int _gfx_an_animation_only {};
    int _gfx_animated {};
    int _gfx_animated_can_hflip {};
    int _gfx_animated_can_vflip {};
    int _gfx_animated_no_dir {};
    int _gfx_attack_anim {};
    int _gfx_bounce_always {};
    int _gfx_bounce_on_move {};
    int _gfx_dead_anim {};
    int _gfx_large_shadow {};
    int _gfx_on_fire_anim {};
    int _gfx_oversized_but_sitting_on_the_ground {};
    int _gfx_show_outlined {};
    int _gfx_small_shadow_caster {};
    int _gfx_weapon_carry_anim {};
    int _is_hazard {};
    int _is_hunger_insatiable {};
    int _is_interesting {}; // e.g. something edible or a monst or lava
    int _is_key {};
    int _is_lava {};
    int _is_light_strength {};
    int _is_loggable {};
    int _is_made_of_meat {};
    int _is_meat_eater {};
    int _is_monst {};
    int _is_movable {};
    int _is_movement_blocking {};
    int _is_msg {};
    int _is_no_tile {};
    int _is_player {};
    int _is_projectile {};
    int _is_ripple {};
    int _is_rock {};
    int _is_rrr1 {};
    int _is_rrr10 {};
    int _is_rrr11 {};
    int _is_rrr12 {};
    int _is_rrr13 {};
    int _is_rrr14 {};
    int _is_rrr15 {};
    int _is_rrr16 {};
    int _is_rrr17 {};
    int _is_rrr18 {};
    int _is_fire_hater {};
    int _is_rrr2 {};
    int _is_rrr20 {};
    int _is_rrr21 {};
    int _is_rrr22 {};
    int _is_rrr23 {};
    int _is_rrr24 {};
    int _is_fire {};
    int _is_rrr3 {};
    int _is_rrr4 {};
    int _is_rrr5 {};
    int _is_rrr6 {};
    int _is_rrr7 {};
    int _is_rrr8 {};
    int _is_rrr9 {};
    int _is_secret_door {};
    int _is_shovable {};
    int _is_torch {};
    int _is_undead {};
    int _is_wall {};
    int _is_wall_deco {};
    int _is_water {};
    int _is_water_dweller {};
    int _is_water_hater {};
    int _is_weapon {};
    int _lifespan_count {};
    int _normal_placement_rules {};
    int _stats01 {};
    int _stats02 {};
    int _stats03 {};
    int _stats04 {};
    int _stats05 {};
    int _stats06 {};
    int _stats07 {};
    int _stats08 {};
    int _stats09 {};
    int _stats10 {};
    int _stats11 {};
    int _stats12 {};
    int _stats13 {};
    int _stats14 {};
    int _stats15 {};
    int _stats16 {};
    int _stats17 {};
    int _stats18 {};
    int _stats19 {};
    int _stats_attack_rate_tenths {};
    int _stats_defence {};
    int _stats_health_hunger_pct {};
    int _stats_health_initial {};
    int _stats_health_starving_pct {};
    int _stats_move_speed_ms {};
    int _stats_strength {};
    int _weapon_damage {};
    int _weapon_use_delay_hundredths {};
    int _weapon_use_distance {};
    std::string _light_color;
    std::string _name;
    std::string _spawn_on_death;
    std::string _str10;
    std::string _str11;
    std::string _str12;
    std::string _str1;
    std::string _str2;
    std::string _str3;
    std::string _str4;
    std::string _str5;
    std::string _str6;
    std::string _str7;
    std::string _str8;
    std::string _text_a_or_an;
    std::string _text_hits;
    std::string _text_name;
    std::string _weapon_carry_anim;
    std::string _weapon_use_anim;
    std::string _str9;
public:
    Tp (void) {
        newptr(this, "Tp");
    }

    ~Tp (void) {
        oldptr(this);
    }

    //
    // Dice
    //
    const Dice& nutrition_dice(void) const;
    const Dice& spawn_on_idle_dice(void) const;
    const Dice& stats_attack_dice(void) const;
    const std::string& nutrition_dice_str(void) const;
    const std::string& spawn_on_idle_dice_str(void) const;
    const std::string& stats_attack_dice_str(void) const;
    void set_nutrition_dice(const std::string &);
    void set_spawn_on_idle_dice(const std::string &);
    void set_stats_attack_dice(const std::string &);

    const Tilemap *tp_bl1_tiles(void) const;
    const Tilemap *tp_bl2_tiles(void) const;
    const Tilemap *tp_bot1_tiles(void) const;
    const Tilemap *tp_bot2_tiles(void) const;
    const Tilemap *tp_br1_tiles(void) const;
    const Tilemap *tp_br2_tiles(void) const;
    const Tilemap *tp_horiz_tiles(void) const;
    const Tilemap *tp_l180_tiles(void) const;
    const Tilemap *tp_l270_tiles(void) const;
    const Tilemap *tp_l90_tiles(void) const;
    const Tilemap *tp_l_tiles(void) const;
    const Tilemap *tp_left1_tiles(void) const;
    const Tilemap *tp_left2_tiles(void) const;
    const Tilemap *tp_outline_tiles(void) const;
    const Tilemap *tp_right1_tiles(void) const;
    const Tilemap *tp_right2_tiles(void) const;
    const Tilemap *tp_t180_tiles(void) const;
    const Tilemap *tp_t270_tiles(void) const;
    const Tilemap *tp_t90_tiles(void) const;
    const Tilemap *tp_t_tiles(void) const;
    const Tilemap *tp_tiles(void) const;
    const Tilemap *tp_tl1_tiles(void) const;
    const Tilemap *tp_tl2_tiles(void) const;
    const Tilemap *tp_top1_tiles(void) const;
    const Tilemap *tp_top2_tiles(void) const;
    const Tilemap *tp_tr1_tiles(void) const;
    const Tilemap *tp_tr2_tiles(void) const;
    const Tilemap *tp_vert_tiles(void) const;
    const Tilemap *tp_x_tiles(void) const;
    const std::string& light_color(void) const;
    const std::string& name(void) const;
    const std::string& text_name(void) const;
    const std::string& spawn_on_death(void) const;
    const std::string& weapon_carry_anim(void) const;
    const std::string& weapon_use_anim(void) const;
    const std::string& str1(void) const;
    const std::string& str10(void) const;
    const std::string& str11(void) const;
    const std::string& str12(void) const;
    const std::string& text_hits(void) const;
    const std::string& str2(void) const;
    const std::string& str3(void) const;
    const std::string& str4(void) const;
    const std::string& str5(void) const;
    const std::string& str6(void) const;
    const std::string& str7(void) const;
    const std::string& str8(void) const;
    const std::string& str9(void) const;
    float collision_radius(void) const;
    int ai_delay_after_moving_ms(void) const;
    int ai_obstacle(void) const;
    int ai_scent_distance(void) const;
    int blit_bot_off(void) const;
    int blit_left_off(void) const;
    int blit_right_off(void) const;
    int blit_top_off(void) const;
    int collision_attack(void) const;
    int collision_box(void) const;
    int collision_check(void) const;
    int collision_circle(void) const;
    int collision_hit_priority(void) const;
    int hunger_clock_freq_ms(void) const;
    int internal_has_dir_anim(void) const;
    int internal_has_hp_anim(void) const;
    int is_active(void) const;
    int is_attack_lunge(void) const;
    int is_attack_shove(void) const;
    int is_attack_shove_chance_d1000(void) const;
    int is_attackable(void) const;
    int is_bleeder(void) const;
    int is_blood(void) const;
    int is_blood_splatter(void) const;
    int is_chasm(void) const;
    int is_combustible(void) const;
    int is_corpse_on_death(void) const;
    int is_corridor(void) const;
    int is_cursor(void) const;
    int is_cursor_can_hover_over(void) const;
    int is_cursor_path(void) const;
    int is_dead_on_shove(void) const;
    int is_deep_water(void) const;
    int is_dirt(void) const;
    int is_door(void) const;
    int is_entrance(void) const;
    int is_exit(void) const;
    int is_explosion(void) const;
    int is_flammable(void) const;
    int is_floor(void) const;
    int is_floor_deco(void) const;
    int is_food(void) const;
    int gfx_an_animation_only(void) const;
    int gfx_animated(void) const;
    int gfx_animated_can_hflip(void) const;
    int gfx_animated_can_vflip(void) const;
    int gfx_animated_no_dir(void) const;
    int gfx_attack_anim(void) const;
    int gfx_bounce_always(void) const;
    int gfx_bounce_on_move(void) const;
    int gfx_dead_anim(void) const;
    int gfx_large_shadow(void) const;
    int gfx_on_fire_anim(void) const;
    int gfx_oversized_but_sitting_on_the_ground(void) const;
    int gfx_show_outlined(void) const;
    int gfx_small_shadow_caster(void) const;
    int gfx_weapon_carry_anim(void) const;
    int is_hazard(void) const;
    int is_hunger_insatiable(void) const;
    int is_interesting(void) const;
    int is_key(void) const;
    int is_lava(void) const;
    int is_light_strength(void) const;
    int is_loggable(void) const;
    int is_made_of_meat(void) const;
    int is_meat_eater(void) const;
    int is_monst(void) const;
    int is_movable(void) const;
    int is_movement_blocking(void) const;
    int is_msg(void) const;
    int is_no_tile(void) const;
    int is_player(void) const;
    int is_projectile(void) const;
    int is_ripple(void) const;
    int is_rock(void) const;
    int is_rrr1(void) const;
    int is_rrr10(void) const;
    int is_rrr11(void) const;
    int is_rrr12(void) const;
    int is_rrr13(void) const;
    int is_rrr14(void) const;
    int is_rrr15(void) const;
    int is_rrr16(void) const;
    int is_rrr17(void) const;
    int is_rrr18(void) const;
    int is_fire_hater(void) const;
    int is_rrr2(void) const;
    int is_rrr20(void) const;
    int is_rrr21(void) const;
    int is_rrr22(void) const;
    int is_rrr23(void) const;
    int is_rrr24(void) const;
    int is_fire(void) const;
    int is_rrr3(void) const;
    int is_rrr4(void) const;
    int is_rrr5(void) const;
    int is_rrr6(void) const;
    int is_rrr7(void) const;
    int is_rrr8(void) const;
    int is_rrr9(void) const;
    int is_secret_door(void) const;
    int is_shovable(void) const;
    int is_torch(void) const;
    int is_undead(void) const;
    int is_wall(void) const;
    int is_wall_deco(void) const;
    int is_water(void) const;
    int is_water_dweller(void) const;
    int is_water_hater(void) const;
    int is_weapon(void) const;
    int lifespan_count(void) const;
    int normal_placement_rules(void) const;
    int stats01(void) const;
    int stats02(void) const;
    int stats03(void) const;
    int stats04(void) const;
    int stats05(void) const;
    int stats06(void) const;
    int stats07(void) const;
    int stats08(void) const;
    int stats09(void) const;
    int stats10(void) const;
    int stats11(void) const;
    int stats12(void) const;
    int stats13(void) const;
    int stats14(void) const;
    int stats15(void) const;
    int stats16(void) const;
    int stats17(void) const;
    int stats18(void) const;
    int stats19(void) const;
    int stats_attack_rate_tenths(void) const;
    int stats_defence(void) const;
    int stats_health_hunger_pct(void) const;
    int stats_health_initial(void) const;
    int stats_health_starving_pct(void) const;
    int stats_move_speed_ms(void) const;
    int stats_strength(void) const;
    int weapon_damage(void) const;
    int weapon_use_delay_hundredths(void) const;
    int weapon_use_distance(void) const;
    std::string text_a_or_an(void) const;
    void set_text_a_or_an(const std::string &);
    void set_ai_delay_after_moving_ms(int);
    void set_ai_obstacle(int);
    void set_ai_scent_distance(int);
    void set_blit_bot_off(int);
    void set_blit_left_off(int);
    void set_blit_right_off(int);
    void set_blit_top_off(int);
    void set_collision_attack(int);
    void set_collision_box(int);
    void set_collision_check(int);
    void set_collision_circle(int);
    void set_collision_hit_priority(int);
    void set_collision_radius(float);
    void set_hunger_clock_freq_ms(int);
    void set_internal_has_dir_anim(int);
    void set_internal_has_hp_anim(int);
    void set_is_active(int);
    void set_is_attack_lunge(int);
    void set_is_attack_shove(int);
    void set_is_attack_shove_chance_d1000(int);
    void set_is_attackable(int);
    void set_is_bleeder(int);
    void set_is_blood(int);
    void set_is_blood_splatter(int);
    void set_is_chasm(int);
    void set_is_combustible(int);
    void set_is_corpse_on_death(int);
    void set_is_corridor(int);
    void set_is_cursor(int);
    void set_is_cursor_can_hover_over(int);
    void set_is_cursor_path(int);
    void set_is_dead_on_shove(int);
    void set_is_deep_water(int);
    void set_is_dirt(int);
    void set_is_door(int);
    void set_is_entrance(int);
    void set_is_exit(int);
    void set_is_explosion(int);
    void set_is_flammable(int);
    void set_is_floor(int);
    void set_is_floor_deco(int);
    void set_is_food(int);
    void set_gfx_an_animation_only(int);
    void set_gfx_animated(int);
    void set_gfx_animated_can_hflip(int);
    void set_gfx_animated_can_vflip(int);
    void set_gfx_animated_no_dir(int);
    void set_gfx_attack_anim(int);
    void set_gfx_bounce_always(int);
    void set_gfx_bounce_on_move(int);
    void set_gfx_dead_anim(int);
    void set_gfx_large_shadow(int);
    void set_gfx_on_fire_anim(int);
    void set_gfx_oversized_but_sitting_on_the_ground(int);
    void set_gfx_show_outlined(int);
    void set_gfx_small_shadow_caster(int);
    void set_gfx_weapon_carry_anim(int);
    void set_is_hazard(int);
    void set_is_hunger_insatiable(int);
    void set_is_interesting(int);
    void set_is_key(int);
    void set_is_lava(int);
    void set_is_light_strength(int);
    void set_is_loggable(int);
    void set_is_made_of_meat(int);
    void set_is_meat_eater(int);
    void set_is_monst(int);
    void set_is_movable(int);
    void set_is_movement_blocking(int);
    void set_is_msg(int);
    void set_is_no_tile(int);
    void set_is_player(int);
    void set_is_projectile(int);
    void set_is_ripple(int);
    void set_is_rock(int);
    void set_is_rrr1(int);
    void set_is_rrr10(int);
    void set_is_rrr11(int);
    void set_is_rrr12(int);
    void set_is_rrr13(int);
    void set_is_rrr14(int);
    void set_is_rrr15(int);
    void set_is_rrr16(int);
    void set_is_rrr17(int);
    void set_is_rrr18(int);
    void set_is_fire_hater(int);
    void set_is_rrr2(int);
    void set_is_rrr20(int);
    void set_is_rrr21(int);
    void set_is_rrr22(int);
    void set_is_rrr23(int);
    void set_is_rrr24(int);
    void set_is_fire(int);
    void set_is_rrr3(int);
    void set_is_rrr4(int);
    void set_is_rrr5(int);
    void set_is_rrr6(int);
    void set_is_rrr7(int);
    void set_is_rrr8(int);
    void set_is_rrr9(int);
    void set_is_secret_door(int);
    void set_is_shovable(int);
    void set_is_torch(int);
    void set_is_undead(int);
    void set_is_wall(int);
    void set_is_wall_deco(int);
    void set_is_water(int);
    void set_is_water_dweller(int);
    void set_is_water_hater(int);
    void set_is_weapon(int);
    void set_lifespan_count(int);
    void set_light_color(const std::string &);
    void set_name(const std::string &);
    void set_normal_placement_rules(int);
    void set_text_name(const std::string &);
    void set_spawn_on_death(const std::string &);
    void set_stats01(int);
    void set_stats02(int);
    void set_stats03(int);
    void set_stats04(int);
    void set_stats05(int);
    void set_stats06(int);
    void set_stats07(int);
    void set_stats08(int);
    void set_stats09(int);
    void set_stats10(int);
    void set_stats11(int);
    void set_stats12(int);
    void set_stats13(int);
    void set_stats14(int);
    void set_stats15(int);
    void set_stats16(int);
    void set_stats17(int);
    void set_stats18(int);
    void set_stats19(int);
    void set_stats_attack_rate_tenths(int);
    void set_stats_defence(int);
    void set_stats_health_hunger_pct(int);
    void set_stats_health_initial(int);
    void set_stats_health_starving_pct(int);
    void set_stats_move_speed_ms(int);
    void set_stats_strength(int);
    void set_weapon_carry_anim(const std::string &);
    void set_weapon_damage(int);
    void set_weapon_use_anim(const std::string &);
    void set_weapon_use_delay_hundredths(int);
    void set_weapon_use_distance(int);
    void set_z_depth(int);
    void set_z_prio(int);
    void set_str1(const std::string &);
    void set_str10(const std::string &);
    void set_str11(const std::string &);
    void set_str12(const std::string &);
    void set_text_hits(const std::string &);
    void set_str2(const std::string &);
    void set_str3(const std::string &);
    void set_str4(const std::string &);
    void set_str5(const std::string &);
    void set_str6(const std::string &);
    void set_str7(const std::string &);
    void set_str8(const std::string &);
    void set_str9(const std::string &);
};

Tpp string2tp(const char **s);
Tpp string2tp(std::string &s, int *len);
Tpp string2tp(std::wstring &s, int *len);
Tpp tp_find(uint32_t id);
Tpp tp_load(int id, std::string const& file, std::string const& text_name);
Tpp tp_random_blood(void);
Tpp tp_random_blood_splatter(void);
Tpp tp_random_deco(void);
Tpp tp_random_dirt(void);
Tpp tp_random_entrance(void);
Tpp tp_random_exit(void);
Tpp tp_random_floor(void);
Tpp tp_random_food(void);
Tpp tp_random_key(void);
Tpp tp_random_monst(void);
Tpp tp_random_ripple(void);
Tpp tp_random_rock(void);
Tpp tp_random_torch(void);
Tpp tp_random_door(void);
Tpp tp_random_secret_door(void);
Tpp tp_random_wall(void);
Tpp tp_random_wall_deco(void);
uint8_t tp_init(void);
void tp_fini(void);
void tp_init_after_loading(void);
Tilep tp_first_tile(Tpp);

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
