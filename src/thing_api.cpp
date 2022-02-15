//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_rightbar.hpp"

//
// Dice
//
const Dice &Thing::on_idle_tick_freq_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_idle_tick_freq_dice());
}

const std::string &Thing::on_idle_tick_freq_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_idle_tick_freq_dice_str());
}

int Thing::on_idle_tick_freq(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_idle_tick_freq_dice().roll());
}

const Dice &Thing::spawn_group_size_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice());
}

const std::string &Thing::spawn_group_size_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice_str());
}

int Thing::spawn_group_size(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice().roll());
}

const Dice &Thing::nutrition_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->nutrition_dice());
}

const std::string &Thing::nutrition_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->nutrition_dice_str());
}

int Thing::nutrition_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->nutrition_dice().roll());
}

const Dice &Thing::health_initial_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice());
}

const std::string &Thing::health_initial_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice_str());
}

int Thing::health_initial(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice().roll());
}

const Dice &Thing::gold_value_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->gold_value_dice());
}

const std::string &Thing::gold_value_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->gold_value_dice_str());
}

int Thing::gold_value(void)
{
  TRACE_NO_INDENT();
  return (tp()->gold_value_dice().roll());
}

const Dice &Thing::lifespan_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice());
}

const std::string &Thing::lifespan_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice_str());
}

int Thing::lifespan_initial(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice().roll());
}

const Dice &Thing::resurrect_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice());
}

const std::string &Thing::resurrect_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice_str());
}

int Thing::resurrect_when(void)
{
  TRACE_NO_INDENT();
  return (tp()->resurrect_dice().roll());
}

float Thing::distance_avoid_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_avoid());
}

int Thing::ai_resent_count(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_resent_count());
}

int Thing::ai_obstacle(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_obstacle());
}

float Thing::distance_vision_get(void)
{
  TRACE_NO_INDENT();

  //
  // Limit vision by torch light if needed.
  //
  auto v = tp()->distance_vision();

  if (is_able_to_see_in_the_dark()) {
    return v;
  }

  auto l = light_power_get();
  if (l < v) {
    return l;
  }
  return v;
}

int Thing::attack_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_eater());
}

int Thing::attack_humanoid(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_humanoid());
}

int Thing::attack_living(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_living());
}

int Thing::attack_lunge(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_lunge());
}

int Thing::attack_meat(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_meat());
}

int Thing::ai_shove_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_shove_chance_d1000());
}

int Thing::unused_chance1_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance1_d1000());
}

int Thing::unused_chance2_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance2_d1000());
}

int Thing::unused_chance3_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance3_d1000());
}

int Thing::unused_chance4_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance4_d1000());
}

int Thing::unused_chance5_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance5_d1000());
}

int Thing::unused_chance6_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance6_d1000());
}

int Thing::melting_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->melting_chance_d1000());
}

int Thing::break_chance_d10000(void)
{
  TRACE_NO_INDENT();

  int chance = tp()->break_chance_d10000();
  int e      = enchant_level();
  while (e-- > 0) {
    chance /= 2;
  }

  return chance;
}

int Thing::damage_melee_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_melee_chance_d1000());
}

int Thing::damage_natural_attack_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_natural_attack_chance_d1000());
}

int Thing::is_able_to_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_shove());
}

int Thing::blast_max_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->blast_max_radius());
}

int Thing::blast_min_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->blast_min_radius());
}

int Thing::collision_hit_priority(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_priority());
}

int Thing::collision_check(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_check());
}

int Thing::damage_received_doubled_from_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_acid());
}

int Thing::damage_received_doubled_from_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_fire());
}

int Thing::damage_received_doubled_from_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_poison());
}

int Thing::damage_received_doubled_from_necrosis(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_necrosis());
}

int Thing::damage_received_doubled_from_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_water());
}

int Thing::enchant_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->enchant_level());
}

int Thing::enchant_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->enchant_max());
}

int Thing::initial_charge_count(void)
{
  TRACE_NO_INDENT();
  return (tp()->charge_count());
}

int Thing::gfx_an_animation_only(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_an_animation_only());
}

int Thing::gfx_animated_can_hflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_animated_can_hflip());
}

int Thing::gfx_animated_can_vflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_animated_can_vflip());
}

int Thing::gfx_animated_no_dir(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_animated_no_dir());
}

int Thing::gfx_animated(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_animated());
}

int Thing::gfx_attack_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_attack_anim());
}

int Thing::gfx_bounce_always(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_bounce_always());
}

int Thing::gfx_bounce_on_move(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_bounce_on_move());
}

int Thing::gfx_dead_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_dead_anim());
}

int Thing::gfx_flickers(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_flickers());
}

int Thing::gfx_glows(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_glows());
}

int Thing::gfx_health_bar_autohide(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_health_bar_autohide());
}

int Thing::gfx_health_bar_shown(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_health_bar_shown());
}

int Thing::gfx_long_shadow_caster(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_long_shadow_caster());
}

int Thing::gfx_on_fire_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_on_fire_anim());
}

int Thing::gfx_oversized_and_on_floor(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_oversized_and_on_floor());
}

int Thing::gfx_short_shadow_caster(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_short_shadow_caster());
}

int Thing::gfx_shown_in_bg(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_shown_in_bg());
}

int Thing::gfx_show_outlined(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_show_outlined());
}

int Thing::gfx_solid_shadow(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_solid_shadow());
}

int Thing::gfx_very_short_shadow_caster(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_very_short_shadow_caster());
}

int Thing::gfx_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_water());
}

int Thing::gfx_equip_carry_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_equip_carry_anim());
}

int Thing::environ_avoids_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_acid());
}

int Thing::environ_avoids_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_fire());
}

int Thing::environ_avoids_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_poison());
}

int Thing::environ_avoids_necrosis(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_necrosis());
}

int Thing::environ_avoids_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_water());
}

int Thing::hunger_health_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_health_pct());
}

int Thing::health_starving_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_starving_pct());
}

int Thing::is_able_to_change_levels(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_change_levels());
}

int Thing::is_able_to_fall(void)
{
  TRACE_NO_INDENT();

  //
  // Dead bats fall...
  //
  if (is_dead) {
    if (is_corpse_on_death()) {
      return true;
    }
  }

  return (tp()->is_able_to_fall());
}

int Thing::is_able_to_fire_at(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_fire_at());
}

int Thing::is_able_to_see_through_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_through_doors());
}

int Thing::is_able_to_walk_through_walls(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_walk_through_walls());
}

int Thing::is_immune_to_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_acid());
}

int Thing::is_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_acid());
}

int Thing::is_alive_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst() && ! is_dead);
}

int Thing::is_alive_on_end_of_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_alive_on_end_of_anim());
}

int Thing::is_always_hit(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_always_hit());
}

int Thing::is_ascend_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ascend_dungeon());
}

int Thing::is_ascend_sewer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ascend_sewer());
}

int Thing::is_attackable_by_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_attackable_by_monst());
}

int Thing::is_attackable_by_player(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_attackable_by_player());
}

int Thing::is_auto_collect_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_collect_item());
}

int Thing::is_bag_item_container(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item_container());
}

int Thing::is_bag_item_not_stackable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item_not_stackable());
}

int Thing::is_bag_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item());
}

int Thing::is_bag(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag());
}

int Thing::is_barrel(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_barrel());
}

int Thing::is_bleeder(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bleeder());
}

int Thing::is_red_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_splatter());
}

int Thing::is_red_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_blood());
}

int Thing::is_bones(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bones());
}

int Thing::is_brazier(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_brazier());
}

int Thing::is_bridge(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bridge());
}

int Thing::is_burnable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_burnable());
}

int Thing::is_carrier_of_treasure_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_treasure_class_a());
}

int Thing::is_carrier_of_treasure_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_treasure_class_b());
}

int Thing::is_carrier_of_treasure_class_c(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_treasure_class_c());
}

int Thing::is_carrier_of_weapon_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_weapon_class_a());
}

int Thing::is_carrier_of_weapon_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_weapon_class_b());
}

int Thing::is_carrier_of_weapon_class_c(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carrier_of_weapon_class_c());
}

int Thing::is_chasm(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_chasm());
}

int Thing::is_collectable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collectable());
}

int Thing::is_collect_as_keys(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collect_as_keys());
}

int Thing::is_collected_as_gold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collected_as_gold());
}

int Thing::is_combustible(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_combustible());
}

int Thing::is_corpse_on_death(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corpse_on_death());
}

int Thing::is_corpse(void)
{
  TRACE_NO_INDENT();
  return (is_dead && is_corpse_on_death());
}

int Thing::is_corridor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corridor());
}

int Thing::is_critical_to_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_critical_to_level());
}

int Thing::is_cursor_can_hover_over_x2_click(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_can_hover_over_x2_click());
}

int Thing::is_cursor_can_hover_over(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_can_hover_over());
}

int Thing::is_cursor_path(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path());
}

int Thing::is_cursor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor());
}

int Thing::is_dead_on_end_of_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_end_of_anim());
}

int Thing::is_dead_on_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_shove());
}

int Thing::is_dead_or_dying(void)
{
  TRACE_NO_INDENT();
  return is_dead || is_dying;
}

int Thing::is_debug_path(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debug_path());
}

int Thing::is_debug_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debug_type());
}

int Thing::is_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_deep_water());
}

int Thing::is_descend_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_descend_dungeon());
}

int Thing::is_descend_sewer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_descend_sewer());
}

int Thing::is_described_when_hovering_over(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_described_when_hovering_over());
}

int Thing::is_dirt(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dirt());
}

int Thing::is_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_door());
}

int Thing::is_droppable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_droppable());
}

int Thing::is_dry_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dry_grass());
}

int Thing::is_wet_grass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wet_grass());
}

int Thing::is_enchantable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_enchantable());
}

int Thing::is_enchantstone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_enchantstone());
}

int Thing::is_ethereal_mob(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ethereal_mob());
}

int Thing::is_ethereal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ethereal());
}

int Thing::is_explosion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_explosion());
}

int Thing::is_cursor_path_hazard_for_player(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path_hazard_for_player());
}

int Thing::is_heavy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_heavy());
}

int Thing::is_fearless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fearless());
}

int Thing::is_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fire());
}

int Thing::is_floating(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floating());
}

int Thing::is_floor_deco(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floor_deco());
}

int Thing::is_floor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floor());
}

int Thing::is_foilage(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_foilage());
}

int Thing::is_food_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_food_eater());
}

int Thing::is_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_food());
}

int Thing::is_gold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gold());
}

int Thing::is_hazard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hazard());
}

int Thing::is_hittable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hittable());
}

int Thing::is_humanoid(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_humanoid());
}

int Thing::hunger_is_insatiable(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_insatiable());
}

int Thing::is_toughness_very_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_toughness_very_hard());
}

int Thing::is_intelligent(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_intelligent());
}

int Thing::is_interesting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_interesting());
}

int Thing::is_item_carrier(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_carrier());
}

int Thing::is_item_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_eater());
}

int Thing::is_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item());
}

int Thing::is_jelly_baby_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jelly_baby_eater());
}

int Thing::is_jelly_baby(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jelly_baby());
}

int Thing::is_jelly_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jelly_eater());
}

int Thing::is_jelly_parent(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jelly_parent());
}

int Thing::is_jelly(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jelly());
}

int Thing::is_able_to_jump_randomly_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_randomly_chance_d1000());
}

int Thing::is_able_to_jump_attack_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_attack_chance_d1000());
}

int Thing::is_able_to_jump_onto_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_onto_chance_d1000());
}

int Thing::distance_jump(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_jump());
}

int Thing::is_able_to_jump_on_low_hp_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_on_low_hp_chance_d1000());
}

int Thing::is_able_to_jump(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump());
}

int Thing::is_able_to_collect_keys(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_collect_keys());
}

int Thing::is_key(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_key());
}

int Thing::is_destroyed_on_hit_or_miss(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_destroyed_on_hit_or_miss());
}

int Thing::is_destroyed_on_hitting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_destroyed_on_hitting());
}

int Thing::is_laser(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_laser());
}

int Thing::is_lava(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_lava());
}

int Thing::is_light_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_light_blocker());
}

int Thing::is_light_blocker_for_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_light_blocker_for_monst());
}

int Thing::is_gas_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gas_blocker());
}

int Thing::noise_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_blocker());
}

int Thing::is_living(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_living());
}

int Thing::is_loggable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_loggable());
}

int Thing::is_meat_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_meat_eater());
}

int Thing::is_meat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_meat());
}

int Thing::is_mob(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob());
}

int Thing::is_minion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_minion());
}

int Thing::is_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst());
}

int Thing::is_moveable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_moveable());
}

int Thing::is_obs_wall_or_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_wall_or_door());
}

int Thing::is_obs_destructable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_destructable());
}

int Thing::is_msg(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg());
}

int Thing::is_no_tile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_no_tile());
}

int Thing::is_openable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_openable());
}

int Thing::is_player(void)
{
  TRACE_NO_INDENT();
  return (is_the_player);
}

int Thing::is_poisonous_danger_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_poisonous_danger_level());
}

int Thing::is_necrotic_danger_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_necrotic_danger_level());
}

int Thing::is_potion_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_potion_eater());
}

int Thing::is_potion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_potion());
}

int Thing::is_projectile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_projectile());
}

int Thing::is_removeable_if_out_of_slots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_removeable_if_out_of_slots());
}

int Thing::is_resurrectable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_resurrectable());
}

int Thing::is_resurrected_or_resurrecting(void)
{
  TRACE_NO_INDENT();
  return (is_resurrected || is_resurrecting);
}

int Thing::is_ripple(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ripple());
}

int Thing::is_rock(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rock());
}

int Thing::is_able_to_jump_escape(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_escape());
}

int Thing::hunger_clock_tick_freq(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_clock_tick_freq());
}

int Thing::is_able_to_follow(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_follow());
}

int Thing::distance_leader_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_leader_max());
}

int Thing::distance_recruitment_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_recruitment_max());
}

float Thing::distance_recruitment_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_recruitment_max());
}

int Thing::spawn_group_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_radius());
}

int Thing::distance_minion_vision_shared(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_minion_vision_shared());
}

int Thing::is_able_to_use_weapons(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_weapons());
}

int Thing::is_bony(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bony());
}

int Thing::is_pink_blooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pink_blooded());
}

int Thing::is_pink_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pink_splatter());
}

int Thing::is_green_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_splatter());
}

int Thing::unused_flag1(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag1());
}

int Thing::unused_flag2(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag2());
}

int Thing::unused_flag3(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag3());
}

int Thing::unused_flag4(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag4());
}

int Thing::unused_flag5(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag5());
}

int Thing::unused_flag6(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag6());
}

int Thing::unused_flag7(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag7());
}

int Thing::unused_flag8(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag8());
}

int Thing::unused_flag9(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag9());
}

int Thing::unused_flag10(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag10());
}

int Thing::unused_flag11(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag11());
}

int Thing::unused_flag12(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag12());
}

int Thing::unused_flag13(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag13());
}

int Thing::unused_flag14(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag14());
}

int Thing::unused_flag15(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag15());
}

int Thing::unused_flag16(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag16());
}

int Thing::unused_flag17(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag17());
}

int Thing::unused_flag18(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag18());
}

int Thing::unused_flag19(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag19());
}

int Thing::unused_flag20(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag20());
}

int Thing::unused_flag21(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag21());
}

int Thing::unused_flag22(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag22());
}

int Thing::unused_flag23(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag23());
}

int Thing::unused_flag24(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag24());
}

int Thing::unused_flag25(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag25());
}

int Thing::unused_flag26(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag26());
}

int Thing::unused_flag27(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag27());
}

int Thing::unused_flag28(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag28());
}

int Thing::unused_flag29(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag29());
}

int Thing::unused_flag30(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag30());
}

int Thing::unused_flag31(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag31());
}

int Thing::unused_flag32(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag32());
}

int Thing::unused_flag33(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag33());
}

int Thing::unused_flag34(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag34());
}

int Thing::unused_flag35(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag35());
}

int Thing::unused_flag36(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag36());
}

int Thing::unused_flag37(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag37());
}

int Thing::unused_flag38(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag38());
}

int Thing::unused_flag39(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag39());
}

int Thing::unused_flag40(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag40());
}

int Thing::unused_flag41(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag41());
}

int Thing::unused_flag42(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag42());
}

int Thing::unused_flag43(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag43());
}

int Thing::unused_flag44(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag44());
}

int Thing::unused_flag45(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag45());
}

int Thing::unused_flag46(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag46());
}

int Thing::unused_flag47(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag47());
}

int Thing::unused_flag48(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag48());
}

int Thing::unused_flag49(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag49());
}

int Thing::unused_flag50(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag50());
}

int Thing::unused_flag51(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag51());
}

int Thing::unused_flag52(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag52());
}

int Thing::unused_flag53(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag53());
}

int Thing::unused_flag54(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag54());
}

int Thing::unused_flag55(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag55());
}

int Thing::unused_flag56(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag56());
}

int Thing::unused_flag57(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag57());
}

int Thing::unused_flag58(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag58());
}

int Thing::unused_flag59(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag59());
}

int Thing::unused_flag60(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag60());
}

int Thing::unused_flag61(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag61());
}

int Thing::unused_flag62(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag62());
}

int Thing::unused_flag63(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag63());
}

int Thing::unused_flag64(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag64());
}

int Thing::unused_flag65(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag65());
}

int Thing::unused_flag66(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag66());
}

int Thing::unused_flag67(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag67());
}

int Thing::unused_flag68(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag68());
}

int Thing::unused_flag69(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag69());
}

int Thing::unused_flag70(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag70());
}

int Thing::unused_flag71(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag71());
}

int Thing::unused_flag72(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag72());
}

int Thing::unused_flag73(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag73());
}

int Thing::unused_flag74(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag74());
}

int Thing::unused_flag75(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag75());
}

int Thing::unused_flag76(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag76());
}

int Thing::unused_flag77(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag77());
}

int Thing::unused_flag78(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag78());
}

int Thing::unused_flag79(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag79());
}

int Thing::unused_flag80(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag80());
}

int Thing::unused_flag81(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag81());
}

int Thing::unused_flag82(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag82());
}

int Thing::unused_flag83(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag83());
}

int Thing::unused_flag84(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag84());
}

int Thing::unused_flag85(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag85());
}

int Thing::unused_flag86(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag86());
}

int Thing::unused_flag87(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag87());
}

int Thing::unused_flag88(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag88());
}

int Thing::unused_flag89(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag89());
}

int Thing::unused_flag90(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag90());
}

int Thing::unused_flag91(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag91());
}

int Thing::unused_flag92(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag92());
}

int Thing::unused_flag93(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag93());
}

int Thing::unused_flag94(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag94());
}

int Thing::unused_flag95(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag95());
}

int Thing::unused_flag96(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag96());
}

int Thing::unused_flag97(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag97());
}

int Thing::unused_flag98(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag98());
}

int Thing::unused_flag99(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag99());
}

int Thing::unused_flag100(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag100());
}

int Thing::unused_flag101(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag101());
}

int Thing::unused_flag102(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag102());
}

int Thing::unused_flag103(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag103());
}

int Thing::unused_flag104(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag104());
}

int Thing::unused_flag105(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag105());
}

int Thing::unused_flag106(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag106());
}

int Thing::unused_flag107(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag107());
}

int Thing::unused_flag108(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag108());
}

int Thing::unused_flag109(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag109());
}

int Thing::unused_flag110(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag110());
}

int Thing::unused_flag111(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag111());
}

int Thing::unused_flag112(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag112());
}

int Thing::unused_flag113(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag113());
}

int Thing::unused_flag114(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag114());
}

int Thing::unused_flag115(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag115());
}

int Thing::unused_flag116(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag116());
}

int Thing::unused_flag117(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag117());
}

int Thing::unused_flag118(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag118());
}

int Thing::unused_flag119(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag119());
}

int Thing::unused_flag120(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag120());
}

int Thing::unused_flag121(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag121());
}

int Thing::unused_flag122(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag122());
}

int Thing::unused_flag123(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag123());
}

int Thing::unused_flag124(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag124());
}

int Thing::unused_flag125(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag125());
}

int Thing::unused_flag126(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag126());
}

int Thing::unused_flag127(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag127());
}

int Thing::unused_flag128(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag128());
}

int Thing::unused_flag129(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag129());
}

int Thing::unused_flag130(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag130());
}

int Thing::unused_flag131(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag131());
}

int Thing::unused_flag132(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag132());
}

int Thing::unused_flag133(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag133());
}

int Thing::unused_flag134(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag134());
}

int Thing::unused_flag135(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag135());
}

int Thing::unused_flag136(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag136());
}

int Thing::move_speed(void)
{
  TRACE_NO_INDENT();
  return (tp()->move_speed());
}

int Thing::damage_received_doubled_from_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_received_doubled_from_cold());
}

int Thing::is_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cold());
}

int Thing::temperature_change_sensitive(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_change_sensitive());
}

int Thing::temperature(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature());
}

int Thing::is_very_heavy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_heavy());
}

int Thing::gfx_health_bar_shown_when_awake_only(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_health_bar_shown_when_awake_only());
}

int Thing::gfx_show_asleep(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_show_asleep());
}

int Thing::noise_on_jumping(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_jumping());
}

int Thing::noise_on_born(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_born());
}

int Thing::noise_on_open(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_open());
}

int Thing::noise_on_you_are_hit_and_now_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_you_are_hit_and_now_dead());
}

int Thing::noise_on_you_are_hit_but_still_alive(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_you_are_hit_but_still_alive());
}

int Thing::noise_decibels_hearing(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_decibels_hearing());
}

int Thing::is_immune_to_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_cold());
}

int Thing::is_breather(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_breather());
}

int Thing::noise_on_moving_or_being_carried(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_moving_or_being_carried());
}

int Thing::is_asleep_initially(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_asleep_initially());
}

int Thing::is_able_to_sleep(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_sleep());
}

int Thing::is_obstacle_when_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obstacle_when_dead());
}

int Thing::is_pink_blood_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pink_blood_eater());
}

int Thing::is_green_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blood());
}

int Thing::is_pink_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pink_blood());
}

int Thing::is_biome_swamp(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_swamp());
}

int Thing::is_biome_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_dungeon());
}

int Thing::is_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure());
}

int Thing::is_monst_class_e(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_e());
}

int Thing::is_green_blood_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blood_eater());
}

int Thing::is_mob_challenge_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob_challenge_class_b());
}

int Thing::is_mob_challenge_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob_challenge_class_a());
}

int Thing::is_monst_class_d(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_d());
}

int Thing::is_monst_class_c(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_c());
}

int Thing::is_monst_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_b());
}

int Thing::is_monst_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_a());
}

int Thing::stat_att_penalty_when_in_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_in_deep_water());
}

int Thing::stat_att_penalty_when_in_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_in_shallow_water());
}

int Thing::stat_att_penalty_when_idle_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_idle_max());
}

int Thing::stat_att_penalty_when_idle(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_idle());
}

int Thing::stat_att_penalty_when_stuck(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_stuck());
}

int Thing::stat_att_penalty_when_stuck_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_stuck_max());
}

int Thing::stat_def_penalty_when_stuck_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_stuck_max());
}

int Thing::stat_def_penalty_when_idle_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_idle_max());
}

int Thing::stat_def_penalty_when_in_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_in_deep_water());
}

int Thing::stat_def_penalty_when_in_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_in_shallow_water());
}

int Thing::stat_def_penalty_when_stuck(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_stuck());
}

int Thing::stat_def_penalty_when_idle(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_idle());
}

int Thing::is_able_to_move_diagonally(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_move_diagonally());
}

int Thing::is_meltable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_meltable());
}

int Thing::is_amulet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_amulet());
}

int Thing::is_able_to_use_amulet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_amulet());
}

int Thing::is_able_to_use_helmet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_helmet());
}

int Thing::is_able_to_use_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_boots());
}

int Thing::is_able_to_use_cloak(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_cloak());
}

int Thing::is_able_to_use_shield(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_shield());
}

int Thing::is_able_to_use_gauntlet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_gauntlet());
}

int Thing::is_helmet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_helmet());
}

int Thing::is_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_boots());
}

int Thing::is_shield(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shield());
}

int Thing::is_cloak(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cloak());
}

int Thing::is_gauntlet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gauntlet());
}

int Thing::is_toughness_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_toughness_hard());
}

int Thing::is_red_blooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_blooded());
}

int Thing::is_green_blooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blooded());
}

int Thing::is_able_to_jump_without_tiring(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_without_tiring());
}

int Thing::is_spider(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spider());
}

int Thing::is_able_to_jump_attack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_attack());
}

int Thing::is_able_to_jump_onto(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_onto());
}

int Thing::is_crushable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crushable());
}

int Thing::collateral_damage_pct(void)
{
  TRACE_NO_INDENT();
  return tp()->collateral_damage_pct();
}

int Thing::aggression_level_pct(void)
{
  TRACE_NO_INDENT();

  int aggression = tp()->aggression_level_pct();

  if (is_able_to_follow()) {
    //
    // Followers are more cockey if they have a leader
    //
    auto l = leader();
    if (l) {
      //
      // If the leader is dead, be timid
      //
      if (l->is_dead) {
        return (aggression / 4);
      }

      //
      // If the leader is weak, be timid
      //
      if (l->health() < l->health_initial() / 3) {
        return (aggression / 2);
      }

      //
      // A strong leader
      //
      aggression += 20;
    } else {
      aggression += 10 * follower_count();
    }
  }

  if (aggression > 100) {
    aggression = 100;
  }

  return aggression;
}

int Thing::is_able_to_see_in_the_dark(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_in_the_dark());
}

int Thing::is_gfx_anim_synced_with_owner(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gfx_anim_synced_with_owner());
}

int Thing::is_item_magical(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_magical());
}

int Thing::is_able_to_use_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_armor());
}

int Thing::is_ring(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ring());
}

int Thing::is_auto_equipped(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_equipped());
}

int Thing::is_buff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_buff());
}

int Thing::is_debuff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debuff());
}

int Thing::attack_undead(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_undead());
}

int Thing::is_red_blood_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_blood_eater());
}

int Thing::is_slippery(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_slippery());
}

int Thing::ai_detect_secret_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_detect_secret_doors());
}

int Thing::is_able_to_break_down_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_down_doors());
}

int Thing::is_able_to_break_out_of_webs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_webs());
}

int Thing::is_able_to_open_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_open_doors());
}

int Thing::is_exit_finder(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_exit_finder());
}

int Thing::is_explorer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_explorer());
}

int Thing::is_rusty(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rusty());
}

int Thing::is_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_armor());
}

int Thing::is_able_to_learn_skills(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_learn_skills());
}

int Thing::is_able_to_enchant_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_enchant_items());
}

int Thing::is_able_to_attack_mobs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_attack_mobs());
}

int Thing::ai_wanderer(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_wanderer());
}

int Thing::is_organic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_organic());
}

int Thing::is_glass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_glass());
}

int Thing::is_stone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_stone());
}

int Thing::is_item_organic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_organic());
}

int Thing::is_metal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_metal());
}

int Thing::is_wooden(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wooden());
}

int Thing::is_flying(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_flying());
}

int Thing::is_engulfer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_engulfer());
}

int Thing::is_health_booster(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_health_booster());
}

int Thing::is_map_beast(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_map_beast());
}

int Thing::is_map_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_map_treasure());
}

int Thing::is_able_to_use_wands(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_wands());
}

int Thing::is_aquatic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_aquatic());
}

int Thing::is_secret_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_secret_door());
}

int Thing::is_sewer_wall(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sewer_wall());
}

int Thing::is_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shallow_water());
}

int Thing::is_shovable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shovable());
}

int Thing::is_skillstone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_skillstone());
}

int Thing::is_skill(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_skill());
}

int Thing::is_smoke(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_smoke());
}

int Thing::is_toughness_soft(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_toughness_soft());
}

int Thing::is_spawner(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spawner());
}

int Thing::is_spiderweb(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spiderweb());
}

int Thing::is_able_to_tire(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_tire());
}

int Thing::is_steal_item_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_steal_item_chance_d1000());
}

int Thing::attack_engulf_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_engulf_chance_d1000());
}

int Thing::damage_poison_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_poison_chance_d1000());
}

int Thing::damage_future1_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future1_chance_d1000());
}

int Thing::damage_future2_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future2_chance_d1000());
}

int Thing::damage_future3_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future3_chance_d1000());
}

int Thing::damage_cold_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_cold_chance_d1000());
}

int Thing::damage_fire_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_fire_chance_d1000());
}

int Thing::damage_crush_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_crush_chance_d1000());
}

int Thing::damage_lightning_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_lightning_chance_d1000());
}

int Thing::damage_energy_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_energy_chance_d1000());
}

int Thing::damage_acid_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_acid_chance_d1000());
}

int Thing::damage_digest_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_digest_chance_d1000());
}

int Thing::damage_necrosis_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_necrosis_chance_d1000());
}

int Thing::is_sticky(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sticky());
}

int Thing::is_sword(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sword());
}

int Thing::is_victim_select(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_victim_select());
}

int Thing::is_throwable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_throwable());
}

int Thing::is_auto_throw(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_throw());
}

int Thing::is_tickable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tickable());
}

int Thing::is_tmp_thing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tmp_thing());
}

int Thing::is_torch(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_torch());
}

int Thing::is_treasure_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_a());
}

int Thing::is_treasure_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_b());
}

int Thing::is_treasure_class_c(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_c());
}

int Thing::is_weapon_class_a(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_a());
}

int Thing::is_weapon_class_b(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_b());
}

int Thing::is_weapon_class_c(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_c());
}

int Thing::is_treasure_chest(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_chest());
}

int Thing::is_item_collector(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_collector());
}

int Thing::is_treasure_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_eater());
}

int Thing::is_treasure_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_type());
}

int Thing::is_undead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_undead());
}

int Thing::is_usable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_usable());
}

int Thing::is_auto_use(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_use());
}

int Thing::is_used_when_thrown(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_used_when_thrown());
}

int Thing::is_very_combustible(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_combustible());
}

int Thing::is_wall_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wall_dungeon());
}

int Thing::is_wall(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wall());
}

int Thing::is_item_magical_eater(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_magical_eater());
}

int Thing::is_wand(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wand());
}

int Thing::is_immune_to_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_water());
}

int Thing::is_weapon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon());
}

int Thing::is_able_to_use_rings(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_rings());
}

int Thing::is_immune_to_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_fire());
}

int Thing::is_immune_to_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_poison());
}

int Thing::is_immune_to_necrosis(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_necrosis());
}

int Thing::is_immune_to_spiderwebs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spiderwebs());
}

float Thing::distance_mob_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_mob_max());
}

float Thing::distance_leader_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_leader_max());
}

int Thing::minion_limit(void)
{
  TRACE_NO_INDENT();
  return (tp()->minion_limit());
}

int Thing::normal_placement_rules(void)
{
  TRACE_NO_INDENT();
  return (tp()->normal_placement_rules());
}

int Thing::on_death_drop_all_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_drop_all_items());
}

int Thing::on_death_is_open(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_is_open());
}

int Thing::range_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->range_max());
}

int Thing::weapon_damage(void)
{
  TRACE_NO_INDENT();
  return (tp()->weapon_damage());
}

int Thing::is_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shallow_water() || tp()->is_deep_water());
}

void Thing::new_infop(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    _infop = new ThingInfo();
    // uncomment to see who allocates things
    // err("New monst info");
    newptr(MTYPE_INFOP, _infop, "ThingInfo");

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

void Thing::new_itemsp(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _itemsp)) {
    _itemsp = new ThingItem();
    // uncomment to see who allocates things
    // err("New monst item");
    newptr(MTYPE_ITEMP, _itemsp, "ThingItem");

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
  TRACE_NO_INDENT();
  if (unlikely(! _aip)) {
    _aip = new ThingAi();
    // uncomment to see who allocates things
    // err("New monst ai");
    newptr(MTYPE_AIP, _aip, "ThingAi");
  }
}

ThingInfop Thing::get_or_alloc_infop(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    new_infop();
  }
  IF_DEBUG3 { verify(MTYPE_INFOP, _infop); }
  return _infop;
}

ThingItemsp Thing::get_or_alloc_itemsp(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _itemsp)) {
    new_itemsp();
  }
  IF_DEBUG3 { verify(MTYPE_ITEMP, _itemsp); }
  return _itemsp;
}

ThingAip Thing::get_or_alloc_aip(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _aip)) {
    new_aip();
  }
  IF_DEBUG3 { verify(MTYPE_AIP, _aip); }
  return _aip;
}

ThingInfop Thing::infop(void)
{
  TRACE_NO_INDENT();
  if (! _infop) {
    die("no _infop");
  }
  IF_DEBUG3 { verify(MTYPE_INFOP, _infop); }
  return _infop;
}

ThingItemsp Thing::itemsp(void)
{
  TRACE_NO_INDENT();
  if (! _itemsp) {
    die("no _itemsp");
  }
  IF_DEBUG3 { verify(MTYPE_ITEMP, _itemsp); }
  return _itemsp;
}

ThingAip Thing::aip(void)
{
  TRACE_NO_INDENT();
  if (! _aip) {
    die("no _aip");
  }
  IF_DEBUG3 { verify(MTYPE_AIP, _aip); }
  return _aip;
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::age_map_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->age_map);
}

void Thing::clear_age_map(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->age_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// seen_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::seen_map_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->seen_map);
}

void Thing::clear_seen_map(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->seen_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// interrupt_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::interrupt_map_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->interrupt_map);
}

void Thing::clear_interrupt_map(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->interrupt_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// _dmap_can_see
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::dmap_can_see_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->dmap_can_see);
}

void Thing::clear_dmap_can_see(void)
{
  TRACE_NO_INDENT();
  new_aip();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      set(aip()->dmap_can_see.val, x, y, DMAP_IS_WALL);
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// can_see_currently
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::can_see_currently(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->can_see_currently);
}

void Thing::clear_can_see_currently(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->can_see_currently.can_see = {};
}

////////////////////////////////////////////////////////////////////////////
// can_see_ever
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::can_see_ever(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->can_see_ever);
}

void Thing::clear_can_see_ever(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->can_see_ever.can_see = {};
}

int Thing::item_height(void)
{
  TRACE_NO_INDENT();
  return (tp()->item_height());
}

int Thing::item_width(void)
{
  TRACE_NO_INDENT();
  return (tp()->item_width());
}

int Thing::capacity_height(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (infop()->capacity_height) {
    return infop()->capacity_height;
  }
  return (tp()->capacity_height());
}

int Thing::capacity_width(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (infop()->capacity_width) {
    return infop()->capacity_width;
  }
  return (tp()->capacity_width());
}

int Thing::monst_size(void)
{
  TRACE_NO_INDENT();
  return (tp()->monst_size());
}

int Thing::rarity(void)
{
  TRACE_NO_INDENT();
  return (tp()->rarity());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
point Thing::lunge_to_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->lunge_to);
  } else {
    return (point(0, 0));
  }
}

void Thing::lunge_to_set(point v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->lunge_to = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::bounce_height_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_height);
  } else {
    return 0;
  }
}

void Thing::bounce_height_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fall_height
////////////////////////////////////////////////////////////////////////////
float Thing::fall_height_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->fall_height);
  } else {
    return 0;
  }
}

void Thing::fall_height_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->fall_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::bounce_fade_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_fade);
  } else {
    return 0;
  }
}

void Thing::bounce_fade_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// born
////////////////////////////////////////////////////////////////////////////
point3d Thing::born_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->born);
  } else {
    die("No born location");
    return (point3d(-1, -1, -1));
  }
}

void Thing::born_set(point3d v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->born = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::bounce_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->bounce_count);
  } else {
    return 0;
  }
}

void Thing::bounce_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->bounce_count = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_height
////////////////////////////////////////////////////////////////////////////
float Thing::fadeup_height_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->fadeup_height);
  } else {
    return 0;
  }
}

void Thing::fadeup_height_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->fadeup_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_fade
////////////////////////////////////////////////////////////////////////////
float Thing::fadeup_fade_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->fadeup_fade);
  } else {
    return 0;
  }
}

void Thing::fadeup_fade_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->fadeup_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// wobble
////////////////////////////////////////////////////////////////////////////
float Thing::wobble_curr(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->wobble);
  } else {
    return 0;
  }
}

void Thing::wobble_set(float v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->wobble = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::msg_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->msg);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::msg_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// dead_reason
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::dead_reason_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->dead_reason);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::dead_reason_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->dead_reason = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::submerged_offset_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    //
    // Floating when dead?
    //
    if (is_dead) {
      return (infop()->submerged_offset / 2);
    }

    return (infop()->submerged_offset);
  } else {
    return 0;
  }
}

void Thing::submerged_offset_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// gold
////////////////////////////////////////////////////////////////////////////
int Thing::gold(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->gold);
  } else {
    return 0;
  }
}

int Thing::gold_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->gold = v);
  return (n);
}

int Thing::gold_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->gold -= v);
  if (infop()->gold < 0) {
    infop()->gold = 0;
  }
  return (n);
}

int Thing::gold_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->gold += v);
  return (n);
}

int Thing::gold_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->gold--);
  if (infop()->gold < 0) {
    infop()->gold = 0;
  }
  return (n);
}

int Thing::gold_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->gold++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// score
////////////////////////////////////////////////////////////////////////////
int Thing::score(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->score);
  } else {
    return 0;
  }
}

void Thing::score_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  infop()->score = v;
}

void Thing::score_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  infop()->score += v;
}

////////////////////////////////////////////////////////////////////////////
// keys
////////////////////////////////////////////////////////////////////////////
int Thing::keys(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->keys);
  } else {
    return 0;
  }
}

int Thing::keys_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->keys = v);
  return (n);
}

int Thing::keys_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->keys -= v);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return (n);
}

int Thing::keys_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->keys += v);
  return (n);
}

int Thing::keys_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->keys--);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return (n);
}

int Thing::keys_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->keys++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::health(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->health;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->health();
  }
  return v;
}

int Thing::health_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health = v);
  return (n);
}

int Thing::health_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health -= v);
  return (n);
}

int Thing::health_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health += v);
  return (n);
}

int Thing::health_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health--);
  return (n);
}

int Thing::health_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::health_max(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->health_max);
  } else {
    return 0;
  }
}

int Thing::health_max_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health_max = v);
  return (n);
}

int Thing::health_max_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health_max -= v);
  return (n);
}

int Thing::health_max_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health_max += v);
  return (n);
}

int Thing::health_max_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health_max--);
  return (n);
}

int Thing::health_max_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->health_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina_max
////////////////////////////////////////////////////////////////////////////
int Thing::stamina_max(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stamina_max);
  } else {
    return 0;
  }
}

int Thing::stamina_max_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max = v);
  return (n);
}

int Thing::stamina_max_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max -= v);
  return (n);
}

int Thing::stamina_max_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max += v);
  return (n);
}

int Thing::stamina_max_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max--);
  return (n);
}

int Thing::stamina_max_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant_max
////////////////////////////////////////////////////////////////////////////
int Thing::enchant_max_current_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->enchant_max);
  } else {
    return 0;
  }
}

int Thing::enchant_max_current_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->enchant_max = v);
  return (n);
}

int Thing::enchant_max_current_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->enchant_max -= v);
  return (n);
}

int Thing::enchant_max_current_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->enchant_max += v);
  return (n);
}

int Thing::enchant_max_current_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->enchant_max--);
  return (n);
}

int Thing::enchant_max_current_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->enchant_max++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// tick_resurrect_when
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_resurrect_when(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_resurrect_when);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_resurrect_when_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when = v);
  return (n);
}

uint32_t Thing::tick_resurrect_when_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when -= v);
  return (n);
}

uint32_t Thing::tick_resurrect_when_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when += v);
  return (n);
}

uint32_t Thing::tick_resurrect_when_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when--);
  return (n);
}

uint32_t Thing::tick_resurrect_when_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->tick_resurrect_when++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// movement_left
////////////////////////////////////////////////////////////////////////////
int Thing::movement_left(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->movement_left);
  } else {
    return 0;
  }
}

int Thing::movement_left_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_left = v);
  return (n);
}

int Thing::movement_left_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_left -= v);
  return (n);
}

int Thing::movement_left_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_left += v);
  return (n);
}

int Thing::movement_left_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_left--);
  return (n);
}

int Thing::movement_left_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_left++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::stats02(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats02);
  } else {
    return 0;
  }
}

int Thing::stats02_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats02 = v);
  return (n);
}

int Thing::stats02_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats02 -= v);
  return (n);
}

int Thing::stats02_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats02 += v);
  return (n);
}

int Thing::stats02_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats02--);
  return (n);
}

int Thing::stats02_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats02++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::stats03(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats03);
  } else {
    return 0;
  }
}

int Thing::stats03_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats03 = v);
  return (n);
}

int Thing::stats03_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats03 -= v);
  return (n);
}

int Thing::stats03_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats03 += v);
  return (n);
}

int Thing::stats03_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats03--);
  return (n);
}

int Thing::stats03_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats03++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::stats04(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats04);
  } else {
    return 0;
  }
}

int Thing::stats04_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats04 = v);
  return (n);
}

int Thing::stats04_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats04 -= v);
  return (n);
}

int Thing::stats04_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats04 += v);
  return (n);
}

int Thing::stats04_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats04--);
  return (n);
}

int Thing::stats04_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats04++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::stats05(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats05);
  } else {
    return 0;
  }
}

int Thing::stats05_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats05 = v);
  return (n);
}

int Thing::stats05_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats05 -= v);
  return (n);
}

int Thing::stats05_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats05 += v);
  return (n);
}

int Thing::stats05_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats05--);
  return (n);
}

int Thing::stats05_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats05++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::stats06(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats06);
  } else {
    return 0;
  }
}

int Thing::stats06_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats06 = v);
  return (n);
}

int Thing::stats06_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats06 -= v);
  return (n);
}

int Thing::stats06_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats06 += v);
  return (n);
}

int Thing::stats06_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats06--);
  return (n);
}

int Thing::stats06_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats06++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::stats07(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats07);
  } else {
    return 0;
  }
}

int Thing::stats07_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats07 = v);
  return (n);
}

int Thing::stats07_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats07 -= v);
  return (n);
}

int Thing::stats07_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats07 += v);
  return (n);
}

int Thing::stats07_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats07--);
  return (n);
}

int Thing::stats07_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats07++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::stats09(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats09);
  } else {
    return 0;
  }
}

int Thing::stats09_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats09 = v);
  return (n);
}

int Thing::stats09_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats09 -= v);
  return (n);
}

int Thing::stats09_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats09 += v);
  return (n);
}

int Thing::stats09_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats09--);
  return (n);
}

int Thing::stats09_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stats09++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_def_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_def_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_def_mod);
  } else {
    return 0;
  }
}

int Thing::stat_def_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_def_mod = v);
  return (n);
}

int Thing::stat_def_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_def_mod -= v);
  return (n);
}

int Thing::stat_def_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_def_mod += v);
  return (n);
}

int Thing::stat_def_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_def_mod--);
  return (n);
}

int Thing::stat_def_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_def_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_con_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_con_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_con_mod);
  } else {
    return 0;
  }
}

int Thing::stat_con_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con_mod = v);
  return (n);
}

int Thing::stat_con_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con_mod -= v);
  return (n);
}

int Thing::stat_con_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con_mod += v);
  return (n);
}

int Thing::stat_con_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con_mod--);
  return (n);
}

int Thing::stat_con_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_con_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_dex_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_dex_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_dex_mod);
  } else {
    return 0;
  }
}

int Thing::stat_dex_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_dex_mod = v);
  return (n);
}

int Thing::stat_dex_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_dex_mod -= v);
  return (n);
}

int Thing::stat_dex_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_dex_mod += v);
  return (n);
}

int Thing::stat_dex_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_dex_mod--);
  return (n);
}

int Thing::stat_dex_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_dex_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_luck_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_luck_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_luck_mod);
  } else {
    return 0;
  }
}

int Thing::stat_luck_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_luck_mod = v);
  return (n);
}

int Thing::stat_luck_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_luck_mod -= v);
  return (n);
}

int Thing::stat_luck_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_luck_mod += v);
  return (n);
}

int Thing::stat_luck_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_luck_mod--);
  return (n);
}

int Thing::stat_luck_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_luck_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_att_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_att_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_att_mod);
  } else {
    return 0;
  }
}

int Thing::stat_att_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_att_mod = v);
  return (n);
}

int Thing::stat_att_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_att_mod -= v);
  return (n);
}

int Thing::stat_att_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_att_mod += v);
  return (n);
}

int Thing::stat_att_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_att_mod--);
  return (n);
}

int Thing::stat_att_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_att_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stat_str_mod
////////////////////////////////////////////////////////////////////////////
int Thing::stat_str_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_str_mod);
  } else {
    return 0;
  }
}

int Thing::stat_str_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_str_mod = v);
  return (n);
}

int Thing::stat_str_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_str_mod -= v);
  return (n);
}

int Thing::stat_str_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_str_mod += v);
  return (n);
}

int Thing::stat_str_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_str_mod--);
  return (n);
}

int Thing::stat_str_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stat_str_mod++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// distance_throw
////////////////////////////////////////////////////////////////////////////
float Thing::distance_throw_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->distance_throw);
  } else {
    return 0;
  }
}

int Thing::distance_throw_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw = v);
  return (n);
}

int Thing::distance_throw_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw -= v);
  return (n);
}

int Thing::distance_throw_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw += v);
  return (n);
}

int Thing::distance_throw_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw--);
  return (n);
}

int Thing::distance_throw_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// stamina
////////////////////////////////////////////////////////////////////////////
int Thing::stamina_get(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->stamina;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->stamina_get();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->stamina_get();
    }
  }
  return v;
}

int Thing::stamina_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->stamina = v);
  return (n);
}

int Thing::stamina_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->stamina -= v);
  if (infop()->stamina < 0) {
    infop()->stamina = 0;
  }
  return (n);
}

int Thing::stamina_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->stamina += v);
  return (n);
}

int Thing::stamina_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->stamina--);
  if (infop()->stamina < 0) {
    infop()->stamina = 0;
  }
  return (n);
}

int Thing::stamina_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->stamina++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// enchant
////////////////////////////////////////////////////////////////////////////
int Thing::enchant_get(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->enchant;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->enchant_get();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->enchant_get();
    }
  }
  return v;
}

int Thing::enchant_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant = v);
  return (n);
}

int Thing::enchant_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant -= v);
  if (infop()->enchant < 0) {
    infop()->enchant = 0;
  }
  return (n);
}

int Thing::enchant_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant += v);
  return (n);
}

int Thing::enchant_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant--);
  if (infop()->enchant < 0) {
    infop()->enchant = 0;
  }
  return (n);
}

int Thing::enchant_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// poison
////////////////////////////////////////////////////////////////////////////
int Thing::poisoned_amount(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->poison;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->poisoned_amount();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->poisoned_amount();
    }
  }
  return v;
}

int Thing::poisoned_amount_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison = v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return (n);
}

int Thing::poisoned_amount_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison -= v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return (n);
}

int Thing::poisoned_amount_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison += v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return (n);
}

int Thing::poisoned_amount_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison--);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return (n);
}

int Thing::poisoned_amount_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// necrosis
////////////////////////////////////////////////////////////////////////////
int Thing::necrotized_amount(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->necrosis;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->necrotized_amount();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->necrotized_amount();
    }
  }
  return v;
}

int Thing::necrotized_amount_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis = v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return (n);
}

int Thing::necrotized_amount_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis -= v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return (n);
}

int Thing::necrotized_amount_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis += v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return (n);
}

int Thing::necrotized_amount_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis--);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return (n);
}

int Thing::necrotized_amount_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis++);
  return (n);
}

////////////////////////////////////////////////////////////////////////////
// owned_count
////////////////////////////////////////////////////////////////////////////
int Thing::owned_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->owned_count);
  } else {
    return 0;
  }
}

int Thing::owned_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owned_count = v);
}

int Thing::owned_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owned_count -= v);
}

int Thing::owned_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owned_count += v);
}

int Thing::owned_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owned_count--);
}

int Thing::owned_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// minion_count
////////////////////////////////////////////////////////////////////////////
int Thing::minion_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->minion_count);
  } else {
    return 0;
  }
}

int Thing::minion_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count = v);
}

int Thing::minion_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count -= v);
}

int Thing::minion_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count += v);
}

int Thing::minion_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count--);
}

int Thing::minion_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->minion_count++);
}

////////////////////////////////////////////////////////////////////////////
// follower_count
////////////////////////////////////////////////////////////////////////////
int Thing::follower_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->follower_count);
  } else {
    return 0;
  }
}

int Thing::follower_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->follower_count = v);
}

int Thing::follower_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->follower_count -= v);
}

int Thing::follower_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->follower_count += v);
}

int Thing::follower_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->follower_count--);
}

int Thing::follower_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->follower_count++);
}

////////////////////////////////////////////////////////////////////////////
// spawned_count
////////////////////////////////////////////////////////////////////////////
int Thing::spawned_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->spawned_count);
  } else {
    return 0;
  }
}

int Thing::spawned_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count = v);
}

int Thing::spawned_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count -= v);
}

int Thing::spawned_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count += v);
}

int Thing::spawned_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count--);
}

int Thing::spawned_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->spawned_count++);
}

////////////////////////////////////////////////////////////////////////////
// charge_count
////////////////////////////////////////////////////////////////////////////
int Thing::charge_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->charge_count);
  } else {
    return 0;
  }
}

int Thing::charge_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->charge_count = v);
}

int Thing::charge_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->charge_count -= v);
}

int Thing::charge_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->charge_count += v);
}

int Thing::charge_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->charge_count--);
}

int Thing::charge_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->charge_count++);
}

////////////////////////////////////////////////////////////////////////////
// sleep_count
////////////////////////////////////////////////////////////////////////////
int Thing::sleep_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->sleep_count);
  } else {
    return 0;
  }
}

int Thing::sleep_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count = v);
}

int Thing::sleep_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count -= v);
}

int Thing::sleep_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count += v);
}

int Thing::sleep_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count--);
}

int Thing::sleep_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->sleep_count++);
}

////////////////////////////////////////////////////////////////////////////
// idle_count
////////////////////////////////////////////////////////////////////////////
int Thing::idle_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->idle_count);
  } else {
    return 0;
  }
}

int Thing::idle_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count = v);
}

int Thing::idle_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count -= v);
}

int Thing::idle_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count += v);
}

int Thing::idle_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count--);
}

int Thing::idle_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->idle_count++);
}

////////////////////////////////////////////////////////////////////////////
// stuck_count
////////////////////////////////////////////////////////////////////////////
int Thing::stuck_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->stuck_count);
  } else {
    return 0;
  }
}

int Thing::stuck_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count = v);
}

int Thing::stuck_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count -= v);
}

int Thing::stuck_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count += v);
}

int Thing::stuck_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count--);
}

int Thing::stuck_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count++);
}

////////////////////////////////////////////////////////////////////////////
// lifespan
////////////////////////////////////////////////////////////////////////////
int Thing::lifespan_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->lifespan);
  } else {
    return 0;
  }
}

int Thing::lifespan_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan = v);
}

int Thing::lifespan_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan -= v);
}

int Thing::lifespan_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan += v);
}

int Thing::lifespan_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan--);
}

int Thing::lifespan_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan++);
}

////////////////////////////////////////////////////////////////////////////
// prev_light_power
////////////////////////////////////////////////////////////////////////////
int Thing::prev_light_power_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->prev_light_power);
  } else {
    return 0;
  }
}

int Thing::prev_light_power_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power = v);
}

int Thing::prev_light_power_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power -= v);
}

int Thing::prev_light_power_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power += v);
}

int Thing::prev_light_power_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power--);
}

int Thing::prev_light_power_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->prev_light_power++);
}

////////////////////////////////////////////////////////////////////////////
// light_power
////////////////////////////////////////////////////////////////////////////
int Thing::initial_light_power_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->light_power());
}

int Thing::light_power_get(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_power_get();
  }

  uint8_t light_power = infop()->light_power;

  if (is_player()) {
    light_power = 0;
  }

  light_power_including_torch_effect_get(light_power);
  infop()->light_power = light_power;

  return light_power;
}

int Thing::update_light_power(void)
{
  TRACE_NO_INDENT();

  if (! maybe_infop()) {
    return initial_light_power_get();
  }

  uint8_t light_power = infop()->light_power;

  if (! light_power) {
    light_power = initial_light_power_get();
  }

  if (is_player()) {
    light_power = 0;
  }

  update_light_power_including_torch_effect(light_power);
  infop()->light_power = light_power;

  return light_power;
}

int Thing::light_power_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power = v);
}

int Thing::light_power_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power -= v);
}

int Thing::light_power_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power += v);
}

int Thing::light_power_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power--);
}

int Thing::light_power_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->light_power++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_did_something(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) {
    return (infop()->tick_last_did_something);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_did_something_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something = v);
}

uint32_t Thing::tick_last_did_something_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something -= v);
}

uint32_t Thing::tick_last_did_something_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something += v);
}

uint32_t Thing::tick_last_did_something_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something--);
}

uint32_t Thing::tick_last_did_something_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_dropped
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_dropped(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) {
    return (infop()->tick_last_dropped);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_dropped_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped = v);
}

uint32_t Thing::tick_last_dropped_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped -= v);
}

uint32_t Thing::tick_last_dropped_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped += v);
}

uint32_t Thing::tick_last_dropped_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped--);
}

uint32_t Thing::tick_last_dropped_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_location_check
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_location_check(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_location_check);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_location_check_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check = v);
}

uint32_t Thing::tick_last_location_check_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check -= v);
}

uint32_t Thing::tick_last_location_check_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check += v);
}

uint32_t Thing::tick_last_location_check_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check--);
}

uint32_t Thing::tick_last_location_check_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_escape
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_escape(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_escape);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_escape_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape = v);
}

uint32_t Thing::tick_last_escape_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape -= v);
}

uint32_t Thing::tick_last_escape_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape += v);
}

uint32_t Thing::tick_last_escape_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape--);
}

uint32_t Thing::tick_last_escape_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_level_change
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_level_change(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_level_change);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_level_change_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change = v);
}

uint32_t Thing::tick_last_level_change_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change -= v);
}

uint32_t Thing::tick_last_level_change_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change += v);
}

uint32_t Thing::tick_last_level_change_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change--);
}

uint32_t Thing::tick_last_level_change_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_was_attacked
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_i_was_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_i_was_attacked);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_i_was_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked = v);
}

uint32_t Thing::tick_last_i_was_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked -= v);
}

uint32_t Thing::tick_last_i_was_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked += v);
}

uint32_t Thing::tick_last_i_was_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked--);
}

uint32_t Thing::tick_last_i_was_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// where_i_dropped_an_item_last
////////////////////////////////////////////////////////////////////////////
point Thing::where_i_dropped_an_item_last_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (itemsp()->where_i_dropped_an_item_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::where_i_dropped_an_item_last_set(point v)
{
  TRACE_NO_INDENT();
  new_itemsp();
  return (itemsp()->where_i_dropped_an_item_last = v);
}

////////////////////////////////////////////////////////////////////////////
// where_i_failed_to_collect_last
////////////////////////////////////////////////////////////////////////////
point Thing::where_i_failed_to_collect_last_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (itemsp()->where_i_failed_to_collect_last);
  } else {
    return (point(-1, -1));
  }
}

point Thing::where_i_failed_to_collect_last_set(point v)
{
  TRACE_NO_INDENT();
  new_itemsp();
  return (itemsp()->where_i_failed_to_collect_last = v);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_lunge_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_lunge_begin);
  } else {
    return 0;
  }
}

ts_t Thing::ts_lunge_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin = v);
}

ts_t Thing::ts_lunge_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin -= v);
}

ts_t Thing::ts_lunge_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin += v);
}

ts_t Thing::ts_lunge_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin--);
}

ts_t Thing::ts_lunge_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_lunge_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_lunge_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_lunge_end);
  } else {
    return 0;
  }
}

ts_t Thing::ts_lunge_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end = v);
}

ts_t Thing::ts_lunge_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end -= v);
}

ts_t Thing::ts_lunge_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end += v);
}

ts_t Thing::ts_lunge_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end--);
}

ts_t Thing::ts_lunge_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_lunge_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_bounce_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_bounce_begin);
  } else {
    return 0;
  }
}

ts_t Thing::ts_bounce_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin = v);
}

ts_t Thing::ts_bounce_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin -= v);
}

ts_t Thing::ts_bounce_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin += v);
}

ts_t Thing::ts_bounce_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin--);
}

ts_t Thing::ts_bounce_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_bounce_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_bounce_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_bounce_end);
  } else {
    return 0;
  }
}

ts_t Thing::ts_bounce_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end = v);
}

ts_t Thing::ts_bounce_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end -= v);
}

ts_t Thing::ts_bounce_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end += v);
}

ts_t Thing::ts_bounce_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end--);
}

ts_t Thing::ts_bounce_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fadeup_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fadeup_begin);
  } else {
    return 0;
  }
}

ts_t Thing::ts_fadeup_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_begin = v);
}

ts_t Thing::ts_fadeup_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_begin -= v);
}

ts_t Thing::ts_fadeup_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_begin += v);
}

ts_t Thing::ts_fadeup_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_begin--);
}

ts_t Thing::ts_fadeup_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fadeup_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fadeup_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fadeup_end);
  } else {
    return 0;
  }
}

ts_t Thing::ts_fadeup_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_end = v);
}

ts_t Thing::ts_fadeup_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_end -= v);
}

ts_t Thing::ts_fadeup_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_end += v);
}

ts_t Thing::ts_fadeup_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_end--);
}

ts_t Thing::ts_fadeup_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fadeup_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_flip_start
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_flip_start_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_flip_start);
  } else {
    return 0;
  }
}

ts_t Thing::ts_flip_start_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_flip_start = v);
}

ts_t Thing::ts_flip_start_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_flip_start -= v);
}

ts_t Thing::ts_flip_start_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_flip_start += v);
}

ts_t Thing::ts_flip_start_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_flip_start--);
}

ts_t Thing::ts_flip_start_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// ts_anim_delay_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_anim_delay_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_anim_delay_end);
  } else {
    return 0;
  }
}

ts_t Thing::ts_anim_delay_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_anim_delay_end = v);
}

ts_t Thing::ts_anim_delay_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_anim_delay_end -= v);
}

ts_t Thing::ts_anim_delay_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_anim_delay_end += v);
}

ts_t Thing::ts_anim_delay_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_anim_delay_end--);
}

ts_t Thing::ts_anim_delay_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_anim_delay_end++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_begin
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fall_begin(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fall_begin);
  } else {
    return 0;
  }
}

ts_t Thing::ts_fall_begin_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin = v);
}

ts_t Thing::ts_fall_begin_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin -= v);
}

ts_t Thing::ts_fall_begin_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin += v);
}

ts_t Thing::ts_fall_begin_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin--);
}

ts_t Thing::ts_fall_begin_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_begin++);
}

////////////////////////////////////////////////////////////////////////////
// ts_fall_end
////////////////////////////////////////////////////////////////////////////
ts_t Thing::ts_fall_end(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->ts_fall_end);
  } else {
    return 0;
  }
}

ts_t Thing::ts_fall_end_set(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end = v);
}

ts_t Thing::ts_fall_end_decr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end -= v);
}

ts_t Thing::ts_fall_end_incr(ts_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end += v);
}

ts_t Thing::ts_fall_end_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end--);
}

ts_t Thing::ts_fall_end_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->ts_fall_end++);
}

////////////////////////////////////////////////////////////////////////////
// equip_id_carry_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id_carry_anim(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    auto id = get(itemsp()->equip_id_carry_anim, equip);
    if (id != NoThingId) {
      verify(MTYPE_THING, level->thing_find(id));
    }
    return id;
  }
  return NoThingId;
}

ThingId Thing::equip_id_carry_anim_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_infop();
  return (itemsp()->equip_id_carry_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_id_use_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id_use_anim(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    auto id = get(itemsp()->equip_id_use_anim, equip);
    if (id != NoThingId) {
      verify(MTYPE_THING, level->thing_find(id));
    }
    return id;
  }
  return NoThingId;
}

ThingId Thing::equip_id_use_anim_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_infop();
  return (itemsp()->equip_id_use_anim[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// equip_tp_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::equip_id(int equip)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    // con("get weapon %" PRIX32 "",  itemsp()->equip_id);
    return (itemsp()->equip_id[ equip ]);
  } else {
    // con("get equip id => none");
    return NoThingId;
  }
}

ThingId Thing::equip_id_set(ThingId v, int equip)
{
  TRACE_NO_INDENT();
  new_infop();
  // con("set weapon %" PRIX32 "", v);
  return (itemsp()->equip_id[ equip ] = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::on_fire_anim_id(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->on_fire_id_anim);
  } else {
    return NoThingId;
  }
}

ThingId Thing::on_fire_anim_id_set(ThingId v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->on_fire_id_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// damage_current
////////////////////////////////////////////////////////////////////////////
int Thing::damage_current(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->damage_current;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->damage_current();
  }
  return v;
}

int Thing::damage_current_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->damage_current = v);
  return (n);
}

int Thing::damage_current_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->damage_current -= v);
  return (n);
}

int Thing::damage_current_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->damage_current += v);
  return (n);
}

int Thing::damage_current_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->damage_current--);
  return (n);
}

int Thing::damage_current_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->damage_current++);
  return (n);
}

const std::string &Thing::gfx_anim_use(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_anim_use());
}

const std::string &Thing::laser_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->laser_name());
}

const std::string &Thing::light_color(void)
{
  TRACE_NO_INDENT();
  return (tp()->light_color());
}

const std::string &Thing::long_text_description(void)
{
  TRACE_NO_INDENT();
  return (tp()->long_text_description());
}

const std::string &Thing::long_text_description_extra(void)
{
  TRACE_NO_INDENT();
  return (tp()->long_text_description_extra());
}

const std::string &Thing::text_unused1(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused1());
}

const std::string &Thing::text_unused2(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused2());
}

const std::string &Thing::name(void)
{
  TRACE_NO_INDENT();
  return (tp()->name());
}

const std::string &Thing::on_polymorphed_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_polymorphed_do());
}

const std::string &Thing::on_you_natural_attack_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_natural_attack_do());
}

const std::string &Thing::on_born_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_born_do());
}

const std::string &Thing::on_death_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_do());
}

const std::string &Thing::on_awake_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_awake_do());
}

const std::string &Thing::on_enchant_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_enchant_do());
}

const std::string &Thing::on_fall_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_fall_do());
}

const std::string &Thing::on_jump_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_jump_do());
}

const std::string &Thing::on_you_are_on_fire_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_on_fire_do());
}

const std::string &Thing::on_firing_at_something_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_firing_at_something_do());
}

const std::string &Thing::on_you_are_hit_but_still_alive_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_hit_but_still_alive_do());
}

const std::string &Thing::on_you_are_hit_and_now_dead_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_hit_and_now_dead_do());
}

const std::string &Thing::on_lifespan_tick_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_lifespan_tick_do());
}

const std::string &Thing::on_you_miss_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_miss_do());
}

const std::string &Thing::on_move_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_move_do());
}

const std::string &Thing::on_open_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_open_do());
}

const std::string &Thing::on_tick_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_tick_do());
}

const std::string &Thing::on_use_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_use_do());
}

const std::string &Thing::on_final_use_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_final_use_do());
}

const std::string &Thing::on_equip_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_equip_do());
}

const std::string &Thing::on_unequip_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_unequip_do());
}

const std::string &Thing::on_owner_add_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_add_do());
}

const std::string &Thing::on_owner_remove_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_remove_do());
}

const std::string &Thing::on_you_are_declared_a_follower_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_declared_a_follower_do());
}

const std::string &Thing::on_death_of_a_follower_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_of_a_follower_do());
}

const std::string &Thing::on_you_are_declared_leader_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_declared_leader_do());
}

const std::string &Thing::on_death_of_my_leader_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_of_my_leader_do());
}

const std::string &Thing::on_owner_damage_poison_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_poison_do());
}

const std::string &Thing::on_owner_damage_future1_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_future1_do());
}

const std::string &Thing::on_owner_damage_future2_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_future2_do());
}

const std::string &Thing::on_owner_damage_future3_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_future3_do());
}

const std::string &Thing::on_owner_damage_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_cold_do());
}

const std::string &Thing::on_owner_damage_fire_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_fire_do());
}

const std::string &Thing::on_owner_damage_crush_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_crush_do());
}

const std::string &Thing::on_owner_damage_lightning_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_lightning_do());
}

const std::string &Thing::on_owner_damage_energy_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_energy_do());
}

const std::string &Thing::on_owner_damage_acid_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_acid_do());
}

const std::string &Thing::on_owner_damage_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_digest_do());
}

const std::string &Thing::on_owner_damage_stat_con_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_stat_con_do());
}

const std::string &Thing::on_owner_damage_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_stat_str_do());
}

const std::string &Thing::on_owner_damage_stat_att_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_stat_att_do());
}

const std::string &Thing::on_owner_damage_melee_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_melee_do());
}

const std::string &Thing::on_owner_damage_necrosis_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_necrosis_do());
}

const std::string &Thing::on_owner_damage_natural_attack_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_damage_natural_attack_do());
}

const std::string &Thing::on_damage_poison_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_poison_do());
}

const std::string &Thing::on_damage_future1_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_future1_do());
}

const std::string &Thing::on_damage_future2_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_future2_do());
}

const std::string &Thing::on_damage_future3_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_future3_do());
}

const std::string &Thing::on_damage_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_cold_do());
}

const std::string &Thing::on_damage_fire_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_fire_do());
}

const std::string &Thing::on_damage_crush_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_crush_do());
}

const std::string &Thing::on_damage_lightning_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_lightning_do());
}

const std::string &Thing::on_damage_energy_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_energy_do());
}

const std::string &Thing::on_damage_acid_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_acid_do());
}

const std::string &Thing::on_damage_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_digest_do());
}

const std::string &Thing::on_damage_stat_con_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_stat_con_do());
}

const std::string &Thing::on_damage_stat_str_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_stat_str_do());
}

const std::string &Thing::on_damage_stat_att_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_stat_att_do());
}

const std::string &Thing::on_damage_melee_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_melee_do());
}

const std::string &Thing::on_damage_necrosis_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_necrosis_do());
}

const std::string &Thing::on_damage_natural_attack_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_damage_natural_attack_do());
}

const std::string &Thing::projectile_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->projectile_name());
}

const std::string &Thing::short_text_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->short_text_name());
}

const std::string &Thing::spawn_on_shoved(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_on_shoved());
}

const std::string &Thing::str1(void)
{
  TRACE_NO_INDENT();
  return (tp()->str1());
}

const std::string &Thing::str2(void)
{
  TRACE_NO_INDENT();
  return (tp()->str2());
}

const std::string &Thing::str4(void)
{
  TRACE_NO_INDENT();
  return (tp()->str4());
}

const std::string &Thing::is_allied_with(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_allied_with());
}

const std::string &Thing::text_description(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_description());
}

const std::string &Thing::text_enchant(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_enchant());
}

const std::string &Thing::text_hits(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_hits());
}

const std::string &Thing::damage_natural_attack_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_natural_attack_type());
}

const std::string &Thing::text_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_name());
}

const std::string &Thing::text_skill(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_skill());
}

const std::string &Thing::text_debuff(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_debuff());
}

const std::string &Thing::text_unused3(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused3());
}

const std::string &Thing::text_title(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_title());
}

const std::string &Thing::text_unused(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused());
}

const std::string &Thing::equip_carry_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->equip_carry_anim());
}

std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::bag_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (&itemsp()->bag);
  } else {
    //
    // Watch out here as lasers can have owners and do not live in bags.
    //
    dbg("No bag");
    return nullptr;
  }
}

const std::array< std::array< ThingId, MAX_BAG_WIDTH >, MAX_BAG_HEIGHT > *Thing::stat_const_bag(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (&itemsp()->bag);
  } else {
    //
    // Watch out here as lasers can have owners and do not live in bags.
    //
    dbg("No bag");
    return nullptr;
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

int Thing::group_get(void)
{
  if (is_laser()) {
    return THING_GROUP_PRIO_HIGH;
  }
  if (is_projectile()) {
    return THING_GROUP_PRIO_HIGH;
  }
  if (is_tmp_thing()) {
    return THING_GROUP_TMP;
  }
  return THING_GROUP_PRIO_NORMAL;
}

bool Thing::is_state_sleeping(void) { return is_sleeping; }
