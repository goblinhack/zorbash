//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_thing_template.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_tile.h"
#include "my_dice.h"

//
// Dice
//
const Dice& Tp::idle_tick_dice(void) const { return _idle_tick_dice; }
const int Tp::idle_tick(void) const { return _idle_tick_dice.roll(); }
const std::string& Tp::idle_tick_dice_str(void) const { return _idle_tick_dice_str; }
void Tp::set_idle_tick_dice(const std::string &v) { _idle_tick_dice = v; _idle_tick_dice_str = v; }

const Dice& Tp::lifespan_dice(void) const { return _lifespan_dice; }
const int Tp::lifespan(void) const { return _lifespan_dice.roll(); }
const std::string& Tp::lifespan_dice_str(void) const { return _lifespan_dice_str; }
void Tp::set_lifespan_dice(const std::string &v) { _lifespan_dice = v; _lifespan_dice_str = v; }

const Dice& Tp::nutrition_dice(void) const { return _nutrition_dice; }
const int Tp::nutrition(void) const { return _nutrition_dice.roll(); }
const std::string& Tp::nutrition_dice_str(void) const { return _nutrition_dice_str; }
void Tp::set_nutrition_dice(const std::string &v) { _nutrition_dice = v; _nutrition_dice_str = v; }

const Dice& Tp::stats_attack_dice(void) const { return _stats_attack_dice; }
const int Tp::stats_attack(void) const { return _stats_attack_dice.roll(); }
const std::string& Tp::stats_attack_dice_str(void) const { return _stats_attack_dice_str; }
void Tp::set_stats_attack_dice(const std::string &v) { _stats_attack_dice = v; _stats_attack_dice_str = v; }

const std::string& Tp::light_color(void) const { return _light_color; }
const std::string& Tp::name(void) const { return _name; }
const std::string& Tp::spawn_on_death(void) const { return _spawn_on_death; }
const std::string& Tp::str1(void) const { return _str1; }
const std::string& Tp::str10(void) const { return _str10; }
const std::string& Tp::str11(void) const { return _str11; }
const std::string& Tp::str12(void) const { return _str12; }
const std::string& Tp::str2(void) const { return _str2; }
const std::string& Tp::str3(void) const { return _str3; }
const std::string& Tp::str4(void) const { return _str4; }
const std::string& Tp::str5(void) const { return _str5; }
const std::string& Tp::str6(void) const { return _str6; }
const std::string& Tp::str7(void) const { return _str7; }
const std::string& Tp::str8(void) const { return _str8; }
const std::string& Tp::str9(void) const { return _str9; }
const std::string& Tp::text_hits(void) const { return _text_hits; }
const std::string& Tp::text_name(void) const { return _text_name; }
const std::string& Tp::weapon_carry_anim(void) const { return _weapon_carry_anim; }
const std::string& Tp::weapon_use_anim(void) const { return _weapon_use_anim; }
float Tp::collision_radius(void) const { return _collision_radius; }
int Tp::ai_delay_after_moving_ms(void) const { return _ai_delay_after_moving_ms; }
int Tp::ai_obstacle(void) const { return _ai_obstacle; }
int Tp::ai_scent_distance(void) const { return _ai_scent_distance; }
int Tp::blit_bot_off(void) const { return _blit_bot_off; }
int Tp::blit_left_off(void) const { return _blit_left_off; }
int Tp::blit_right_off(void) const { return _blit_right_off; }
int Tp::blit_top_off(void) const { return _blit_top_off; }
int Tp::collision_attack(void) const { return _collision_attack; }
int Tp::collision_box(void) const { return _collision_box; }
int Tp::collision_check(void) const { return _collision_check; }
int Tp::collision_circle(void) const { return _collision_circle; }
int Tp::collision_hit_priority(void) const { return _collision_hit_priority; }
int Tp::gfx_an_animation_only(void) const { return _gfx_an_animation_only; }
int Tp::gfx_animated(void) const { return _gfx_animated; }
int Tp::gfx_animated_can_hflip(void) const { return _gfx_animated_can_hflip; }
int Tp::gfx_animated_can_vflip(void) const { return _gfx_animated_can_vflip; }
int Tp::gfx_animated_no_dir(void) const { return _gfx_animated_no_dir; }
int Tp::gfx_attack_anim(void) const { return _gfx_attack_anim; }
int Tp::gfx_bounce_always(void) const { return _gfx_bounce_always; }
int Tp::gfx_bounce_on_move(void) const { return _gfx_bounce_on_move; }
int Tp::gfx_dead_anim(void) const { return _gfx_dead_anim; }
int Tp::gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
int Tp::gfx_oversized_but_sitting_on_the_ground(void) const { return _gfx_oversized_but_sitting_on_the_ground; }
int Tp::gfx_show_outlined(void) const { return _gfx_show_outlined; }
int Tp::gfx_small_shadow_caster(void) const { return _gfx_small_shadow_caster; }
int Tp::gfx_weapon_carry_anim(void) const { return _gfx_weapon_carry_anim; }
int Tp::hunger_clock_freq_ms(void) const { return _hunger_clock_freq_ms; }
int Tp::internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
int Tp::internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
int Tp::is_active(void) const { return _is_active; }
int Tp::is_attack_lunge(void) const { return _is_attack_lunge; }
int Tp::is_attack_shove(void) const { return _is_attack_shove; }
int Tp::is_attack_shove_chance_d1000(void) const { return _is_attack_shove_chance_d1000; }
int Tp::is_attackable(void) const { return _is_attackable; }
int Tp::is_bleeder(void) const { return _is_bleeder; }
int Tp::is_blood(void) const { return _is_blood; }
int Tp::is_blood_splatter(void) const { return _is_blood_splatter; }
int Tp::is_chasm(void) const { return _is_chasm; }
int Tp::is_combustible(void) const { return _is_combustible; }
int Tp::is_corpse_on_death(void) const { return _is_corpse_on_death; }
int Tp::is_corridor(void) const { return _is_corridor; }
int Tp::is_cursor(void) const { return _is_cursor; }
int Tp::is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
int Tp::is_cursor_path(void) const { return _is_cursor_path; }
int Tp::is_dead_on_shove(void) const { return _is_dead_on_shove; }
int Tp::is_deep_water(void) const { return _is_deep_water; }
int Tp::is_dirt(void) const { return _is_dirt; }
int Tp::is_door(void) const { return _is_door; }
int Tp::is_entrance(void) const { return _is_entrance; }
int Tp::is_exit(void) const { return _is_exit; }
int Tp::is_explosion(void) const { return _is_explosion; }
int Tp::is_fire(void) const { return _is_fire; }
int Tp::is_fire_hater(void) const { return _is_fire_hater; }
int Tp::is_flammable(void) const { return _is_flammable; }
int Tp::is_floor(void) const { return _is_floor; }
int Tp::is_floor_deco(void) const { return _is_floor_deco; }
int Tp::is_food(void) const { return _is_food; }
int Tp::is_hazard(void) const { return _is_hazard; }
int Tp::is_hunger_insatiable(void) const { return _is_hunger_insatiable; }
int Tp::is_interesting(void) const { return _is_interesting; }
int Tp::is_key(void) const { return _is_key; }
int Tp::is_large(void) const { return _is_large; }
int Tp::is_smoke(void) const { return _is_smoke; }
int Tp::is_lava(void) const { return _is_lava; }
int Tp::is_light_strength(void) const { return _is_light_strength; }
int Tp::is_loggable_for_unimportant_stuff(void) const { return _is_loggable_for_unimportant_stuff; }
int Tp::is_made_of_meat(void) const { return _is_made_of_meat; }
int Tp::is_meat_eater(void) const { return _is_meat_eater; }
int Tp::is_monst(void) const { return _is_monst; }
int Tp::is_movable(void) const { return _is_movable; }
int Tp::is_movement_blocking(void) const { return _is_movement_blocking; }
int Tp::is_msg(void) const { return _is_msg; }
int Tp::is_no_tile(void) const { return _is_no_tile; }
int Tp::is_player(void) const { return _is_player; }
int Tp::is_projectile(void) const { return _is_projectile; }
int Tp::is_ripple(void) const { return _is_ripple; }
int Tp::is_rock(void) const { return _is_rock; }
int Tp::is_rrr1(void) const { return _is_rrr1; }
int Tp::is_rrr10(void) const { return _is_rrr10; }
int Tp::is_rrr11(void) const { return _is_rrr11; }
int Tp::is_rrr12(void) const { return _is_rrr12; }
int Tp::is_rrr13(void) const { return _is_rrr13; }
int Tp::is_rrr14(void) const { return _is_rrr14; }
int Tp::is_loggable_for_important_stuff(void) const { return _is_loggable_for_important_stuff; }
int Tp::tick_catches_up_on_attack(void) const { return _tick_catches_up_on_attack; }
int Tp::is_temporary(void) const { return _is_temporary; }
int Tp::is_rrr2(void) const { return _is_rrr2; }
int Tp::is_rrr20(void) const { return _is_rrr20; }
int Tp::is_rrr21(void) const { return _is_rrr21; }
int Tp::is_rrr22(void) const { return _is_rrr22; }
int Tp::is_intelligent(void) const { return _is_intelligent; }
int Tp::is_double_damage_from_fire(void) const { return _is_double_damage_from_fire; }
int Tp::is_rrr3(void) const { return _is_rrr3; }
int Tp::is_rrr4(void) const { return _is_rrr4; }
int Tp::is_rrr5(void) const { return _is_rrr5; }
int Tp::is_rrr6(void) const { return _is_rrr6; }
int Tp::is_rrr7(void) const { return _is_rrr7; }
int Tp::is_rrr8(void) const { return _is_rrr8; }
int Tp::is_rrr9(void) const { return _is_rrr9; }
int Tp::is_secret_door(void) const { return _is_secret_door; }
int Tp::is_shovable(void) const { return _is_shovable; }
int Tp::is_torch(void) const { return _is_torch; }
int Tp::is_undead(void) const { return _is_undead; }
int Tp::is_wall(void) const { return _is_wall; }
int Tp::is_wall_deco(void) const { return _is_wall_deco; }
int Tp::is_water(void) const { return _is_water; }
int Tp::is_water_dweller(void) const { return _is_water_dweller; }
int Tp::is_water_hater(void) const { return _is_water_hater; }
int Tp::is_weapon(void) const { return _is_weapon; }
int Tp::normal_placement_rules(void) const { return _normal_placement_rules; }
int Tp::stats01(void) const { return _stats01; }
int Tp::stats02(void) const { return _stats02; }
int Tp::stats03(void) const { return _stats03; }
int Tp::stats04(void) const { return _stats04; }
int Tp::stats05(void) const { return _stats05; }
int Tp::stats06(void) const { return _stats06; }
int Tp::stats07(void) const { return _stats07; }
int Tp::stats08(void) const { return _stats08; }
int Tp::stats09(void) const { return _stats09; }
int Tp::stats10(void) const { return _stats10; }
int Tp::stats11(void) const { return _stats11; }
int Tp::stats12(void) const { return _stats12; }
int Tp::stats13(void) const { return _stats13; }
int Tp::stats14(void) const { return _stats14; }
int Tp::stats15(void) const { return _stats15; }
int Tp::stats16(void) const { return _stats16; }
int Tp::stats17(void) const { return _stats17; }
int Tp::stats18(void) const { return _stats18; }
int Tp::stats19(void) const { return _stats19; }
int Tp::tick_rate_tenths(void) const { return _tick_rate_tenths; }
int Tp::stats_defence(void) const { return _stats_defence; }
int Tp::stats_health_hunger_pct(void) const { return _stats_health_hunger_pct; }
int Tp::stats_health_initial(void) const { return _stats_health_initial; }
int Tp::stats_health_starving_pct(void) const { return _stats_health_starving_pct; }
int Tp::stats_move_speed_ms(void) const { return _stats_move_speed_ms; }
int Tp::stats_strength(void) const { return _stats_strength; }
int Tp::weapon_damage(void) const { return _weapon_damage; }
int Tp::weapon_use_delay_hundredths(void) const { return _weapon_use_delay_hundredths; }
int Tp::weapon_use_distance(void) const { return _weapon_use_distance; }
std::string Tp::text_a_or_an(void) const { return _text_a_or_an; }
void Tp::set_ai_delay_after_moving_ms(int v) { _ai_delay_after_moving_ms = v; }
void Tp::set_ai_obstacle(int v) { _ai_obstacle = v; }
void Tp::set_ai_scent_distance(int v) { _ai_scent_distance = v; }
void Tp::set_blit_bot_off(int v) { _blit_bot_off = v; }
void Tp::set_blit_left_off(int v) { _blit_left_off = v; }
void Tp::set_blit_right_off(int v) { _blit_right_off = v; }
void Tp::set_blit_top_off(int v) { _blit_top_off = v; }
void Tp::set_collision_attack(int v) { _collision_attack = v; }
void Tp::set_collision_box(int v) { _collision_box = v; }
void Tp::set_collision_check(int v) { _collision_check = v; }
void Tp::set_collision_circle(int v) { _collision_circle = v; }
void Tp::set_collision_hit_priority(int v) { _collision_hit_priority = v; }
void Tp::set_collision_radius(float v) { _collision_radius = v; }
void Tp::set_gfx_an_animation_only(int v) { _gfx_an_animation_only = v; }
void Tp::set_gfx_animated(int v) { _gfx_animated = v; }
void Tp::set_gfx_animated_can_hflip(int v) { _gfx_animated_can_hflip = v; }
void Tp::set_gfx_animated_can_vflip(int v) { _gfx_animated_can_vflip = v; }
void Tp::set_gfx_animated_no_dir(int v) { _gfx_animated_no_dir = v; }
void Tp::set_gfx_attack_anim(int v) { _gfx_attack_anim = v; }
void Tp::set_gfx_bounce_always(int v) { _gfx_bounce_always = v; }
void Tp::set_gfx_bounce_on_move(int v) { _gfx_bounce_on_move = v; }
void Tp::set_gfx_dead_anim(int v) { _gfx_dead_anim = v; }
void Tp::set_gfx_on_fire_anim(int v) { _gfx_on_fire_anim = v; }
void Tp::set_gfx_oversized_but_sitting_on_the_ground(int v) { _gfx_oversized_but_sitting_on_the_ground = v; }
void Tp::set_gfx_show_outlined(int v) { _gfx_show_outlined = v; }
void Tp::set_gfx_small_shadow_caster(int v) { _gfx_small_shadow_caster = v; }
void Tp::set_gfx_weapon_carry_anim(int v) { _gfx_weapon_carry_anim = v; }
void Tp::set_hunger_clock_freq_ms(int v) { _hunger_clock_freq_ms = v; }
void Tp::set_internal_has_dir_anim(int v) { _internal_has_dir_anim = v; }
void Tp::set_internal_has_hp_anim(int v) { _internal_has_hp_anim = v; }
void Tp::set_is_active(int v) { _is_active = v; }
void Tp::set_is_attack_lunge(int v) { _is_attack_lunge = v; }
void Tp::set_is_attack_shove(int v) { _is_attack_shove = v; }
void Tp::set_is_attack_shove_chance_d1000(int v) { _is_attack_shove_chance_d1000 = v; }
void Tp::set_is_attackable(int v) { _is_attackable = v; }
void Tp::set_is_bleeder(int v) { _is_bleeder = v; }
void Tp::set_is_blood(int v) { _is_blood = v; }
void Tp::set_is_blood_splatter(int v) { _is_blood_splatter = v; }
void Tp::set_is_chasm(int v) { _is_chasm = v; }
void Tp::set_is_combustible(int v) { _is_combustible = v; }
void Tp::set_is_corpse_on_death(int v) { _is_corpse_on_death = v; }
void Tp::set_is_corridor(int v) { _is_corridor = v; }
void Tp::set_is_cursor(int v) { _is_cursor = v; }
void Tp::set_is_cursor_can_hover_over(int v) { _is_cursor_can_hover_over = v; }
void Tp::set_is_cursor_path(int v) { _is_cursor_path = v; }
void Tp::set_is_dead_on_shove(int v) { _is_dead_on_shove = v; }
void Tp::set_is_deep_water(int v) { _is_deep_water = v; }
void Tp::set_is_dirt(int v) { _is_dirt = v; }
void Tp::set_is_door(int v) { _is_door = v; }
void Tp::set_is_entrance(int v) { _is_entrance = v; }
void Tp::set_is_exit(int v) { _is_exit = v; }
void Tp::set_is_explosion(int v) { _is_explosion = v; }
void Tp::set_is_fire(int v) { _is_fire = v; }
void Tp::set_is_fire_hater(int v) { _is_fire_hater = v; }
void Tp::set_is_flammable(int v) { _is_flammable = v; }
void Tp::set_is_floor(int v) { _is_floor = v; }
void Tp::set_is_floor_deco(int v) { _is_floor_deco = v; }
void Tp::set_is_food(int v) { _is_food = v; }
void Tp::set_is_hazard(int v) { _is_hazard = v; }
void Tp::set_is_hunger_insatiable(int v) { _is_hunger_insatiable = v; }
void Tp::set_is_interesting(int v) { _is_interesting = v; }
void Tp::set_is_key(int v) { _is_key = v; }
void Tp::set_is_large(int v) { _is_large = v; }
void Tp::set_is_smoke(int v) { _is_smoke = v; }
void Tp::set_is_lava(int v) { _is_lava = v; }
void Tp::set_is_light_strength(int v) { _is_light_strength = v; }
void Tp::set_is_loggable_for_unimportant_stuff(int v) { _is_loggable_for_unimportant_stuff = v; }
void Tp::set_is_made_of_meat(int v) { _is_made_of_meat = v; }
void Tp::set_is_meat_eater(int v) { _is_meat_eater = v; }
void Tp::set_is_monst(int v) { _is_monst = v; }
void Tp::set_is_movable(int v) { _is_movable = v; }
void Tp::set_is_movement_blocking(int v) { _is_movement_blocking = v; }
void Tp::set_is_msg(int v) { _is_msg = v; }
void Tp::set_is_no_tile(int v) { _is_no_tile = v; }
void Tp::set_is_player(int v) { _is_player = v; }
void Tp::set_is_projectile(int v) { _is_projectile = v; }
void Tp::set_is_ripple(int v) { _is_ripple = v; }
void Tp::set_is_rock(int v) { _is_rock = v; }
void Tp::set_is_rrr1(int v) { _is_rrr1 = v; }
void Tp::set_is_rrr10(int v) { _is_rrr10 = v; }
void Tp::set_is_rrr11(int v) { _is_rrr11 = v; }
void Tp::set_is_rrr12(int v) { _is_rrr12 = v; }
void Tp::set_is_rrr13(int v) { _is_rrr13 = v; }
void Tp::set_is_rrr14(int v) { _is_rrr14 = v; }
void Tp::set_is_loggable_for_important_stuff(int v) { _is_loggable_for_important_stuff = v; }
void Tp::set_tick_catches_up_on_attack(int v) { _tick_catches_up_on_attack = v; }
void Tp::set_is_temporary(int v) { _is_temporary = v; }
void Tp::set_is_rrr2(int v) { _is_rrr2 = v; }
void Tp::set_is_rrr20(int v) { _is_rrr20 = v; }
void Tp::set_is_rrr21(int v) { _is_rrr21 = v; }
void Tp::set_is_rrr22(int v) { _is_rrr22 = v; }
void Tp::set_is_intelligent(int v) { _is_intelligent = v; }
void Tp::set_is_double_damage_from_fire(int v) { _is_double_damage_from_fire = v; }
void Tp::set_is_rrr3(int v) { _is_rrr3 = v; }
void Tp::set_is_rrr4(int v) { _is_rrr4 = v; }
void Tp::set_is_rrr5(int v) { _is_rrr5 = v; }
void Tp::set_is_rrr6(int v) { _is_rrr6 = v; }
void Tp::set_is_rrr7(int v) { _is_rrr7 = v; }
void Tp::set_is_rrr8(int v) { _is_rrr8 = v; }
void Tp::set_is_rrr9(int v) { _is_rrr9 = v; }
void Tp::set_is_secret_door(int v) { _is_secret_door = v; }
void Tp::set_is_shovable(int v) { _is_shovable = v; }
void Tp::set_is_torch(int v) { _is_torch = v; }
void Tp::set_is_undead(int v) { _is_undead = v; }
void Tp::set_is_wall(int v) { _is_wall = v; }
void Tp::set_is_wall_deco(int v) { _is_wall_deco = v; }
void Tp::set_is_water(int v) { _is_water = v; }
void Tp::set_is_water_dweller(int v) { _is_water_dweller = v; }
void Tp::set_is_water_hater(int v) { _is_water_hater = v; }
void Tp::set_is_weapon(int v) { _is_weapon = v; }
void Tp::set_light_color(const std::string &v) { _light_color = v; }
void Tp::set_name(const std::string &v) { _name = v; }
void Tp::set_normal_placement_rules(int v) { _normal_placement_rules = v; }
void Tp::set_spawn_on_death(const std::string &v) { _spawn_on_death = v; }
void Tp::set_stats01(int v) { _stats01 = v; }
void Tp::set_stats02(int v) { _stats02 = v; }
void Tp::set_stats03(int v) { _stats03 = v; }
void Tp::set_stats04(int v) { _stats04 = v; }
void Tp::set_stats05(int v) { _stats05 = v; }
void Tp::set_stats06(int v) { _stats06 = v; }
void Tp::set_stats07(int v) { _stats07 = v; }
void Tp::set_stats08(int v) { _stats08 = v; }
void Tp::set_stats09(int v) { _stats09 = v; }
void Tp::set_stats10(int v) { _stats10 = v; }
void Tp::set_stats11(int v) { _stats11 = v; }
void Tp::set_stats12(int v) { _stats12 = v; }
void Tp::set_stats13(int v) { _stats13 = v; }
void Tp::set_stats14(int v) { _stats14 = v; }
void Tp::set_stats15(int v) { _stats15 = v; }
void Tp::set_stats16(int v) { _stats16 = v; }
void Tp::set_stats17(int v) { _stats17 = v; }
void Tp::set_stats18(int v) { _stats18 = v; }
void Tp::set_stats19(int v) { _stats19 = v; }
void Tp::set_tick_rate_tenths(int v) { _tick_rate_tenths = v; }
void Tp::set_stats_defence(int v) { _stats_defence = v; }
void Tp::set_stats_health_hunger_pct(int v) { _stats_health_hunger_pct = v; }
void Tp::set_stats_health_initial(int v) { _stats_health_initial = v; }
void Tp::set_stats_health_starving_pct(int v) { _stats_health_starving_pct = v; }
void Tp::set_stats_move_speed_ms(int v) { _stats_move_speed_ms = v; }
void Tp::set_stats_strength(int v) { _stats_strength = v; }
void Tp::set_str1(const std::string &v) { _str1 = v; }
void Tp::set_str10(const std::string &v) { _str10 = v; }
void Tp::set_str11(const std::string &v) { _str11 = v; }
void Tp::set_str12(const std::string &v) { _str12 = v; }
void Tp::set_str2(const std::string &v) { _str2 = v; }
void Tp::set_str3(const std::string &v) { _str3 = v; }
void Tp::set_str4(const std::string &v) { _str4 = v; }
void Tp::set_str5(const std::string &v) { _str5 = v; }
void Tp::set_str6(const std::string &v) { _str6 = v; }
void Tp::set_str7(const std::string &v) { _str7 = v; }
void Tp::set_str8(const std::string &v) { _str8 = v; }
void Tp::set_str9(const std::string &v) { _str9 = v; }
void Tp::set_text_a_or_an(const std::string &v) { _text_a_or_an = v; }
void Tp::set_text_hits(const std::string &v) { _text_hits = v; }
void Tp::set_text_name(const std::string &v) { _text_name = v; }
void Tp::set_weapon_carry_anim(const std::string &v) { _weapon_carry_anim = v; }
void Tp::set_weapon_damage(int v) { _weapon_damage = v; }
void Tp::set_weapon_use_anim(const std::string &v) { _weapon_use_anim = v; }
void Tp::set_weapon_use_delay_hundredths(int v) { _weapon_use_delay_hundredths = v; }
void Tp::set_weapon_use_distance(int v) { _weapon_use_distance = v; }
void Tp::set_z_depth(int v) { z_depth = v; }
void Tp::set_z_prio(int v) { z_prio = v; }
