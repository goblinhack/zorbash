//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_rightbar.hpp"

//
// Dice
//
const Dice &Thing::get_on_idle_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice());
}

const std::string &Thing::get_on_idle_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice_str());
}

int Thing::get_idle_tick(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_idle_dice().roll());
}

const Dice &Thing::get_nutrition_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice());
}

const std::string &Thing::get_nutrition_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice_str());
}

int Thing::get_nutrition(void)
{
  TRACE_AND_INDENT();
  return (tp()->nutrition_dice().roll());
}

const Dice &Thing::get_health_initial_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice());
}

const std::string &Thing::get_health_initial_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice_str());
}

int Thing::get_health_initial(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_health_initial_dice().roll());
}

const Dice &Thing::get_gold_value_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice());
}

const std::string &Thing::get_gold_value_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice_str());
}

int Thing::get_gold_value(void)
{
  TRACE_AND_INDENT();
  return (tp()->gold_value_dice().roll());
}

const Dice &Thing::get_lifespan_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice());
}

const std::string &Thing::get_lifespan_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice_str());
}

int Thing::get_lifespan_initial(void)
{
  TRACE_AND_INDENT();
  return (tp()->lifespan_dice().roll());
}

const Dice &Thing::get_resurrect_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice());
}

const std::string &Thing::get_resurrect_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice_str());
}

int Thing::get_resurrect(void)
{
  TRACE_AND_INDENT();
  return (tp()->resurrect_dice().roll());
}

int Thing::ai_avoid_distance(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_avoid_distance());
}

int Thing::ai_resent_count(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_resent_count());
}

int Thing::ai_obstacle(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_obstacle());
}

int Thing::ai_scent_distance(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_scent_distance());
}

int Thing::ai_vision_distance(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_vision_distance());
}

int Thing::attack_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_eater());
}

int Thing::attack_humanoid(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_humanoid());
}

int Thing::attack_living(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_living());
}

int Thing::attack_lunge(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_lunge());
}

int Thing::attack_meat(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_meat());
}

int Thing::ai_shove_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_shove_chance_d1000());
}

int Thing::ai_unprovoked_attack_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_unprovoked_attack_chance_d1000());
}

int Thing::ai_is_able_to_shove(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_shove());
}

int Thing::blast_max_radius(void)
{
  TRACE_AND_INDENT();
  return (tp()->blast_max_radius());
}

int Thing::blast_min_radius(void)
{
  TRACE_AND_INDENT();
  return (tp()->blast_min_radius());
}

int Thing::collision_attack(void)
{
  TRACE_AND_INDENT();
  return (tp()->collision_attack());
}

int Thing::collision_box(void)
{
  TRACE_AND_INDENT();
  return (tp()->collision_box());
}

int Thing::collision_check(void)
{
  TRACE_AND_INDENT();
  return (tp()->collision_check());
}

int Thing::collision_circle(void)
{
  TRACE_AND_INDENT();
  return (tp()->collision_circle());
}

int Thing::collision_hit_priority(void)
{
  TRACE_AND_INDENT();
  return (tp()->collision_hit_priority());
}

int Thing::environ_damage_doubled_from_acid(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_damage_doubled_from_acid());
}

int Thing::environ_damage_doubled_from_fire(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_damage_doubled_from_fire());
}

int Thing::environ_damage_doubled_from_poison(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_damage_doubled_from_poison());
}

int Thing::environ_damage_doubled_from_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_damage_doubled_from_water());
}

int Thing::defence(void)
{
  TRACE_AND_INDENT();
  return (tp()->stat_defence());
}

int Thing::enchant_level(void)
{
  TRACE_AND_INDENT();
  return (tp()->enchant_level());
}

int Thing::enchant_max(void)
{
  TRACE_AND_INDENT();
  return (tp()->enchant_max());
}

int Thing::get_initial_charge_count(void)
{
  TRACE_AND_INDENT();
  return (tp()->charge_count());
}

int Thing::gfx_an_animation_only(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_an_animation_only());
}

int Thing::gfx_animated_can_hflip(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_can_hflip());
}

int Thing::gfx_animated_can_vflip(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_can_vflip());
}

int Thing::gfx_animated_no_dir(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated_no_dir());
}

int Thing::gfx_animated(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_animated());
}

int Thing::gfx_attack_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_attack_anim());
}

int Thing::gfx_bounce_always(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_bounce_always());
}

int Thing::gfx_bounce_on_move(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_bounce_on_move());
}

int Thing::gfx_dead_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_dead_anim());
}

int Thing::gfx_flickers(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_flickers());
}

int Thing::gfx_glows(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_glows());
}

int Thing::gfx_health_bar_autohide(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_health_bar_autohide());
}

int Thing::gfx_health_bar_shown(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_health_bar_shown());
}

int Thing::gfx_long_shadow_caster(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_long_shadow_caster());
}

int Thing::gfx_on_fire_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_on_fire_anim());
}

int Thing::gfx_oversized_and_on_floor(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_oversized_and_on_floor());
}

int Thing::gfx_short_shadow_caster(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_short_shadow_caster());
}

int Thing::gfx_shown_in_bg(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_shown_in_bg());
}

int Thing::gfx_show_outlined(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_show_outlined());
}

int Thing::gfx_solid_shadow(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_solid_shadow());
}

int Thing::gfx_very_short_shadow_caster(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_very_short_shadow_caster());
}

int Thing::gfx_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_water());
}

int Thing::gfx_equip_carry_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_equip_carry_anim());
}

int Thing::environ_dislikes_acid(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_dislikes_acid());
}

int Thing::environ_dislikes_fire(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_dislikes_fire());
}

int Thing::environ_dislikes_poison(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_dislikes_poison());
}

int Thing::environ_dislikes_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_dislikes_water());
}

int Thing::health_hunger_pct(void)
{
  TRACE_AND_INDENT();
  return (tp()->health_hunger_pct());
}

int Thing::health_starving_pct(void)
{
  TRACE_AND_INDENT();
  return (tp()->health_starving_pct());
}

int Thing::is_able_to_change_levels(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_change_levels());
}

int Thing::is_able_to_fall(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_fall());
}

int Thing::is_able_to_fire_at(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_fire_at());
}

int Thing::ai_is_able_to_see_through_doors(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_see_through_doors());
}

int Thing::ai_is_able_to_walk_through_walls(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_walk_through_walls());
}

int Thing::environ_loves_acid(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_loves_acid());
}

int Thing::is_acid(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_acid());
}

int Thing::is_alive_monst(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_monst() && ! is_dead);
}

int Thing::is_alive_on_end_of_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_alive_on_end_of_anim());
}

int Thing::is_always_hit(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_always_hit());
}

int Thing::is_ascend_dungeon(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ascend_dungeon());
}

int Thing::is_ascend_sewer(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ascend_sewer());
}

int Thing::is_attackable_by_monst(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_attackable_by_monst());
}

int Thing::is_attackable_by_player(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_attackable_by_player());
}

int Thing::is_auto_collect_item(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_collect_item());
}

int Thing::is_bag_item_container(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item_container());
}

int Thing::is_bag_item_not_stackable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item_not_stackable());
}

int Thing::is_bag_item(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bag_item());
}

int Thing::is_bag(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bag());
}

int Thing::is_barrel(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_barrel());
}

int Thing::is_bleeder(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bleeder());
}

int Thing::is_blood_splatter(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_blood_splatter());
}

int Thing::is_blood(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_blood());
}

int Thing::is_bones(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bones());
}

int Thing::is_brazier(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_brazier());
}

int Thing::is_bridge(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_bridge());
}

int Thing::is_burnable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_burnable());
}

int Thing::is_carrier_of_treasure_class_a(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_a());
}

int Thing::is_carrier_of_treasure_class_b(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_b());
}

int Thing::is_carrier_of_treasure_class_c(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_carrier_of_treasure_class_c());
}

int Thing::is_chasm(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_chasm());
}

int Thing::is_collectable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_collectable());
}

int Thing::is_collect_as_keys(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_collect_as_keys());
}

int Thing::is_collected_as_gold(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_collected_as_gold());
}

int Thing::is_combustible(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_combustible());
}

int Thing::is_corpse_on_death(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_corpse_on_death());
}

int Thing::is_corpse(void)
{
  TRACE_AND_INDENT();
  return (is_dead && is_corpse_on_death());
}

int Thing::is_corridor(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_corridor());
}

int Thing::is_critical_to_level(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_critical_to_level());
}

int Thing::is_cursor_can_hover_over_x2_click(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_can_hover_over_x2_click());
}

int Thing::is_cursor_can_hover_over(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_can_hover_over());
}

int Thing::is_cursor_path(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_path());
}

int Thing::is_cursor(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor());
}

int Thing::is_dead_on_end_of_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_dead_on_end_of_anim());
}

int Thing::is_dead_on_shove(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_dead_on_shove());
}

int Thing::is_dead_or_dying(void)
{
  TRACE_AND_INDENT();
  return is_dead || is_dying;
}

int Thing::is_debug_path(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_debug_path());
}

int Thing::is_debug_type(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_debug_type());
}

int Thing::is_deep_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_deep_water());
}

int Thing::is_descend_dungeon(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_descend_dungeon());
}

int Thing::is_descend_sewer(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_descend_sewer());
}

int Thing::is_described_when_hovering_over(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_described_when_hovering_over());
}

int Thing::is_dirt(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_dirt());
}

int Thing::is_door(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_door());
}

int Thing::is_droppable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_droppable());
}

int Thing::is_dry_grass(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_dry_grass());
}

int Thing::is_enchantable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_enchantable());
}

int Thing::is_enchantstone(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_enchantstone());
}

int Thing::is_ethereal_minion_generator(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ethereal_minion_generator());
}

int Thing::is_ethereal(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ethereal());
}

int Thing::is_explosion(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_explosion());
}

int Thing::is_cursor_path_hazard_for_player(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_cursor_path_hazard_for_player());
}

int Thing::is_fearless(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_fearless());
}

int Thing::is_fire(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_fire());
}

int Thing::is_floating(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_floating());
}

int Thing::is_floor_deco(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_floor_deco());
}

int Thing::is_floor(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_floor());
}

int Thing::is_foilage(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_foilage());
}

int Thing::is_food_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_food_eater());
}

int Thing::is_food(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_food());
}

int Thing::is_gold(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_gold());
}

int Thing::is_hazard(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_hazard());
}

int Thing::is_hittable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_hittable());
}

int Thing::is_humanoid(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_humanoid());
}

int Thing::is_hunger_insatiable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_hunger_insatiable());
}

int Thing::is_indestructible(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_indestructible());
}

int Thing::is_intelligent(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_intelligent());
}

int Thing::is_interesting(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_interesting());
}

int Thing::is_item_carrier(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item_carrier());
}

int Thing::is_item_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item_eater());
}

int Thing::is_item(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item());
}

int Thing::is_jelly_baby_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_baby_eater());
}

int Thing::is_jelly_baby(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_baby());
}

int Thing::is_jelly_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_eater());
}

int Thing::is_jelly_parent(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly_parent());
}

int Thing::is_jelly(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_jelly());
}

int Thing::ai_random_jump_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_random_jump_chance_d1000());
}

int Thing::ai_is_able_to_jump_distance(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_jump_distance());
}

int Thing::ai_is_able_to_jump_on_low_hp_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_jump_on_low_hp_chance_d1000());
}

int Thing::ai_is_able_to_jump(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_jump());
}

int Thing::ai_is_able_to_collect_keys(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_collect_keys());
}

int Thing::is_key(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_key());
}

int Thing::is_destroyed_on_hit_or_miss(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_destroyed_on_hit_or_miss());
}

int Thing::is_destroyed_on_hitting(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_destroyed_on_hitting());
}

int Thing::is_laser(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_laser());
}

int Thing::is_lava(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_lava());
}

int Thing::is_light_blocker(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_light_blocker());
}

int Thing::is_living(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_living());
}

int Thing::is_loggable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_loggable());
}

int Thing::is_meat_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_meat_eater());
}

int Thing::is_meat(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_meat());
}

int Thing::is_minion_generator(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_minion_generator());
}

int Thing::is_minion(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_minion());
}

int Thing::is_monst(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_monst());
}

int Thing::is_moveable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_moveable());
}

int Thing::is_obs_wall_or_door(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_obs_wall_or_door());
}

int Thing::is_obs_destructable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_obs_destructable());
}

int Thing::is_msg(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_msg());
}

int Thing::is_no_tile(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_no_tile());
}

int Thing::is_openable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_openable());
}

int Thing::is_player(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_player());
}

int Thing::is_poison(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_poison());
}

int Thing::is_potion_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_potion_eater());
}

int Thing::is_potion(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_potion());
}

int Thing::is_projectile(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_projectile());
}

int Thing::is_removeable_if_out_of_slots(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_removeable_if_out_of_slots());
}

int Thing::is_resurrectable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_resurrectable());
}

int Thing::is_ripple(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ripple());
}

int Thing::is_rock(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_rock());
}

int Thing::unused_flag10(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag10());
}

int Thing::unused_flag11(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag11());
}

int Thing::unused_flag12(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag12());
}

int Thing::unused_flag13(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag13());
}

int Thing::unused_flag14(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag14());
}

int Thing::unused_flag15(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag15());
}

int Thing::unused_flag16(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag16());
}

int Thing::unused_flag17(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag17());
}

int Thing::unused_flag18(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag18());
}

int Thing::unused_flag19(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag19());
}

int Thing::unused_flag1(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag1());
}

int Thing::unused_flag20(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag20());
}

int Thing::unused_flag21(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag21());
}

int Thing::unused_flag22(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag22());
}

int Thing::unused_flag23(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag23());
}

int Thing::unused_flag24(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag24());
}

int Thing::unused_flag25(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag25());
}

int Thing::unused_flag26(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag26());
}

int Thing::unused_flag27(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag27());
}

int Thing::is_gfx_anim_synced_with_owner(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_gfx_anim_synced_with_owner());
}

int Thing::is_item_magical(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item_magical());
}

int Thing::unused_flag2(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag2());
}

int Thing::unused_flag30(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag30());
}

int Thing::is_ring(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_ring());
}

int Thing::is_auto_equipped(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_equipped());
}

int Thing::is_buff(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_buff());
}

int Thing::is_debuff(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_debuff());
}

int Thing::attack_undead(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_undead());
}

int Thing::is_blood_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_blood_eater());
}

int Thing::attack_blood(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_blood());
}

int Thing::environ_hates_poison(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_hates_poison());
}

int Thing::environ_hates_fire(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_hates_fire());
}

int Thing::unused_flag3(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag3());
}

int Thing::environ_hates_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_hates_water());
}

int Thing::environ_hates_acid(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_hates_acid());
}

int Thing::ai_is_able_to_detect_secret_doors_when_close(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_detect_secret_doors_when_close());
}

int Thing::ai_is_able_to_break_down_doors(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_break_down_doors());
}

int Thing::ai_is_able_to_break_out_of_webs(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_break_out_of_webs());
}

int Thing::ai_is_able_to_open_doors(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_open_doors());
}

int Thing::ai_is_exit_finder(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_exit_finder());
}

int Thing::ai_is_level_explorer(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_level_explorer());
}

int Thing::is_rusty(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_rusty());
}

int Thing::unused_flag4(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag4());
}

int Thing::ai_is_able_to_learn_skills(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_learn_skills());
}

int Thing::ai_is_able_to_enchant_weapons(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_enchant_weapons());
}

int Thing::ai_is_able_to_attack_generators(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_able_to_attack_generators());
}

int Thing::ai_wanderer(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_wanderer());
}

int Thing::is_organic(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_organic());
}

int Thing::is_glass(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_glass());
}

int Thing::is_stone(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_stone());
}

int Thing::is_item_organic(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item_organic());
}

int Thing::is_metal(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_metal());
}

int Thing::is_wooden(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_wooden());
}

int Thing::unused_flag5(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag5());
}

int Thing::is_engulfer(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_engulfer());
}

int Thing::is_health_booster(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_health_booster());
}

int Thing::unused_flag6(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag6());
}

int Thing::unused_flag7(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag7());
}

int Thing::unused_flag8(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag8());
}

int Thing::unused_flag9(void)
{
  TRACE_AND_INDENT();
  return (tp()->unused_flag9());
}

int Thing::is_secret_door(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_secret_door());
}

int Thing::is_sewer_wall(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_sewer_wall());
}

int Thing::is_shallow_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_shallow_water());
}

int Thing::is_shovable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_shovable());
}

int Thing::is_skillstone(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_skillstone());
}

int Thing::is_skill(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_skill());
}

int Thing::is_smoke(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_smoke());
}

int Thing::is_soft_body(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_soft_body());
}

int Thing::is_spawner(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_spawner());
}

int Thing::is_spiderweb(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_spiderweb());
}

int Thing::is_able_to_tire(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_able_to_tire());
}

int Thing::is_steal_item_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_steal_item_chance_d1000());
}

int Thing::attack_engulf_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_engulf_chance_d1000());
}

int Thing::attack_poison_chance_d1000(void)
{
  TRACE_AND_INDENT();
  return (tp()->attack_poison_chance_d1000());
}

int Thing::is_sticky(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_sticky());
}

int Thing::is_sword(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_sword());
}

int Thing::is_target_auto_select(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_target_auto_select());
}

int Thing::is_throwable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_throwable());
}

int Thing::is_auto_throw(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_throw());
}

int Thing::is_tickable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_tickable());
}

int Thing::is_tmp_thing(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_tmp_thing());
}

int Thing::is_torch(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_torch());
}

int Thing::is_treasure_class_a(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_a());
}

int Thing::is_treasure_class_b(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_b());
}

int Thing::is_treasure_class_c(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_class_c());
}

int Thing::is_treasure_type_chest(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type_chest());
}

int Thing::ai_is_item_collector(void)
{
  TRACE_AND_INDENT();
  return (tp()->ai_is_item_collector());
}

int Thing::is_treasure_type_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type_eater());
}

int Thing::is_treasure_type(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_treasure_type());
}

int Thing::is_undead(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_undead());
}

int Thing::is_usable(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_usable());
}

int Thing::is_auto_use(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_auto_use());
}

int Thing::is_used_when_thrown(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_used_when_thrown());
}

int Thing::is_very_combustible(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_very_combustible());
}

int Thing::is_wall_dungeon(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_wall_dungeon());
}

int Thing::is_wall(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_wall());
}

int Thing::is_item_magical_eater(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_item_magical_eater());
}

int Thing::is_wand(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_wand());
}

int Thing::environ_loves_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_loves_water());
}

int Thing::is_weapon(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_weapon());
}

int Thing::is_weapon_equiper(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_weapon_equiper());
}

int Thing::environ_loves_fire(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_loves_fire());
}

int Thing::environ_loves_poison(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_loves_poison());
}

int Thing::environ_loves_spiderwebs(void)
{
  TRACE_AND_INDENT();
  return (tp()->environ_loves_spiderwebs());
}

int Thing::minion_leash_distance(void)
{
  TRACE_AND_INDENT();
  return (tp()->minion_leash_distance());
}

int Thing::minion_limit(void)
{
  TRACE_AND_INDENT();
  return (tp()->minion_limit());
}

int Thing::normal_placement_rules(void)
{
  TRACE_AND_INDENT();
  return (tp()->normal_placement_rules());
}

int Thing::on_death_drop_all_items(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_death_drop_all_items());
}

int Thing::on_death_is_open(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_death_is_open());
}

int Thing::range_max(void)
{
  TRACE_AND_INDENT();
  return (tp()->range_max());
}

int Thing::weapon_damage(void)
{
  TRACE_AND_INDENT();
  return (tp()->weapon_damage());
}

int Thing::is_water(void)
{
  TRACE_AND_INDENT();
  return (tp()->is_shallow_water() || tp()->is_deep_water());
}

void Thing::new_infop(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _infop)) {
    _infop = new ThingInfo();
    // uncomment to see who allocates things
    // err("New monst info");
    newptr(_infop, "ThingInfo");

    if (mytp && (tp_id != -1)) {
      //
      // Walls and rock can be destroyed, hence no checks
      //
      if (is_dirt() || is_the_grid || is_floor()) {
        die("Unexpectedly needs info monst struct");
      }
    }
  }
}

void Thing::new_itemp(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _itemp)) {
    _itemp = new ThingItem();
    // uncomment to see who allocates things
    // err("New monst item");
    newptr(_itemp, "ThingItem");

    if (mytp && (tp_id != -1)) {
      //
      // Walls and rock can be destroyed, hence no checks
      //
      if (is_wall() || is_dirt() || is_the_grid || is_floor()) {
        die("Unexpectedly needs item monst struct");
      }
    }
  }
}

void Thing::new_aip(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _aip)) {
    _aip = new ThingAi();
    // uncomment to see who allocates things
    // err("New monst ai");
    newptr(_aip, "ThingAi");
  }
}

ThingInfop Thing::get_or_alloc_infop(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _infop)) {
    new_infop();
  }
  verify(_infop);
  return _infop;
}

ThingItemp Thing::get_or_alloc_itemp(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _itemp)) {
    new_itemp();
  }
  verify(_itemp);
  return _itemp;
}

ThingAip Thing::get_or_alloc_aip(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! _aip)) {
    new_aip();
  }
  verify(_aip);
  return _aip;
}

ThingInfop Thing::get_infop(void)
{
  TRACE_AND_INDENT();
  if (! _infop) {
    die("no _infop");
  }
  verify(_infop);
  return _infop;
}

ThingItemp Thing::get_itemp(void)
{
  TRACE_AND_INDENT();
  if (! _itemp) {
    die("no _itemp");
  }
  verify(_itemp);
  return _itemp;
}

ThingAip Thing::get_aip(void)
{
  TRACE_AND_INDENT();
  if (! _aip) {
    die("no _aip");
  }
  verify(_aip);
  return _aip;
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_age_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->age_map);
}

void Thing::clear_age_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  get_aip()->age_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// seen_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_seen_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->seen_map);
}

void Thing::clear_seen_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  get_aip()->seen_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// interrupt_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_interrupt_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->interrupt_map);
}

void Thing::clear_interrupt_map(void)
{
  TRACE_AND_INDENT();
  new_aip();
  get_aip()->interrupt_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// _dmap_can_see
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::get_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->dmap_can_see);
}

void Thing::clear_dmap_can_see(void)
{
  TRACE_AND_INDENT();
  new_aip();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      set(get_aip()->dmap_can_see.val, x, y, DMAP_IS_WALL);
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// can_see_currently
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::get_can_see_currently(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->can_see_currently);
}

void Thing::clear_can_see_currently(void)
{
  TRACE_AND_INDENT();
  new_aip();
  get_aip()->can_see_currently.can_see = {};
}

////////////////////////////////////////////////////////////////////////////
// can_see_ever
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::get_can_see_ever(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (&get_aip()->can_see_ever);
}

void Thing::clear_can_see_ever(void)
{
  TRACE_AND_INDENT();
  new_aip();
  get_aip()->can_see_ever.can_see = {};
}

int Thing::item_height(void)
{
  TRACE_AND_INDENT();
  return (tp()->item_height());
}

int Thing::item_width(void)
{
  TRACE_AND_INDENT();
  return (tp()->item_width());
}

int Thing::capacity_height(void)
{
  TRACE_AND_INDENT();
  new_infop();
  if (get_infop()->capacity_height) {
    return get_infop()->capacity_height;
  }
  return (tp()->capacity_height());
}

int Thing::capacity_width(void)
{
  TRACE_AND_INDENT();
  new_infop();
  if (get_infop()->capacity_width) {
    return get_infop()->capacity_width;
  }
  return (tp()->capacity_width());
}

int Thing::monst_size(void)
{
  TRACE_AND_INDENT();
  return (tp()->monst_size());
}

int Thing::rarity(void)
{
  TRACE_AND_INDENT();
  return (tp()->rarity());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
point Thing::get_lunge_to(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->lunge_to);
  } else {
    return (point(0, 0));
  }
}

void Thing::set_lunge_to(point v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->lunge_to = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_height(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->bounce_height);
  } else {
    return 0;
  }
}

void Thing::set_bounce_height(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fall_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fall_height(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->fall_height);
  } else {
    return 0;
  }
}

void Thing::set_fall_height(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->fall_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_fade(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->bounce_fade);
  } else {
    return 0;
  }
}

void Thing::set_bounce_fade(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->bounce_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_bounce_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->bounce_count);
  } else {
    return 0;
  }
}

void Thing::set_bounce_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->bounce_count = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_height(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->fadeup_height);
  } else {
    return 0;
  }
}

void Thing::set_fadeup_height(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->fadeup_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_fade(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->fadeup_fade);
  } else {
    return 0;
  }
}

void Thing::set_fadeup_fade(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->fadeup_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// wobble
////////////////////////////////////////////////////////////////////////////
float Thing::get_wobble(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->wobble);
  } else {
    return 0;
  }
}

void Thing::set_wobble(float v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->wobble = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::get_msg(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->msg);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::set_msg(const std::string &v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// dead_reason
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::get_dead_reason(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->dead_reason);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::set_dead_reason(const std::string &v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->dead_reason = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::get_submerged_offset(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    //
    // Floating when dead?
    //
    if (is_dead) {
      return (get_infop()->submerged_offset / 2);
    }

    return (get_infop()->submerged_offset);
  } else {
    return 0;
  }
}

void Thing::set_submerged_offset(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  get_infop()->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// gold
////////////////////////////////////////////////////////////////////////////
int Thing::get_gold(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->gold);
  } else {
    return 0;
  }
}

int Thing::set_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->gold = v);
  return (n);
}

int Thing::decr_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->gold -= v);
  if (get_infop()->gold < 0) {
    get_infop()->gold = 0;
  }
  return (n);
}

int Thing::incr_gold(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->gold += v);
  return (n);
}

int Thing::decr_gold(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->gold--);
  if (get_infop()->gold < 0) {
    get_infop()->gold = 0;
  }
  return (n);
}

int Thing::incr_gold(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->gold++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// score
////////////////////////////////////////////////////////////////////////////
int Thing::get_score(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->score);
  } else {
    return 0;
  }
}

void Thing::set_score(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  get_infop()->score = v;
}

void Thing::incr_score(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  get_infop()->score += v;
}

////////////////////////////////////////////////////////////////////////////
// keys
////////////////////////////////////////////////////////////////////////////
int Thing::get_keys(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->keys);
  } else {
    return 0;
  }
}

int Thing::set_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->keys = v);
  return (n);
}

int Thing::decr_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->keys -= v);
  if (get_infop()->keys < 0) {
    get_infop()->keys = 0;
  }
  return (n);
}

int Thing::incr_keys(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->keys += v);
  return (n);
}

int Thing::decr_keys(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->keys--);
  if (get_infop()->keys < 0) {
    get_infop()->keys = 0;
  }
  return (n);
}

int Thing::incr_keys(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->keys++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::get_health(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->health;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->health = v);
  return (n);
}

int Thing::decr_health(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health -= v);
  return (n);
}

int Thing::incr_health(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health += v);
  return (n);
}

int Thing::decr_health(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health--);
  return (n);
}

int Thing::incr_health(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_health_max(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->health_max);
  } else {
    return 0;
  }
}

int Thing::set_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health_max = v);
  return (n);
}

int Thing::decr_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health_max -= v);
  return (n);
}

int Thing::incr_health_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health_max += v);
  return (n);
}

int Thing::decr_health_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health_max--);
  return (n);
}

int Thing::incr_health_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->health_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_defence(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->stat_defence;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->stat_defence = v);
  return (n);
}

int Thing::decr_stat_defence(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_defence -= v);
  if (get_infop()->stat_defence < 0) {
    get_infop()->stat_defence = 0;
  }
  return (n);
}

int Thing::incr_stat_defence(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_defence += v);
  return (n);
}

int Thing::decr_stat_defence(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_defence--);
  if (get_infop()->stat_defence < 0) {
    get_infop()->stat_defence = 0;
  }
  return (n);
}

int Thing::incr_stat_defence(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_defence++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats19
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats19(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats19);
  } else {
    return 0;
  }
}

int Thing::set_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats19 = v);
  return (n);
}

int Thing::decr_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats19 -= v);
  return (n);
}

int Thing::incr_stats19(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats19 += v);
  return (n);
}

int Thing::decr_stats19(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats19--);
  return (n);
}

int Thing::incr_stats19(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats19++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stamina_max(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stamina_max);
  } else {
    return 0;
  }
}

int Thing::set_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stamina_max = v);
  return (n);
}

int Thing::decr_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stamina_max -= v);
  return (n);
}

int Thing::incr_stamina_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stamina_max += v);
  return (n);
}

int Thing::decr_stamina_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stamina_max--);
  return (n);
}

int Thing::incr_stamina_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stamina_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_enchant_max(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->enchant_max);
  } else {
    return 0;
  }
}

int Thing::set_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->enchant_max = v);
  return (n);
}

int Thing::decr_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->enchant_max -= v);
  return (n);
}

int Thing::incr_enchant_max(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->enchant_max += v);
  return (n);
}

int Thing::decr_enchant_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->enchant_max--);
  return (n);
}

int Thing::incr_enchant_max(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->enchant_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_resurrect_when
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_resurrect_when(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_resurrect_when);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->tick_resurrect_when = v);
  return (n);
}

uint32_t Thing::decr_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->tick_resurrect_when -= v);
  return (n);
}

uint32_t Thing::incr_tick_resurrect_when(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->tick_resurrect_when += v);
  return (n);
}

uint32_t Thing::decr_tick_resurrect_when(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->tick_resurrect_when--);
  return (n);
}

uint32_t Thing::incr_tick_resurrect_when(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->tick_resurrect_when++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats01
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats01(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats01);
  } else {
    return 0;
  }
}

int Thing::set_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats01 = v);
  return (n);
}

int Thing::decr_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats01 -= v);
  return (n);
}

int Thing::incr_stats01(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats01 += v);
  return (n);
}

int Thing::decr_stats01(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats01--);
  return (n);
}

int Thing::incr_stats01(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats01++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats02(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats02);
  } else {
    return 0;
  }
}

int Thing::set_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats02 = v);
  return (n);
}

int Thing::decr_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats02 -= v);
  return (n);
}

int Thing::incr_stats02(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats02 += v);
  return (n);
}

int Thing::decr_stats02(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats02--);
  return (n);
}

int Thing::incr_stats02(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats02++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats03(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats03);
  } else {
    return 0;
  }
}

int Thing::set_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats03 = v);
  return (n);
}

int Thing::decr_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats03 -= v);
  return (n);
}

int Thing::incr_stats03(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats03 += v);
  return (n);
}

int Thing::decr_stats03(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats03--);
  return (n);
}

int Thing::incr_stats03(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats03++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats04(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats04);
  } else {
    return 0;
  }
}

int Thing::set_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats04 = v);
  return (n);
}

int Thing::decr_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats04 -= v);
  return (n);
}

int Thing::incr_stats04(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats04 += v);
  return (n);
}

int Thing::decr_stats04(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats04--);
  return (n);
}

int Thing::incr_stats04(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats04++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats05(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats05);
  } else {
    return 0;
  }
}

int Thing::set_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats05 = v);
  return (n);
}

int Thing::decr_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats05 -= v);
  return (n);
}

int Thing::incr_stats05(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats05 += v);
  return (n);
}

int Thing::decr_stats05(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats05--);
  return (n);
}

int Thing::incr_stats05(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats05++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats06(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats06);
  } else {
    return 0;
  }
}

int Thing::set_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats06 = v);
  return (n);
}

int Thing::decr_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats06 -= v);
  return (n);
}

int Thing::incr_stats06(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats06 += v);
  return (n);
}

int Thing::decr_stats06(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats06--);
  return (n);
}

int Thing::incr_stats06(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats06++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats07(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats07);
  } else {
    return 0;
  }
}

int Thing::set_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats07 = v);
  return (n);
}

int Thing::decr_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats07 -= v);
  return (n);
}

int Thing::incr_stats07(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats07 += v);
  return (n);
}

int Thing::decr_stats07(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats07--);
  return (n);
}

int Thing::incr_stats07(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats07++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats08
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats08(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats08);
  } else {
    return 0;
  }
}

int Thing::set_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats08 = v);
  return (n);
}

int Thing::decr_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats08 -= v);
  return (n);
}

int Thing::incr_stats08(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats08 += v);
  return (n);
}

int Thing::decr_stats08(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats08--);
  return (n);
}

int Thing::incr_stats08(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats08++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats09(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats09);
  } else {
    return 0;
  }
}

int Thing::set_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats09 = v);
  return (n);
}

int Thing::decr_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats09 -= v);
  return (n);
}

int Thing::incr_stats09(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats09 += v);
  return (n);
}

int Thing::decr_stats09(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats09--);
  return (n);
}

int Thing::incr_stats09(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats09++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats10
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats10(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats10);
  } else {
    return 0;
  }
}

int Thing::set_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats10 = v);
  return (n);
}

int Thing::decr_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats10 -= v);
  return (n);
}

int Thing::incr_stats10(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats10 += v);
  return (n);
}

int Thing::decr_stats10(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats10--);
  return (n);
}

int Thing::incr_stats10(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats10++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats11
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats11(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats11);
  } else {
    return 0;
  }
}

int Thing::set_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats11 = v);
  return (n);
}

int Thing::decr_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats11 -= v);
  return (n);
}

int Thing::incr_stats11(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats11 += v);
  return (n);
}

int Thing::decr_stats11(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats11--);
  return (n);
}

int Thing::incr_stats11(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats11++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats12
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats12(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats12);
  } else {
    return 0;
  }
}

int Thing::set_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats12 = v);
  return (n);
}

int Thing::decr_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats12 -= v);
  return (n);
}

int Thing::incr_stats12(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats12 += v);
  return (n);
}

int Thing::decr_stats12(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats12--);
  return (n);
}

int Thing::incr_stats12(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats12++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_constitution
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_constitution(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stat_constitution);
  } else {
    return 0;
  }
}

int Thing::set_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_constitution = v);
  return (n);
}

int Thing::decr_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_constitution -= v);
  return (n);
}

int Thing::incr_stat_constitution(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_constitution += v);
  return (n);
}

int Thing::decr_stat_constitution(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_constitution--);
  return (n);
}

int Thing::incr_stat_constitution(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_constitution++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_attack
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_attack(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stat_attack);
  } else {
    return 0;
  }
}

int Thing::set_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_attack = v);
  return (n);
}

int Thing::decr_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_attack -= v);
  return (n);
}

int Thing::incr_stat_attack(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_attack += v);
  return (n);
}

int Thing::decr_stat_attack(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_attack--);
  return (n);
}

int Thing::incr_stat_attack(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_attack++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats17
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats17(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stats17);
  } else {
    return 0;
  }
}

int Thing::set_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats17 = v);
  return (n);
}

int Thing::decr_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats17 -= v);
  return (n);
}

int Thing::incr_stats17(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats17 += v);
  return (n);
}

int Thing::decr_stats17(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats17--);
  return (n);
}

int Thing::incr_stats17(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stats17++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// throw_distance
////////////////////////////////////////////////////////////////////////////
int Thing::get_throw_distance(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->throw_distance);
  } else {
    return 0;
  }
}

int Thing::set_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->throw_distance = v);
  return (n);
}

int Thing::decr_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->throw_distance -= v);
  return (n);
}

int Thing::incr_throw_distance(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->throw_distance += v);
  return (n);
}

int Thing::decr_throw_distance(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->throw_distance--);
  return (n);
}

int Thing::incr_throw_distance(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->throw_distance++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina
////////////////////////////////////////////////////////////////////////////
int Thing::get_stamina(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->stamina;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->stamina = v);
  return (n);
}

int Thing::decr_stamina(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->stamina -= v);
  if (get_infop()->stamina < 0) {
    get_infop()->stamina = 0;
  }
  return (n);
}

int Thing::incr_stamina(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->stamina += v);
  return (n);
}

int Thing::decr_stamina(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->stamina--);
  if (get_infop()->stamina < 0) {
    get_infop()->stamina = 0;
  }
  return (n);
}

int Thing::incr_stamina(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->stamina++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant
////////////////////////////////////////////////////////////////////////////
int Thing::get_enchant(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->enchant;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->enchant = v);
  return (n);
}

int Thing::decr_enchant(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->enchant -= v);
  if (get_infop()->enchant < 0) {
    get_infop()->enchant = 0;
  }
  return (n);
}

int Thing::incr_enchant(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->enchant += v);
  return (n);
}

int Thing::decr_enchant(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->enchant--);
  if (get_infop()->enchant < 0) {
    get_infop()->enchant = 0;
  }
  return (n);
}

int Thing::incr_enchant(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->enchant++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// poison
////////////////////////////////////////////////////////////////////////////
int Thing::get_poison(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->poison;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->poison = v);
  if (get_infop()->poison < 0) {
    get_infop()->poison = 0;
  }
  return (n);
}

int Thing::decr_poison(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->poison -= v);
  if (get_infop()->poison < 0) {
    get_infop()->poison = 0;
  }
  return (n);
}

int Thing::incr_poison(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->poison += v);
  if (get_infop()->poison < 0) {
    get_infop()->poison = 0;
  }
  return (n);
}

int Thing::decr_poison(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->poison--);
  if (get_infop()->poison < 0) {
    get_infop()->poison = 0;
  }
  return (n);
}

int Thing::incr_poison(void)
{
  TRACE_AND_INDENT();
  new_infop();
  auto n = (get_infop()->poison++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_strength
////////////////////////////////////////////////////////////////////////////
int Thing::get_stat_strength(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->stat_strength);
  } else {
    return 0;
  }
}

int Thing::set_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_strength = v);
  return (n);
}

int Thing::decr_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_strength -= v);
  return (n);
}

int Thing::incr_stat_strength(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_strength += v);
  return (n);
}

int Thing::decr_stat_strength(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_strength--);
  return (n);
}

int Thing::incr_stat_strength(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_strength++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// owned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_owned_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->owned_count);
  } else {
    return 0;
  }
}

int Thing::set_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owned_count = v);
}

int Thing::decr_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owned_count -= v);
}

int Thing::incr_owned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owned_count += v);
}

int Thing::decr_owned_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owned_count--);
}

int Thing::incr_owned_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// minion_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_minion_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->minion_count);
  } else {
    return 0;
  }
}

int Thing::set_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->minion_count = v);
}

int Thing::decr_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->minion_count -= v);
}

int Thing::incr_minion_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->minion_count += v);
}

int Thing::decr_minion_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->minion_count--);
}

int Thing::incr_minion_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->minion_count++);
}

////////////////////////////////////////////////////////////////////////////
// spawned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_spawned_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->spawned_count);
  } else {
    return 0;
  }
}

int Thing::set_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawned_count = v);
}

int Thing::decr_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawned_count -= v);
}

int Thing::incr_spawned_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawned_count += v);
}

int Thing::decr_spawned_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawned_count--);
}

int Thing::incr_spawned_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->spawned_count++);
}

////////////////////////////////////////////////////////////////////////////
// charge_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_charge_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->charge_count);
  } else {
    return 0;
  }
}

int Thing::set_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->charge_count = v);
}

int Thing::decr_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->charge_count -= v);
}

int Thing::incr_charge_count(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->charge_count += v);
}

int Thing::decr_charge_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->charge_count--);
}

int Thing::incr_charge_count(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->charge_count++);
}

////////////////////////////////////////////////////////////////////////////
// idle_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_idle_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_aip()) {
    verify(maybe_aip());
    return (get_aip()->idle_count);
  } else {
    return 0;
  }
}

int Thing::set_idle_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->idle_count = v);
}

int Thing::decr_idle_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->idle_count -= v);
}

int Thing::incr_idle_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->idle_count += v);
}

int Thing::decr_idle_count(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->idle_count--);
}

int Thing::incr_idle_count(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->idle_count++);
}

////////////////////////////////////////////////////////////////////////////
// stuck_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_stuck_count(void)
{
  TRACE_AND_INDENT();
  if (maybe_aip()) {
    verify(maybe_aip());
    return (get_aip()->stuck_count);
  } else {
    return 0;
  }
}

int Thing::set_stuck_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->stuck_count = v);
}

int Thing::decr_stuck_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->stuck_count -= v);
}

int Thing::incr_stuck_count(int v)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->stuck_count += v);
}

int Thing::decr_stuck_count(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->stuck_count--);
}

int Thing::incr_stuck_count(void)
{
  TRACE_AND_INDENT();
  new_aip();
  return (get_aip()->stuck_count++);
}

////////////////////////////////////////////////////////////////////////////
// lifespan
////////////////////////////////////////////////////////////////////////////
int Thing::get_lifespan(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->lifespan);
  } else {
    return 0;
  }
}

int Thing::set_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->lifespan = v);
}

int Thing::decr_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->lifespan -= v);
}

int Thing::incr_lifespan(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->lifespan += v);
}

int Thing::decr_lifespan(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->lifespan--);
}

int Thing::incr_lifespan(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->lifespan++);
}

////////////////////////////////////////////////////////////////////////////
// light_strength
////////////////////////////////////////////////////////////////////////////
int Thing::get_initial_light_strength(void)
{
  TRACE_AND_INDENT();
  return (tp()->light_strength());
}

int Thing::get_light_strength(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return get_initial_light_strength();
  }

  verify(maybe_infop());
  uint8_t light_strength = get_infop()->light_strength;

  if (! light_strength) {
    light_strength = get_initial_light_strength();
  }

  if (is_player()) {
    get_light_strength_including_torch_effect(light_strength);
  }

  get_infop()->light_strength = light_strength;
  return light_strength;
}

int Thing::update_light_strength(void)
{
  TRACE_AND_INDENT();
  if (! maybe_infop()) {
    return get_initial_light_strength();
  }

  verify(maybe_infop());
  uint8_t light_strength = get_infop()->light_strength;

  if (! light_strength) {
    light_strength = get_initial_light_strength();
  }

  if (is_player()) {
    update_light_strength_including_torch_effect(light_strength);
  }

  get_infop()->light_strength = light_strength;
  return light_strength;
}

int Thing::set_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->light_strength = v);
}

int Thing::decr_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->light_strength -= v);
}

int Thing::incr_light_strength(int v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->light_strength += v);
}

int Thing::decr_light_strength(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->light_strength--);
}

int Thing::incr_light_strength(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->light_strength++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_did_something(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_last_did_something);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_did_something = v);
}

uint32_t Thing::decr_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_did_something -= v);
}

uint32_t Thing::incr_tick_last_did_something(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_did_something += v);
}

uint32_t Thing::decr_tick_last_did_something(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_did_something--);
}

uint32_t Thing::incr_tick_last_did_something(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_dropped
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_dropped(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_last_dropped);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_dropped = v);
}

uint32_t Thing::decr_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_dropped -= v);
}

uint32_t Thing::incr_tick_last_dropped(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_dropped += v);
}

uint32_t Thing::decr_tick_last_dropped(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_dropped--);
}

uint32_t Thing::incr_tick_last_dropped(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_dropped++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_location_check
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_location_check(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_last_location_check);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_location_check = v);
}

uint32_t Thing::decr_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_location_check -= v);
}

uint32_t Thing::incr_tick_last_location_check(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_location_check += v);
}

uint32_t Thing::decr_tick_last_location_check(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_location_check--);
}

uint32_t Thing::incr_tick_last_location_check(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_location_check++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_escape
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_escape(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_last_escape);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_escape = v);
}

uint32_t Thing::decr_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_escape -= v);
}

uint32_t Thing::incr_tick_last_escape(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_escape += v);
}

uint32_t Thing::decr_tick_last_escape(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_escape--);
}

uint32_t Thing::incr_tick_last_escape(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_escape++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_level_change
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_level_change(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->tick_last_level_change);
  } else {
    return 0;
  }
}

uint32_t Thing::set_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_level_change = v);
}

uint32_t Thing::decr_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_level_change -= v);
}

uint32_t Thing::incr_tick_last_level_change(uint32_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_level_change += v);
}

uint32_t Thing::decr_tick_last_level_change(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_level_change--);
}

uint32_t Thing::incr_tick_last_level_change(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->tick_last_level_change++);
}

////////////////////////////////////////////////////////////////////////////
// where_i_dropped_an_item_last
////////////////////////////////////////////////////////////////////////////
point Thing::get_where_i_dropped_an_item_last(void)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    verify(maybe_itemp());
    return (get_itemp()->where_i_dropped_an_item_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::set_where_i_dropped_an_item_last(point v)
{
  TRACE_AND_INDENT();
  new_itemp();
  return (get_itemp()->where_i_dropped_an_item_last = v);
}

////////////////////////////////////////////////////////////////////////////
// where_i_failed_to_collect_last
////////////////////////////////////////////////////////////////////////////
point Thing::get_where_i_failed_to_collect_last(void)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    verify(maybe_itemp());
    return (get_itemp()->where_i_failed_to_collect_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::set_where_i_failed_to_collect_last(point v)
{
  TRACE_AND_INDENT();
  new_itemp();
  return (get_itemp()->where_i_failed_to_collect_last = v);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_lunge_begin(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_lunge_begin);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_begin = v);
}

ts_t Thing::decr_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_begin -= v);
}

ts_t Thing::incr_ts_lunge_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_begin += v);
}

ts_t Thing::decr_ts_lunge_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_begin--);
}

ts_t Thing::incr_ts_lunge_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_lunge_end(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_lunge_end);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_end = v);
}

ts_t Thing::decr_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_end -= v);
}

ts_t Thing::incr_ts_lunge_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_end += v);
}

ts_t Thing::decr_ts_lunge_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_end--);
}

ts_t Thing::incr_ts_lunge_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_lunge_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_bounce_begin(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_bounce_begin);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_begin = v);
}

ts_t Thing::decr_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_begin -= v);
}

ts_t Thing::incr_ts_bounce_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_begin += v);
}

ts_t Thing::decr_ts_bounce_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_begin--);
}

ts_t Thing::incr_ts_bounce_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_bounce_end(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_bounce_end);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_end = v);
}

ts_t Thing::decr_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_end -= v);
}

ts_t Thing::incr_ts_bounce_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_end += v);
}

ts_t Thing::decr_ts_bounce_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_end--);
}

ts_t Thing::incr_ts_bounce_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fadeup_begin(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_fadeup_begin);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_begin = v);
}

ts_t Thing::decr_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_begin -= v);
}

ts_t Thing::incr_ts_fadeup_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_begin += v);
}

ts_t Thing::decr_ts_fadeup_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_begin--);
}

ts_t Thing::incr_ts_fadeup_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fadeup_end(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_fadeup_end);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_end = v);
}

ts_t Thing::decr_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_end -= v);
}

ts_t Thing::incr_ts_fadeup_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_end += v);
}

ts_t Thing::decr_ts_fadeup_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_end--);
}

ts_t Thing::incr_ts_fadeup_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fadeup_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_flip_start
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_flip_start(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_flip_start);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_flip_start = v);
}

ts_t Thing::decr_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_flip_start -= v);
}

ts_t Thing::incr_ts_flip_start(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_flip_start += v);
}

ts_t Thing::decr_ts_flip_start(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_flip_start--);
}

ts_t Thing::incr_ts_flip_start(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// ts_anim_delay_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_anim_delay_end(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_anim_delay_end);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_anim_delay_end = v);
}

ts_t Thing::decr_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_anim_delay_end -= v);
}

ts_t Thing::incr_ts_anim_delay_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_anim_delay_end += v);
}

ts_t Thing::decr_ts_anim_delay_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_anim_delay_end--);
}

ts_t Thing::incr_ts_anim_delay_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_anim_delay_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fall_begin(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_fall_begin);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_begin = v);
}

ts_t Thing::decr_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_begin -= v);
}

ts_t Thing::incr_ts_fall_begin(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_begin += v);
}

ts_t Thing::decr_ts_fall_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_begin--);
}

ts_t Thing::incr_ts_fall_begin(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::get_ts_fall_end(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    verify(maybe_infop());
    return (get_infop()->ts_fall_end);
  } else {
    return 0;
  }
}

ts_t Thing::set_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_end = v);
}

ts_t Thing::decr_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_end -= v);
}

ts_t Thing::incr_ts_fall_end(ts_t v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_end += v);
}

ts_t Thing::decr_ts_fall_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_end--);
}

ts_t Thing::incr_ts_fall_end(void)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->ts_fall_end++);
}

////////////////////////////////////////////////////////////////////////////
// equip_id_carry_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_equip_id_carry_anim(int equip)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    return (get_itemp()->equip_id_carry_anim[ equip ]);
  } else {
    return NoThingId;
  }
}

ThingId Thing::set_equip_id_carry_anim(ThingId v, int equip)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_itemp()->equip_id_carry_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_id_use_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_equip_id_use_anim(int equip)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    return (get_itemp()->equip_id_use_anim[ equip ]);
  } else {
    return NoThingId;
  }
}

ThingId Thing::set_equip_id_use_anim(ThingId v, int equip)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_itemp()->equip_id_use_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_tp_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_equip_id(int equip)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    // con("get weapon %08" PRIx32 "",  get_itemp()->equip_id);
    return (get_itemp()->equip_id[ equip ]);
  } else {
    // con("get equip id => none");
    return NoThingId;
  }
}

ThingId Thing::set_equip_id(ThingId v, int equip)
{
  TRACE_AND_INDENT();
  new_infop();
  // con("set weapon %08" PRIx32 "", v);
  return (get_itemp()->equip_id[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_on_fire_anim_id(void)
{
  TRACE_AND_INDENT();
  if (maybe_infop()) {
    return (get_infop()->on_fire_id_anim);
  } else {
    return NoThingId;
  }
}

ThingId Thing::set_on_fire_anim_id(ThingId v)
{
  TRACE_AND_INDENT();
  new_infop();
  return (get_infop()->on_fire_id_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// current_damage
////////////////////////////////////////////////////////////////////////////
int Thing::get_current_damage(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  if (maybe_infop()) {
    verify(maybe_infop());
    v = get_infop()->current_damage;
  }
  auto owner = get_immediate_owner();
  if (owner && (owner != this)) {
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
  new_infop();
  auto n = (get_infop()->current_damage = v);
  return (n);
}

int Thing::decr_current_damage(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->current_damage -= v);
  return (n);
}

int Thing::incr_current_damage(int v)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->current_damage += v);
  return (n);
}

int Thing::decr_current_damage(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->current_damage--);
  return (n);
}

int Thing::incr_current_damage(void)
{
  TRACE_AND_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->current_damage++);
  return (n);
}

const std::string &Thing::gfx_anim_use(void)
{
  TRACE_AND_INDENT();
  return (tp()->gfx_anim_use());
}

const std::string &Thing::laser_name(void)
{
  TRACE_AND_INDENT();
  return (tp()->laser_name());
}

const std::string &Thing::light_color(void)
{
  TRACE_AND_INDENT();
  return (tp()->light_color());
}

const std::string &Thing::long_text_description(void)
{
  TRACE_AND_INDENT();
  return (tp()->long_text_description());
}

const std::string &Thing::name(void)
{
  TRACE_AND_INDENT();
  return (tp()->name());
}

const std::string &Thing::on_birth_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_birth_do());
}

const std::string &Thing::on_you_bite_attack_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_you_bite_attack_do());
}

const std::string &Thing::on_born_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_born_do());
}

const std::string &Thing::on_death_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_death_do());
}

const std::string &Thing::on_enchant_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_enchant_do());
}

const std::string &Thing::on_fall_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_fall_do());
}

const std::string &Thing::on_you_are_on_fire_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_you_are_on_fire_do());
}

const std::string &Thing::on_firing_at_something_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_firing_at_something_do());
}

const std::string &Thing::on_you_are_hit_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_you_are_hit_do());
}

const std::string &Thing::on_lifespan_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_lifespan_do());
}

const std::string &Thing::on_you_miss_do_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_you_miss_do_do());
}

const std::string &Thing::on_move_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_move_do());
}

const std::string &Thing::on_open_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_open_do());
}

const std::string &Thing::on_tick_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_tick_do());
}

const std::string &Thing::on_use_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_use_do());
}

const std::string &Thing::on_final_use_do(void)
{
  TRACE_AND_INDENT();
  return (tp()->on_final_use_do());
}

const std::string &Thing::projectile_name(void)
{
  TRACE_AND_INDENT();
  return (tp()->projectile_name());
}

const std::string &Thing::short_text_name(void)
{
  TRACE_AND_INDENT();
  return (tp()->short_text_name());
}

const std::string &Thing::spawn_on_shoved(void)
{
  TRACE_AND_INDENT();
  return (tp()->spawn_on_shoved());
}

const std::string &Thing::str1(void)
{
  TRACE_AND_INDENT();
  return (tp()->str1());
}

const std::string &Thing::str2(void)
{
  TRACE_AND_INDENT();
  return (tp()->str2());
}

const std::string &Thing::str4(void)
{
  TRACE_AND_INDENT();
  return (tp()->str4());
}

const std::string &Thing::str5(void)
{
  TRACE_AND_INDENT();
  return (tp()->str5());
}

const std::string &Thing::text_description(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_description());
}

const std::string &Thing::text_enchant(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_enchant());
}

const std::string &Thing::text_hits(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_hits());
}

const std::string &Thing::text_name(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_name());
}

const std::string &Thing::text_skill(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_skill());
}

const std::string &Thing::text_debuff(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_debuff());
}

const std::string &Thing::text_buff(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_buff());
}

const std::string &Thing::text_title(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_title());
}

const std::string &Thing::text_unused(void)
{
  TRACE_AND_INDENT();
  return (tp()->text_unused());
}

const std::string &Thing::equip_carry_anim(void)
{
  TRACE_AND_INDENT();
  return (tp()->equip_carry_anim());
}

std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::get_bag(void)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    return (&get_itemp()->bag);
  } else {
    DIE("No bag");
  }
}

const std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::get_const_bag(void)
{
  TRACE_AND_INDENT();
  if (maybe_itemp()) {
    return (&get_itemp()->bag);
  } else {
    DIE("No bag");
  }
}

const std::string &Thing::title(void)
{
  if (g_opt_player_name.empty()) {
    return text_title();
  } else {
    return g_opt_player_name;
  }
}

int Thing::get_group(void)
{
  if (is_laser()) {
    return THING_GROUP_PRIO_HIGH;
  }
  if (is_tmp_thing()) {
    return THING_GROUP_TMP;
  }
  return THING_GROUP_PRIO_NORMAL;
}
