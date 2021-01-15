//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
const Dice& Tp::on_idle_dice_do(void) const { return _on_idle_dice_do; }
const int Tp::idle_tick(void) const { return _on_idle_dice_do.roll(); }
const std::string& Tp::on_idle_dice_do_str(void) const { return _on_idle_dice_do_str; }
void Tp::set_on_idle_dice_do(const std::string &v) { _on_idle_dice_do = v; _on_idle_dice_do_str = v; }

const Dice& Tp::lifespan_dice(void) const { return _lifespan_dice; }
const int Tp::lifespan(void) const { return _lifespan_dice.roll(); }
const std::string& Tp::lifespan_dice_str(void) const { return _lifespan_dice_str; }
void Tp::set_lifespan_dice(const std::string &v) { _lifespan_dice = v; _lifespan_dice_str = v; }

const Dice& Tp::nutrition_dice(void) const { return _nutrition_dice; }
const int Tp::nutrition(void) const { return _nutrition_dice.roll(); }
const std::string& Tp::nutrition_dice_str(void) const { return _nutrition_dice_str; }
void Tp::set_nutrition_dice(const std::string &v) { _nutrition_dice = v; _nutrition_dice_str = v; }

const Dice& Tp::get_damage_melee_dice(void) const { return _damage_melee_dice; }
const int Tp::get_damage_melee(void) const { return _damage_melee_dice.roll(); }
const std::string& Tp::get_damage_melee_dice_str(void) const { return _damage_melee_dice_str; }
void Tp::set_damage_melee_dice(const std::string &v) { _damage_melee_dice = v; _damage_melee_dice_str = v; }

const Dice& Tp::get_damage_poison_dice(void) const { return _damage_poison_dice; }
const int Tp::get_damage_poison(void) const { return _damage_poison_dice.roll(); }
const std::string& Tp::get_damage_poison_dice_str(void) const { return _damage_poison_dice_str; }
void Tp::set_damage_poison_dice(const std::string &v) { _damage_poison_dice = v; _damage_poison_dice_str = v; }

const Dice& Tp::get_health_initial_dice(void) const { return _health_initial_dice; }
const int Tp::get_health_initial(void) const { return _health_initial_dice.roll(); }
const std::string& Tp::get_health_initial_dice_str(void) const { return _health_initial_dice_str; }
void Tp::set_health_initial_dice(const std::string &v) { _health_initial_dice = v; _health_initial_dice_str = v; }

const Dice& Tp::gold_value_dice(void) const { return _gold_value_dice; }
const int Tp::cash(void) const { return _gold_value_dice.roll(); }
const std::string& Tp::gold_value_dice_str(void) const { return _gold_value_dice_str; }
void Tp::set_gold_value_dice(const std::string &v) { _gold_value_dice = v; _gold_value_dice_str = v; }

const Dice& Tp::resurrect_dice(void) const { return _resurrect_dice; }
const int Tp::resurrect(void) const { return _resurrect_dice.roll(); }
const std::string& Tp::resurrect_dice_str(void) const { return _resurrect_dice_str; }
void Tp::set_resurrect_dice(const std::string &v) { _resurrect_dice = v; _resurrect_dice_str = v; }

const std::string& Tp::light_color(void) const { return _light_color; }
const std::string& Tp::name(void) const { return _name; }
const std::string& Tp::on_death_do(void) const { return _on_death_do; }
const std::string& Tp::spawn_on_shoved(void) const { return _spawn_on_shoved; }
const std::string& Tp::str1(void) const { return _str1; }
const std::string& Tp::on_birth_do(void) const { return _on_birth_do; }
const std::string& Tp::on_use_do(void) const { return _on_use_do; }
const std::string& Tp::text_title(void) const { return _text_title; }
const std::string& Tp::str2(void) const { return _str2; }
const std::string& Tp::str3(void) const { return _str3; }
const std::string& Tp::str4(void) const { return _str4; }
const std::string& Tp::str5(void) const { return _str5; }
const std::string& Tp::str6(void) const { return _str6; }
const std::string& Tp::str7(void) const { return _str7; }
const std::string& Tp::long_text_description(void) const { return _long_text_description; }
const std::string& Tp::text_description(void) const { return _text_description; }
const std::string& Tp::text_hits(void) const { return _text_hits; }
const std::string& Tp::text_name(void) const { return _text_name; }
const std::string& Tp::short_text_name(void) const { return _short_text_name; }
const std::string& Tp::weapon_carry_anim(void) const { return _weapon_carry_anim; }
const std::string& Tp::gfx_anim_attack(void) const { return _gfx_anim_attack; }
float Tp::collision_attack_radius(void) const { return _collision_attack_radius; }
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
int Tp::is_chasm(void) const { return _is_chasm; }
int Tp::hunger_clock_freq_ms(void) const { return _hunger_clock_freq_ms; }
int Tp::internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
int Tp::internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
int Tp::is_able_to_change_levels(void) const { return _is_able_to_change_levels; }
int Tp::is_acid(void) const { return _is_acid; }
int Tp::is_acid_lover(void) const { return _is_acid_lover; }
int Tp::avoids_acid(void) const { return _avoids_acid; }
int Tp::is_active(void) const { return _is_active; }
int Tp::attack_eater(void) const { return _attack_eater; }
int Tp::attack_lunge(void) const { return _attack_lunge; }
int Tp::attack_shove(void) const { return _attack_shove; }
int Tp::attack_shove_chance_d1000(void) const { return _attack_shove_chance_d1000; }
int Tp::attackable_by_monst(void) const { return _attackable_by_monst; }
int Tp::attackable_by_player(void) const { return _attackable_by_player; }
int Tp::is_bag(void) const { return _is_bag; }
int Tp::is_bleeder(void) const { return _is_bleeder; }
int Tp::is_blood(void) const { return _is_blood; }
int Tp::is_blood_splatter(void) const { return _is_blood_splatter; }
int Tp::is_collect_as_keys(void) const { return _is_collect_as_keys; }
int Tp::is_collectable(void) const { return _is_collectable; }
int Tp::is_combustible(void) const { return _is_combustible; }
int Tp::on_death_is_corpse(void) const { return _on_death_is_corpse; }
int Tp::is_corridor(void) const { return _is_corridor; }
int Tp::is_cursor(void) const { return _is_cursor; }
int Tp::is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
int Tp::is_cursor_can_hover_over_but_needs_double_click(void) const { return _is_cursor_can_hover_over_but_needs_double_click; }
int Tp::is_cursor_path(void) const { return _is_cursor_path; }
int Tp::is_dead_on_shove(void) const { return _is_dead_on_shove; }
int Tp::is_deep_water(void) const { return _is_deep_water; }
int Tp::is_dirt(void) const { return _is_dirt; }
int Tp::is_door(void) const { return _is_door; }
int Tp::damage_doubled_from_acid(void) const { return _damage_doubled_from_acid; }
int Tp::damage_doubled_from_fire(void) const { return _damage_doubled_from_fire; }
int Tp::damage_doubled_from_water(void) const { return _damage_doubled_from_water; }
int Tp::is_droppable(void) const { return _is_droppable; }
int Tp::is_entrance(void) const { return _is_entrance; }
int Tp::is_ethereal(void) const { return _is_ethereal; }
int Tp::is_exit(void) const { return _is_exit; }
int Tp::is_explosion(void) const { return _is_explosion; }
int Tp::is_fire(void) const { return _is_fire; }
int Tp::avoids_fire(void) const { return _avoids_fire; }
int Tp::is_flammable(void) const { return _is_flammable; }
int Tp::is_floating(void) const { return _is_floating; }
int Tp::is_floor(void) const { return _is_floor; }
int Tp::is_floor_deco(void) const { return _is_floor_deco; }
int Tp::is_food(void) const { return _is_food; }
int Tp::is_generator(void) const { return _is_generator; }
int Tp::gfx_health_bar_shown(void) const { return _gfx_health_bar_shown; }
int Tp::gfx_health_bar_shown_only_when_injured(void) const { return _gfx_health_bar_shown_only_when_injured; }
int Tp::gfx_moves_ahead_shown(void) const { return _gfx_moves_ahead_shown; }
int Tp::is_gold(void) const { return _is_gold; }
int Tp::is_hazard(void) const { return _is_hazard; }
int Tp::is_hunger_insatiable(void) const { return _is_hunger_insatiable; }
int Tp::is_intelligent(void) const { return _is_intelligent; }
int Tp::is_interesting(void) const { return _is_interesting; }
int Tp::is_treasure_class_a(void) const { return _is_treasure_class_a; }
int Tp::is_treasure_class_b(void) const { return _is_treasure_class_b; }
int Tp::is_item_collected_as_gold(void) const { return _is_item_collected_as_gold; }
int Tp::is_item_eater(void) const { return _is_item_eater; }
int Tp::is_item_not_stackable(void) const { return _is_item_not_stackable; }
int Tp::is_jumper(void) const { return _is_jumper; }
int Tp::is_jumper_chance_d1000(void) const { return _is_jumper_chance_d1000; }
int Tp::is_jumper_distance(void) const { return _is_jumper_distance; }
int Tp::is_jumper_on_low_hp_chance_d1000(void) const { return _is_jumper_on_low_hp_chance_d1000; }
int Tp::is_key(void) const { return _is_key; }
int Tp::is_killed_on_hit_or_miss(void) const { return _is_killed_on_hit_or_miss; }
int Tp::is_killed_on_hitting(void) const { return _is_killed_on_hitting; }
int Tp::is_lava(void) const { return _is_lava; }
int Tp::is_light_blocker(void) const { return _is_light_blocker; }
int Tp::is_light_strength(void) const { return _is_light_strength; }
int Tp::is_loggable_for_important_stuff(void) const { return _is_loggable_for_important_stuff; }
int Tp::is_loggable_for_unimportant_stuff(void) const { return _is_loggable_for_unimportant_stuff; }
int Tp::is_meat(void) const { return _is_meat; }
int Tp::is_meat_eater(void) const { return _is_meat_eater; }
int Tp::is_monst(void) const { return _is_monst; }
int Tp::is_movable(void) const { return _is_movable; }
int Tp::is_movement_blocking_hard(void) const { return _is_movement_blocking_hard; }
int Tp::is_movement_blocking_soft(void) const { return _is_movement_blocking_soft; }
int Tp::is_msg(void) const { return _is_msg; }
int Tp::is_no_tile(void) const { return _is_no_tile; }
int Tp::on_death_is_open(void) const { return _on_death_is_open; }
int Tp::is_player(void) const { return _is_player; }
int Tp::is_potion(void) const { return _is_potion; }
int Tp::is_potion_eater(void) const { return _is_potion_eater; }
int Tp::is_projectile(void) const { return _is_projectile; }
int Tp::is_removable_if_out_of_slots(void) const { return _is_removable_if_out_of_slots; }
int Tp::is_resurrectable(void) const { return _is_resurrectable; }
int Tp::is_ripple(void) const { return _is_ripple; }
int Tp::is_rock(void) const { return _is_rock; }
int Tp::is_rrr1(void) const { return _is_rrr1; }
int Tp::is_rrr10(void) const { return _is_rrr10; }
int Tp::is_rrr11(void) const { return _is_rrr11; }
int Tp::is_rrr12(void) const { return _is_rrr12; }
int Tp::is_rrr13(void) const { return _is_rrr13; }
int Tp::is_rrr14(void) const { return _is_rrr14; }
int Tp::is_rrr15(void) const { return _is_rrr15; }
int Tp::is_rrr16(void) const { return _is_rrr16; }
int Tp::is_rrr17(void) const { return _is_rrr17; }
int Tp::is_rrr18(void) const { return _is_rrr18; }
int Tp::is_rrr19(void) const { return _is_rrr19; }
int Tp::is_rrr2(void) const { return _is_rrr2; }
int Tp::is_rrr20(void) const { return _is_rrr20; }
int Tp::is_rrr21(void) const { return _is_rrr21; }
int Tp::is_rrr22(void) const { return _is_rrr22; }
int Tp::is_rrr23(void) const { return _is_rrr23; }
int Tp::is_rrr24(void) const { return _is_rrr24; }
int Tp::is_rrr25(void) const { return _is_rrr25; }
int Tp::is_rrr26(void) const { return _is_rrr26; }
int Tp::is_rrr27(void) const { return _is_rrr27; }
int Tp::is_rrr28(void) const { return _is_rrr28; }
int Tp::is_rrr29(void) const { return _is_rrr29; }
int Tp::is_rrr3(void) const { return _is_rrr3; }
int Tp::is_rrr30(void) const { return _is_rrr30; }
int Tp::is_rrr31(void) const { return _is_rrr31; }
int Tp::is_rrr32(void) const { return _is_rrr32; }
int Tp::is_rrr33(void) const { return _is_rrr33; }
int Tp::is_rrr34(void) const { return _is_rrr34; }
int Tp::is_rrr35(void) const { return _is_rrr35; }
int Tp::is_rrr36(void) const { return _is_rrr36; }
int Tp::is_poison_lover(void) const { return _is_poison_lover; }
int Tp::damage_doubled_from_poison(void) const { return _damage_doubled_from_poison; }
int Tp::avoids_poison(void) const { return _avoids_poison; }
int Tp::is_rrr4(void) const { return _is_rrr4; }
int Tp::is_rrr40(void) const { return _is_rrr40; }
int Tp::is_poison(void) const { return _is_poison; }
int Tp::is_used_when_thrown(void) const { return _is_used_when_thrown; }
int Tp::is_used_automatically_when_selected(void) const { return _is_used_automatically_when_selected; }
int Tp::is_thrown_automatically_when_selected(void) const { return _is_thrown_automatically_when_selected; }
int Tp::is_extreme_hazard(void) const { return _is_extreme_hazard; }
int Tp::is_auto_collect_item(void) const { return _is_auto_collect_item; }
int Tp::attack_meat(void) const { return _attack_meat; }
int Tp::is_food_eater(void) const { return _is_food_eater; }
int Tp::is_item_effect_max_radius(void) const { return _is_item_effect_max_radius; }
int Tp::is_rrr5(void) const { return _is_rrr5; }
int Tp::is_item_effect_min_radius(void) const { return _is_item_effect_min_radius; }
int Tp::is_critical_to_level(void) const { return _is_critical_to_level; }
int Tp::is_able_to_fall(void) const { return _is_able_to_fall; }
int Tp::is_temporary_bag(void) const { return _is_temporary_bag; }
int Tp::is_treasure_class_c(void) const { return _is_treasure_class_c; }
int Tp::bag_item_height(void) const { return _bag_item_height; }
int Tp::bag_item_width(void) const { return _bag_item_width; }
int Tp::bag_height(void) const { return _bag_height; }
int Tp::bag_width(void) const { return _bag_width; }
int Tp::monst_size(void) const { return _monst_size; }
int Tp::is_rrr6(void) const { return _is_rrr6; }
int Tp::rarity(void) const { return _rarity; }
int Tp::gfx_is_rrr99(void) const { return _gfx_is_rrr99; }
int Tp::is_shown_uniquely_on_leftbar(void) const { return _is_shown_uniquely_on_leftbar; }
int Tp::is_stamina_check(void) const { return _is_stamina_check; }
int Tp::gfx_shown_in_bg(void) const { return _gfx_shown_in_bg; }
int Tp::on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
int Tp::is_steal_item_chance_d1000(void) const { return _is_steal_item_chance_d1000; }
int Tp::is_weapon_wielder(void) const { return _is_weapon_wielder; }
int Tp::is_item(void) const { return _is_item; }
int Tp::is_rrr7(void) const { return _is_rrr7; }
int Tp::is_rrr8(void) const { return _is_rrr8; }
int Tp::is_rrr9(void) const { return _is_rrr9; }
int Tp::is_secret_door(void) const { return _is_secret_door; }
int Tp::is_shovable(void) const { return _is_shovable; }
int Tp::is_shown_on_leftbar(void) const { return _is_shown_on_leftbar; }
int Tp::is_jelly(void) const { return _is_jelly; }
int Tp::is_jelly_baby(void) const { return _is_jelly_baby; }
int Tp::is_jelly_baby_eater(void) const { return _is_jelly_baby_eater; }
int Tp::is_jelly_eater(void) const { return _is_jelly_eater; }
int Tp::is_jelly_parent(void) const { return _is_jelly_parent; }
int Tp::is_smoke(void) const { return _is_smoke; }
int Tp::is_the_grid(void) const { return _is_the_grid; }
int Tp::is_throwable(void) const { return _is_throwable; }
int Tp::is_torch(void) const { return _is_torch; }
int Tp::is_treasure(void) const { return _is_treasure; }
int Tp::is_treasure_eater(void) const { return _is_treasure_eater; }
int Tp::is_undead(void) const { return _is_undead; }
int Tp::is_usable(void) const { return _is_usable; }
int Tp::is_wall(void) const { return _is_wall; }
int Tp::is_wall_deco(void) const { return _is_wall_deco; }
int Tp::is_water(void) const { return _is_water; }
int Tp::is_water_lover(void) const { return _is_water_lover; }
int Tp::avoids_water(void) const { return _avoids_water; }
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
int Tp::modifier_constitution(void) const { return _modifier_constitution; }
int Tp::modifier_attack(void) const { return _modifier_attack; }
int Tp::stats17(void) const { return _stats17; }
int Tp::throw_distance(void) const { return _throw_distance; }
int Tp::stamina(void) const { return _stamina; }
int Tp::modifier_defence(void) const { return _modifier_defence; }
int Tp::health_hunger_pct(void) const { return _health_hunger_pct; }
int Tp::health_starving_pct(void) const { return _health_starving_pct; }
int Tp::move_speed_ms(void) const { return _move_speed_ms; }
int Tp::modifier_strength(void) const { return _modifier_strength; }
int Tp::tick_catches_up_on_attack(void) const { return _tick_catches_up_on_attack; }
int Tp::tick_rate_tenths(void) const { return _tick_rate_tenths; }
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
void Tp::set_collision_attack_radius(float v) { _collision_attack_radius = v; }
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
void Tp::set_is_chasm(int v) { _is_chasm = v; }
void Tp::set_hunger_clock_freq_ms(int v) { _hunger_clock_freq_ms = v; }
void Tp::set_internal_has_dir_anim(int v) { _internal_has_dir_anim = v; }
void Tp::set_internal_has_hp_anim(int v) { _internal_has_hp_anim = v; }
void Tp::set_is_able_to_change_levels(int v) { _is_able_to_change_levels = v; }
void Tp::set_is_acid(int v) { _is_acid = v; }
void Tp::set_is_acid_lover(int v) { _is_acid_lover = v; }
void Tp::set_avoids_acid(int v) { _avoids_acid = v; }
void Tp::set_is_active(int v) { _is_active = v; }
void Tp::set_attack_eater(int v) { _attack_eater = v; }
void Tp::set_attack_lunge(int v) { _attack_lunge = v; }
void Tp::set_attack_shove(int v) { _attack_shove = v; }
void Tp::set_attack_shove_chance_d1000(int v) { _attack_shove_chance_d1000 = v; }
void Tp::set_attackable_by_monst(int v) { _attackable_by_monst = v; }
void Tp::set_attackable_by_player(int v) { _attackable_by_player = v; }
void Tp::set_is_bag(int v) { _is_bag = v; }
void Tp::set_is_bleeder(int v) { _is_bleeder = v; }
void Tp::set_is_blood(int v) { _is_blood = v; }
void Tp::set_is_blood_splatter(int v) { _is_blood_splatter = v; }
void Tp::set_is_collect_as_keys(int v) { _is_collect_as_keys = v; }
void Tp::set_is_collectable(int v) { _is_collectable = v; }
void Tp::set_is_combustible(int v) { _is_combustible = v; }
void Tp::set_on_death_is_corpse(int v) { _on_death_is_corpse = v; }
void Tp::set_is_corridor(int v) { _is_corridor = v; }
void Tp::set_is_cursor(int v) { _is_cursor = v; }
void Tp::set_is_cursor_can_hover_over(int v) { _is_cursor_can_hover_over = v; }
void Tp::set_is_cursor_can_hover_over_but_needs_double_click(int v) { _is_cursor_can_hover_over_but_needs_double_click = v; }
void Tp::set_is_cursor_path(int v) { _is_cursor_path = v; }
void Tp::set_is_dead_on_shove(int v) { _is_dead_on_shove = v; }
void Tp::set_is_deep_water(int v) { _is_deep_water = v; }
void Tp::set_is_dirt(int v) { _is_dirt = v; }
void Tp::set_is_door(int v) { _is_door = v; }
void Tp::set_damage_doubled_from_acid(int v) { _damage_doubled_from_acid = v; }
void Tp::set_damage_doubled_from_fire(int v) { _damage_doubled_from_fire = v; }
void Tp::set_damage_doubled_from_water(int v) { _damage_doubled_from_water = v; }
void Tp::set_is_droppable(int v) { _is_droppable = v; }
void Tp::set_is_entrance(int v) { _is_entrance = v; }
void Tp::set_is_ethereal(int v) { _is_ethereal = v; }
void Tp::set_is_exit(int v) { _is_exit = v; }
void Tp::set_is_explosion(int v) { _is_explosion = v; }
void Tp::set_is_fire(int v) { _is_fire = v; }
void Tp::set_avoids_fire(int v) { _avoids_fire = v; }
void Tp::set_is_flammable(int v) { _is_flammable = v; }
void Tp::set_is_floating(int v) { _is_floating = v; }
void Tp::set_is_floor(int v) { _is_floor = v; }
void Tp::set_is_floor_deco(int v) { _is_floor_deco = v; }
void Tp::set_is_food(int v) { _is_food = v; }
void Tp::set_is_generator(int v) { _is_generator = v; }
void Tp::set_gfx_health_bar_shown(int v) { _gfx_health_bar_shown = v; }
void Tp::set_gfx_health_bar_shown_only_when_injured(int v) { _gfx_health_bar_shown_only_when_injured = v; }
void Tp::set_gfx_moves_ahead_shown(int v) { _gfx_moves_ahead_shown = v; }
void Tp::set_is_gold(int v) { _is_gold = v; }
void Tp::set_is_hazard(int v) { _is_hazard = v; }
void Tp::set_is_hunger_insatiable(int v) { _is_hunger_insatiable = v; }
void Tp::set_is_intelligent(int v) { _is_intelligent = v; }
void Tp::set_is_interesting(int v) { _is_interesting = v; }
void Tp::set_is_treasure_class_a(int v) { _is_treasure_class_a = v; }
void Tp::set_is_treasure_class_b(int v) { _is_treasure_class_b = v; }
void Tp::set_is_item_collected_as_gold(int v) { _is_item_collected_as_gold = v; }
void Tp::set_is_item_eater(int v) { _is_item_eater = v; }
void Tp::set_is_item_not_stackable(int v) { _is_item_not_stackable = v; }
void Tp::set_is_jumper(int v) { _is_jumper = v; }
void Tp::set_is_jumper_chance_d1000(int v) { _is_jumper_chance_d1000 = v; }
void Tp::set_is_jumper_distance(int v) { _is_jumper_distance = v; }
void Tp::set_is_jumper_on_low_hp_chance_d1000(int v) { _is_jumper_on_low_hp_chance_d1000 = v; }
void Tp::set_is_key(int v) { _is_key = v; }
void Tp::set_is_killed_on_hit_or_miss(int v) { _is_killed_on_hit_or_miss = v; }
void Tp::set_is_killed_on_hitting(int v) { _is_killed_on_hitting = v; }
void Tp::set_is_lava(int v) { _is_lava = v; }
void Tp::set_is_light_blocker(int v) { _is_light_blocker = v; }
void Tp::set_is_light_strength(int v) { _is_light_strength = v; }
void Tp::set_is_loggable_for_important_stuff(int v) { _is_loggable_for_important_stuff = v; }
void Tp::set_is_loggable_for_unimportant_stuff(int v) { _is_loggable_for_unimportant_stuff = v; }
void Tp::set_is_meat(int v) { _is_meat = v; }
void Tp::set_is_meat_eater(int v) { _is_meat_eater = v; }
void Tp::set_is_monst(int v) { _is_monst = v; }
void Tp::set_is_movable(int v) { _is_movable = v; }
void Tp::set_is_movement_blocking_hard(int v) { _is_movement_blocking_hard = v; }
void Tp::set_is_movement_blocking_soft(int v) { _is_movement_blocking_soft = v; }
void Tp::set_is_msg(int v) { _is_msg = v; }
void Tp::set_is_no_tile(int v) { _is_no_tile = v; }
void Tp::set_on_death_is_open(int v) { _on_death_is_open = v; }
void Tp::set_is_player(int v) { _is_player = v; }
void Tp::set_is_potion(int v) { _is_potion = v; }
void Tp::set_is_potion_eater(int v) { _is_potion_eater = v; }
void Tp::set_is_projectile(int v) { _is_projectile = v; }
void Tp::set_is_removable_if_out_of_slots(int v) { _is_removable_if_out_of_slots = v; }
void Tp::set_is_resurrectable(int v) { _is_resurrectable = v; }
void Tp::set_is_ripple(int v) { _is_ripple = v; }
void Tp::set_is_rock(int v) { _is_rock = v; }
void Tp::set_is_rrr1(int v) { _is_rrr1 = v; }
void Tp::set_is_rrr10(int v) { _is_rrr10 = v; }
void Tp::set_is_rrr11(int v) { _is_rrr11 = v; }
void Tp::set_is_rrr12(int v) { _is_rrr12 = v; }
void Tp::set_is_rrr13(int v) { _is_rrr13 = v; }
void Tp::set_is_rrr14(int v) { _is_rrr14 = v; }
void Tp::set_is_rrr15(int v) { _is_rrr15 = v; }
void Tp::set_is_rrr16(int v) { _is_rrr16 = v; }
void Tp::set_is_rrr17(int v) { _is_rrr17 = v; }
void Tp::set_is_rrr18(int v) { _is_rrr18 = v; }
void Tp::set_is_rrr19(int v) { _is_rrr19 = v; }
void Tp::set_is_rrr2(int v) { _is_rrr2 = v; }
void Tp::set_is_rrr20(int v) { _is_rrr20 = v; }
void Tp::set_is_rrr21(int v) { _is_rrr21 = v; }
void Tp::set_is_rrr22(int v) { _is_rrr22 = v; }
void Tp::set_is_rrr23(int v) { _is_rrr23 = v; }
void Tp::set_is_rrr24(int v) { _is_rrr24 = v; }
void Tp::set_is_rrr25(int v) { _is_rrr25 = v; }
void Tp::set_is_rrr26(int v) { _is_rrr26 = v; }
void Tp::set_is_rrr27(int v) { _is_rrr27 = v; }
void Tp::set_is_rrr28(int v) { _is_rrr28 = v; }
void Tp::set_is_rrr29(int v) { _is_rrr29 = v; }
void Tp::set_is_rrr3(int v) { _is_rrr3 = v; }
void Tp::set_is_rrr30(int v) { _is_rrr30 = v; }
void Tp::set_is_rrr31(int v) { _is_rrr31 = v; }
void Tp::set_is_rrr32(int v) { _is_rrr32 = v; }
void Tp::set_is_rrr33(int v) { _is_rrr33 = v; }
void Tp::set_is_rrr34(int v) { _is_rrr34 = v; }
void Tp::set_is_rrr35(int v) { _is_rrr35 = v; }
void Tp::set_is_rrr36(int v) { _is_rrr36 = v; }
void Tp::set_is_poison_lover(int v) { _is_poison_lover = v; }
void Tp::set_damage_doubled_from_poison(int v) { _damage_doubled_from_poison = v; }
void Tp::set_avoids_poison(int v) { _avoids_poison = v; }
void Tp::set_is_rrr4(int v) { _is_rrr4 = v; }
void Tp::set_is_rrr40(int v) { _is_rrr40 = v; }
void Tp::set_is_poison(int v) { _is_poison = v; }
void Tp::set_is_used_when_thrown(int v) { _is_used_when_thrown = v; }
void Tp::set_is_used_automatically_when_selected(int v) { _is_used_automatically_when_selected = v; }
void Tp::set_is_thrown_automatically_when_selected(int v) { _is_thrown_automatically_when_selected = v; }
void Tp::set_is_extreme_hazard(int v) { _is_extreme_hazard = v; }
void Tp::set_is_auto_collect_item(int v) { _is_auto_collect_item = v; }
void Tp::set_attack_meat(int v) { _attack_meat = v; }
void Tp::set_is_food_eater(int v) { _is_food_eater = v; }
void Tp::set_is_item_effect_max_radius(int v) { _is_item_effect_max_radius = v; }
void Tp::set_is_rrr5(int v) { _is_rrr5 = v; }
void Tp::set_is_item_effect_min_radius(int v) { _is_item_effect_min_radius = v; }
void Tp::set_is_critical_to_level(int v) { _is_critical_to_level = v; }
void Tp::set_is_able_to_fall(int v) { _is_able_to_fall = v; }
void Tp::set_is_temporary_bag(int v) { _is_temporary_bag = v; }
void Tp::set_is_treasure_class_c(int v) { _is_treasure_class_c = v; }
void Tp::set_bag_item_height(int v) { _bag_item_height = v; }
void Tp::set_bag_item_width(int v) { _bag_item_width = v; }
void Tp::set_bag_height(int v) { _bag_height = v; }
void Tp::set_bag_width(int v) { _bag_width = v; }
void Tp::set_monst_size(int v) { _monst_size = v; }
void Tp::set_is_rrr6(int v) { _is_rrr6 = v; }
void Tp::set_rarity(int v) { _rarity = v; }
void Tp::set_gfx_is_rrr99(int v) { _gfx_is_rrr99 = v; }
void Tp::set_is_shown_uniquely_on_leftbar(int v) { _is_shown_uniquely_on_leftbar = v; }
void Tp::set_is_stamina_check(int v) { _is_stamina_check = v; }
void Tp::set_gfx_shown_in_bg(int v) { _gfx_shown_in_bg = v; }
void Tp::set_on_death_drop_all_items(int v) { _on_death_drop_all_items = v; }
void Tp::set_is_steal_item_chance_d1000(int v) { _is_steal_item_chance_d1000 = v; }
void Tp::set_is_weapon_wielder(int v) { _is_weapon_wielder = v; }
void Tp::set_is_item(int v) { _is_item = v; }
void Tp::set_is_rrr7(int v) { _is_rrr7 = v; }
void Tp::set_is_rrr8(int v) { _is_rrr8 = v; }
void Tp::set_is_rrr9(int v) { _is_rrr9 = v; }
void Tp::set_is_secret_door(int v) { _is_secret_door = v; }
void Tp::set_is_shovable(int v) { _is_shovable = v; }
void Tp::set_is_shown_on_leftbar(int v) { _is_shown_on_leftbar = v; }
void Tp::set_is_jelly(int v) { _is_jelly = v; }
void Tp::set_is_jelly_baby(int v) { _is_jelly_baby = v; }
void Tp::set_is_jelly_baby_eater(int v) { _is_jelly_baby_eater = v; }
void Tp::set_is_jelly_eater(int v) { _is_jelly_eater = v; }
void Tp::set_is_jelly_parent(int v) { _is_jelly_parent = v; }
void Tp::set_is_smoke(int v) { _is_smoke = v; }
void Tp::set_is_the_grid(int v) { _is_the_grid = v; }
void Tp::set_is_throwable(int v) { _is_throwable = v; }
void Tp::set_is_torch(int v) { _is_torch = v; }
void Tp::set_is_treasure(int v) { _is_treasure = v; }
void Tp::set_is_treasure_eater(int v) { _is_treasure_eater = v; }
void Tp::set_is_undead(int v) { _is_undead = v; }
void Tp::set_is_usable(int v) { _is_usable = v; }
void Tp::set_is_wall(int v) { _is_wall = v; }
void Tp::set_is_wall_deco(int v) { _is_wall_deco = v; }
void Tp::set_is_water(int v) { _is_water = v; }
void Tp::set_is_water_lover(int v) { _is_water_lover = v; }
void Tp::set_avoids_water(int v) { _avoids_water = v; }
void Tp::set_is_weapon(int v) { _is_weapon = v; }
void Tp::set_light_color(const std::string &v) { _light_color = v; }
void Tp::set_name(const std::string &v) { _name = v; }
void Tp::set_normal_placement_rules(int v) { _normal_placement_rules = v; }
void Tp::set_on_birth_do(const std::string &v) { _on_birth_do = v; }
void Tp::set_on_use_do(const std::string &v) { _on_use_do = v; }
void Tp::set_on_death_do(const std::string &v) { _on_death_do = v; }
void Tp::set_spawn_on_shoved(const std::string &v) { _spawn_on_shoved = v; }
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
void Tp::set_modifier_constitution(int v) { _modifier_constitution = v; }
void Tp::set_modifier_attack(int v) { _modifier_attack = v; }
void Tp::set_stats17(int v) { _stats17 = v; }
void Tp::set_throw_distance(int v) { _throw_distance = v; }
void Tp::set_stamina(int v) { _stamina = v; }
void Tp::set_modifier_defence(int v) { _modifier_defence = v; }
void Tp::set_health_hunger_pct(int v) { _health_hunger_pct = v; }
void Tp::set_health_starving_pct(int v) { _health_starving_pct = v; }
void Tp::set_move_speed_ms(int v) { _move_speed_ms = v; }
void Tp::set_modifier_strength(int v) { _modifier_strength = v; }
void Tp::set_str1(const std::string &v) { _str1 = v; }
void Tp::set_str2(const std::string &v) { _str2 = v; }
void Tp::set_str3(const std::string &v) { _str3 = v; }
void Tp::set_str4(const std::string &v) { _str4 = v; }
void Tp::set_str5(const std::string &v) { _str5 = v; }
void Tp::set_str6(const std::string &v) { _str6 = v; }
void Tp::set_str7(const std::string &v) { _str7 = v; }
void Tp::set_long_text_description(const std::string &v) { _long_text_description = v; }
void Tp::set_text_a_or_an(const std::string &v) { _text_a_or_an = v; }
void Tp::set_text_description(const std::string &v) { _text_description = v; }
void Tp::set_text_hits(const std::string &v) { _text_hits = v; }
void Tp::set_text_name(const std::string &v) { _text_name = v; }
void Tp::set_short_text_name(const std::string &v) { _short_text_name = v; }
void Tp::set_text_title(const std::string &v) { _text_title = v; }
void Tp::set_tick_catches_up_on_attack(int v) { _tick_catches_up_on_attack = v; }
void Tp::set_tick_rate_tenths(int v) { _tick_rate_tenths = v; }
void Tp::set_weapon_carry_anim(const std::string &v) { _weapon_carry_anim = v; }
void Tp::set_weapon_damage(int v) { _weapon_damage = v; }
void Tp::set_gfx_anim_attack(const std::string &v) { _gfx_anim_attack = v; }
void Tp::set_weapon_use_delay_hundredths(int v) { _weapon_use_delay_hundredths = v; }
void Tp::set_weapon_use_distance(int v) { _weapon_use_distance = v; }
void Tp::set_z_depth(int v) { z_depth = v; }
void Tp::set_z_prio(int v) { z_prio = v; }
