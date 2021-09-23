//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_wid_rightbar.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

//
// Dice
//
const Dice &Thing::get_on_idle_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice());
}
const std::string &Thing::get_on_idle_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice_str());
}
int Thing::get_idle_tick(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice().roll());
}

const Dice &Thing::get_nutrition_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice());
}
const std::string &Thing::get_nutrition_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice_str());
}
int Thing::get_nutrition(void) const
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice().roll());
}

const Dice &Thing::get_health_initial_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice());
}
const std::string &Thing::get_health_initial_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice_str());
}
int Thing::get_health_initial(void) const
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice().roll());
}

const Dice &Thing::get_gold_value_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice());
}
const std::string &Thing::get_gold_value_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice_str());
}
int Thing::get_gold_value(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice().roll());
}

const Dice &Thing::get_lifespan_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice());
}
const std::string &Thing::get_lifespan_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice_str());
}
int Thing::get_lifespan_initial(void) const
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice().roll());
}

const Dice &Thing::get_resurrect_dice(void) const
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice());
}
const std::string &Thing::get_resurrect_dice_str(void) const
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice_str());
}
int Thing::get_resurrect(void) const
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice().roll());
}

int Thing::ai_avoid_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->ai_avoid_distance());
}
int Thing::ai_enemy_memory(void) const
{
  TRACE_AND_INDENT();
  return (tp()->ai_enemy_memory());
}
int Thing::ai_obstacle(void) const
{
  TRACE_AND_INDENT();
  return (tp()->ai_obstacle());
}
int Thing::ai_scent_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->ai_scent_distance());
}
int Thing::ai_vision_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->ai_vision_distance());
}
int Thing::attack_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_eater());
}
int Thing::attack_humanoid(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_humanoid());
}
int Thing::attack_living(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_living());
}
int Thing::attack_lunge(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_lunge());
}
int Thing::attack_meat(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_meat());
}
int Thing::attack_shove_chance_d1000(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_shove_chance_d1000());
}
int Thing::attack_shove(void) const
{
  TRACE_AND_INDENT();
  return (tp()->attack_shove());
}
int Thing::blast_max_radius(void) const
{
  TRACE_AND_INDENT();
  return (tp()->blast_max_radius());
}
int Thing::blast_min_radius(void) const
{
  TRACE_AND_INDENT();
  return (tp()->blast_min_radius());
}
int Thing::collision_attack(void) const
{
  TRACE_AND_INDENT();
  return (tp()->collision_attack());
}
int Thing::collision_box(void) const
{
  TRACE_AND_INDENT();
  return (tp()->collision_box());
}
int Thing::collision_check(void) const
{
  TRACE_AND_INDENT();
  return (tp()->collision_check());
}
int Thing::collision_circle(void) const
{
  TRACE_AND_INDENT();
  return (tp()->collision_circle());
}
int Thing::collision_hit_priority(void) const
{
  TRACE_AND_INDENT();
  return (tp()->collision_hit_priority());
}
int Thing::damage_doubled_from_acid(void) const
{
  TRACE_AND_INDENT();
  return (tp()->damage_doubled_from_acid());
}
int Thing::damage_doubled_from_fire(void) const
{
  TRACE_AND_INDENT();
  return (tp()->damage_doubled_from_fire());
}
int Thing::damage_doubled_from_poison(void) const
{
  TRACE_AND_INDENT();
  return (tp()->damage_doubled_from_poison());
}
int Thing::damage_doubled_from_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->damage_doubled_from_water());
}
int Thing::defence(void) const
{
  TRACE_AND_INDENT();
  return (tp()->stat_defence());
}
int Thing::enchant_level(void) const
{
  TRACE_AND_INDENT();
  return (tp()->enchant_level());
}
int Thing::enchant_max(void) const
{
  TRACE_AND_INDENT();
  return (tp()->enchant_max());
}
int Thing::get_initial_charge_count(void) const
{
  TRACE_AND_INDENT();
  return (tp()->charge_count());
}
int Thing::gfx_an_animation_only(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_an_animation_only());
}
int Thing::gfx_animated_can_hflip(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_can_hflip());
}
int Thing::gfx_animated_can_vflip(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_can_vflip());
}
int Thing::gfx_animated_no_dir(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_no_dir());
}
int Thing::gfx_animated(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated());
}
int Thing::gfx_attack_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_attack_anim());
}
int Thing::gfx_bounce_always(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_bounce_always());
}
int Thing::gfx_bounce_on_move(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_bounce_on_move());
}
int Thing::gfx_dead_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_dead_anim());
}
int Thing::gfx_flickers(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_flickers());
}
int Thing::gfx_glows(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_glows());
}
int Thing::gfx_health_bar_autohide(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_health_bar_autohide());
}
int Thing::gfx_health_bar_shown(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_health_bar_shown());
}
int Thing::gfx_long_shadow_caster(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_long_shadow_caster());
}
int Thing::gfx_on_fire_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_on_fire_anim());
}
int Thing::gfx_oversized_and_on_floor(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_oversized_and_on_floor());
}
int Thing::gfx_short_shadow_caster(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_short_shadow_caster());
}
int Thing::gfx_shown_in_bg(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_shown_in_bg());
}
int Thing::gfx_show_outlined(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_show_outlined());
}
int Thing::gfx_solid_shadow(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_solid_shadow());
}
int Thing::gfx_very_short_shadow_caster(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_very_short_shadow_caster());
}
int Thing::gfx_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_water());
}
int Thing::gfx_weapon_carry_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_weapon_carry_anim());
}
int Thing::hates_acid(void) const
{
  TRACE_AND_INDENT();
  return (tp()->hates_acid());
}
int Thing::hates_fire(void) const
{
  TRACE_AND_INDENT();
  return (tp()->hates_fire());
}
int Thing::hates_poison(void) const
{
  TRACE_AND_INDENT();
  return (tp()->hates_poison());
}
int Thing::hates_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->hates_water());
}
int Thing::health_hunger_pct(void) const
{
  TRACE_AND_INDENT();
  return (tp()->health_hunger_pct());
}
int Thing::health_starving_pct(void) const
{
  TRACE_AND_INDENT();
  return (tp()->health_starving_pct());
}
int Thing::is_able_to_change_levels(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_change_levels());
}
int Thing::is_able_to_fall(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_fall());
}
int Thing::is_able_to_fire_at(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_fire_at());
}
int Thing::is_able_to_see_through_doors(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_see_through_doors());
}
int Thing::is_able_to_walk_through_walls(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_walk_through_walls());
}
int Thing::is_acid_lover(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_acid_lover());
}
int Thing::is_acid(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_acid());
}
int Thing::is_alive_monst(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_monst() && ! is_dead);
}
int Thing::is_alive_on_end_of_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_alive_on_end_of_anim());
}
int Thing::is_always_hit(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_always_hit());
}
int Thing::is_ascend_dungeon(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ascend_dungeon());
}
int Thing::is_ascend_sewer(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ascend_sewer());
}
int Thing::is_attackable_by_monst(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_attackable_by_monst());
}
int Thing::is_attackable_by_player(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_attackable_by_player());
}
int Thing::is_auto_collect_item(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_collect_item());
}
int Thing::is_bag_item_container(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item_container());
}
int Thing::is_bag_item_not_stackable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item_not_stackable());
}
int Thing::is_bag_item(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item());
}
int Thing::is_bag(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bag());
}
int Thing::is_barrel(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_barrel());
}
int Thing::is_bleeder(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bleeder());
}
int Thing::is_blood_splatter(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_blood_splatter());
}
int Thing::is_blood(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_blood());
}
int Thing::is_bones(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bones());
}
int Thing::is_brazier(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_brazier());
}
int Thing::is_bridge(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_bridge());
}
int Thing::is_burnable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_burnable());
}
int Thing::is_carrier_of_treasure_class_a(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_a());
}
int Thing::is_carrier_of_treasure_class_b(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_b());
}
int Thing::is_carrier_of_treasure_class_c(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_c());
}
int Thing::is_chasm(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_chasm());
}
int Thing::is_collectable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_collectable());
}
int Thing::is_collect_as_keys(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_collect_as_keys());
}
int Thing::is_collected_as_gold(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_collected_as_gold());
}
int Thing::is_combustible(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_combustible());
}
int Thing::is_corpse_on_death(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_corpse_on_death());
}
int Thing::is_corpse(void) const
{
  TRACE_AND_INDENT();
  return (is_dead && is_corpse_on_death());
}
int Thing::is_corridor(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_corridor());
}
int Thing::is_critical_to_level(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_critical_to_level());
}
int Thing::is_cursor_can_hover_over_x2_click(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_can_hover_over_x2_click());
}
int Thing::is_cursor_can_hover_over(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_can_hover_over());
}
int Thing::is_cursor_path(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_path());
}
int Thing::is_cursor(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor());
}
int Thing::is_dead_on_end_of_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_dead_on_end_of_anim());
}
int Thing::is_dead_on_shove(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_dead_on_shove());
}
int Thing::is_dead_or_dying(void) const
{
  TRACE_AND_INDENT();
  return is_dead || is_dying;
}
int Thing::is_debug_path(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_debug_path());
}
int Thing::is_debug_type(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_debug_type());
}
int Thing::is_deep_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_deep_water());
}
int Thing::is_descend_dungeon(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_descend_dungeon());
}
int Thing::is_descend_sewer(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_descend_sewer());
}
int Thing::is_described_when_hovering_over(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_described_when_hovering_over());
}
int Thing::is_dirt(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_dirt());
}
int Thing::is_door(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_door());
}
int Thing::is_droppable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_droppable());
}
int Thing::is_dry_grass(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_dry_grass());
}
int Thing::is_enchantable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_enchantable());
}
int Thing::is_enchantstone(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_enchantstone());
}
int Thing::is_ethereal_minion_generator(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ethereal_minion_generator());
}
int Thing::is_ethereal(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ethereal());
}
int Thing::is_explosion(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_explosion());
}
int Thing::is_extreme_hazard(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_extreme_hazard());
}
int Thing::is_fearless(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_fearless());
}
int Thing::is_fire(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_fire());
}
int Thing::is_floating(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_floating());
}
int Thing::is_floor_deco(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_floor_deco());
}
int Thing::is_floor(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_floor());
}
int Thing::is_foilage(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_foilage());
}
int Thing::is_food_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_food_eater());
}
int Thing::is_food(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_food());
}
int Thing::is_gold(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_gold());
}
int Thing::is_hazard(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_hazard());
}
int Thing::is_hittable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_hittable());
}
int Thing::is_humanoid(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_humanoid());
}
int Thing::is_hunger_insatiable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_hunger_insatiable());
}
int Thing::is_indestructible(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_indestructible());
}
int Thing::is_intelligent(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_intelligent());
}
int Thing::is_interesting(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_interesting());
}
int Thing::is_item_carrier(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_item_carrier());
}
int Thing::is_item_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_item_eater());
}
int Thing::is_item(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_item());
}
int Thing::is_jelly_baby_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_baby_eater());
}
int Thing::is_jelly_baby(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_baby());
}
int Thing::is_jelly_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_eater());
}
int Thing::is_jelly_parent(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_parent());
}
int Thing::is_jelly(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly());
}
int Thing::is_jumper_chance_d1000(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jumper_chance_d1000());
}
int Thing::is_jumper_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jumper_distance());
}
int Thing::is_jumper_on_low_hp_chance_d1000(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jumper_on_low_hp_chance_d1000());
}
int Thing::is_jumper(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_jumper());
}
int Thing::is_key_collector(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_key_collector());
}
int Thing::is_key(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_key());
}
int Thing::is_killed_on_hit_or_miss(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_killed_on_hit_or_miss());
}
int Thing::is_killed_on_hitting(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_killed_on_hitting());
}
int Thing::is_laser(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_laser());
}
int Thing::is_lava(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_lava());
}
int Thing::is_light_blocker(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_light_blocker());
}
int Thing::is_living(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_living());
}
int Thing::is_loggable_for_important_stuff(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_loggable_for_important_stuff());
}
int Thing::is_loggable_for_unimportant_stuff(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_loggable_for_unimportant_stuff());
}
int Thing::is_meat_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_meat_eater());
}
int Thing::is_meat(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_meat());
}
int Thing::is_minion_generator(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_minion_generator());
}
int Thing::is_minion(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_minion());
}
int Thing::is_monst(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_monst());
}
int Thing::is_moveable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_moveable());
}
int Thing::is_obs_wall_or_door(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_obs_wall_or_door());
}
int Thing::is_obs_destructable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_obs_destructable());
}
int Thing::is_msg(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_msg());
}
int Thing::is_no_tile(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_no_tile());
}
int Thing::is_openable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_openable());
}
int Thing::is_player(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_player());
}
int Thing::is_poison(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_poison());
}
int Thing::is_potion_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_potion_eater());
}
int Thing::is_potion(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_potion());
}
int Thing::is_projectile(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_projectile());
}
int Thing::is_removeable_if_out_of_slots(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_removeable_if_out_of_slots());
}
int Thing::is_resurrectable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_resurrectable());
}
int Thing::is_ripple(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ripple());
}
int Thing::is_rock(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_rock());
}
int Thing::unused_flag10(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag10());
}
int Thing::unused_flag11(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag11());
}
int Thing::unused_flag12(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag12());
}
int Thing::unused_flag13(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag13());
}
int Thing::unused_flag14(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag14());
}
int Thing::unused_flag15(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag15());
}
int Thing::unused_flag16(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag16());
}
int Thing::unused_flag17(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag17());
}
int Thing::unused_flag18(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag18());
}
int Thing::unused_flag19(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag19());
}
int Thing::unused_flag1(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag1());
}
int Thing::unused_flag20(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag20());
}
int Thing::unused_flag21(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag21());
}
int Thing::unused_flag22(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag22());
}
int Thing::unused_flag23(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag23());
}
int Thing::unused_flag24(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag24());
}
int Thing::unused_flag25(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag25());
}
int Thing::unused_flag26(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag26());
}
int Thing::unused_flag27(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag27());
}
int Thing::unused_flag28(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag28());
}
int Thing::unused_flag29(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag29());
}
int Thing::unused_flag2(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag2());
}
int Thing::unused_flag30(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag30());
}
int Thing::unused_flag31(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag31());
}
int Thing::unused_flag32(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag32());
}
int Thing::unused_flag33(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag33());
}
int Thing::unused_flag34(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag34());
}
int Thing::unused_flag35(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag35());
}
int Thing::unused_flag36(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag36());
}
int Thing::unused_flag37(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag37());
}
int Thing::unused_flag38(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag38());
}
int Thing::unused_flag39(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag39());
}
int Thing::unused_flag3(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag3());
}
int Thing::unused_flag40(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag40());
}
int Thing::unused_flag41(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag41());
}
int Thing::unused_flag42(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag42());
}
int Thing::unused_flag43(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag43());
}
int Thing::unused_flag44(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag44());
}
int Thing::unused_flag45(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag45());
}
int Thing::unused_flag46(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag46());
}
int Thing::unused_flag47(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag47());
}
int Thing::unused_flag48(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag48());
}
int Thing::is_rusty(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_rusty());
}
int Thing::unused_flag4(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag4());
}
int Thing::unused_flag50(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag50());
}
int Thing::unused_flag51(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag51());
}
int Thing::unused_flag52(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag52());
}
int Thing::is_ai_wanderer(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_ai_wanderer());
}
int Thing::is_organic(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_organic());
}
int Thing::is_glass(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_glass());
}
int Thing::is_stone(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_stone());
}
int Thing::is_item_organic(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_item_organic());
}
int Thing::is_metal(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_metal());
}
int Thing::is_wooden(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_wooden());
}
int Thing::unused_flag5(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag5());
}
int Thing::is_engulfer(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_engulfer());
}
int Thing::is_health_booster(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_health_booster());
}
int Thing::unused_flag6(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag6());
}
int Thing::unused_flag7(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag7());
}
int Thing::unused_flag8(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag8());
}
int Thing::unused_flag9(void) const
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag9());
}
int Thing::is_secret_door(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_secret_door());
}
int Thing::is_sewer_wall(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_sewer_wall());
}
int Thing::is_shallow_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_shallow_water());
}
int Thing::is_shovable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_shovable());
}
int Thing::is_skillstone(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_skillstone());
}
int Thing::is_skill(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_skill());
}
int Thing::is_smoke(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_smoke());
}
int Thing::is_soft_body(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_soft_body());
}
int Thing::is_spawner(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_spawner());
}
int Thing::is_spiderweb(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_spiderweb());
}
int Thing::is_stamina_check(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_stamina_check());
}
int Thing::is_steal_item_chance_d1000(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_steal_item_chance_d1000());
}
int Thing::is_engulf_chance_d1000(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_engulf_chance_d1000());
}
int Thing::is_sticky(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_sticky());
}
int Thing::is_sword(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_sword());
}
int Thing::is_target_auto_select(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_target_auto_select());
}
int Thing::is_throwable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_throwable());
}
int Thing::is_auto_throw(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_throw());
}
int Thing::is_tickable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_tickable());
}
int Thing::is_tmp_thing(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_tmp_thing());
}
int Thing::is_torch(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_torch());
}
int Thing::is_treasure_class_a(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_a());
}
int Thing::is_treasure_class_b(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_b());
}
int Thing::is_treasure_class_c(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_c());
}
int Thing::is_treasure_type_chest(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type_chest());
}
int Thing::is_item_collector(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_item_collector());
}
int Thing::is_treasure_type_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type_eater());
}
int Thing::is_treasure_type(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type());
}
int Thing::is_undead(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_undead());
}
int Thing::is_usable(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_usable());
}
int Thing::is_auto_use(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_use());
}
int Thing::is_used_when_thrown(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_used_when_thrown());
}
int Thing::is_very_combustible(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_very_combustible());
}
int Thing::is_wall_dungeon(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_wall_dungeon());
}
int Thing::is_wall(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_wall());
}
int Thing::is_wand_eater(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_wand_eater());
}
int Thing::is_wand(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_wand());
}
int Thing::is_water_lover(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_water_lover());
}
int Thing::is_weapon(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_weapon());
}
int Thing::is_weapon_wielder(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_weapon_wielder());
}
int Thing::loves_fire(void) const
{
  TRACE_AND_INDENT();
  return (tp()->loves_fire());
}
int Thing::loves_poison(void) const
{
  TRACE_AND_INDENT();
  return (tp()->loves_poison());
}
int Thing::loves_spiderwebs(void) const
{
  TRACE_AND_INDENT();
  return (tp()->loves_spiderwebs());
}
int Thing::minion_leash_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->minion_leash_distance());
}
int Thing::minion_limit(void) const
{
  TRACE_AND_INDENT();
  return (tp()->minion_limit());
}
int Thing::normal_placement_rules(void) const
{
  TRACE_AND_INDENT();
  return (tp()->normal_placement_rules());
}
int Thing::on_death_drop_all_items(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_death_drop_all_items());
}
int Thing::on_death_is_open(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_death_is_open());
}
int Thing::range_max(void) const
{
  TRACE_AND_INDENT();
  return (tp()->range_max());
}
int Thing::weapon_damage(void) const
{
  TRACE_AND_INDENT();
  return (tp()->weapon_damage());
}
int Thing::weapon_use_distance(void) const
{
  TRACE_AND_INDENT();
  return (tp()->weapon_use_distance());
}

int Thing::is_water(void) const
{
  TRACE_AND_INDENT();
  return (tp()->is_shallow_water() || tp()->is_deep_water());
}

void Thing::new_monst(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! monstp)) {
    monstp = new Monst();
    // uncomment to see who allocates things
    // err("New monst");
    newptr(monstp, "Monst");

    if (tp_id != -1) {
      //
      // Walls and rock can be destroyed, hence no checks
      //
      if (is_dirt() || is_the_grid || is_floor()) {
        die("Unexpectedly needs monst struct");
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_age_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->_age_map);
  } else {
    return (0);
  }
}

void Thing::new_age_map(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (! monstp->_age_map) {
    monstp->_age_map = new AgeMap();
    newptr(monstp->_age_map, "age map");

    //
    // Setup random ages
    //
    auto _age_map = monstp->_age_map->val;
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        set(_age_map, x, y, 0U);
      }
    }
  }
}

void Thing::delete_age_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_age_map) {
      oldptr(monstp->_age_map);
      delete monstp->_age_map;
      monstp->_age_map = 0;
    }
  }
}

void Thing::clear_age_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_age_map) {
      *monstp->_age_map = {};
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// seen_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_seen_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->_seen_map);
  } else {
    return (0);
  }
}

void Thing::new_seen_map(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (! monstp->_seen_map) {
    monstp->_seen_map = new AgeMap();
    newptr(monstp->_seen_map, "age map");

    //
    // Setup random ages
    //
    auto _seen_map = monstp->_seen_map->val;
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        set(_seen_map, x, y, 0U);
      }
    }
  }
}

void Thing::delete_seen_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_seen_map) {
      oldptr(monstp->_seen_map);
      delete monstp->_seen_map;
      monstp->_seen_map = 0;
    }
  }
}

void Thing::clear_seen_map(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_seen_map) {
      *monstp->_seen_map = {};
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// _dmap_can_see
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::get_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->_dmap_can_see);
  } else {
    return (0);
  }
}

void Thing::new_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (! monstp->_dmap_can_see) {
    monstp->_dmap_can_see = new Dmap();
    newptr(monstp->_dmap_can_see, "AgeMap");

    auto dmap = monstp->_dmap_can_see->val;
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        set(dmap, x, y, DMAP_IS_WALL);
      }
    }
  }
}

void Thing::delete_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_dmap_can_see) {
      oldptr(monstp->_dmap_can_see);
      delete monstp->_dmap_can_see;
      monstp->_dmap_can_see = 0;
    }
  }
}

void Thing::clear_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_dmap_can_see) {
      *monstp->_dmap_can_see = {};
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// _dmap_unused
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::get_dmap_unused(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->_dmap_unused);
  } else {
    return (0);
  }
}

void Thing::new_dmap_unused(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (! monstp->_dmap_unused) {
    monstp->_dmap_unused = new Dmap();
    newptr(monstp->_dmap_unused, "AgeMap");

    auto dmap = monstp->_dmap_unused->val;
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        set(dmap, x, y, DMAP_IS_WALL);
      }
    }
  }
}

void Thing::delete_dmap_unused(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_dmap_unused) {
      oldptr(monstp->_dmap_unused);
      delete monstp->_dmap_unused;
      monstp->_dmap_unused = 0;
    }
  }
}

void Thing::clear_dmap_unused(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    if (monstp->_dmap_unused) {
      *monstp->_dmap_unused = {};
    }
  }
}

int Thing::item_height(void) const
{
  TRACE_AND_INDENT();
  return (tp()->item_height());
}

int Thing::item_width(void) const
{
  TRACE_AND_INDENT();
  return (tp()->item_width());
}

int Thing::capacity_height(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (monstp->capacity_height) {
    return monstp->capacity_height;
  }
  return (tp()->capacity_height());
}

int Thing::capacity_width(void)
{
  TRACE_AND_INDENT();
  new_monst();
  if (monstp->capacity_width) {
    return monstp->capacity_width;
  }
  return (tp()->capacity_width());
}

int Thing::monst_size(void) const
{
  TRACE_AND_INDENT();
  return (tp()->monst_size());
}

int Thing::rarity(void) const
{
  TRACE_AND_INDENT();
  return (tp()->rarity());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_lunge_to(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->lunge_to);
  } else {
    return (fpoint(0, 0));
  }
}

void Thing::set_lunge_to(fpoint v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->lunge_to = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_height(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->bounce_height);
  } else {
    return (0);
  }
}

void Thing::set_bounce_height(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fall_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fall_height(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->fall_height);
  } else {
    return (0);
  }
}

void Thing::set_fall_height(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->fall_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_fade(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->bounce_fade);
  } else {
    return (0);
  }
}

void Thing::set_bounce_fade(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->bounce_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_bounce_count(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->bounce_count);
  } else {
    return (0);
  }
}

void Thing::set_bounce_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->bounce_count = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_height(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->fadeup_height);
  } else {
    return (0);
  }
}

void Thing::set_fadeup_height(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->fadeup_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_fade(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->fadeup_fade);
  } else {
    return (0);
  }
}

void Thing::set_fadeup_fade(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->fadeup_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// wobble
////////////////////////////////////////////////////////////////////////////
float Thing::get_wobble(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->wobble);
  } else {
    return (0);
  }
}

void Thing::set_wobble(float v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->wobble = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::get_msg(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->msg);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::set_msg(const std::string &v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// dead_reason
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::get_dead_reason(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->dead_reason);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::set_dead_reason(const std::string &v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->dead_reason = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::get_submerged_offset(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    //
    // Floating when dead?
    //
    if (is_dead) {
      return (monstp->submerged_offset / 2);
    }

    return (monstp->submerged_offset);
  } else {
    return (0);
  }
}

void Thing::set_submerged_offset(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  monstp->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// gold
////////////////////////////////////////////////////////////////////////////
int Thing::get_gold(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->gold);
  } else {
    return (0);
  }
}

int Thing::set_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->gold = v);
  return (n);
}

int Thing::decr_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->gold -= v);
  if (monstp->gold < 0) {
    monstp->gold = 0;
  }
  return (n);
}

int Thing::incr_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->gold += v);
  return (n);
}

int Thing::decr_gold(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->gold--);
  if (monstp->gold < 0) {
    monstp->gold = 0;
  }
  return (n);
}

int Thing::incr_gold(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->gold++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// score
////////////////////////////////////////////////////////////////////////////
int Thing::get_score(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->score);
  } else {
    return (0);
  }
}

void Thing::set_score(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  monstp->score = v;
}

void Thing::incr_score(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  monstp->score += v;
}

////////////////////////////////////////////////////////////////////////////
// keys
////////////////////////////////////////////////////////////////////////////
int Thing::get_keys(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->keys);
  } else {
    return (0);
  }
}

int Thing::set_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->keys = v);
  return (n);
}

int Thing::decr_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->keys -= v);
  if (monstp->keys < 0) {
    monstp->keys = 0;
  }
  return (n);
}

int Thing::incr_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->keys += v);
  return (n);
}

int Thing::decr_keys(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->keys--);
  if (monstp->keys < 0) {
    monstp->keys = 0;
  }
  return (n);
}

int Thing::incr_keys(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->keys++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::get_health(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->health;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_health();
  }
  return v;
}

int Thing::set_health(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health = v);
  return (n);
}

int Thing::decr_health(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health -= v);
  return (n);
}

int Thing::incr_health(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health += v);
  return (n);
}

int Thing::decr_health(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health--);
  return (n);
}

int Thing::incr_health(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_health_max(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->health_max);
  } else {
    return (0);
  }
}

int Thing::set_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health_max = v);
  return (n);
}

int Thing::decr_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health_max -= v);
  return (n);
}

int Thing::incr_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health_max += v);
  return (n);
}

int Thing::decr_health_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health_max--);
  return (n);
}

int Thing::incr_health_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->health_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_defence(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->stat_defence;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_stat_defence();
  }
  if (is_minion()) {
    auto minion_owner = get_immediate_minion_owner();
    if (minion_owner) {
      auto minion_owner = get_immediate_minion_owner();
      v += minion_owner->get_stat_defence();
    }
  }
  return v;
}

int Thing::set_stat_defence(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_defence = v);
  return (n);
}

int Thing::decr_stat_defence(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_defence -= v);
  if (monstp->stat_defence < 0) {
    monstp->stat_defence = 0;
  }
  return (n);
}

int Thing::incr_stat_defence(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_defence += v);
  return (n);
}

int Thing::decr_stat_defence(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_defence--);
  if (monstp->stat_defence < 0) {
    monstp->stat_defence = 0;
  }
  return (n);
}

int Thing::incr_stat_defence(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_defence++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats19
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats19(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats19);
  } else {
    return (0);
  }
}

int Thing::set_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats19 = v);
  return (n);
}

int Thing::decr_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats19 -= v);
  return (n);
}

int Thing::incr_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats19 += v);
  return (n);
}

int Thing::decr_stats19(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats19--);
  return (n);
}

int Thing::incr_stats19(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats19++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stamina_max(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stamina_max);
  } else {
    return (0);
  }
}

int Thing::set_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stamina_max = v);
  return (n);
}

int Thing::decr_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stamina_max -= v);
  return (n);
}

int Thing::incr_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stamina_max += v);
  return (n);
}

int Thing::decr_stamina_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stamina_max--);
  return (n);
}

int Thing::incr_stamina_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stamina_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_enchant_max(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->enchant_max);
  } else {
    return (0);
  }
}

int Thing::set_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->enchant_max = v);
  return (n);
}

int Thing::decr_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->enchant_max -= v);
  return (n);
}

int Thing::incr_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->enchant_max += v);
  return (n);
}

int Thing::decr_enchant_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->enchant_max--);
  return (n);
}

int Thing::incr_enchant_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->enchant_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_resurrect_when
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_resurrect_when(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_resurrect_when);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->tick_resurrect_when = v);
  return (n);
}

uint32_t Thing::decr_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->tick_resurrect_when -= v);
  return (n);
}

uint32_t Thing::incr_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->tick_resurrect_when += v);
  return (n);
}

uint32_t Thing::decr_tick_resurrect_when(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->tick_resurrect_when--);
  return (n);
}

uint32_t Thing::incr_tick_resurrect_when(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->tick_resurrect_when++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats01
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats01(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats01);
  } else {
    return (0);
  }
}

int Thing::set_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats01 = v);
  return (n);
}

int Thing::decr_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats01 -= v);
  return (n);
}

int Thing::incr_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats01 += v);
  return (n);
}

int Thing::decr_stats01(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats01--);
  return (n);
}

int Thing::incr_stats01(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats01++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats02(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats02);
  } else {
    return (0);
  }
}

int Thing::set_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats02 = v);
  return (n);
}

int Thing::decr_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats02 -= v);
  return (n);
}

int Thing::incr_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats02 += v);
  return (n);
}

int Thing::decr_stats02(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats02--);
  return (n);
}

int Thing::incr_stats02(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats02++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats03(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats03);
  } else {
    return (0);
  }
}

int Thing::set_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats03 = v);
  return (n);
}

int Thing::decr_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats03 -= v);
  return (n);
}

int Thing::incr_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats03 += v);
  return (n);
}

int Thing::decr_stats03(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats03--);
  return (n);
}

int Thing::incr_stats03(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats03++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats04(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats04);
  } else {
    return (0);
  }
}

int Thing::set_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats04 = v);
  return (n);
}

int Thing::decr_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats04 -= v);
  return (n);
}

int Thing::incr_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats04 += v);
  return (n);
}

int Thing::decr_stats04(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats04--);
  return (n);
}

int Thing::incr_stats04(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats04++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats05(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats05);
  } else {
    return (0);
  }
}

int Thing::set_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats05 = v);
  return (n);
}

int Thing::decr_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats05 -= v);
  return (n);
}

int Thing::incr_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats05 += v);
  return (n);
}

int Thing::decr_stats05(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats05--);
  return (n);
}

int Thing::incr_stats05(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats05++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats06(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats06);
  } else {
    return (0);
  }
}

int Thing::set_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats06 = v);
  return (n);
}

int Thing::decr_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats06 -= v);
  return (n);
}

int Thing::incr_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats06 += v);
  return (n);
}

int Thing::decr_stats06(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats06--);
  return (n);
}

int Thing::incr_stats06(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats06++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats07(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats07);
  } else {
    return (0);
  }
}

int Thing::set_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats07 = v);
  return (n);
}

int Thing::decr_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats07 -= v);
  return (n);
}

int Thing::incr_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats07 += v);
  return (n);
}

int Thing::decr_stats07(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats07--);
  return (n);
}

int Thing::incr_stats07(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats07++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats08
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats08(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats08);
  } else {
    return (0);
  }
}

int Thing::set_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats08 = v);
  return (n);
}

int Thing::decr_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats08 -= v);
  return (n);
}

int Thing::incr_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats08 += v);
  return (n);
}

int Thing::decr_stats08(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats08--);
  return (n);
}

int Thing::incr_stats08(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats08++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats09(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats09);
  } else {
    return (0);
  }
}

int Thing::set_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats09 = v);
  return (n);
}

int Thing::decr_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats09 -= v);
  return (n);
}

int Thing::incr_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats09 += v);
  return (n);
}

int Thing::decr_stats09(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats09--);
  return (n);
}

int Thing::incr_stats09(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats09++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats10
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats10(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats10);
  } else {
    return (0);
  }
}

int Thing::set_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats10 = v);
  return (n);
}

int Thing::decr_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats10 -= v);
  return (n);
}

int Thing::incr_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats10 += v);
  return (n);
}

int Thing::decr_stats10(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats10--);
  return (n);
}

int Thing::incr_stats10(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats10++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats11
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats11(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats11);
  } else {
    return (0);
  }
}

int Thing::set_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats11 = v);
  return (n);
}

int Thing::decr_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats11 -= v);
  return (n);
}

int Thing::incr_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats11 += v);
  return (n);
}

int Thing::decr_stats11(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats11--);
  return (n);
}

int Thing::incr_stats11(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats11++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats12
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats12(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats12);
  } else {
    return (0);
  }
}

int Thing::set_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats12 = v);
  return (n);
}

int Thing::decr_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats12 -= v);
  return (n);
}

int Thing::incr_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats12 += v);
  return (n);
}

int Thing::decr_stats12(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats12--);
  return (n);
}

int Thing::incr_stats12(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats12++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_constitution
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_constitution(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stat_constitution);
  } else {
    return (0);
  }
}

int Thing::set_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_constitution = v);
  return (n);
}

int Thing::decr_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_constitution -= v);
  return (n);
}

int Thing::incr_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_constitution += v);
  return (n);
}

int Thing::decr_stat_constitution(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_constitution--);
  return (n);
}

int Thing::incr_stat_constitution(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_constitution++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_attack
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_attack(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stat_attack);
  } else {
    return (0);
  }
}

int Thing::set_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_attack = v);
  return (n);
}

int Thing::decr_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_attack -= v);
  return (n);
}

int Thing::incr_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_attack += v);
  return (n);
}

int Thing::decr_stat_attack(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_attack--);
  return (n);
}

int Thing::incr_stat_attack(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_attack++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats17
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats17(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stats17);
  } else {
    return (0);
  }
}

int Thing::set_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats17 = v);
  return (n);
}

int Thing::decr_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats17 -= v);
  return (n);
}

int Thing::incr_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats17 += v);
  return (n);
}

int Thing::decr_stats17(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats17--);
  return (n);
}

int Thing::incr_stats17(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stats17++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// throw_distance
////////////////////////////////////////////////////////////////////////////
int Thing::get_throw_distance(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->throw_distance);
  } else {
    return (0);
  }
}

int Thing::set_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->throw_distance = v);
  return (n);
}

int Thing::decr_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->throw_distance -= v);
  return (n);
}

int Thing::incr_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->throw_distance += v);
  return (n);
}

int Thing::decr_throw_distance(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->throw_distance--);
  return (n);
}

int Thing::incr_throw_distance(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->throw_distance++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina
////////////////////////////////////////////////////////////////////////////
int Thing::get_stamina(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->stamina;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_stamina();
  }
  if (is_minion()) {
    auto minion_owner = get_immediate_minion_owner();
    if (minion_owner) {
      auto minion_owner = get_immediate_minion_owner();
      v += minion_owner->get_stamina();
    }
  }
  return v;
}

int Thing::set_stamina(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->stamina = v);
  return (n);
}

int Thing::decr_stamina(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->stamina -= v);
  if (monstp->stamina < 0) {
    monstp->stamina = 0;
  }
  return (n);
}

int Thing::incr_stamina(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->stamina += v);
  return (n);
}

int Thing::decr_stamina(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->stamina--);
  if (monstp->stamina < 0) {
    monstp->stamina = 0;
  }
  return (n);
}

int Thing::incr_stamina(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->stamina++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant
////////////////////////////////////////////////////////////////////////////
int Thing::get_enchant(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->enchant;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_enchant();
  }
  if (is_minion()) {
    auto minion_owner = get_immediate_minion_owner();
    if (minion_owner) {
      auto minion_owner = get_immediate_minion_owner();
      v += minion_owner->get_enchant();
    }
  }
  return v;
}

int Thing::set_enchant(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->enchant = v);
  return (n);
}

int Thing::decr_enchant(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->enchant -= v);
  if (monstp->enchant < 0) {
    monstp->enchant = 0;
  }
  return (n);
}

int Thing::incr_enchant(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->enchant += v);
  return (n);
}

int Thing::decr_enchant(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->enchant--);
  if (monstp->enchant < 0) {
    monstp->enchant = 0;
  }
  return (n);
}

int Thing::incr_enchant(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->enchant++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// poison
////////////////////////////////////////////////////////////////////////////
int Thing::get_poison(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->poison;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_poison();
  }
  if (is_minion()) {
    auto minion_owner = get_immediate_minion_owner();
    if (minion_owner) {
      auto minion_owner = get_immediate_minion_owner();
      v += minion_owner->get_poison();
    }
  }
  return v;
}

int Thing::set_poison(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->poison = v);
  return (n);
}

int Thing::decr_poison(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->poison -= v);
  if (monstp->poison < 0) {
    monstp->poison = 0;
  }
  return (n);
}

int Thing::incr_poison(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->poison += v);
  return (n);
}

int Thing::decr_poison(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->poison--);
  if (monstp->poison < 0) {
    monstp->poison = 0;
  }
  return (n);
}

int Thing::incr_poison(void)
{
  TRACE_AND_INDENT();
  new_monst();
  auto n = (monstp->poison++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_strength
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_strength(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->stat_strength);
  } else {
    return (0);
  }
}

int Thing::set_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_strength = v);
  return (n);
}

int Thing::decr_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_strength -= v);
  return (n);
}

int Thing::incr_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_strength += v);
  return (n);
}

int Thing::decr_stat_strength(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_strength--);
  return (n);
}

int Thing::incr_stat_strength(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->stat_strength++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// owned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_owned_count(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->owned_count);
  } else {
    return (0);
  }
}

int Thing::set_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->owned_count = v);
}

int Thing::decr_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->owned_count -= v);
}

int Thing::incr_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->owned_count += v);
}

int Thing::decr_owned_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->owned_count--);
}

int Thing::incr_owned_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// minion_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_minion_count(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->minion_count);
  } else {
    return (0);
  }
}

int Thing::set_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->minion_count = v);
}

int Thing::decr_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->minion_count -= v);
}

int Thing::incr_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->minion_count += v);
}

int Thing::decr_minion_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->minion_count--);
}

int Thing::incr_minion_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->minion_count++);
}

////////////////////////////////////////////////////////////////////////////
// spawned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_spawned_count(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->spawned_count);
  } else {
    return (0);
  }
}

int Thing::set_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->spawned_count = v);
}

int Thing::decr_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->spawned_count -= v);
}

int Thing::incr_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->spawned_count += v);
}

int Thing::decr_spawned_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->spawned_count--);
}

int Thing::incr_spawned_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->spawned_count++);
}

////////////////////////////////////////////////////////////////////////////
// charge_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_charge_count(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->charge_count);
  } else {
    return (0);
  }
}

int Thing::set_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->charge_count = v);
}

int Thing::decr_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->charge_count -= v);
}

int Thing::incr_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->charge_count += v);
}

int Thing::decr_charge_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->charge_count--);
}

int Thing::incr_charge_count(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->charge_count++);
}

////////////////////////////////////////////////////////////////////////////
// lifespan
////////////////////////////////////////////////////////////////////////////
int Thing::get_lifespan(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->lifespan);
  } else {
    return (0);
  }
}

int Thing::set_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->lifespan = v);
}

int Thing::decr_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->lifespan -= v);
}

int Thing::incr_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->lifespan += v);
}

int Thing::decr_lifespan(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->lifespan--);
}

int Thing::incr_lifespan(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->lifespan++);
}

////////////////////////////////////////////////////////////////////////////
// light_strength
////////////////////////////////////////////////////////////////////////////
int Thing::get_initial_light_strength(void) const
{
  TRACE_AND_INDENT();
  return (tp()->light_strength());
}

int Thing::get_light_strength(void) const
{
  TRACE_AND_INDENT();
  if (! monstp) {
    return get_initial_light_strength();
  }

  verify(monstp);
  auto light_strength = monstp->light_strength;

  if (! light_strength) {
    light_strength = get_initial_light_strength();
  }

  if (is_player()) {
    get_light_strength_including_torch_effect(light_strength);
  }

  monstp->light_strength = light_strength;
  return light_strength;
}

int Thing::update_light_strength(void)
{
  TRACE_AND_INDENT();
  if (! monstp) {
    return get_initial_light_strength();
  }

  verify(monstp);
  auto light_strength = monstp->light_strength;

  if (! light_strength) {
    light_strength = get_initial_light_strength();
  }

  if (is_player()) {
    update_light_strength_including_torch_effect(light_strength);
  }

  monstp->light_strength = light_strength;
  return light_strength;
}

int Thing::set_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->light_strength = v);
}

int Thing::decr_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->light_strength -= v);
}

int Thing::incr_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->light_strength += v);
}

int Thing::decr_light_strength(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->light_strength--);
}

int Thing::incr_light_strength(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->light_strength++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_did_something(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_last_did_something);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_did_something = v);
}

uint32_t Thing::decr_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_did_something -= v);
}

uint32_t Thing::incr_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_did_something += v);
}

uint32_t Thing::decr_tick_last_did_something(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_did_something--);
}

uint32_t Thing::incr_tick_last_did_something(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_dropped
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_dropped(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_last_dropped);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_dropped = v);
}

uint32_t Thing::decr_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_dropped -= v);
}

uint32_t Thing::incr_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_dropped += v);
}

uint32_t Thing::decr_tick_last_dropped(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_dropped--);
}

uint32_t Thing::incr_tick_last_dropped(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_dropped++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_location_check
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_location_check(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_last_location_check);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_location_check = v);
}

uint32_t Thing::decr_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_location_check -= v);
}

uint32_t Thing::incr_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_location_check += v);
}

uint32_t Thing::decr_tick_last_location_check(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_location_check--);
}

uint32_t Thing::incr_tick_last_location_check(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_location_check++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_escape
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_escape(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_last_escape);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_escape = v);
}

uint32_t Thing::decr_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_escape -= v);
}

uint32_t Thing::incr_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_escape += v);
}

uint32_t Thing::decr_tick_last_escape(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_escape--);
}

uint32_t Thing::incr_tick_last_escape(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_escape++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_level_change
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_level_change(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->tick_last_level_change);
  } else {
    return (0);
  }
}

uint32_t Thing::set_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_level_change = v);
}

uint32_t Thing::decr_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_level_change -= v);
}

uint32_t Thing::incr_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_level_change += v);
}

uint32_t Thing::decr_tick_last_level_change(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_level_change--);
}

uint32_t Thing::incr_tick_last_level_change(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->tick_last_level_change++);
}

////////////////////////////////////////////////////////////////////////////
// where_i_dropped_an_item_last
////////////////////////////////////////////////////////////////////////////
point Thing::get_where_i_dropped_an_item_last(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->where_i_dropped_an_item_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::set_where_i_dropped_an_item_last(point v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->where_i_dropped_an_item_last = v);
}

////////////////////////////////////////////////////////////////////////////
// where_i_failed_to_collect_last
////////////////////////////////////////////////////////////////////////////
point Thing::get_where_i_failed_to_collect_last(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->where_i_failed_to_collect_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::set_where_i_failed_to_collect_last(point v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->where_i_failed_to_collect_last = v);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_lunge_begin(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_lunge_begin);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_begin = v);
}

ts_t Thing::decr_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_begin -= v);
}

ts_t Thing::incr_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_begin += v);
}

ts_t Thing::decr_ts_lunge_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_begin--);
}

ts_t Thing::incr_ts_lunge_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_lunge_end(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_lunge_end);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_end = v);
}

ts_t Thing::decr_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_end -= v);
}

ts_t Thing::incr_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_end += v);
}

ts_t Thing::decr_ts_lunge_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_end--);
}

ts_t Thing::incr_ts_lunge_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_lunge_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_bounce_begin(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_bounce_begin);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_begin = v);
}

ts_t Thing::decr_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_begin -= v);
}

ts_t Thing::incr_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_begin += v);
}

ts_t Thing::decr_ts_bounce_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_begin--);
}

ts_t Thing::incr_ts_bounce_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_bounce_end(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_bounce_end);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_end = v);
}

ts_t Thing::decr_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_end -= v);
}

ts_t Thing::incr_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_end += v);
}

ts_t Thing::decr_ts_bounce_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_end--);
}

ts_t Thing::incr_ts_bounce_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fadeup_begin(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_fadeup_begin);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_begin = v);
}

ts_t Thing::decr_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_begin -= v);
}

ts_t Thing::incr_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_begin += v);
}

ts_t Thing::decr_ts_fadeup_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_begin--);
}

ts_t Thing::incr_ts_fadeup_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fadeup_end(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_fadeup_end);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_end = v);
}

ts_t Thing::decr_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_end -= v);
}

ts_t Thing::incr_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_end += v);
}

ts_t Thing::decr_ts_fadeup_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_end--);
}

ts_t Thing::incr_ts_fadeup_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fadeup_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_flip_start
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_flip_start(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_flip_start);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_flip_start = v);
}

ts_t Thing::decr_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_flip_start -= v);
}

ts_t Thing::incr_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_flip_start += v);
}

ts_t Thing::decr_ts_flip_start(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_flip_start--);
}

ts_t Thing::incr_ts_flip_start(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// ts_anim_delay_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_anim_delay_end(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_anim_delay_end);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_anim_delay_end = v);
}

ts_t Thing::decr_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_anim_delay_end -= v);
}

ts_t Thing::incr_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_anim_delay_end += v);
}

ts_t Thing::decr_ts_anim_delay_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_anim_delay_end--);
}

ts_t Thing::incr_ts_anim_delay_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_anim_delay_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fall_begin(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_fall_begin);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_begin = v);
}

ts_t Thing::decr_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_begin -= v);
}

ts_t Thing::incr_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_begin += v);
}

ts_t Thing::decr_ts_fall_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_begin--);
}

ts_t Thing::incr_ts_fall_begin(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fall_end(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    verify(monstp);
    return (monstp->ts_fall_end);
  } else {
    return (0);
  }
}

ts_t Thing::set_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_end = v);
}

ts_t Thing::decr_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_end -= v);
}

ts_t Thing::incr_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_end += v);
}

ts_t Thing::decr_ts_fall_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_end--);
}

ts_t Thing::incr_ts_fall_end(void)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->ts_fall_end++);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_carry_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id_carry_anim(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    return (monstp->weapon_id_carry_anim);
  } else {
    return (0);
  }
}

ThingId Thing::set_weapon_id_carry_anim(ThingId v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->weapon_id_carry_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_use_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id_use_anim(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    return (monstp->weapon_id_use_anim);
  } else {
    return (0);
  }
}

ThingId Thing::set_weapon_id_use_anim(ThingId v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->weapon_id_use_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_tp_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    // con("get weapon %08" PRIx32 "", monstp->weapon_id);
    return (monstp->weapon_id);
  } else {
    // con("get weapon id => none");
    return (0);
  }
}

ThingId Thing::set_weapon_id(ThingId v)
{
  TRACE_AND_INDENT();
  new_monst();
  // con("set weapon %08" PRIx32 "", v);
  return (monstp->weapon_id = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_on_fire_anim_id(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    return (monstp->on_fire_id_anim);
  } else {
    return (0);
  }
}

ThingId Thing::set_on_fire_anim_id(ThingId v)
{
  TRACE_AND_INDENT();
  new_monst();
  return (monstp->on_fire_id_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// current_damage
////////////////////////////////////////////////////////////////////////////
int Thing::get_current_damage(void) const
{
  TRACE_AND_INDENT();
  int v = 0;
  if (monstp) {
    verify(monstp);
    v = monstp->current_damage;
  }
  auto owner = get_immediate_owner();
  if (owner) {
    auto owner = get_immediate_owner();
    v += owner->get_current_damage();
  }
  return v;
}

int Thing::set_current_damage(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->current_damage = v);
  return (n);
}

int Thing::decr_current_damage(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->current_damage -= v);
  return (n);
}

int Thing::incr_current_damage(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->current_damage += v);
  return (n);
}

int Thing::decr_current_damage(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->current_damage--);
  return (n);
}

int Thing::incr_current_damage(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_monst();
  auto n = (monstp->current_damage++);
  return (n);
}

const std::string &Thing::gfx_anim_attack(void) const
{
  TRACE_AND_INDENT();
  return (tp()->gfx_anim_attack());
}
const std::string &Thing::laser_name(void) const
{
  TRACE_AND_INDENT();
  return (tp()->laser_name());
}
const std::string &Thing::light_color(void) const
{
  TRACE_AND_INDENT();
  return (tp()->light_color());
}
const std::string &Thing::long_text_description(void) const
{
  TRACE_AND_INDENT();
  return (tp()->long_text_description());
}
const std::string &Thing::name(void) const
{
  TRACE_AND_INDENT();
  return (tp()->name());
}
const std::string &Thing::on_birth_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_birth_do());
}
const std::string &Thing::on_bite_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_bite_do());
}
const std::string &Thing::on_born_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_born_do());
}
const std::string &Thing::on_death_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_death_do());
}
const std::string &Thing::on_enchant_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_enchant_do());
}
const std::string &Thing::on_fall_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_fall_do());
}
const std::string &Thing::on_fire_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_fire_do());
}
const std::string &Thing::on_firing_at_something_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_firing_at_something_do());
}
const std::string &Thing::on_hit_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_hit_do());
}
const std::string &Thing::on_lifespan_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_lifespan_do());
}
const std::string &Thing::on_miss_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_miss_do());
}
const std::string &Thing::on_move_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_move_do());
}
const std::string &Thing::on_open_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_open_do());
}
const std::string &Thing::on_tick_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_tick_do());
}
const std::string &Thing::on_use_do(void) const
{
  TRACE_AND_INDENT();
  return (tp()->on_use_do());
}
const std::string &Thing::projectile_name(void) const
{
  TRACE_AND_INDENT();
  return (tp()->projectile_name());
}
const std::string &Thing::short_text_name(void) const
{
  TRACE_AND_INDENT();
  return (tp()->short_text_name());
}
const std::string &Thing::spawn_on_shoved(void) const
{
  TRACE_AND_INDENT();
  return (tp()->spawn_on_shoved());
}
const std::string &Thing::str1(void) const
{
  TRACE_AND_INDENT();
  return (tp()->str1());
}
const std::string &Thing::str2(void) const
{
  TRACE_AND_INDENT();
  return (tp()->str2());
}
const std::string &Thing::str4(void) const
{
  TRACE_AND_INDENT();
  return (tp()->str4());
}
const std::string &Thing::str5(void) const
{
  TRACE_AND_INDENT();
  return (tp()->str5());
}
const std::string &Thing::text_description(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_description());
}
const std::string &Thing::text_enchant(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_enchant());
}
const std::string &Thing::text_hits(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_hits());
}
const std::string &Thing::text_name(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_name());
}
const std::string &Thing::text_skill(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_skill());
}
const std::string &Thing::text_title(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_title());
}
const std::string &Thing::text_unused(void) const
{
  TRACE_AND_INDENT();
  return (tp()->text_unused());
}
const std::string &Thing::weapon_carry_anim(void) const
{
  TRACE_AND_INDENT();
  return (tp()->weapon_carry_anim());
}

std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::get_bag(void)
{
  TRACE_AND_INDENT();
  if (monstp) {
    return (&monstp->bag);
  } else {
    DIE("No bag");
  }
}

const std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::get_const_bag(void) const
{
  TRACE_AND_INDENT();
  if (monstp) {
    return (&monstp->bag);
  } else {
    DIE("No bag");
  }
}

const std::string &Thing::title(void) const
{
  if (g_opt_player_name.empty()) {
    return text_title();
  } else {
    return g_opt_player_name;
  }
}

int Thing::get_group(void)
{
  if (is_tmp_thing()) {
    return THING_GROUP_TMP;
  }
  return THING_GROUP_ALL;
}
