import my


class Tp:
    """thing template"""

    def __init__(self, name, text_name=None, short_text_name=None):
        self.name = name

        if text_name is None:
            self.text_name = name
        else:
            self.text_name = text_name

        if short_text_name is None:
            self.short_text_name = self.text_name
        else:
            self.short_text_name = short_text_name

        #
        # Load it into the game engine
        #
        my.tp_load(self)

    def update(self):
        my.tp_update(self)

    def set_tile(self, tile=None, **kw):
        my.tp_set_tile(self, tile, **kw)

    def set_left1_tile(self, left1_tile=None, **kw):
        my.tp_set_left1_tile(self, left1_tile, **kw)

    def set_right1_tile(self, right1_tile=None, **kw):
        my.tp_set_right1_tile(self, right1_tile, **kw)

    def set_bot1_tile(self, bot1_tile=None, **kw):
        my.tp_set_bot1_tile(self, bot1_tile, **kw)

    def set_top1_tile(self, top1_tile=None, **kw):
        my.tp_set_top1_tile(self, top1_tile, **kw)

    def set_tl1_tile(self, tl1_tile=None, **kw):
        my.tp_set_tl1_tile(self, tl1_tile, **kw)

    def set_tr1_tile(self, tr1_tile=None, **kw):
        my.tp_set_tr1_tile(self, tr1_tile, **kw)

    def set_br1_tile(self, br1_tile=None, **kw):
        my.tp_set_br1_tile(self, br1_tile, **kw)

    def set_bl1_tile(self, bl1_tile=None, **kw):
        my.tp_set_bl1_tile(self, bl1_tile, **kw)

    def set_left2_tile(self, left2_tile=None, **kw):
        my.tp_set_left2_tile(self, left2_tile, **kw)

    def set_right2_tile(self, right2_tile=None, **kw):
        my.tp_set_right2_tile(self, right2_tile, **kw)

    def set_bot2_tile(self, bot2_tile=None, **kw):
        my.tp_set_bot2_tile(self, bot2_tile, **kw)

    def set_bot3_tile(self, bot3_tile=None, **kw):
        my.tp_set_bot3_tile(self, bot3_tile, **kw)

    def set_top2_tile(self, top2_tile=None, **kw):
        my.tp_set_top2_tile(self, top2_tile, **kw)

    def set_tl2_tile(self, tl2_tile=None, **kw):
        my.tp_set_tl2_tile(self, tl2_tile, **kw)

    def set_tr2_tile(self, tr2_tile=None, **kw):
        my.tp_set_tr2_tile(self, tr2_tile, **kw)

    def set_br2_tile(self, br2_tile=None, **kw):
        my.tp_set_br2_tile(self, br2_tile, **kw)

    def set_bl2_tile(self, bl2_tile=None, **kw):
        my.tp_set_bl2_tile(self, bl2_tile, **kw)

    def set_name(self, value):
        my.tp_set_name(self, value)

    def set_short_name(self, value):
        my.tp_set_short_name(self, value)

    def set_blit_top_off(self, value):
        my.tp_set_blit_top_off(self, value)

    def set_blit_bot_off(self, value):
        my.tp_set_blit_bot_off(self, value)

    def set_blit_left_off(self, value):
        my.tp_set_blit_left_off(self, value)

    def set_blit_right_off(self, value):
        my.tp_set_blit_right_off(self, value)

    def set_gfx_animated(self, value):
        my.tp_set_gfx_animated(self, value)

    def set_gfx_animated_no_dir(self, value):
        my.tp_set_gfx_animated_no_dir(self, value)

    def set_gfx_an_animation_only(self, value):
        my.tp_set_gfx_an_animation_only(self, value)

    def set_gfx_on_fire_anim(self, value):
        my.tp_set_gfx_on_fire_anim(self, value)

    def set_is_monst(self, value):
        my.tp_set_is_monst(self, value)

    def set_is_key(self, value):
        my.tp_set_is_key(self, value)

    def set_is_floor_deco(self, value):
        my.tp_set_is_floor_deco(self, value)

    def set_is_ascend_sewer(self, value):
        my.tp_set_is_ascend_sewer(self, value)

    def set_is_player(self, value):
        my.tp_set_is_player(self, value)

    def set_str1(self, value):
        my.tp_set_str1(self, value)

    def set_str_str2(self, value):
        my.tp_set_str_str2(self, value)

    def set_text_enchant(self, value):
        my.tp_set_text_enchant(self, value)

    def set_text_skill(self, value):
        my.tp_set_text_skill(self, value)

    def set_text_debuff(self, value):
        my.tp_set_text_debuff(self, value)

    def set_text_buff(self, value):
        my.tp_set_text_buff(self, value)

    def set_str_str4(self, value):
        my.tp_set_str_str4(self, value)

    def set_str_is_allied_with(self, value):
        my.tp_set_str_is_allied_with(self, value)

    def set_str_projectile_name(self, value):
        my.tp_set_str_projectile_name(self, value)

    def set_laser_name(self, value):
        my.tp_set_laser_name(self, value)

    def set_projectile_name(self, value):
        my.tp_set_projectile_name(self, value)

    def set_long_text_description(self, value):
        my.tp_set_long_text_description(self, value)

    def set_long_text_description_extra(self, value):
        my.tp_set_long_text_description_extra(self, value)

    def set_text_unused1(self, value):
        my.tp_set_text_unused1(self, value)

    def set_text_unused2(self, value):
        my.tp_set_text_unused2(self, value)

    def set_text_description(self, value):
        my.tp_set_text_description(self, value)

    def set_text_unused(self, value):
        my.tp_set_text_unused(self, value)

    def set_on_birth_do(self, value):
        my.tp_set_on_birth_do(self, value)

    def set_on_polymorphed_do(self, value):
        my.tp_set_on_polymorphed_do(self, value)

    def set_on_use_do(self, value):
        my.tp_set_on_use_do(self, value)

    def set_on_final_use_do(self, value):
        my.tp_set_on_final_use_do(self, value)

    def set_on_equip_do(self, value):
        my.tp_set_on_equip_do(self, value)

    def set_on_unequip_do(self, value):
        my.tp_set_on_unequip_do(self, value)

    def set_on_owner_set_do(self, value):
        my.tp_set_on_owner_set_do(self, value)

    def set_on_owner_unset_do(self, value):
        my.tp_set_on_owner_unset_do(self, value)

    def set_on_you_are_declared_leader_do(self, value):
        my.tp_set_on_you_are_declared_leader_do(self, value)

    def set_on_death_of_my_leader_do(self, value):
        my.tp_set_on_death_of_my_leader_do(self, value)

    def set_on_owner_damage_poison_do(self, value):
        my.tp_set_on_owner_damage_poison_do(self, value)

    def set_on_you_are_declared_a_follower_do(self, value):
        my.tp_set_on_you_are_declared_a_follower_do(self, value)

    def set_on_death_of_a_follower_do(self, value):
        my.tp_set_on_death_of_a_follower_do(self, value)

    def set_on_owner_damage_future1_do(self, value):
        my.tp_set_on_owner_damage_future1_do(self, value)

    def set_on_owner_damage_future2_do(self, value):
        my.tp_set_on_owner_damage_future2_do(self, value)

    def set_on_owner_damage_future3_do(self, value):
        my.tp_set_on_owner_damage_future3_do(self, value)

    def set_on_owner_damage_future4_do(self, value):
        my.tp_set_on_owner_damage_future4_do(self, value)

    def set_on_owner_damage_fire_do(self, value):
        my.tp_set_on_owner_damage_fire_do(self, value)

    def set_on_owner_damage_crush_do(self, value):
        my.tp_set_on_owner_damage_crush_do(self, value)

    def set_on_owner_damage_lightning_do(self, value):
        my.tp_set_on_owner_damage_lightning_do(self, value)

    def set_on_owner_damage_energy_do(self, value):
        my.tp_set_on_owner_damage_energy_do(self, value)

    def set_on_owner_damage_acid_do(self, value):
        my.tp_set_on_owner_damage_acid_do(self, value)

    def set_on_owner_damage_digest_do(self, value):
        my.tp_set_on_owner_damage_digest_do(self, value)

    def set_on_owner_damage_constitution_do(self, value):
        my.tp_set_on_owner_damage_constitution_do(self, value)

    def set_on_owner_damage_strength_do(self, value):
        my.tp_set_on_owner_damage_strength_do(self, value)

    def set_on_owner_damage_melee_do(self, value):
        my.tp_set_on_owner_damage_melee_do(self, value)

    def set_on_owner_damage_necrosis_do(self, value):
        my.tp_set_on_owner_damage_necrosis_do(self, value)

    def set_on_owner_damage_bite_do(self, value):
        my.tp_set_on_owner_damage_bite_do(self, value)

    def set_on_damage_poison_do(self, value):
        my.tp_set_on_damage_poison_do(self, value)

    def set_on_damage_future1_do(self, value):
        my.tp_set_on_damage_future1_do(self, value)

    def set_on_damage_future2_do(self, value):
        my.tp_set_on_damage_future2_do(self, value)

    def set_on_damage_future3_do(self, value):
        my.tp_set_on_damage_future3_do(self, value)

    def set_on_damage_future4_do(self, value):
        my.tp_set_on_damage_future4_do(self, value)

    def set_on_damage_fire_do(self, value):
        my.tp_set_on_damage_fire_do(self, value)

    def set_on_damage_crush_do(self, value):
        my.tp_set_on_damage_crush_do(self, value)

    def set_on_damage_lightning_do(self, value):
        my.tp_set_on_damage_lightning_do(self, value)

    def set_on_damage_energy_do(self, value):
        my.tp_set_on_damage_energy_do(self, value)

    def set_on_damage_acid_do(self, value):
        my.tp_set_on_damage_acid_do(self, value)

    def set_on_damage_digest_do(self, value):
        my.tp_set_on_damage_digest_do(self, value)

    def set_on_damage_constitution_do(self, value):
        my.tp_set_on_damage_constitution_do(self, value)

    def set_on_damage_strength_do(self, value):
        my.tp_set_on_damage_strength_do(self, value)

    def set_on_damage_melee_do(self, value):
        my.tp_set_on_damage_melee_do(self, value)

    def set_on_damage_necrosis_do(self, value):
        my.tp_set_on_damage_necrosis_do(self, value)

    def set_on_damage_bite_do(self, value):
        my.tp_set_on_damage_bite_do(self, value)

    def set_on_you_are_hit_but_still_alive_do(self, value):
        my.tp_set_on_you_are_hit_but_still_alive_do(self, value)

    def set_on_you_are_hit_and_now_dead_do(self, value):
        my.tp_set_on_you_are_hit_and_now_dead_do(self, value)

    def set_on_you_miss_do(self, value):
        my.tp_set_on_you_miss_do(self, value)

    def set_on_fall_do(self, value):
        my.tp_set_on_fall_do(self, value)

    def set_on_enchant_do(self, value):
        my.tp_set_on_enchant_do(self, value)

    def set_on_you_are_on_fire_do(self, value):
        my.tp_set_on_you_are_on_fire_do(self, value)

    def set_on_firing_at_something_do(self, value):
        my.tp_set_on_firing_at_something_do(self, value)

    def set_on_tick_do(self, value):
        my.tp_set_on_tick_do(self, value)

    def set_on_lifespan_tick_do(self, value):
        my.tp_set_on_lifespan_tick_do(self, value)

    def set_on_you_bite_attack_do(self, value):
        my.tp_set_on_you_bite_attack_do(self, value)

    def set_on_death_do(self, value):
        my.tp_set_on_death_do(self, value)

    def set_on_born_do(self, value):
        my.tp_set_on_born_do(self, value)

    def set_on_move_do(self, value):
        my.tp_set_on_move_do(self, value)

    def set_on_open_do(self, value):
        my.tp_set_on_open_do(self, value)

    def set_text_title(self, value):
        my.tp_set_text_title(self, value)

    def set_on_idle_tick_frequency_dice(self, value):
        my.tp_set_on_idle_tick_frequency_dice(self, value)

    def set_spawn_group_size_dice(self, value):
        my.tp_set_spawn_group_size_dice(self, value)

    def set_text_hits(self, value):
        my.tp_set_text_hits(self, value)

    def set_text_natural_attack_type(self, value):
        my.tp_set_text_natural_attack_type(self, value)

    def set_spawn_on_shoved(self, value):
        my.tp_set_spawn_on_shoved(self, value)

    def set_text_a_or_an(self, value):
        my.tp_set_text_a_or_an(self, value)

    def set_text_name(self, value):
        my.tp_set_text_name(self, value)

    def set_light_color(self, value):
        my.tp_set_light_color(self, value)

    def set_equip_carry_anim(self, value):
        my.tp_set_equip_carry_anim(self, value)

    def set_gfx_anim_use(self, value):
        my.tp_set_gfx_anim_use(self, value)

    def set_unused_flag1(self, value):
        my.tp_set_unused_flag1(self, value)

    def set_unused_flag2(self, value):
        my.tp_set_unused_flag2(self, value)

    def set_unused_flag3(self, value):
        my.tp_set_unused_flag3(self, value)

    def set_unused_flag4(self, value):
        my.tp_set_unused_flag4(self, value)

    def set_unused_flag5(self, value):
        my.tp_set_unused_flag5(self, value)

    def set_is_beast_map(self, value):
        my.tp_set_is_beast_map(self, value)

    def set_is_treasure_map(self, value):
        my.tp_set_is_treasure_map(self, value)

    def set_is_able_to_use_wands(self, value):
        my.tp_set_is_able_to_use_wands(self, value)

    def set_is_aquatic(self, value):
        my.tp_set_is_aquatic(self, value)

    def set_is_able_to_jump_escape(self, value):
        my.tp_set_is_able_to_jump_escape(self, value)

    def set_hunger_clock_tick_frequency(self, value):
        my.tp_set_hunger_clock_tick_frequency(self, value)

    def set_is_able_to_follow(self, value):
        my.tp_set_is_able_to_follow(self, value)

    def set_distance_leader_max(self, value):
        my.tp_set_distance_leader_max(self, value)

    def set_distance_recruitment_max(self, value):
        my.tp_set_distance_recruitment_max(self, value)

    def set_spawn_group_radius(self, value):
        my.tp_set_spawn_group_radius(self, value)

    def set_distance_minion_vision_shared(self, value):
        my.tp_set_distance_minion_vision_shared(self, value)

    def set_is_able_to_use_weapons(self, value):
        my.tp_set_is_able_to_use_weapons(self, value)

    def set_is_bony(self, value):
        my.tp_set_is_bony(self, value)

    def set_is_pink_blooded(self, value):
        my.tp_set_is_pink_blooded(self, value)

    def set_is_pink_splatter(self, value):
        my.tp_set_is_pink_splatter(self, value)

    def set_is_green_splatter(self, value):
        my.tp_set_is_green_splatter(self, value)

    def set_is_red_blooded(self, value):
        my.tp_set_is_red_blooded(self, value)

    def set_is_green_blooded(self, value):
        my.tp_set_is_green_blooded(self, value)

    def set_is_able_to_jump_without_tiring(self, value):
        my.tp_set_is_able_to_jump_without_tiring(self, value)

    def set_is_spider(self, value):
        my.tp_set_is_spider(self, value)

    def set_is_able_to_jump_attack(self, value):
        my.tp_set_is_able_to_jump_attack(self, value)

    def set_is_able_to_jump_onto(self, value):
        my.tp_set_is_able_to_jump_onto(self, value)

    def set_is_crushable(self, value):
        my.tp_set_is_crushable(self, value)

    def set_birthplace_leas(self, value):
        my.tp_set_birthplace_leas(self, value)

    def set_aggression_level_pct(self, value):
        my.tp_set_aggression_level_pct(self, value)

    def set_collateral_damage_pct(self, value):
        my.tp_set_collateral_damage_pct(self, value)

    def set_is_able_to_see_in_the_dark(self, value):
        my.tp_set_is_able_to_see_in_the_dark(self, value)

    def set_is_gfx_anim_synced_with_owner(self, value):
        my.tp_set_is_gfx_anim_synced_with_owner(self, value)

    def set_is_item_magical(self, value):
        my.tp_set_is_item_magical(self, value)

    def set_is_heavy(self, value):
        my.tp_set_is_heavy(self, value)

    def set_is_ring(self, value):
        my.tp_set_is_ring(self, value)

    def set_is_auto_equipped(self, value):
        my.tp_set_is_auto_equipped(self, value)

    def set_is_buff(self, value):
        my.tp_set_is_buff(self, value)

    def set_is_debuff(self, value):
        my.tp_set_is_debuff(self, value)

    def set_attack_undead(self, value):
        my.tp_set_attack_undead(self, value)

    def set_is_blood_eater(self, value):
        my.tp_set_is_blood_eater(self, value)

    def set_attack_blood(self, value):
        my.tp_set_attack_blood(self, value)

    def set_environ_avoids_water(self, value):
        my.tp_set_environ_avoids_water(self, value)

    def set_environ_avoids_acid(self, value):
        my.tp_set_environ_avoids_acid(self, value)

    def set_ai_detect_secret_doors(self, value):
        my.tp_set_ai_detect_secret_doors(self, value)

    def set_is_able_to_break_down_doors(self, value):
        my.tp_set_is_able_to_break_down_doors(self, value)

    def set_is_able_to_break_out_of_webs(self, value):
        my.tp_set_is_able_to_break_out_of_webs(self, value)

    def set_is_able_to_open_doors(self, value):
        my.tp_set_is_able_to_open_doors(self, value)

    def set_is_exit_finder(self, value):
        my.tp_set_is_exit_finder(self, value)

    def set_is_explorer(self, value):
        my.tp_set_is_explorer(self, value)

    def set_is_rusty(self, value):
        my.tp_set_is_rusty(self, value)

    def set_is_able_to_learn_skills(self, value):
        my.tp_set_is_able_to_learn_skills(self, value)

    def set_is_able_to_enchant_items(self, value):
        my.tp_set_is_able_to_enchant_items(self, value)

    def set_is_able_to_attack_mobs(self, value):
        my.tp_set_is_able_to_attack_mobs(self, value)

    def set_ai_wanderer(self, value):
        my.tp_set_ai_wanderer(self, value)

    def set_is_organic(self, value):
        my.tp_set_is_organic(self, value)

    def set_is_glass(self, value):
        my.tp_set_is_glass(self, value)

    def set_is_stone(self, value):
        my.tp_set_is_stone(self, value)

    def set_is_item_organic(self, value):
        my.tp_set_is_item_organic(self, value)

    def set_is_metal(self, value):
        my.tp_set_is_metal(self, value)

    def set_is_wooden(self, value):
        my.tp_set_is_wooden(self, value)

    def set_is_engulfer(self, value):
        my.tp_set_is_engulfer(self, value)

    def set_is_health_booster(self, value):
        my.tp_set_is_health_booster(self, value)

    def set_is_tmp_thing(self, value):
        my.tp_set_is_tmp_thing(self, value)

    def set_is_debug_type(self, value):
        my.tp_set_is_debug_type(self, value)

    def set_is_hittable(self, value):
        my.tp_set_is_hittable(self, value)

    def set_is_alive_on_end_of_anim(self, value):
        my.tp_set_is_alive_on_end_of_anim(self, value)

    def set_is_dead_on_end_of_anim(self, value):
        my.tp_set_is_dead_on_end_of_anim(self, value)

    def set_ai_resent_count(self, value):
        my.tp_set_ai_resent_count(self, value)

    def set_is_debug_path(self, value):
        my.tp_set_is_debug_path(self, value)

    def set_is_able_to_collect_keys(self, value):
        my.tp_set_is_able_to_collect_keys(self, value)

    def set_is_item_collector(self, value):
        my.tp_set_is_item_collector(self, value)

    def set_is_item(self, value):
        my.tp_set_is_item(self, value)

    def set_is_bag_item_container(self, value):
        my.tp_set_is_bag_item_container(self, value)

    def set_is_treasure_chest(self, value):
        my.tp_set_is_treasure_chest(self, value)

    def set_is_openable(self, value):
        my.tp_set_is_openable(self, value)

    def set_gfx_long_shadow_caster(self, value):
        my.tp_set_gfx_long_shadow_caster(self, value)

    def set_gfx_solid_shadow(self, value):
        my.tp_set_gfx_solid_shadow(self, value)

    def set_is_sticky(self, value):
        my.tp_set_is_sticky(self, value)

    def set_is_sword(self, value):
        my.tp_set_is_sword(self, value)

    def set_is_skillstone(self, value):
        my.tp_set_is_skillstone(self, value)

    def set_enchant_level(self, value):
        my.tp_set_enchant_level(self, value)

    def set_enchant_max(self, value):
        my.tp_set_enchant_max(self, value)

    def set_is_enchantstone(self, value):
        my.tp_set_is_enchantstone(self, value)

    def set_is_enchantable(self, value):
        my.tp_set_is_enchantable(self, value)

    def set_is_indestructible(self, value):
        my.tp_set_is_indestructible(self, value)

    def set_is_bones(self, value):
        my.tp_set_is_bones(self, value)

    def set_is_allied_with(self, value):
        my.tp_set_is_allied_with(self, value)

    def set_is_soft_body(self, value):
        my.tp_set_is_soft_body(self, value)

    def set_is_foilage(self, value):
        my.tp_set_is_foilage(self, value)

    def set_is_spiderweb(self, value):
        my.tp_set_is_spiderweb(self, value)

    def set_gfx_very_short_shadow_caster(self, value):
        my.tp_set_gfx_very_short_shadow_caster(self, value)

    def set_is_dry_grass(self, value):
        my.tp_set_is_dry_grass(self, value)

    def set_is_bridge(self, value):
        my.tp_set_is_bridge(self, value)

    def set_is_barrel(self, value):
        my.tp_set_is_barrel(self, value)

    def set_is_burnable(self, value):
        my.tp_set_is_burnable(self, value)

    def set_is_item_magical_eater(self, value):
        my.tp_set_is_item_magical_eater(self, value)

    def set_environ_prefers_fire(self, value):
        my.tp_set_environ_prefers_fire(self, value)

    def set_is_projectile(self, value):
        my.tp_set_is_projectile(self, value)

    def set_gfx_flickers(self, value):
        my.tp_set_gfx_flickers(self, value)

    def set_is_laser(self, value):
        my.tp_set_is_laser(self, value)

    def set_is_able_to_fire_at(self, value):
        my.tp_set_is_able_to_fire_at(self, value)

    def set_distance_vision(self, value):
        my.tp_set_distance_vision(self, value)

    def set_is_ethereal_mob(self, value):
        my.tp_set_is_ethereal_mob(self, value)

    def set_is_spawner(self, value):
        my.tp_set_is_spawner(self, value)

    def set_distance_avoid(self, value):
        my.tp_set_distance_avoid(self, value)

    def set_is_item_carrier(self, value):
        my.tp_set_is_item_carrier(self, value)

    def set_is_carrier_of_treasure_class_c(self, value):
        my.tp_set_is_carrier_of_treasure_class_c(self, value)

    def set_is_carrier_of_treasure_class_b(self, value):
        my.tp_set_is_carrier_of_treasure_class_b(self, value)

    def set_is_carrier_of_treasure_class_a(self, value):
        my.tp_set_is_carrier_of_treasure_class_a(self, value)

    def set_is_carrier_of_weapon_class_c(self, value):
        my.tp_set_is_carrier_of_weapon_class_c(self, value)

    def set_is_carrier_of_weapon_class_b(self, value):
        my.tp_set_is_carrier_of_weapon_class_b(self, value)

    def set_is_carrier_of_weapon_class_a(self, value):
        my.tp_set_is_carrier_of_weapon_class_a(self, value)

    def set_is_torch(self, value):
        my.tp_set_is_torch(self, value)

    def set_range_max(self, value):
        my.tp_set_range_max(self, value)

    def set_is_target_auto_select(self, value):
        my.tp_set_is_target_auto_select(self, value)

    def set_is_wand(self, value):
        my.tp_set_is_wand(self, value)

    def set_charge_count(self, value):
        my.tp_set_charge_count(self, value)

    def set_distance_manifestor_max(self, value):
        my.tp_set_distance_manifestor_max(self, value)

    def set_is_skill(self, value):
        my.tp_set_is_skill(self, value)

    def set_is_sewer_wall(self, value):
        my.tp_set_is_sewer_wall(self, value)

    def set_is_wall_dungeon(self, value):
        my.tp_set_is_wall_dungeon(self, value)

    def set_is_descend_sewer(self, value):
        my.tp_set_is_descend_sewer(self, value)

    def set_environ_prefers_spiderwebs(self, value):
        my.tp_set_environ_prefers_spiderwebs(self, value)

    def set_is_shallow_water(self, value):
        my.tp_set_is_shallow_water(self, value)

    def set_minion_limit(self, value):
        my.tp_set_minion_limit(self, value)

    def set_is_living(self, value):
        my.tp_set_is_living(self, value)

    def set_attack_living(self, value):
        my.tp_set_attack_living(self, value)

    def set_is_minion(self, value):
        my.tp_set_is_minion(self, value)

    def set_is_described_when_hovering_over(self, value):
        my.tp_set_is_described_when_hovering_over(self, value)

    def set_is_always_hit(self, value):
        my.tp_set_is_always_hit(self, value)

    def set_is_fearless(self, value):
        my.tp_set_is_fearless(self, value)

    def set_is_able_to_see_through_doors(self, value):
        my.tp_set_is_able_to_see_through_doors(self, value)

    def set_is_able_to_walk_through_walls(self, value):
        my.tp_set_is_able_to_walk_through_walls(self, value)

    def set_is_humanoid(self, value):
        my.tp_set_is_humanoid(self, value)

    def set_environ_prefers_poison(self, value):
        my.tp_set_environ_prefers_poison(self, value)

    def set_damage_received_doubled_from_poison(self, value):
        my.tp_set_damage_received_doubled_from_poison(self, value)

    def set_environ_avoids_poison(self, value):
        my.tp_set_environ_avoids_poison(self, value)

    def set_environ_prefers_necrosis(self, value):
        my.tp_set_environ_prefers_necrosis(self, value)

    def set_damage_received_doubled_from_necrosis(self, value):
        my.tp_set_damage_received_doubled_from_necrosis(self, value)

    def set_environ_avoids_necrosis(self, value):
        my.tp_set_environ_avoids_necrosis(self, value)

    def set_attack_humanoid(self, value):
        my.tp_set_attack_humanoid(self, value)

    def set_is_poisonous_danger_level(self, value):
        my.tp_set_is_poisonous_danger_level(self, value)

    def set_is_necrotic_danger_level(self, value):
        my.tp_set_is_necrotic_danger_level(self, value)

    def set_is_used_when_thrown(self, value):
        my.tp_set_is_used_when_thrown(self, value)

    def set_is_auto_use(self, value):
        my.tp_set_is_auto_use(self, value)

    def set_is_auto_throw(self, value):
        my.tp_set_is_auto_throw(self, value)

    def set_is_cursor_path_hazard_for_player(self, value):
        my.tp_set_is_cursor_path_hazard_for_player(self, value)

    def set_is_auto_collect_item(self, value):
        my.tp_set_is_auto_collect_item(self, value)

    def set_attack_meat(self, value):
        my.tp_set_attack_meat(self, value)

    def set_is_food_eater(self, value):
        my.tp_set_is_food_eater(self, value)

    def set_blast_max_radius(self, value):
        my.tp_set_blast_max_radius(self, value)

    def set_blast_min_radius(self, value):
        my.tp_set_blast_min_radius(self, value)

    def set_is_critical_to_level(self, value):
        my.tp_set_is_critical_to_level(self, value)

    def set_is_able_to_fall(self, value):
        my.tp_set_is_able_to_fall(self, value)

    def set_item_height(self, value):
        my.tp_set_item_height(self, value)

    def set_item_width(self, value):
        my.tp_set_item_width(self, value)

    def set_capacity_height(self, value):
        my.tp_set_capacity_height(self, value)

    def set_capacity_width(self, value):
        my.tp_set_capacity_width(self, value)

    def set_monst_size(self, value):
        my.tp_set_monst_size(self, value)

    def set_rarity(self, value):
        my.tp_set_rarity(self, value)

    def set_is_able_to_tire(self, value):
        my.tp_set_is_able_to_tire(self, value)

    def set_gfx_shown_in_bg(self, value):
        my.tp_set_gfx_shown_in_bg(self, value)

    def set_on_death_drop_all_items(self, value):
        my.tp_set_on_death_drop_all_items(self, value)

    def set_is_steal_item_chance_d1000(self, value):
        my.tp_set_is_steal_item_chance_d1000(self, value)

    def set_attack_engulf_chance_d1000(self, value):
        my.tp_set_attack_engulf_chance_d1000(self, value)

    def set_damage_poison_chance_d1000(self, value):
        my.tp_set_damage_poison_chance_d1000(self, value)

    def set_damage_future1_chance_d1000(self, value):
        my.tp_set_damage_future1_chance_d1000(self, value)

    def set_damage_future2_chance_d1000(self, value):
        my.tp_set_damage_future2_chance_d1000(self, value)

    def set_damage_future3_chance_d1000(self, value):
        my.tp_set_damage_future3_chance_d1000(self, value)

    def set_damage_future4_chance_d1000(self, value):
        my.tp_set_damage_future4_chance_d1000(self, value)

    def set_damage_fire_chance_d1000(self, value):
        my.tp_set_damage_fire_chance_d1000(self, value)

    def set_damage_crush_chance_d1000(self, value):
        my.tp_set_damage_crush_chance_d1000(self, value)

    def set_damage_lightning_chance_d1000(self, value):
        my.tp_set_damage_lightning_chance_d1000(self, value)

    def set_damage_energy_chance_d1000(self, value):
        my.tp_set_damage_energy_chance_d1000(self, value)

    def set_damage_acid_chance_d1000(self, value):
        my.tp_set_damage_acid_chance_d1000(self, value)

    def set_damage_digest_chance_d1000(self, value):
        my.tp_set_damage_digest_chance_d1000(self, value)

    def set_damage_necrosis_chance_d1000(self, value):
        my.tp_set_damage_necrosis_chance_d1000(self, value)

    def set_is_able_to_use_rings(self, value):
        my.tp_set_is_able_to_use_rings(self, value)

    def set_is_bag_item(self, value):
        my.tp_set_is_bag_item(self, value)

    def set_is_attackable_by_player(self, value):
        my.tp_set_is_attackable_by_player(self, value)

    def set_is_item_eater(self, value):
        my.tp_set_is_item_eater(self, value)

    def set_is_obs_destructable(self, value):
        my.tp_set_is_obs_destructable(self, value)

    def set_is_the_grid(self, value):
        my.tp_set_is_the_grid(self, value)

    def set_is_cursor_can_hover_over_x2_click(self, value):
        my.tp_set_is_cursor_can_hover_over_x2_click(self, value)

    def set_gfx_glows(self, value):
        my.tp_set_gfx_glows(self, value)

    def set_gfx_health_bar_autohide(self, value):
        my.tp_set_gfx_health_bar_autohide(self, value)

    def set_gfx_health_bar_shown(self, value):
        my.tp_set_gfx_health_bar_shown(self, value)

    def set_on_death_is_open(self, value):
        my.tp_set_on_death_is_open(self, value)

    def set_is_destroyed_on_hit_or_miss(self, value):
        my.tp_set_is_destroyed_on_hit_or_miss(self, value)

    def set_is_destroyed_on_hitting(self, value):
        my.tp_set_is_destroyed_on_hitting(self, value)

    def set_is_collect_as_keys(self, value):
        my.tp_set_is_collect_as_keys(self, value)

    def set_is_ethereal(self, value):
        my.tp_set_is_ethereal(self, value)

    def set_is_potion_eater(self, value):
        my.tp_set_is_potion_eater(self, value)

    def set_is_throwable(self, value):
        my.tp_set_is_throwable(self, value)

    def set_is_usable(self, value):
        my.tp_set_is_usable(self, value)

    def set_is_droppable(self, value):
        my.tp_set_is_droppable(self, value)

    def set_is_bag_item_not_stackable(self, value):
        my.tp_set_is_bag_item_not_stackable(self, value)

    def set_is_treasure_class_a(self, value):
        my.tp_set_is_treasure_class_a(self, value)

    def set_is_treasure_class_c(self, value):
        my.tp_set_is_treasure_class_c(self, value)

    def set_is_treasure_class_b(self, value):
        my.tp_set_is_treasure_class_b(self, value)

    def set_is_weapon_class_a(self, value):
        my.tp_set_is_weapon_class_a(self, value)

    def set_is_weapon_class_c(self, value):
        my.tp_set_is_weapon_class_c(self, value)

    def set_is_weapon_class_b(self, value):
        my.tp_set_is_weapon_class_b(self, value)

    def set_is_bag(self, value):
        my.tp_set_is_bag(self, value)

    def set_is_temporary_bag(self, value):
        my.tp_set_is_temporary_bag(self, value)

    def set_is_chasm(self, value):
        my.tp_set_is_chasm(self, value)

    def set_is_potion(self, value):
        my.tp_set_is_potion(self, value)

    def set_is_floating(self, value):
        my.tp_set_is_floating(self, value)

    def set_damage_received_doubled_from_water(self, value):
        my.tp_set_damage_received_doubled_from_water(self, value)

    def set_is_mob(self, value):
        my.tp_set_is_mob(self, value)

    def set_is_treasure_eater(self, value):
        my.tp_set_is_treasure_eater(self, value)

    def set_damage_received_doubled_from_acid(self, value):
        my.tp_set_damage_received_doubled_from_acid(self, value)

    def set_environ_prefers_acid(self, value):
        my.tp_set_environ_prefers_acid(self, value)

    def set_is_jelly_parent(self, value):
        my.tp_set_is_jelly_parent(self, value)

    def set_is_jelly_eater(self, value):
        my.tp_set_is_jelly_eater(self, value)

    def set_is_jelly(self, value):
        my.tp_set_is_jelly(self, value)

    def set_attack_eater(self, value):
        my.tp_set_attack_eater(self, value)

    def set_distance_jump(self, value):
        my.tp_set_distance_jump(self, value)

    def set_is_able_to_jump(self, value):
        my.tp_set_is_able_to_jump(self, value)

    def set_is_acid(self, value):
        my.tp_set_is_acid(self, value)

    def set_is_jelly_baby_eater(self, value):
        my.tp_set_is_jelly_baby_eater(self, value)

    def set_is_jelly_baby(self, value):
        my.tp_set_is_jelly_baby(self, value)

    def set_is_able_to_change_levels(self, value):
        my.tp_set_is_able_to_change_levels(self, value)

    def set_is_collected_as_gold(self, value):
        my.tp_set_is_collected_as_gold(self, value)

    def set_is_gold(self, value):
        my.tp_set_is_gold(self, value)

    def set_is_removeable_if_out_of_slots(self, value):
        my.tp_set_is_removeable_if_out_of_slots(self, value)

    def set_is_smoke(self, value):
        my.tp_set_is_smoke(self, value)

    def set_environ_avoids_fire(self, value):
        my.tp_set_environ_avoids_fire(self, value)

    def set_is_treasure_type(self, value):
        my.tp_set_is_treasure_type(self, value)

    def set_is_collectable(self, value):
        my.tp_set_is_collectable(self, value)

    def set_is_resurrectable(self, value):
        my.tp_set_is_resurrectable(self, value)

    def set_is_intelligent(self, value):
        my.tp_set_is_intelligent(self, value)

    def set_damage_received_doubled_from_fire(self, value):
        my.tp_set_damage_received_doubled_from_fire(self, value)

    def set_is_fire(self, value):
        my.tp_set_is_fire(self, value)

    def set_is_dead_on_shove(self, value):
        my.tp_set_is_dead_on_shove(self, value)

    def set_is_loggable(self, value):
        my.tp_set_is_loggable(self, value)

    def set_is_brazier(self, value):
        my.tp_set_is_brazier(self, value)

    def set_gfx_bounce_always(self, value):
        my.tp_set_gfx_bounce_always(self, value)

    def set_normal_placement_rules(self, value):
        my.tp_set_normal_placement_rules(self, value)

    def set_is_very_combustible(self, value):
        my.tp_set_is_very_combustible(self, value)

    def set_is_combustible(self, value):
        my.tp_set_is_combustible(self, value)

    def set_gfx_attack_anim(self, value):
        my.tp_set_gfx_attack_anim(self, value)

    def set_ai_shove_chance_d1000(self, value):
        my.tp_set_ai_shove_chance_d1000(self, value)

    def set_unused_chance1_d1000(self, value):
        my.tp_set_unused_chance1_d1000(self, value)

    def set_unused_chance2_d1000(self, value):
        my.tp_set_unused_chance2_d1000(self, value)

    def set_unused_chance3_d1000(self, value):
        my.tp_set_unused_chance3_d1000(self, value)

    def set_unused_chance4_d1000(self, value):
        my.tp_set_unused_chance4_d1000(self, value)

    def set_unused_chance5_d1000(self, value):
        my.tp_set_unused_chance5_d1000(self, value)

    def set_unused_chance6_d1000(self, value):
        my.tp_set_unused_chance6_d1000(self, value)

    def set_unused_chance7_d1000(self, value):
        my.tp_set_unused_chance7_d1000(self, value)

    def set_unused_chance8_d1000(self, value):
        my.tp_set_unused_chance8_d1000(self, value)

    def set_damage_melee_chance_d1000(self, value):
        my.tp_set_damage_melee_chance_d1000(self, value)

    def set_damage_bite_chance_d1000(self, value):
        my.tp_set_damage_bite_chance_d1000(self, value)

    def set_is_able_to_jump_randomly_chance_d1000(self, value):
        my.tp_set_is_able_to_jump_randomly_chance_d1000(self, value)

    def set_is_able_to_jump_attack_chance_d1000(self, value):
        my.tp_set_is_able_to_jump_attack_chance_d1000(self, value)

    def set_is_able_to_jump_onto_chance_d1000(self, value):
        my.tp_set_is_able_to_jump_onto_chance_d1000(self, value)

    def set_is_able_to_jump_on_low_hp_chance_d1000(self, value):
        my.tp_set_is_able_to_jump_on_low_hp_chance_d1000(self, value)

    def set_is_hazard(self, value):
        my.tp_set_is_hazard(self, value)

    def set_is_able_to_shove(self, value):
        my.tp_set_is_able_to_shove(self, value)

    def set_is_shovable(self, value):
        my.tp_set_is_shovable(self, value)

    def set_is_cursor_path(self, value):
        my.tp_set_is_cursor_path(self, value)

    def set_is_blood_splatter(self, value):
        my.tp_set_is_blood_splatter(self, value)

    def set_is_no_tile(self, value):
        my.tp_set_is_no_tile(self, value)

    def set_is_msg(self, value):
        my.tp_set_is_msg(self, value)

    def set_attack_lunge(self, value):
        my.tp_set_attack_lunge(self, value)

    def set_stamina(self, value):
        my.tp_set_stamina(self, value)

    def set_stat_strength(self, value):
        my.tp_set_stat_strength(self, value)

    def set_stat_dexterity(self, value):
        my.tp_set_stat_dexterity(self, value)

    def set_stat_armor_class(self, value):
        my.tp_set_stat_armor_class(self, value)

    def set_stat_attack_bonus(self, value):
        my.tp_set_stat_attack_bonus(self, value)

    def set_stat_constitution(self, value):
        my.tp_set_stat_constitution(self, value)

    def set_distance_throw(self, value):
        my.tp_set_distance_throw(self, value)

    def set_lifespan_dice(self, value):
        my.tp_set_lifespan_dice(self, value)

    def set_is_secret_door(self, value):
        my.tp_set_is_secret_door(self, value)

    def set_is_cursor_can_hover_over(self, value):
        my.tp_set_is_cursor_can_hover_over(self, value)

    def set_is_cursor(self, value):
        my.tp_set_is_cursor(self, value)

    def set_gfx_dead_anim(self, value):
        my.tp_set_gfx_dead_anim(self, value)

    def set_ai_obstacle(self, value):
        my.tp_set_ai_obstacle(self, value)

    def set_is_attackable_by_monst(self, value):
        my.tp_set_is_attackable_by_monst(self, value)

    def set_is_food(self, value):
        my.tp_set_is_food(self, value)

    def set_hunger_is_insatiable(self, value):
        my.tp_set_hunger_is_insatiable(self, value)

    def set_is_undead(self, value):
        my.tp_set_is_undead(self, value)

    def set_tick_catches_up_on_attack(self, value):
        my.tp_set_tick_catches_up_on_attack(self, value)

    def set_nutrition_dice(self, value):
        my.tp_set_nutrition_dice(self, value)

    def set_damage_melee_dice(self, value):
        my.tp_set_damage_melee_dice(self, value)

    def set_damage_poison_dice(self, value):
        my.tp_set_damage_poison_dice(self, value)

    def set_damage_future1_dice(self, value):
        my.tp_set_damage_future1_dice(self, value)

    def set_damage_future2_dice(self, value):
        my.tp_set_damage_future2_dice(self, value)

    def set_damage_future3_dice(self, value):
        my.tp_set_damage_future3_dice(self, value)

    def set_damage_future4_dice(self, value):
        my.tp_set_damage_future4_dice(self, value)

    def set_damage_fire_dice(self, value):
        my.tp_set_damage_fire_dice(self, value)

    def set_damage_crush_dice(self, value):
        my.tp_set_damage_crush_dice(self, value)

    def set_damage_lightning_dice(self, value):
        my.tp_set_damage_lightning_dice(self, value)

    def set_damage_energy_dice(self, value):
        my.tp_set_damage_energy_dice(self, value)

    def set_damage_acid_dice(self, value):
        my.tp_set_damage_acid_dice(self, value)

    def set_damage_digest_dice(self, value):
        my.tp_set_damage_digest_dice(self, value)

    def set_damage_necrosis_dice(self, value):
        my.tp_set_damage_necrosis_dice(self, value)

    def set_damage_bite_dice(self, value):
        my.tp_set_damage_bite_dice(self, value)

    def set_gold_value_dice(self, value):
        my.tp_set_gold_value_dice(self, value)

    def set_resurrect_dice(self, value):
        my.tp_set_resurrect_dice(self, value)

    def set_collision_check(self, value):
        my.tp_set_collision_check(self, value)

    def set_collision_attack(self, value):
        my.tp_set_collision_attack(self, value)

    def set_environ_prefers_water(self, value):
        my.tp_set_environ_prefers_water(self, value)

    def set_collision_hit_priority(self, value):
        my.tp_set_collision_hit_priority(self, value)

    def set_collision_radius(self, value):
        my.tp_set_collision_radius(self, value)

    def set_collision_attack_radius(self, value):
        my.tp_set_collision_attack_radius(self, value)

    def set_gfx_bounce_on_move(self, value):
        my.tp_set_gfx_bounce_on_move(self, value)

    def set_is_bleeder(self, value):
        my.tp_set_is_bleeder(self, value)

    def set_is_corpse_on_death(self, value):
        my.tp_set_is_corpse_on_death(self, value)

    def set_is_meat_eater(self, value):
        my.tp_set_is_meat_eater(self, value)

    def set_is_meat(self, value):
        my.tp_set_is_meat(self, value)

    def set_is_tickable(self, value):
        my.tp_set_is_tickable(self, value)

    def set_health_starving_pct(self, value):
        my.tp_set_health_starving_pct(self, value)

    def set_health_initial_dice(self, value):
        my.tp_set_health_initial_dice(self, value)

    def set_hunger_health_pct(self, value):
        my.tp_set_hunger_health_pct(self, value)

    def set_is_ripple(self, value):
        my.tp_set_is_ripple(self, value)

    def set_light_strength(self, value):
        my.tp_set_light_strength(self, value)

    def set_is_blood(self, value):
        my.tp_set_is_blood(self, value)

    def set_gfx_animated_can_vflip(self, value):
        my.tp_set_gfx_animated_can_vflip(self, value)

    def set_is_corridor(self, value):
        my.tp_set_is_corridor(self, value)

    def set_gfx_oversized_and_on_floor(self, value):
        my.tp_set_gfx_oversized_and_on_floor(self, value)

    def set_is_interesting(self, value):
        my.tp_set_is_interesting(self, value)

    def set_is_descend_dungeon(self, value):
        my.tp_set_is_descend_dungeon(self, value)

    def set_is_door(self, value):
        my.tp_set_is_door(self, value)

    def set_is_ascend_dungeon(self, value):
        my.tp_set_is_ascend_dungeon(self, value)

    def set_weapon_use_delay_hundredths(self, value):
        my.tp_set_weapon_use_delay_hundredths(self, value)

    def set_collision_box(self, value):
        my.tp_set_collision_box(self, value)

    def set_collision_circle(self, value):
        my.tp_set_collision_circle(self, value)

    def set_weapon_damage(self, value):
        my.tp_set_weapon_damage(self, value)

    def set_is_explosion(self, value):
        my.tp_set_is_explosion(self, value)

    def set_weapon_use_distance(self, value):
        my.tp_set_weapon_use_distance(self, value)

    def set_gfx_equip_carry_anim(self, value):
        my.tp_set_gfx_equip_carry_anim(self, value)

    def set_is_weapon(self, value):
        my.tp_set_is_weapon(self, value)

    def set_gfx_show_outlined(self, value):
        my.tp_set_gfx_show_outlined(self, value)

    def set_is_light_blocker(self, value):
        my.tp_set_is_light_blocker(self, value)

    def set_z_depth(self, value):
        my.tp_set_z_depth(self, value)

    def set_ascii_z_depth(self, value):
        my.tp_set_ascii_z_depth(self, value)

    def set_z_prio(self, value):
        my.tp_set_z_prio(self, value)

    def set_is_moveable(self, value):
        my.tp_set_is_moveable(self, value)

    def set_gfx_animated_can_hflip(self, value):
        my.tp_set_gfx_animated_can_hflip(self, value)

    def set_is_obs_wall_or_door(self, value):
        my.tp_set_is_obs_wall_or_door(self, value)

    def set_is_wall(self, value):
        my.tp_set_is_wall(self, value)

    def set_is_rock(self, value):
        my.tp_set_is_rock(self, value)

    def set_is_floor(self, value):
        my.tp_set_is_floor(self, value)

    def set_is_dirt(self, value):
        my.tp_set_is_dirt(self, value)

    def set_is_lava(self, value):
        my.tp_set_is_lava(self, value)

    def set_gfx_water(self, value):
        my.tp_set_gfx_water(self, value)

    def set_is_deep_water(self, value):
        my.tp_set_is_deep_water(self, value)

    def set_gfx_short_shadow_caster(self, value):
        my.tp_set_gfx_short_shadow_caster(self, value)
