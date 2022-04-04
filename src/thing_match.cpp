//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_string.hpp"
#include "my_thing.hpp"
#include "slre.hpp"
#include <algorithm>

bool Thing::matches(const std::string &what)
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

  if (is_able_to_attack_mobs() && (what == "is_able_to_attack_mobs")) {
    return true;
  }
  if (is_able_to_break_down_doors() && (what == "is_able_to_break_down_doors")) {
    return true;
  }
  if (is_able_to_break_out_of_webs() && (what == "is_able_to_break_out_of_webs")) {
    return true;
  }
  if (is_able_to_collect_keys() && (what == "is_able_to_collect_keys")) {
    return true;
  }
  if (ai_detect_secret_doors() && (what == "ai_detect_secret_doors")) {
    return true;
  }
  if (is_able_to_enchant_items() && (what == "is_able_to_enchant_items")) {
    return true;
  }
  if (is_able_to_jump() && (what == "is_able_to_jump")) {
    return true;
  }
  if (is_able_to_learn_skills() && (what == "is_able_to_learn_skills")) {
    return true;
  }
  if (is_able_to_open_doors() && (what == "is_able_to_open_doors")) {
    return true;
  }
  if (is_able_to_see_through_doors() && (what == "is_able_to_see_through_doors")) {
    return true;
  }
  if (is_able_to_shove() && (what == "is_able_to_shove")) {
    return true;
  }
  if (is_able_to_walk_through_walls() && (what == "is_able_to_walk_through_walls")) {
    return true;
  }
  if (is_exit_finder() && (what == "is_exit_finder")) {
    return true;
  }
  if (is_item_collector() && (what == "is_item_collector")) {
    return true;
  }
  if (is_explorer() && (what == "is_explorer")) {
    return true;
  }
  if (ai_resent_count() && (what == "ai_resent_count")) {
    return true;
  }
  if (ai_wanderer() && (what == "ai_wanderer")) {
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
  if (attack_undead() && (what == "attack_undead")) {
    return true;
  }
  if (blast_max_radius() && (what == "blast_max_radius")) {
    return true;
  }
  if (blast_min_radius() && (what == "blast_min_radius")) {
    return true;
  }
  if (enchant_level() && (what == "enchant_level")) {
    return true;
  }
  if (enchant_max() && (what == "enchant_max")) {
    return true;
  }
  if (environ_avoids_acid() && (what == "environ_avoids_acid")) {
    return true;
  }
  if (environ_avoids_cold() && (what == "environ_avoids_cold")) {
    return true;
  }
  if (environ_avoids_fire() && (what == "environ_avoids_fire")) {
    return true;
  }
  if (environ_avoids_necrosis() && (what == "environ_avoids_necrosis")) {
    return true;
  }
  if (environ_avoids_poison() && (what == "environ_avoids_poison")) {
    return true;
  }
  if (environ_avoids_water() && (what == "environ_avoids_water")) {
    return true;
  }
  if (is_immune_to_acid() && (what == "is_immune_to_acid")) {
    return true;
  }
  if (is_immune_to_fire() && (what == "is_immune_to_fire")) {
    return true;
  }
  if (is_immune_to_necrosis() && (what == "is_immune_to_necrosis")) {
    return true;
  }
  if (is_immune_to_poison() && (what == "is_immune_to_poison")) {
    return true;
  }
  if (is_immune_to_spiderwebs() && (what == "is_immune_to_spiderwebs")) {
    return true;
  }
  if (is_immune_to_water() && (what == "is_immune_to_water")) {
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
  if (is_able_to_change_levels() && (what == "is_able_to_change_levels")) {
    return true;
  }
  if (is_able_to_fall() && (what == "is_able_to_fall")) {
    return true;
  }
  if (is_able_to_fire_at() && (what == "is_able_to_fire_at")) {
    return true;
  }
  if (is_able_to_see_in_the_dark() && (what == "is_able_to_see_in_the_dark")) {
    return true;
  }
  if (is_able_to_tire() && (what == "is_able_to_tire")) {
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
  if (is_auto_equipped() && (what == "is_auto_equipped")) {
    return true;
  }
  if (is_auto_throw() && (what == "is_auto_throw")) {
    return true;
  }
  if (is_auto_use() && (what == "is_auto_use")) {
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
  if (is_red_blood_eater() && (what == "is_red_blood_eater")) {
    return true;
  }
  if (is_red_splatter() && (what == "is_red_splatter")) {
    return true;
  }
  if (is_red_blood() && (what == "is_red_blood")) {
    return true;
  }
  if (is_green_blood_eater() && (what == "is_green_blood_eater")) {
    return true;
  }
  if (is_green_splatter() && (what == "is_green_splatter")) {
    return true;
  }
  if (is_green_blood() && (what == "is_green_blood")) {
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
  if (is_buff() && (what == "is_buff")) {
    return true;
  }
  if (is_burnable() && (what == "is_burnable")) {
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
  if (is_cursor_can_hover_over() && (what == "is_cursor_can_hover_over")) {
    return true;
  }
  if (is_cursor_can_hover_over_x2_click() && (what == "is_cursor_can_hover_over_x2_click")) {
    return true;
  }
  if (is_cursor_path_hazard_for_player() && (what == "is_cursor_path_hazard_for_player")) {
    return true;
  }
  if (is_combustible() && (what == "is_combustible")) {
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
  if (is_debuff() && (what == "is_debuff")) {
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
  if (is_destroyed_on_hit_or_miss() && (what == "is_defeated _on_you_are_hit_but_still_alive_or_miss")) {
    return true;
  }
  if (is_destroyed_on_hitting() && (what == "is_defeated _on_you_are_hit_but_still_aliveting")) {
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
  if (is_wet_grass() && (what == "is_wet_grass")) {
    return true;
  }
  if (is_enchantable() && (what == "is_enchantable")) {
    return true;
  }
  if (is_enchantstone() && (what == "is_enchantstone")) {
    return true;
  }
  if (is_engulfer() && (what == "is_engulfer")) {
    return true;
  }
  if (is_ethereal_mob() && (what == "is_ethereal_mob")) {
    return true;
  }
  if (is_ethereal() && (what == "is_ethereal")) {
    return true;
  }
  if (is_explosion() && (what == "is_explosion")) {
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
  if (is_gfx_anim_synced_with_owner() && (what == "is_gfx_anim_synced_with_owner")) {
    return true;
  }
  if (is_glass() && (what == "is_glass")) {
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
  if (hunger_is_insatiable() && (what == "hunger_is_insatiable")) {
    return true;
  }
  if (is_toughness_very_hard() && (what == "is_toughness_very_hard")) {
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
  if (is_item_eater() && (what == "is_item_eater")) {
    return true;
  }
  if (is_item_magical_eater() && (what == "is_item_magical_eater")) {
    return true;
  }
  if (is_item_magical() && (what == "is_item_magical")) {
    return true;
  }
  if (is_item_organic() && (what == "is_item_organic")) {
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
  if (is_key() && (what == "is_key")) {
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
  if (is_light_blocker_for_monst() && (what == "is_light_blocker_for_monst")) {
    return true;
  }
  if (is_gas_blocker() && (what == "is_gas_blocker")) {
    return true;
  }
  if (noise_blocker() && (what == "noise_blocker")) {
    return true;
  }
  if (is_living() && (what == "is_living")) {
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
  if (is_metal() && (what == "is_metal")) {
    return true;
  }
  if (is_mob() && (what == "is_mob")) {
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
  if (is_msg() && (what == "is_msg")) {
    return true;
  }
  if (is_necrotic_danger_level() && (what == "is_necrotic_danger_level")) {
    return true;
  }
  if (is_no_tile() && (what == "is_no_tile")) {
    return true;
  }
  if (is_obs_destructable() && (what == "is_obs_destructable")) {
    return true;
  }
  if (is_obs_wall_or_door() && (what == "is_obs_wall_or_door")) {
    return true;
  }
  if (is_openable() && (what == "is_openable")) {
    return true;
  }
  if (is_organic() && (what == "is_organic")) {
    return true;
  }
  if (is_player() && (what == "is_player")) {
    return true;
  }
  if (is_poisonous_danger_level() && (what == "is_poisonous_danger_level")) {
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
  if (is_ring() && (what == "is_ring")) {
    return true;
  }
  if (is_ripple() && (what == "is_ripple")) {
    return true;
  }
  if (is_rock() && (what == "is_rock")) {
    return true;
  }
  if (is_rusty() && (what == "is_rusty")) {
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
  if (is_toughness_soft() && (what == "is_toughness_soft")) {
    return true;
  }
  if (is_spawner() && (what == "is_spawner")) {
    return true;
  }
  if (is_spiderweb() && (what == "is_spiderweb")) {
    return true;
  }
  if (is_sticky() && (what == "is_sticky")) {
    return true;
  }
  if (is_stone() && (what == "is_stone")) {
    return true;
  }
  if (is_sword() && (what == "is_sword")) {
    return true;
  }
  if (is_target_select() && (what == "is_target_select")) {
    return true;
  }
  if (is_throwable() && (what == "is_throwable")) {
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
  if (is_treasure_chest() && (what == "is_treasure_chest")) {
    return true;
  }
  if (is_treasure_eater() && (what == "is_treasure_eater")) {
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
  if (is_used_when_thrown() && (what == "is_used_when_thrown")) {
    return true;
  }
  if (is_very_is_combustible() && (what == "is_very_is_combustible")) {
    return true;
  }
  if (is_wall_dungeon() && (what == "is_wall_dungeon")) {
    return true;
  }
  if (is_wall() && (what == "is_wall")) {
    return true;
  }
  if (is_wand_or_staff() && (what == "is_wand_or_staff")) {
    return true;
  }
  if (is_able_to_use_rings() && (what == "is_able_to_use_rings")) {
    return true;
  }
  if (is_weapon() && (what == "is_weapon")) {
    return true;
  }
  if (is_wooden() && (what == "is_wooden")) {
    return true;
  }
  if (minion_limit() && (what == "minion_limit")) {
    return true;
  }
  if (range_max() && (what == "range_max")) {
    return true;
  }
  if (is_able_to_jump_escape() && (what == "is_able_to_jump_escape")) {
    return true;
  }
  if (is_able_to_follow() && (what == "is_able_to_follow")) {
    return true;
  }
  if (is_able_to_use_weapons() && (what == "is_able_to_use_weapons")) {
    return true;
  }
  if (is_corpse_with_bones() && (what == "is_corpse_with_bones")) {
    return true;
  }
  if (is_pink_blooded() && (what == "is_pink_blooded")) {
    return true;
  }
  if (is_pink_splatter() && (what == "is_pink_splatter")) {
    return true;
  }
  if (is_green_splatter() && (what == "is_green_splatter")) {
    return true;
  }
  if (unused_flag1() && (what == "unused_flag1")) {
    return true;
  }
  if (unused_flag2() && (what == "unused_flag2")) {
    return true;
  }
  if (unused_flag3() && (what == "unused_flag3")) {
    return true;
  }
  if (unused_flag4() && (what == "unused_flag4")) {
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
  if (unused_flag49() && (what == "unused_flag49")) {
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
  if (unused_flag53() && (what == "unused_flag53")) {
    return true;
  }
  if (unused_flag54() && (what == "unused_flag54")) {
    return true;
  }
  if (unused_flag55() && (what == "unused_flag55")) {
    return true;
  }
  if (unused_flag56() && (what == "unused_flag56")) {
    return true;
  }
  if (unused_flag57() && (what == "unused_flag57")) {
    return true;
  }
  if (unused_flag58() && (what == "unused_flag58")) {
    return true;
  }
  if (unused_flag59() && (what == "unused_flag59")) {
    return true;
  }
  if (unused_flag60() && (what == "unused_flag60")) {
    return true;
  }
  if (unused_flag61() && (what == "unused_flag61")) {
    return true;
  }
  if (unused_flag62() && (what == "unused_flag62")) {
    return true;
  }
  if (unused_flag63() && (what == "unused_flag63")) {
    return true;
  }
  if (unused_flag64() && (what == "unused_flag64")) {
    return true;
  }
  if (unused_flag65() && (what == "unused_flag65")) {
    return true;
  }
  if (unused_flag66() && (what == "unused_flag66")) {
    return true;
  }
  if (unused_flag67() && (what == "unused_flag67")) {
    return true;
  }
  if (unused_flag68() && (what == "unused_flag68")) {
    return true;
  }
  if (unused_flag69() && (what == "unused_flag69")) {
    return true;
  }
  if (unused_flag70() && (what == "unused_flag70")) {
    return true;
  }
  if (unused_flag71() && (what == "unused_flag71")) {
    return true;
  }
  if (unused_flag72() && (what == "unused_flag72")) {
    return true;
  }
  if (unused_flag73() && (what == "unused_flag73")) {
    return true;
  }
  if (unused_flag74() && (what == "unused_flag74")) {
    return true;
  }
  if (unused_flag75() && (what == "unused_flag75")) {
    return true;
  }
  if (unused_flag76() && (what == "unused_flag76")) {
    return true;
  }
  if (unused_flag77() && (what == "unused_flag77")) {
    return true;
  }
  if (unused_flag78() && (what == "unused_flag78")) {
    return true;
  }
  if (unused_flag79() && (what == "unused_flag79")) {
    return true;
  }
  if (unused_flag80() && (what == "unused_flag80")) {
    return true;
  }
  if (unused_flag81() && (what == "unused_flag81")) {
    return true;
  }
  if (unused_flag82() && (what == "unused_flag82")) {
    return true;
  }
  if (unused_flag83() && (what == "unused_flag83")) {
    return true;
  }
  if (unused_flag84() && (what == "unused_flag84")) {
    return true;
  }
  if (unused_flag85() && (what == "unused_flag85")) {
    return true;
  }
  if (unused_flag86() && (what == "unused_flag86")) {
    return true;
  }
  if (unused_flag87() && (what == "unused_flag87")) {
    return true;
  }
  if (unused_flag88() && (what == "unused_flag88")) {
    return true;
  }
  if (unused_flag89() && (what == "unused_flag89")) {
    return true;
  }
  if (unused_flag90() && (what == "unused_flag90")) {
    return true;
  }
  if (unused_flag91() && (what == "unused_flag91")) {
    return true;
  }
  if (unused_flag92() && (what == "unused_flag92")) {
    return true;
  }
  if (unused_flag93() && (what == "unused_flag93")) {
    return true;
  }
  if (unused_flag94() && (what == "unused_flag94")) {
    return true;
  }
  if (unused_flag95() && (what == "unused_flag95")) {
    return true;
  }
  if (unused_flag96() && (what == "unused_flag96")) {
    return true;
  }
  if (unused_flag97() && (what == "unused_flag97")) {
    return true;
  }
  if (unused_flag98() && (what == "unused_flag98")) {
    return true;
  }
  if (unused_flag99() && (what == "unused_flag99")) {
    return true;
  }
  if (unused_flag100() && (what == "unused_flag100")) {
    return true;
  }
  if (unused_flag101() && (what == "unused_flag101")) {
    return true;
  }
  if (unused_flag102() && (what == "unused_flag102")) {
    return true;
  }
  if (unused_flag103() && (what == "unused_flag103")) {
    return true;
  }
  if (unused_flag104() && (what == "unused_flag104")) {
    return true;
  }
  if (unused_flag105() && (what == "unused_flag105")) {
    return true;
  }
  if (unused_flag106() && (what == "unused_flag106")) {
    return true;
  }
  if (unused_flag107() && (what == "unused_flag107")) {
    return true;
  }
  if (unused_flag108() && (what == "unused_flag108")) {
    return true;
  }
  if (is_key_special() && (what == "is_key_special")) {
    return true;
  }
  if (is_crystal() && (what == "is_crystal")) {
    return true;
  }
  if (noise_on_moving() && (what == "noise_on_moving")) {
    return true;
  }
  if (is_tireless() && (what == "is_tireless")) {
    return true;
  }
  if (shove_strength() && (what == "shove_strength")) {
    return true;
  }
  if (gfx_wobbles_when_hit() && (what == "gfx_wobbles_when_hit")) {
    return true;
  }
  if (is_snake() && (what == "is_snake")) {
    return true;
  }
  if (is_item_targetted() && (what == "is_item_targetted")) {
    return true;
  }
  if (noise_additional_on_teleporting() && (what == "noise_additional_on_teleporting")) {
    return true;
  }
  if (is_able_to_jump_attack_chance_d1000() && (what == "is_able_to_jump_attack_chance_d1000")) {
    return true;
  }
  if (is_able_to_teleport_attack_chance_d1000() && (what == "is_able_to_teleport_attack_chance_d1000")) {
    return true;
  }
  if (is_able_to_teleport_attack() && (what == "is_able_to_teleport_attack")) {
    return true;
  }
  if (is_able_to_teleport_without_tiring() && (what == "is_able_to_teleport_without_tiring")) {
    return true;
  }
  if (is_able_to_teleport_escape() && (what == "is_able_to_teleport_escape")) {
    return true;
  }
  if (unused_flag123() && (what == "unused_flag123")) {
    return true;
  }
  if (is_pack() && (what == "is_pack")) {
    return true;
  }
  if (is_pillar() && (what == "is_pillar")) {
    return true;
  }
  if (is_able_to_walk_through_walls() && (what == "is_able_to_walk_through_walls")) {
    return true;
  }
  if (collision_hit_two_tiles_ahead() && (what == "collision_hit_two_tiles_ahead")) {
    return true;
  }
  if (is_flat() && (what == "is_flat")) {
    return true;
  }
  if (is_target_radial() && (what == "is_target_radial")) {
    return true;
  }
  if (is_staff() && (what == "is_staff")) {
    return true;
  }
  if (collision_hit_adj() && (what == "collision_hit_adj")) {
    return true;
  }
  if (collision_hit_180() && (what == "collision_hit_180")) {
    return true;
  }
  if (collision_hit_360() && (what == "collision_hit_360")) {
    return true;
  }
  if (is_dead_on_falling() && (what == "is_dead_on_falling")) {
    return true;
  }
  if (is_temperature_sensitive() && (what == "is_temperature_sensitive")) {
    return true;
  }
  if (damage_received_doubled_from_cold() && (what == "damage_received_doubled_from_cold")) {
    return true;
  }
  if (is_cold() && (what == "is_cold")) {
    return true;
  }
  if (is_temperature_change_sensitive() && (what == "is_temperature_change_sensitive")) {
    return true;
  }
  if (temperature() && (what == "temperature")) {
    return true;
  }
  if (is_very_heavy() && (what == "is_very_heavy")) {
    return true;
  }
  if (gfx_health_bar_shown_when_awake_only() && (what == "gfx_health_bar_shown_when_awake_only")) {
    return true;
  }
  if (gfx_show_asleep() && (what == "gfx_show_asleep")) {
    return true;
  }
  if (noise_additional_on_jump_end() && (what == "noise_additional_on_jump_end")) {
    return true;
  }
  if (noise_on_born() && (what == "noise_on_born")) {
    return true;
  }
  if (noise_on_open() && (what == "noise_on_open")) {
    return true;
  }
  if (noise_on_you_are_hit_and_now_dead() && (what == "noise_on_you_are_hit_and_now_dead")) {
    return true;
  }
  if (noise_on_you_are_hit_but_still_alive() && (what == "noise_on_you_are_hit_but_still_alive")) {
    return true;
  }
  if (noise_decibels_hearing() && (what == "noise_decibels_hearing")) {
    return true;
  }
  if (noise_blocker() && (what == "noise_blocker")) {
    return true;
  }
  if (is_immune_to_cold() && (what == "is_immune_to_cold")) {
    return true;
  }
  if (is_breather() && (what == "is_breather")) {
    return true;
  }
  if (noise_on_dropping() && (what == "noise_on_dropping")) {
    return true;
  }
  if (is_asleep_initially() && (what == "is_asleep_initially")) {
    return true;
  }
  if (is_able_to_sleep() && (what == "is_able_to_sleep")) {
    return true;
  }
  if (is_obstacle_when_dead() && (what == "is_obstacle_when_dead")) {
    return true;
  }
  if (is_gas_blocker() && (what == "is_gas_blocker")) {
    return true;
  }
  if (is_light_blocker_for_monst() && (what == "is_light_blocker_for_monst")) {
    return true;
  }
  if (noise_blocker() && (what == "noise_blocker")) {
    return true;
  }
  if (is_pink_blood_eater() && (what == "is_pink_blood_eater")) {
    return true;
  }
  if (is_green_blood() && (what == "is_green_blood")) {
    return true;
  }
  if (is_biome_swamp() && (what == "is_biome_swamp")) {
    return true;
  }
  if (is_biome_dungeon() && (what == "is_biome_dungeon")) {
    return true;
  }
  if (is_treasure() && (what == "is_treasure")) {
    return true;
  }
  if (is_monst_class_e() && (what == "is_monst_class_e")) {
    return true;
  }
  if (is_green_blood_eater() && (what == "is_green_blood_eater")) {
    return true;
  }
  if (is_mob_challenge_class_b() && (what == "is_mob_challenge_class_b")) {
    return true;
  }
  if (is_mob_challenge_class_a() && (what == "is_mob_challenge_class_a")) {
    return true;
  }
  if (is_monst_class_d() && (what == "is_monst_class_d")) {
    return true;
  }
  if (is_monst_class_c() && (what == "is_monst_class_c")) {
    return true;
  }
  if (is_monst_class_b() && (what == "is_monst_class_b")) {
    return true;
  }
  if (is_monst_class_a() && (what == "is_monst_class_a")) {
    return true;
  }
  if (stat_att_penalty_when_in_deep_water() && (what == "stat_att_penalty_when_in_deep_water")) {
    return true;
  }
  if (stat_att_penalty_when_in_shallow_water() && (what == "stat_att_penalty_when_in_shallow_water")) {
    return true;
  }
  if (stat_att_penalty_when_idle_max() && (what == "stat_att_penalty_when_idle_max")) {
    return true;
  }
  if (stat_att_penalty_when_idle() && (what == "stat_att_penalty_when_idle")) {
    return true;
  }
  if (stat_att_penalty_when_stuck() && (what == "stat_att_penalty_when_stuck")) {
    return true;
  }
  if (stat_att_penalty_when_stuck_max() && (what == "stat_att_penalty_when_stuck_max")) {
    return true;
  }
  if (stat_def_penalty_when_stuck_max() && (what == "stat_def_penalty_when_stuck_max")) {
    return true;
  }
  if (stat_def_penalty_when_idle_max() && (what == "stat_def_penalty_when_idle_max")) {
    return true;
  }
  if (stat_def_penalty_when_in_deep_water() && (what == "stat_def_penalty_when_in_deep_water")) {
    return true;
  }
  if (stat_def_penalty_when_in_shallow_water() && (what == "stat_def_penalty_when_in_shallow_water")) {
    return true;
  }
  if (stat_def_penalty_when_stuck() && (what == "stat_def_penalty_when_stuck")) {
    return true;
  }
  if (stat_def_penalty_when_idle() && (what == "stat_def_penalty_when_idle")) {
    return true;
  }
  if (is_able_to_move_diagonally() && (what == "is_able_to_move_diagonally")) {
    return true;
  }
  if (is_meltable() && (what == "is_meltable")) {
    return true;
  }
  if (is_amulet() && (what == "is_amulet")) {
    return true;
  }
  if (is_able_to_use_amulet() && (what == "is_able_to_use_amulet")) {
    return true;
  }
  if (is_able_to_use_helmet() && (what == "is_able_to_use_helmet")) {
    return true;
  }
  if (is_able_to_use_boots() && (what == "is_able_to_use_boots")) {
    return true;
  }
  if (is_able_to_use_cloak() && (what == "is_able_to_use_cloak")) {
    return true;
  }
  if (is_able_to_use_shield() && (what == "is_able_to_use_shield")) {
    return true;
  }
  if (is_able_to_use_gauntlet() && (what == "is_able_to_use_gauntlet")) {
    return true;
  }
  if (is_able_to_use_helmet() && (what == "is_able_to_use_helmet")) {
    return true;
  }
  if (is_helmet() && (what == "is_helmet")) {
    return true;
  }
  if (is_boots() && (what == "is_boots")) {
    return true;
  }
  if (is_shield() && (what == "is_shield")) {
    return true;
  }
  if (is_cloak() && (what == "is_cloak")) {
    return true;
  }
  if (is_gauntlet() && (what == "is_gauntlet")) {
    return true;
  }
  if (is_toughness_hard() && (what == "is_toughness_hard")) {
    return true;
  }
  if (is_red_blooded() && (what == "is_red_blooded")) {
    return true;
  }
  if (is_green_blooded() && (what == "is_green_blooded")) {
    return true;
  }
  if (is_able_to_jump_without_tiring() && (what == "is_able_to_jump_without_tiring")) {
    return true;
  }
  if (is_spider() && (what == "is_spider")) {
    return true;
  }
  if (is_able_to_jump_attack() && (what == "is_able_to_jump_attack")) {
    return true;
  }
  if (is_able_to_jump_onto() && (what == "is_able_to_jump_onto")) {
    return true;
  }
  if (is_crushable() && (what == "is_crushable")) {
    return true;
  }
  if (is_able_to_use_armor() && (what == "is_able_to_use_armor")) {
    return true;
  }
  if (is_heavy() && (what == "is_heavy")) {
    return true;
  }
  if (is_slippery() && (what == "is_slippery")) {
    return true;
  }
  if (is_armor() && (what == "is_armor")) {
    return true;
  }
  if (is_flying() && (what == "is_flying")) {
    return true;
  }
  if (is_map_beast() && (what == "is_map_beast")) {
    return true;
  }
  if (is_able_to_use_wands_or_staffs() && (what == "is_able_to_use_wands_or_staffs")) {
    return true;
  }
  if (is_aquatic() && (what == "is_aquatic")) {
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
  if (what == "ai_detect_secret_doors") {
    return &Thing::ai_detect_secret_doors;
  }
  if (what == "ai_resent_count") {
    return &Thing::ai_resent_count;
  }
  if (what == "ai_wanderer") {
    return &Thing::ai_wanderer;
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
  if (what == "attack_undead") {
    return &Thing::attack_undead;
  }
  if (what == "blast_max_radius") {
    return &Thing::blast_max_radius;
  }
  if (what == "blast_min_radius") {
    return &Thing::blast_min_radius;
  }
  if (what == "collision_hit_180") {
    return &Thing::collision_hit_180;
  }
  if (what == "collision_hit_360") {
    return &Thing::collision_hit_360;
  }
  if (what == "collision_hit_adj") {
    return &Thing::collision_hit_adj;
  }
  if (what == "collision_hit_two_tiles_ahead") {
    return &Thing::collision_hit_two_tiles_ahead;
  }
  if (what == "damage_received_doubled_from_cold") {
    return &Thing::damage_received_doubled_from_cold;
  }
  if (what == "enchant_level") {
    return &Thing::enchant_level;
  }
  if (what == "enchant_max") {
    return &Thing::enchant_max;
  }
  if (what == "environ_avoids_acid") {
    return &Thing::environ_avoids_acid;
  }
  if (what == "environ_avoids_cold") {
    return &Thing::environ_avoids_cold;
  }
  if (what == "environ_avoids_fire") {
    return &Thing::environ_avoids_fire;
  }
  if (what == "environ_avoids_necrosis") {
    return &Thing::environ_avoids_necrosis;
  }
  if (what == "environ_avoids_poison") {
    return &Thing::environ_avoids_poison;
  }
  if (what == "environ_avoids_water") {
    return &Thing::environ_avoids_water;
  }
  if (what == "gfx_flickers") {
    return &Thing::gfx_flickers;
  }
  if (what == "gfx_health_bar_shown_when_awake_only") {
    return &Thing::gfx_health_bar_shown_when_awake_only;
  }
  if (what == "gfx_long_shadow_caster") {
    return &Thing::gfx_long_shadow_caster;
  }
  if (what == "gfx_show_asleep") {
    return &Thing::gfx_show_asleep;
  }
  if (what == "gfx_solid_shadow") {
    return &Thing::gfx_solid_shadow;
  }
  if (what == "gfx_very_short_shadow_caster") {
    return &Thing::gfx_very_short_shadow_caster;
  }
  if (what == "hunger_is_insatiable") {
    return &Thing::hunger_is_insatiable;
  }
  if (what == "is_able_to_attack_mobs") {
    return &Thing::is_able_to_attack_mobs;
  }
  if (what == "is_able_to_break_down_doors") {
    return &Thing::is_able_to_break_down_doors;
  }
  if (what == "is_able_to_break_out_of_webs") {
    return &Thing::is_able_to_break_out_of_webs;
  }
  if (what == "is_able_to_change_levels") {
    return &Thing::is_able_to_change_levels;
  }
  if (what == "is_able_to_collect_keys") {
    return &Thing::is_able_to_collect_keys;
  }
  if (what == "is_able_to_enchant_items") {
    return &Thing::is_able_to_enchant_items;
  }
  if (what == "is_able_to_fall") {
    return &Thing::is_able_to_fall;
  }
  if (what == "is_able_to_fire_at") {
    return &Thing::is_able_to_fire_at;
  }
  if (what == "is_able_to_follow") {
    return &Thing::is_able_to_follow;
  }
  if (what == "is_able_to_jump_attack") {
    return &Thing::is_able_to_jump_attack;
  }
  if (what == "is_able_to_jump_escape") {
    return &Thing::is_able_to_jump_escape;
  }
  if (what == "is_able_to_jump_onto") {
    return &Thing::is_able_to_jump_onto;
  }
  if (what == "is_able_to_jump") {
    return &Thing::is_able_to_jump;
  }
  if (what == "is_able_to_jump_without_tiring") {
    return &Thing::is_able_to_jump_without_tiring;
  }
  if (what == "is_able_to_learn_skills") {
    return &Thing::is_able_to_learn_skills;
  }
  if (what == "is_able_to_move_diagonally") {
    return &Thing::is_able_to_move_diagonally;
  }
  if (what == "is_able_to_open_doors") {
    return &Thing::is_able_to_open_doors;
  }
  if (what == "is_able_to_see_in_the_dark") {
    return &Thing::is_able_to_see_in_the_dark;
  }
  if (what == "is_able_to_see_through_doors") {
    return &Thing::is_able_to_see_through_doors;
  }
  if (what == "is_able_to_shove") {
    return &Thing::is_able_to_shove;
  }
  if (what == "is_able_to_sleep") {
    return &Thing::is_able_to_sleep;
  }
  if (what == "is_able_to_tire") {
    return &Thing::is_able_to_tire;
  }
  if (what == "is_able_to_use_amulet") {
    return &Thing::is_able_to_use_amulet;
  }
  if (what == "is_able_to_use_armor") {
    return &Thing::is_able_to_use_armor;
  }
  if (what == "is_able_to_use_boots") {
    return &Thing::is_able_to_use_boots;
  }
  if (what == "is_able_to_use_cloak") {
    return &Thing::is_able_to_use_cloak;
  }
  if (what == "is_able_to_use_gauntlet") {
    return &Thing::is_able_to_use_gauntlet;
  }
  if (what == "is_able_to_use_helmet") {
    return &Thing::is_able_to_use_helmet;
  }
  if (what == "is_able_to_use_rings") {
    return &Thing::is_able_to_use_rings;
  }
  if (what == "is_able_to_use_shield") {
    return &Thing::is_able_to_use_shield;
  }
  if (what == "is_able_to_use_wands_or_staffs") {
    return &Thing::is_able_to_use_wands_or_staffs;
  }
  if (what == "is_able_to_use_weapons") {
    return &Thing::is_able_to_use_weapons;
  }
  if (what == "is_able_to_walk_through_walls") {
    return &Thing::is_able_to_walk_through_walls;
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
  if (what == "is_amulet") {
    return &Thing::is_amulet;
  }
  if (what == "is_aquatic") {
    return &Thing::is_aquatic;
  }
  if (what == "is_armor") {
    return &Thing::is_armor;
  }
  if (what == "is_ascend_dungeon") {
    return &Thing::is_ascend_dungeon;
  }
  if (what == "is_ascend_sewer") {
    return &Thing::is_ascend_sewer;
  }
  if (what == "is_asleep_initially") {
    return &Thing::is_asleep_initially;
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
  if (what == "is_auto_equipped") {
    return &Thing::is_auto_equipped;
  }
  if (what == "is_auto_throw") {
    return &Thing::is_auto_throw;
  }
  if (what == "is_auto_use") {
    return &Thing::is_auto_use;
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
  if (what == "is_biome_dungeon") {
    return &Thing::is_biome_dungeon;
  }
  if (what == "is_biome_swamp") {
    return &Thing::is_biome_swamp;
  }
  if (what == "is_bleeder") {
    return &Thing::is_bleeder;
  }
  if (what == "is_bones") {
    return &Thing::is_bones;
  }
  if (what == "is_corpse_with_bones") {
    return &Thing::is_corpse_with_bones;
  }
  if (what == "is_boots") {
    return &Thing::is_boots;
  }
  if (what == "is_brazier") {
    return &Thing::is_brazier;
  }
  if (what == "is_breather") {
    return &Thing::is_breather;
  }
  if (what == "is_bridge") {
    return &Thing::is_bridge;
  }
  if (what == "is_buff") {
    return &Thing::is_buff;
  }
  if (what == "is_burnable") {
    return &Thing::is_burnable;
  }
  if (what == "is_chasm") {
    return &Thing::is_chasm;
  }
  if (what == "is_cloak") {
    return &Thing::is_cloak;
  }
  if (what == "is_cold") {
    return &Thing::is_cold;
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
  if (what == "is_crushable") {
    return &Thing::is_crushable;
  }
  if (what == "is_cursor_can_hover_over") {
    return &Thing::is_cursor_can_hover_over;
  }
  if (what == "is_cursor_can_hover_over_x2_click") {
    return &Thing::is_cursor_can_hover_over_x2_click;
  }
  if (what == "is_cursor_path_hazard_for_player") {
    return &Thing::is_cursor_path_hazard_for_player;
  }
  if (what == "is_combustible") {
    return &Thing::is_combustible;
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
  if (what == "is_dead_on_falling") {
    return &Thing::is_dead_on_falling;
  }
  if (what == "is_dead_on_shove") {
    return &Thing::is_dead_on_shove;
  }
  if (what == "is_debuff") {
    return &Thing::is_debuff;
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
  if (what == "is_engulfer") {
    return &Thing::is_engulfer;
  }
  if (what == "is_ethereal_mob") {
    return &Thing::is_ethereal_mob;
  }
  if (what == "is_ethereal") {
    return &Thing::is_ethereal;
  }
  if (what == "is_exit_finder") {
    return &Thing::is_exit_finder;
  }
  if (what == "is_explorer") {
    return &Thing::is_explorer;
  }
  if (what == "is_explosion") {
    return &Thing::is_explosion;
  }
  if (what == "is_fearless") {
    return &Thing::is_fearless;
  }
  if (what == "is_fire") {
    return &Thing::is_fire;
  }
  if (what == "is_flat") {
    return &Thing::is_flat;
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
  if (what == "is_flying") {
    return &Thing::is_flying;
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
  if (what == "is_gas_blocker") {
    return &Thing::is_gas_blocker;
  }
  if (what == "is_gauntlet") {
    return &Thing::is_gauntlet;
  }
  if (what == "is_gfx_anim_synced_with_owner") {
    return &Thing::is_gfx_anim_synced_with_owner;
  }
  if (what == "is_glass") {
    return &Thing::is_glass;
  }
  if (what == "is_gold") {
    return &Thing::is_gold;
  }
  if (what == "is_green_blood_eater") {
    return &Thing::is_green_blood_eater;
  }
  if (what == "is_green_blooded") {
    return &Thing::is_green_blooded;
  }
  if (what == "is_green_blood") {
    return &Thing::is_green_blood;
  }
  if (what == "is_green_splatter") {
    return &Thing::is_green_splatter;
  }
  if (what == "is_hazard") {
    return &Thing::is_hazard;
  }
  if (what == "is_health_booster") {
    return &Thing::is_health_booster;
  }
  if (what == "is_heavy") {
    return &Thing::is_heavy;
  }
  if (what == "is_helmet") {
    return &Thing::is_helmet;
  }
  if (what == "is_hittable") {
    return &Thing::is_hittable;
  }
  if (what == "is_humanoid") {
    return &Thing::is_humanoid;
  }
  if (what == "is_immune_to_acid") {
    return &Thing::is_immune_to_acid;
  }
  if (what == "is_immune_to_cold") {
    return &Thing::is_immune_to_cold;
  }
  if (what == "is_immune_to_fire") {
    return &Thing::is_immune_to_fire;
  }
  if (what == "is_immune_to_necrosis") {
    return &Thing::is_immune_to_necrosis;
  }
  if (what == "is_immune_to_poison") {
    return &Thing::is_immune_to_poison;
  }
  if (what == "is_immune_to_spiderwebs") {
    return &Thing::is_immune_to_spiderwebs;
  }
  if (what == "is_immune_to_water") {
    return &Thing::is_immune_to_water;
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
  if (what == "is_item_magical_eater") {
    return &Thing::is_item_magical_eater;
  }
  if (what == "is_item_magical") {
    return &Thing::is_item_magical;
  }
  if (what == "is_item_organic") {
    return &Thing::is_item_organic;
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
  if (what == "is_key") {
    return &Thing::is_key;
  }
  if (what == "is_laser") {
    return &Thing::is_laser;
  }
  if (what == "is_lava") {
    return &Thing::is_lava;
  }
  if (what == "is_light_blocker_for_monst") {
    return &Thing::is_light_blocker_for_monst;
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
  if (what == "is_map_beast") {
    return &Thing::is_map_beast;
  }
  if (what == "is_meat_eater") {
    return &Thing::is_meat_eater;
  }
  if (what == "is_meat") {
    return &Thing::is_meat;
  }
  if (what == "is_meltable") {
    return &Thing::is_meltable;
  }
  if (what == "is_metal") {
    return &Thing::is_metal;
  }
  if (what == "is_minion") {
    return &Thing::is_minion;
  }
  if (what == "is_mob_challenge_class_a") {
    return &Thing::is_mob_challenge_class_a;
  }
  if (what == "is_mob_challenge_class_b") {
    return &Thing::is_mob_challenge_class_b;
  }
  if (what == "is_mob") {
    return &Thing::is_mob;
  }
  if (what == "is_monst_class_a") {
    return &Thing::is_monst_class_a;
  }
  if (what == "is_monst_class_b") {
    return &Thing::is_monst_class_b;
  }
  if (what == "is_monst_class_c") {
    return &Thing::is_monst_class_c;
  }
  if (what == "is_monst_class_d") {
    return &Thing::is_monst_class_d;
  }
  if (what == "is_monst_class_e") {
    return &Thing::is_monst_class_e;
  }
  if (what == "is_monst") {
    return &Thing::is_monst;
  }
  if (what == "is_moveable") {
    return &Thing::is_moveable;
  }
  if (what == "is_msg") {
    return &Thing::is_msg;
  }
  if (what == "is_necrotic_danger_level") {
    return &Thing::is_necrotic_danger_level;
  }
  if (what == "is_no_tile") {
    return &Thing::is_no_tile;
  }
  if (what == "is_obs_destructable") {
    return &Thing::is_obs_destructable;
  }
  if (what == "is_obstacle_when_dead") {
    return &Thing::is_obstacle_when_dead;
  }
  if (what == "is_obs_wall_or_door") {
    return &Thing::is_obs_wall_or_door;
  }
  if (what == "is_openable") {
    return &Thing::is_openable;
  }
  if (what == "is_organic") {
    return &Thing::is_organic;
  }
  if (what == "is_pink_blood_eater") {
    return &Thing::is_pink_blood_eater;
  }
  if (what == "is_pink_blooded") {
    return &Thing::is_pink_blooded;
  }
  if (what == "is_pink_splatter") {
    return &Thing::is_pink_splatter;
  }
  if (what == "is_player") {
    return &Thing::is_player;
  }
  if (what == "is_poisonous_danger_level") {
    return &Thing::is_poisonous_danger_level;
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
  if (what == "is_red_blood_eater") {
    return &Thing::is_red_blood_eater;
  }
  if (what == "is_red_blooded") {
    return &Thing::is_red_blooded;
  }
  if (what == "is_red_blood") {
    return &Thing::is_red_blood;
  }
  if (what == "is_red_splatter") {
    return &Thing::is_red_splatter;
  }
  if (what == "is_removeable_if_out_of_slots") {
    return &Thing::is_removeable_if_out_of_slots;
  }
  if (what == "is_resurrectable") {
    return &Thing::is_resurrectable;
  }
  if (what == "is_ring") {
    return &Thing::is_ring;
  }
  if (what == "is_ripple") {
    return &Thing::is_ripple;
  }
  if (what == "is_rock") {
    return &Thing::is_rock;
  }
  if (what == "is_rusty") {
    return &Thing::is_rusty;
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
  if (what == "is_shield") {
    return &Thing::is_shield;
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
  if (what == "is_slippery") {
    return &Thing::is_slippery;
  }
  if (what == "is_smoke") {
    return &Thing::is_smoke;
  }
  if (what == "is_spawner") {
    return &Thing::is_spawner;
  }
  if (what == "is_spider") {
    return &Thing::is_spider;
  }
  if (what == "is_spiderweb") {
    return &Thing::is_spiderweb;
  }
  if (what == "is_staff") {
    return &Thing::is_staff;
  }
  if (what == "is_sticky") {
    return &Thing::is_sticky;
  }
  if (what == "is_stone") {
    return &Thing::is_stone;
  }
  if (what == "is_sword") {
    return &Thing::is_sword;
  }
  if (what == "is_target_radial") {
    return &Thing::is_target_radial;
  }
  if (what == "is_temperature_change_sensitive") {
    return &Thing::is_temperature_change_sensitive;
  }
  if (what == "is_temperature_sensitive") {
    return &Thing::is_temperature_sensitive;
  }
  if (what == "is_throwable") {
    return &Thing::is_throwable;
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
  if (what == "is_toughness_hard") {
    return &Thing::is_toughness_hard;
  }
  if (what == "is_toughness_soft") {
    return &Thing::is_toughness_soft;
  }
  if (what == "is_toughness_very_hard") {
    return &Thing::is_toughness_very_hard;
  }
  if (what == "is_treasure_chest") {
    return &Thing::is_treasure_chest;
  }
  if (what == "is_treasure_eater") {
    return &Thing::is_treasure_eater;
  }
  if (what == "is_treasure") {
    return &Thing::is_treasure;
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
  if (what == "is_used_when_thrown") {
    return &Thing::is_used_when_thrown;
  }
  if (what == "is_very_is_combustible") {
    return &Thing::is_very_is_combustible;
  }
  if (what == "is_very_heavy") {
    return &Thing::is_very_heavy;
  }
  if (what == "is_wall_dungeon") {
    return &Thing::is_wall_dungeon;
  }
  if (what == "is_wall") {
    return &Thing::is_wall;
  }
  if (what == "is_wand_or_staff") {
    return &Thing::is_wand_or_staff;
  }
  if (what == "is_water") {
    return &Thing::is_water;
  }
  if (what == "is_weapon") {
    return &Thing::is_weapon;
  }
  if (what == "is_wet_grass") {
    return &Thing::is_wet_grass;
  }
  if (what == "is_wooden") {
    return &Thing::is_wooden;
  }
  if (what == "minion_limit") {
    return &Thing::minion_limit;
  }
  if (what == "noise_blocker") {
    return &Thing::noise_blocker;
  }
  if (what == "noise_decibels_hearing") {
    return &Thing::noise_decibels_hearing;
  }
  if (what == "noise_on_born") {
    return &Thing::noise_on_born;
  }
  if (what == "noise_additional_on_jump_end") {
    return &Thing::noise_additional_on_jump_end;
  }
  if (what == "noise_on_dropping") {
    return &Thing::noise_on_dropping;
  }
  if (what == "noise_on_open") {
    return &Thing::noise_on_open;
  }
  if (what == "noise_on_you_are_hit_and_now_dead") {
    return &Thing::noise_on_you_are_hit_and_now_dead;
  }
  if (what == "noise_on_you_are_hit_but_still_alive") {
    return &Thing::noise_on_you_are_hit_but_still_alive;
  }
  if (what == "range_max") {
    return &Thing::range_max;
  }
  if (what == "stat_att_penalty_when_idle_max") {
    return &Thing::stat_att_penalty_when_idle_max;
  }
  if (what == "stat_att_penalty_when_idle") {
    return &Thing::stat_att_penalty_when_idle;
  }
  if (what == "stat_att_penalty_when_in_deep_water") {
    return &Thing::stat_att_penalty_when_in_deep_water;
  }
  if (what == "stat_att_penalty_when_in_shallow_water") {
    return &Thing::stat_att_penalty_when_in_shallow_water;
  }
  if (what == "stat_att_penalty_when_stuck_max") {
    return &Thing::stat_att_penalty_when_stuck_max;
  }
  if (what == "stat_att_penalty_when_stuck") {
    return &Thing::stat_att_penalty_when_stuck;
  }
  if (what == "stat_def_penalty_when_idle_max") {
    return &Thing::stat_def_penalty_when_idle_max;
  }
  if (what == "stat_def_penalty_when_idle") {
    return &Thing::stat_def_penalty_when_idle;
  }
  if (what == "stat_def_penalty_when_in_deep_water") {
    return &Thing::stat_def_penalty_when_in_deep_water;
  }
  if (what == "stat_def_penalty_when_in_shallow_water") {
    return &Thing::stat_def_penalty_when_in_shallow_water;
  }
  if (what == "stat_def_penalty_when_stuck_max") {
    return &Thing::stat_def_penalty_when_stuck_max;
  }
  if (what == "stat_def_penalty_when_stuck") {
    return &Thing::stat_def_penalty_when_stuck;
  }
  if (what == "temperature") {
    return &Thing::temperature;
  }
  if (what == "unused_flag100") {
    return &Thing::unused_flag100;
  }
  if (what == "unused_flag101") {
    return &Thing::unused_flag101;
  }
  if (what == "unused_flag102") {
    return &Thing::unused_flag102;
  }
  if (what == "unused_flag103") {
    return &Thing::unused_flag103;
  }
  if (what == "unused_flag104") {
    return &Thing::unused_flag104;
  }
  if (what == "unused_flag105") {
    return &Thing::unused_flag105;
  }
  if (what == "unused_flag106") {
    return &Thing::unused_flag106;
  }
  if (what == "unused_flag107") {
    return &Thing::unused_flag107;
  }
  if (what == "unused_flag108") {
    return &Thing::unused_flag108;
  }
  if (what == "is_key_special") {
    return &Thing::is_key_special;
  }
  if (what == "unused_flag10") {
    return &Thing::unused_flag10;
  }
  if (what == "is_crystal") {
    return &Thing::is_crystal;
  }
  if (what == "noise_on_moving") {
    return &Thing::noise_on_moving;
  }
  if (what == "is_tireless") {
    return &Thing::is_tireless;
  }
  if (what == "shove_strength") {
    return &Thing::shove_strength;
  }
  if (what == "gfx_wobbles_when_hit") {
    return &Thing::gfx_wobbles_when_hit;
  }
  if (what == "is_snake") {
    return &Thing::is_snake;
  }
  if (what == "is_item_targetted") {
    return &Thing::is_item_targetted;
  }
  if (what == "noise_additional_on_teleporting") {
    return &Thing::noise_additional_on_teleporting;
  }
  if (what == "is_able_to_jump_attack_chance_d1000") {
    return &Thing::is_able_to_jump_attack_chance_d1000;
  }
  if (what == "is_able_to_teleport_attack_chance_d1000") {
    return &Thing::is_able_to_teleport_attack_chance_d1000;
  }
  if (what == "unused_flag11") {
    return &Thing::unused_flag11;
  }
  if (what == "is_able_to_teleport_attack") {
    return &Thing::is_able_to_teleport_attack;
  }
  if (what == "is_able_to_teleport_without_tiring") {
    return &Thing::is_able_to_teleport_without_tiring;
  }
  if (what == "is_able_to_teleport_escape") {
    return &Thing::is_able_to_teleport_escape;
  }
  if (what == "unused_flag123") {
    return &Thing::unused_flag123;
  }
  if (what == "is_pack") {
    return &Thing::is_pack;
  }
  if (what == "is_pillar") {
    return &Thing::is_pillar;
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
  if (what == "unused_flag49") {
    return &Thing::unused_flag49;
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
  if (what == "unused_flag53") {
    return &Thing::unused_flag53;
  }
  if (what == "unused_flag54") {
    return &Thing::unused_flag54;
  }
  if (what == "unused_flag55") {
    return &Thing::unused_flag55;
  }
  if (what == "unused_flag56") {
    return &Thing::unused_flag56;
  }
  if (what == "unused_flag57") {
    return &Thing::unused_flag57;
  }
  if (what == "unused_flag58") {
    return &Thing::unused_flag58;
  }
  if (what == "unused_flag59") {
    return &Thing::unused_flag59;
  }
  if (what == "unused_flag5") {
    return &Thing::unused_flag5;
  }
  if (what == "unused_flag60") {
    return &Thing::unused_flag60;
  }
  if (what == "unused_flag61") {
    return &Thing::unused_flag61;
  }
  if (what == "unused_flag62") {
    return &Thing::unused_flag62;
  }
  if (what == "unused_flag63") {
    return &Thing::unused_flag63;
  }
  if (what == "unused_flag64") {
    return &Thing::unused_flag64;
  }
  if (what == "unused_flag65") {
    return &Thing::unused_flag65;
  }
  if (what == "unused_flag66") {
    return &Thing::unused_flag66;
  }
  if (what == "unused_flag67") {
    return &Thing::unused_flag67;
  }
  if (what == "unused_flag68") {
    return &Thing::unused_flag68;
  }
  if (what == "unused_flag69") {
    return &Thing::unused_flag69;
  }
  if (what == "unused_flag6") {
    return &Thing::unused_flag6;
  }
  if (what == "unused_flag70") {
    return &Thing::unused_flag70;
  }
  if (what == "unused_flag71") {
    return &Thing::unused_flag71;
  }
  if (what == "unused_flag72") {
    return &Thing::unused_flag72;
  }
  if (what == "unused_flag73") {
    return &Thing::unused_flag73;
  }
  if (what == "unused_flag74") {
    return &Thing::unused_flag74;
  }
  if (what == "unused_flag75") {
    return &Thing::unused_flag75;
  }
  if (what == "unused_flag76") {
    return &Thing::unused_flag76;
  }
  if (what == "unused_flag77") {
    return &Thing::unused_flag77;
  }
  if (what == "unused_flag78") {
    return &Thing::unused_flag78;
  }
  if (what == "unused_flag79") {
    return &Thing::unused_flag79;
  }
  if (what == "unused_flag7") {
    return &Thing::unused_flag7;
  }
  if (what == "unused_flag80") {
    return &Thing::unused_flag80;
  }
  if (what == "unused_flag81") {
    return &Thing::unused_flag81;
  }
  if (what == "unused_flag82") {
    return &Thing::unused_flag82;
  }
  if (what == "unused_flag83") {
    return &Thing::unused_flag83;
  }
  if (what == "unused_flag84") {
    return &Thing::unused_flag84;
  }
  if (what == "unused_flag85") {
    return &Thing::unused_flag85;
  }
  if (what == "unused_flag86") {
    return &Thing::unused_flag86;
  }
  if (what == "unused_flag87") {
    return &Thing::unused_flag87;
  }
  if (what == "unused_flag88") {
    return &Thing::unused_flag88;
  }
  if (what == "unused_flag89") {
    return &Thing::unused_flag89;
  }
  if (what == "unused_flag8") {
    return &Thing::unused_flag8;
  }
  if (what == "unused_flag90") {
    return &Thing::unused_flag90;
  }
  if (what == "unused_flag91") {
    return &Thing::unused_flag91;
  }
  if (what == "unused_flag92") {
    return &Thing::unused_flag92;
  }
  if (what == "unused_flag93") {
    return &Thing::unused_flag93;
  }
  if (what == "unused_flag94") {
    return &Thing::unused_flag94;
  }
  if (what == "unused_flag95") {
    return &Thing::unused_flag95;
  }
  if (what == "unused_flag96") {
    return &Thing::unused_flag96;
  }
  if (what == "unused_flag97") {
    return &Thing::unused_flag97;
  }
  if (what == "unused_flag98") {
    return &Thing::unused_flag98;
  }
  if (what == "unused_flag99") {
    return &Thing::unused_flag99;
  }
  if (what == "unused_flag9") {
    return &Thing::unused_flag9;
  }

  DIE("could not find a matches function for [%s]", what.c_str());
}
