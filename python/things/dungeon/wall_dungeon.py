import my
import tp


def tp_init(name,
            tiles=[],
            left1_tiles=[],
            right1_tiles=[],
            top1_tiles=[],
            bot1_tiles=[],
            tl1_tiles=[],
            tr1_tiles=[],
            bl1_tiles=[],
            br1_tiles=[],
            left2_tiles=[],
            right2_tiles=[],
            top2_tiles=[],
            bot2_tiles=[],
            tl2_tiles=[],
            tr2_tiles=[],
            bl2_tiles=[],
            br2_tiles=[]):

    mytp = tp.Tp(name, "dungeon wall")
    mytp.set_ai_is_able_to_attack_generators(False)
    mytp.set_ai_is_able_to_break_down_doors(False)
    mytp.set_ai_is_able_to_break_out_of_webs(False)
    mytp.set_ai_is_able_to_collect_keys(False)
    mytp.set_ai_is_able_to_detect_secret_doors_when_close(False)
    mytp.set_ai_is_able_to_enchant_weapons(False)
    mytp.set_ai_is_able_to_jump(False)
    mytp.set_ai_is_able_to_learn_skills(False)
    mytp.set_ai_is_able_to_open_doors(False)
    mytp.set_ai_is_able_to_see_through_doors(False)
    mytp.set_ai_is_able_to_shove(False)
    mytp.set_ai_is_able_to_walk_through_walls(False)
    mytp.set_ai_is_exit_finder(False)
    mytp.set_ai_is_item_collector(False)
    mytp.set_ai_is_level_explorer(False)
    mytp.set_ai_obstacle(True)
    mytp.set_ai_resent_count(False)
    mytp.set_ai_wanderer(False)
    mytp.set_attack_blood(False)
    mytp.set_attack_eater(False)
    mytp.set_attack_humanoid(False)
    mytp.set_attack_living(False)
    mytp.set_attack_lunge(False)
    mytp.set_attack_meat(False)
    mytp.set_attack_undead(False)
    mytp.set_collision_check(False)
    mytp.set_collision_hit_priority(False)
    mytp.set_enchant_level(False)
    mytp.set_enchant_max(False)
    mytp.set_environ_damage_doubled_from_acid(False)
    mytp.set_environ_damage_doubled_from_fire(False)
    mytp.set_environ_damage_doubled_from_poison(False)
    mytp.set_environ_damage_doubled_from_water(False)
    mytp.set_environ_dislikes_acid(False)
    mytp.set_environ_dislikes_fire(False)
    mytp.set_environ_dislikes_poison(False)
    mytp.set_environ_dislikes_water(False)
    mytp.set_environ_hates_acid(False)
    mytp.set_environ_hates_fire(False)
    mytp.set_environ_hates_poison(False)
    mytp.set_environ_hates_water(False)
    mytp.set_environ_loves_acid(False)
    mytp.set_environ_loves_fire(False)
    mytp.set_environ_loves_poison(False)
    mytp.set_environ_loves_spiderwebs(False)
    mytp.set_environ_loves_water(False)
    mytp.set_gfx_an_animation_only(False)
    mytp.set_gfx_animated_can_hflip(False)
    mytp.set_gfx_animated_can_vflip(False)
    mytp.set_gfx_animated(False)
    mytp.set_gfx_animated_no_dir(False)
    mytp.set_gfx_attack_anim(False)
    mytp.set_gfx_bounce_always(False)
    mytp.set_gfx_bounce_on_move(False)
    mytp.set_gfx_dead_anim(False)
    mytp.set_gfx_equip_carry_anim(False)
    mytp.set_gfx_flickers(False)
    mytp.set_gfx_glows(False)
    mytp.set_gfx_health_bar_autohide(False)
    mytp.set_gfx_health_bar_shown(False)
    mytp.set_gfx_long_shadow_caster(False)
    mytp.set_gfx_on_fire_anim(False)
    mytp.set_gfx_oversized_and_on_floor(False)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_gfx_solid_shadow(False)
    mytp.set_gfx_very_short_shadow_caster(False)
    mytp.set_gfx_water(False)
    mytp.set_health_initial_dice("25d10")
    mytp.set_is_able_to_change_levels(False)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_able_to_fire_at(False)
    mytp.set_is_able_to_see_in_the_dark(False)
    mytp.set_is_able_to_tire(False)
    mytp.set_is_acid(False)
    mytp.set_is_alive_on_end_of_anim(False)
    mytp.set_is_always_hit(False)
    mytp.set_is_ascend_dungeon(False)
    mytp.set_is_ascend_sewer(False)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_auto_collect_item(False)
    mytp.set_is_auto_equipped(False)
    mytp.set_is_auto_throw(False)
    mytp.set_is_auto_use(False)
    mytp.set_is_bag(False)
    mytp.set_is_bag_item_container(False)
    mytp.set_is_bag_item(False)
    mytp.set_is_bag_item_not_stackable(False)
    mytp.set_is_barrel(False)
    mytp.set_is_bleeder(False)
    mytp.set_is_blood_eater(False)
    mytp.set_is_blood(False)
    mytp.set_is_blood_splatter(False)
    mytp.set_is_bones(False)
    mytp.set_is_brazier(False)
    mytp.set_is_bridge(False)
    mytp.set_is_buff(False)
    mytp.set_is_burnable(False)
    mytp.set_is_carrier_of_treasure_class_a(False)
    mytp.set_is_carrier_of_treasure_class_b(False)
    mytp.set_is_carrier_of_treasure_class_c(False)
    mytp.set_is_chasm(False)
    mytp.set_is_collectable(False)
    mytp.set_is_collect_as_keys(False)
    mytp.set_is_collected_as_gold(False)
    mytp.set_is_combustible(False)
    mytp.set_is_corpse_on_death(False)
    mytp.set_is_corridor(False)
    mytp.set_is_critical_to_level(False)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_cursor_can_hover_over_x2_click(False)
    mytp.set_is_cursor_path(False)
    mytp.set_is_cursor_path_hazard_for_player(False)
    mytp.set_is_dead_on_end_of_anim(False)
    mytp.set_is_dead_on_shove(False)
    mytp.set_is_debuff(False)
    mytp.set_is_debug_path(False)
    mytp.set_is_debug_type(False)
    mytp.set_is_deep_water(False)
    mytp.set_is_descend_dungeon(False)
    mytp.set_is_descend_sewer(False)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_destroyed_on_hit_or_miss(False)
    mytp.set_is_destroyed_on_hitting(False)
    mytp.set_is_dirt(False)
    mytp.set_is_door(False)
    mytp.set_is_droppable(False)
    mytp.set_is_dry_grass(False)
    mytp.set_is_enchantable(False)
    mytp.set_is_enchantstone(False)
    mytp.set_is_engulfer(False)
    mytp.set_is_ethereal(False)
    mytp.set_is_ethereal_minion_generator(False)
    mytp.set_is_explosion(False)
    mytp.set_is_fearless(False)
    mytp.set_is_fire(False)
    mytp.set_is_floating(False)
    mytp.set_is_floor_deco(False)
    mytp.set_is_floor(False)
    mytp.set_is_foilage(False)
    mytp.set_is_food_eater(False)
    mytp.set_is_food(False)
    mytp.set_is_gfx_anim_synced_with_owner(False)
    mytp.set_is_glass(False)
    mytp.set_is_gold(False)
    mytp.set_is_hazard(False)
    mytp.set_is_health_booster(False)
    mytp.set_is_hittable(True)
    mytp.set_is_humanoid(False)
    mytp.set_is_hunger_insatiable(False)
    mytp.set_is_indestructible(False)
    mytp.set_is_intelligent(False)
    mytp.set_is_interesting(False)
    mytp.set_is_item_carrier(False)
    mytp.set_is_item_eater(False)
    mytp.set_is_item(False)
    mytp.set_is_item_magical_eater(False)
    mytp.set_is_item_magical(False)
    mytp.set_is_item_organic(False)
    mytp.set_is_jelly_baby_eater(False)
    mytp.set_is_jelly_baby(False)
    mytp.set_is_jelly_eater(False)
    mytp.set_is_jelly(False)
    mytp.set_is_jelly_parent(False)
    mytp.set_is_key(False)
    mytp.set_is_laser(False)
    mytp.set_is_lava(False)
    mytp.set_is_light_blocker(True)
    mytp.set_is_living(False)
    mytp.set_is_loggable(False)
    mytp.set_is_meat_eater(False)
    mytp.set_is_meat(False)
    mytp.set_is_metal(False)
    mytp.set_is_minion(False)
    mytp.set_is_minion_generator(False)
    mytp.set_is_monst(False)
    mytp.set_is_moveable(False)
    mytp.set_is_msg(False)
    mytp.set_is_no_tile(False)
    mytp.set_is_obs_destructable(False)
    mytp.set_is_obs_wall_or_door(True)
    mytp.set_is_openable(False)
    mytp.set_is_organic(False)
    mytp.set_is_player(False)
    mytp.set_is_poison(False)
    mytp.set_is_potion_eater(False)
    mytp.set_is_potion(False)
    mytp.set_is_projectile(False)
    mytp.set_is_removeable_if_out_of_slots(False)
    mytp.set_is_resurrectable(False)
    mytp.set_is_ring(False)
    mytp.set_is_ripple(False)
    mytp.set_is_rock(False)
    mytp.set_is_rusty(False)
    mytp.set_is_secret_door(False)
    mytp.set_is_sewer_wall(False)
    mytp.set_is_shallow_water(False)
    mytp.set_is_shovable(False)
    mytp.set_is_skill(False)
    mytp.set_is_skillstone(False)
    mytp.set_is_smoke(False)
    mytp.set_is_soft_body(False)
    mytp.set_is_spawner(False)
    mytp.set_is_spiderweb(False)
    mytp.set_is_sticky(False)
    mytp.set_is_stone(False)
    mytp.set_is_sword(False)
    mytp.set_is_target_auto_select(False)
    mytp.set_is_the_grid(False)
    mytp.set_is_throwable(False)
    mytp.set_is_tickable(False)
    mytp.set_is_tmp_thing(False)
    mytp.set_is_torch(False)
    mytp.set_is_treasure_class_a(False)
    mytp.set_is_treasure_class_b(False)
    mytp.set_is_treasure_class_c(False)
    mytp.set_is_treasure_type_chest(False)
    mytp.set_is_treasure_type_eater(False)
    mytp.set_is_treasure_type(False)
    mytp.set_is_undead(False)
    mytp.set_is_usable(False)
    mytp.set_is_used_when_thrown(False)
    mytp.set_is_very_combustible(False)
    mytp.set_is_wall_dungeon(True)
    mytp.set_is_wall(True)
    mytp.set_is_wand(False)
    mytp.set_is_weapon_equiper(False)
    mytp.set_is_weapon(False)
    mytp.set_is_wooden(False)
    mytp.set_normal_placement_rules(False)
    mytp.set_on_death_drop_all_items(False)
    mytp.set_on_death_is_open(False)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A moss covered wall.")
    mytp.set_unused_flag10(False)
    mytp.set_unused_flag11(False)
    mytp.set_unused_flag12(False)
    mytp.set_unused_flag13(False)
    mytp.set_unused_flag14(False)
    mytp.set_unused_flag15(False)
    mytp.set_unused_flag16(False)
    mytp.set_unused_flag17(False)
    mytp.set_unused_flag18(False)
    mytp.set_unused_flag19(False)
    mytp.set_unused_flag1(False)
    mytp.set_unused_flag20(False)
    mytp.set_unused_flag21(False)
    mytp.set_unused_flag22(False)
    mytp.set_unused_flag23(False)
    mytp.set_unused_flag24(False)
    mytp.set_unused_flag25(False)
    mytp.set_unused_flag2(False)
    mytp.set_unused_flag30(False)
    mytp.set_unused_flag3(False)
    mytp.set_unused_flag4(False)
    mytp.set_unused_flag5(False)
    mytp.set_unused_flag6(False)
    mytp.set_unused_flag7(False)
    mytp.set_unused_flag8(False)
    mytp.set_unused_flag9(False)
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    if tiles is not None:
        for t in tiles:
            mytp.set_tile(t)
    else:
        mytp.set_tile(tile=name)

    if left1_tiles is not None:
        for t in left1_tiles:
            mytp.set_left1_tile(t)
    else:
        mytp.set_left1_tile(left1_tile=name)

    if right1_tiles is not None:
        for t in right1_tiles:
            mytp.set_right1_tile(t)
    else:
        mytp.set_right1_tile(right1_tile=name)

    if top1_tiles is not None:
        for t in top1_tiles:
            mytp.set_top1_tile(t)
    else:
        mytp.set_top1_tile(top1_tile=name)

    if bot1_tiles is not None:
        for t in bot1_tiles:
            mytp.set_bot1_tile(t)
    else:
        mytp.set_bot1_tile(bot1_tile=name)

    if tl1_tiles is not None:
        for t in tl1_tiles:
            mytp.set_tl1_tile(t)
    else:
        mytp.set_tl1_tile(tl1_tile=name)

    if tr1_tiles is not None:
        for t in tr1_tiles:
            mytp.set_tr1_tile(t)
    else:
        mytp.set_tr1_tile(tr1_tile=name)

    if bl1_tiles is not None:
        for t in bl1_tiles:
            mytp.set_bl1_tile(t)
    else:
        mytp.set_bl1_tile(bl1_tile=name)

    if br1_tiles is not None:
        for t in br1_tiles:
            mytp.set_br1_tile(t)
    else:
        mytp.set_br1_tile(br1_tile=name)

    if left2_tiles is not None:
        for t in left2_tiles:
            mytp.set_left2_tile(t)
    else:
        mytp.set_left2_tile(left2_tile=name)

    if right2_tiles is not None:
        for t in right2_tiles:
            mytp.set_right2_tile(t)
    else:
        mytp.set_right2_tile(right2_tile=name)

    if top2_tiles is not None:
        for t in top2_tiles:
            mytp.set_top2_tile(t)
    else:
        mytp.set_top2_tile(top2_tile=name)

    if bot2_tiles is not None:
        for t in bot2_tiles:
            mytp.set_bot2_tile(t)
    else:
        mytp.set_bot2_tile(bot2_tile=name)

    if tl2_tiles is not None:
        for t in tl2_tiles:
            mytp.set_tl2_tile(t)
    else:
        mytp.set_tl2_tile(tl2_tile=name)

    if tr2_tiles is not None:
        for t in tr2_tiles:
            mytp.set_tr2_tile(t)
    else:
        mytp.set_tr2_tile(tr2_tile=name)

    if bl2_tiles is not None:
        for t in bl2_tiles:
            mytp.set_bl2_tile(t)
    else:
        mytp.set_bl2_tile(bl2_tile=name)

    if br2_tiles is not None:
        for t in br2_tiles:
            mytp.set_br2_tile(t)
    else:
        mytp.set_br2_tile(br2_tile=name)

    mytp.update()

def init():
    tp_init(name="wall_dungeon.1",
            tiles=[      
                "wall_dungeon.1.1",
                "wall_dungeon.1.2",
                "wall_dungeon.1.3",
                "wall_dungeon.1.4",
                         
                "wall_dungeon.1.5",
                "wall_dungeon.1.6",
                "wall_dungeon.1.7",
                "wall_dungeon.1.8",
                         
                "wall_dungeon.1.9",
                "wall_dungeon.1.10",
                "wall_dungeon.1.11",
                "wall_dungeon.1.12",
                         
                "wall_dungeon.1.13",
                "wall_dungeon.1.14",
                "wall_dungeon.1.15",
                "wall_dungeon.1.16",
                         
                "wall_dungeon.1.17",
                "wall_dungeon.1.18",
                "wall_dungeon.1.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

    tp_init(name="wall_dungeon.2",
            tiles=[      
                "wall_dungeon.2.1",
                "wall_dungeon.2.2",
                "wall_dungeon.2.3",
                "wall_dungeon.2.4",
                         
                "wall_dungeon.2.5",
                "wall_dungeon.2.6",
                "wall_dungeon.2.7",
                "wall_dungeon.2.8",
                         
                "wall_dungeon.2.9",
                "wall_dungeon.2.10",
                "wall_dungeon.2.11",
                "wall_dungeon.2.12",
                         
                "wall_dungeon.2.13",
                "wall_dungeon.2.14",
                "wall_dungeon.2.15",
                "wall_dungeon.2.16",
                         
                "wall_dungeon.2.17",
                "wall_dungeon.2.18",
                "wall_dungeon.2.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

    tp_init(name="wall_dungeon.3",
            tiles=[      
                "wall_dungeon.3.1",
                "wall_dungeon.3.2",
                "wall_dungeon.3.3",
                "wall_dungeon.3.4",
                         
                "wall_dungeon.3.5",
                "wall_dungeon.3.6",
                "wall_dungeon.3.7",
                "wall_dungeon.3.8",
                         
                "wall_dungeon.3.9",
                "wall_dungeon.3.10",
                "wall_dungeon.3.11",
                "wall_dungeon.3.12",
                         
                "wall_dungeon.3.13",
                "wall_dungeon.3.14",
                "wall_dungeon.3.15",
                "wall_dungeon.3.16",
                         
                "wall_dungeon.3.17",
                "wall_dungeon.3.18",
                "wall_dungeon.3.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

    tp_init(name="wall_dungeon.4",
            tiles=[      
                "wall_dungeon.4.1",
                "wall_dungeon.4.2",
                "wall_dungeon.4.3",
                "wall_dungeon.4.4",
                         
                "wall_dungeon.4.5",
                "wall_dungeon.4.6",
                "wall_dungeon.4.7",
                "wall_dungeon.4.8",
                         
                "wall_dungeon.4.9",
                "wall_dungeon.4.10",
                "wall_dungeon.4.11",
                "wall_dungeon.4.12",
                         
                "wall_dungeon.4.13",
                "wall_dungeon.4.14",
                "wall_dungeon.4.15",
                "wall_dungeon.4.16",
                         
                "wall_dungeon.4.17",
                "wall_dungeon.4.18",
                "wall_dungeon.4.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

    tp_init(name="wall_dungeon.5",
            tiles=[      
                "wall_dungeon.5.1",
                "wall_dungeon.5.2",
                "wall_dungeon.5.3",
                "wall_dungeon.5.4",
                         
                "wall_dungeon.5.5",
                "wall_dungeon.5.6",
                "wall_dungeon.5.7",
                "wall_dungeon.5.8",
                         
                "wall_dungeon.5.9",
                "wall_dungeon.5.10",
                "wall_dungeon.5.11",
                "wall_dungeon.5.12",
                         
                "wall_dungeon.5.13",
                "wall_dungeon.5.14",
                "wall_dungeon.5.15",
                "wall_dungeon.5.16",
                         
                "wall_dungeon.5.17",
                "wall_dungeon.5.18",
                "wall_dungeon.5.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

    tp_init(name="wall_dungeon.6",
            tiles=[      
                "wall_dungeon.6.1",
                "wall_dungeon.6.2",
                "wall_dungeon.6.3",
                "wall_dungeon.6.4",
                         
                "wall_dungeon.6.5",
                "wall_dungeon.6.6",
                "wall_dungeon.6.7",
                "wall_dungeon.6.8",
                         
                "wall_dungeon.6.9",
                "wall_dungeon.6.10",
                "wall_dungeon.6.11",
                "wall_dungeon.6.12",
                         
                "wall_dungeon.6.13",
                "wall_dungeon.6.14",
                "wall_dungeon.6.15",
                "wall_dungeon.6.16",
                         
                "wall_dungeon.6.17",
                "wall_dungeon.6.18",
                "wall_dungeon.6.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.7",
            tiles=[      
                "wall_dungeon.7.1",
                "wall_dungeon.7.2",
                "wall_dungeon.7.3",
                "wall_dungeon.7.4",
                         
                "wall_dungeon.7.5",
                "wall_dungeon.7.6",
                "wall_dungeon.7.7",
                "wall_dungeon.7.8",
                         
                "wall_dungeon.7.9",
                "wall_dungeon.7.10",
                "wall_dungeon.7.11",
                "wall_dungeon.7.12",
                         
                "wall_dungeon.7.13",
                "wall_dungeon.7.14",
                "wall_dungeon.7.15",
                "wall_dungeon.7.16",
                         
                "wall_dungeon.7.17",
                "wall_dungeon.7.18",
                "wall_dungeon.7.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.8",
            tiles=[      
                "wall_dungeon.8.1",
                "wall_dungeon.8.2",
                "wall_dungeon.8.3",
                "wall_dungeon.8.4",
                         
                "wall_dungeon.8.5",
                "wall_dungeon.8.6",
                "wall_dungeon.8.7",
                "wall_dungeon.8.8",
                         
                "wall_dungeon.8.9",
                "wall_dungeon.8.10",
                "wall_dungeon.8.11",
                "wall_dungeon.8.12",
                         
                "wall_dungeon.8.13",
                "wall_dungeon.8.14",
                "wall_dungeon.8.15",
                "wall_dungeon.8.16",
                         
                "wall_dungeon.8.17",
                "wall_dungeon.8.18",
                "wall_dungeon.8.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.9",
            tiles=[      
                "wall_dungeon.9.1",
                "wall_dungeon.9.2",
                "wall_dungeon.9.3",
                "wall_dungeon.9.4",
                         
                "wall_dungeon.9.5",
                "wall_dungeon.9.6",
                "wall_dungeon.9.7",
                "wall_dungeon.9.8",
                         
                "wall_dungeon.9.9",
                "wall_dungeon.9.10",
                "wall_dungeon.9.11",
                "wall_dungeon.9.12",
                         
                "wall_dungeon.9.13",
                "wall_dungeon.9.14",
                "wall_dungeon.9.15",
                "wall_dungeon.9.16",
                         
                "wall_dungeon.9.17",
                "wall_dungeon.9.18",
                "wall_dungeon.9.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.10",
            tiles=[      
                "wall_dungeon.10.1",
                "wall_dungeon.10.2",
                "wall_dungeon.10.3",
                "wall_dungeon.10.4",
                         
                "wall_dungeon.10.5",
                "wall_dungeon.10.6",
                "wall_dungeon.10.7",
                "wall_dungeon.10.8",
                         
                "wall_dungeon.10.9",
                "wall_dungeon.10.10",
                "wall_dungeon.10.11",
                "wall_dungeon.10.12",
                         
                "wall_dungeon.10.13",
                "wall_dungeon.10.14",
                "wall_dungeon.10.15",
                "wall_dungeon.10.16",
                         
                "wall_dungeon.10.17",
                "wall_dungeon.10.18",
                "wall_dungeon.10.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.11",
            tiles=[      
                "wall_dungeon.11.1",
                "wall_dungeon.11.2",
                "wall_dungeon.11.3",
                "wall_dungeon.11.4",
                         
                "wall_dungeon.11.5",
                "wall_dungeon.11.6",
                "wall_dungeon.11.7",
                "wall_dungeon.11.8",
                         
                "wall_dungeon.11.9",
                "wall_dungeon.11.10",
                "wall_dungeon.11.11",
                "wall_dungeon.11.12",
                         
                "wall_dungeon.11.13",
                "wall_dungeon.11.14",
                "wall_dungeon.11.15",
                "wall_dungeon.11.16",
                         
                "wall_dungeon.11.17",
                "wall_dungeon.11.18",
                "wall_dungeon.11.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )
    tp_init(name="wall_dungeon.12",
            tiles=[      
                "wall_dungeon.12.1",
                "wall_dungeon.12.2",
                "wall_dungeon.12.3",
                "wall_dungeon.12.4",
                         
                "wall_dungeon.12.5",
                "wall_dungeon.12.6",
                "wall_dungeon.12.7",
                "wall_dungeon.12.8",
                         
                "wall_dungeon.12.9",
                "wall_dungeon.12.10",
                "wall_dungeon.12.11",
                "wall_dungeon.12.12",
                         
                "wall_dungeon.12.13",
                "wall_dungeon.12.14",
                "wall_dungeon.12.15",
                "wall_dungeon.12.16",
                         
                "wall_dungeon.12.17",
                "wall_dungeon.12.18",
                "wall_dungeon.12.19",
                ],
            left1_tiles=[
                "wall_deco1.left.1",
                "wall_deco2.left.1",
                "wall_deco1.left.2",
                "wall_deco2.left.2",
                         
                "wall_deco1.left.3",
                "wall_deco2.left.3",
                "wall_deco1.left.4",
                "wall_deco2.left.4",
                         
                "wall_deco1.left.5",
                "wall_deco2.left.5",
                "wall_deco1.left.6",
                "wall_deco2.left.6",
                ],
            right1_tiles=[
                "wall_deco1.right.1",
                "wall_deco2.right.1",
                "wall_deco1.right.2",
                "wall_deco2.right.2",
                         
                "wall_deco1.right.3",
                "wall_deco2.right.3",
                "wall_deco1.right.4",
                "wall_deco2.right.4",
                         
                "wall_deco1.right.5",
                "wall_deco2.right.5",
                "wall_deco1.right.6",
                "wall_deco2.right.6",
                ],
            top1_tiles=[ 
                "wall_deco1.top.1",
                "wall_deco2.top.1",
                "wall_deco1.top.2",
                "wall_deco2.top.2",
                         
                "wall_deco1.top.3",
                "wall_deco2.top.3",
                "wall_deco1.top.4",
                "wall_deco2.top.4",
                         
                "wall_deco1.top.5",
                "wall_deco2.top.5",
                "wall_deco1.top.6",
                "wall_deco2.top.6",
                         
                "wall_deco1.top.7",
                "wall_deco2.top.7",
                ],
            bot1_tiles=[ 
                "wall_deco1.bot.1",
                "wall_deco2.bot.1",
                "wall_deco1.bot.2",
                "wall_deco2.bot.2",
                         
                "wall_deco1.bot.3",
                "wall_deco2.bot.3",
                "wall_deco1.bot.4",
                "wall_deco2.bot.4",
                         
                "wall_deco1.bot.5",
                "wall_deco2.bot.5",
                "wall_deco1.bot.6",
                "wall_deco2.bot.6",
                         
                "wall_deco1.bot.7",
                "wall_deco2.bot.7",
                ],
            tl1_tiles=[  
                "wall_deco1.tl.1",
                "wall_deco2.tl.1",
                "wall_deco1.tl.2",
                "wall_deco2.tl.2",
                         
                "wall_deco1.tl.3",
                "wall_deco2.tl.3",
                "wall_deco1.tl.4",
                "wall_deco2.tl.4",
                         
                "wall_deco1.tl.5",
                "wall_deco2.tl.5",
                "wall_deco1.tl.6",
                "wall_deco2.tl.6",
                ],
            tr1_tiles=[  
                "wall_deco1.tr.1",
                "wall_deco2.tr.1",
                "wall_deco1.tr.2",
                "wall_deco2.tr.2",
                         
                "wall_deco1.tr.3",
                "wall_deco2.tr.3",
                "wall_deco1.tr.4",
                "wall_deco2.tr.4",
                         
                "wall_deco1.tr.5",
                "wall_deco2.tr.5",
                "wall_deco1.tr.6",
                "wall_deco2.tr.6",
                ],
            br1_tiles=[  
                "wall_deco1.br.1",
                "wall_deco2.br.1",
                "wall_deco1.br.2",
                "wall_deco2.br.2",
                         
                "wall_deco1.br.3",
                "wall_deco2.br.3",
                "wall_deco1.br.4",
                "wall_deco2.br.4",
                         
                "wall_deco1.br.5",
                "wall_deco2.br.5",
                "wall_deco1.br.6",
                "wall_deco2.br.6",
                ],
            bl1_tiles=[  
                "wall_deco1.bl.1",
                "wall_deco2.bl.1",
                "wall_deco1.bl.2",
                "wall_deco2.bl.2",
                         
                "wall_deco1.bl.3",
                "wall_deco2.bl.3",
                "wall_deco1.bl.4",
                "wall_deco2.bl.4",
                         
                "wall_deco1.bl.5",
                "wall_deco2.bl.5",
                "wall_deco1.bl.6",
                "wall_deco2.bl.6",
                ],
            left2_tiles=[
                "wall_shadow_deco1.left.1",
                "wall_shadow_deco2.left.1",
                "wall_shadow_deco1.left.2",
                "wall_shadow_deco2.left.2",
                         
                "wall_shadow_deco1.left.3",
                "wall_shadow_deco2.left.3",
                "wall_shadow_deco1.left.4",
                "wall_shadow_deco2.left.4",
                         
                "wall_shadow_deco1.left.5",
                "wall_shadow_deco2.left.5",
                "wall_shadow_deco1.left.6",
                "wall_shadow_deco2.left.6",
                ],
            right2_tiles=[
                "wall_shadow_deco1.right.1",
                "wall_shadow_deco2.right.1",
                "wall_shadow_deco1.right.2",
                "wall_shadow_deco2.right.2",
                         
                "wall_shadow_deco1.right.3",
                "wall_shadow_deco2.right.3",
                "wall_shadow_deco1.right.4",
                "wall_shadow_deco2.right.4",
                         
                "wall_shadow_deco1.right.5",
                "wall_shadow_deco2.right.5",
                "wall_shadow_deco1.right.6",
                "wall_shadow_deco2.right.6",
                ],
            top2_tiles=[ 
                "wall_shadow_deco1.top.1",
                "wall_shadow_deco2.top.1",
                "wall_shadow_deco1.top.2",
                "wall_shadow_deco2.top.2",
                         
                "wall_shadow_deco1.top.3",
                "wall_shadow_deco2.top.3",
                "wall_shadow_deco1.top.4",
                "wall_shadow_deco2.top.4",
                         
                "wall_shadow_deco1.top.5",
                "wall_shadow_deco2.top.5",
                "wall_shadow_deco1.top.6",
                "wall_shadow_deco2.top.6",
                         
                "wall_shadow_deco1.top.7",
                "wall_shadow_deco2.top.7",
                ],
            bot2_tiles=[ 
                "wall_shadow_deco1.bot.1",
                "wall_shadow_deco2.bot.1",
                "wall_shadow_deco1.bot.2",
                "wall_shadow_deco2.bot.2",
                         
                "wall_shadow_deco1.bot.3",
                "wall_shadow_deco2.bot.3",
                "wall_shadow_deco1.bot.4",
                "wall_shadow_deco2.bot.4",
                         
                "wall_shadow_deco1.bot.5",
                "wall_shadow_deco2.bot.5",
                "wall_shadow_deco1.bot.6",
                "wall_shadow_deco2.bot.6",
                         
                "wall_shadow_deco1.bot.7",
                "wall_shadow_deco2.bot.7",
                ],
            tl2_tiles=[  
                "wall_shadow_deco1.tl.1",
                "wall_shadow_deco2.tl.1",
                "wall_shadow_deco1.tl.2",
                "wall_shadow_deco2.tl.2",
                         
                "wall_shadow_deco1.tl.3",
                "wall_shadow_deco2.tl.3",
                "wall_shadow_deco1.tl.4",
                "wall_shadow_deco2.tl.4",
                         
                "wall_shadow_deco1.tl.5",
                "wall_shadow_deco2.tl.5",
                "wall_shadow_deco1.tl.6",
                "wall_shadow_deco2.tl.6",
                ],
            tr2_tiles=[  
                "wall_shadow_deco1.tr.1",
                "wall_shadow_deco2.tr.1",
                "wall_shadow_deco1.tr.2",
                "wall_shadow_deco2.tr.2",
                         
                "wall_shadow_deco1.tr.3",
                "wall_shadow_deco2.tr.3",
                "wall_shadow_deco1.tr.4",
                "wall_shadow_deco2.tr.4",
                         
                "wall_shadow_deco1.tr.5",
                "wall_shadow_deco2.tr.5",
                "wall_shadow_deco1.tr.6",
                "wall_shadow_deco2.tr.6",
                ],
            br2_tiles=[  
                "wall_shadow_deco1.br.1",
                "wall_shadow_deco2.br.1",
                "wall_shadow_deco1.br.2",
                "wall_shadow_deco2.br.2",
                         
                "wall_shadow_deco1.br.3",
                "wall_shadow_deco2.br.3",
                "wall_shadow_deco1.br.4",
                "wall_shadow_deco2.br.4",
                         
                "wall_shadow_deco1.br.5",
                "wall_shadow_deco2.br.5",
                "wall_shadow_deco1.br.6",
                "wall_shadow_deco2.br.6",
                ],
            bl2_tiles=[  
                "wall_shadow_deco1.bl.1",
                "wall_shadow_deco2.bl.1",
                "wall_shadow_deco1.bl.2",
                "wall_shadow_deco2.bl.2",
                         
                "wall_shadow_deco1.bl.3",
                "wall_shadow_deco2.bl.3",
                "wall_shadow_deco1.bl.4",
                "wall_shadow_deco2.bl.4",
                         
                "wall_shadow_deco1.bl.5",
                "wall_shadow_deco2.bl.5",
                "wall_shadow_deco1.bl.6",
                "wall_shadow_deco2.bl.6",
                ],
            )

init()
