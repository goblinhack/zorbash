import zx


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
        zx.tp_load(self)

    def update(self):
        zx.tp_update(self)

    def set_tile(self, tile=None, **kw):
        zx.tp_set_tile(self, tile, **kw)

    def set_left1_tile(self, left1_tile=None, **kw):
        zx.tp_set_left1_tile(self, left1_tile, **kw)

    def set_right1_tile(self, right1_tile=None, **kw):
        zx.tp_set_right1_tile(self, right1_tile, **kw)

    def set_bot1_tile(self, bot1_tile=None, **kw):
        zx.tp_set_bot1_tile(self, bot1_tile, **kw)

    def set_top1_tile(self, top1_tile=None, **kw):
        zx.tp_set_top1_tile(self, top1_tile, **kw)

    def set_tl1_tile(self, tl1_tile=None, **kw):
        zx.tp_set_tl1_tile(self, tl1_tile, **kw)

    def set_tr1_tile(self, tr1_tile=None, **kw):
        zx.tp_set_tr1_tile(self, tr1_tile, **kw)

    def set_br1_tile(self, br1_tile=None, **kw):
        zx.tp_set_br1_tile(self, br1_tile, **kw)

    def set_bl1_tile(self, bl1_tile=None, **kw):
        zx.tp_set_bl1_tile(self, bl1_tile, **kw)

    def set_left2_tile(self, left2_tile=None, **kw):
        zx.tp_set_left2_tile(self, left2_tile, **kw)

    def set_right2_tile(self, right2_tile=None, **kw):
        zx.tp_set_right2_tile(self, right2_tile, **kw)

    def set_bot2_tile(self, bot2_tile=None, **kw):
        zx.tp_set_bot2_tile(self, bot2_tile, **kw)

    def set_bot3_tile(self, bot3_tile=None, **kw):
        zx.tp_set_bot3_tile(self, bot3_tile, **kw)

    def set_top2_tile(self, top2_tile=None, **kw):
        zx.tp_set_top2_tile(self, top2_tile, **kw)

    def set_tl2_tile(self, tl2_tile=None, **kw):
        zx.tp_set_tl2_tile(self, tl2_tile, **kw)

    def set_tr2_tile(self, tr2_tile=None, **kw):
        zx.tp_set_tr2_tile(self, tr2_tile, **kw)

    def set_br2_tile(self, br2_tile=None, **kw):
        zx.tp_set_br2_tile(self, br2_tile, **kw)

    def set_bl2_tile(self, bl2_tile=None, **kw):
        zx.tp_set_bl2_tile(self, bl2_tile, **kw)

    def set_name(self, value):
        zx.tp_set_name(self, value)

    def set_short_name(self, value):
        zx.tp_set_short_name(self, value)

    def set_blit_top_off(self, value):
        zx.tp_set_blit_top_off(self, value)

    def set_blit_bot_off(self, value):
        zx.tp_set_blit_bot_off(self, value)

    def set_blit_left_off(self, value):
        zx.tp_set_blit_left_off(self, value)

    def set_blit_right_off(self, value):
        zx.tp_set_blit_right_off(self, value)

    def set_gfx_animated(self, value):
        zx.tp_set_gfx_animated(self, value)

    def set_gfx_animated_no_dir(self, value):
        zx.tp_set_gfx_animated_no_dir(self, value)

    def set_gfx_an_animation_only(self, value):
        zx.tp_set_gfx_an_animation_only(self, value)

    def set_gfx_on_fire_anim(self, value):
        zx.tp_set_gfx_on_fire_anim(self, value)

    def set_is_monst(self, value):
        zx.tp_set_is_monst(self, value)

    def set_is_key(self, value):
        zx.tp_set_is_key(self, value)

    def set_is_floor_deco(self, value):
        zx.tp_set_is_floor_deco(self, value)

    def set_is_ascend_sewer(self, value):
        zx.tp_set_is_ascend_sewer(self, value)

    def set_is_player(self, value):
        zx.tp_set_is_player(self, value)

    def set_str1(self, value):
        zx.tp_set_str1(self, value)

    def set_str_str2(self, value):
        zx.tp_set_str_str2(self, value)

    def set_text_enchant(self, value):
        zx.tp_set_text_enchant(self, value)

    def set_text_skill(self, value):
        zx.tp_set_text_skill(self, value)

    def set_str_str4(self, value):
        zx.tp_set_str_str4(self, value)

    def set_str_str5(self, value):
        zx.tp_set_str_str5(self, value)

    def set_str_projectile_name(self, value):
        zx.tp_set_str_projectile_name(self, value)

    def set_laser_name(self, value):
        zx.tp_set_laser_name(self, value)

    def set_projectile_name(self, value):
        zx.tp_set_projectile_name(self, value)

    def set_long_text_description(self, value):
        zx.tp_set_long_text_description(self, value)

    def set_text_description(self, value):
        zx.tp_set_text_description(self, value)

    def set_text_unused(self, value):
        zx.tp_set_text_unused(self, value)

    def set_on_birth_do(self, value):
        zx.tp_set_on_birth_do(self, value)

    def set_on_use_do(self, value):
        zx.tp_set_on_use_do(self, value)

    def set_on_hit_do(self, value):
        zx.tp_set_on_hit_do(self, value)

    def set_on_miss_do(self, value):
        zx.tp_set_on_miss_do(self, value)

    def set_on_fall_do(self, value):
        zx.tp_set_on_fall_do(self, value)

    def set_on_enchant_do(self, value):
        zx.tp_set_on_enchant_do(self, value)

    def set_on_fire_do(self, value):
        zx.tp_set_on_fire_do(self, value)

    def set_on_firing_at_something_do(self, value):
        zx.tp_set_on_firing_at_something_do(self, value)

    def set_on_tick_do(self, value):
        zx.tp_set_on_tick_do(self, value)

    def set_on_lifespan_do(self, value):
        zx.tp_set_on_lifespan_do(self, value)

    def set_on_bite_do(self, value):
        zx.tp_set_on_bite_do(self, value)

    def set_on_death_do(self, value):
        zx.tp_set_on_death_do(self, value)

    def set_on_born_do(self, value):
        zx.tp_set_on_born_do(self, value)

    def set_on_move_do(self, value):
        zx.tp_set_on_move_do(self, value)

    def set_on_open_do(self, value):
        zx.tp_set_on_open_do(self, value)

    def set_text_title(self, value):
        zx.tp_set_text_title(self, value)

    def set_on_idle_dice(self, value):
        zx.tp_set_on_idle_dice(self, value)

    def set_text_hits(self, value):
        zx.tp_set_text_hits(self, value)

    def set_spawn_on_shoved(self, value):
        zx.tp_set_spawn_on_shoved(self, value)

    def set_text_a_or_an(self, value):
        zx.tp_set_text_a_or_an(self, value)

    def set_text_name(self, value):
        zx.tp_set_text_name(self, value)

    def set_light_color(self, value):
        zx.tp_set_light_color(self, value)

    def set_weapon_carry_anim(self, value):
        zx.tp_set_weapon_carry_anim(self, value)

    def set_gfx_anim_attack(self, value):
        zx.tp_set_gfx_anim_attack(self, value)

    def set_unused_flag1(self, value):
        zx.tp_set_unused_flag1(self, value)

    def set_unused_flag2(self, value):
        zx.tp_set_unused_flag2(self, value)

    def set_unused_flag3(self, value):
        zx.tp_set_unused_flag3(self, value)

    def set_unused_flag4(self, value):
        zx.tp_set_unused_flag4(self, value)

    def set_unused_flag5(self, value):
        zx.tp_set_unused_flag5(self, value)

    def set_unused_flag6(self, value):
        zx.tp_set_unused_flag6(self, value)

    def set_unused_flag7(self, value):
        zx.tp_set_unused_flag7(self, value)

    def set_unused_flag8(self, value):
        zx.tp_set_unused_flag8(self, value)

    def set_unused_flag9(self, value):
        zx.tp_set_unused_flag9(self, value)

    def set_unused_flag10(self, value):
        zx.tp_set_unused_flag10(self, value)

    def set_unused_flag11(self, value):
        zx.tp_set_unused_flag11(self, value)

    def set_unused_flag12(self, value):
        zx.tp_set_unused_flag12(self, value)

    def set_unused_flag13(self, value):
        zx.tp_set_unused_flag13(self, value)

    def set_unused_flag14(self, value):
        zx.tp_set_unused_flag14(self, value)

    def set_unused_flag15(self, value):
        zx.tp_set_unused_flag15(self, value)

    def set_unused_flag16(self, value):
        zx.tp_set_unused_flag16(self, value)

    def set_unused_flag17(self, value):
        zx.tp_set_unused_flag17(self, value)

    def set_unused_flag18(self, value):
        zx.tp_set_unused_flag18(self, value)

    def set_unused_flag19(self, value):
        zx.tp_set_unused_flag19(self, value)

    def set_unused_flag20(self, value):
        zx.tp_set_unused_flag20(self, value)

    def set_unused_flag21(self, value):
        zx.tp_set_unused_flag21(self, value)

    def set_unused_flag22(self, value):
        zx.tp_set_unused_flag22(self, value)

    def set_unused_flag23(self, value):
        zx.tp_set_unused_flag23(self, value)

    def set_unused_flag24(self, value):
        zx.tp_set_unused_flag24(self, value)

    def set_unused_flag25(self, value):
        zx.tp_set_unused_flag25(self, value)

    def set_unused_flag26(self, value):
        zx.tp_set_unused_flag26(self, value)

    def set_unused_flag27(self, value):
        zx.tp_set_unused_flag27(self, value)

    def set_unused_flag28(self, value):
        zx.tp_set_unused_flag28(self, value)

    def set_unused_flag29(self, value):
        zx.tp_set_unused_flag29(self, value)

    def set_unused_flag30(self, value):
        zx.tp_set_unused_flag30(self, value)

    def set_unused_flag31(self, value):
        zx.tp_set_unused_flag31(self, value)

    def set_unused_flag32(self, value):
        zx.tp_set_unused_flag32(self, value)

    def set_unused_flag33(self, value):
        zx.tp_set_unused_flag33(self, value)

    def set_unused_flag34(self, value):
        zx.tp_set_unused_flag34(self, value)

    def set_unused_flag35(self, value):
        zx.tp_set_unused_flag35(self, value)

    def set_unused_flag36(self, value):
        zx.tp_set_unused_flag36(self, value)

    def set_unused_flag37(self, value):
        zx.tp_set_unused_flag37(self, value)

    def set_unused_flag38(self, value):
        zx.tp_set_unused_flag38(self, value)

    def set_unused_flag39(self, value):
        zx.tp_set_unused_flag39(self, value)

    def set_unused_flag40(self, value):
        zx.tp_set_unused_flag40(self, value)

    def set_unused_flag41(self, value):
        zx.tp_set_unused_flag41(self, value)

    def set_unused_flag42(self, value):
        zx.tp_set_unused_flag42(self, value)

    def set_unused_flag43(self, value):
        zx.tp_set_unused_flag43(self, value)

    def set_unused_flag44(self, value):
        zx.tp_set_unused_flag44(self, value)

    def set_unused_flag45(self, value):
        zx.tp_set_unused_flag45(self, value)

    def set_unused_flag46(self, value):
        zx.tp_set_unused_flag46(self, value)

    def set_unused_flag47(self, value):
        zx.tp_set_unused_flag47(self, value)

    def set_unused_flag48(self, value):
        zx.tp_set_unused_flag48(self, value)

    def set_is_rusty(self, value):
        zx.tp_set_is_rusty(self, value)

    def set_unused_flag50(self, value):
        zx.tp_set_unused_flag50(self, value)

    def set_unused_flag51(self, value):
        zx.tp_set_unused_flag51(self, value)

    def set_unused_flag52(self, value):
        zx.tp_set_unused_flag52(self, value)

    def set_is_ai_wanderer(self, value):
        zx.tp_set_is_ai_wanderer(self, value)

    def set_is_organic(self, value):
        zx.tp_set_is_organic(self, value)

    def set_is_glass(self, value):
        zx.tp_set_is_glass(self, value)

    def set_is_stone(self, value):
        zx.tp_set_is_stone(self, value)

    def set_is_item_organic(self, value):
        zx.tp_set_is_item_organic(self, value)

    def set_is_metal(self, value):
        zx.tp_set_is_metal(self, value)

    def set_is_wooden(self, value):
        zx.tp_set_is_wooden(self, value)

    def set_is_engulfer(self, value):
        zx.tp_set_is_engulfer(self, value)

    def set_is_health_booster(self, value):
        zx.tp_set_is_health_booster(self, value)

    def set_is_tmp_thing(self, value):
        zx.tp_set_is_tmp_thing(self, value)

    def set_is_debug_type(self, value):
        zx.tp_set_is_debug_type(self, value)

    def set_is_hittable(self, value):
        zx.tp_set_is_hittable(self, value)

    def set_is_alive_on_end_of_anim(self, value):
        zx.tp_set_is_alive_on_end_of_anim(self, value)

    def set_is_dead_on_end_of_anim(self, value):
        zx.tp_set_is_dead_on_end_of_anim(self, value)

    def set_ai_enemy_memory(self, value):
        zx.tp_set_ai_enemy_memory(self, value)

    def set_is_debug_path(self, value):
        zx.tp_set_is_debug_path(self, value)

    def set_is_key_collector(self, value):
        zx.tp_set_is_key_collector(self, value)

    def set_is_item_collector(self, value):
        zx.tp_set_is_item_collector(self, value)

    def set_is_item(self, value):
        zx.tp_set_is_item(self, value)

    def set_is_bag_item_container(self, value):
        zx.tp_set_is_bag_item_container(self, value)

    def set_is_treasure_type_chest(self, value):
        zx.tp_set_is_treasure_type_chest(self, value)

    def set_is_openable(self, value):
        zx.tp_set_is_openable(self, value)

    def set_gfx_long_shadow_caster(self, value):
        zx.tp_set_gfx_long_shadow_caster(self, value)

    def set_gfx_solid_shadow(self, value):
        zx.tp_set_gfx_solid_shadow(self, value)

    def set_is_sticky(self, value):
        zx.tp_set_is_sticky(self, value)

    def set_is_sword(self, value):
        zx.tp_set_is_sword(self, value)

    def set_is_skillstone(self, value):
        zx.tp_set_is_skillstone(self, value)

    def set_enchant_level(self, value):
        zx.tp_set_enchant_level(self, value)

    def set_enchant_max(self, value):
        zx.tp_set_enchant_max(self, value)

    def set_is_enchantstone(self, value):
        zx.tp_set_is_enchantstone(self, value)

    def set_is_enchantable(self, value):
        zx.tp_set_is_enchantable(self, value)

    def set_is_indestructible(self, value):
        zx.tp_set_is_indestructible(self, value)

    def set_is_bones(self, value):
        zx.tp_set_is_bones(self, value)

    def set_is_soft_body(self, value):
        zx.tp_set_is_soft_body(self, value)

    def set_is_foilage(self, value):
        zx.tp_set_is_foilage(self, value)

    def set_is_spiderweb(self, value):
        zx.tp_set_is_spiderweb(self, value)

    def set_gfx_very_short_shadow_caster(self, value):
        zx.tp_set_gfx_very_short_shadow_caster(self, value)

    def set_is_dry_grass(self, value):
        zx.tp_set_is_dry_grass(self, value)

    def set_is_bridge(self, value):
        zx.tp_set_is_bridge(self, value)

    def set_is_barrel(self, value):
        zx.tp_set_is_barrel(self, value)

    def set_is_burnable(self, value):
        zx.tp_set_is_burnable(self, value)

    def set_is_wand_eater(self, value):
        zx.tp_set_is_wand_eater(self, value)

    def set_loves_fire(self, value):
        zx.tp_set_loves_fire(self, value)

    def set_is_projectile(self, value):
        zx.tp_set_is_projectile(self, value)

    def set_gfx_flickers(self, value):
        zx.tp_set_gfx_flickers(self, value)

    def set_is_laser(self, value):
        zx.tp_set_is_laser(self, value)

    def set_is_able_to_fire_at(self, value):
        zx.tp_set_is_able_to_fire_at(self, value)

    def set_ai_vision_distance(self, value):
        zx.tp_set_ai_vision_distance(self, value)

    def set_is_ethereal_minion_generator(self, value):
        zx.tp_set_is_ethereal_minion_generator(self, value)

    def set_is_spawner(self, value):
        zx.tp_set_is_spawner(self, value)

    def set_ai_avoid_distance(self, value):
        zx.tp_set_ai_avoid_distance(self, value)

    def set_is_item_carrier(self, value):
        zx.tp_set_is_item_carrier(self, value)

    def set_is_carrier_of_treasure_class_c(self, value):
        zx.tp_set_is_carrier_of_treasure_class_c(self, value)

    def set_is_carrier_of_treasure_class_b(self, value):
        zx.tp_set_is_carrier_of_treasure_class_b(self, value)

    def set_is_carrier_of_treasure_class_a(self, value):
        zx.tp_set_is_carrier_of_treasure_class_a(self, value)

    def set_is_torch(self, value):
        zx.tp_set_is_torch(self, value)

    def set_range_max(self, value):
        zx.tp_set_range_max(self, value)

    def set_is_target_auto_select(self, value):
        zx.tp_set_is_target_auto_select(self, value)

    def set_is_wand(self, value):
        zx.tp_set_is_wand(self, value)

    def set_charge_count(self, value):
        zx.tp_set_charge_count(self, value)

    def set_minion_leash_distance(self, value):
        zx.tp_set_minion_leash_distance(self, value)

    def set_is_skill(self, value):
        zx.tp_set_is_skill(self, value)

    def set_is_sewer_wall(self, value):
        zx.tp_set_is_sewer_wall(self, value)

    def set_is_wall_dungeon(self, value):
        zx.tp_set_is_wall_dungeon(self, value)

    def set_is_descend_sewer(self, value):
        zx.tp_set_is_descend_sewer(self, value)

    def set_loves_spiderwebs(self, value):
        zx.tp_set_loves_spiderwebs(self, value)

    def set_is_shallow_water(self, value):
        zx.tp_set_is_shallow_water(self, value)

    def set_minion_limit(self, value):
        zx.tp_set_minion_limit(self, value)

    def set_is_living(self, value):
        zx.tp_set_is_living(self, value)

    def set_attack_living(self, value):
        zx.tp_set_attack_living(self, value)

    def set_is_minion(self, value):
        zx.tp_set_is_minion(self, value)

    def set_is_described_when_hovering_over(self, value):
        zx.tp_set_is_described_when_hovering_over(self, value)

    def set_is_always_hit(self, value):
        zx.tp_set_is_always_hit(self, value)

    def set_is_fearless(self, value):
        zx.tp_set_is_fearless(self, value)

    def set_is_able_to_see_through_doors(self, value):
        zx.tp_set_is_able_to_see_through_doors(self, value)

    def set_is_able_to_walk_through_walls(self, value):
        zx.tp_set_is_able_to_walk_through_walls(self, value)

    def set_is_humanoid(self, value):
        zx.tp_set_is_humanoid(self, value)

    def set_loves_poison(self, value):
        zx.tp_set_loves_poison(self, value)

    def set_damage_doubled_from_poison(self, value):
        zx.tp_set_damage_doubled_from_poison(self, value)

    def set_hates_poison(self, value):
        zx.tp_set_hates_poison(self, value)

    def set_attack_humanoid(self, value):
        zx.tp_set_attack_humanoid(self, value)

    def set_is_poison(self, value):
        zx.tp_set_is_poison(self, value)

    def set_is_used_when_thrown(self, value):
        zx.tp_set_is_used_when_thrown(self, value)

    def set_is_auto_use(self, value):
        zx.tp_set_is_auto_use(self, value)

    def set_is_auto_throw(self, value):
        zx.tp_set_is_auto_throw(self, value)

    def set_is_extreme_hazard(self, value):
        zx.tp_set_is_extreme_hazard(self, value)

    def set_is_auto_collect_item(self, value):
        zx.tp_set_is_auto_collect_item(self, value)

    def set_attack_meat(self, value):
        zx.tp_set_attack_meat(self, value)

    def set_is_food_eater(self, value):
        zx.tp_set_is_food_eater(self, value)

    def set_blast_max_radius(self, value):
        zx.tp_set_blast_max_radius(self, value)

    def set_blast_min_radius(self, value):
        zx.tp_set_blast_min_radius(self, value)

    def set_is_critical_to_level(self, value):
        zx.tp_set_is_critical_to_level(self, value)

    def set_is_able_to_fall(self, value):
        zx.tp_set_is_able_to_fall(self, value)

    def set_is_treasure_class_c(self, value):
        zx.tp_set_is_treasure_class_c(self, value)

    def set_item_height(self, value):
        zx.tp_set_item_height(self, value)

    def set_item_width(self, value):
        zx.tp_set_item_width(self, value)

    def set_capacity_height(self, value):
        zx.tp_set_capacity_height(self, value)

    def set_capacity_width(self, value):
        zx.tp_set_capacity_width(self, value)

    def set_monst_size(self, value):
        zx.tp_set_monst_size(self, value)

    def set_rarity(self, value):
        zx.tp_set_rarity(self, value)

    def set_is_able_to_tire(self, value):
        zx.tp_set_is_able_to_tire(self, value)

    def set_gfx_shown_in_bg(self, value):
        zx.tp_set_gfx_shown_in_bg(self, value)

    def set_on_death_drop_all_items(self, value):
        zx.tp_set_on_death_drop_all_items(self, value)

    def set_is_steal_item_chance_d1000(self, value):
        zx.tp_set_is_steal_item_chance_d1000(self, value)

    def set_is_engulf_chance_d1000(self, value):
        zx.tp_set_is_engulf_chance_d1000(self, value)

    def set_is_weapon_wielder(self, value):
        zx.tp_set_is_weapon_wielder(self, value)

    def set_is_bag_item(self, value):
        zx.tp_set_is_bag_item(self, value)

    def set_is_attackable_by_player(self, value):
        zx.tp_set_is_attackable_by_player(self, value)

    def set_is_treasure_class_b(self, value):
        zx.tp_set_is_treasure_class_b(self, value)

    def set_is_item_eater(self, value):
        zx.tp_set_is_item_eater(self, value)

    def set_is_obs_destructable(self, value):
        zx.tp_set_is_obs_destructable(self, value)

    def set_is_the_grid(self, value):
        zx.tp_set_is_the_grid(self, value)

    def set_is_cursor_can_hover_over_x2_click(self, value):
        zx.tp_set_is_cursor_can_hover_over_x2_click(self, value)

    def set_gfx_glows(self, value):
        zx.tp_set_gfx_glows(self, value)

    def set_gfx_health_bar_autohide(self, value):
        zx.tp_set_gfx_health_bar_autohide(self, value)

    def set_gfx_health_bar_shown(self, value):
        zx.tp_set_gfx_health_bar_shown(self, value)

    def set_on_death_is_open(self, value):
        zx.tp_set_on_death_is_open(self, value)

    def set_is_killed_on_hit_or_miss(self, value):
        zx.tp_set_is_killed_on_hit_or_miss(self, value)

    def set_is_killed_on_hitting(self, value):
        zx.tp_set_is_killed_on_hitting(self, value)

    def set_is_collect_as_keys(self, value):
        zx.tp_set_is_collect_as_keys(self, value)

    def set_is_ethereal(self, value):
        zx.tp_set_is_ethereal(self, value)

    def set_is_potion_eater(self, value):
        zx.tp_set_is_potion_eater(self, value)

    def set_is_throwable(self, value):
        zx.tp_set_is_throwable(self, value)

    def set_is_usable(self, value):
        zx.tp_set_is_usable(self, value)

    def set_is_droppable(self, value):
        zx.tp_set_is_droppable(self, value)

    def set_is_bag_item_not_stackable(self, value):
        zx.tp_set_is_bag_item_not_stackable(self, value)

    def set_is_treasure_class_a(self, value):
        zx.tp_set_is_treasure_class_a(self, value)

    def set_is_bag(self, value):
        zx.tp_set_is_bag(self, value)

    def set_is_temporary_bag(self, value):
        zx.tp_set_is_temporary_bag(self, value)

    def set_is_chasm(self, value):
        zx.tp_set_is_chasm(self, value)

    def set_is_potion(self, value):
        zx.tp_set_is_potion(self, value)

    def set_is_floating(self, value):
        zx.tp_set_is_floating(self, value)

    def set_damage_doubled_from_acid(self, value):
        zx.tp_set_damage_doubled_from_acid(self, value)

    def set_damage_doubled_from_water(self, value):
        zx.tp_set_damage_doubled_from_water(self, value)

    def set_is_minion_generator(self, value):
        zx.tp_set_is_minion_generator(self, value)

    def set_is_treasure_type_eater(self, value):
        zx.tp_set_is_treasure_type_eater(self, value)

    def set_damage_doubled_from_acid(self, value):
        zx.tp_set_damage_doubled_from_acid(self, value)

    def set_is_acid_lover(self, value):
        zx.tp_set_is_acid_lover(self, value)

    def set_hates_acid(self, value):
        zx.tp_set_hates_acid(self, value)

    def set_is_jelly_parent(self, value):
        zx.tp_set_is_jelly_parent(self, value)

    def set_is_jelly_eater(self, value):
        zx.tp_set_is_jelly_eater(self, value)

    def set_is_jelly(self, value):
        zx.tp_set_is_jelly(self, value)

    def set_attack_eater(self, value):
        zx.tp_set_attack_eater(self, value)

    def set_is_able_to_jump_distance(self, value):
        zx.tp_set_is_able_to_jump_distance(self, value)

    def set_is_able_to_jump(self, value):
        zx.tp_set_is_able_to_jump(self, value)

    def set_is_acid(self, value):
        zx.tp_set_is_acid(self, value)

    def set_is_jelly_baby_eater(self, value):
        zx.tp_set_is_jelly_baby_eater(self, value)

    def set_is_jelly_baby(self, value):
        zx.tp_set_is_jelly_baby(self, value)

    def set_is_able_to_change_levels(self, value):
        zx.tp_set_is_able_to_change_levels(self, value)

    def set_is_collected_as_gold(self, value):
        zx.tp_set_is_collected_as_gold(self, value)

    def set_is_gold(self, value):
        zx.tp_set_is_gold(self, value)

    def set_is_loggable(self, value):
        zx.tp_set_is_loggable(self, value)

    def set_is_removeable_if_out_of_slots(self, value):
        zx.tp_set_is_removeable_if_out_of_slots(self, value)

    def set_is_smoke(self, value):
        zx.tp_set_is_smoke(self, value)

    def set_hates_fire(self, value):
        zx.tp_set_hates_fire(self, value)

    def set_is_treasure_type(self, value):
        zx.tp_set_is_treasure_type(self, value)

    def set_is_collectable(self, value):
        zx.tp_set_is_collectable(self, value)

    def set_is_resurrectable(self, value):
        zx.tp_set_is_resurrectable(self, value)

    def set_is_intelligent(self, value):
        zx.tp_set_is_intelligent(self, value)

    def set_damage_doubled_from_fire(self, value):
        zx.tp_set_damage_doubled_from_fire(self, value)

    def set_is_fire(self, value):
        zx.tp_set_is_fire(self, value)

    def set_is_dead_on_shove(self, value):
        zx.tp_set_is_dead_on_shove(self, value)

    def set_is_loggable(self, value):
        zx.tp_set_is_loggable(self, value)

    def set_is_brazier(self, value):
        zx.tp_set_is_brazier(self, value)

    def set_gfx_bounce_always(self, value):
        zx.tp_set_gfx_bounce_always(self, value)

    def set_normal_placement_rules(self, value):
        zx.tp_set_normal_placement_rules(self, value)

    def set_is_very_combustible(self, value):
        zx.tp_set_is_very_combustible(self, value)

    def set_is_combustible(self, value):
        zx.tp_set_is_combustible(self, value)

    def set_gfx_attack_anim(self, value):
        zx.tp_set_gfx_attack_anim(self, value)

    def set_attack_shove_chance_d1000(self, value):
        zx.tp_set_attack_shove_chance_d1000(self, value)

    def set_random_jump_chance_d1000(self, value):
        zx.tp_set_random_jump_chance_d1000(self, value)

    def set_is_able_to_jump_on_low_hp_chance_d1000(self, value):
        zx.tp_set_is_able_to_jump_on_low_hp_chance_d1000(self, value)

    def set_is_chasm(self, value):
        zx.tp_set_is_chasm(self, value)

    def set_is_hazard(self, value):
        zx.tp_set_is_hazard(self, value)

    def set_attack_shove(self, value):
        zx.tp_set_attack_shove(self, value)

    def set_is_shovable(self, value):
        zx.tp_set_is_shovable(self, value)

    def set_is_cursor_path(self, value):
        zx.tp_set_is_cursor_path(self, value)

    def set_is_blood_splatter(self, value):
        zx.tp_set_is_blood_splatter(self, value)

    def set_is_no_tile(self, value):
        zx.tp_set_is_no_tile(self, value)

    def set_is_msg(self, value):
        zx.tp_set_is_msg(self, value)

    def set_attack_lunge(self, value):
        zx.tp_set_attack_lunge(self, value)

    def set_stamina(self, value):
        zx.tp_set_stamina(self, value)

    def set_stat_strength(self, value):
        zx.tp_set_stat_strength(self, value)

    def set_stat_defence(self, value):
        zx.tp_set_stat_defence(self, value)

    def set_stat_attack(self, value):
        zx.tp_set_stat_attack(self, value)

    def set_stat_constitution(self, value):
        zx.tp_set_stat_constitution(self, value)

    def set_throw_distance(self, value):
        zx.tp_set_throw_distance(self, value)

    def set_lifespan_dice(self, value):
        zx.tp_set_lifespan_dice(self, value)

    def set_is_secret_door(self, value):
        zx.tp_set_is_secret_door(self, value)

    def set_is_cursor_can_hover_over(self, value):
        zx.tp_set_is_cursor_can_hover_over(self, value)

    def set_is_cursor(self, value):
        zx.tp_set_is_cursor(self, value)

    def set_gfx_dead_anim(self, value):
        zx.tp_set_gfx_dead_anim(self, value)

    def set_ai_obstacle(self, value):
        zx.tp_set_ai_obstacle(self, value)

    def set_is_attackable_by_monst(self, value):
        zx.tp_set_is_attackable_by_monst(self, value)

    def set_is_food(self, value):
        zx.tp_set_is_food(self, value)

    def set_hates_water(self, value):
        zx.tp_set_hates_water(self, value)

    def set_is_hunger_insatiable(self, value):
        zx.tp_set_is_hunger_insatiable(self, value)

    def set_is_undead(self, value):
        zx.tp_set_is_undead(self, value)

    def set_tick_catches_up_on_attack(self, value):
        zx.tp_set_tick_catches_up_on_attack(self, value)

    def set_nutrition_dice(self, value):
        zx.tp_set_nutrition_dice(self, value)

    def set_damage_melee_dice(self, value):
        zx.tp_set_damage_melee_dice(self, value)

    def set_damage_poison_dice(self, value):
        zx.tp_set_damage_poison_dice(self, value)

    def set_damage_crush_dice(self, value):
        zx.tp_set_damage_crush_dice(self, value)

    def set_damage_bite_dice(self, value):
        zx.tp_set_damage_bite_dice(self, value)

    def set_damage_swallow_dice(self, value):
        zx.tp_set_damage_swallow_dice(self, value)

    def set_gold_value_dice(self, value):
        zx.tp_set_gold_value_dice(self, value)

    def set_resurrect_dice(self, value):
        zx.tp_set_resurrect_dice(self, value)

    def set_collision_check(self, value):
        zx.tp_set_collision_check(self, value)

    def set_collision_attack(self, value):
        zx.tp_set_collision_attack(self, value)

    def set_is_water_lover(self, value):
        zx.tp_set_is_water_lover(self, value)

    def set_collision_hit_priority(self, value):
        zx.tp_set_collision_hit_priority(self, value)

    def set_collision_radius(self, value):
        zx.tp_set_collision_radius(self, value)

    def set_collision_attack_radius(self, value):
        zx.tp_set_collision_attack_radius(self, value)

    def set_gfx_bounce_on_move(self, value):
        zx.tp_set_gfx_bounce_on_move(self, value)

    def set_is_loggable(self, value):
        zx.tp_set_is_loggable(self, value)

    def set_is_bleeder(self, value):
        zx.tp_set_is_bleeder(self, value)

    def set_is_corpse_on_death(self, value):
        zx.tp_set_is_corpse_on_death(self, value)

    def set_is_meat_eater(self, value):
        zx.tp_set_is_meat_eater(self, value)

    def set_is_meat(self, value):
        zx.tp_set_is_meat(self, value)

    def set_is_tickable(self, value):
        zx.tp_set_is_tickable(self, value)

    def set_health_starving_pct(self, value):
        zx.tp_set_health_starving_pct(self, value)

    def set_health_initial_dice(self, value):
        zx.tp_set_health_initial_dice(self, value)

    def set_health_hunger_pct(self, value):
        zx.tp_set_health_hunger_pct(self, value)

    def set_stat_attack(self, value):
        zx.tp_set_stat_attack(self, value)

    def set_stat_defence(self, value):
        zx.tp_set_stat_defence(self, value)

    def set_ai_scent_distance(self, value):
        zx.tp_set_ai_scent_distance(self, value)

    def set_is_ripple(self, value):
        zx.tp_set_is_ripple(self, value)

    def set_light_strength(self, value):
        zx.tp_set_light_strength(self, value)

    def set_is_blood(self, value):
        zx.tp_set_is_blood(self, value)

    def set_gfx_animated_can_vflip(self, value):
        zx.tp_set_gfx_animated_can_vflip(self, value)

    def set_is_corridor(self, value):
        zx.tp_set_is_corridor(self, value)

    def set_gfx_oversized_and_on_floor(self, value):
        zx.tp_set_gfx_oversized_and_on_floor(self, value)

    def set_is_interesting(self, value):
        zx.tp_set_is_interesting(self, value)

    def set_is_descend_dungeon(self, value):
        zx.tp_set_is_descend_dungeon(self, value)

    def set_is_door(self, value):
        zx.tp_set_is_door(self, value)

    def set_is_ascend_dungeon(self, value):
        zx.tp_set_is_ascend_dungeon(self, value)

    def set_weapon_use_delay_hundredths(self, value):
        zx.tp_set_weapon_use_delay_hundredths(self, value)

    def set_collision_box(self, value):
        zx.tp_set_collision_box(self, value)

    def set_collision_circle(self, value):
        zx.tp_set_collision_circle(self, value)

    def set_weapon_damage(self, value):
        zx.tp_set_weapon_damage(self, value)

    def set_is_projectile(self, value):
        zx.tp_set_is_projectile(self, value)

    def set_is_explosion(self, value):
        zx.tp_set_is_explosion(self, value)

    def set_is_combustible(self, value):
        zx.tp_set_is_combustible(self, value)

    def set_weapon_use_distance(self, value):
        zx.tp_set_weapon_use_distance(self, value)

    def set_gfx_weapon_carry_anim(self, value):
        zx.tp_set_gfx_weapon_carry_anim(self, value)

    def set_gfx_attack_anim(self, value):
        zx.tp_set_gfx_attack_anim(self, value)

    def set_is_weapon(self, value):
        zx.tp_set_is_weapon(self, value)

    def set_gfx_show_outlined(self, value):
        zx.tp_set_gfx_show_outlined(self, value)

    def set_is_light_blocker(self, value):
        zx.tp_set_is_light_blocker(self, value)

    def set_z_depth(self, value):
        zx.tp_set_z_depth(self, value)

    def set_ascii_z_depth(self, value):
        zx.tp_set_ascii_z_depth(self, value)

    def set_z_prio(self, value):
        zx.tp_set_z_prio(self, value)

    def set_is_moveable(self, value):
        zx.tp_set_is_moveable(self, value)

    def set_gfx_animated_can_hflip(self, value):
        zx.tp_set_gfx_animated_can_hflip(self, value)

    def set_gfx_animated_can_vflip(self, value):
        zx.tp_set_gfx_animated_can_vflip(self, value)

    def set_is_obs_wall_or_door(self, value):
        zx.tp_set_is_obs_wall_or_door(self, value)

    def set_is_treasure_type(self, value):
        zx.tp_set_is_treasure_type(self, value)

    def set_is_wall(self, value):
        zx.tp_set_is_wall(self, value)

    def set_is_rock(self, value):
        zx.tp_set_is_rock(self, value)

    def set_is_floor(self, value):
        zx.tp_set_is_floor(self, value)

    def set_is_dirt(self, value):
        zx.tp_set_is_dirt(self, value)

    def set_is_lava(self, value):
        zx.tp_set_is_lava(self, value)

    def set_is_chasm(self, value):
        zx.tp_set_is_chasm(self, value)

    def set_gfx_water(self, value):
        zx.tp_set_gfx_water(self, value)

    def set_is_deep_water(self, value):
        zx.tp_set_is_deep_water(self, value)

    def set_gfx_short_shadow_caster(self, value):
        zx.tp_set_gfx_short_shadow_caster(self, value)
