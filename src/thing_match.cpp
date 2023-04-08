//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "slre.hpp"

bool Tp::matches(const std::string &what)
{
  if (strisregexp(what.c_str())) {
    struct slre slre;
    if (slre_compile(&slre, what.c_str())) {
      auto name = text_short_name();
      if (slre_match(&slre, name.c_str(), name.size(), nullptr /* captures */)) {
        return true;
      }
    }
    return false;
  }

  // clang-format off
  // begin sort marker1 {
  if (ai_detect_secret_doors() && (what == "ai_detect_secret_doors")) { return true; }
  if (ai_resent_count() && (what == "ai_resent_count")) { return true; }
  if (ai_wanderer() && (what == "ai_wanderer")) { return true; }
  if (attack_blood() && (what == "attack_blood")) { return true; }
  if (attack_eater() && (what == "attack_eater")) { return true; }
  if (attack_humanoid() && (what == "attack_humanoid")) { return true; }
  if (attack_living() && (what == "attack_living")) { return true; }
  if (attack_meat() && (what == "attack_meat")) { return true; }
  if (attack_no_msg() && (what == "attack_no_msg")) { return true; }
  if (attacks_per_round() && (what == "attacks_per_round")) { return true; }
  if (attack_undead() && (what == "attack_undead")) { return true; }
  if (collision_hit_180() && (what == "collision_hit_180")) { return true; }
  if (collision_hit_360() && (what == "collision_hit_360")) { return true; }
  if (collision_hit_adj() && (what == "collision_hit_adj")) { return true; }
  if (collision_hit_two_tiles_ahead() && (what == "collision_hit_two_tiles_ahead")) { return true; }
  if (consume_per_bite_amount() && (what == "consume_per_bite_amount")) { return true; }
  if (dmg_received_doubled_from_cold() && (what == "dmg_received_doubled_from_cold")) { return true; }
  if (enchant_max() && (what == "enchant_max")) { return true; }
  if (environ_dislikes_acid() && (what == "environ_dislikes_acid")) { return true; }
  if (environ_dislikes_cold() && (what == "environ_dislikes_cold")) { return true; }
  if (environ_dislikes_fire() && (what == "environ_dislikes_fire")) { return true; }
  if (environ_dislikes_necrosis() && (what == "environ_dislikes_necrosis")) { return true; }
  if (environ_dislikes_poison() && (what == "environ_dislikes_poison")) { return true; }
  if (environ_dislikes_water() && (what == "environ_dislikes_water")) { return true; }
  if (environ_hates_acid() && (what == "environ_hates_acid")) { return true; }
  if (environ_hates_cold() && (what == "environ_hates_cold")) { return true; }
  if (environ_hates_fire() && (what == "environ_hates_fire")) { return true; }
  if (environ_hates_necrosis() && (what == "environ_hates_necrosis")) { return true; }
  if (environ_hates_poison() && (what == "environ_hates_poison")) { return true; }
  if (environ_hates_water() && (what == "environ_hates_water")) { return true; }
  if (environ_likes_deep_water() && (what == "environ_likes_deep_water")) { return true; }
  if (environ_likes_lava() && (what == "environ_likes_lava")) { return true; }
  if (environ_likes_shallow_water() && (what == "environ_likes_shallow_water")) { return true; }
  if (gfx_pixelart_show_highlighted() && (what == "gfx_pixelart_show_highlighted")) { return true; }
  if (gfx_pixelart_show_square_outlined() && (what == "gfx_pixelart_show_square_outlined")) { return true; }
  if (hunger_is_insatiable() && (what == "hunger_is_insatiable")) { return true; }
  if (is_able_to_amplify_footsteps() && (what == "is_able_to_amplify_footsteps")) { return true; }
  if (is_able_to_attack_mobs() && (what == "is_able_to_attack_mobs")) { return true; }
  if (is_able_to_attack_owner() && (what == "is_able_to_attack_owner")) { return true; }
  if (is_able_to_be_resurrected() && (what == "is_able_to_be_resurrected")) { return true; }
  if (is_able_to_be_surprised() && (what == "is_able_to_be_surprised")) { return true; }
  if (is_able_to_be_teleported() && (what == "is_able_to_be_teleported")) { return true; }
  if (is_able_to_break_down_doors() && (what == "is_able_to_break_down_doors")) { return true; }
  if (is_able_to_break_out_of_ice() && (what == "is_able_to_break_out_of_ice")) { return true; }
  if (is_able_to_break_out_of_webs() && (what == "is_able_to_break_out_of_webs")) { return true; }
  if (is_able_to_change_levels() && (what == "is_able_to_change_levels")) { return true; }
  if (is_able_to_collect_keys() && (what == "is_able_to_collect_keys")) { return true; }
  if (is_able_to_dampen_footsteps() && (what == "is_able_to_dampen_footsteps")) { return true; }
  if (is_able_to_enchant_items() && (what == "is_able_to_enchant_items")) { return true; }
  if (is_able_to_fall() && (what == "is_able_to_fall")) { return true; }
  if (is_able_to_follow() && (what == "is_able_to_follow")) { return true; }
  if (is_able_to_freeze() && (what == "is_able_to_freeze")) { return true; }
  if (is_able_to_grapple() && (what == "is_able_to_grapple")) { return true; }
  if (is_able_to_jump_attack() && (what == "is_able_to_jump_attack")) { return true; }
  if (is_able_to_jump_escape() && (what == "is_able_to_jump_escape")) { return true; }
  if (is_able_to_jump_onto() && (what == "is_able_to_jump_onto")) { return true; }
  if (is_able_to_jump() && (what == "is_able_to_jump")) { return true; }
  if (is_able_to_jump_without_tiring() && (what == "is_able_to_jump_without_tiring")) { return true; }
  if (is_able_to_learn_skills() && (what == "is_able_to_learn_skills")) { return true; }
  if (is_able_to_live_out_of_water() && (what == "is_able_to_live_out_of_water")) { return true; }
  if (is_able_to_lunge() && (what == "is_able_to_lunge")) { return true; }
  if (is_able_to_melt() && (what == "is_able_to_melt")) { return true; }
  if (is_able_to_move_diagonally() && (what == "is_able_to_move_diagonally")) { return true; }
  if (is_able_to_open_doors() && (what == "is_able_to_open_doors")) { return true; }
  if (is_able_to_regenerate() && (what == "is_able_to_regenerate")) { return true; }
  if (is_able_to_rest() && (what == "is_able_to_rest")) { return true; }
  if (is_able_to_run_away_after_stealing() && (what == "is_able_to_run_away_after_stealing")) { return true; }
  if (is_able_to_see_in_the_dark() && (what == "is_able_to_see_in_the_dark")) { return true; }
  if (is_able_to_see_invisible() && (what == "is_able_to_see_invisible")) { return true; }
  if (is_able_to_see_through_doors() && (what == "is_able_to_see_through_doors")) { return true; }
  if (is_able_to_shoot_at_close_range() && (what == "is_able_to_shoot_at_close_range")) { return true; }
  if (is_able_to_shoot_at() && (what == "is_able_to_shoot_at")) { return true; }
  if (is_able_to_shove() && (what == "is_able_to_shove")) { return true; }
  if (is_able_to_sleep() && (what == "is_able_to_sleep")) { return true; }
  if (is_able_to_spawn_things() && (what == "is_able_to_spawn_things")) { return true; }
  if (is_able_to_swim() && (what == "is_able_to_swim")) { return true; }
  if (is_able_to_teleport_attack() && (what == "is_able_to_teleport_attack")) { return true; }
  if (is_able_to_teleport_escape() && (what == "is_able_to_teleport_escape")) { return true; }
  if (is_able_to_teleport_self() && (what == "is_able_to_teleport_self")) { return true; }
  if (is_able_to_teleport_without_tiring() && (what == "is_able_to_teleport_without_tiring")) { return true; }
  if (is_able_to_tire() && (what == "is_able_to_tire")) { return true; }
  if (is_able_to_use_amulet() && (what == "is_able_to_use_amulet")) { return true; }
  if (is_able_to_use_armor() && (what == "is_able_to_use_armor")) { return true; }
  if (is_able_to_use_boots() && (what == "is_able_to_use_boots")) { return true; }
  if (is_able_to_use_cloak() && (what == "is_able_to_use_cloak")) { return true; }
  if (is_able_to_use_gauntlet() && (what == "is_able_to_use_gauntlet")) { return true; }
  if (is_able_to_use_helmet() && (what == "is_able_to_use_helmet")) { return true; }
  if (is_able_to_use_ranged_weapons() && (what == "is_able_to_use_ranged_weapons")) { return true; }
  if (is_able_to_use_rings() && (what == "is_able_to_use_rings")) { return true; }
  if (is_able_to_use_shield() && (what == "is_able_to_use_shield")) { return true; }
  if (is_able_to_use_staffs() && (what == "is_able_to_use_staffs")) { return true; }
  if (is_able_to_use_weapons() && (what == "is_able_to_use_weapons")) { return true; }
  if (is_able_to_walk_through_walls() && (what == "is_able_to_walk_through_walls")) { return true; }
  if (is_acid() && (what == "is_acid")) { return true; }
  if (is_aerodynamic() && (what == "is_aerodynamic")) { return true; }
  if (is_air_breather() && (what == "is_air_breather")) { return true; }
  if (is_alive_on_end_of_anim() && (what == "is_alive_on_end_of_anim")) { return true; }
  if (is_always_hit() && (what == "is_always_hit")) { return true; }
  if (is_always_submerged_in_water() && (what == "is_always_submerged_in_water")) { return true; }
  if (is_amulet() && (what == "is_amulet")) { return true; }
  if (is_ant() && (what == "is_ant")) { return true; }
  if (is_aquatic() && (what == "is_aquatic")) { return true; }
  if (is_armor() && (what == "is_armor")) { return true; }
  if (is_ascend_dungeon() && (what == "is_ascend_dungeon")) { return true; }
  if (is_ascend_sewer() && (what == "is_ascend_sewer")) { return true; }
  if (is_asleep_initially() && (what == "is_asleep_initially")) { return true; }
  if (is_attackable_by_magic() && (what == "is_attackable_by_magic")) { return true; }
  if (is_attackable_by_monst() && (what == "is_attackable_by_monst")) { return true; }
  if (is_attackable_by_player() && (what == "is_attackable_by_player")) { return true; }
  if (is_auto_collect_item() && (what == "is_auto_collect_item")) { return true; }
  if (is_auto_equipped() && (what == "is_auto_equipped")) { return true; }
  if (is_auto_throw() && (what == "is_auto_throw")) { return true; }
  if (is_auto_use() && (what == "is_auto_use")) { return true; }
  if (is_bag_item_container() && (what == "is_bag_item_container")) { return true; }
  if (is_bag_item_not_stackable() && (what == "is_bag_item_not_stackable")) { return true; }
  if (is_bag_item() && (what == "is_bag_item")) { return true; }
  if (is_bag() && (what == "is_bag")) { return true; }
  if (is_barrel() && (what == "is_barrel")) { return true; }
  if (is_basalt() && (what == "is_basalt")) { return true; }
  if (is_bearowl() && (what == "is_bearowl")) { return true; }
  if (is_bedbug() && (what == "is_bedbug")) { return true; }
  if (is_bee() && (what == "is_bee")) { return true; }
  if (is_biome_dungeon() && (what == "is_biome_dungeon")) { return true; }
  if (is_biome_sewer() && (what == "is_biome_sewer")) { return true; }
  if (is_biome_swamp() && (what == "is_biome_swamp")) { return true; }
  if (is_biome_unused() && (what == "is_biome_unused")) { return true; }
  if (is_bleeder() && (what == "is_bleeder")) { return true; }
  if (is_block_of_ice() && (what == "is_block_of_ice")) { return true; }
  if (is_bones() && (what == "is_bones")) { return true; }
  if (is_boots() && (what == "is_boots")) { return true; }
  if (is_brazier() && (what == "is_brazier")) { return true; }
  if (is_bridge() && (what == "is_bridge")) { return true; }
  if (is_brittle() && (what == "is_brittle")) { return true; }
  if (is_buff() && (what == "is_buff")) { return true; }
  if (is_burnable() && (what == "is_burnable")) { return true; }
  if (is_carnivorous_plant() && (what == "is_carnivorous_plant")) { return true; }
  if (is_cautious() && (what == "is_cautious")) { return true; }
  if (is_centipede() && (what == "is_centipede")) { return true; }
  if (is_chasm() && (what == "is_chasm")) { return true; }
  if (is_cloak() && (what == "is_cloak")) { return true; }
  if (is_cold_elemental() && (what == "is_cold_elemental")) { return true; }
  if (is_cold() && (what == "is_cold")) { return true; }
  if (is_collectable() && (what == "is_collectable")) { return true; }
  if (is_collected_as_gold() && (what == "is_collected_as_gold")) { return true; }
  if (is_collected_as_keys() && (what == "is_collected_as_keys")) { return true; }
  if (is_combustible() && (what == "is_combustible")) { return true; }
  if (is_corpse_with_bones() && (what == "is_corpse_with_bones")) { return true; }
  if (is_corridor() && (what == "is_corridor")) { return true; }
  if (is_cowardly() && (what == "is_cowardly")) { return true; }
  if (is_crab() && (what == "is_crab")) { return true; }
  if (is_critical_to_level() && (what == "is_critical_to_level")) { return true; }
  if (is_crushable() && (what == "is_crushable")) { return true; }
  if (is_crystal() && (what == "is_crystal")) { return true; }
  if (is_cursor_can_hover_over() && (what == "is_cursor_can_hover_over")) { return true; }
  if (is_cursor_can_hover_over_x2_click() && (what == "is_cursor_can_hover_over_x2_click")) { return true; }
  if (is_cursor_path_blocker() && (what == "is_cursor_path_blocker")) { return true; }
  if (is_cursor_path_hazard() && (what == "is_cursor_path_hazard")) { return true; }
  if (is_cursor_path() && (what == "is_cursor_path")) { return true; }
  if (is_cursor() && (what == "is_cursor")) { return true; }
  if (is_dagger() && (what == "is_dagger")) { return true; }
  if (is_daring() && (what == "is_daring")) { return true; }
  if (is_dead_on_end_of_anim() && (what == "is_dead_on_end_of_anim")) { return true; }
  if (is_dead_on_falling() && (what == "is_dead_on_falling")) { return true; }
  if (is_dead_on_shove() && (what == "is_dead_on_shove")) { return true; }
  if (is_death_hornet() && (what == "is_death_hornet")) { return true; }
  if (is_debuff() && (what == "is_debuff")) { return true; }
  if (is_debug_path() && (what == "is_debug_path")) { return true; }
  if (is_debug_type() && (what == "is_debug_type")) { return true; }
  if (is_deep_water() && (what == "is_deep_water")) { return true; }
  if (is_demon() && (what == "is_demon")) { return true; }
  if (is_descend_dungeon() && (what == "is_descend_dungeon")) { return true; }
  if (is_descend_sewer() && (what == "is_descend_sewer")) { return true; }
  if (is_described_when_hovering_over() && (what == "is_described_when_hovering_over")) { return true; }
  if (is_destroyed_on_hit_or_miss() && (what == "is_defeated _on_hit_and_still_alive_or_miss")) { return true; }
  if (is_destroyed_on_hitting() && (what == "is_defeated _on_hit_and_still_aliveting")) { return true; }
  if (is_dirt() && (what == "is_dirt")) { return true; }
  if (is_door() && (what == "is_door")) { return true; }
  if (is_droppable() && (what == "is_droppable")) { return true; }
  if (is_dry_grass_trampled() && (what == "dry_grass_trampled")) { return true; }
  if (is_dry_grass() && (what == "dry_grass")) { return true; }
  if (is_eater_of_amulets() && (what == "is_eater_of_amulets")) { return true; }
  if (is_eater_of_armor() && (what == "is_eater_of_armor")) { return true; }
  if (is_eater_of_blood() && (what == "is_eater_of_blood")) { return true; }
  if (is_eater_of_boots() && (what == "is_eater_of_boots")) { return true; }
  if (is_eater_of_cloaks() && (what == "is_eater_of_cloaks")) { return true; }
  if (is_eater_of_foliage() && (what == "is_eater_of_foliage")) { return true; }
  if (is_eater_of_food() && (what == "is_eater_of_food")) { return true; }
  if (is_eater_of_gauntlets() && (what == "is_eater_of_gauntlets")) { return true; }
  if (is_eater_of_grass() && (what == "is_eater_of_grass")) { return true; }
  if (is_eater_of_green_blood() && (what == "is_eater_of_green_blood")) { return true; }
  if (is_eater_of_helmets() && (what == "is_eater_of_helmets")) { return true; }
  if (is_eater_of_magical_items() && (what == "is_eater_of_magical_items")) { return true; }
  if (is_eater_of_meat() && (what == "is_eater_of_meat")) { return true; }
  if (is_eater_of_plants() && (what == "is_eater_of_plants")) { return true; }
  if (is_eater_of_potions() && (what == "is_eater_of_potions")) { return true; }
  if (is_eater_of_red_blood() && (what == "is_eater_of_red_blood")) { return true; }
  if (is_eater_of_rings() && (what == "is_eater_of_rings")) { return true; }
  if (is_eater_of_shields() && (what == "is_eater_of_shields")) { return true; }
  if (is_eater_of_slime() && (what == "is_eater_of_slime")) { return true; }
  if (is_eater_of_staffs() && (what == "is_eater_of_staffs")) { return true; }
  if (is_eater_of_treasure() && (what == "is_eater_of_treasure")) { return true; }
  if (is_eater_of_weapons() && (what == "is_eater_of_weapons")) { return true; }
  if (is_enchantable_as_a_group() && (what == "is_enchantable_as_a_group")) { return true; }
  if (is_enchantable() && (what == "is_enchantable")) { return true; }
  if (is_enchantstone() && (what == "is_enchantstone")) { return true; }
  if (is_engulfer() && (what == "is_engulfer")) { return true; }
  if (is_equippable() && (what == "is_equippable")) { return true; }
  if (is_ethereal_mob() && (what == "is_ethereal_mob")) { return true; }
  if (is_ethereal() && (what == "is_ethereal")) { return true; }
  if (is_ettin() && (what == "is_ettin")) { return true; }
  if (is_exit_finder() && (what == "is_exit_finder")) { return true; }
  if (is_explorer() && (what == "is_explorer")) { return true; }
  if (is_explosion() && (what == "is_explosion")) { return true; }
  if (is_fairy() && (what == "is_fairy")) { return true; }
  if (is_fearless() && (what == "is_fearless")) { return true; }
  if (is_fire_elemental() && (what == "is_fire_elemental")) { return true; }
  if (is_fire() && (what == "is_fire")) { return true; }
  if (is_flat() && (what == "is_flat")) { return true; }
  if (is_floating() && (what == "is_floating")) { return true; }
  if (is_floor_deco() && (what == "is_floor_deco")) { return true; }
  if (is_floor() && (what == "is_floor")) { return true; }
  if (is_flying() && (what == "is_flying")) { return true; }
  if (is_foliage() && (what == "is_foliage")) { return true; }
  if (is_food() && (what == "is_food")) { return true; }
  if (is_gas_blocker() && (what == "is_gas_blocker")) { return true; }
  if (is_gauntlet() && (what == "is_gauntlet")) { return true; }
  if (is_gelatinous() && (what == "is_gelatinous")) { return true; }
  if (is_glass() && (what == "is_glass")) { return true; }
  if (is_gnome() && (what == "is_gnome")) { return true; }
  if (is_goat() && (what == "is_goat")) { return true; }
  if (is_gold() && (what == "is_gold")) { return true; }
  if (is_golem() && (what == "is_golem")) { return true; }
  if (is_grass() && (what == "is_grass")) { return true; }
  if (is_green_blooded() && (what == "is_green_blooded")) { return true; }
  if (is_green_blood() && (what == "is_green_blood")) { return true; }
  if (is_green_splatter() && (what == "is_green_splatter")) { return true; }
  if (is_hard() && (what == "is_hard")) { return true; }
  if (is_hazard() && (what == "is_hazard")) { return true; }
  if (is_health_booster() && (what == "is_health_booster")) { return true; }
  if (is_heavy() && (what == "is_heavy")) { return true; }
  if (is_helmet() && (what == "is_helmet")) { return true; }
  if (is_herbivore() && (what == "is_herbivore")) { return true; }
  if (is_hittable() && (what == "is_hittable")) { return true; }
  if (is_humanoid() && (what == "is_humanoid")) { return true; }
  if (is_iceman() && (what == "is_iceman")) { return true; }
  if (is_immune_to_acid() && (what == "is_immune_to_acid")) { return true; }
  if (is_immune_to_cold() && (what == "is_immune_to_cold")) { return true; }
  if (is_immune_to_draining() && (what == "is_immune_to_draining")) { return true; }
  if (is_immune_to_electricity() && (what == "is_immune_to_electricity")) { return true; }
  if (is_immune_to_fire() && (what == "is_immune_to_fire")) { return true; }
  if (is_immune_to_necrosis() && (what == "is_immune_to_necrosis")) { return true; }
  if (is_immune_to_negation() && (what == "is_immune_to_negation")) { return true; }
  if (is_immune_to_poison() && (what == "is_immune_to_poison")) { return true; }
  if (is_immune_to_spiderwebs() && (what == "is_immune_to_spiderwebs")) { return true; }
  if (is_immune_to_teleport_attack() && (what == "is_immune_to_teleport_attack")) { return true; }
  if (is_immune_to_water() && (what == "is_immune_to_water")) { return true; }
  if (is_intelligent() && (what == "is_intelligent")) { return true; }
  if (is_interesting() && (what == "is_interesting")) { return true; }
  if (is_internal() && (what == "is_internal")) { return true; }
  if (is_invisible() && (what == "is_invisible")) { return true; }
  if (is_item_carrier() && (what == "is_item_carrier")) { return true; }
  if (is_item_collector() && (what == "is_item_collector")) { return true; }
  if (is_item_organic() && (what == "is_item_organic")) { return true; }
  if (is_item_targetted() && (what == "is_item_targetted")) { return true; }
  if (is_item() && (what == "is_item")) { return true; }
  if (is_key_special() && (what == "is_key_special")) { return true; }
  if (is_key() && (what == "is_key")) { return true; }
  if (is_laser() && (what == "is_laser")) { return true; }
  if (is_lava() && (what == "is_lava")) { return true; }
  if (is_leech() && (what == "is_leech")) { return true; }
  if (is_lifeless() && (what == "is_lifeless")) { return true; }
  if (is_light_blocker_for_monst() && (what == "is_light_blocker_for_monst")) { return true; }
  if (is_light_blocker() && (what == "is_light_blocker")) { return true; }
  if (is_lightning() && (what == "is_lightning")) { return true; }
  if (is_light() && (what == "is_light")) { return true; }
  if (is_limb() && (what == "is_limb")) { return true; }
  if (is_living() && (what == "is_living")) { return true; }
  if (is_loggable() && (what == "is_loggable")) { return true; }
  if (is_made_of_rock() && (what == "is_made_of_rock")) { return true; }
  if (is_magical_effect() && (what == "is_magical_effect")) { return true; }
  if (is_magical() && (what == "is_magical")) { return true; }
  if (is_mantisman() && (what == "is_mantisman")) { return true; }
  if (is_map_beast() && (what == "is_map_beast")) { return true; }
  if (is_meat() && (what == "is_meat")) { return true; }
  if (is_metal() && (what == "is_metal")) { return true; }
  if (is_mimic() && (what == "is_mimic")) { return true; }
  if (is_minion() && (what == "is_minion")) { return true; }
  if (is_missile() && (what == "is_missile")) { return true; }
  if (is_mob_challenge_class_A() && (what == "is_mob_challenge_class_A")) { return true; }
  if (is_mob_challenge_class_B() && (what == "is_mob_challenge_class_B")) { return true; }
  if (is_mob() && (what == "is_mob")) { return true; }
  if (is_molekin() && (what == "is_molekin")) { return true; }
  if (is_monst_class_A() && (what == "is_monst_class_A")) { return true; }
  if (is_monst_class_B() && (what == "is_monst_class_B")) { return true; }
  if (is_monst_class_C() && (what == "is_monst_class_C")) { return true; }
  if (is_monst_class_D() && (what == "is_monst_class_D")) { return true; }
  if (is_monst_class_E() && (what == "is_monst_class_E")) { return true; }
  if (is_monst_pack() && (what == "is_monst_pack")) { return true; }
  if (is_monst() && (what == "is_monst")) { return true; }
  if (is_moveable() && (what == "is_moveable")) { return true; }
  if (is_msg_allowed_hears_something() && (what == "is_msg_allowed_hears_something")) { return true; }
  if (is_msg_allowed_is_dead() && (what == "is_msg_allowed_is_dead")) { return true; }
  if (is_msg_allowed_is_seen() && (what == "is_msg_allowed_is_seen")) { return true; }
  if (is_msg_allowed_is_surprised() && (what == "is_msg_allowed_is_surprised")) { return true; }
  if (is_msg_allowed_is_wounded() && (what == "is_msg_allowed_is_wounded")) { return true; }
  if (is_msg_allowed_senses_danger() && (what == "is_msg_allowed_senses_danger")) { return true; }
  if (is_msg() && (what == "is_msg")) { return true; }
  if (is_necrotic_danger_level() && (what == "is_necrotic_danger_level")) { return true; }
  if (is_no_tile() && (what == "is_no_tile")) { return true; }
  if (is_obs_destructable() && (what == "is_obs_destructable")) { return true; }
  if (is_obs_for_jump_landing() && (what == "is_obs_for_jump_landing")) { return true; }
  if (is_obs_for_shoving() && (what == "is_obs_for_shoving")) { return true; }
  if (is_obsidian() && (what == "is_obsidian")) { return true; }
  if (is_obs_in_the_way_for_jumping() && (what == "is_obs_in_the_way_for_jumping")) { return true; }
  if (is_obs_in_the_way_for_shooting() && (what == "is_obs_in_the_way_for_shooting")) { return true; }
  if (is_obs_in_the_way_for_throwing() && (what == "is_obs_in_the_way_for_throwing")) { return true; }
  if (is_obs_wall_or_door() && (what == "is_obs_wall_or_door")) { return true; }
  if (is_obs_when_dead() && (what == "is_obs_when_dead")) { return true; }
  if (is_ogre() && (what == "is_ogre")) { return true; }
  if (is_openable() && (what == "is_openable")) { return true; }
  if (is_organic() && (what == "is_organic")) { return true; }
  if (is_pillar() && (what == "is_pillar")) { return true; }
  if (is_pirhana() && (what == "is_pirhana")) { return true; }
  if (is_plant() && (what == "is_plant")) { return true; }
  if (is_player() && (what == "is_player")) { return true; }
  if (is_poisonous_danger_level() && (what == "is_poisonous_danger_level")) { return true; }
  if (is_portal() && (what == "is_portal")) { return true; }
  if (is_potion() && (what == "is_potion")) { return true; }
  if (is_pressure_plate() && (what == "is_pressure_plate")) { return true; }
  if (is_projectile() && (what == "is_projectile")) { return true; }
  if (is_ranged_weapon() && (what == "is_ranged_weapon")) { return true; }
  if (is_rat() && (what == "is_rat")) { return true; }
  if (is_red_blooded() && (what == "is_red_blooded")) { return true; }
  if (is_red_blood() && (what == "is_red_blood")) { return true; }
  if (is_red_splatter() && (what == "is_red_splatter")) { return true; }
  if (is_removable_if_out_of_slots() && (what == "is_removable_if_out_of_slots")) { return true; }
  if (is_ring() && (what == "is_ring")) { return true; }
  if (is_ripple() && (what == "is_ripple")) { return true; }
  if (is_rock() && (what == "is_rock")) { return true; }
  if (is_rusty() && (what == "is_rusty")) { return true; }
  if (is_scorpion() && (what == "is_scorpion")) { return true; }
  if (is_secret_door() && (what == "is_secret_door")) { return true; }
  if (is_sewer_wall() && (what == "is_sewer_wall")) { return true; }
  if (is_shallow_water() && (what == "is_shallow_water")) { return true; }
  if (is_sheep() && (what == "is_sheep")) { return true; }
  if (is_shield() && (what == "is_shield")) { return true; }
  if (is_shovable_and_sticky() && (what == "is_shovable_and_sticky")) { return true; }
  if (is_shovable() && (what == "is_shovable")) { return true; }
  if (is_skillstone() && (what == "is_skillstone")) { return true; }
  if (is_skill() && (what == "is_skill")) { return true; }
  if (is_slime() && (what == "is_slime")) { return true; }
  if (is_slippery() && (what == "is_slippery")) { return true; }
  if (is_smoke() && (what == "is_smoke")) { return true; }
  if (is_snake() && (what == "is_snake")) { return true; }
  if (is_soft() && (what == "is_soft")) { return true; }
  if (is_spiderweb() && (what == "is_spiderweb")) { return true; }
  if (is_spider() && (what == "is_spider")) { return true; }
  if (is_splatter() && (what == "is_splatter")) { return true; }
  if (is_staff() && (what == "is_staff")) { return true; }
  if (is_steam() && (what == "is_steam")) { return true; }
  if (is_sticky() && (what == "is_sticky")) { return true; }
  if (is_stone() && (what == "is_stone")) { return true; }
  if (is_swimmer() && (what == "is_swimmer")) { return true; }
  if (is_sword() && (what == "is_sword")) { return true; }
  if (is_target_radial() && (what == "is_target_radial")) { return true; }
  if (is_target_select() && (what == "is_target_select")) { return true; }
  if (is_tentacle() && (what == "is_tentacle")) { return true; }
  if (is_thief() && (what == "is_thief")) { return true; }
  if (is_throwable() && (what == "is_throwable")) { return true; }
  if (is_thrown_as_a_weapon() && (what == "is_thrown_as_a_weapon")) { return true; }
  if (is_tickable() && (what == "is_tickable")) { return true; }
  if (is_tireless() && (what == "is_tireless")) { return true; }
  if (is_tmp_thing() && (what == "is_tmp_thing")) { return true; }
  if (is_torch() && (what == "is_torch")) { return true; }
  if (is_trap() && (what == "is_trap")) { return true; }
  if (is_treasure_chest() && (what == "is_treasure_chest")) { return true; }
  if (is_treasure_type() && (what == "is_treasure_type")) { return true; }
  if (is_treasure() && (what == "is_treasure")) { return true; }
  if (is_troll() && (what == "is_troll")) { return true; }
  if (is_undead() && (what == "is_undead")) { return true; }
  if (is_unused_flag100() && (what == "is_unused_flag100")) { return true; }
  if (is_unused_flag101() && (what == "is_unused_flag101")) { return true; }
  if (is_unused_flag102() && (what == "is_unused_flag102")) { return true; }
  if (is_unused_flag103() && (what == "is_unused_flag103")) { return true; }
  if (is_unused_flag104() && (what == "is_unused_flag104")) { return true; }
  if (is_unused_flag105() && (what == "is_unused_flag105")) { return true; }
  if (is_unused_flag106() && (what == "is_unused_flag106")) { return true; }
  if (is_unused_flag107() && (what == "is_unused_flag107")) { return true; }
  if (is_unused_flag108() && (what == "is_unused_flag108")) { return true; }
  if (is_unused_flag109() && (what == "is_unused_flag109")) { return true; }
  if (is_unused_flag10() && (what == "is_unused_flag10")) { return true; }
  if (is_unused_flag110() && (what == "is_unused_flag110")) { return true; }
  if (is_unused_flag111() && (what == "is_unused_flag111")) { return true; }
  if (is_unused_flag112() && (what == "is_unused_flag112")) { return true; }
  if (is_unused_flag113() && (what == "is_unused_flag113")) { return true; }
  if (is_unused_flag114() && (what == "is_unused_flag114")) { return true; }
  if (is_unused_flag115() && (what == "is_unused_flag115")) { return true; }
  if (is_unused_flag116() && (what == "is_unused_flag116")) { return true; }
  if (is_unused_flag117() && (what == "is_unused_flag117")) { return true; }
  if (is_unused_flag118() && (what == "is_unused_flag118")) { return true; }
  if (is_unused_flag119() && (what == "is_unused_flag119")) { return true; }
  if (is_unused_flag11() && (what == "is_unused_flag11")) { return true; }
  if (is_unused_flag120() && (what == "is_unused_flag120")) { return true; }
  if (is_unused_flag121() && (what == "is_unused_flag121")) { return true; }
  if (is_unused_flag122() && (what == "is_unused_flag122")) { return true; }
  if (is_unused_flag123() && (what == "is_unused_flag123")) { return true; }
  if (is_unused_flag124() && (what == "is_unused_flag124")) { return true; }
  if (is_unused_flag125() && (what == "is_unused_flag125")) { return true; }
  if (is_unused_flag126() && (what == "is_unused_flag126")) { return true; }
  if (is_unused_flag127() && (what == "is_unused_flag127")) { return true; }
  if (is_unused_flag128() && (what == "is_unused_flag128")) { return true; }
  if (is_unused_flag129() && (what == "is_unused_flag129")) { return true; }
  if (is_unused_flag12() && (what == "is_unused_flag12")) { return true; }
  if (is_unused_flag130() && (what == "is_unused_flag130")) { return true; }
  if (is_unused_flag131() && (what == "is_unused_flag131")) { return true; }
  if (is_unused_flag132() && (what == "is_unused_flag132")) { return true; }
  if (is_unused_flag133() && (what == "is_unused_flag133")) { return true; }
  if (is_unused_flag134() && (what == "is_unused_flag134")) { return true; }
  if (is_unused_flag135() && (what == "is_unused_flag135")) { return true; }
  if (is_unused_flag136() && (what == "is_unused_flag136")) { return true; }
  if (is_unused_flag137() && (what == "is_unused_flag137")) { return true; }
  if (is_unused_flag138() && (what == "is_unused_flag138")) { return true; }
  if (is_unused_flag139() && (what == "is_unused_flag139")) { return true; }
  if (is_unused_flag13() && (what == "is_unused_flag13")) { return true; }
  if (is_unused_flag140() && (what == "is_unused_flag140")) { return true; }
  if (is_unused_flag141() && (what == "is_unused_flag141")) { return true; }
  if (is_unused_flag142() && (what == "is_unused_flag142")) { return true; }
  if (is_unused_flag143() && (what == "is_unused_flag143")) { return true; }
  if (is_unused_flag144() && (what == "is_unused_flag144")) { return true; }
  if (is_unused_flag145() && (what == "is_unused_flag145")) { return true; }
  if (is_unused_flag146() && (what == "is_unused_flag146")) { return true; }
  if (is_unused_flag147() && (what == "is_unused_flag147")) { return true; }
  if (is_unused_flag148() && (what == "is_unused_flag148")) { return true; }
  if (is_unused_flag149() && (what == "is_unused_flag149")) { return true; }
  if (is_unused_flag14() && (what == "is_unused_flag14")) { return true; }
  if (is_unused_flag150() && (what == "is_unused_flag150")) { return true; }
  if (is_unused_flag151() && (what == "is_unused_flag151")) { return true; }
  if (is_unused_flag152() && (what == "is_unused_flag152")) { return true; }
  if (is_unused_flag153() && (what == "is_unused_flag153")) { return true; }
  if (is_unused_flag154() && (what == "is_unused_flag154")) { return true; }
  if (is_unused_flag155() && (what == "is_unused_flag155")) { return true; }
  if (is_unused_flag15() && (what == "is_unused_flag15")) { return true; }
  if (is_unused_flag16() && (what == "is_unused_flag16")) { return true; }
  if (is_unused_flag179() && (what == "is_unused_flag179")) { return true; }
  if (is_unused_flag17() && (what == "is_unused_flag17")) { return true; }
  if (is_unused_flag18() && (what == "is_unused_flag18")) { return true; }
  if (is_unused_flag192() && (what == "is_unused_flag192")) { return true; }
  if (is_unused_flag19() && (what == "is_unused_flag19")) { return true; }
  if (is_unused_flag1() && (what == "is_unused_flag1")) { return true; }
  if (is_unused_flag20() && (what == "is_unused_flag20")) { return true; }
  if (is_unused_flag21() && (what == "is_unused_flag21")) { return true; }
  if (is_unused_flag22() && (what == "is_unused_flag22")) { return true; }
  if (is_unused_flag23() && (what == "is_unused_flag23")) { return true; }
  if (is_unused_flag24() && (what == "is_unused_flag24")) { return true; }
  if (is_unused_flag25() && (what == "is_unused_flag25")) { return true; }
  if (is_unused_flag26() && (what == "is_unused_flag26")) { return true; }
  if (is_unused_flag27() && (what == "is_unused_flag27")) { return true; }
  if (is_unused_flag28() && (what == "is_unused_flag28")) { return true; }
  if (is_unused_flag29() && (what == "is_unused_flag29")) { return true; }
  if (is_unused_flag2() && (what == "is_unused_flag2")) { return true; }
  if (is_unused_flag30() && (what == "is_unused_flag30")) { return true; }
  if (is_unused_flag31() && (what == "is_unused_flag31")) { return true; }
  if (is_unused_flag32() && (what == "is_unused_flag32")) { return true; }
  if (is_unused_flag33() && (what == "is_unused_flag33")) { return true; }
  if (is_unused_flag34() && (what == "is_unused_flag34")) { return true; }
  if (is_unused_flag35() && (what == "is_unused_flag35")) { return true; }
  if (is_unused_flag36() && (what == "is_unused_flag36")) { return true; }
  if (is_unused_flag37() && (what == "is_unused_flag37")) { return true; }
  if (is_unused_flag38() && (what == "is_unused_flag38")) { return true; }
  if (is_unused_flag39() && (what == "is_unused_flag39")) { return true; }
  if (is_unused_flag3() && (what == "is_unused_flag3")) { return true; }
  if (is_unused_flag40() && (what == "is_unused_flag40")) { return true; }
  if (is_unused_flag41() && (what == "is_unused_flag41")) { return true; }
  if (is_unused_flag42() && (what == "is_unused_flag42")) { return true; }
  if (is_unused_flag43() && (what == "is_unused_flag43")) { return true; }
  if (is_unused_flag44() && (what == "is_unused_flag44")) { return true; }
  if (is_unused_flag45() && (what == "is_unused_flag45")) { return true; }
  if (is_unused_flag46() && (what == "is_unused_flag46")) { return true; }
  if (is_unused_flag47() && (what == "is_unused_flag47")) { return true; }
  if (is_unused_flag48() && (what == "is_unused_flag48")) { return true; }
  if (is_unused_flag49() && (what == "is_unused_flag49")) { return true; }
  if (is_unused_flag4() && (what == "is_unused_flag4")) { return true; }
  if (is_unused_flag50() && (what == "is_unused_flag50")) { return true; }
  if (is_unused_flag51() && (what == "is_unused_flag51")) { return true; }
  if (is_unused_flag52() && (what == "is_unused_flag52")) { return true; }
  if (is_unused_flag53() && (what == "is_unused_flag53")) { return true; }
  if (is_unused_flag54() && (what == "is_unused_flag54")) { return true; }
  if (is_unused_flag55() && (what == "is_unused_flag55")) { return true; }
  if (is_unused_flag56() && (what == "is_unused_flag56")) { return true; }
  if (is_unused_flag57() && (what == "is_unused_flag57")) { return true; }
  if (is_unused_flag58() && (what == "is_unused_flag58")) { return true; }
  if (is_unused_flag59() && (what == "is_unused_flag59")) { return true; }
  if (is_unused_flag5() && (what == "is_unused_flag5")) { return true; }
  if (is_unused_flag60() && (what == "is_unused_flag60")) { return true; }
  if (is_unused_flag61() && (what == "is_unused_flag61")) { return true; }
  if (is_unused_flag62() && (what == "is_unused_flag62")) { return true; }
  if (is_unused_flag63() && (what == "is_unused_flag63")) { return true; }
  if (is_unused_flag64() && (what == "is_unused_flag64")) { return true; }
  if (is_unused_flag65() && (what == "is_unused_flag65")) { return true; }
  if (is_unused_flag66() && (what == "is_unused_flag66")) { return true; }
  if (is_unused_flag67() && (what == "is_unused_flag67")) { return true; }
  if (is_unused_flag68() && (what == "is_unused_flag68")) { return true; }
  if (is_unused_flag69() && (what == "is_unused_flag69")) { return true; }
  if (is_unused_flag6() && (what == "is_unused_flag6")) { return true; }
  if (is_unused_flag70() && (what == "is_unused_flag70")) { return true; }
  if (is_unused_flag71() && (what == "is_unused_flag71")) { return true; }
  if (is_unused_flag72() && (what == "is_unused_flag72")) { return true; }
  if (is_unused_flag73() && (what == "is_unused_flag73")) { return true; }
  if (is_unused_flag74() && (what == "is_unused_flag74")) { return true; }
  if (is_unused_flag75() && (what == "is_unused_flag75")) { return true; }
  if (is_unused_flag76() && (what == "is_unused_flag76")) { return true; }
  if (is_unused_flag77() && (what == "is_unused_flag77")) { return true; }
  if (is_unused_flag78() && (what == "is_unused_flag78")) { return true; }
  if (is_unused_flag79() && (what == "is_unused_flag79")) { return true; }
  if (is_unused_flag7() && (what == "is_unused_flag7")) { return true; }
  if (is_unused_flag80() && (what == "is_unused_flag80")) { return true; }
  if (is_unused_flag81() && (what == "is_unused_flag81")) { return true; }
  if (is_unused_flag82() && (what == "is_unused_flag82")) { return true; }
  if (is_unused_flag83() && (what == "is_unused_flag83")) { return true; }
  if (is_unused_flag84() && (what == "is_unused_flag84")) { return true; }
  if (is_unused_flag85() && (what == "is_unused_flag85")) { return true; }
  if (is_unused_flag86() && (what == "is_unused_flag86")) { return true; }
  if (is_unused_flag87() && (what == "is_unused_flag87")) { return true; }
  if (is_unused_flag88() && (what == "is_unused_flag88")) { return true; }
  if (is_unused_flag89() && (what == "is_unused_flag89")) { return true; }
  if (is_unused_flag8() && (what == "is_unused_flag8")) { return true; }
  if (is_unused_flag90() && (what == "is_unused_flag90")) { return true; }
  if (is_unused_flag91() && (what == "is_unused_flag91")) { return true; }
  if (is_unused_flag92() && (what == "is_unused_flag92")) { return true; }
  if (is_unused_flag93() && (what == "is_unused_flag93")) { return true; }
  if (is_unused_flag94() && (what == "is_unused_flag94")) { return true; }
  if (is_unused_flag95() && (what == "is_unused_flag95")) { return true; }
  if (is_unused_flag96() && (what == "is_unused_flag96")) { return true; }
  if (is_unused_flag97() && (what == "is_unused_flag97")) { return true; }
  if (is_unused_flag98() && (what == "is_unused_flag98")) { return true; }
  if (is_unused_flag99() && (what == "is_unused_flag99")) { return true; }
  if (is_unused_flag9() && (what == "is_unused_flag9")) { return true; }
  if (is_usable() && (what == "is_usable")) { return true; }
  if (is_used_when_thrown() && (what == "is_used_when_thrown")) { return true; }
  if (is_very_combustible() && (what == "is_very_combustible")) { return true; }
  if (is_very_hard() && (what == "is_very_hard")) { return true; }
  if (is_very_heavy() && (what == "is_very_heavy")) { return true; }
  if (is_very_intelligent() && (what == "is_very_intelligent")) { return true; }
  if (is_wall_dungeon() && (what == "is_wall_dungeon")) { return true; }
  if (is_wall() && (what == "is_wall")) { return true; }
  if (is_weapon() && (what == "is_weapon")) { return true; }
  if (is_wet_grass_trampled() && (what == "is_wet_grass_trampled")) { return true; }
  if (is_wet_grass() && (what == "is_wet_grass")) { return true; }
  if (is_wooden() && (what == "is_wooden")) { return true; }
  if (is_yeti() && (what == "is_yeti")) { return true; }
  if (minion_limit() && (what == "minion_limit")) { return true; }
  if (noise_additional_on_jump_end() && (what == "noise_additional_on_jump_end")) { return true; }
  if (noise_additional_on_teleporting() && (what == "noise_additional_on_teleporting")) { return true; }
  if (noise_blocker() && (what == "noise_blocker")) { return true; }
  if (noise_decibels_hearing() && (what == "noise_decibels_hearing")) { return true; }
  if (noise_on_born() && (what == "noise_on_born")) { return true; }
  if (noise_on_dropping() && (what == "noise_on_dropping")) { return true; }
  if (noise_on_hit_and_now_dead() && (what == "noise_on_hit_and_now_dead")) { return true; }
  if (noise_on_hit_and_still_alive() && (what == "noise_on_hit_and_still_alive")) { return true; }
  if (noise_on_moving() && (what == "noise_on_moving")) { return true; }
  if (noise_on_open_or_close() && (what == "noise_on_open_or_close")) { return true; }
  if (on_death_is_stone() && (what == "on_death_is_stone")) { return true; }
  if (range_max() && (what == "range_max")) { return true; }
  if (shove_strength() && (what == "shove_strength")) { return true; }
  if (stat_att_penalty_when_idle_max() && (what == "stat_att_penalty_when_idle_max")) { return true; }
  if (stat_att_penalty_when_idle() && (what == "stat_att_penalty_when_idle")) { return true; }
  if (stat_att_penalty_when_in_deep_water() && (what == "stat_att_penalty_when_in_deep_water")) { return true; }
  if (stat_att_penalty_when_in_shallow_water() && (what == "stat_att_penalty_when_in_shallow_water")) { return true; }
  if (stat_att_penalty_when_stuck_max() && (what == "stat_att_penalty_when_stuck_max")) { return true; }
  if (stat_att_penalty_when_stuck() && (what == "stat_att_penalty_when_stuck")) { return true; }
  if (stat_def_penalty_when_idle_max() && (what == "stat_def_penalty_when_idle_max")) { return true; }
  if (stat_def_penalty_when_idle() && (what == "stat_def_penalty_when_idle")) { return true; }
  if (stat_def_penalty_when_in_deep_water() && (what == "stat_def_penalty_when_in_deep_water")) { return true; }
  if (stat_def_penalty_when_in_shallow_water() && (what == "stat_def_penalty_when_in_shallow_water")) { return true; }
  if (stat_def_penalty_when_stuck_max() && (what == "stat_def_penalty_when_stuck_max")) { return true; }
  if (stat_def_penalty_when_stuck() && (what == "stat_def_penalty_when_stuck")) { return true; }
  if (tick_prio() && (what == "tick_prio")) { return true; }
  // end sort marker1 }

  // Any water type
  if ((is_shallow_water() || is_deep_water()) && (what == "is_water")) { return true; }

  // clang-format on
  return (what == text_short_name());
}

bool Thing::matches(const std::string &what)
{
  if (strisregexp(what.c_str())) {
    struct slre slre;
    if (slre_compile(&slre, what.c_str())) {
      auto name = text_short_name();
      if (slre_match(&slre, name.c_str(), name.size(), nullptr /* captures */)) {
        return true;
      }
    }
    return false;
  }
  // clang-format off
  // begin sort marker2 {
  if (ai_detect_secret_doors() && (what == "ai_detect_secret_doors")) { return true; }
  if (ai_resent_count() && (what == "ai_resent_count")) { return true; }
  if (ai_wanderer() && (what == "ai_wanderer")) { return true; }
  if (attack_blood() && (what == "attack_blood")) { return true; }
  if (attack_eater() && (what == "attack_eater")) { return true; }
  if (attack_humanoid() && (what == "attack_humanoid")) { return true; }
  if (attack_living() && (what == "attack_living")) { return true; }
  if (attack_meat() && (what == "attack_meat")) { return true; }
  if (attack_no_msg() && (what == "attack_no_msg")) { return true; }
  if (attacks_per_round() && (what == "attacks_per_round")) { return true; }
  if (attack_undead() && (what == "attack_undead")) { return true; }
  if (collision_hit_180() && (what == "collision_hit_180")) { return true; }
  if (collision_hit_360() && (what == "collision_hit_360")) { return true; }
  if (collision_hit_adj() && (what == "collision_hit_adj")) { return true; }
  if (collision_hit_two_tiles_ahead() && (what == "collision_hit_two_tiles_ahead")) { return true; }
  if (consume_per_bite_amount() && (what == "consume_per_bite_amount")) { return true; }
  if (dmg_received_doubled_from_cold() && (what == "dmg_received_doubled_from_cold")) { return true; }
  if (enchant_max() && (what == "enchant_max")) { return true; }
  if (environ_dislikes_acid() && (what == "environ_dislikes_acid")) { return true; }
  if (environ_dislikes_cold() && (what == "environ_dislikes_cold")) { return true; }
  if (environ_dislikes_fire() && (what == "environ_dislikes_fire")) { return true; }
  if (environ_dislikes_necrosis() && (what == "environ_dislikes_necrosis")) { return true; }
  if (environ_dislikes_poison() && (what == "environ_dislikes_poison")) { return true; }
  if (environ_dislikes_water() && (what == "environ_dislikes_water")) { return true; }
  if (environ_hates_acid() && (what == "environ_hates_acid")) { return true; }
  if (environ_hates_cold() && (what == "environ_hates_cold")) { return true; }
  if (environ_hates_fire() && (what == "environ_hates_fire")) { return true; }
  if (environ_hates_necrosis() && (what == "environ_hates_necrosis")) { return true; }
  if (environ_hates_poison() && (what == "environ_hates_poison")) { return true; }
  if (environ_hates_water() && (what == "environ_hates_water")) { return true; }
  if (environ_likes_deep_water() && (what == "environ_likes_deep_water")) { return true; }
  if (environ_likes_lava() && (what == "environ_likes_lava")) { return true; }
  if (environ_likes_shallow_water() && (what == "environ_likes_shallow_water")) { return true; }
  if (gfx_pixelart_show_highlighted() && (what == "gfx_pixelart_show_highlighted")) { return true; }
  if (gfx_pixelart_show_square_outlined() && (what == "gfx_pixelart_show_square_outlined")) { return true; }
  if (hunger_is_insatiable() && (what == "hunger_is_insatiable")) { return true; }
  if (is_able_to_amplify_footsteps() && (what == "is_able_to_amplify_footsteps")) { return true; }
  if (is_able_to_attack_mobs() && (what == "is_able_to_attack_mobs")) { return true; }
  if (is_able_to_attack_owner() && (what == "is_able_to_attack_owner")) { return true; }
  if (is_able_to_be_resurrected() && (what == "is_able_to_be_resurrected")) { return true; }
  if (is_able_to_be_surprised() && (what == "is_able_to_be_surprised")) { return true; }
  if (is_able_to_be_teleported() && (what == "is_able_to_be_teleported")) { return true; }
  if (is_able_to_break_down_doors() && (what == "is_able_to_break_down_doors")) { return true; }
  if (is_able_to_break_out_of_ice() && (what == "is_able_to_break_out_of_ice")) { return true; }
  if (is_able_to_break_out_of_webs() && (what == "is_able_to_break_out_of_webs")) { return true; }
  if (is_able_to_change_levels() && (what == "is_able_to_change_levels")) { return true; }
  if (is_able_to_collect_keys() && (what == "is_able_to_collect_keys")) { return true; }
  if (is_able_to_dampen_footsteps() && (what == "is_able_to_dampen_footsteps")) { return true; }
  if (is_able_to_enchant_items() && (what == "is_able_to_enchant_items")) { return true; }
  if (is_able_to_fall() && (what == "is_able_to_fall")) { return true; }
  if (is_able_to_follow() && (what == "is_able_to_follow")) { return true; }
  if (is_able_to_freeze() && (what == "is_able_to_freeze")) { return true; }
  if (is_able_to_grapple() && (what == "is_able_to_grapple")) { return true; }
  if (is_able_to_jump_attack() && (what == "is_able_to_jump_attack")) { return true; }
  if (is_able_to_jump_escape() && (what == "is_able_to_jump_escape")) { return true; }
  if (is_able_to_jump_onto() && (what == "is_able_to_jump_onto")) { return true; }
  if (is_able_to_jump() && (what == "is_able_to_jump")) { return true; }
  if (is_able_to_jump_without_tiring() && (what == "is_able_to_jump_without_tiring")) { return true; }
  if (is_able_to_learn_skills() && (what == "is_able_to_learn_skills")) { return true; }
  if (is_able_to_live_out_of_water() && (what == "is_able_to_live_out_of_water")) { return true; }
  if (is_able_to_lunge() && (what == "is_able_to_lunge")) { return true; }
  if (is_able_to_melt() && (what == "is_able_to_melt")) { return true; }
  if (is_able_to_move_diagonally() && (what == "is_able_to_move_diagonally")) { return true; }
  if (is_able_to_open_doors() && (what == "is_able_to_open_doors")) { return true; }
  if (is_able_to_regenerate() && (what == "is_able_to_regenerate")) { return true; }
  if (is_able_to_rest() && (what == "is_able_to_rest")) { return true; }
  if (is_able_to_run_away_after_stealing() && (what == "is_able_to_run_away_after_stealing")) { return true; }
  if (is_able_to_see_in_the_dark() && (what == "is_able_to_see_in_the_dark")) { return true; }
  if (is_able_to_see_invisible() && (what == "is_able_to_see_invisible")) { return true; }
  if (is_able_to_see_through_doors() && (what == "is_able_to_see_through_doors")) { return true; }
  if (is_able_to_shoot_at_close_range() && (what == "is_able_to_shoot_at_close_range")) { return true; }
  if (is_able_to_shoot_at() && (what == "is_able_to_shoot_at")) { return true; }
  if (is_able_to_shove() && (what == "is_able_to_shove")) { return true; }
  if (is_able_to_sleep() && (what == "is_able_to_sleep")) { return true; }
  if (is_able_to_spawn_things() && (what == "is_able_to_spawn_things")) { return true; }
  if (is_able_to_swim() && (what == "is_able_to_swim")) { return true; }
  if (is_able_to_teleport_attack() && (what == "is_able_to_teleport_attack")) { return true; }
  if (is_able_to_teleport_escape() && (what == "is_able_to_teleport_escape")) { return true; }
  if (is_able_to_teleport_self() && (what == "is_able_to_teleport_self")) { return true; }
  if (is_able_to_teleport_without_tiring() && (what == "is_able_to_teleport_without_tiring")) { return true; }
  if (is_able_to_tire() && (what == "is_able_to_tire")) { return true; }
  if (is_able_to_use_amulet() && (what == "is_able_to_use_amulet")) { return true; }
  if (is_able_to_use_armor() && (what == "is_able_to_use_armor")) { return true; }
  if (is_able_to_use_boots() && (what == "is_able_to_use_boots")) { return true; }
  if (is_able_to_use_cloak() && (what == "is_able_to_use_cloak")) { return true; }
  if (is_able_to_use_gauntlet() && (what == "is_able_to_use_gauntlet")) { return true; }
  if (is_able_to_use_helmet() && (what == "is_able_to_use_helmet")) { return true; }
  if (is_able_to_use_ranged_weapons() && (what == "is_able_to_use_ranged_weapons")) { return true; }
  if (is_able_to_use_rings() && (what == "is_able_to_use_rings")) { return true; }
  if (is_able_to_use_shield() && (what == "is_able_to_use_shield")) { return true; }
  if (is_able_to_use_staffs() && (what == "is_able_to_use_staffs")) { return true; }
  if (is_able_to_use_weapons() && (what == "is_able_to_use_weapons")) { return true; }
  if (is_able_to_walk_through_walls() && (what == "is_able_to_walk_through_walls")) { return true; }
  if (is_acid() && (what == "is_acid")) { return true; }
  if (is_aerodynamic() && (what == "is_aerodynamic")) { return true; }
  if (is_air_breather() && (what == "is_air_breather")) { return true; }
  if (is_alive_monst() && (what == "is_alive_monst")) { return true; }
  if (is_alive_on_end_of_anim() && (what == "is_alive_on_end_of_anim")) { return true; }
  if (is_always_hit() && (what == "is_always_hit")) { return true; }
  if (is_always_submerged_in_water() && (what == "is_always_submerged_in_water")) { return true; }
  if (is_amulet() && (what == "is_amulet")) { return true; }
  if (is_ant() && (what == "is_ant")) { return true; }
  if (is_aquatic() && (what == "is_aquatic")) { return true; }
  if (is_armor() && (what == "is_armor")) { return true; }
  if (is_ascend_dungeon() && (what == "is_ascend_dungeon")) { return true; }
  if (is_ascend_sewer() && (what == "is_ascend_sewer")) { return true; }
  if (is_asleep_initially() && (what == "is_asleep_initially")) { return true; }
  if (is_attackable_by_magic() && (what == "is_attackable_by_magic")) { return true; }
  if (is_attackable_by_monst() && (what == "is_attackable_by_monst")) { return true; }
  if (is_attackable_by_player() && (what == "is_attackable_by_player")) { return true; }
  if (is_auto_collect_item() && (what == "is_auto_collect_item")) { return true; }
  if (is_auto_equipped() && (what == "is_auto_equipped")) { return true; }
  if (is_auto_throw() && (what == "is_auto_throw")) { return true; }
  if (is_auto_use() && (what == "is_auto_use")) { return true; }
  if (is_bag_item_container() && (what == "is_bag_item_container")) { return true; }
  if (is_bag_item_not_stackable() && (what == "is_bag_item_not_stackable")) { return true; }
  if (is_bag_item() && (what == "is_bag_item")) { return true; }
  if (is_bag() && (what == "is_bag")) { return true; }
  if (is_barrel() && (what == "is_barrel")) { return true; }
  if (is_basalt() && (what == "is_basalt")) { return true; }
  if (is_bearowl() && (what == "is_bearowl")) { return true; }
  if (is_bedbug() && (what == "is_bedbug")) { return true; }
  if (is_bee() && (what == "is_bee")) { return true; }
  if (is_biome_dungeon() && (what == "is_biome_dungeon")) { return true; }
  if (is_biome_sewer() && (what == "is_biome_sewer")) { return true; }
  if (is_biome_swamp() && (what == "is_biome_swamp")) { return true; }
  if (is_biome_unused() && (what == "is_biome_unused")) { return true; }
  if (is_bleeder() && (what == "is_bleeder")) { return true; }
  if (is_block_of_ice() && (what == "is_block_of_ice")) { return true; }
  if (is_bones() && (what == "is_bones")) { return true; }
  if (is_boots() && (what == "is_boots")) { return true; }
  if (is_brazier() && (what == "is_brazier")) { return true; }
  if (is_bridge() && (what == "is_bridge")) { return true; }
  if (is_brittle() && (what == "is_brittle")) { return true; }
  if (is_buff() && (what == "is_buff")) { return true; }
  if (is_burnable() && (what == "is_burnable")) { return true; }
  if (is_carnivorous_plant() && (what == "is_carnivorous_plant")) { return true; }
  if (is_cautious() && (what == "is_cautious")) { return true; }
  if (is_centipede() && (what == "is_centipede")) { return true; }
  if (is_chasm() && (what == "is_chasm")) { return true; }
  if (is_cloak() && (what == "is_cloak")) { return true; }
  if (is_cold_elemental() && (what == "is_cold_elemental")) { return true; }
  if (is_cold() && (what == "is_cold")) { return true; }
  if (is_collectable() && (what == "is_collectable")) { return true; }
  if (is_collected_as_gold() && (what == "is_collected_as_gold")) { return true; }
  if (is_collected_as_keys() && (what == "is_collected_as_keys")) { return true; }
  if (is_combustible() && (what == "is_combustible")) { return true; }
  if (is_corpse() && (what == "is_corpse")) { return true; }
  if (is_corpse_with_bones() && (what == "is_corpse_with_bones")) { return true; }
  if (is_corridor() && (what == "is_corridor")) { return true; }
  if (is_cowardly() && (what == "is_cowardly")) { return true; }
  if (is_crab() && (what == "is_crab")) { return true; }
  if (is_critical_to_level() && (what == "is_critical_to_level")) { return true; }
  if (is_crushable() && (what == "is_crushable")) { return true; }
  if (is_crystal() && (what == "is_crystal")) { return true; }
  if (is_cursor_can_hover_over() && (what == "is_cursor_can_hover_over")) { return true; }
  if (is_cursor_can_hover_over_x2_click() && (what == "is_cursor_can_hover_over_x2_click")) { return true; }
  if (is_cursor_path_blocker() && (what == "is_cursor_path_blocker")) { return true; }
  if (is_cursor_path_hazard() && (what == "is_cursor_path_hazard")) { return true; }
  if (is_cursor_path() && (what == "is_cursor_path")) { return true; }
  if (is_cursor() && (what == "is_cursor")) { return true; }
  if (is_dagger() && (what == "is_dagger")) { return true; }
  if (is_daring() && (what == "is_daring")) { return true; }
  if (is_dead_on_end_of_anim() && (what == "is_dead_on_end_of_anim")) { return true; }
  if (is_dead_on_falling() && (what == "is_dead_on_falling")) { return true; }
  if (is_dead_on_shove() && (what == "is_dead_on_shove")) { return true; }
  if (is_death_hornet() && (what == "is_death_hornet")) { return true; }
  if (is_debuff() && (what == "is_debuff")) { return true; }
  if (is_debug_path() && (what == "is_debug_path")) { return true; }
  if (is_debug_type() && (what == "is_debug_type")) { return true; }
  if (is_deep_water() && (what == "is_deep_water")) { return true; }
  if (is_demon() && (what == "is_demon")) { return true; }
  if (is_descend_dungeon() && (what == "is_descend_dungeon")) { return true; }
  if (is_descend_sewer() && (what == "is_descend_sewer")) { return true; }
  if (is_described_when_hovering_over() && (what == "is_described_when_hovering_over")) { return true; }
  if (is_destroyed_on_hit_or_miss() && (what == "is_defeated _on_hit_and_still_alive_or_miss")) { return true; }
  if (is_destroyed_on_hitting() && (what == "is_defeated _on_hit_and_still_aliveting")) { return true; }
  if (is_dirt() && (what == "is_dirt")) { return true; }
  if (is_door() && (what == "is_door")) { return true; }
  if (is_droppable() && (what == "is_droppable")) { return true; }
  if (is_dry_grass_trampled() && (what == "dry_grass_trampled")) { return true; }
  if (is_dry_grass() && (what == "dry_grass")) { return true; }
  if (is_eater_of_amulets() && (what == "is_eater_of_amulets")) { return true; }
  if (is_eater_of_armor() && (what == "is_eater_of_armor")) { return true; }
  if (is_eater_of_blood() && (what == "is_eater_of_blood")) { return true; }
  if (is_eater_of_boots() && (what == "is_eater_of_boots")) { return true; }
  if (is_eater_of_cloaks() && (what == "is_eater_of_cloaks")) { return true; }
  if (is_eater_of_foliage() && (what == "is_eater_of_foliage")) { return true; }
  if (is_eater_of_food() && (what == "is_eater_of_food")) { return true; }
  if (is_eater_of_gauntlets() && (what == "is_eater_of_gauntlets")) { return true; }
  if (is_eater_of_grass() && (what == "is_eater_of_grass")) { return true; }
  if (is_eater_of_green_blood() && (what == "is_eater_of_green_blood")) { return true; }
  if (is_eater_of_helmets() && (what == "is_eater_of_helmets")) { return true; }
  if (is_eater_of_magical_items() && (what == "is_eater_of_magical_items")) { return true; }
  if (is_eater_of_meat() && (what == "is_eater_of_meat")) { return true; }
  if (is_eater_of_plants() && (what == "is_eater_of_plants")) { return true; }
  if (is_eater_of_potions() && (what == "is_eater_of_potions")) { return true; }
  if (is_eater_of_red_blood() && (what == "is_eater_of_red_blood")) { return true; }
  if (is_eater_of_rings() && (what == "is_eater_of_rings")) { return true; }
  if (is_eater_of_shields() && (what == "is_eater_of_shields")) { return true; }
  if (is_eater_of_slime() && (what == "is_eater_of_slime")) { return true; }
  if (is_eater_of_staffs() && (what == "is_eater_of_staffs")) { return true; }
  if (is_eater_of_treasure() && (what == "is_eater_of_treasure")) { return true; }
  if (is_eater_of_weapons() && (what == "is_eater_of_weapons")) { return true; }
  if (is_enchantable_as_a_group() && (what == "is_enchantable_as_a_group")) { return true; }
  if (is_enchantable() && (what == "is_enchantable")) { return true; }
  if (is_enchantstone() && (what == "is_enchantstone")) { return true; }
  if (is_engulfer() && (what == "is_engulfer")) { return true; }
  if (is_equippable() && (what == "is_equippable")) { return true; }
  if (is_ethereal_mob() && (what == "is_ethereal_mob")) { return true; }
  if (is_ethereal() && (what == "is_ethereal")) { return true; }
  if (is_ettin() && (what == "is_ettin")) { return true; }
  if (is_exit_finder() && (what == "is_exit_finder")) { return true; }
  if (is_explorer() && (what == "is_explorer")) { return true; }
  if (is_explosion() && (what == "is_explosion")) { return true; }
  if (is_fairy() && (what == "is_fairy")) { return true; }
  if (is_fearless() && (what == "is_fearless")) { return true; }
  if (is_fire_elemental() && (what == "is_fire_elemental")) { return true; }
  if (is_fire() && (what == "is_fire")) { return true; }
  if (is_flat() && (what == "is_flat")) { return true; }
  if (is_floating() && (what == "is_floating")) { return true; }
  if (is_floor_deco() && (what == "is_floor_deco")) { return true; }
  if (is_floor() && (what == "is_floor")) { return true; }
  if (is_flying() && (what == "is_flying")) { return true; }
  if (is_foliage() && (what == "is_foliage")) { return true; }
  if (is_food() && (what == "is_food")) { return true; }
  if (is_gas_blocker() && (what == "is_gas_blocker")) { return true; }
  if (is_gauntlet() && (what == "is_gauntlet")) { return true; }
  if (is_gelatinous() && (what == "is_gelatinous")) { return true; }
  if (is_glass() && (what == "is_glass")) { return true; }
  if (is_gnome() && (what == "is_gnome")) { return true; }
  if (is_goat() && (what == "is_goat")) { return true; }
  if (is_gold() && (what == "is_gold")) { return true; }
  if (is_golem() && (what == "is_golem")) { return true; }
  if (is_grass() && (what == "is_grass")) { return true; }
  if (is_green_blooded() && (what == "is_green_blooded")) { return true; }
  if (is_green_blood() && (what == "is_green_blood")) { return true; }
  if (is_green_splatter() && (what == "is_green_splatter")) { return true; }
  if (is_hard() && (what == "is_hard")) { return true; }
  if (is_hazard() && (what == "is_hazard")) { return true; }
  if (is_health_booster() && (what == "is_health_booster")) { return true; }
  if (is_heavy() && (what == "is_heavy")) { return true; }
  if (is_helmet() && (what == "is_helmet")) { return true; }
  if (is_herbivore() && (what == "is_herbivore")) { return true; }
  if (is_hittable() && (what == "is_hittable")) { return true; }
  if (is_humanoid() && (what == "is_humanoid")) { return true; }
  if (is_iceman() && (what == "is_iceman")) { return true; }
  if (is_immune_to_acid() && (what == "is_immune_to_acid")) { return true; }
  if (is_immune_to_cold() && (what == "is_immune_to_cold")) { return true; }
  if (is_immune_to_draining() && (what == "is_immune_to_draining")) { return true; }
  if (is_immune_to_electricity() && (what == "is_immune_to_electricity")) { return true; }
  if (is_immune_to_fire() && (what == "is_immune_to_fire")) { return true; }
  if (is_immune_to_necrosis() && (what == "is_immune_to_necrosis")) { return true; }
  if (is_immune_to_negation() && (what == "is_immune_to_negation")) { return true; }
  if (is_immune_to_poison() && (what == "is_immune_to_poison")) { return true; }
  if (is_immune_to_spiderwebs() && (what == "is_immune_to_spiderwebs")) { return true; }
  if (is_immune_to_teleport_attack() && (what == "is_immune_to_teleport_attack")) { return true; }
  if (is_immune_to_water() && (what == "is_immune_to_water")) { return true; }
  if (is_intelligent() && (what == "is_intelligent")) { return true; }
  if (is_interesting() && (what == "is_interesting")) { return true; }
  if (is_internal() && (what == "is_internal")) { return true; }
  if (is_invisible() && (what == "is_invisible")) { return true; }
  if (is_item_carrier() && (what == "is_item_carrier")) { return true; }
  if (is_item_collector() && (what == "is_item_collector")) { return true; }
  if (is_item_organic() && (what == "is_item_organic")) { return true; }
  if (is_item_targetted() && (what == "is_item_targetted")) { return true; }
  if (is_item() && (what == "is_item")) { return true; }
  if (is_key_special() && (what == "is_key_special")) { return true; }
  if (is_key() && (what == "is_key")) { return true; }
  if (is_laser() && (what == "is_laser")) { return true; }
  if (is_lava() && (what == "is_lava")) { return true; }
  if (is_leech() && (what == "is_leech")) { return true; }
  if (is_lifeless() && (what == "is_lifeless")) { return true; }
  if (is_light_blocker_for_monst() && (what == "is_light_blocker_for_monst")) { return true; }
  if (is_light_blocker() && (what == "is_light_blocker")) { return true; }
  if (is_lightning() && (what == "is_lightning")) { return true; }
  if (is_light() && (what == "is_light")) { return true; }
  if (is_limb() && (what == "is_limb")) { return true; }
  if (is_living() && (what == "is_living")) { return true; }
  if (is_loggable() && (what == "is_loggable")) { return true; }
  if (is_made_of_rock() && (what == "is_made_of_rock")) { return true; }
  if (is_magical_effect() && (what == "is_magical_effect")) { return true; }
  if (is_magical() && (what == "is_magical")) { return true; }
  if (is_mantisman() && (what == "is_mantisman")) { return true; }
  if (is_map_beast() && (what == "is_map_beast")) { return true; }
  if (is_meat() && (what == "is_meat")) { return true; }
  if (is_metal() && (what == "is_metal")) { return true; }
  if (is_mimic() && (what == "is_mimic")) { return true; }
  if (is_minion() && (what == "is_minion")) { return true; }
  if (is_missile() && (what == "is_missile")) { return true; }
  if (is_mob_challenge_class_A() && (what == "is_mob_challenge_class_A")) { return true; }
  if (is_mob_challenge_class_B() && (what == "is_mob_challenge_class_B")) { return true; }
  if (is_mob() && (what == "is_mob")) { return true; }
  if (is_molekin() && (what == "is_molekin")) { return true; }
  if (is_monst_class_A() && (what == "is_monst_class_A")) { return true; }
  if (is_monst_class_B() && (what == "is_monst_class_B")) { return true; }
  if (is_monst_class_C() && (what == "is_monst_class_C")) { return true; }
  if (is_monst_class_D() && (what == "is_monst_class_D")) { return true; }
  if (is_monst_class_E() && (what == "is_monst_class_E")) { return true; }
  if (is_monst_pack() && (what == "is_monst_pack")) { return true; }
  if (is_monst() && (what == "is_monst")) { return true; }
  if (is_moveable() && (what == "is_moveable")) { return true; }
  if (is_msg_allowed_hears_something() && (what == "is_msg_allowed_hears_something")) { return true; }
  if (is_msg_allowed_is_dead() && (what == "is_msg_allowed_is_dead")) { return true; }
  if (is_msg_allowed_is_seen() && (what == "is_msg_allowed_is_seen")) { return true; }
  if (is_msg_allowed_is_surprised() && (what == "is_msg_allowed_is_surprised")) { return true; }
  if (is_msg_allowed_is_wounded() && (what == "is_msg_allowed_is_wounded")) { return true; }
  if (is_msg_allowed_senses_danger() && (what == "is_msg_allowed_senses_danger")) { return true; }
  if (is_msg() && (what == "is_msg")) { return true; }
  if (is_necrotic_danger_level() && (what == "is_necrotic_danger_level")) { return true; }
  if (is_no_tile() && (what == "is_no_tile")) { return true; }
  if (is_obs_destructable() && (what == "is_obs_destructable")) { return true; }
  if (is_obs_for_jump_landing() && (what == "is_obs_for_jump_landing")) { return true; }
  if (is_obs_for_shoving() && (what == "is_obs_for_shoving")) { return true; }
  if (is_obsidian() && (what == "is_obsidian")) { return true; }
  if (is_obs_in_the_way_for_jumping() && (what == "is_obs_in_the_way_for_jumping")) { return true; }
  if (is_obs_in_the_way_for_shooting() && (what == "is_obs_in_the_way_for_shooting")) { return true; }
  if (is_obs_in_the_way_for_throwing() && (what == "is_obs_in_the_way_for_throwing")) { return true; }
  if (is_obs_wall_or_door() && (what == "is_obs_wall_or_door")) { return true; }
  if (is_obs_when_dead() && (what == "is_obs_when_dead")) { return true; }
  if (is_ogre() && (what == "is_ogre")) { return true; }
  if (is_openable() && (what == "is_openable")) { return true; }
  if (is_organic() && (what == "is_organic")) { return true; }
  if (is_pillar() && (what == "is_pillar")) { return true; }
  if (is_pirhana() && (what == "is_pirhana")) { return true; }
  if (is_plant() && (what == "is_plant")) { return true; }
  if (is_player() && (what == "is_player")) { return true; }
  if (is_poisonous_danger_level() && (what == "is_poisonous_danger_level")) { return true; }
  if (is_portal() && (what == "is_portal")) { return true; }
  if (is_potion() && (what == "is_potion")) { return true; }
  if (is_pressure_plate() && (what == "is_pressure_plate")) { return true; }
  if (is_projectile() && (what == "is_projectile")) { return true; }
  if (is_ranged_weapon() && (what == "is_ranged_weapon")) { return true; }
  if (is_rat() && (what == "is_rat")) { return true; }
  if (is_red_blooded() && (what == "is_red_blooded")) { return true; }
  if (is_red_blood() && (what == "is_red_blood")) { return true; }
  if (is_red_splatter() && (what == "is_red_splatter")) { return true; }
  if (is_removable_if_out_of_slots() && (what == "is_removable_if_out_of_slots")) { return true; }
  if (is_ring() && (what == "is_ring")) { return true; }
  if (is_ripple() && (what == "is_ripple")) { return true; }
  if (is_rock() && (what == "is_rock")) { return true; }
  if (is_rusty() && (what == "is_rusty")) { return true; }
  if (is_scorpion() && (what == "is_scorpion")) { return true; }
  if (is_secret_door() && (what == "is_secret_door")) { return true; }
  if (is_sewer_wall() && (what == "is_sewer_wall")) { return true; }
  if (is_shallow_water() && (what == "is_shallow_water")) { return true; }
  if (is_sheep() && (what == "is_sheep")) { return true; }
  if (is_shield() && (what == "is_shield")) { return true; }
  if (is_shovable_and_sticky() && (what == "is_shovable_and_sticky")) { return true; }
  if (is_shovable() && (what == "is_shovable")) { return true; }
  if (is_skillstone() && (what == "is_skillstone")) { return true; }
  if (is_skill() && (what == "is_skill")) { return true; }
  if (is_slime() && (what == "is_slime")) { return true; }
  if (is_slippery() && (what == "is_slippery")) { return true; }
  if (is_smoke() && (what == "is_smoke")) { return true; }
  if (is_snake() && (what == "is_snake")) { return true; }
  if (is_soft() && (what == "is_soft")) { return true; }
  if (is_spiderweb() && (what == "is_spiderweb")) { return true; }
  if (is_spider() && (what == "is_spider")) { return true; }
  if (is_splatter() && (what == "is_splatter")) { return true; }
  if (is_staff() && (what == "is_staff")) { return true; }
  if (is_steam() && (what == "is_steam")) { return true; }
  if (is_sticky() && (what == "is_sticky")) { return true; }
  if (is_stone() && (what == "is_stone")) { return true; }
  if (is_swimmer() && (what == "is_swimmer")) { return true; }
  if (is_sword() && (what == "is_sword")) { return true; }
  if (is_target_radial() && (what == "is_target_radial")) { return true; }
  if (is_target_select() && (what == "is_target_select")) { return true; }
  if (is_tentacle() && (what == "is_tentacle")) { return true; }
  if (is_thief() && (what == "is_thief")) { return true; }
  if (is_throwable() && (what == "is_throwable")) { return true; }
  if (is_thrown_as_a_weapon() && (what == "is_thrown_as_a_weapon")) { return true; }
  if (is_tickable() && (what == "is_tickable")) { return true; }
  if (is_tireless() && (what == "is_tireless")) { return true; }
  if (is_tmp_thing() && (what == "is_tmp_thing")) { return true; }
  if (is_torch() && (what == "is_torch")) { return true; }
  if (is_trap() && (what == "is_trap")) { return true; }
  if (is_treasure_chest() && (what == "is_treasure_chest")) { return true; }
  if (is_treasure_type() && (what == "is_treasure_type")) { return true; }
  if (is_treasure() && (what == "is_treasure")) { return true; }
  if (is_troll() && (what == "is_troll")) { return true; }
  if (is_undead() && (what == "is_undead")) { return true; }
  if (is_unused_flag100() && (what == "is_unused_flag100")) { return true; }
  if (is_unused_flag101() && (what == "is_unused_flag101")) { return true; }
  if (is_unused_flag102() && (what == "is_unused_flag102")) { return true; }
  if (is_unused_flag103() && (what == "is_unused_flag103")) { return true; }
  if (is_unused_flag104() && (what == "is_unused_flag104")) { return true; }
  if (is_unused_flag105() && (what == "is_unused_flag105")) { return true; }
  if (is_unused_flag106() && (what == "is_unused_flag106")) { return true; }
  if (is_unused_flag107() && (what == "is_unused_flag107")) { return true; }
  if (is_unused_flag108() && (what == "is_unused_flag108")) { return true; }
  if (is_unused_flag109() && (what == "is_unused_flag109")) { return true; }
  if (is_unused_flag10() && (what == "is_unused_flag10")) { return true; }
  if (is_unused_flag110() && (what == "is_unused_flag110")) { return true; }
  if (is_unused_flag111() && (what == "is_unused_flag111")) { return true; }
  if (is_unused_flag112() && (what == "is_unused_flag112")) { return true; }
  if (is_unused_flag113() && (what == "is_unused_flag113")) { return true; }
  if (is_unused_flag114() && (what == "is_unused_flag114")) { return true; }
  if (is_unused_flag115() && (what == "is_unused_flag115")) { return true; }
  if (is_unused_flag116() && (what == "is_unused_flag116")) { return true; }
  if (is_unused_flag117() && (what == "is_unused_flag117")) { return true; }
  if (is_unused_flag118() && (what == "is_unused_flag118")) { return true; }
  if (is_unused_flag119() && (what == "is_unused_flag119")) { return true; }
  if (is_unused_flag11() && (what == "is_unused_flag11")) { return true; }
  if (is_unused_flag120() && (what == "is_unused_flag120")) { return true; }
  if (is_unused_flag121() && (what == "is_unused_flag121")) { return true; }
  if (is_unused_flag122() && (what == "is_unused_flag122")) { return true; }
  if (is_unused_flag123() && (what == "is_unused_flag123")) { return true; }
  if (is_unused_flag124() && (what == "is_unused_flag124")) { return true; }
  if (is_unused_flag125() && (what == "is_unused_flag125")) { return true; }
  if (is_unused_flag126() && (what == "is_unused_flag126")) { return true; }
  if (is_unused_flag127() && (what == "is_unused_flag127")) { return true; }
  if (is_unused_flag128() && (what == "is_unused_flag128")) { return true; }
  if (is_unused_flag129() && (what == "is_unused_flag129")) { return true; }
  if (is_unused_flag12() && (what == "is_unused_flag12")) { return true; }
  if (is_unused_flag130() && (what == "is_unused_flag130")) { return true; }
  if (is_unused_flag131() && (what == "is_unused_flag131")) { return true; }
  if (is_unused_flag132() && (what == "is_unused_flag132")) { return true; }
  if (is_unused_flag133() && (what == "is_unused_flag133")) { return true; }
  if (is_unused_flag134() && (what == "is_unused_flag134")) { return true; }
  if (is_unused_flag135() && (what == "is_unused_flag135")) { return true; }
  if (is_unused_flag136() && (what == "is_unused_flag136")) { return true; }
  if (is_unused_flag137() && (what == "is_unused_flag137")) { return true; }
  if (is_unused_flag138() && (what == "is_unused_flag138")) { return true; }
  if (is_unused_flag139() && (what == "is_unused_flag139")) { return true; }
  if (is_unused_flag13() && (what == "is_unused_flag13")) { return true; }
  if (is_unused_flag140() && (what == "is_unused_flag140")) { return true; }
  if (is_unused_flag141() && (what == "is_unused_flag141")) { return true; }
  if (is_unused_flag142() && (what == "is_unused_flag142")) { return true; }
  if (is_unused_flag143() && (what == "is_unused_flag143")) { return true; }
  if (is_unused_flag144() && (what == "is_unused_flag144")) { return true; }
  if (is_unused_flag145() && (what == "is_unused_flag145")) { return true; }
  if (is_unused_flag146() && (what == "is_unused_flag146")) { return true; }
  if (is_unused_flag147() && (what == "is_unused_flag147")) { return true; }
  if (is_unused_flag148() && (what == "is_unused_flag148")) { return true; }
  if (is_unused_flag149() && (what == "is_unused_flag149")) { return true; }
  if (is_unused_flag14() && (what == "is_unused_flag14")) { return true; }
  if (is_unused_flag150() && (what == "is_unused_flag150")) { return true; }
  if (is_unused_flag151() && (what == "is_unused_flag151")) { return true; }
  if (is_unused_flag152() && (what == "is_unused_flag152")) { return true; }
  if (is_unused_flag153() && (what == "is_unused_flag153")) { return true; }
  if (is_unused_flag154() && (what == "is_unused_flag154")) { return true; }
  if (is_unused_flag155() && (what == "is_unused_flag155")) { return true; }
  if (is_unused_flag15() && (what == "is_unused_flag15")) { return true; }
  if (is_unused_flag16() && (what == "is_unused_flag16")) { return true; }
  if (is_unused_flag179() && (what == "is_unused_flag179")) { return true; }
  if (is_unused_flag17() && (what == "is_unused_flag17")) { return true; }
  if (is_unused_flag18() && (what == "is_unused_flag18")) { return true; }
  if (is_unused_flag192() && (what == "is_unused_flag192")) { return true; }
  if (is_unused_flag19() && (what == "is_unused_flag19")) { return true; }
  if (is_unused_flag1() && (what == "is_unused_flag1")) { return true; }
  if (is_unused_flag20() && (what == "is_unused_flag20")) { return true; }
  if (is_unused_flag21() && (what == "is_unused_flag21")) { return true; }
  if (is_unused_flag22() && (what == "is_unused_flag22")) { return true; }
  if (is_unused_flag23() && (what == "is_unused_flag23")) { return true; }
  if (is_unused_flag24() && (what == "is_unused_flag24")) { return true; }
  if (is_unused_flag25() && (what == "is_unused_flag25")) { return true; }
  if (is_unused_flag26() && (what == "is_unused_flag26")) { return true; }
  if (is_unused_flag27() && (what == "is_unused_flag27")) { return true; }
  if (is_unused_flag28() && (what == "is_unused_flag28")) { return true; }
  if (is_unused_flag29() && (what == "is_unused_flag29")) { return true; }
  if (is_unused_flag2() && (what == "is_unused_flag2")) { return true; }
  if (is_unused_flag30() && (what == "is_unused_flag30")) { return true; }
  if (is_unused_flag31() && (what == "is_unused_flag31")) { return true; }
  if (is_unused_flag32() && (what == "is_unused_flag32")) { return true; }
  if (is_unused_flag33() && (what == "is_unused_flag33")) { return true; }
  if (is_unused_flag34() && (what == "is_unused_flag34")) { return true; }
  if (is_unused_flag35() && (what == "is_unused_flag35")) { return true; }
  if (is_unused_flag36() && (what == "is_unused_flag36")) { return true; }
  if (is_unused_flag37() && (what == "is_unused_flag37")) { return true; }
  if (is_unused_flag38() && (what == "is_unused_flag38")) { return true; }
  if (is_unused_flag39() && (what == "is_unused_flag39")) { return true; }
  if (is_unused_flag3() && (what == "is_unused_flag3")) { return true; }
  if (is_unused_flag40() && (what == "is_unused_flag40")) { return true; }
  if (is_unused_flag41() && (what == "is_unused_flag41")) { return true; }
  if (is_unused_flag42() && (what == "is_unused_flag42")) { return true; }
  if (is_unused_flag43() && (what == "is_unused_flag43")) { return true; }
  if (is_unused_flag44() && (what == "is_unused_flag44")) { return true; }
  if (is_unused_flag45() && (what == "is_unused_flag45")) { return true; }
  if (is_unused_flag46() && (what == "is_unused_flag46")) { return true; }
  if (is_unused_flag47() && (what == "is_unused_flag47")) { return true; }
  if (is_unused_flag48() && (what == "is_unused_flag48")) { return true; }
  if (is_unused_flag49() && (what == "is_unused_flag49")) { return true; }
  if (is_unused_flag4() && (what == "is_unused_flag4")) { return true; }
  if (is_unused_flag50() && (what == "is_unused_flag50")) { return true; }
  if (is_unused_flag51() && (what == "is_unused_flag51")) { return true; }
  if (is_unused_flag52() && (what == "is_unused_flag52")) { return true; }
  if (is_unused_flag53() && (what == "is_unused_flag53")) { return true; }
  if (is_unused_flag54() && (what == "is_unused_flag54")) { return true; }
  if (is_unused_flag55() && (what == "is_unused_flag55")) { return true; }
  if (is_unused_flag56() && (what == "is_unused_flag56")) { return true; }
  if (is_unused_flag57() && (what == "is_unused_flag57")) { return true; }
  if (is_unused_flag58() && (what == "is_unused_flag58")) { return true; }
  if (is_unused_flag59() && (what == "is_unused_flag59")) { return true; }
  if (is_unused_flag5() && (what == "is_unused_flag5")) { return true; }
  if (is_unused_flag60() && (what == "is_unused_flag60")) { return true; }
  if (is_unused_flag61() && (what == "is_unused_flag61")) { return true; }
  if (is_unused_flag62() && (what == "is_unused_flag62")) { return true; }
  if (is_unused_flag63() && (what == "is_unused_flag63")) { return true; }
  if (is_unused_flag64() && (what == "is_unused_flag64")) { return true; }
  if (is_unused_flag65() && (what == "is_unused_flag65")) { return true; }
  if (is_unused_flag66() && (what == "is_unused_flag66")) { return true; }
  if (is_unused_flag67() && (what == "is_unused_flag67")) { return true; }
  if (is_unused_flag68() && (what == "is_unused_flag68")) { return true; }
  if (is_unused_flag69() && (what == "is_unused_flag69")) { return true; }
  if (is_unused_flag6() && (what == "is_unused_flag6")) { return true; }
  if (is_unused_flag70() && (what == "is_unused_flag70")) { return true; }
  if (is_unused_flag71() && (what == "is_unused_flag71")) { return true; }
  if (is_unused_flag72() && (what == "is_unused_flag72")) { return true; }
  if (is_unused_flag73() && (what == "is_unused_flag73")) { return true; }
  if (is_unused_flag74() && (what == "is_unused_flag74")) { return true; }
  if (is_unused_flag75() && (what == "is_unused_flag75")) { return true; }
  if (is_unused_flag76() && (what == "is_unused_flag76")) { return true; }
  if (is_unused_flag77() && (what == "is_unused_flag77")) { return true; }
  if (is_unused_flag78() && (what == "is_unused_flag78")) { return true; }
  if (is_unused_flag79() && (what == "is_unused_flag79")) { return true; }
  if (is_unused_flag7() && (what == "is_unused_flag7")) { return true; }
  if (is_unused_flag80() && (what == "is_unused_flag80")) { return true; }
  if (is_unused_flag81() && (what == "is_unused_flag81")) { return true; }
  if (is_unused_flag82() && (what == "is_unused_flag82")) { return true; }
  if (is_unused_flag83() && (what == "is_unused_flag83")) { return true; }
  if (is_unused_flag84() && (what == "is_unused_flag84")) { return true; }
  if (is_unused_flag85() && (what == "is_unused_flag85")) { return true; }
  if (is_unused_flag86() && (what == "is_unused_flag86")) { return true; }
  if (is_unused_flag87() && (what == "is_unused_flag87")) { return true; }
  if (is_unused_flag88() && (what == "is_unused_flag88")) { return true; }
  if (is_unused_flag89() && (what == "is_unused_flag89")) { return true; }
  if (is_unused_flag8() && (what == "is_unused_flag8")) { return true; }
  if (is_unused_flag90() && (what == "is_unused_flag90")) { return true; }
  if (is_unused_flag91() && (what == "is_unused_flag91")) { return true; }
  if (is_unused_flag92() && (what == "is_unused_flag92")) { return true; }
  if (is_unused_flag93() && (what == "is_unused_flag93")) { return true; }
  if (is_unused_flag94() && (what == "is_unused_flag94")) { return true; }
  if (is_unused_flag95() && (what == "is_unused_flag95")) { return true; }
  if (is_unused_flag96() && (what == "is_unused_flag96")) { return true; }
  if (is_unused_flag97() && (what == "is_unused_flag97")) { return true; }
  if (is_unused_flag98() && (what == "is_unused_flag98")) { return true; }
  if (is_unused_flag99() && (what == "is_unused_flag99")) { return true; }
  if (is_unused_flag9() && (what == "is_unused_flag9")) { return true; }
  if (is_usable() && (what == "is_usable")) { return true; }
  if (is_used_when_thrown() && (what == "is_used_when_thrown")) { return true; }
  if (is_very_combustible() && (what == "is_very_combustible")) { return true; }
  if (is_very_hard() && (what == "is_very_hard")) { return true; }
  if (is_very_heavy() && (what == "is_very_heavy")) { return true; }
  if (is_very_intelligent() && (what == "is_very_intelligent")) { return true; }
  if (is_wall_dungeon() && (what == "is_wall_dungeon")) { return true; }
  if (is_wall() && (what == "is_wall")) { return true; }
  if (is_weapon() && (what == "is_weapon")) { return true; }
  if (is_wet_grass_trampled() && (what == "is_wet_grass_trampled")) { return true; }
  if (is_wet_grass() && (what == "is_wet_grass")) { return true; }
  if (is_wooden() && (what == "is_wooden")) { return true; }
  if (is_yeti() && (what == "is_yeti")) { return true; }
  if (minion_limit() && (what == "minion_limit")) { return true; }
  if (noise_additional_on_jump_end() && (what == "noise_additional_on_jump_end")) { return true; }
  if (noise_additional_on_teleporting() && (what == "noise_additional_on_teleporting")) { return true; }
  if (noise_blocker() && (what == "noise_blocker")) { return true; }
  if (noise_decibels_hearing() && (what == "noise_decibels_hearing")) { return true; }
  if (noise_on_born() && (what == "noise_on_born")) { return true; }
  if (noise_on_dropping() && (what == "noise_on_dropping")) { return true; }
  if (noise_on_hit_and_now_dead() && (what == "noise_on_hit_and_now_dead")) { return true; }
  if (noise_on_hit_and_still_alive() && (what == "noise_on_hit_and_still_alive")) { return true; }
  if (noise_on_moving() && (what == "noise_on_moving")) { return true; }
  if (noise_on_open_or_close() && (what == "noise_on_open_or_close")) { return true; }
  if (on_death_is_stone() && (what == "on_death_is_stone")) { return true; }
  if (range_max() && (what == "range_max")) { return true; }
  if (shove_strength() && (what == "shove_strength")) { return true; }
  if (stat_att_penalty_when_idle_max() && (what == "stat_att_penalty_when_idle_max")) { return true; }
  if (stat_att_penalty_when_idle() && (what == "stat_att_penalty_when_idle")) { return true; }
  if (stat_att_penalty_when_in_deep_water() && (what == "stat_att_penalty_when_in_deep_water")) { return true; }
  if (stat_att_penalty_when_in_shallow_water() && (what == "stat_att_penalty_when_in_shallow_water")) { return true; }
  if (stat_att_penalty_when_stuck_max() && (what == "stat_att_penalty_when_stuck_max")) { return true; }
  if (stat_att_penalty_when_stuck() && (what == "stat_att_penalty_when_stuck")) { return true; }
  if (stat_def_penalty_when_idle_max() && (what == "stat_def_penalty_when_idle_max")) { return true; }
  if (stat_def_penalty_when_idle() && (what == "stat_def_penalty_when_idle")) { return true; }
  if (stat_def_penalty_when_in_deep_water() && (what == "stat_def_penalty_when_in_deep_water")) { return true; }
  if (stat_def_penalty_when_in_shallow_water() && (what == "stat_def_penalty_when_in_shallow_water")) { return true; }
  if (stat_def_penalty_when_stuck_max() && (what == "stat_def_penalty_when_stuck_max")) { return true; }
  if (stat_def_penalty_when_stuck() && (what == "stat_def_penalty_when_stuck")) { return true; }
  if (tick_prio() && (what == "tick_prio")) { return true; }
  // end sort marker2 }
  // clang-format on

  //
  // Any water type
  //
  if ((is_shallow_water() || is_deep_water()) && (what == "is_water")) {
    return true;
  }

  return (what == text_short_name());
}

std::function< int(Thingp) > Thing::matches_to_func(const std::string &what)
{
  // clang-format off
  // begin sort marker3 {
  if (what == "ai_detect_secret_doors") { return &Thing::ai_detect_secret_doors; }
  if (what == "ai_resent_count") { return &Thing::ai_resent_count; }
  if (what == "ai_wanderer") { return &Thing::ai_wanderer; }
  if (what == "attack_blood") { return &Thing::attack_blood; }
  if (what == "attack_eater") { return &Thing::attack_eater; }
  if (what == "attack_humanoid") { return &Thing::attack_humanoid; }
  if (what == "attack_living") { return &Thing::attack_living; }
  if (what == "attack_meat") { return &Thing::attack_meat; }
  if (what == "attack_no_msg") { return &Thing::attack_no_msg; }
  if (what == "attacks_per_round") { return &Thing::attacks_per_round; }
  if (what == "attack_undead") { return &Thing::attack_undead; }
  if (what == "collision_hit_180") { return &Thing::collision_hit_180; }
  if (what == "collision_hit_360") { return &Thing::collision_hit_360; }
  if (what == "collision_hit_adj") { return &Thing::collision_hit_adj; }
  if (what == "collision_hit_two_tiles_ahead") { return &Thing::collision_hit_two_tiles_ahead; }
  if (what == "consume_per_bite_amount") { return &Thing::consume_per_bite_amount; }
  if (what == "dmg_received_doubled_from_cold") { return &Thing::dmg_received_doubled_from_cold; }
  if (what == "dry_grass") { return &Thing::is_dry_grass; }
  if (what == "dry_grass_trampled") { return &Thing::is_dry_grass_trampled; }
  if (what == "enchant_max") { return &Thing::enchant_max; }
  if (what == "environ_dislikes_acid") { return &Thing::environ_dislikes_acid; }
  if (what == "environ_dislikes_cold") { return &Thing::environ_dislikes_cold; }
  if (what == "environ_dislikes_fire") { return &Thing::environ_dislikes_fire; }
  if (what == "environ_dislikes_necrosis") { return &Thing::environ_dislikes_necrosis; }
  if (what == "environ_dislikes_poison") { return &Thing::environ_dislikes_poison; }
  if (what == "environ_dislikes_water") { return &Thing::environ_dislikes_water; }
  if (what == "environ_hates_acid") { return &Thing::environ_hates_acid; }
  if (what == "environ_hates_cold") { return &Thing::environ_hates_cold; }
  if (what == "environ_hates_fire") { return &Thing::environ_hates_fire; }
  if (what == "environ_hates_necrosis") { return &Thing::environ_hates_necrosis; }
  if (what == "environ_hates_poison") { return &Thing::environ_hates_poison; }
  if (what == "environ_hates_water") { return &Thing::environ_hates_water; }
  if (what == "environ_likes_deep_water") { return &Thing::environ_likes_deep_water; }
  if (what == "environ_likes_lava") { return &Thing::environ_likes_lava; }
  if (what == "environ_likes_shallow_water") { return &Thing::environ_likes_shallow_water; }
  if (what == "gfx_pixelart_show_highlighted") { return &Thing::gfx_pixelart_show_highlighted; }
  if (what == "gfx_pixelart_show_square_outlined") { return &Thing::gfx_pixelart_show_square_outlined; }
  if (what == "hunger_is_insatiable") { return &Thing::hunger_is_insatiable; }
  if (what == "internal") { return &Thing::is_internal; }
  if (what == "is_able_to_amplify_footsteps") { return &Thing::is_able_to_amplify_footsteps; }
  if (what == "is_able_to_attack_mobs") { return &Thing::is_able_to_attack_mobs; }
  if (what == "is_able_to_attack_owner") { return &Thing::is_able_to_attack_owner; }
  if (what == "is_able_to_be_resurrected") { return &Thing::is_able_to_be_resurrected; }
  if (what == "is_able_to_be_surprised") { return &Thing::is_able_to_be_surprised; }
  if (what == "is_able_to_be_teleported") { return &Thing::is_able_to_be_teleported; }
  if (what == "is_able_to_break_down_doors") { return &Thing::is_able_to_break_down_doors; }
  if (what == "is_able_to_break_out_of_ice") { return &Thing::is_able_to_break_out_of_ice; }
  if (what == "is_able_to_break_out_of_webs") { return &Thing::is_able_to_break_out_of_webs; }
  if (what == "is_able_to_change_levels") { return &Thing::is_able_to_change_levels; }
  if (what == "is_able_to_collect_keys") { return &Thing::is_able_to_collect_keys; }
  if (what == "is_able_to_dampen_footsteps") { return &Thing::is_able_to_dampen_footsteps; }
  if (what == "is_able_to_enchant_items") { return &Thing::is_able_to_enchant_items; }
  if (what == "is_able_to_fall") { return &Thing::is_able_to_fall; }
  if (what == "is_able_to_follow") { return &Thing::is_able_to_follow; }
  if (what == "is_able_to_freeze") { return &Thing::is_able_to_freeze; }
  if (what == "is_able_to_grapple") { return &Thing::is_able_to_grapple; }
  if (what == "is_able_to_jump_attack") { return &Thing::is_able_to_jump_attack; }
  if (what == "is_able_to_jump_escape") { return &Thing::is_able_to_jump_escape; }
  if (what == "is_able_to_jump_onto") { return &Thing::is_able_to_jump_onto; }
  if (what == "is_able_to_jump") { return &Thing::is_able_to_jump; }
  if (what == "is_able_to_jump_without_tiring") { return &Thing::is_able_to_jump_without_tiring; }
  if (what == "is_able_to_learn_skills") { return &Thing::is_able_to_learn_skills; }
  if (what == "is_able_to_live_out_of_water") { return &Thing::is_able_to_live_out_of_water; }
  if (what == "is_able_to_lunge") { return &Thing::is_able_to_lunge; }
  if (what == "is_able_to_melt") { return &Thing::is_able_to_melt; }
  if (what == "is_able_to_move_diagonally") { return &Thing::is_able_to_move_diagonally; }
  if (what == "is_able_to_open_doors") { return &Thing::is_able_to_open_doors; }
  if (what == "is_able_to_regenerate") { return &Thing::is_able_to_regenerate; }
  if (what == "is_able_to_rest") { return &Thing::is_able_to_rest; }
  if (what == "is_able_to_run_away_after_stealing") { return &Thing::is_able_to_run_away_after_stealing; }
  if (what == "is_able_to_see_in_the_dark") { return &Thing::is_able_to_see_in_the_dark; }
  if (what == "is_able_to_see_invisible") { return &Thing::is_able_to_see_invisible; }
  if (what == "is_able_to_see_through_doors") { return &Thing::is_able_to_see_through_doors; }
  if (what == "is_able_to_shoot_at_close_range") { return &Thing::is_able_to_shoot_at_close_range; }
  if (what == "is_able_to_shoot_at") { return &Thing::is_able_to_shoot_at; }
  if (what == "is_able_to_shove") { return &Thing::is_able_to_shove; }
  if (what == "is_able_to_sleep") { return &Thing::is_able_to_sleep; }
  if (what == "is_able_to_spawn_things") { return &Thing::is_able_to_spawn_things; }
  if (what == "is_able_to_swim") { return &Thing::is_able_to_swim; }
  if (what == "is_able_to_teleport_attack") { return &Thing::is_able_to_teleport_attack; }
  if (what == "is_able_to_teleport_escape") { return &Thing::is_able_to_teleport_escape; }
  if (what == "is_able_to_teleport_self") { return &Thing::is_able_to_teleport_self; }
  if (what == "is_able_to_teleport_without_tiring") { return &Thing::is_able_to_teleport_without_tiring; }
  if (what == "is_able_to_tire") { return &Thing::is_able_to_tire; }
  if (what == "is_able_to_use_amulet") { return &Thing::is_able_to_use_amulet; }
  if (what == "is_able_to_use_armor") { return &Thing::is_able_to_use_armor; }
  if (what == "is_able_to_use_boots") { return &Thing::is_able_to_use_boots; }
  if (what == "is_able_to_use_cloak") { return &Thing::is_able_to_use_cloak; }
  if (what == "is_able_to_use_gauntlet") { return &Thing::is_able_to_use_gauntlet; }
  if (what == "is_able_to_use_helmet") { return &Thing::is_able_to_use_helmet; }
  if (what == "is_able_to_use_ranged_weapons") { return &Thing::is_able_to_use_ranged_weapons; }
  if (what == "is_able_to_use_rings") { return &Thing::is_able_to_use_rings; }
  if (what == "is_able_to_use_shield") { return &Thing::is_able_to_use_shield; }
  if (what == "is_able_to_use_staffs") { return &Thing::is_able_to_use_staffs; }
  if (what == "is_able_to_use_weapons") { return &Thing::is_able_to_use_weapons; }
  if (what == "is_able_to_walk_through_walls") { return &Thing::is_able_to_walk_through_walls; }
  if (what == "is_acid") { return &Thing::is_acid; }
  if (what == "is_aerodynamic") { return &Thing::is_aerodynamic; }
  if (what == "is_air_breather") { return &Thing::is_air_breather; }
  if (what == "is_alive_monst") { return &Thing::is_alive_monst; }
  if (what == "is_alive_on_end_of_anim") { return &Thing::is_alive_on_end_of_anim; }
  if (what == "is_always_hit") { return &Thing::is_always_hit; }
  if (what == "is_always_submerged_in_water") { return &Thing::is_always_submerged_in_water; }
  if (what == "is_amulet") { return &Thing::is_amulet; }
  if (what == "is_ant") { return &Thing::is_ant; }
  if (what == "is_aquatic") { return &Thing::is_aquatic; }
  if (what == "is_armor") { return &Thing::is_armor; }
  if (what == "is_ascend_dungeon") { return &Thing::is_ascend_dungeon; }
  if (what == "is_ascend_sewer") { return &Thing::is_ascend_sewer; }
  if (what == "is_asleep_initially") { return &Thing::is_asleep_initially; }
  if (what == "is_attackable_by_magic") { return &Thing::is_attackable_by_magic; }
  if (what == "is_attackable_by_monst") { return &Thing::is_attackable_by_monst; }
  if (what == "is_attackable_by_player") { return &Thing::is_attackable_by_player; }
  if (what == "is_auto_collect_item") { return &Thing::is_auto_collect_item; }
  if (what == "is_auto_equipped") { return &Thing::is_auto_equipped; }
  if (what == "is_auto_throw") { return &Thing::is_auto_throw; }
  if (what == "is_auto_use") { return &Thing::is_auto_use; }
  if (what == "is_bag_item_container") { return &Thing::is_bag_item_container; }
  if (what == "is_bag_item_not_stackable") { return &Thing::is_bag_item_not_stackable; }
  if (what == "is_bag_item") { return &Thing::is_bag_item; }
  if (what == "is_bag") { return &Thing::is_bag; }
  if (what == "is_barrel") { return &Thing::is_barrel; }
  if (what == "is_basalt") { return &Thing::is_basalt; }
  if (what == "is_bearowl") { return &Thing::is_bearowl; }
  if (what == "is_bedbug") { return &Thing::is_bedbug; }
  if (what == "is_bee") { return &Thing::is_bee; }
  if (what == "is_biome_dungeon") { return &Thing::is_biome_dungeon; }
  if (what == "is_biome_sewer") { return &Thing::is_biome_sewer; }
  if (what == "is_biome_swamp") { return &Thing::is_biome_swamp; }
  if (what == "is_biome_unused") { return &Thing::is_biome_unused; }
  if (what == "is_bleeder") { return &Thing::is_bleeder; }
  if (what == "is_block_of_ice") { return &Thing::is_block_of_ice; }
  if (what == "is_bones") { return &Thing::is_bones; }
  if (what == "is_boots") { return &Thing::is_boots; }
  if (what == "is_brazier") { return &Thing::is_brazier; }
  if (what == "is_bridge") { return &Thing::is_bridge; }
  if (what == "is_brittle") { return &Thing::is_brittle; }
  if (what == "is_buff") { return &Thing::is_buff; }
  if (what == "is_burnable") { return &Thing::is_burnable; }
  if (what == "is_carnivorous_plant") { return &Thing::is_carnivorous_plant; }
  if (what == "is_cautious") { return &Thing::is_cautious; }
  if (what == "is_centipede") { return &Thing::is_centipede; }
  if (what == "is_chasm") { return &Thing::is_chasm; }
  if (what == "is_cloak") { return &Thing::is_cloak; }
  if (what == "is_cold_elemental") { return &Thing::is_cold_elemental; }
  if (what == "is_cold") { return &Thing::is_cold; }
  if (what == "is_collectable") { return &Thing::is_collectable; }
  if (what == "is_collected_as_gold") { return &Thing::is_collected_as_gold; }
  if (what == "is_collected_as_keys") { return &Thing::is_collected_as_keys; }
  if (what == "is_combustible") { return &Thing::is_combustible; }
  if (what == "is_corpse") { return &Thing::is_corpse; }
  if (what == "is_corpse_with_bones") { return &Thing::is_corpse_with_bones; }
  if (what == "is_corridor") { return &Thing::is_corridor; }
  if (what == "is_cowardly") { return &Thing::is_cowardly; }
  if (what == "is_crab") { return &Thing::is_crab; }
  if (what == "is_critical_to_level") { return &Thing::is_critical_to_level; }
  if (what == "is_crushable") { return &Thing::is_crushable; }
  if (what == "is_crystal") { return &Thing::is_crystal; }
  if (what == "is_cursor_can_hover_over") { return &Thing::is_cursor_can_hover_over; }
  if (what == "is_cursor_can_hover_over_x2_click") { return &Thing::is_cursor_can_hover_over_x2_click; }
  if (what == "is_cursor_path_blocker") { return &Thing::is_cursor_path_blocker; }
  if (what == "is_cursor_path_hazard") { return &Thing::is_cursor_path_hazard; }
  if (what == "is_cursor_path") { return &Thing::is_cursor_path; }
  if (what == "is_cursor") { return &Thing::is_cursor; }
  if (what == "is_dagger") { return &Thing::is_dagger; }
  if (what == "is_daring") { return &Thing::is_daring; }
  if (what == "is_dead_on_end_of_anim") { return &Thing::is_dead_on_end_of_anim; }
  if (what == "is_dead_on_falling") { return &Thing::is_dead_on_falling; }
  if (what == "is_dead_on_shove") { return &Thing::is_dead_on_shove; }
  if (what == "is_death_hornet") { return &Thing::is_death_hornet; }
  if (what == "is_debuff") { return &Thing::is_debuff; }
  if (what == "is_debug_path") { return &Thing::is_debug_path; }
  if (what == "is_debug_type") { return &Thing::is_debug_type; }
  if (what == "is_deep_water") { return &Thing::is_deep_water; }
  if (what == "is_demon") { return &Thing::is_demon; }
  if (what == "is_descend_dungeon") { return &Thing::is_descend_dungeon; }
  if (what == "is_descend_sewer") { return &Thing::is_descend_sewer; }
  if (what == "is_described_when_hovering_over") { return &Thing::is_described_when_hovering_over; }
  if (what == "is_dirt") { return &Thing::is_dirt; }
  if (what == "is_door") { return &Thing::is_door; }
  if (what == "is_droppable") { return &Thing::is_droppable; }
  if (what == "is_eater_of_amulets") { return &Thing::is_eater_of_amulets; }
  if (what == "is_eater_of_armor") { return &Thing::is_eater_of_armor; }
  if (what == "is_eater_of_blood") { return &Thing::is_eater_of_blood; }
  if (what == "is_eater_of_boots") { return &Thing::is_eater_of_boots; }
  if (what == "is_eater_of_cloaks") { return &Thing::is_eater_of_cloaks; }
  if (what == "is_eater_of_foliage") { return &Thing::is_eater_of_foliage; }
  if (what == "is_eater_of_food") { return &Thing::is_eater_of_food; }
  if (what == "is_eater_of_gauntlets") { return &Thing::is_eater_of_gauntlets; }
  if (what == "is_eater_of_grass") { return &Thing::is_eater_of_grass; }
  if (what == "is_eater_of_green_blood") { return &Thing::is_eater_of_green_blood; }
  if (what == "is_eater_of_helmets") { return &Thing::is_eater_of_helmets; }
  if (what == "is_eater_of_magical_items") { return &Thing::is_eater_of_magical_items; }
  if (what == "is_eater_of_meat") { return &Thing::is_eater_of_meat; }
  if (what == "is_eater_of_plants") { return &Thing::is_eater_of_plants; }
  if (what == "is_eater_of_potions") { return &Thing::is_eater_of_potions; }
  if (what == "is_eater_of_red_blood") { return &Thing::is_eater_of_red_blood; }
  if (what == "is_eater_of_rings") { return &Thing::is_eater_of_rings; }
  if (what == "is_eater_of_shields") { return &Thing::is_eater_of_shields; }
  if (what == "is_eater_of_slime") { return &Thing::is_eater_of_slime; }
  if (what == "is_eater_of_staffs") { return &Thing::is_eater_of_staffs; }
  if (what == "is_eater_of_treasure") { return &Thing::is_eater_of_treasure; }
  if (what == "is_eater_of_weapons") { return &Thing::is_eater_of_weapons; }
  if (what == "is_enchantable_as_a_group") { return &Thing::is_enchantable_as_a_group; }
  if (what == "is_enchantable") { return &Thing::is_enchantable; }
  if (what == "is_enchantstone") { return &Thing::is_enchantstone; }
  if (what == "is_engulfer") { return &Thing::is_engulfer; }
  if (what == "is_equippable") { return &Thing::is_equippable; }
  if (what == "is_ethereal_mob") { return &Thing::is_ethereal_mob; }
  if (what == "is_ethereal") { return &Thing::is_ethereal; }
  if (what == "is_ettin") { return &Thing::is_ettin; }
  if (what == "is_exit_finder") { return &Thing::is_exit_finder; }
  if (what == "is_explorer") { return &Thing::is_explorer; }
  if (what == "is_explosion") { return &Thing::is_explosion; }
  if (what == "is_fairy") { return &Thing::is_fairy; }
  if (what == "is_fearless") { return &Thing::is_fearless; }
  if (what == "is_fire_elemental") { return &Thing::is_fire_elemental; }
  if (what == "is_fire") { return &Thing::is_fire; }
  if (what == "is_flat") { return &Thing::is_flat; }
  if (what == "is_floating") { return &Thing::is_floating; }
  if (what == "is_floor_deco") { return &Thing::is_floor_deco; }
  if (what == "is_floor") { return &Thing::is_floor; }
  if (what == "is_flying") { return &Thing::is_flying; }
  if (what == "is_foliage") { return &Thing::is_foliage; }
  if (what == "is_food") { return &Thing::is_food; }
  if (what == "is_gas_blocker") { return &Thing::is_gas_blocker; }
  if (what == "is_gauntlet") { return &Thing::is_gauntlet; }
  if (what == "is_gelatinous") { return &Thing::is_gelatinous; }
  if (what == "is_glass") { return &Thing::is_glass; }
  if (what == "is_gnome") { return &Thing::is_gnome; }
  if (what == "is_goat") { return &Thing::is_goat; }
  if (what == "is_gold") { return &Thing::is_gold; }
  if (what == "is_golem") { return &Thing::is_golem; }
  if (what == "is_grass") { return &Thing::is_grass; }
  if (what == "is_green_blooded") { return &Thing::is_green_blooded; }
  if (what == "is_green_blood") { return &Thing::is_green_blood; }
  if (what == "is_green_splatter") { return &Thing::is_green_splatter; }
  if (what == "is_hard") { return &Thing::is_hard; }
  if (what == "is_hazard") { return &Thing::is_hazard; }
  if (what == "is_health_booster") { return &Thing::is_health_booster; }
  if (what == "is_heavy") { return &Thing::is_heavy; }
  if (what == "is_helmet") { return &Thing::is_helmet; }
  if (what == "is_herbivore") { return &Thing::is_herbivore; }
  if (what == "is_hittable") { return &Thing::is_hittable; }
  if (what == "is_humanoid") { return &Thing::is_humanoid; }
  if (what == "is_iceman") { return &Thing::is_iceman; }
  if (what == "is_immune_to_acid") { return &Thing::is_immune_to_acid; }
  if (what == "is_immune_to_cold") { return &Thing::is_immune_to_cold; }
  if (what == "is_immune_to_draining") { return &Thing::is_immune_to_draining; }
  if (what == "is_immune_to_electricity") { return &Thing::is_immune_to_electricity; }
  if (what == "is_immune_to_fire") { return &Thing::is_immune_to_fire; }
  if (what == "is_immune_to_necrosis") { return &Thing::is_immune_to_necrosis; }
  if (what == "is_immune_to_negation") { return &Thing::is_immune_to_negation; }
  if (what == "is_immune_to_poison") { return &Thing::is_immune_to_poison; }
  if (what == "is_immune_to_spiderwebs") { return &Thing::is_immune_to_spiderwebs; }
  if (what == "is_immune_to_teleport_attack") { return &Thing::is_immune_to_teleport_attack; }
  if (what == "is_immune_to_water") { return &Thing::is_immune_to_water; }
  if (what == "is_intelligent") { return &Thing::is_intelligent; }
  if (what == "is_interesting") { return &Thing::is_interesting; }
  if (what == "is_invisible") { return &Thing::is_invisible; }
  if (what == "is_item_carrier") { return &Thing::is_item_carrier; }
  if (what == "is_item_collector") { return &Thing::is_item_collector; }
  if (what == "is_item_organic") { return &Thing::is_item_organic; }
  if (what == "is_item") { return &Thing::is_item; }
  if (what == "is_item_targetted") { return &Thing::is_item_targetted; }
  if (what == "is_key") { return &Thing::is_key; }
  if (what == "is_key_special") { return &Thing::is_key_special; }
  if (what == "is_laser") { return &Thing::is_laser; }
  if (what == "is_lava") { return &Thing::is_lava; }
  if (what == "is_leech") { return &Thing::is_leech; }
  if (what == "is_lifeless") { return &Thing::is_lifeless; }
  if (what == "is_light_blocker_for_monst") { return &Thing::is_light_blocker_for_monst; }
  if (what == "is_light_blocker") { return &Thing::is_light_blocker; }
  if (what == "is_lightning") { return &Thing::is_lightning; }
  if (what == "is_light") { return &Thing::is_light; }
  if (what == "is_limb") { return &Thing::is_limb; }
  if (what == "is_living") { return &Thing::is_living; }
  if (what == "is_loggable") { return &Thing::is_loggable; }
  if (what == "is_made_of_rock") { return &Thing::is_made_of_rock; }
  if (what == "is_magical_effect") { return &Thing::is_magical_effect; }
  if (what == "is_magical") { return &Thing::is_magical; }
  if (what == "is_mantisman") { return &Thing::is_mantisman; }
  if (what == "is_map_beast") { return &Thing::is_map_beast; }
  if (what == "is_meat") { return &Thing::is_meat; }
  if (what == "is_metal") { return &Thing::is_metal; }
  if (what == "is_mimic") { return &Thing::is_mimic; }
  if (what == "is_minion") { return &Thing::is_minion; }
  if (what == "is_missile") { return &Thing::is_missile; }
  if (what == "is_mob_challenge_class_A") { return &Thing::is_mob_challenge_class_A; }
  if (what == "is_mob_challenge_class_B") { return &Thing::is_mob_challenge_class_B; }
  if (what == "is_mob") { return &Thing::is_mob; }
  if (what == "is_molekin") { return &Thing::is_molekin; }
  if (what == "is_monst_class_A") { return &Thing::is_monst_class_A; }
  if (what == "is_monst_class_B") { return &Thing::is_monst_class_B; }
  if (what == "is_monst_class_C") { return &Thing::is_monst_class_C; }
  if (what == "is_monst_class_D") { return &Thing::is_monst_class_D; }
  if (what == "is_monst_class_E") { return &Thing::is_monst_class_E; }
  if (what == "is_monst_pack") { return &Thing::is_monst_pack; }
  if (what == "is_monst") { return &Thing::is_monst; }
  if (what == "is_moveable") { return &Thing::is_moveable; }
  if (what == "is_msg_allowed_hears_something") { return &Thing::is_msg_allowed_hears_something; }
  if (what == "is_msg_allowed_is_dead") { return &Thing::is_msg_allowed_is_dead; }
  if (what == "is_msg_allowed_is_seen") { return &Thing::is_msg_allowed_is_seen; }
  if (what == "is_msg_allowed_is_surprised") { return &Thing::is_msg_allowed_is_surprised; }
  if (what == "is_msg_allowed_is_wounded") { return &Thing::is_msg_allowed_is_wounded; }
  if (what == "is_msg_allowed_senses_danger") { return &Thing::is_msg_allowed_senses_danger; }
  if (what == "is_msg") { return &Thing::is_msg; }
  if (what == "is_necrotic_danger_level") { return &Thing::is_necrotic_danger_level; }
  if (what == "is_no_tile") { return &Thing::is_no_tile; }
  if (what == "is_obs_destructable") { return &Thing::is_obs_destructable; }
  if (what == "is_obs_for_shoving") { return &Thing::is_obs_for_shoving; }
  if (what == "is_obsidian") { return &Thing::is_obsidian; }
  if (what == "is_obs_in_the_way_for_jumping") { return &Thing::is_obs_in_the_way_for_jumping; }
  if (what == "is_obs_in_the_way_for_shooting") { return &Thing::is_obs_in_the_way_for_shooting; }
  if (what == "is_obs_in_the_way_for_throwing") { return &Thing::is_obs_in_the_way_for_throwing; }
  if (what == "is_obs_wall_or_door") { return &Thing::is_obs_wall_or_door; }
  if (what == "is_obs_when_dead") { return &Thing::is_obs_when_dead; }
  if (what == "is_ogre") { return &Thing::is_ogre; }
  if (what == "is_openable") { return &Thing::is_openable; }
  if (what == "is_organic") { return &Thing::is_organic; }
  if (what == "is_pillar") { return &Thing::is_pillar; }
  if (what == "is_pirhana") { return &Thing::is_pirhana; }
  if (what == "is_plant") { return &Thing::is_plant; }
  if (what == "is_player") { return &Thing::is_player; }
  if (what == "is_poisonous_danger_level") { return &Thing::is_poisonous_danger_level; }
  if (what == "is_portal") { return &Thing::is_portal; }
  if (what == "is_potion") { return &Thing::is_potion; }
  if (what == "is_pressure_plate") { return &Thing::is_pressure_plate; }
  if (what == "is_projectile") { return &Thing::is_projectile; }
  if (what == "is_ranged_weapon") { return &Thing::is_ranged_weapon; }
  if (what == "is_rat") { return &Thing::is_rat; }
  if (what == "is_red_blooded") { return &Thing::is_red_blooded; }
  if (what == "is_red_blood") { return &Thing::is_red_blood; }
  if (what == "is_red_splatter") { return &Thing::is_red_splatter; }
  if (what == "is_removable_if_out_of_slots") { return &Thing::is_removable_if_out_of_slots; }
  if (what == "is_ring") { return &Thing::is_ring; }
  if (what == "is_ripple") { return &Thing::is_ripple; }
  if (what == "is_rock") { return &Thing::is_rock; }
  if (what == "is_rusty") { return &Thing::is_rusty; }
  if (what == "is_scorpion") { return &Thing::is_scorpion; }
  if (what == "is_secret_door") { return &Thing::is_secret_door; }
  if (what == "is_sewer_wall") { return &Thing::is_sewer_wall; }
  if (what == "is_shallow_water") { return &Thing::is_shallow_water; }
  if (what == "is_sheep") { return &Thing::is_sheep; }
  if (what == "is_shield") { return &Thing::is_shield; }
  if (what == "is_shovable_and_sticky") { return &Thing::is_shovable_and_sticky; }
  if (what == "is_shovable") { return &Thing::is_shovable; }
  if (what == "is_skill") { return &Thing::is_skill; }
  if (what == "is_skillstone") { return &Thing::is_skillstone; }
  if (what == "is_slime") { return &Thing::is_slime; }
  if (what == "is_slippery") { return &Thing::is_slippery; }
  if (what == "is_smoke") { return &Thing::is_smoke; }
  if (what == "is_snake") { return &Thing::is_snake; }
  if (what == "is_soft") { return &Thing::is_soft; }
  if (what == "is_spider") { return &Thing::is_spider; }
  if (what == "is_spiderweb") { return &Thing::is_spiderweb; }
  if (what == "is_splatter") { return &Thing::is_splatter; }
  if (what == "is_staff") { return &Thing::is_staff; }
  if (what == "is_steam") { return &Thing::is_steam; }
  if (what == "is_sticky") { return &Thing::is_sticky; }
  if (what == "is_stone") { return &Thing::is_stone; }
  if (what == "is_swimmer") { return &Thing::is_swimmer; }
  if (what == "is_sword") { return &Thing::is_sword; }
  if (what == "is_target_radial") { return &Thing::is_target_radial; }
  if (what == "is_tentacle") { return &Thing::is_tentacle; }
  if (what == "is_thief") { return &Thing::is_thief; }
  if (what == "is_throwable") { return &Thing::is_throwable; }
  if (what == "is_thrown_as_a_weapon") { return &Thing::is_thrown_as_a_weapon; }
  if (what == "is_tickable") { return &Thing::is_tickable; }
  if (what == "is_tireless") { return &Thing::is_tireless; }
  if (what == "is_tmp_thing") { return &Thing::is_tmp_thing; }
  if (what == "is_torch") { return &Thing::is_torch; }
  if (what == "is_trap") { return &Thing::is_trap; }
  if (what == "is_treasure_chest") { return &Thing::is_treasure_chest; }
  if (what == "is_treasure") { return &Thing::is_treasure; }
  if (what == "is_treasure_type") { return &Thing::is_treasure_type; }
  if (what == "is_troll") { return &Thing::is_troll; }
  if (what == "is_undead") { return &Thing::is_undead; }
  if (what == "is_unused_flag100") { return &Thing::is_unused_flag100; }
  if (what == "is_unused_flag101") { return &Thing::is_unused_flag101; }
  if (what == "is_unused_flag102") { return &Thing::is_unused_flag102; }
  if (what == "is_unused_flag103") { return &Thing::is_unused_flag103; }
  if (what == "is_unused_flag104") { return &Thing::is_unused_flag104; }
  if (what == "is_unused_flag105") { return &Thing::is_unused_flag105; }
  if (what == "is_unused_flag106") { return &Thing::is_unused_flag106; }
  if (what == "is_unused_flag107") { return &Thing::is_unused_flag107; }
  if (what == "is_unused_flag108") { return &Thing::is_unused_flag108; }
  if (what == "is_unused_flag109") { return &Thing::is_unused_flag109; }
  if (what == "is_unused_flag10") { return &Thing::is_unused_flag10; }
  if (what == "is_unused_flag110") { return &Thing::is_unused_flag110; }
  if (what == "is_unused_flag111") { return &Thing::is_unused_flag111; }
  if (what == "is_unused_flag112") { return &Thing::is_unused_flag112; }
  if (what == "is_unused_flag113") { return &Thing::is_unused_flag113; }
  if (what == "is_unused_flag114") { return &Thing::is_unused_flag114; }
  if (what == "is_unused_flag115") { return &Thing::is_unused_flag115; }
  if (what == "is_unused_flag116") { return &Thing::is_unused_flag116; }
  if (what == "is_unused_flag117") { return &Thing::is_unused_flag117; }
  if (what == "is_unused_flag118") { return &Thing::is_unused_flag118; }
  if (what == "is_unused_flag119") { return &Thing::is_unused_flag119; }
  if (what == "is_unused_flag11") { return &Thing::is_unused_flag11; }
  if (what == "is_unused_flag120") { return &Thing::is_unused_flag120; }
  if (what == "is_unused_flag121") { return &Thing::is_unused_flag121; }
  if (what == "is_unused_flag122") { return &Thing::is_unused_flag122; }
  if (what == "is_unused_flag123") { return &Thing::is_unused_flag123; }
  if (what == "is_unused_flag124") { return &Thing::is_unused_flag124; }
  if (what == "is_unused_flag125") { return &Thing::is_unused_flag125; }
  if (what == "is_unused_flag126") { return &Thing::is_unused_flag126; }
  if (what == "is_unused_flag127") { return &Thing::is_unused_flag127; }
  if (what == "is_unused_flag128") { return &Thing::is_unused_flag128; }
  if (what == "is_unused_flag129") { return &Thing::is_unused_flag129; }
  if (what == "is_unused_flag12") { return &Thing::is_unused_flag12; }
  if (what == "is_unused_flag130") { return &Thing::is_unused_flag130; }
  if (what == "is_unused_flag131") { return &Thing::is_unused_flag131; }
  if (what == "is_unused_flag132") { return &Thing::is_unused_flag132; }
  if (what == "is_unused_flag133") { return &Thing::is_unused_flag133; }
  if (what == "is_unused_flag134") { return &Thing::is_unused_flag134; }
  if (what == "is_unused_flag135") { return &Thing::is_unused_flag135; }
  if (what == "is_unused_flag136") { return &Thing::is_unused_flag136; }
  if (what == "is_unused_flag137") { return &Thing::is_unused_flag137; }
  if (what == "is_unused_flag138") { return &Thing::is_unused_flag138; }
  if (what == "is_unused_flag139") { return &Thing::is_unused_flag139; }
  if (what == "is_unused_flag13") { return &Thing::is_unused_flag13; }
  if (what == "is_unused_flag140") { return &Thing::is_unused_flag140; }
  if (what == "is_unused_flag141") { return &Thing::is_unused_flag141; }
  if (what == "is_unused_flag142") { return &Thing::is_unused_flag142; }
  if (what == "is_unused_flag143") { return &Thing::is_unused_flag143; }
  if (what == "is_unused_flag144") { return &Thing::is_unused_flag144; }
  if (what == "is_unused_flag145") { return &Thing::is_unused_flag145; }
  if (what == "is_unused_flag146") { return &Thing::is_unused_flag146; }
  if (what == "is_unused_flag147") { return &Thing::is_unused_flag147; }
  if (what == "is_unused_flag148") { return &Thing::is_unused_flag148; }
  if (what == "is_unused_flag149") { return &Thing::is_unused_flag149; }
  if (what == "is_unused_flag14") { return &Thing::is_unused_flag14; }
  if (what == "is_unused_flag150") { return &Thing::is_unused_flag150; }
  if (what == "is_unused_flag151") { return &Thing::is_unused_flag151; }
  if (what == "is_unused_flag152") { return &Thing::is_unused_flag152; }
  if (what == "is_unused_flag153") { return &Thing::is_unused_flag153; }
  if (what == "is_unused_flag154") { return &Thing::is_unused_flag154; }
  if (what == "is_unused_flag155") { return &Thing::is_unused_flag155; }
  if (what == "is_unused_flag15") { return &Thing::is_unused_flag15; }
  if (what == "is_unused_flag16") { return &Thing::is_unused_flag16; }
  if (what == "is_unused_flag179") { return &Thing::is_unused_flag179; }
  if (what == "is_unused_flag17") { return &Thing::is_unused_flag17; }
  if (what == "is_unused_flag18") { return &Thing::is_unused_flag18; }
  if (what == "is_unused_flag192") { return &Thing::is_unused_flag192; }
  if (what == "is_unused_flag19") { return &Thing::is_unused_flag19; }
  if (what == "is_unused_flag1") { return &Thing::is_unused_flag1; }
  if (what == "is_unused_flag20") { return &Thing::is_unused_flag20; }
  if (what == "is_unused_flag21") { return &Thing::is_unused_flag21; }
  if (what == "is_unused_flag22") { return &Thing::is_unused_flag22; }
  if (what == "is_unused_flag23") { return &Thing::is_unused_flag23; }
  if (what == "is_unused_flag24") { return &Thing::is_unused_flag24; }
  if (what == "is_unused_flag25") { return &Thing::is_unused_flag25; }
  if (what == "is_unused_flag26") { return &Thing::is_unused_flag26; }
  if (what == "is_unused_flag27") { return &Thing::is_unused_flag27; }
  if (what == "is_unused_flag28") { return &Thing::is_unused_flag28; }
  if (what == "is_unused_flag29") { return &Thing::is_unused_flag29; }
  if (what == "is_unused_flag2") { return &Thing::is_unused_flag2; }
  if (what == "is_unused_flag30") { return &Thing::is_unused_flag30; }
  if (what == "is_unused_flag31") { return &Thing::is_unused_flag31; }
  if (what == "is_unused_flag32") { return &Thing::is_unused_flag32; }
  if (what == "is_unused_flag33") { return &Thing::is_unused_flag33; }
  if (what == "is_unused_flag34") { return &Thing::is_unused_flag34; }
  if (what == "is_unused_flag35") { return &Thing::is_unused_flag35; }
  if (what == "is_unused_flag36") { return &Thing::is_unused_flag36; }
  if (what == "is_unused_flag37") { return &Thing::is_unused_flag37; }
  if (what == "is_unused_flag38") { return &Thing::is_unused_flag38; }
  if (what == "is_unused_flag39") { return &Thing::is_unused_flag39; }
  if (what == "is_unused_flag3") { return &Thing::is_unused_flag3; }
  if (what == "is_unused_flag40") { return &Thing::is_unused_flag40; }
  if (what == "is_unused_flag41") { return &Thing::is_unused_flag41; }
  if (what == "is_unused_flag42") { return &Thing::is_unused_flag42; }
  if (what == "is_unused_flag43") { return &Thing::is_unused_flag43; }
  if (what == "is_unused_flag44") { return &Thing::is_unused_flag44; }
  if (what == "is_unused_flag45") { return &Thing::is_unused_flag45; }
  if (what == "is_unused_flag46") { return &Thing::is_unused_flag46; }
  if (what == "is_unused_flag47") { return &Thing::is_unused_flag47; }
  if (what == "is_unused_flag48") { return &Thing::is_unused_flag48; }
  if (what == "is_unused_flag49") { return &Thing::is_unused_flag49; }
  if (what == "is_unused_flag4") { return &Thing::is_unused_flag4; }
  if (what == "is_unused_flag50") { return &Thing::is_unused_flag50; }
  if (what == "is_unused_flag51") { return &Thing::is_unused_flag51; }
  if (what == "is_unused_flag52") { return &Thing::is_unused_flag52; }
  if (what == "is_unused_flag53") { return &Thing::is_unused_flag53; }
  if (what == "is_unused_flag54") { return &Thing::is_unused_flag54; }
  if (what == "is_unused_flag55") { return &Thing::is_unused_flag55; }
  if (what == "is_unused_flag56") { return &Thing::is_unused_flag56; }
  if (what == "is_unused_flag57") { return &Thing::is_unused_flag57; }
  if (what == "is_unused_flag58") { return &Thing::is_unused_flag58; }
  if (what == "is_unused_flag59") { return &Thing::is_unused_flag59; }
  if (what == "is_unused_flag5") { return &Thing::is_unused_flag5; }
  if (what == "is_unused_flag60") { return &Thing::is_unused_flag60; }
  if (what == "is_unused_flag61") { return &Thing::is_unused_flag61; }
  if (what == "is_unused_flag62") { return &Thing::is_unused_flag62; }
  if (what == "is_unused_flag63") { return &Thing::is_unused_flag63; }
  if (what == "is_unused_flag64") { return &Thing::is_unused_flag64; }
  if (what == "is_unused_flag65") { return &Thing::is_unused_flag65; }
  if (what == "is_unused_flag66") { return &Thing::is_unused_flag66; }
  if (what == "is_unused_flag67") { return &Thing::is_unused_flag67; }
  if (what == "is_unused_flag68") { return &Thing::is_unused_flag68; }
  if (what == "is_unused_flag69") { return &Thing::is_unused_flag69; }
  if (what == "is_unused_flag6") { return &Thing::is_unused_flag6; }
  if (what == "is_unused_flag70") { return &Thing::is_unused_flag70; }
  if (what == "is_unused_flag71") { return &Thing::is_unused_flag71; }
  if (what == "is_unused_flag72") { return &Thing::is_unused_flag72; }
  if (what == "is_unused_flag73") { return &Thing::is_unused_flag73; }
  if (what == "is_unused_flag74") { return &Thing::is_unused_flag74; }
  if (what == "is_unused_flag75") { return &Thing::is_unused_flag75; }
  if (what == "is_unused_flag76") { return &Thing::is_unused_flag76; }
  if (what == "is_unused_flag77") { return &Thing::is_unused_flag77; }
  if (what == "is_unused_flag78") { return &Thing::is_unused_flag78; }
  if (what == "is_unused_flag79") { return &Thing::is_unused_flag79; }
  if (what == "is_unused_flag7") { return &Thing::is_unused_flag7; }
  if (what == "is_unused_flag80") { return &Thing::is_unused_flag80; }
  if (what == "is_unused_flag81") { return &Thing::is_unused_flag81; }
  if (what == "is_unused_flag82") { return &Thing::is_unused_flag82; }
  if (what == "is_unused_flag83") { return &Thing::is_unused_flag83; }
  if (what == "is_unused_flag84") { return &Thing::is_unused_flag84; }
  if (what == "is_unused_flag85") { return &Thing::is_unused_flag85; }
  if (what == "is_unused_flag86") { return &Thing::is_unused_flag86; }
  if (what == "is_unused_flag87") { return &Thing::is_unused_flag87; }
  if (what == "is_unused_flag88") { return &Thing::is_unused_flag88; }
  if (what == "is_unused_flag89") { return &Thing::is_unused_flag89; }
  if (what == "is_unused_flag8") { return &Thing::is_unused_flag8; }
  if (what == "is_unused_flag90") { return &Thing::is_unused_flag90; }
  if (what == "is_unused_flag91") { return &Thing::is_unused_flag91; }
  if (what == "is_unused_flag92") { return &Thing::is_unused_flag92; }
  if (what == "is_unused_flag93") { return &Thing::is_unused_flag93; }
  if (what == "is_unused_flag94") { return &Thing::is_unused_flag94; }
  if (what == "is_unused_flag95") { return &Thing::is_unused_flag95; }
  if (what == "is_unused_flag96") { return &Thing::is_unused_flag96; }
  if (what == "is_unused_flag97") { return &Thing::is_unused_flag97; }
  if (what == "is_unused_flag98") { return &Thing::is_unused_flag98; }
  if (what == "is_unused_flag99") { return &Thing::is_unused_flag99; }
  if (what == "is_unused_flag9") { return &Thing::is_unused_flag9; }
  if (what == "is_usable") { return &Thing::is_usable; }
  if (what == "is_used_when_thrown") { return &Thing::is_used_when_thrown; }
  if (what == "is_very_combustible") { return &Thing::is_very_combustible; }
  if (what == "is_very_hard") { return &Thing::is_very_hard; }
  if (what == "is_very_heavy") { return &Thing::is_very_heavy; }
  if (what == "is_very_intelligent") { return &Thing::is_very_intelligent; }
  if (what == "is_wall_dungeon") { return &Thing::is_wall_dungeon; }
  if (what == "is_wall") { return &Thing::is_wall; }
  if (what == "is_water") { return &Thing::is_water; }
  if (what == "is_weapon") { return &Thing::is_weapon; }
  if (what == "is_wet_grass") { return &Thing::is_wet_grass; }
  if (what == "is_wet_grass_trampled") { return &Thing::is_wet_grass_trampled; }
  if (what == "is_wooden") { return &Thing::is_wooden; }
  if (what == "is_yeti") { return &Thing::is_yeti; }
  if (what == "minion_limit") { return &Thing::minion_limit; }
  if (what == "noise_additional_on_jump_end") { return &Thing::noise_additional_on_jump_end; }
  if (what == "noise_additional_on_teleporting") { return &Thing::noise_additional_on_teleporting; }
  if (what == "noise_blocker") { return &Thing::noise_blocker; }
  if (what == "noise_decibels_hearing") { return &Thing::noise_decibels_hearing; }
  if (what == "noise_on_born") { return &Thing::noise_on_born; }
  if (what == "noise_on_dropping") { return &Thing::noise_on_dropping; }
  if (what == "noise_on_hit_and_now_dead") { return &Thing::noise_on_hit_and_now_dead; }
  if (what == "noise_on_hit_and_still_alive") { return &Thing::noise_on_hit_and_still_alive; }
  if (what == "noise_on_moving") { return &Thing::noise_on_moving; }
  if (what == "noise_on_open_or_close") { return &Thing::noise_on_open_or_close; }
  if (what == "on_death_is_stone") { return &Thing::on_death_is_stone; }
  if (what == "range_max") { return &Thing::range_max; }
  if (what == "shove_strength") { return &Thing::shove_strength; }
  if (what == "stat_att_penalty_when_idle_max") { return &Thing::stat_att_penalty_when_idle_max; }
  if (what == "stat_att_penalty_when_idle") { return &Thing::stat_att_penalty_when_idle; }
  if (what == "stat_att_penalty_when_in_deep_water") { return &Thing::stat_att_penalty_when_in_deep_water; }
  if (what == "stat_att_penalty_when_in_shallow_water") { return &Thing::stat_att_penalty_when_in_shallow_water; }
  if (what == "stat_att_penalty_when_stuck_max") { return &Thing::stat_att_penalty_when_stuck_max; }
  if (what == "stat_att_penalty_when_stuck") { return &Thing::stat_att_penalty_when_stuck; }
  if (what == "stat_def_penalty_when_idle_max") { return &Thing::stat_def_penalty_when_idle_max; }
  if (what == "stat_def_penalty_when_idle") { return &Thing::stat_def_penalty_when_idle; }
  if (what == "stat_def_penalty_when_in_deep_water") { return &Thing::stat_def_penalty_when_in_deep_water; }
  if (what == "stat_def_penalty_when_in_shallow_water") { return &Thing::stat_def_penalty_when_in_shallow_water; }
  if (what == "stat_def_penalty_when_stuck_max") { return &Thing::stat_def_penalty_when_stuck_max; }
  if (what == "stat_def_penalty_when_stuck") { return &Thing::stat_def_penalty_when_stuck; }
  if (what == "tick_prio") { return &Thing::tick_prio; }
  // end sort marker3 }
  // clang-format on

  DIE("could not find a matches function for [%s]", what.c_str());
}
