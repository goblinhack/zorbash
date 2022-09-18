//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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

int Thing::damaged_chance_d10000(void)
{
  TRACE_NO_INDENT();

  int chance = tp()->damaged_chance_d10000();
  int e      = enchant_get();
  while (e-- > 0) {
    chance /= 2;
  }

  return chance;
}

int Thing::crit_chance_d10000(void)
{
  TRACE_NO_INDENT();

  int chance = tp()->crit_chance_d10000();
  int e      = enchant_get();
  while (e-- > 0) {
    chance *= 2;
  }

  return chance;
}

int Thing::is_able_to_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_shove());
}

int Thing::blast_max_radius(void)
{
  TRACE_NO_INDENT();

  int radius = tp()->blast_max_radius();
  if (radius) {
    radius += enchant_get();
  }
  return radius;
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

int Thing::initial_charge_count(void)
{
  TRACE_NO_INDENT();
  return (tp()->charge_count());
}

int Thing::gfx_ascii_shown(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown());
}

int Thing::gfx_pixelart_animated_can_hflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_can_hflip());
}

int Thing::gfx_pixelart_animated_can_vflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_can_vflip());
}

int Thing::gfx_pixelart_animated_no_dir(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_no_dir());
}

int Thing::gfx_pixelart_attack_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_attack_anim());
}

int Thing::gfx_pixelart_bounce_always(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_bounce_always());
}

int Thing::gfx_pixelart_bounce_on_move(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_bounce_on_move());
}

int Thing::unused_flag103(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag103());
}

int Thing::gfx_pixelart_flickers(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_flickers());
}

int Thing::gfx_glows(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_glows());
}

int Thing::gfx_pixelart_health_bar_autohide(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_autohide());
}

int Thing::gfx_pixelart_health_bar_shown(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_shown());
}

int Thing::gfx_pixelart_shadow_long(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_long());
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

int Thing::gfx_pixelart_shadow_short(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_short());
}

int Thing::gfx_pixelart_shown_in_bg(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shown_in_bg());
}

int Thing::gfx_pixelart_show_outlined(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_outlined());
}

int Thing::gfx_pixelart_shadow_solid(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_solid());
}

int Thing::gfx_pixelart_shadow_very_short(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_very_short());
}

int Thing::gfx_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_water());
}

int Thing::gfx_pixelart_equip_carry_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_equip_carry_anim());
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

int Thing::environ_avoids_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_avoids_cold());
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

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_see_through_doors()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_see_through_doors());
}

int Thing::is_able_to_walk_through_walls(void)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_walk_through_walls()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_walk_through_walls());
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

int Thing::is_able_to_burn(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_burn());
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

int Thing::is_collected_as_keys(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collected_as_keys());
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

int Thing::is_dead_check(void)
{
  TRACE_NO_INDENT();
  return is_dead;
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

int Thing::is_cursor_path_hazard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path_hazard());
}

int Thing::is_cursor_path_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path_blocker());
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

int Thing::is_eater_of_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_food());
}

int Thing::is_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_food());
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

int Thing::is_very_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_hard());
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

int Thing::is_thief(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_thief());
}

int Thing::is_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item());
}

int Thing::is_eater_of_jelly(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_jelly());
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

int Thing::is_eater_of_meat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_meat());
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

int Thing::is_eater_of_potions(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_potions());
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

int Thing::is_corpse_with_bones(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corpse_with_bones());
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

int Thing::is_eater_of_helmets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_helmets());
}

int Thing::is_eater_of_amulets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_amulets());
}

int Thing::is_eater_of_weapons(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_weapons());
}

int Thing::is_eater_of_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_boots());
}

int Thing::is_eater_of_gauntlets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_gauntlets());
}

int Thing::is_eater_of_cloaks(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_cloaks());
}

int Thing::is_eater_of_shields(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_shields());
}

int Thing::is_eater_of_rings(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_rings());
}

int Thing::is_eater_of_staffs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_staffs());
}

int Thing::is_eater_of_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_armor());
}

int Thing::is_eater_of_wands(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_wands());
}

int Thing::is_dry_grass_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dry_grass_trampled());
}

int Thing::is_cowardly(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cowardly());
}

int Thing::appearing_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->appearing_chance_d1000());
}

int Thing::is_throw_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_throw_blocker());
}

int Thing::is_able_to_freeze(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_freeze());
}

int Thing::is_gelatinous(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gelatinous());
}

int Thing::is_plant(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_plant());
}

int Thing::is_steam(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_steam());
}

int Thing::is_carnivorous_plant(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_carnivorous_plant());
}

int Thing::is_basalt(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_basalt());
}

int Thing::is_shovable_and_sticky(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shovable_and_sticky());
}

int Thing::is_block_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_block_of_ice());
}

int Thing::is_able_to_break_out_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_ice());
}

int Thing::is_brittle(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_brittle());
}

int Thing::unused_flag87(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag87());
}

int Thing::is_able_to_swim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_swim());
}

int Thing::gfx_ascii_shown_as_gray_in_shadow(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown_as_gray_in_shadow());
}

int Thing::gfx_ascii_shown_in_bg(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown_in_bg());
}

int Thing::gfx_ascii_fade_with_dist(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fade_with_dist());
}

int Thing::is_jump_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_jump_blocker());
}

int Thing::tick_prio(void)
{
  TRACE_NO_INDENT();
  return (tp()->tick_prio());
}

int Thing::attack_no_msg(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_no_msg());
}

int Thing::is_able_to_attack_owner(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_attack_owner());
}

int Thing::is_dagger(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dagger());
}

int Thing::is_lifeless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_lifeless());
}

int Thing::is_immune_to_draining(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_draining());
}

int Thing::is_key_special(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_key_special());
}

int Thing::is_crystal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crystal());
}

int Thing::noise_on_moving(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_moving());
}

int Thing::is_tireless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tireless());
}

int Thing::gfx_pixelart_wobbles_when_hit(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_wobbles_when_hit());
}

int Thing::is_snake(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_snake());
}

int Thing::is_item_targetted(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_targetted());
}

int Thing::noise_additional_on_teleporting(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_additional_on_teleporting());
}

int Thing::is_able_to_teleport_attack_chance_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_attack_chance_d1000());
}

int Thing::teleport_distance(void)
{
  TRACE_NO_INDENT();
  return (tp()->teleport_distance());
}

int Thing::is_able_to_teleport_attack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_attack());
}

int Thing::is_able_to_teleport_without_tiring(void)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_teleport_without_tiring()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_teleport_without_tiring());
}

int Thing::is_able_to_teleport_escape(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_escape());
}

int Thing::unused_flag123(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_flag123());
}

int Thing::is_pack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pack());
}

int Thing::is_pillar(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pillar());
}

int Thing::collision_hit_two_tiles_ahead(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_two_tiles_ahead());
}

int Thing::is_flat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_flat());
}

int Thing::is_target_radial(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_target_radial());
}

int Thing::is_staff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_staff());
}

int Thing::collision_hit_adj(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_adj());
}

int Thing::collision_hit_180(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_180());
}

int Thing::stamina_drain_on_attacking(void)
{
  TRACE_NO_INDENT();
  return (tp()->stamina_drain_on_attacking());
}

int Thing::stamina_drain_on_using(void)
{
  TRACE_NO_INDENT();
  return (tp()->stamina_drain_on_using());
}

int Thing::collision_hit_360(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_360());
}

int Thing::is_dead_on_falling(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_falling());
}

int Thing::is_temperature_sensitive(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_temperature_sensitive());
}

int Thing::is_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cold());
}

int Thing::is_temperature_change_sensitive(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_temperature_change_sensitive());
}

int Thing::is_very_heavy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_heavy());
}

int Thing::gfx_pixelart_health_bar_only_when_awake(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_only_when_awake());
}

int Thing::gfx_pixelart_show_asleep_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_asleep_anim());
}

int Thing::noise_additional_on_jump_end(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_additional_on_jump_end());
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

int Thing::is_air_breathher(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_air_breathher());
}

int Thing::noise_on_dropping(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_dropping());
}

int Thing::is_obstacle_when_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obstacle_when_dead());
}

int Thing::is_green_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blood());
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

int Thing::is_eater_of_green_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_green_blood());
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

int Thing::is_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hard());
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

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_jump_without_tiring()) {
        return true;
      }
    }
  }

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

int Thing::is_able_to_see_in_the_dark(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_in_the_dark());
}

int Thing::gfx_pixelart_anim_synced_with_owner(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_anim_synced_with_owner());
}

int Thing::is_magical(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_magical());
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

int Thing::is_eater_of_red_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_red_blood());
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

int Thing::is_able_to_use_wands_or_staffs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_wands_or_staffs());
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

int Thing::is_soft(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_soft());
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

int Thing::is_target_select(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_target_select());
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

int Thing::is_eater_of_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_treasure());
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

int Thing::is_eater_of_magical_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_magical_items());
}

int Thing::is_wand(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wand());
}

int Thing::is_wand_or_staff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wand_or_staff());
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
  if (buff_find_is_fire_proof()) {
    return true;
  }
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

int Thing::thing_size(void)
{
  TRACE_NO_INDENT();
  return (tp()->thing_size());
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  infop()->score = v;
}

void Thing::score_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys = v);
  return n;
}

int Thing::keys_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys -= v);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return n;
}

int Thing::keys_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys += v);
  return n;
}

int Thing::keys_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys--);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return n;
}

int Thing::keys_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// movement_remaining
////////////////////////////////////////////////////////////////////////////
int Thing::movement_remaining(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->movement_remaining);
  } else {
    return 0;
  }
}

int Thing::movement_remaining_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining = v);
  return n;
}

int Thing::movement_remaining_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining -= v);
  return n;
}

int Thing::movement_remaining_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining += v);
  return n;
}

int Thing::movement_remaining_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining--);
  return n;
}

int Thing::movement_remaining_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->movement_remaining++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 = v);
  return n;
}

int Thing::stats02_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 -= v);
  return n;
}

int Thing::stats02_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 += v);
  return n;
}

int Thing::stats02_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02--);
  return n;
}

int Thing::stats02_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 = v);
  return n;
}

int Thing::stats03_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 -= v);
  return n;
}

int Thing::stats03_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 += v);
  return n;
}

int Thing::stats03_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03--);
  return n;
}

int Thing::stats03_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 = v);
  return n;
}

int Thing::stats04_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 -= v);
  return n;
}

int Thing::stats04_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 += v);
  return n;
}

int Thing::stats04_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04--);
  return n;
}

int Thing::stats04_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 = v);
  return n;
}

int Thing::stats05_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 -= v);
  return n;
}

int Thing::stats05_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 += v);
  return n;
}

int Thing::stats05_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05--);
  return n;
}

int Thing::stats05_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 = v);
  return n;
}

int Thing::stats06_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 -= v);
  return n;
}

int Thing::stats06_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 += v);
  return n;
}

int Thing::stats06_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06--);
  return n;
}

int Thing::stats06_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 = v);
  return n;
}

int Thing::stats07_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 -= v);
  return n;
}

int Thing::stats07_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 += v);
  return n;
}

int Thing::stats07_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07--);
  return n;
}

int Thing::stats07_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 = v);
  return n;
}

int Thing::stats09_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 -= v);
  return n;
}

int Thing::stats09_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 += v);
  return n;
}

int Thing::stats09_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09--);
  return n;
}

int Thing::stats09_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def_mod = v);
  return n;
}

int Thing::stat_def_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def_mod -= v);
  return n;
}

int Thing::stat_def_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def_mod += v);
  return n;
}

int Thing::stat_def_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def_mod--);
  return n;
}

int Thing::stat_def_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_def_mod++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_con_mod = v);
  return n;
}

int Thing::stat_con_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_con_mod -= v);
  return n;
}

int Thing::stat_con_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_con_mod += v);
  return n;
}

int Thing::stat_con_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_con_mod--);
  return n;
}

int Thing::stat_con_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_con_mod++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_dex_mod = v);
  return n;
}

int Thing::stat_dex_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_dex_mod -= v);
  return n;
}

int Thing::stat_dex_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_dex_mod += v);
  return n;
}

int Thing::stat_dex_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_dex_mod--);
  return n;
}

int Thing::stat_dex_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_dex_mod++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att_mod = v);
  return n;
}

int Thing::stat_att_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att_mod -= v);
  return n;
}

int Thing::stat_att_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att_mod += v);
  return n;
}

int Thing::stat_att_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att_mod--);
  return n;
}

int Thing::stat_att_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_att_mod++);
  return n;
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
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_mod = v);
  return n;
}

int Thing::stat_str_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_mod -= v);
  return n;
}

int Thing::stat_str_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_mod += v);
  return n;
}

int Thing::stat_str_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_mod--);
  return n;
}

int Thing::stat_str_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_mod++);
  return n;
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
  return n;
}

int Thing::distance_throw_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw -= v);
  return n;
}

int Thing::distance_throw_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw += v);
  return n;
}

int Thing::distance_throw_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw--);
  return n;
}

int Thing::distance_throw_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw++);
  return n;
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
// damaged_count
////////////////////////////////////////////////////////////////////////////
int Thing::damaged_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->damaged_count);
  } else {
    return 0;
  }
}

int Thing::damaged_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count = v);
}

int Thing::damaged_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count -= v);
}

int Thing::damaged_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count += v);
}

int Thing::damaged_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count--);
}

int Thing::damaged_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count++);
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
// tick_last_i_attacked
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_i_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_i_attacked);
  } else {
    return 0;
  }
}

uint32_t Thing::tick_last_i_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked = v);
}

uint32_t Thing::tick_last_i_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked -= v);
}

uint32_t Thing::tick_last_i_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked += v);
}

uint32_t Thing::tick_last_i_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked--);
}

uint32_t Thing::tick_last_i_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked++);
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

const std::string &Thing::gfx_anim_use(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_anim_use());
}

const std::string &Thing::target_name_laser(void)
{
  TRACE_NO_INDENT();
  return (tp()->target_name_laser());
}

const std::string &Thing::target_name_radial(void)
{
  TRACE_NO_INDENT();
  return (tp()->target_name_radial());
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

const std::string &Thing::on_you_nat_att_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_nat_att_do());
}

const std::string &Thing::on_born_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_born_do());
}

const std::string &Thing::on_resting_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_resting_do());
}

const std::string &Thing::on_waiting_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_waiting_do());
}

const std::string &Thing::on_stuck_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_stuck_do());
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

const std::string &Thing::on_thrown_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_thrown_do());
}

const std::string &Thing::on_dropped_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_dropped_do());
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

const std::string &Thing::on_you_are_hit_but_dodge_it_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_hit_but_dodge_it_do());
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

const std::string &Thing::on_swing_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_swing_do());
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

const std::string &Thing::target_name_projectile(void)
{
  TRACE_NO_INDENT();
  return (tp()->target_name_projectile());
}

const std::string &Thing::text_short_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_short_name());
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

const std::string &Thing::damage_nat_att_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_nat_att_type());
}

const std::string &Thing::text_long_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_long_name());
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

std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *Thing::bag_get(void)
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

const std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *Thing::stat_const_bag(void)
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
