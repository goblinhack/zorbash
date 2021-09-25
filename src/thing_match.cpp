//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dmap.h"
#include "my_level.h"
#include "my_math.h"
#include "my_string.h"
#include "my_sys.h"
#include "my_thing.h"
#include "slre.h"
#include <algorithm>

bool Thing::matches(const std::string &what) const
{
  if (strisregexp(what.c_str())) {
    struct slre slre;
    if (slre_compile(&slre, what.c_str())) {
      auto name = short_text_name();
      if (slre_match(&slre, name.c_str(), name.size(), 0 /* captures */)) {
        return true;
      }
    }
    return false;
  }

  if (ai_avoid_distance() && (what == "ai_avoid_distance")) {
    return true;
  }
  if (ai_enemy_memory() && (what == "ai_enemy_memory")) {
    return true;
  }
  if (ai_vision_distance() && (what == "ai_vision_distance")) {
    return true;
  }
  if (attack_eater() && (what == "attack_eater")) {
    return true;
  }
  if (attack_humanoid() && (what == "attack_humanoid")) {
    return true;
  }
  if (attack_living() && (what == "attack_living")) {
    return true;
  }
  if (attack_lunge() && (what == "attack_lunge")) {
    return true;
  }
  if (attack_meat() && (what == "attack_meat")) {
    return true;
  }
  if (attack_shove_chance_d1000() && (what == "attack_shove_chance_d1000")) {
    return true;
  }
  if (attack_shove() && (what == "attack_shove")) {
    return true;
  }
  if (blast_max_radius() && (what == "blast_max_radius")) {
    return true;
  }
  if (blast_min_radius() && (what == "blast_min_radius")) {
    return true;
  }
  if (damage_doubled_from_acid() && (what == "damage_doubled_from_acid")) {
    return true;
  }
  if (damage_doubled_from_fire() && (what == "damage_doubled_from_fire")) {
    return true;
  }
  if (damage_doubled_from_poison() && (what == "damage_doubled_from_poison")) {
    return true;
  }
  if (damage_doubled_from_water() && (what == "damage_doubled_from_water")) {
    return true;
  }
  if (enchant_level() && (what == "enchant_level")) {
    return true;
  }
  if (enchant_max() && (what == "enchant_max")) {
    return true;
  }
  if (gfx_flickers() && (what == "gfx_flickers")) {
    return true;
  }
  if (gfx_long_shadow_caster() && (what == "gfx_long_shadow_caster")) {
    return true;
  }
  if (gfx_solid_shadow() && (what == "gfx_solid_shadow")) {
    return true;
  }
  if (gfx_very_short_shadow_caster() && (what == "gfx_very_short_shadow_caster")) {
    return true;
  }
  if (hates_acid() && (what == "hates_acid")) {
    return true;
  }
  if (hates_fire() && (what == "hates_fire")) {
    return true;
  }
  if (hates_poison() && (what == "hates_poison")) {
    return true;
  }
  if (hates_water() && (what == "hates_water")) {
    return true;
  }
  if (is_able_to_change_levels() && (what == "is_able_to_change_levels")) {
    return true;
  }
  if (is_able_to_fall() && (what == "is_able_to_fall")) {
    return true;
  }
  if (is_able_to_fire_at() && (what == "is_able_to_fire_at")) {
    return true;
  }
  if (is_able_to_see_through_doors() && (what == "is_able_to_see_through_doors")) {
    return true;
  }
  if (is_able_to_walk_through_walls() && (what == "is_able_to_walk_through_walls")) {
    return true;
  }
  if (is_acid_lover() && (what == "is_acid_lover")) {
    return true;
  }
  if (is_acid() && (what == "is_acid")) {
    return true;
  }
  if (is_alive_monst() && (what == "is_alive_monst")) {
    return true;
  }
  if (is_alive_on_end_of_anim() && (what == "is_alive_on_end_of_anim")) {
    return true;
  }
  if (is_always_hit() && (what == "is_always_hit")) {
    return true;
  }
  if (is_ascend_dungeon() && (what == "is_ascend_dungeon")) {
    return true;
  }
  if (is_ascend_sewer() && (what == "is_ascend_sewer")) {
    return true;
  }
  if (is_attackable_by_monst() && (what == "is_attackable_by_monst")) {
    return true;
  }
  if (is_attackable_by_player() && (what == "is_attackable_by_player")) {
    return true;
  }
  if (is_auto_collect_item() && (what == "is_auto_collect_item")) {
    return true;
  }
  if (is_bag_item_container() && (what == "is_bag_item_container")) {
    return true;
  }
  if (is_bag_item_not_stackable() && (what == "is_bag_item_not_stackable")) {
    return true;
  }
  if (is_bag_item() && (what == "is_bag_item")) {
    return true;
  }
  if (is_bag() && (what == "is_bag")) {
    return true;
  }
  if (is_barrel() && (what == "is_barrel")) {
    return true;
  }
  if (is_bleeder() && (what == "is_bleeder")) {
    return true;
  }
  if (is_blood_splatter() && (what == "is_blood_splatter")) {
    return true;
  }
  if (is_blood() && (what == "is_blood")) {
    return true;
  }
  if (is_bones() && (what == "is_bones")) {
    return true;
  }
  if (is_brazier() && (what == "is_brazier")) {
    return true;
  }
  if (is_bridge() && (what == "is_bridge")) {
    return true;
  }
  if (is_burnable() && (what == "is_burnable")) {
    return true;
  }
  if (is_carrier_of_treasure_class_a() && (what == "is_carrier_of_treasure_class_a")) {
    return true;
  }
  if (is_carrier_of_treasure_class_b() && (what == "is_carrier_of_treasure_class_b")) {
    return true;
  }
  if (is_carrier_of_treasure_class_c() && (what == "is_carrier_of_treasure_class_c")) {
    return true;
  }
  if (is_chasm() && (what == "is_chasm")) {
    return true;
  }
  if (is_collectable() && (what == "is_collectable")) {
    return true;
  }
  if (is_collect_as_keys() && (what == "is_collect_as_keys")) {
    return true;
  }
  if (is_collected_as_gold() && (what == "is_collected_as_gold")) {
    return true;
  }
  if (is_combustible() && (what == "is_combustible")) {
    return true;
  }
  if (is_corpse() && (what == "is_corpse")) {
    return true;
  }
  if (is_corridor() && (what == "is_corridor")) {
    return true;
  }
  if (is_critical_to_level() && (what == "is_critical_to_level")) {
    return true;
  }
  if (is_cursor_can_hover_over_x2_click() && (what == "is_cursor_can_hover_over_x2_click")) {
    return true;
  }
  if (is_cursor_can_hover_over() && (what == "is_cursor_can_hover_over")) {
    return true;
  }
  if (is_cursor_path() && (what == "is_cursor_path")) {
    return true;
  }
  if (is_cursor() && (what == "is_cursor")) {
    return true;
  }
  if (is_dead_on_end_of_anim() && (what == "is_dead_on_end_of_anim")) {
    return true;
  }
  if (is_dead_on_shove() && (what == "is_dead_on_shove")) {
    return true;
  }
  if (is_debug_path() && (what == "is_debug_path")) {
    return true;
  }
  if (is_debug_type() && (what == "is_debug_type")) {
    return true;
  }
  if (is_deep_water() && (what == "is_deep_water")) {
    return true;
  }
  if (is_descend_dungeon() && (what == "is_descend_dungeon")) {
    return true;
  }
  if (is_descend_sewer() && (what == "is_descend_sewer")) {
    return true;
  }
  if (is_described_when_hovering_over() && (what == "is_described_when_hovering_over")) {
    return true;
  }
  if (is_dirt() && (what == "is_dirt")) {
    return true;
  }
  if (is_door() && (what == "is_door")) {
    return true;
  }
  if (is_droppable() && (what == "is_droppable")) {
    return true;
  }
  if (is_dry_grass() && (what == "is_dry_grass")) {
    return true;
  }
  if (is_enchantable() && (what == "is_enchantable")) {
    return true;
  }
  if (is_enchantstone() && (what == "is_enchantstone")) {
    return true;
  }
  if (is_engulf_chance_d1000() && (what == "is_engulf_chance_d1000")) {
    return true;
  }
  if (is_engulfer() && (what == "is_engulfer")) {
    return true;
  }
  if (is_ethereal_minion_generator() && (what == "is_ethereal_minion_generator")) {
    return true;
  }
  if (is_ethereal() && (what == "is_ethereal")) {
    return true;
  }
  if (is_explosion() && (what == "is_explosion")) {
    return true;
  }
  if (is_extreme_hazard() && (what == "is_extreme_hazard")) {
    return true;
  }
  if (is_fearless() && (what == "is_fearless")) {
    return true;
  }
  if (is_fire() && (what == "is_fire")) {
    return true;
  }
  if (is_floating() && (what == "is_floating")) {
    return true;
  }
  if (is_floor_deco() && (what == "is_floor_deco")) {
    return true;
  }
  if (is_floor() && (what == "is_floor")) {
    return true;
  }
  if (is_foilage() && (what == "is_foilage")) {
    return true;
  }
  if (is_food_eater() && (what == "is_food_eater")) {
    return true;
  }
  if (is_food() && (what == "is_food")) {
    return true;
  }
  if (is_gold() && (what == "is_gold")) {
    return true;
  }
  if (is_hazard() && (what == "is_hazard")) {
    return true;
  }
  if (is_health_booster() && (what == "is_health_booster")) {
    return true;
  }
  if (is_hittable() && (what == "is_hittable")) {
    return true;
  }
  if (is_humanoid() && (what == "is_humanoid")) {
    return true;
  }
  if (is_hunger_insatiable() && (what == "is_hunger_insatiable")) {
    return true;
  }
  if (is_indestructible() && (what == "is_indestructible")) {
    return true;
  }
  if (is_intelligent() && (what == "is_intelligent")) {
    return true;
  }
  if (is_interesting() && (what == "is_interesting")) {
    return true;
  }
  if (is_item_carrier() && (what == "is_item_carrier")) {
    return true;
  }
  if (is_item_collector() && (what == "is_item_collector")) {
    return true;
  }
  if (is_item_eater() && (what == "is_item_eater")) {
    return true;
  }
  if (is_item() && (what == "is_item")) {
    return true;
  }
  if (is_jelly_baby_eater() && (what == "is_jelly_baby_eater")) {
    return true;
  }
  if (is_jelly_baby() && (what == "is_jelly_baby")) {
    return true;
  }
  if (is_jelly_eater() && (what == "is_jelly_eater")) {
    return true;
  }
  if (is_jelly_parent() && (what == "is_jelly_parent")) {
    return true;
  }
  if (is_jelly() && (what == "is_jelly")) {
    return true;
  }
  if (random_jump_chance_d1000() && (what == "random_jump_chance_d1000")) {
    return true;
  }
  if (is_able_to_jump_distance() && (what == "is_able_to_jump_distance")) {
    return true;
  }
  if (is_able_to_jump_on_low_hp_chance_d1000() && (what == "is_able_to_jump_on_low_hp_chance_d1000")) {
    return true;
  }
  if (is_able_to_jump() && (what == "is_able_to_jump")) {
    return true;
  }
  if (is_key_collector() && (what == "is_key_collector")) {
    return true;
  }
  if (is_key() && (what == "is_key")) {
    return true;
  }
  if (is_killed_on_hit_or_miss() && (what == "is_killed_on_hit_or_miss")) {
    return true;
  }
  if (is_killed_on_hitting() && (what == "is_killed_on_hitting")) {
    return true;
  }
  if (is_laser() && (what == "is_laser")) {
    return true;
  }
  if (is_lava() && (what == "is_lava")) {
    return true;
  }
  if (is_light_blocker() && (what == "is_light_blocker")) {
    return true;
  }
  if (is_living() && (what == "is_living")) {
    return true;
  }
  if (is_loggable() && (what == "is_loggable")) {
    return true;
  }
  if (is_loggable() && (what == "is_loggable")) {
    return true;
  }
  if (is_meat_eater() && (what == "is_meat_eater")) {
    return true;
  }
  if (is_meat() && (what == "is_meat")) {
    return true;
  }
  if (is_minion_generator() && (what == "is_minion_generator")) {
    return true;
  }
  if (is_minion() && (what == "is_minion")) {
    return true;
  }
  if (is_monst() && (what == "is_monst")) {
    return true;
  }
  if (is_moveable() && (what == "is_moveable")) {
    return true;
  }
  if (is_obs_destructable() && (what == "is_obs_destructable")) {
    return true;
  }
  if (is_obs_wall_or_door() && (what == "is_obs_wall_or_door")) {
    return true;
  }
  if (is_msg() && (what == "is_msg")) {
    return true;
  }
  if (is_no_tile() && (what == "is_no_tile")) {
    return true;
  }
  if (is_openable() && (what == "is_openable")) {
    return true;
  }
  if (is_player() && (what == "is_player")) {
    return true;
  }
  if (is_poison() && (what == "is_poison")) {
    return true;
  }
  if (is_potion_eater() && (what == "is_potion_eater")) {
    return true;
  }
  if (is_potion() && (what == "is_potion")) {
    return true;
  }
  if (is_projectile() && (what == "is_projectile")) {
    return true;
  }
  if (is_removeable_if_out_of_slots() && (what == "is_removeable_if_out_of_slots")) {
    return true;
  }
  if (is_resurrectable() && (what == "is_resurrectable")) {
    return true;
  }
  if (is_ripple() && (what == "is_ripple")) {
    return true;
  }
  if (is_rock() && (what == "is_rock")) {
    return true;
  }
  if (unused_flag10() && (what == "unused_flag10")) {
    return true;
  }
  if (unused_flag11() && (what == "unused_flag11")) {
    return true;
  }
  if (unused_flag12() && (what == "unused_flag12")) {
    return true;
  }
  if (unused_flag13() && (what == "unused_flag13")) {
    return true;
  }
  if (unused_flag14() && (what == "unused_flag14")) {
    return true;
  }
  if (unused_flag15() && (what == "unused_flag15")) {
    return true;
  }
  if (unused_flag16() && (what == "unused_flag16")) {
    return true;
  }
  if (unused_flag17() && (what == "unused_flag17")) {
    return true;
  }
  if (unused_flag18() && (what == "unused_flag18")) {
    return true;
  }
  if (unused_flag19() && (what == "unused_flag19")) {
    return true;
  }
  if (unused_flag1() && (what == "unused_flag1")) {
    return true;
  }
  if (unused_flag20() && (what == "unused_flag20")) {
    return true;
  }
  if (unused_flag21() && (what == "unused_flag21")) {
    return true;
  }
  if (unused_flag22() && (what == "unused_flag22")) {
    return true;
  }
  if (unused_flag23() && (what == "unused_flag23")) {
    return true;
  }
  if (unused_flag24() && (what == "unused_flag24")) {
    return true;
  }
  if (unused_flag25() && (what == "unused_flag25")) {
    return true;
  }
  if (unused_flag26() && (what == "unused_flag26")) {
    return true;
  }
  if (unused_flag27() && (what == "unused_flag27")) {
    return true;
  }
  if (unused_flag28() && (what == "unused_flag28")) {
    return true;
  }
  if (unused_flag29() && (what == "unused_flag29")) {
    return true;
  }
  if (unused_flag2() && (what == "unused_flag2")) {
    return true;
  }
  if (unused_flag30() && (what == "unused_flag30")) {
    return true;
  }
  if (unused_flag31() && (what == "unused_flag31")) {
    return true;
  }
  if (unused_flag32() && (what == "unused_flag32")) {
    return true;
  }
  if (unused_flag33() && (what == "unused_flag33")) {
    return true;
  }
  if (unused_flag34() && (what == "unused_flag34")) {
    return true;
  }
  if (unused_flag35() && (what == "unused_flag35")) {
    return true;
  }
  if (unused_flag36() && (what == "unused_flag36")) {
    return true;
  }
  if (unused_flag37() && (what == "unused_flag37")) {
    return true;
  }
  if (unused_flag38() && (what == "unused_flag38")) {
    return true;
  }
  if (unused_flag39() && (what == "unused_flag39")) {
    return true;
  }
  if (unused_flag3() && (what == "unused_flag3")) {
    return true;
  }
  if (unused_flag40() && (what == "unused_flag40")) {
    return true;
  }
  if (unused_flag41() && (what == "unused_flag41")) {
    return true;
  }
  if (unused_flag42() && (what == "unused_flag42")) {
    return true;
  }
  if (unused_flag43() && (what == "unused_flag43")) {
    return true;
  }
  if (unused_flag44() && (what == "unused_flag44")) {
    return true;
  }
  if (unused_flag45() && (what == "unused_flag45")) {
    return true;
  }
  if (unused_flag46() && (what == "unused_flag46")) {
    return true;
  }
  if (unused_flag47() && (what == "unused_flag47")) {
    return true;
  }
  if (unused_flag48() && (what == "unused_flag48")) {
    return true;
  }
  if (is_rusty() && (what == "is_rusty")) {
    return true;
  }
  if (unused_flag4() && (what == "unused_flag4")) {
    return true;
  }
  if (unused_flag50() && (what == "unused_flag50")) {
    return true;
  }
  if (unused_flag51() && (what == "unused_flag51")) {
    return true;
  }
  if (unused_flag52() && (what == "unused_flag52")) {
    return true;
  }
  if (is_ai_wanderer() && (what == "is_ai_wanderer")) {
    return true;
  }
  if (is_organic() && (what == "is_organic")) {
    return true;
  }
  if (is_glass() && (what == "is_glass")) {
    return true;
  }
  if (is_stone() && (what == "is_stone")) {
    return true;
  }
  if (is_item_organic() && (what == "is_item_organic")) {
    return true;
  }
  if (is_metal() && (what == "is_metal")) {
    return true;
  }
  if (is_wooden() && (what == "is_wooden")) {
    return true;
  }
  if (unused_flag5() && (what == "unused_flag5")) {
    return true;
  }
  if (unused_flag6() && (what == "unused_flag6")) {
    return true;
  }
  if (unused_flag7() && (what == "unused_flag7")) {
    return true;
  }
  if (unused_flag8() && (what == "unused_flag8")) {
    return true;
  }
  if (unused_flag9() && (what == "unused_flag9")) {
    return true;
  }
  if (is_secret_door() && (what == "is_secret_door")) {
    return true;
  }
  if (is_sewer_wall() && (what == "is_sewer_wall")) {
    return true;
  }
  if (is_shallow_water() && (what == "is_shallow_water")) {
    return true;
  }
  if (is_shovable() && (what == "is_shovable")) {
    return true;
  }
  if (is_skillstone() && (what == "is_skillstone")) {
    return true;
  }
  if (is_skill() && (what == "is_skill")) {
    return true;
  }
  if (is_smoke() && (what == "is_smoke")) {
    return true;
  }
  if (is_soft_body() && (what == "is_soft_body")) {
    return true;
  }
  if (is_spawner() && (what == "is_spawner")) {
    return true;
  }
  if (is_spiderweb() && (what == "is_spiderweb")) {
    return true;
  }
  if (is_able_to_tire() && (what == "is_able_to_tire")) {
    return true;
  }
  if (is_steal_item_chance_d1000() && (what == "is_steal_item_chance_d1000")) {
    return true;
  }
  if (is_sticky() && (what == "is_sticky")) {
    return true;
  }
  if (is_sword() && (what == "is_sword")) {
    return true;
  }
  if (is_target_auto_select() && (what == "is_target_auto_select")) {
    return true;
  }
  if (is_throwable() && (what == "is_throwable")) {
    return true;
  }
  if (is_auto_throw() && (what == "is_auto_throw")) {
    return true;
  }
  if (is_tickable() && (what == "is_tickable")) {
    return true;
  }
  if (is_tmp_thing() && (what == "is_tmp_thing")) {
    return true;
  }
  if (is_torch() && (what == "is_torch")) {
    return true;
  }
  if (is_treasure_class_a() && (what == "is_treasure_class_a")) {
    return true;
  }
  if (is_treasure_class_b() && (what == "is_treasure_class_b")) {
    return true;
  }
  if (is_treasure_class_c() && (what == "is_treasure_class_c")) {
    return true;
  }
  if (is_treasure_type_chest() && (what == "is_treasure_type_chest")) {
    return true;
  }
  if (is_treasure_type_eater() && (what == "is_treasure_type_eater")) {
    return true;
  }
  if (is_treasure_type() && (what == "is_treasure_type")) {
    return true;
  }
  if (is_undead() && (what == "is_undead")) {
    return true;
  }
  if (is_usable() && (what == "is_usable")) {
    return true;
  }
  if (is_auto_use() && (what == "is_auto_use")) {
    return true;
  }
  if (is_used_when_thrown() && (what == "is_used_when_thrown")) {
    return true;
  }
  if (is_very_combustible() && (what == "is_very_combustible")) {
    return true;
  }
  if (is_wall_dungeon() && (what == "is_wall_dungeon")) {
    return true;
  }
  if (is_wall() && (what == "is_wall")) {
    return true;
  }
  if (is_wand_eater() && (what == "is_wand_eater")) {
    return true;
  }
  if (is_wand() && (what == "is_wand")) {
    return true;
  }
  if (is_water_lover() && (what == "is_water_lover")) {
    return true;
  }
  if (is_weapon() && (what == "is_weapon")) {
    return true;
  }
  if (is_weapon_wielder() && (what == "is_weapon_wielder")) {
    return true;
  }
  if (loves_fire() && (what == "loves_fire")) {
    return true;
  }
  if (loves_poison() && (what == "loves_poison")) {
    return true;
  }
  if (loves_spiderwebs() && (what == "loves_spiderwebs")) {
    return true;
  }
  if (minion_leash_distance() && (what == "minion_leash_distance")) {
    return true;
  }
  if (minion_limit() && (what == "minion_limit")) {
    return true;
  }
  if (range_max() && (what == "range_max")) {
    return true;
  }

  //
  // Any water type
  //
  if ((is_shallow_water() || is_deep_water()) && (what == "is_water")) {
    return true;
  }

  return (what == short_text_name());
}

std::function< int(Thingp) > Thing::matches_to_func(const std::string &what)
{
  if (what == "ai_avoid_distance") {
    return &Thing::ai_avoid_distance;
  }
  if (what == "ai_enemy_memory") {
    return &Thing::ai_enemy_memory;
  }
  if (what == "ai_vision_distance") {
    return &Thing::ai_vision_distance;
  }
  if (what == "attack_eater") {
    return &Thing::attack_eater;
  }
  if (what == "attack_humanoid") {
    return &Thing::attack_humanoid;
  }
  if (what == "attack_living") {
    return &Thing::attack_living;
  }
  if (what == "attack_lunge") {
    return &Thing::attack_lunge;
  }
  if (what == "attack_meat") {
    return &Thing::attack_meat;
  }
  if (what == "attack_shove_chance_d1000") {
    return &Thing::attack_shove_chance_d1000;
  }
  if (what == "attack_shove") {
    return &Thing::attack_shove;
  }
  if (what == "blast_max_radius") {
    return &Thing::blast_max_radius;
  }
  if (what == "blast_min_radius") {
    return &Thing::blast_min_radius;
  }
  if (what == "damage_doubled_from_acid") {
    return &Thing::damage_doubled_from_acid;
  }
  if (what == "damage_doubled_from_fire") {
    return &Thing::damage_doubled_from_fire;
  }
  if (what == "damage_doubled_from_poison") {
    return &Thing::damage_doubled_from_poison;
  }
  if (what == "damage_doubled_from_water") {
    return &Thing::damage_doubled_from_water;
  }
  if (what == "enchant_level") {
    return &Thing::enchant_level;
  }
  if (what == "enchant_max") {
    return &Thing::enchant_max;
  }
  if (what == "gfx_flickers") {
    return &Thing::gfx_flickers;
  }
  if (what == "gfx_long_shadow_caster") {
    return &Thing::gfx_long_shadow_caster;
  }
  if (what == "gfx_solid_shadow") {
    return &Thing::gfx_solid_shadow;
  }
  if (what == "gfx_very_short_shadow_caster") {
    return &Thing::gfx_very_short_shadow_caster;
  }
  if (what == "hates_acid") {
    return &Thing::hates_acid;
  }
  if (what == "hates_fire") {
    return &Thing::hates_fire;
  }
  if (what == "hates_poison") {
    return &Thing::hates_poison;
  }
  if (what == "hates_water") {
    return &Thing::hates_water;
  }
  if (what == "is_able_to_change_levels") {
    return &Thing::is_able_to_change_levels;
  }
  if (what == "is_able_to_fall") {
    return &Thing::is_able_to_fall;
  }
  if (what == "is_able_to_fire_at") {
    return &Thing::is_able_to_fire_at;
  }
  if (what == "is_able_to_see_through_doors") {
    return &Thing::is_able_to_see_through_doors;
  }
  if (what == "is_able_to_walk_through_walls") {
    return &Thing::is_able_to_walk_through_walls;
  }
  if (what == "is_acid_lover") {
    return &Thing::is_acid_lover;
  }
  if (what == "is_acid") {
    return &Thing::is_acid;
  }
  if (what == "is_alive_monst") {
    return &Thing::is_alive_monst;
  }
  if (what == "is_alive_on_end_of_anim") {
    return &Thing::is_alive_on_end_of_anim;
  }
  if (what == "is_always_hit") {
    return &Thing::is_always_hit;
  }
  if (what == "is_ascend_dungeon") {
    return &Thing::is_ascend_dungeon;
  }
  if (what == "is_ascend_sewer") {
    return &Thing::is_ascend_sewer;
  }
  if (what == "is_attackable_by_monst") {
    return &Thing::is_attackable_by_monst;
  }
  if (what == "is_attackable_by_player") {
    return &Thing::is_attackable_by_player;
  }
  if (what == "is_auto_collect_item") {
    return &Thing::is_auto_collect_item;
  }
  if (what == "is_bag_item_container") {
    return &Thing::is_bag_item_container;
  }
  if (what == "is_bag_item_not_stackable") {
    return &Thing::is_bag_item_not_stackable;
  }
  if (what == "is_bag_item") {
    return &Thing::is_bag_item;
  }
  if (what == "is_bag") {
    return &Thing::is_bag;
  }
  if (what == "is_barrel") {
    return &Thing::is_barrel;
  }
  if (what == "is_bleeder") {
    return &Thing::is_bleeder;
  }
  if (what == "is_blood") {
    return &Thing::is_blood;
  }
  if (what == "is_blood_splatter") {
    return &Thing::is_blood_splatter;
  }
  if (what == "is_bones") {
    return &Thing::is_bones;
  }
  if (what == "is_brazier") {
    return &Thing::is_brazier;
  }
  if (what == "is_bridge") {
    return &Thing::is_bridge;
  }
  if (what == "is_burnable") {
    return &Thing::is_burnable;
  }
  if (what == "is_carrier_of_treasure_class_a") {
    return &Thing::is_carrier_of_treasure_class_a;
  }
  if (what == "is_carrier_of_treasure_class_b") {
    return &Thing::is_carrier_of_treasure_class_b;
  }
  if (what == "is_carrier_of_treasure_class_c") {
    return &Thing::is_carrier_of_treasure_class_c;
  }
  if (what == "is_chasm") {
    return &Thing::is_chasm;
  }
  if (what == "is_collectable") {
    return &Thing::is_collectable;
  }
  if (what == "is_collect_as_keys") {
    return &Thing::is_collect_as_keys;
  }
  if (what == "is_collected_as_gold") {
    return &Thing::is_collected_as_gold;
  }
  if (what == "is_combustible") {
    return &Thing::is_combustible;
  }
  if (what == "is_corpse") {
    return &Thing::is_corpse;
  }
  if (what == "is_corridor") {
    return &Thing::is_corridor;
  }
  if (what == "is_critical_to_level") {
    return &Thing::is_critical_to_level;
  }
  if (what == "is_cursor_can_hover_over_x2_click") {
    return &Thing::is_cursor_can_hover_over_x2_click;
  }
  if (what == "is_cursor_can_hover_over") {
    return &Thing::is_cursor_can_hover_over;
  }
  if (what == "is_cursor_path") {
    return &Thing::is_cursor_path;
  }
  if (what == "is_cursor") {
    return &Thing::is_cursor;
  }
  if (what == "is_dead_on_end_of_anim") {
    return &Thing::is_dead_on_end_of_anim;
  }
  if (what == "is_dead_on_shove") {
    return &Thing::is_dead_on_shove;
  }
  if (what == "is_debug_path") {
    return &Thing::is_debug_path;
  }
  if (what == "is_debug_type") {
    return &Thing::is_debug_type;
  }
  if (what == "is_deep_water") {
    return &Thing::is_deep_water;
  }
  if (what == "is_descend_dungeon") {
    return &Thing::is_descend_dungeon;
  }
  if (what == "is_descend_sewer") {
    return &Thing::is_descend_sewer;
  }
  if (what == "is_described_when_hovering_over") {
    return &Thing::is_described_when_hovering_over;
  }
  if (what == "is_dirt") {
    return &Thing::is_dirt;
  }
  if (what == "is_door") {
    return &Thing::is_door;
  }
  if (what == "is_droppable") {
    return &Thing::is_droppable;
  }
  if (what == "is_dry_grass") {
    return &Thing::is_dry_grass;
  }
  if (what == "is_enchantable") {
    return &Thing::is_enchantable;
  }
  if (what == "is_enchantstone") {
    return &Thing::is_enchantstone;
  }
  if (what == "is_engulf_chance_d1000") {
    return &Thing::is_engulf_chance_d1000;
  }
  if (what == "is_engulfer") {
    return &Thing::is_engulfer;
  }
  if (what == "is_ethereal_minion_generator") {
    return &Thing::is_ethereal_minion_generator;
  }
  if (what == "is_ethereal") {
    return &Thing::is_ethereal;
  }
  if (what == "is_explosion") {
    return &Thing::is_explosion;
  }
  if (what == "is_extreme_hazard") {
    return &Thing::is_extreme_hazard;
  }
  if (what == "is_fearless") {
    return &Thing::is_fearless;
  }
  if (what == "is_fire") {
    return &Thing::is_fire;
  }
  if (what == "is_floating") {
    return &Thing::is_floating;
  }
  if (what == "is_floor_deco") {
    return &Thing::is_floor_deco;
  }
  if (what == "is_floor") {
    return &Thing::is_floor;
  }
  if (what == "is_foilage") {
    return &Thing::is_foilage;
  }
  if (what == "is_food_eater") {
    return &Thing::is_food_eater;
  }
  if (what == "is_food") {
    return &Thing::is_food;
  }
  if (what == "is_gold") {
    return &Thing::is_gold;
  }
  if (what == "is_hazard") {
    return &Thing::is_hazard;
  }
  if (what == "is_health_booster") {
    return &Thing::is_health_booster;
  }
  if (what == "is_hittable") {
    return &Thing::is_hittable;
  }
  if (what == "is_humanoid") {
    return &Thing::is_humanoid;
  }
  if (what == "is_hunger_insatiable") {
    return &Thing::is_hunger_insatiable;
  }
  if (what == "is_indestructible") {
    return &Thing::is_indestructible;
  }
  if (what == "is_intelligent") {
    return &Thing::is_intelligent;
  }
  if (what == "is_interesting") {
    return &Thing::is_interesting;
  }
  if (what == "is_item_carrier") {
    return &Thing::is_item_carrier;
  }
  if (what == "is_item_collector") {
    return &Thing::is_item_collector;
  }
  if (what == "is_item_eater") {
    return &Thing::is_item_eater;
  }
  if (what == "is_item") {
    return &Thing::is_item;
  }
  if (what == "is_jelly_baby_eater") {
    return &Thing::is_jelly_baby_eater;
  }
  if (what == "is_jelly_baby") {
    return &Thing::is_jelly_baby;
  }
  if (what == "is_jelly_eater") {
    return &Thing::is_jelly_eater;
  }
  if (what == "is_jelly_parent") {
    return &Thing::is_jelly_parent;
  }
  if (what == "is_jelly") {
    return &Thing::is_jelly;
  }
  if (what == "random_jump_chance_d1000") {
    return &Thing::random_jump_chance_d1000;
  }
  if (what == "is_able_to_jump_distance") {
    return &Thing::is_able_to_jump_distance;
  }
  if (what == "is_able_to_jump_on_low_hp_chance_d1000") {
    return &Thing::is_able_to_jump_on_low_hp_chance_d1000;
  }
  if (what == "is_able_to_jump") {
    return &Thing::is_able_to_jump;
  }
  if (what == "is_key_collector") {
    return &Thing::is_key_collector;
  }
  if (what == "is_key") {
    return &Thing::is_key;
  }
  if (what == "is_killed_on_hit_or_miss") {
    return &Thing::is_killed_on_hit_or_miss;
  }
  if (what == "is_killed_on_hitting") {
    return &Thing::is_killed_on_hitting;
  }
  if (what == "is_laser") {
    return &Thing::is_laser;
  }
  if (what == "is_lava") {
    return &Thing::is_lava;
  }
  if (what == "is_light_blocker") {
    return &Thing::is_light_blocker;
  }
  if (what == "is_living") {
    return &Thing::is_living;
  }
  if (what == "is_loggable") {
    return &Thing::is_loggable;
  }
  if (what == "is_loggable") {
    return &Thing::is_loggable;
  }
  if (what == "is_meat_eater") {
    return &Thing::is_meat_eater;
  }
  if (what == "is_meat") {
    return &Thing::is_meat;
  }
  if (what == "is_minion_generator") {
    return &Thing::is_minion_generator;
  }
  if (what == "is_minion") {
    return &Thing::is_minion;
  }
  if (what == "is_monst") {
    return &Thing::is_monst;
  }
  if (what == "is_moveable") {
    return &Thing::is_moveable;
  }
  if (what == "is_obs_destructable") {
    return &Thing::is_obs_destructable;
  }
  if (what == "is_obs_wall_or_door") {
    return &Thing::is_obs_wall_or_door;
  }
  if (what == "is_msg") {
    return &Thing::is_msg;
  }
  if (what == "is_no_tile") {
    return &Thing::is_no_tile;
  }
  if (what == "is_openable") {
    return &Thing::is_openable;
  }
  if (what == "is_player") {
    return &Thing::is_player;
  }
  if (what == "is_poison") {
    return &Thing::is_poison;
  }
  if (what == "is_potion_eater") {
    return &Thing::is_potion_eater;
  }
  if (what == "is_potion") {
    return &Thing::is_potion;
  }
  if (what == "is_projectile") {
    return &Thing::is_projectile;
  }
  if (what == "is_removeable_if_out_of_slots") {
    return &Thing::is_removeable_if_out_of_slots;
  }
  if (what == "is_resurrectable") {
    return &Thing::is_resurrectable;
  }
  if (what == "is_ripple") {
    return &Thing::is_ripple;
  }
  if (what == "is_rock") {
    return &Thing::is_rock;
  }
  if (what == "unused_flag10") {
    return &Thing::unused_flag10;
  }
  if (what == "unused_flag11") {
    return &Thing::unused_flag11;
  }
  if (what == "unused_flag12") {
    return &Thing::unused_flag12;
  }
  if (what == "unused_flag13") {
    return &Thing::unused_flag13;
  }
  if (what == "unused_flag14") {
    return &Thing::unused_flag14;
  }
  if (what == "unused_flag15") {
    return &Thing::unused_flag15;
  }
  if (what == "unused_flag16") {
    return &Thing::unused_flag16;
  }
  if (what == "unused_flag17") {
    return &Thing::unused_flag17;
  }
  if (what == "unused_flag18") {
    return &Thing::unused_flag18;
  }
  if (what == "unused_flag19") {
    return &Thing::unused_flag19;
  }
  if (what == "unused_flag1") {
    return &Thing::unused_flag1;
  }
  if (what == "unused_flag20") {
    return &Thing::unused_flag20;
  }
  if (what == "unused_flag21") {
    return &Thing::unused_flag21;
  }
  if (what == "unused_flag22") {
    return &Thing::unused_flag22;
  }
  if (what == "unused_flag23") {
    return &Thing::unused_flag23;
  }
  if (what == "unused_flag24") {
    return &Thing::unused_flag24;
  }
  if (what == "unused_flag25") {
    return &Thing::unused_flag25;
  }
  if (what == "unused_flag26") {
    return &Thing::unused_flag26;
  }
  if (what == "unused_flag27") {
    return &Thing::unused_flag27;
  }
  if (what == "unused_flag28") {
    return &Thing::unused_flag28;
  }
  if (what == "unused_flag29") {
    return &Thing::unused_flag29;
  }
  if (what == "unused_flag2") {
    return &Thing::unused_flag2;
  }
  if (what == "unused_flag30") {
    return &Thing::unused_flag30;
  }
  if (what == "unused_flag31") {
    return &Thing::unused_flag31;
  }
  if (what == "unused_flag32") {
    return &Thing::unused_flag32;
  }
  if (what == "unused_flag33") {
    return &Thing::unused_flag33;
  }
  if (what == "unused_flag34") {
    return &Thing::unused_flag34;
  }
  if (what == "unused_flag35") {
    return &Thing::unused_flag35;
  }
  if (what == "unused_flag36") {
    return &Thing::unused_flag36;
  }
  if (what == "unused_flag37") {
    return &Thing::unused_flag37;
  }
  if (what == "unused_flag38") {
    return &Thing::unused_flag38;
  }
  if (what == "unused_flag39") {
    return &Thing::unused_flag39;
  }
  if (what == "unused_flag3") {
    return &Thing::unused_flag3;
  }
  if (what == "unused_flag40") {
    return &Thing::unused_flag40;
  }
  if (what == "unused_flag41") {
    return &Thing::unused_flag41;
  }
  if (what == "unused_flag42") {
    return &Thing::unused_flag42;
  }
  if (what == "unused_flag43") {
    return &Thing::unused_flag43;
  }
  if (what == "unused_flag44") {
    return &Thing::unused_flag44;
  }
  if (what == "unused_flag45") {
    return &Thing::unused_flag45;
  }
  if (what == "unused_flag46") {
    return &Thing::unused_flag46;
  }
  if (what == "unused_flag47") {
    return &Thing::unused_flag47;
  }
  if (what == "unused_flag48") {
    return &Thing::unused_flag48;
  }
  if (what == "is_rusty") {
    return &Thing::is_rusty;
  }
  if (what == "unused_flag4") {
    return &Thing::unused_flag4;
  }
  if (what == "unused_flag50") {
    return &Thing::unused_flag50;
  }
  if (what == "unused_flag51") {
    return &Thing::unused_flag51;
  }
  if (what == "unused_flag52") {
    return &Thing::unused_flag52;
  }
  if (what == "is_ai_wanderer") {
    return &Thing::is_ai_wanderer;
  }
  if (what == "is_organic") {
    return &Thing::is_organic;
  }
  if (what == "is_glass") {
    return &Thing::is_glass;
  }
  if (what == "is_stone") {
    return &Thing::is_stone;
  }
  if (what == "is_item_organic") {
    return &Thing::is_item_organic;
  }
  if (what == "is_metal") {
    return &Thing::is_metal;
  }
  if (what == "is_wooden") {
    return &Thing::is_wooden;
  }
  if (what == "unused_flag5") {
    return &Thing::unused_flag5;
  }
  if (what == "unused_flag6") {
    return &Thing::unused_flag6;
  }
  if (what == "unused_flag7") {
    return &Thing::unused_flag7;
  }
  if (what == "unused_flag8") {
    return &Thing::unused_flag8;
  }
  if (what == "unused_flag9") {
    return &Thing::unused_flag9;
  }
  if (what == "is_secret_door") {
    return &Thing::is_secret_door;
  }
  if (what == "is_sewer_wall") {
    return &Thing::is_sewer_wall;
  }
  if (what == "is_shallow_water") {
    return &Thing::is_shallow_water;
  }
  if (what == "is_shovable") {
    return &Thing::is_shovable;
  }
  if (what == "is_skill") {
    return &Thing::is_skill;
  }
  if (what == "is_skillstone") {
    return &Thing::is_skillstone;
  }
  if (what == "is_smoke") {
    return &Thing::is_smoke;
  }
  if (what == "is_soft_body") {
    return &Thing::is_soft_body;
  }
  if (what == "is_spawner") {
    return &Thing::is_spawner;
  }
  if (what == "is_spiderweb") {
    return &Thing::is_spiderweb;
  }
  if (what == "is_able_to_tire") {
    return &Thing::is_able_to_tire;
  }
  if (what == "is_steal_item_chance_d1000") {
    return &Thing::is_steal_item_chance_d1000;
  }
  if (what == "is_sticky") {
    return &Thing::is_sticky;
  }
  if (what == "is_sword") {
    return &Thing::is_sword;
  }
  if (what == "is_target_auto_select") {
    return &Thing::is_target_auto_select;
  }
  if (what == "is_throwable") {
    return &Thing::is_throwable;
  }
  if (what == "is_auto_throw") {
    return &Thing::is_auto_throw;
  }
  if (what == "is_tickable") {
    return &Thing::is_tickable;
  }
  if (what == "is_tmp_thing") {
    return &Thing::is_tmp_thing;
  }
  if (what == "is_torch") {
    return &Thing::is_torch;
  }
  if (what == "is_treasure_class_a") {
    return &Thing::is_treasure_class_a;
  }
  if (what == "is_treasure_class_b") {
    return &Thing::is_treasure_class_b;
  }
  if (what == "is_treasure_class_c") {
    return &Thing::is_treasure_class_c;
  }
  if (what == "is_treasure_type_chest") {
    return &Thing::is_treasure_type_chest;
  }
  if (what == "is_treasure_type_eater") {
    return &Thing::is_treasure_type_eater;
  }
  if (what == "is_treasure_type") {
    return &Thing::is_treasure_type;
  }
  if (what == "is_undead") {
    return &Thing::is_undead;
  }
  if (what == "is_usable") {
    return &Thing::is_usable;
  }
  if (what == "is_auto_use") {
    return &Thing::is_auto_use;
  }
  if (what == "is_used_when_thrown") {
    return &Thing::is_used_when_thrown;
  }
  if (what == "is_very_combustible") {
    return &Thing::is_very_combustible;
  }
  if (what == "is_wall_dungeon") {
    return &Thing::is_wall_dungeon;
  }
  if (what == "is_wall") {
    return &Thing::is_wall;
  }
  if (what == "is_wand_eater") {
    return &Thing::is_wand_eater;
  }
  if (what == "is_wand") {
    return &Thing::is_wand;
  }
  if (what == "is_water_lover") {
    return &Thing::is_water_lover;
  }
  if (what == "is_water") {
    return &Thing::is_water;
  }
  if (what == "is_weapon") {
    return &Thing::is_weapon;
  }
  if (what == "is_weapon_wielder") {
    return &Thing::is_weapon_wielder;
  }
  if (what == "loves_fire") {
    return &Thing::loves_fire;
  }
  if (what == "loves_poison") {
    return &Thing::loves_poison;
  }
  if (what == "loves_spiderwebs") {
    return &Thing::loves_spiderwebs;
  }
  if (what == "minion_leash_distance") {
    return &Thing::minion_leash_distance;
  }
  if (what == "minion_limit") {
    return &Thing::minion_limit;
  }
  if (what == "range_max") {
    return &Thing::range_max;
  }

  DIE("could not find a matches function for [%s]", what.c_str());
}
