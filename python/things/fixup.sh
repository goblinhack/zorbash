#!/bin/bash
#
# Adds default flags to all the templates and sorts them so it is easier to
# see what is missing or needs added.
#
# Use "do" as the first arg if the output looks sane.
#

PRE=$(mktemp) || exit 1
PAYLOAD=$(mktemp) || exit 1
POST=$(mktemp) || exit 1
OUT=$(mktemp) || exit 1

for IN in \
    armor/*py \
    amulets/*py \
    buffs/*py \
    boots/*py \
    gauntlets/*py \
    debuffs/*py \
    doors/*py \
    dungeon/*py \
    effects/*py \
    lasers/*py \
    projectiles/*py \
    food/*py \
    internal/*py \
    items/*py \
    mobs/*py \
    monsts/*py \
    player/*py \
    potions/*py \
    rings/*py \
    skills/*py \
    treasure/*py \
    wands/*py \
    weapons/*py
do
    echo $IN

    grep -q is_pack $IN
    if [ $? -eq 0 ]; then
        continue
    fi

    sed '1,/self = tp.Tp(/!d' $IN > $PRE
    sed '/self = tp.Tp(/,/z_prio(/!d' $IN | tail -n +2 - | sort > $PAYLOAD
    sed '/z_prio(/,$!d' $IN | tail -n +2 - > $POST

    for arg in \
      aggression_level_pct_set \
      ai_detect_secret_doors_set \
      ai_obstacle_set \
      ai_resent_count_set \
      ai_wanderer_set \
      attack_eater_set \
      attack_humanoid_set \
      attack_living_set \
      attack_lunge_set \
      attack_meat_set \
      attack_undead_set \
      collateral_damage_pct_set \
      collision_check_set \
      collision_hit_priority_set \
      damage_received_doubled_from_acid_set \
      damage_received_doubled_from_fire_set \
      damage_received_doubled_from_necrosis_set \
      damage_received_doubled_from_poison_set \
      damage_received_doubled_from_water_set \
      distance_leader_max_set \
      distance_minion_vision_shared_set \
      enchant_level_set \
      enchant_max_set \
      environ_avoids_acid_set \
      environ_avoids_fire_set \
      environ_avoids_necrosis_set \
      environ_avoids_poison_set \
      environ_avoids_water_set \
      is_immune_to_acid_set \
      is_immune_to_fire_set \
      is_immune_to_necrosis_set \
      is_immune_to_poison_set \
      is_immune_to_spiderwebs_set \
      is_immune_to_water_set \
      gfx_an_animation_only_set \
      gfx_animated_set \
      gfx_animated_can_hflip_set \
      gfx_animated_can_vflip_set \
      gfx_animated_no_dir_set \
      gfx_attack_anim_set \
      gfx_bounce_always_set \
      gfx_bounce_on_move_set \
      gfx_dead_anim_set \
      gfx_equip_carry_anim_set \
      gfx_flickers_set \
      gfx_glows_set \
      gfx_health_bar_autohide_set \
      gfx_health_bar_shown_set \
      gfx_long_shadow_caster_set \
      gfx_on_fire_anim_set \
      gfx_oversized_and_on_floor_set \
      gfx_shown_in_bg_set \
      gfx_show_outlined_set \
      gfx_solid_shadow_set \
      gfx_very_short_shadow_caster_set \
      gfx_water_set \
      hunger_clock_tick_freq_set \
      hunger_is_insatiable_set \
      is_able_to_attack_mobs_set \
      is_able_to_break_down_doors_set \
      is_able_to_break_out_of_webs_set \
      is_able_to_change_levels_set \
      is_able_to_collect_keys_set \
      is_able_to_enchant_items_set \
      is_able_to_fall_set \
      is_able_to_fire_at_set \
      is_able_to_follow_set \
      is_able_to_jump_set \
      is_able_to_jump_attack_set \
      is_able_to_jump_escape_set \
      is_able_to_jump_onto_set \
      is_able_to_jump_without_tiring_set \
      is_able_to_learn_skills_set \
      is_able_to_open_doors_set \
      is_able_to_see_in_the_dark_set \
      is_able_to_see_through_doors_set \
      is_able_to_shove_set \
      is_able_to_tire_set \
      is_able_to_use_armor_set \
      is_able_to_use_rings_set \
      is_able_to_use_wands_or_staffs_set \
      is_able_to_use_weapons_set \
      is_able_to_walk_through_walls_set \
      is_acid_set \
      is_alive_on_end_of_anim_set \
      is_always_hit_set \
      is_aquatic_set \
      is_armor_set \
      is_ascend_dungeon_set \
      is_ascend_sewer_set \
      is_attackable_by_monst_set \
      is_attackable_by_player_set \
      is_auto_collect_item_set \
      is_auto_equipped_set \
      is_auto_throw_set \
      is_auto_use_set \
      is_bag_set \
      is_bag_item_set \
      is_bag_item_container_set \
      is_bag_item_not_stackable_set \
      is_barrel_set \
      is_map_beast_set \
      is_bleeder_set \
      is_red_blood_set \
      is_red_blood_eater_set \
      is_red_splatter_set \
      is_bones_set \
      is_corpse_with_bones_set \
      is_brazier_set \
      is_bridge_set \
      is_buff_set \
      is_burnable_set \
      is_carrier_of_treasure_class_a_set \
      is_carrier_of_treasure_class_b_set \
      is_carrier_of_treasure_class_c_set \
      is_carrier_of_weapon_class_a_set \
      is_carrier_of_weapon_class_b_set \
      is_carrier_of_weapon_class_c_set \
      is_chasm_set \
      is_collectable_set \
      is_collect_as_keys_set \
      is_collected_as_gold_set \
      is_combustible_set \
      is_corpse_on_death_set \
      is_corridor_set \
      is_critical_to_level_set \
      is_crushable_set \
      is_cursor_set \
      is_cursor_can_hover_over_set \
      is_cursor_can_hover_over_x2_click_set \
      is_cursor_path_set \
      is_cursor_path_hazard_for_player_set \
      is_dead_on_end_of_anim_set \
      is_dead_on_shove_set \
      is_debuff_set \
      is_debug_path_set \
      is_debug_type_set \
      is_deep_water_set \
      is_descend_dungeon_set \
      is_descend_sewer_set \
      is_described_when_hovering_over_set \
      is_destroyed_on_hit_or_miss_set \
      is_destroyed_on_hitting_set \
      is_dirt_set \
      is_door_set \
      is_droppable_set \
      is_dry_grass_set \
      is_enchantable_set \
      is_enchantstone_set \
      is_engulfer_set \
      is_ethereal_set \
      is_ethereal_mob_set \
      is_exit_finder_set \
      is_explorer_set \
      is_explosion_set \
      is_fearless_set \
      is_fire_set \
      is_floating_set \
      is_floor_set \
      is_floor_deco_set \
      is_flying_set \
      is_foilage_set \
      is_food_set \
      is_food_eater_set \
      is_gfx_anim_synced_with_owner_set \
      is_glass_set \
      is_gold_set \
      is_green_blooded_set \
      is_green_splatter_set \
      is_hazard_set \
      is_health_booster_set \
      is_heavy_set \
      is_hittable_set \
      is_humanoid_set \
      is_toughness_very_hard_set \
      is_intelligent_set \
      is_interesting_set \
      is_item_set \
      is_item_carrier_set \
      is_item_collector_set \
      is_item_eater_set \
      is_item_magical_set \
      is_item_magical_eater_set \
      is_item_organic_set \
      is_jelly_set \
      is_jelly_baby_set \
      is_jelly_baby_eater_set \
      is_jelly_eater_set \
      is_jelly_parent_set \
      is_key_set \
      is_laser_set \
      is_lava_set \
      is_light_blocker_set \
      is_living_set \
      is_loggable_set \
      is_meat_set \
      is_meat_eater_set \
      is_metal_set \
      is_minion_set \
      is_mob_set \
      is_monst_set \
      is_moveable_set \
      is_msg_set \
      is_necrotic_danger_level_set \
      is_no_tile_set \
      is_obs_destructable_set \
      is_obs_wall_or_door_set \
      is_openable_set \
      is_organic_set \
      is_pink_blooded_set \
      is_pink_splatter_set \
      is_player_set \
      is_poisonous_danger_level_set \
      is_potion_set \
      is_potion_eater_set \
      is_projectile_set \
      is_red_blooded_set \
      is_removeable_if_out_of_slots_set \
      is_resurrectable_set \
      is_ring_set \
      is_ripple_set \
      is_rock_set \
      is_rusty_set \
      is_secret_door_set \
      is_sewer_wall_set \
      is_shallow_water_set \
      is_shovable_set \
      is_skill_set \
      is_skillstone_set \
      is_slippery_set \
      is_smoke_set \
      is_toughness_soft_set \
      is_spawner_set \
      is_spider_set \
      is_spiderweb_set \
      is_sticky_set \
      is_stone_set \
      is_sword_set \
      is_target_select_set \
      is_the_grid_set \
      is_throwable_set \
      is_tickable_set \
      is_tmp_thing_set \
      is_torch_set \
      is_treasure_chest_set \
      is_treasure_class_a_set \
      is_treasure_class_b_set \
      is_treasure_class_c_set \
      is_treasure_eater_set \
      is_map_treasure_set \
      is_treasure_type_set \
      is_undead_set \
      is_usable_set \
      is_used_when_thrown_set \
      is_very_is_combustible_set \
      is_wall_set \
      is_wall_dungeon_set \
      is_wand_set \
      is_weapon_set \
      is_wooden_set \
      normal_placement_rules_set \
      on_death_drop_all_items_set \
      spawn_group_radius_set \
      unused_flag1_set \
      unused_flag2_set \
      unused_flag3_set \
      unused_flag4_set \
      unused_flag5_set \
      unused_flag6_set \
      unused_flag7_set \
      unused_flag8_set \
      unused_flag9_set \
      unused_flag10_set \
      unused_flag11_set \
      unused_flag12_set \
      unused_flag13_set \
      unused_flag14_set \
      unused_flag15_set \
      unused_flag16_set \
      unused_flag17_set \
      unused_flag18_set \
      unused_flag19_set \
      unused_flag20_set \
      unused_flag21_set \
      unused_flag22_set \
      unused_flag23_set \
      unused_flag24_set \
      unused_flag25_set \
      unused_flag26_set \
      unused_flag27_set \
      unused_flag28_set \
      unused_flag29_set \
      unused_flag30_set \
      unused_flag31_set \
      unused_flag32_set \
      unused_flag33_set \
      unused_flag34_set \
      unused_flag35_set \
      unused_flag36_set \
      unused_flag37_set \
      unused_flag38_set \
      unused_flag39_set \
      unused_flag40_set \
      unused_flag41_set \
      unused_flag42_set \
      unused_flag43_set \
      unused_flag44_set \
      unused_flag45_set \
      unused_flag46_set \
      unused_flag47_set \
      unused_flag48_set \
      unused_flag49_set \
      unused_flag50_set \
      unused_flag51_set \
      unused_flag52_set \
      unused_flag53_set \
      unused_flag54_set \
      unused_flag55_set \
      unused_flag56_set \
      unused_flag57_set \
      unused_flag58_set \
      unused_flag59_set \
      unused_flag60_set \
      unused_flag61_set \
      unused_flag62_set \
      unused_flag63_set \
      unused_flag64_set \
      unused_flag65_set \
      unused_flag66_set \
      unused_flag67_set \
      unused_flag68_set \
      unused_flag69_set \
      unused_flag70_set \
      unused_flag71_set \
      unused_flag72_set \
      unused_flag73_set \
      unused_flag74_set \
      unused_flag75_set \
      unused_flag76_set \
      unused_flag77_set \
      unused_flag78_set \
      unused_flag79_set \
      unused_flag80_set \
      unused_flag81_set \
      unused_flag82_set \
      unused_flag83_set \
      unused_flag84_set \
      unused_flag85_set \
      unused_flag86_set \
      unused_flag87_set \
      unused_flag88_set \
      unused_flag89_set \
      unused_flag90_set \
      unused_flag91_set \
      unused_flag92_set \
      unused_flag93_set \
      unused_flag94_set \
      unused_flag95_set \
      unused_flag96_set \
      unused_flag97_set \
      unused_flag98_set \
      unused_flag99_set \
      unused_flag100_set \
      unused_flag101_set \
      unused_flag102_set \
      unused_flag103_set \
      unused_flag104_set \
      unused_flag105_set \
      unused_flag106_set \
      unused_flag107_set \
      damage_num_attacks_set \
      is_key_special_set \
      is_crystal_set \
      noise_on_moving_set \
      is_tireless_set \
      shove_strength_set \
      gfx_wobbles_when_hit_set \
      is_snake_set \
      is_item_targetted_set \
      noise_additional_on_teleporting_set \
      is_able_to_jump_attack_chance_d1000_set \
      teleport_distance_set \
      is_able_to_teleport_attack_set \
      is_able_to_teleport_without_tiring_set \
      is_able_to_teleport_escape_set \
      unused_flag123_set \
      is_pack_set \
      is_pillar_set \
      is_able_to_walk_through_walls_set \
      collision_hit_two_tiles_ahead_set \
      is_flat_set \
      is_target_radial_set \
      is_staff_set \
      collision_hit_adj_set \
      collision_hit_180_set \
      stamina_drain_on_swinging_set \
      collision_hit_360_set \
      is_dead_on_falling_set \
      is_temperature_sensitive_set \
      move_speed_set \
      damage_received_doubled_from_cold_set \
      is_cold_set \
      is_temperature_change_sensitive_set \
      temperature_set \
      is_very_heavy_set \
      gfx_health_bar_shown_when_awake_only_set \
      gfx_show_asleep_set \
      noise_additional_on_jump_end_set \
      noise_on_born_set \
      noise_on_open_set \
      noise_on_you_are_hit_and_now_dead_set \
      noise_on_you_are_hit_but_still_alive_set \
      noise_decibels_hearing_set \
      noise_blocker_set \
      is_immune_to_cold_set \
      is_breather_set \
      noise_on_dropping_set \
      is_asleep_initially_set \
      is_able_to_sleep_set \
      is_obstacle_when_dead_set \
      is_gas_blocker_set \
      is_light_blocker_for_monst_set \
      is_pink_blood_eater_set \
      is_green_blood_set \
      is_biome_swamp_set \
      is_biome_dungeon_set \
      is_treasure_set \
      is_monst_class_e_set \
      is_green_blood_eater_set \
      is_mob_challenge_class_b_set \
      is_mob_challenge_class_a_set \
      is_monst_class_d_set \
      is_monst_class_c_set \
      is_monst_class_b_set \
      is_monst_class_a_set \
      stat_att_penalty_when_in_deep_water_set \
      stat_att_penalty_when_in_shallow_water_set \
      stat_att_penalty_when_idle_max_set \
      stat_att_penalty_when_idle_set \
      stat_att_penalty_when_stuck_set \
      stat_att_penalty_when_stuck_max_set \
      stat_def_penalty_when_stuck_max_set \
      stat_def_penalty_when_idle_max_set \
      stat_def_penalty_when_in_deep_water_set \
      stat_def_penalty_when_in_shallow_water_set \
      stat_def_penalty_when_stuck_set \
      stat_def_penalty_when_idle_set \
      is_able_to_move_diagonally_set \
      is_meltable_set \
      is_amulet_set \
      is_able_to_use_amulet_set \
      is_able_to_use_helmet_set \
      is_able_to_use_boots_set \
      is_able_to_use_cloak_set \
      is_able_to_use_shield_set \
      is_able_to_use_gauntlet_set \
      is_able_to_use_helmet_set \
      is_helmet_set \
      is_boots_set \
      is_shield_set \
      is_cloak_set \
      is_gauntlet_set \
      is_toughness_hard_set \
      on_death_is_open_set
    do
        grep -q $arg $PAYLOAD
        # Too much noise
        #if [ $? -ne 0 ]; then
        #  echo "    my.tp_$arg(self, False)" >> $PAYLOAD
        #fi
    done

    sort $PAYLOAD | uniq > $PAYLOAD.tmp
    mv $PAYLOAD.tmp $PAYLOAD

    cat $PRE $PAYLOAD $POST > $OUT

    diff $OUT $IN

    if [ "$1" = "do" ]; then
        mv $OUT $IN
    fi

done
