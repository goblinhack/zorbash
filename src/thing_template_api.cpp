//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.h"
#include "my_dice.h"
#include "my_level.h"
#include "my_sys.h"
#include "my_thing_template.h"
#include "my_tile.h"

//
// Dice
//
const Dice &       Tp::on_idle_dice(void) const { return _on_idle_dice; }
const int          Tp::idle_tick(void) const { return _on_idle_dice.roll(); }
const std::string &Tp::on_idle_dice_str(void) const { return _on_idle_dice_str; }
void               Tp::set_on_idle_dice(const std::string &v)
{
  _on_idle_dice     = v;
  _on_idle_dice_str = v;
}

const Dice &       Tp::lifespan_dice(void) const { return _lifespan_dice; }
const int          Tp::lifespan(void) const { return _lifespan_dice.roll(); }
const std::string &Tp::lifespan_dice_str(void) const { return _lifespan_dice_str; }
void               Tp::set_lifespan_dice(const std::string &v)
{
  _lifespan_dice     = v;
  _lifespan_dice_str = v;
}

const Dice &       Tp::nutrition_dice(void) const { return _nutrition_dice; }
const int          Tp::nutrition(void) const { return _nutrition_dice.roll(); }
const std::string &Tp::nutrition_dice_str(void) const { return _nutrition_dice_str; }
void               Tp::set_nutrition_dice(const std::string &v)
{
  _nutrition_dice     = v;
  _nutrition_dice_str = v;
}

const Dice &       Tp::get_damage_melee_dice(void) const { return _damage_melee_dice; }
const int          Tp::get_damage_melee(void) const { return _damage_melee_dice.roll(); }
const std::string &Tp::get_damage_melee_dice_str(void) const { return _damage_melee_dice_str; }
void               Tp::set_damage_melee_dice(const std::string &v)
{
  _damage_melee_dice     = v;
  _damage_melee_dice_str = v;
}

const Dice &       Tp::get_damage_poison_dice(void) const { return _damage_poison_dice; }
const int          Tp::get_damage_poison(void) const { return _damage_poison_dice.roll(); }
const std::string &Tp::get_damage_poison_dice_str(void) const { return _damage_poison_dice_str; }
void               Tp::set_damage_poison_dice(const std::string &v)
{
  _damage_poison_dice     = v;
  _damage_poison_dice_str = v;
}

const Dice &       Tp::get_damage_crush_dice(void) const { return _damage_crush_dice; }
const int          Tp::get_damage_crush(void) const { return _damage_crush_dice.roll(); }
const std::string &Tp::get_damage_crush_dice_str(void) const { return _damage_crush_dice_str; }
void               Tp::set_damage_crush_dice(const std::string &v)
{
  _damage_crush_dice     = v;
  _damage_crush_dice_str = v;
}

const Dice &       Tp::get_damage_bite_dice(void) const { return _damage_bite_dice; }
const int          Tp::get_damage_bite(void) const { return _damage_bite_dice.roll(); }
const std::string &Tp::get_damage_bite_dice_str(void) const { return _damage_bite_dice_str; }
void               Tp::set_damage_bite_dice(const std::string &v)
{
  _damage_bite_dice     = v;
  _damage_bite_dice_str = v;
}

const Dice &       Tp::get_damage_swallow_dice(void) const { return _damage_swallow_dice; }
const int          Tp::get_damage_swallow(void) const { return _damage_swallow_dice.roll(); }
const std::string &Tp::get_damage_swallow_dice_str(void) const { return _damage_swallow_dice_str; }
void               Tp::set_damage_swallow_dice(const std::string &v)
{
  _damage_swallow_dice     = v;
  _damage_swallow_dice_str = v;
}

const Dice &       Tp::get_health_initial_dice(void) const { return _health_initial_dice; }
const int          Tp::get_health_initial(void) const { return _health_initial_dice.roll(); }
const std::string &Tp::get_health_initial_dice_str(void) const { return _health_initial_dice_str; }
void               Tp::set_health_initial_dice(const std::string &v)
{
  _health_initial_dice     = v;
  _health_initial_dice_str = v;
}

const Dice &       Tp::gold_value_dice(void) const { return _gold_value_dice; }
const int          Tp::cash(void) const { return _gold_value_dice.roll(); }
const std::string &Tp::gold_value_dice_str(void) const { return _gold_value_dice_str; }
void               Tp::set_gold_value_dice(const std::string &v)
{
  _gold_value_dice     = v;
  _gold_value_dice_str = v;
}

const Dice &       Tp::resurrect_dice(void) const { return _resurrect_dice; }
const int          Tp::resurrect(void) const { return _resurrect_dice.roll(); }
const std::string &Tp::resurrect_dice_str(void) const { return _resurrect_dice_str; }
void               Tp::set_resurrect_dice(const std::string &v)
{
  _resurrect_dice     = v;
  _resurrect_dice_str = v;
}

const std::string &Tp::gfx_anim_attack(void) const { return _gfx_anim_attack; }
const std::string &Tp::laser_name(void) const { return _laser_name; }
const std::string &Tp::light_color(void) const { return _light_color; }
const std::string &Tp::long_text_description(void) const { return _long_text_description; }
const std::string &Tp::name(void) const { return _name; }
const std::string &Tp::on_birth_do(void) const { return _on_birth_do; }
const std::string &Tp::on_you_bite_attack_do(void) const { return _on_you_bite_attack_do; }
const std::string &Tp::on_born_do(void) const { return _on_born_do; }
const std::string &Tp::on_death_do(void) const { return _on_death_do; }
const std::string &Tp::on_enchant_do(void) const { return _on_enchant_do; }
const std::string &Tp::on_fall_do(void) const { return _on_fall_do; }
const std::string &Tp::on_you_are_on_fire_do(void) const { return _on_you_are_on_fire_do; }
const std::string &Tp::on_firing_at_something_do(void) const { return _on_firing_at_something_do; }
const std::string &Tp::on_you_are_hit_do(void) const { return _on_you_are_hit_do; }
const std::string &Tp::on_lifespan_do(void) const { return _on_lifespan_do; }
const std::string &Tp::on_you_miss_do_do(void) const { return _on_you_miss_do_do; }
const std::string &Tp::on_move_do(void) const { return _on_move_do; }
const std::string &Tp::on_open_do(void) const { return _on_open_do; }
const std::string &Tp::on_tick_do(void) const { return _on_tick_do; }
const std::string &Tp::on_use_do(void) const { return _on_use_do; }
const std::string &Tp::projectile_name(void) const { return _projectile_name; }
const std::string &Tp::short_text_name(void) const { return _short_text_name; }
const std::string &Tp::spawn_on_shoved(void) const { return _spawn_on_shoved; }
const std::string &Tp::str1(void) const { return _str1; }
const std::string &Tp::str2(void) const { return _str2; }
const std::string &Tp::str4(void) const { return _str4; }
const std::string &Tp::str5(void) const { return _str5; }
const std::string &Tp::text_description(void) const { return _text_description; }
const std::string &Tp::text_enchant(void) const { return _text_enchant; }
const std::string &Tp::text_hits(void) const { return _text_hits; }
const std::string &Tp::text_name(void) const { return _text_name; }
const std::string &Tp::text_skill(void) const { return _text_skill; }
const std::string &Tp::text_debuff(void) const { return _text_debuff; }
const std::string &Tp::text_buff(void) const { return _text_buff; }
const std::string &Tp::text_title(void) const { return _text_title; }
const std::string &Tp::text_unused(void) const { return _text_unused; }
const std::string &Tp::weapon_carry_anim(void) const { return _weapon_carry_anim; }
float              Tp::collision_attack_radius(void) const { return _collision_attack_radius; }
float              Tp::collision_radius(void) const { return _collision_radius; }
int                Tp::ai_avoid_distance(void) const { return _ai_avoid_distance; }
int                Tp::ai_resent_count(void) const { return _ai_resent_count; }
int                Tp::ai_obstacle(void) const { return _ai_obstacle; }
int                Tp::ai_scent_distance(void) const { return _ai_scent_distance; }
int                Tp::ai_vision_distance(void) const { return _ai_vision_distance; }
int                Tp::attack_eater(void) const { return _attack_eater; }
int                Tp::attack_humanoid(void) const { return _attack_humanoid; }
int                Tp::attack_living(void) const { return _attack_living; }
int                Tp::attack_lunge(void) const { return _attack_lunge; }
int                Tp::attack_meat(void) const { return _attack_meat; }
int                Tp::ai_shove_chance_d1000(void) const { return _ai_shove_chance_d1000; }
int                Tp::ai_unprovoked_attack_chance_d1000(void) const { return _ai_unprovoked_attack_chance_d1000; }
int                Tp::ai_is_able_to_shove(void) const { return _ai_is_able_to_shove; }
int                Tp::blast_max_radius(void) const { return _blast_max_radius; }
int                Tp::blast_min_radius(void) const { return _blast_min_radius; }
int                Tp::blit_bot_off(void) const { return _blit_bot_off; }
int                Tp::blit_left_off(void) const { return _blit_left_off; }
int                Tp::blit_right_off(void) const { return _blit_right_off; }
int                Tp::blit_top_off(void) const { return _blit_top_off; }
int                Tp::capacity_height(void) const { return _capacity_height; }
int                Tp::capacity_width(void) const { return _capacity_width; }
int                Tp::charge_count(void) const { return _charge_count; }
int                Tp::collision_attack(void) const { return _collision_attack; }
int                Tp::collision_box(void) const { return _collision_box; }
int                Tp::collision_check(void) const { return _collision_check; }
int                Tp::collision_circle(void) const { return _collision_circle; }
int                Tp::collision_hit_priority(void) const { return _collision_hit_priority; }
int                Tp::environ_damage_doubled_from_acid(void) const { return _environ_damage_doubled_from_acid; }
int                Tp::environ_damage_doubled_from_fire(void) const { return _environ_damage_doubled_from_fire; }
int                Tp::environ_damage_doubled_from_poison(void) const { return _environ_damage_doubled_from_poison; }
int                Tp::environ_damage_doubled_from_water(void) const { return _environ_damage_doubled_from_water; }
int                Tp::enchant_level(void) const { return _enchant_level; }
int                Tp::enchant_max(void) const { return _enchant_max; }
int                Tp::gfx_an_animation_only(void) const { return _gfx_an_animation_only; }
int                Tp::gfx_animated_can_hflip(void) const { return _gfx_animated_can_hflip; }
int                Tp::gfx_animated_can_vflip(void) const { return _gfx_animated_can_vflip; }
int                Tp::gfx_animated_no_dir(void) const { return _gfx_animated_no_dir; }
int                Tp::gfx_animated(void) const { return _gfx_animated; }
int                Tp::gfx_attack_anim(void) const { return _gfx_attack_anim; }
int                Tp::gfx_bounce_always(void) const { return _gfx_bounce_always; }
int                Tp::gfx_bounce_on_move(void) const { return _gfx_bounce_on_move; }
int                Tp::gfx_dead_anim(void) const { return _gfx_dead_anim; }
int                Tp::gfx_flickers(void) const { return _gfx_flickers; }
int                Tp::gfx_glows(void) const { return _gfx_glows; }
int                Tp::gfx_health_bar_autohide(void) const { return _gfx_health_bar_autohide; }
int                Tp::gfx_health_bar_shown(void) const { return _gfx_health_bar_shown; }
int                Tp::gfx_long_shadow_caster(void) const { return _gfx_long_shadow_caster; }
int                Tp::gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
int                Tp::gfx_oversized_and_on_floor(void) const { return _gfx_oversized_and_on_floor; }
int                Tp::gfx_short_shadow_caster(void) const { return _gfx_short_shadow_caster; }
int                Tp::gfx_shown_in_bg(void) const { return _gfx_shown_in_bg; }
int                Tp::gfx_show_outlined(void) const { return _gfx_show_outlined; }
int                Tp::gfx_solid_shadow(void) const { return _gfx_solid_shadow; }
int                Tp::gfx_very_short_shadow_caster(void) const { return _gfx_very_short_shadow_caster; }
int                Tp::gfx_water(void) const { return _gfx_water; }
int                Tp::gfx_weapon_carry_anim(void) const { return _gfx_weapon_carry_anim; }
int                Tp::environ_dislikes_acid(void) const { return _environ_dislikes_acid; }
int                Tp::environ_dislikes_fire(void) const { return _environ_dislikes_fire; }
int                Tp::environ_dislikes_poison(void) const { return _environ_dislikes_poison; }
int                Tp::environ_dislikes_water(void) const { return _environ_dislikes_water; }
int                Tp::health_hunger_pct(void) const { return _health_hunger_pct; }
int                Tp::health_starving_pct(void) const { return _health_starving_pct; }
int                Tp::internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
int                Tp::internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
int                Tp::is_able_to_change_levels(void) const { return _is_able_to_change_levels; }
int                Tp::is_able_to_fall(void) const { return _is_able_to_fall; }
int                Tp::is_able_to_fire_at(void) const { return _is_able_to_fire_at; }
int                Tp::ai_is_able_to_see_through_doors(void) const { return _ai_is_able_to_see_through_doors; }
int                Tp::ai_is_able_to_walk_through_walls(void) const { return _ai_is_able_to_walk_through_walls; }
int                Tp::environ_loves_acid(void) const { return _environ_loves_acid; }
int                Tp::is_acid(void) const { return _is_acid; }
int                Tp::is_alive_on_end_of_anim(void) const { return _is_alive_on_end_of_anim; }
int                Tp::is_always_hit(void) const { return _is_always_hit; }
int                Tp::is_ascend_dungeon(void) const { return _is_ascend_dungeon; }
int                Tp::is_ascend_sewer(void) const { return _is_ascend_sewer; }
int                Tp::is_attackable_by_monst(void) const { return _is_attackable_by_monst; }
int                Tp::is_attackable_by_player(void) const { return _is_attackable_by_player; }
int                Tp::is_auto_collect_item(void) const { return _is_auto_collect_item; }
int                Tp::is_bag_item_container(void) const { return _is_bag_item_container; }
int                Tp::is_bag_item_not_stackable(void) const { return _is_bag_item_not_stackable; }
int                Tp::is_bag_item(void) const { return _is_bag_item; }
int                Tp::is_bag(void) const { return _is_bag; }
int                Tp::is_barrel(void) const { return _is_barrel; }
int                Tp::is_bleeder(void) const { return _is_bleeder; }
int                Tp::is_blood_splatter(void) const { return _is_blood_splatter; }
int                Tp::is_blood(void) const { return _is_blood; }
int                Tp::is_bones(void) const { return _is_bones; }
int                Tp::is_brazier(void) const { return _is_brazier; }
int                Tp::is_bridge(void) const { return _is_bridge; }
int                Tp::is_burnable(void) const { return _is_burnable; }
int                Tp::is_carrier_of_treasure_class_a(void) const { return _is_carrier_of_treasure_class_a; }
int                Tp::is_carrier_of_treasure_class_b(void) const { return _is_carrier_of_treasure_class_b; }
int                Tp::is_carrier_of_treasure_class_c(void) const { return _is_carrier_of_treasure_class_c; }
int                Tp::is_chasm(void) const { return _is_chasm; }
int                Tp::is_collectable(void) const { return _is_collectable; }
int                Tp::is_collect_as_keys(void) const { return _is_collect_as_keys; }
int                Tp::is_collected_as_gold(void) const { return _is_collected_as_gold; }
int                Tp::is_combustible(void) const { return _is_combustible; }
int                Tp::is_corpse_on_death(void) const { return _is_corpse_on_death; }
int                Tp::is_corridor(void) const { return _is_corridor; }
int                Tp::is_critical_to_level(void) const { return _is_critical_to_level; }
int                Tp::is_cursor_can_hover_over_x2_click(void) const { return _is_cursor_can_hover_over_x2_click; }
int                Tp::is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
int                Tp::is_cursor_path(void) const { return _is_cursor_path; }
int                Tp::is_cursor(void) const { return _is_cursor; }
int                Tp::is_dead_on_end_of_anim(void) const { return _is_dead_on_end_of_anim; }
int                Tp::is_dead_on_shove(void) const { return _is_dead_on_shove; }
int                Tp::is_debug_path(void) const { return _is_debug_path; }
int                Tp::is_debug_type(void) const { return _is_debug_type; }
int                Tp::is_deep_water(void) const { return _is_deep_water; }
int                Tp::is_descend_dungeon(void) const { return _is_descend_dungeon; }
int                Tp::is_descend_sewer(void) const { return _is_descend_sewer; }
int                Tp::is_described_when_hovering_over(void) const { return _is_described_when_hovering_over; }
int                Tp::is_dirt(void) const { return _is_dirt; }
int                Tp::is_door(void) const { return _is_door; }
int                Tp::is_droppable(void) const { return _is_droppable; }
int                Tp::is_dry_grass(void) const { return _is_dry_grass; }
int                Tp::is_enchantable(void) const { return _is_enchantable; }
int                Tp::is_enchantstone(void) const { return _is_enchantstone; }
int                Tp::is_engulf_chance_d1000(void) const { return _is_engulf_chance_d1000; }
int                Tp::is_engulfer(void) const { return _is_engulfer; }
int                Tp::is_ethereal_minion_generator(void) const { return _is_ethereal_minion_generator; }
int                Tp::is_ethereal(void) const { return _is_ethereal; }
int                Tp::is_explosion(void) const { return _is_explosion; }
int                Tp::is_cursor_path_hazard_for_player(void) const { return _is_cursor_path_hazard_for_player; }
int                Tp::is_fearless(void) const { return _is_fearless; }
int                Tp::is_fire(void) const { return _is_fire; }
int                Tp::is_floating(void) const { return _is_floating; }
int                Tp::is_floor_deco(void) const { return _is_floor_deco; }
int                Tp::is_floor(void) const { return _is_floor; }
int                Tp::is_foilage(void) const { return _is_foilage; }
int                Tp::is_food_eater(void) const { return _is_food_eater; }
int                Tp::is_food(void) const { return _is_food; }
int                Tp::is_gold(void) const { return _is_gold; }
int                Tp::is_hazard(void) const { return _is_hazard; }
int                Tp::is_health_booster(void) const { return _is_health_booster; }
int                Tp::is_hittable(void) const { return _is_hittable; }
int                Tp::is_humanoid(void) const { return _is_humanoid; }
int                Tp::is_hunger_insatiable(void) const { return _is_hunger_insatiable; }
int                Tp::is_indestructible(void) const { return _is_indestructible; }
int                Tp::is_intelligent(void) const { return _is_intelligent; }
int                Tp::is_interesting(void) const { return _is_interesting; }
int                Tp::is_item_carrier(void) const { return _is_item_carrier; }
int                Tp::ai_is_item_collector(void) const { return _ai_is_item_collector; }
int                Tp::is_item_eater(void) const { return _is_item_eater; }
int                Tp::is_item(void) const { return _is_item; }
int                Tp::is_jelly_baby_eater(void) const { return _is_jelly_baby_eater; }
int                Tp::is_jelly_baby(void) const { return _is_jelly_baby; }
int                Tp::is_jelly_eater(void) const { return _is_jelly_eater; }
int                Tp::is_jelly_parent(void) const { return _is_jelly_parent; }
int                Tp::is_jelly(void) const { return _is_jelly; }
int                Tp::ai_random_jump_chance_d1000(void) const { return _ai_random_jump_chance_d1000; }
int                Tp::ai_is_able_to_jump_distance(void) const { return _ai_is_able_to_jump_distance; }
int Tp::ai_is_able_to_jump_on_low_hp_chance_d1000(void) const { return _ai_is_able_to_jump_on_low_hp_chance_d1000; }
int Tp::ai_is_able_to_jump(void) const { return _ai_is_able_to_jump; }
int Tp::ai_is_able_to_collect_keys(void) const { return _ai_is_able_to_collect_keys; }
int Tp::is_key(void) const { return _is_key; }
int Tp::is_destroyed_on_hit_or_miss(void) const { return _is_destroyed_on_hit_or_miss; }
int Tp::is_destroyed_on_hitting(void) const { return _is_destroyed_on_hitting; }
int Tp::is_laser(void) const { return _is_laser; }
int Tp::is_lava(void) const { return _is_lava; }
int Tp::is_light_blocker(void) const { return _is_light_blocker; }
int Tp::is_living(void) const { return _is_living; }
int Tp::is_loggable(void) const { return _is_loggable; }
int Tp::is_meat_eater(void) const { return _is_meat_eater; }
int Tp::is_meat(void) const { return _is_meat; }
int Tp::is_minion_generator(void) const { return _is_minion_generator; }
int Tp::is_minion(void) const { return _is_minion; }
int Tp::is_monst(void) const { return _is_monst; }
int Tp::is_moveable(void) const { return _is_moveable; }
int Tp::is_obs_destructable(void) const { return _is_obs_destructable; }
int Tp::is_obs_wall_or_door(void) const { return _is_obs_wall_or_door; }
int Tp::is_msg(void) const { return _is_msg; }
int Tp::is_no_tile(void) const { return _is_no_tile; }
int Tp::is_openable(void) const { return _is_openable; }
int Tp::is_player(void) const { return _is_player; }
int Tp::is_poison(void) const { return _is_poison; }
int Tp::is_potion_eater(void) const { return _is_potion_eater; }
int Tp::is_potion(void) const { return _is_potion; }
int Tp::is_projectile(void) const { return _is_projectile; }
int Tp::is_removeable_if_out_of_slots(void) const { return _is_removeable_if_out_of_slots; }
int Tp::is_resurrectable(void) const { return _is_resurrectable; }
int Tp::is_ripple(void) const { return _is_ripple; }
int Tp::is_rock(void) const { return _is_rock; }
int Tp::unused_flag10(void) const { return _unused_flag10; }
int Tp::unused_flag11(void) const { return _unused_flag11; }
int Tp::unused_flag12(void) const { return _unused_flag12; }
int Tp::unused_flag13(void) const { return _unused_flag13; }
int Tp::unused_flag14(void) const { return _unused_flag14; }
int Tp::unused_flag15(void) const { return _unused_flag15; }
int Tp::unused_flag16(void) const { return _unused_flag16; }
int Tp::unused_flag17(void) const { return _unused_flag17; }
int Tp::unused_flag18(void) const { return _unused_flag18; }
int Tp::unused_flag19(void) const { return _unused_flag19; }
int Tp::unused_flag1(void) const { return _unused_flag1; }
int Tp::unused_flag20(void) const { return _unused_flag20; }
int Tp::unused_flag21(void) const { return _unused_flag21; }
int Tp::unused_flag22(void) const { return _unused_flag22; }
int Tp::unused_flag23(void) const { return _unused_flag23; }
int Tp::unused_flag24(void) const { return _unused_flag24; }
int Tp::unused_flag25(void) const { return _unused_flag25; }
int Tp::unused_flag26(void) const { return _unused_flag26; }
int Tp::unused_flag27(void) const { return _unused_flag27; }
int Tp::unused_flag28(void) const { return _unused_flag28; }
int Tp::unused_flag29(void) const { return _unused_flag29; }
int Tp::unused_flag2(void) const { return _unused_flag2; }
int Tp::unused_flag30(void) const { return _unused_flag30; }
int Tp::unused_flag31(void) const { return _unused_flag31; }
int Tp::unused_flag32(void) const { return _unused_flag32; }
int Tp::is_buff(void) const { return _is_buff; }
int Tp::is_debuff(void) const { return _is_debuff; }
int Tp::attack_undead(void) const { return _attack_undead; }
int Tp::is_blood_eater(void) const { return _is_blood_eater; }
int Tp::attack_blood(void) const { return _attack_blood; }
int Tp::environ_hates_poison(void) const { return _environ_hates_poison; }
int Tp::environ_hates_fire(void) const { return _environ_hates_fire; }
int Tp::unused_flag3(void) const { return _unused_flag3; }
int Tp::environ_hates_water(void) const { return _environ_hates_water; }
int Tp::environ_hates_acid(void) const { return _environ_hates_acid; }
int Tp::ai_is_able_to_detect_secret_doors_when_close(void) const
{
  return _ai_is_able_to_detect_secret_doors_when_close;
}
int  Tp::ai_is_able_to_break_down_doors(void) const { return _ai_is_able_to_break_down_doors; }
int  Tp::ai_is_able_to_break_out_of_webs(void) const { return _ai_is_able_to_break_out_of_webs; }
int  Tp::ai_is_able_to_open_doors(void) const { return _ai_is_able_to_open_doors; }
int  Tp::ai_is_exit_finder(void) const { return _ai_is_exit_finder; }
int  Tp::ai_is_level_explorer(void) const { return _ai_is_level_explorer; }
int  Tp::is_rusty(void) const { return _is_rusty; }
int  Tp::unused_flag4(void) const { return _unused_flag4; }
int  Tp::ai_is_able_to_learn_skills(void) const { return _ai_is_able_to_learn_skills; }
int  Tp::ai_is_able_to_enchant_weapons(void) const { return _ai_is_able_to_enchant_weapons; }
int  Tp::ai_is_able_to_attack_generators(void) const { return _ai_is_able_to_attack_generators; }
int  Tp::ai_wanderer(void) const { return _ai_wanderer; }
int  Tp::is_organic(void) const { return _is_organic; }
int  Tp::is_glass(void) const { return _is_glass; }
int  Tp::is_stone(void) const { return _is_stone; }
int  Tp::is_item_organic(void) const { return _is_item_organic; }
int  Tp::is_metal(void) const { return _is_metal; }
int  Tp::is_wooden(void) const { return _is_wooden; }
int  Tp::unused_flag5(void) const { return _unused_flag5; }
int  Tp::unused_flag6(void) const { return _unused_flag6; }
int  Tp::unused_flag7(void) const { return _unused_flag7; }
int  Tp::unused_flag8(void) const { return _unused_flag8; }
int  Tp::unused_flag9(void) const { return _unused_flag9; }
int  Tp::is_secret_door(void) const { return _is_secret_door; }
int  Tp::is_sewer_wall(void) const { return _is_sewer_wall; }
int  Tp::is_shallow_water(void) const { return _is_shallow_water; }
int  Tp::is_shovable(void) const { return _is_shovable; }
int  Tp::is_skillstone(void) const { return _is_skillstone; }
int  Tp::is_skill(void) const { return _is_skill; }
int  Tp::is_smoke(void) const { return _is_smoke; }
int  Tp::is_soft_body(void) const { return _is_soft_body; }
int  Tp::is_spawner(void) const { return _is_spawner; }
int  Tp::is_spiderweb(void) const { return _is_spiderweb; }
int  Tp::is_able_to_tire(void) const { return _is_able_to_tire; }
int  Tp::is_steal_item_chance_d1000(void) const { return _is_steal_item_chance_d1000; }
int  Tp::is_sticky(void) const { return _is_sticky; }
int  Tp::is_sword(void) const { return _is_sword; }
int  Tp::is_target_auto_select(void) const { return _is_target_auto_select; }
int  Tp::is_the_grid(void) const { return _is_the_grid; }
int  Tp::is_throwable(void) const { return _is_throwable; }
int  Tp::is_auto_throw(void) const { return _is_auto_throw; }
int  Tp::is_tickable(void) const { return _is_tickable; }
int  Tp::is_tmp_thing(void) const { return _is_tmp_thing; }
int  Tp::is_torch(void) const { return _is_torch; }
int  Tp::is_treasure_class_a(void) const { return _is_treasure_class_a; }
int  Tp::is_treasure_class_b(void) const { return _is_treasure_class_b; }
int  Tp::is_treasure_class_c(void) const { return _is_treasure_class_c; }
int  Tp::is_treasure_type_chest(void) const { return _is_treasure_type_chest; }
int  Tp::is_treasure_type_eater(void) const { return _is_treasure_type_eater; }
int  Tp::is_treasure_type(void) const { return _is_treasure_type; }
int  Tp::is_undead(void) const { return _is_undead; }
int  Tp::is_usable(void) const { return _is_usable; }
int  Tp::is_auto_use(void) const { return _is_auto_use; }
int  Tp::is_used_when_thrown(void) const { return _is_used_when_thrown; }
int  Tp::is_very_combustible(void) const { return _is_very_combustible; }
int  Tp::is_wall_dungeon(void) const { return _is_wall_dungeon; }
int  Tp::is_wall(void) const { return _is_wall; }
int  Tp::is_wand_eater(void) const { return _is_wand_eater; }
int  Tp::is_wand(void) const { return _is_wand; }
int  Tp::environ_loves_water(void) const { return _environ_loves_water; }
int  Tp::is_weapon(void) const { return _is_weapon; }
int  Tp::is_weapon_wielder(void) const { return _is_weapon_wielder; }
int  Tp::item_height(void) const { return _item_height ? _item_height : 1; }
int  Tp::item_width(void) const { return _item_width ? _item_width : 1; }
int  Tp::light_strength(void) const { return _light_strength; }
int  Tp::environ_loves_fire(void) const { return _environ_loves_fire; }
int  Tp::environ_loves_poison(void) const { return _environ_loves_poison; }
int  Tp::environ_loves_spiderwebs(void) const { return _environ_loves_spiderwebs; }
int  Tp::minion_leash_distance(void) const { return _minion_leash_distance; }
int  Tp::minion_limit(void) const { return _minion_limit; }
int  Tp::monst_size(void) const { return _monst_size; }
int  Tp::normal_placement_rules(void) const { return _normal_placement_rules; }
int  Tp::on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
int  Tp::on_death_is_open(void) const { return _on_death_is_open; }
int  Tp::range_max(void) const { return _range_max; }
int  Tp::rarity(void) const { return _rarity; }
int  Tp::stamina(void) const { return _stamina; }
int  Tp::stat_attack(void) const { return _stat_attack; }
int  Tp::stat_constitution(void) const { return _stat_constitution; }
int  Tp::stat_defence(void) const { return _stat_defence; }
int  Tp::stats01(void) const { return _stats01; }
int  Tp::stats02(void) const { return _stats02; }
int  Tp::stats03(void) const { return _stats03; }
int  Tp::stats04(void) const { return _stats04; }
int  Tp::stats05(void) const { return _stats05; }
int  Tp::stats06(void) const { return _stats06; }
int  Tp::stats07(void) const { return _stats07; }
int  Tp::stats08(void) const { return _stats08; }
int  Tp::stats09(void) const { return _stats09; }
int  Tp::stats10(void) const { return _stats10; }
int  Tp::stats11(void) const { return _stats11; }
int  Tp::stats12(void) const { return _stats12; }
int  Tp::stats17(void) const { return _stats17; }
int  Tp::stat_strength(void) const { return _stat_strength; }
int  Tp::throw_distance(void) const { return _throw_distance; }
int  Tp::weapon_damage(void) const { return _weapon_damage; }
int  Tp::weapon_use_distance(void) const { return _weapon_use_distance; }
void Tp::set_ai_avoid_distance(int v) { _ai_avoid_distance = v; }
void Tp::set_ai_resent_count(int v) { _ai_resent_count = v; }
void Tp::set_ai_obstacle(int v) { _ai_obstacle = v; }
void Tp::set_ai_scent_distance(int v) { _ai_scent_distance = v; }
void Tp::set_ai_vision_distance(int v) { _ai_vision_distance = v; }
void Tp::set_attack_eater(int v) { _attack_eater = v; }
void Tp::set_attack_humanoid(int v) { _attack_humanoid = v; }
void Tp::set_attack_living(int v) { _attack_living = v; }
void Tp::set_attack_lunge(int v) { _attack_lunge = v; }
void Tp::set_attack_meat(int v) { _attack_meat = v; }
void Tp::set_ai_shove_chance_d1000(int v) { _ai_shove_chance_d1000 = v; }
void Tp::set_ai_unprovoked_attack_chance_d1000(int v) { _ai_unprovoked_attack_chance_d1000 = v; }
void Tp::set_ai_is_able_to_shove(int v) { _ai_is_able_to_shove = v; }
void Tp::set_blast_max_radius(int v) { _blast_max_radius = v; }
void Tp::set_blast_min_radius(int v) { _blast_min_radius = v; }
void Tp::set_blit_bot_off(int v) { _blit_bot_off = v; }
void Tp::set_blit_left_off(int v) { _blit_left_off = v; }
void Tp::set_blit_right_off(int v) { _blit_right_off = v; }
void Tp::set_blit_top_off(int v) { _blit_top_off = v; }
void Tp::set_capacity_height(int v) { _capacity_height = v; }
void Tp::set_capacity_width(int v) { _capacity_width = v; }
void Tp::set_charge_count(int v) { _charge_count = v; }
void Tp::set_collision_attack(int v) { _collision_attack = v; }
void Tp::set_collision_attack_radius(float v) { _collision_attack_radius = v; }
void Tp::set_collision_box(int v) { _collision_box = v; }
void Tp::set_collision_check(int v) { _collision_check = v; }
void Tp::set_collision_circle(int v) { _collision_circle = v; }
void Tp::set_collision_hit_priority(int v) { _collision_hit_priority = v; }
void Tp::set_collision_radius(float v) { _collision_radius = v; }
void Tp::set_environ_damage_doubled_from_acid(int v) { _environ_damage_doubled_from_acid = v; }
void Tp::set_environ_damage_doubled_from_fire(int v) { _environ_damage_doubled_from_fire = v; }
void Tp::set_environ_damage_doubled_from_poison(int v) { _environ_damage_doubled_from_poison = v; }
void Tp::set_environ_damage_doubled_from_water(int v) { _environ_damage_doubled_from_water = v; }
void Tp::set_enchant_level(int v) { _enchant_level = v; }
void Tp::set_enchant_max(int v) { _enchant_max = v; }
void Tp::set_gfx_an_animation_only(int v) { _gfx_an_animation_only = v; }
void Tp::set_gfx_animated_can_hflip(int v) { _gfx_animated_can_hflip = v; }
void Tp::set_gfx_animated_can_vflip(int v) { _gfx_animated_can_vflip = v; }
void Tp::set_gfx_animated(int v) { _gfx_animated = v; }
void Tp::set_gfx_animated_no_dir(int v) { _gfx_animated_no_dir = v; }
void Tp::set_gfx_anim_attack(const std::string &v) { _gfx_anim_attack = v; }
void Tp::set_gfx_attack_anim(int v) { _gfx_attack_anim = v; }
void Tp::set_gfx_bounce_always(int v) { _gfx_bounce_always = v; }
void Tp::set_gfx_bounce_on_move(int v) { _gfx_bounce_on_move = v; }
void Tp::set_gfx_dead_anim(int v) { _gfx_dead_anim = v; }
void Tp::set_gfx_flickers(int v) { _gfx_flickers = v; }
void Tp::set_gfx_glows(int v) { _gfx_glows = v; }
void Tp::set_gfx_health_bar_shown(int v) { _gfx_health_bar_shown = v; }
void Tp::set_gfx_health_bar_autohide(int v) { _gfx_health_bar_autohide = v; }
void Tp::set_gfx_long_shadow_caster(int v) { _gfx_long_shadow_caster = v; }
void Tp::set_gfx_on_fire_anim(int v) { _gfx_on_fire_anim = v; }
void Tp::set_gfx_oversized_and_on_floor(int v) { _gfx_oversized_and_on_floor = v; }
void Tp::set_gfx_short_shadow_caster(int v) { _gfx_short_shadow_caster = v; }
void Tp::set_gfx_shown_in_bg(int v) { _gfx_shown_in_bg = v; }
void Tp::set_gfx_show_outlined(int v) { _gfx_show_outlined = v; }
void Tp::set_gfx_solid_shadow(int v) { _gfx_solid_shadow = v; }
void Tp::set_gfx_very_short_shadow_caster(int v) { _gfx_very_short_shadow_caster = v; }
void Tp::set_gfx_water(int v) { _gfx_water = v; }
void Tp::set_gfx_weapon_carry_anim(int v) { _gfx_weapon_carry_anim = v; }
void Tp::set_environ_dislikes_acid(int v) { _environ_dislikes_acid = v; }
void Tp::set_environ_dislikes_fire(int v) { _environ_dislikes_fire = v; }
void Tp::set_environ_dislikes_poison(int v) { _environ_dislikes_poison = v; }
void Tp::set_environ_dislikes_water(int v) { _environ_dislikes_water = v; }
void Tp::set_health_hunger_pct(int v) { _health_hunger_pct = v; }
void Tp::set_health_starving_pct(int v) { _health_starving_pct = v; }
void Tp::set_internal_has_dir_anim(int v) { _internal_has_dir_anim = v; }
void Tp::set_internal_has_hp_anim(int v) { _internal_has_hp_anim = v; }
void Tp::set_is_able_to_change_levels(int v) { _is_able_to_change_levels = v; }
void Tp::set_is_able_to_fall(int v) { _is_able_to_fall = v; }
void Tp::set_is_able_to_fire_at(int v) { _is_able_to_fire_at = v; }
void Tp::set_ai_is_able_to_see_through_doors(int v) { _ai_is_able_to_see_through_doors = v; }
void Tp::set_ai_is_able_to_walk_through_walls(int v) { _ai_is_able_to_walk_through_walls = v; }
void Tp::set_is_acid(int v) { _is_acid = v; }
void Tp::set_environ_loves_acid(int v) { _environ_loves_acid = v; }
void Tp::set_is_alive_on_end_of_anim(int v) { _is_alive_on_end_of_anim = v; }
void Tp::set_is_always_hit(int v) { _is_always_hit = v; }
void Tp::set_is_ascend_dungeon(int v) { _is_ascend_dungeon = v; }
void Tp::set_is_ascend_sewer(int v) { _is_ascend_sewer = v; }
void Tp::set_is_attackable_by_monst(int v) { _is_attackable_by_monst = v; }
void Tp::set_is_attackable_by_player(int v) { _is_attackable_by_player = v; }
void Tp::set_is_auto_collect_item(int v) { _is_auto_collect_item = v; }
void Tp::set_is_bag(int v) { _is_bag = v; }
void Tp::set_is_bag_item_container(int v) { _is_bag_item_container = v; }
void Tp::set_is_bag_item(int v) { _is_bag_item = v; }
void Tp::set_is_bag_item_not_stackable(int v) { _is_bag_item_not_stackable = v; }
void Tp::set_is_barrel(int v) { _is_barrel = v; }
void Tp::set_is_bleeder(int v) { _is_bleeder = v; }
void Tp::set_is_blood(int v) { _is_blood = v; }
void Tp::set_is_blood_splatter(int v) { _is_blood_splatter = v; }
void Tp::set_is_bones(int v) { _is_bones = v; }
void Tp::set_is_brazier(int v) { _is_brazier = v; }
void Tp::set_is_bridge(int v) { _is_bridge = v; }
void Tp::set_is_burnable(int v) { _is_burnable = v; }
void Tp::set_is_carrier_of_treasure_class_a(int v) { _is_carrier_of_treasure_class_a = v; }
void Tp::set_is_carrier_of_treasure_class_b(int v) { _is_carrier_of_treasure_class_b = v; }
void Tp::set_is_carrier_of_treasure_class_c(int v) { _is_carrier_of_treasure_class_c = v; }
void Tp::set_is_chasm(int v) { _is_chasm = v; }
void Tp::set_is_collectable(int v) { _is_collectable = v; }
void Tp::set_is_collect_as_keys(int v) { _is_collect_as_keys = v; }
void Tp::set_is_collected_as_gold(int v) { _is_collected_as_gold = v; }
void Tp::set_is_combustible(int v) { _is_combustible = v; }
void Tp::set_is_corpse_on_death(int v) { _is_corpse_on_death = v; }
void Tp::set_is_corridor(int v) { _is_corridor = v; }
void Tp::set_is_critical_to_level(int v) { _is_critical_to_level = v; }
void Tp::set_is_cursor_can_hover_over_x2_click(int v) { _is_cursor_can_hover_over_x2_click = v; }
void Tp::set_is_cursor_can_hover_over(int v) { _is_cursor_can_hover_over = v; }
void Tp::set_is_cursor(int v) { _is_cursor = v; }
void Tp::set_is_cursor_path(int v) { _is_cursor_path = v; }
void Tp::set_is_dead_on_end_of_anim(int v) { _is_dead_on_end_of_anim = v; }
void Tp::set_is_dead_on_shove(int v) { _is_dead_on_shove = v; }
void Tp::set_is_debug_path(int v) { _is_debug_path = v; }
void Tp::set_is_debug_type(int v) { _is_debug_type = v; }
void Tp::set_is_deep_water(int v) { _is_deep_water = v; }
void Tp::set_is_descend_dungeon(int v) { _is_descend_dungeon = v; }
void Tp::set_is_descend_sewer(int v) { _is_descend_sewer = v; }
void Tp::set_is_described_when_hovering_over(int v) { _is_described_when_hovering_over = v; }
void Tp::set_is_dirt(int v) { _is_dirt = v; }
void Tp::set_is_door(int v) { _is_door = v; }
void Tp::set_is_droppable(int v) { _is_droppable = v; }
void Tp::set_is_dry_grass(int v) { _is_dry_grass = v; }
void Tp::set_is_enchantable(int v) { _is_enchantable = v; }
void Tp::set_is_enchantstone(int v) { _is_enchantstone = v; }
void Tp::set_is_engulfer(int v) { _is_engulfer = v; }
void Tp::set_is_ethereal(int v) { _is_ethereal = v; }
void Tp::set_is_ethereal_minion_generator(int v) { _is_ethereal_minion_generator = v; }
void Tp::set_is_explosion(int v) { _is_explosion = v; }
void Tp::set_is_cursor_path_hazard_for_player(int v) { _is_cursor_path_hazard_for_player = v; }
void Tp::set_is_fearless(int v) { _is_fearless = v; }
void Tp::set_is_fire(int v) { _is_fire = v; }
void Tp::set_is_floating(int v) { _is_floating = v; }
void Tp::set_is_floor_deco(int v) { _is_floor_deco = v; }
void Tp::set_is_floor(int v) { _is_floor = v; }
void Tp::set_is_foilage(int v) { _is_foilage = v; }
void Tp::set_is_food_eater(int v) { _is_food_eater = v; }
void Tp::set_is_food(int v) { _is_food = v; }
void Tp::set_is_gold(int v) { _is_gold = v; }
void Tp::set_is_hazard(int v) { _is_hazard = v; }
void Tp::set_is_health_booster(int v) { _is_health_booster = v; }
void Tp::set_is_hittable(int v) { _is_hittable = v; }
void Tp::set_is_humanoid(int v) { _is_humanoid = v; }
void Tp::set_is_hunger_insatiable(int v) { _is_hunger_insatiable = v; }
void Tp::set_is_indestructible(int v) { _is_indestructible = v; }
void Tp::set_is_intelligent(int v) { _is_intelligent = v; }
void Tp::set_is_interesting(int v) { _is_interesting = v; }
void Tp::set_is_item_carrier(int v) { _is_item_carrier = v; }
void Tp::set_ai_is_item_collector(int v) { _ai_is_item_collector = v; }
void Tp::set_is_item_eater(int v) { _is_item_eater = v; }
void Tp::set_is_item(int v) { _is_item = v; }
void Tp::set_is_jelly_baby_eater(int v) { _is_jelly_baby_eater = v; }
void Tp::set_is_jelly_baby(int v) { _is_jelly_baby = v; }
void Tp::set_is_jelly_eater(int v) { _is_jelly_eater = v; }
void Tp::set_is_jelly(int v) { _is_jelly = v; }
void Tp::set_is_jelly_parent(int v) { _is_jelly_parent = v; }
void Tp::set_ai_random_jump_chance_d1000(int v) { _ai_random_jump_chance_d1000 = v; }
void Tp::set_ai_is_able_to_jump_distance(int v) { _ai_is_able_to_jump_distance = v; }
void Tp::set_ai_is_able_to_jump(int v) { _ai_is_able_to_jump = v; }
void Tp::set_ai_is_able_to_jump_on_low_hp_chance_d1000(int v) { _ai_is_able_to_jump_on_low_hp_chance_d1000 = v; }
void Tp::set_ai_is_able_to_collect_keys(int v) { _ai_is_able_to_collect_keys = v; }
void Tp::set_is_key(int v) { _is_key = v; }
void Tp::set_is_destroyed_on_hit_or_miss(int v) { _is_destroyed_on_hit_or_miss = v; }
void Tp::set_is_destroyed_on_hitting(int v) { _is_destroyed_on_hitting = v; }
void Tp::set_is_laser(int v) { _is_laser = v; }
void Tp::set_is_lava(int v) { _is_lava = v; }
void Tp::set_is_light_blocker(int v) { _is_light_blocker = v; }
void Tp::set_is_living(int v) { _is_living = v; }
void Tp::set_is_loggable(int v) { _is_loggable = v; }
void Tp::set_is_meat_eater(int v) { _is_meat_eater = v; }
void Tp::set_is_meat(int v) { _is_meat = v; }
void Tp::set_is_minion_generator(int v) { _is_minion_generator = v; }
void Tp::set_is_minion(int v) { _is_minion = v; }
void Tp::set_is_monst(int v) { _is_monst = v; }
void Tp::set_is_moveable(int v) { _is_moveable = v; }
void Tp::set_is_obs_destructable(int v) { _is_obs_destructable = v; }
void Tp::set_is_obs_wall_or_door(int v) { _is_obs_wall_or_door = v; }
void Tp::set_is_msg(int v) { _is_msg = v; }
void Tp::set_is_no_tile(int v) { _is_no_tile = v; }
void Tp::set_is_openable(int v) { _is_openable = v; }
void Tp::set_is_player(int v) { _is_player = v; }
void Tp::set_is_poison(int v) { _is_poison = v; }
void Tp::set_is_potion_eater(int v) { _is_potion_eater = v; }
void Tp::set_is_potion(int v) { _is_potion = v; }
void Tp::set_is_projectile(int v) { _is_projectile = v; }
void Tp::set_is_removeable_if_out_of_slots(int v) { _is_removeable_if_out_of_slots = v; }
void Tp::set_is_resurrectable(int v) { _is_resurrectable = v; }
void Tp::set_is_ripple(int v) { _is_ripple = v; }
void Tp::set_is_rock(int v) { _is_rock = v; }
void Tp::set_unused_flag10(int v) { _unused_flag10 = v; }
void Tp::set_unused_flag11(int v) { _unused_flag11 = v; }
void Tp::set_unused_flag12(int v) { _unused_flag12 = v; }
void Tp::set_unused_flag13(int v) { _unused_flag13 = v; }
void Tp::set_unused_flag14(int v) { _unused_flag14 = v; }
void Tp::set_unused_flag15(int v) { _unused_flag15 = v; }
void Tp::set_unused_flag16(int v) { _unused_flag16 = v; }
void Tp::set_unused_flag17(int v) { _unused_flag17 = v; }
void Tp::set_unused_flag18(int v) { _unused_flag18 = v; }
void Tp::set_unused_flag19(int v) { _unused_flag19 = v; }
void Tp::set_unused_flag1(int v) { _unused_flag1 = v; }
void Tp::set_unused_flag20(int v) { _unused_flag20 = v; }
void Tp::set_unused_flag21(int v) { _unused_flag21 = v; }
void Tp::set_unused_flag22(int v) { _unused_flag22 = v; }
void Tp::set_unused_flag23(int v) { _unused_flag23 = v; }
void Tp::set_unused_flag24(int v) { _unused_flag24 = v; }
void Tp::set_unused_flag25(int v) { _unused_flag25 = v; }
void Tp::set_unused_flag26(int v) { _unused_flag26 = v; }
void Tp::set_unused_flag27(int v) { _unused_flag27 = v; }
void Tp::set_unused_flag28(int v) { _unused_flag28 = v; }
void Tp::set_unused_flag29(int v) { _unused_flag29 = v; }
void Tp::set_unused_flag2(int v) { _unused_flag2 = v; }
void Tp::set_unused_flag30(int v) { _unused_flag30 = v; }
void Tp::set_unused_flag31(int v) { _unused_flag31 = v; }
void Tp::set_unused_flag32(int v) { _unused_flag32 = v; }
void Tp::set_is_buff(int v) { _is_buff = v; }
void Tp::set_is_debuff(int v) { _is_debuff = v; }
void Tp::set_attack_undead(int v) { _attack_undead = v; }
void Tp::set_is_blood_eater(int v) { _is_blood_eater = v; }
void Tp::set_attack_blood(int v) { _attack_blood = v; }
void Tp::set_environ_hates_poison(int v) { _environ_hates_poison = v; }
void Tp::set_environ_hates_fire(int v) { _environ_hates_fire = v; }
void Tp::set_unused_flag3(int v) { _unused_flag3 = v; }
void Tp::set_environ_hates_water(int v) { _environ_hates_water = v; }
void Tp::set_environ_hates_acid(int v) { _environ_hates_acid = v; }
void Tp::set_ai_is_able_to_detect_secret_doors_when_close(int v) { _ai_is_able_to_detect_secret_doors_when_close = v; }
void Tp::set_ai_is_able_to_break_down_doors(int v) { _ai_is_able_to_break_down_doors = v; }
void Tp::set_ai_is_able_to_break_out_of_webs(int v) { _ai_is_able_to_break_out_of_webs = v; }
void Tp::set_ai_is_able_to_open_doors(int v) { _ai_is_able_to_open_doors = v; }
void Tp::set_ai_is_exit_finder(int v) { _ai_is_exit_finder = v; }
void Tp::set_ai_is_level_explorer(int v) { _ai_is_level_explorer = v; }
void Tp::set_is_rusty(int v) { _is_rusty = v; }
void Tp::set_unused_flag4(int v) { _unused_flag4 = v; }
void Tp::set_ai_is_able_to_learn_skills(int v) { _ai_is_able_to_learn_skills = v; }
void Tp::set_ai_is_able_to_enchant_weapons(int v) { _ai_is_able_to_enchant_weapons = v; }
void Tp::set_ai_is_able_to_attack_generators(int v) { _ai_is_able_to_attack_generators = v; }
void Tp::set_ai_wanderer(int v) { _ai_wanderer = v; }
void Tp::set_is_organic(int v) { _is_organic = v; }
void Tp::set_is_glass(int v) { _is_glass = v; }
void Tp::set_is_stone(int v) { _is_stone = v; }
void Tp::set_is_item_organic(int v) { _is_item_organic = v; }
void Tp::set_is_metal(int v) { _is_metal = v; }
void Tp::set_is_wooden(int v) { _is_wooden = v; }
void Tp::set_unused_flag5(int v) { _unused_flag5 = v; }
void Tp::set_unused_flag6(int v) { _unused_flag6 = v; }
void Tp::set_unused_flag7(int v) { _unused_flag7 = v; }
void Tp::set_unused_flag8(int v) { _unused_flag8 = v; }
void Tp::set_unused_flag9(int v) { _unused_flag9 = v; }
void Tp::set_is_secret_door(int v) { _is_secret_door = v; }
void Tp::set_is_sewer_wall(int v) { _is_sewer_wall = v; }
void Tp::set_is_shallow_water(int v) { _is_shallow_water = v; }
void Tp::set_is_shovable(int v) { _is_shovable = v; }
void Tp::set_is_skill(int v) { _is_skill = v; }
void Tp::set_is_skillstone(int v) { _is_skillstone = v; }
void Tp::set_is_smoke(int v) { _is_smoke = v; }
void Tp::set_is_soft_body(int v) { _is_soft_body = v; }
void Tp::set_is_spawner(int v) { _is_spawner = v; }
void Tp::set_is_spiderweb(int v) { _is_spiderweb = v; }
void Tp::set_is_able_to_tire(int v) { _is_able_to_tire = v; }
void Tp::set_is_steal_item_chance_d1000(int v) { _is_steal_item_chance_d1000 = v; }
void Tp::set_is_engulf_chance_d1000(int v) { _is_engulf_chance_d1000 = v; }
void Tp::set_is_sticky(int v) { _is_sticky = v; }
void Tp::set_is_sword(int v) { _is_sword = v; }
void Tp::set_is_target_auto_select(int v) { _is_target_auto_select = v; }
void Tp::set_is_the_grid(int v) { _is_the_grid = v; }
void Tp::set_is_throwable(int v) { _is_throwable = v; }
void Tp::set_is_auto_throw(int v) { _is_auto_throw = v; }
void Tp::set_is_tickable(int v) { _is_tickable = v; }
void Tp::set_is_tmp_thing(int v) { _is_tmp_thing = v; }
void Tp::set_is_torch(int v) { _is_torch = v; }
void Tp::set_is_treasure_class_a(int v) { _is_treasure_class_a = v; }
void Tp::set_is_treasure_class_b(int v) { _is_treasure_class_b = v; }
void Tp::set_is_treasure_class_c(int v) { _is_treasure_class_c = v; }
void Tp::set_is_treasure_type_chest(int v) { _is_treasure_type_chest = v; }
void Tp::set_is_treasure_type_eater(int v) { _is_treasure_type_eater = v; }
void Tp::set_is_treasure_type(int v) { _is_treasure_type = v; }
void Tp::set_is_undead(int v) { _is_undead = v; }
void Tp::set_is_usable(int v) { _is_usable = v; }
void Tp::set_is_auto_use(int v) { _is_auto_use = v; }
void Tp::set_is_used_when_thrown(int v) { _is_used_when_thrown = v; }
void Tp::set_is_very_combustible(int v) { _is_very_combustible = v; }
void Tp::set_is_wall_dungeon(int v) { _is_wall_dungeon = v; }
void Tp::set_is_wall(int v) { _is_wall = v; }
void Tp::set_is_wand_eater(int v) { _is_wand_eater = v; }
void Tp::set_is_wand(int v) { _is_wand = v; }
void Tp::set_environ_loves_water(int v) { _environ_loves_water = v; }
void Tp::set_is_weapon(int v) { _is_weapon = v; }
void Tp::set_is_weapon_wielder(int v) { _is_weapon_wielder = v; }
void Tp::set_item_height(int v) { _item_height = v; }
void Tp::set_item_width(int v) { _item_width = v; }
void Tp::set_laser_name(const std::string &v) { _laser_name = v; }
void Tp::set_light_color(const std::string &v) { _light_color = v; }
void Tp::set_light_strength(int v) { _light_strength = v; }
void Tp::set_long_text_description(const std::string &v) { _long_text_description = v; }
void Tp::set_environ_loves_fire(int v) { _environ_loves_fire = v; }
void Tp::set_environ_loves_poison(int v) { _environ_loves_poison = v; }
void Tp::set_environ_loves_spiderwebs(int v) { _environ_loves_spiderwebs = v; }
void Tp::set_minion_leash_distance(int v) { _minion_leash_distance = v; }
void Tp::set_minion_limit(int v) { _minion_limit = v; }
void Tp::set_monst_size(int v) { _monst_size = v; }
void Tp::set_name(const std::string &v) { _name = v; }
void Tp::set_normal_placement_rules(int v) { _normal_placement_rules = v; }
void Tp::set_on_birth_do(const std::string &v) { _on_birth_do = v; }
void Tp::set_on_you_bite_attack_do(const std::string &v) { _on_you_bite_attack_do = v; }
void Tp::set_on_born_do(const std::string &v) { _on_born_do = v; }
void Tp::set_on_death_do(const std::string &v) { _on_death_do = v; }
void Tp::set_on_death_drop_all_items(int v) { _on_death_drop_all_items = v; }
void Tp::set_on_death_is_open(int v) { _on_death_is_open = v; }
void Tp::set_on_enchant_do(const std::string &v) { _on_enchant_do = v; }
void Tp::set_on_fall_do(const std::string &v) { _on_fall_do = v; }
void Tp::set_on_you_are_on_fire_do(const std::string &v) { _on_you_are_on_fire_do = v; }
void Tp::set_on_firing_at_something_do(const std::string &v) { _on_firing_at_something_do = v; }
void Tp::set_on_you_are_hit_do(const std::string &v) { _on_you_are_hit_do = v; }
void Tp::set_on_lifespan_do(const std::string &v) { _on_lifespan_do = v; }
void Tp::set_on_you_miss_do_do(const std::string &v) { _on_you_miss_do_do = v; }
void Tp::set_on_move_do(const std::string &v) { _on_move_do = v; }
void Tp::set_on_open_do(const std::string &v) { _on_open_do = v; }
void Tp::set_on_tick_do(const std::string &v) { _on_tick_do = v; }
void Tp::set_on_use_do(const std::string &v) { _on_use_do = v; }
void Tp::set_projectile_name(const std::string &v) { _projectile_name = v; }
void Tp::set_range_max(int v) { _range_max = v; }
void Tp::set_rarity(int v) { _rarity = v; }
void Tp::set_short_text_name(const std::string &v) { _short_text_name = v; }
void Tp::set_spawn_on_shoved(const std::string &v) { _spawn_on_shoved = v; }
void Tp::set_stamina(int v) { _stamina = v; }
void Tp::set_stat_attack(int v) { _stat_attack = v; }
void Tp::set_stat_constitution(int v) { _stat_constitution = v; }
void Tp::set_stat_defence(int v) { _stat_defence = v; }
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
void Tp::set_stats17(int v) { _stats17 = v; }
void Tp::set_stat_strength(int v) { _stat_strength = v; }
void Tp::set_str1(const std::string &v) { _str1 = v; }
void Tp::set_str2(const std::string &v) { _str2 = v; }
void Tp::set_str4(const std::string &v) { _str4 = v; }
void Tp::set_str5(const std::string &v) { _str5 = v; }
void Tp::set_text_a_or_an(const std::string &v) { _text_a_or_an = v; }
void Tp::set_text_description(const std::string &v) { _text_description = v; }
void Tp::set_text_enchant(const std::string &v) { _text_enchant = v; }
void Tp::set_text_hits(const std::string &v) { _text_hits = v; }
void Tp::set_text_name(const std::string &v) { _text_name = v; }
void Tp::set_text_skill(const std::string &v) { _text_skill = v; }
void Tp::set_text_debuff(const std::string &v) { _text_debuff = v; }
void Tp::set_text_buff(const std::string &v) { _text_buff = v; }
void Tp::set_text_title(const std::string &v) { _text_title = v; }
void Tp::set_text_unused(const std::string &v) { _text_unused = v; }
void Tp::set_throw_distance(int v) { _throw_distance = v; }
void Tp::set_weapon_carry_anim(const std::string &v) { _weapon_carry_anim = v; }
void Tp::set_weapon_damage(int v) { _weapon_damage = v; }
void Tp::set_weapon_use_distance(int v) { _weapon_use_distance = v; }
void Tp::set_z_depth(int v) { z_depth = v; }
void Tp::set_z_prio(int v) { z_prio = v; }

std::string Tp::text_a_or_an(void) const { return _text_a_or_an; }

//
// foo bar -> Foo Bar
//
std::string Tp::short_text_capitalized(void) const
{
  TRACE_AND_INDENT();
  std::string out        = text_name();
  char *      b          = (char *) out.c_str();
  char *      e          = b + out.size();
  char *      c          = b;
  bool        word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}
