import zx
import tp

def on_bite(me, x, y):
    sound = "growl{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    sound = "hiss{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_miss(me, hitter, x, y):
    sound = "hiss{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, "monst_death1"):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, "monst_death1")

def on_firing_at_something(me, target, x, y): # Return True on doing an action
    if zx.pcg_randint(1, 10) < 3:
        zx.thing_fire_at(me, "laser_energy", target)
        return True
    return False


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_avoid_distance(4)
    mytp.set_ai_is_able_to_attack_generators(False)
    mytp.set_ai_is_able_to_break_down_doors(False)
    mytp.set_ai_is_able_to_break_out_of_webs(False)
    mytp.set_ai_is_able_to_collect_keys(False)
    mytp.set_ai_is_able_to_detect_secret_doors_when_close(False)
    mytp.set_ai_is_able_to_enchant_weapons(False)
    mytp.set_ai_is_able_to_jump(False)
    mytp.set_ai_is_able_to_learn_skills(False)
    mytp.set_ai_is_able_to_open_doors(False)
    mytp.set_ai_is_able_to_remember_enemies_for_n_ticks(100)
    mytp.set_ai_is_able_to_see_through_doors(False)
    mytp.set_ai_is_able_to_shove(False)
    mytp.set_ai_is_able_to_walk_through_walls(False)
    mytp.set_ai_is_exit_finder(False)
    mytp.set_ai_is_item_collector(False)
    mytp.set_ai_is_level_explorer(False)
    mytp.set_ai_obstacle(False)
    mytp.set_ai_scent_distance(14)
    mytp.set_ai_vision_distance(8)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_living(False)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_attack(True)
    mytp.set_collision_box(False)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_acid(False)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_doubled_from_poison(False)
    mytp.set_damage_doubled_from_water(False)
    mytp.set_damage_melee_dice("2d6")
    mytp.set_enchant_level(False)
    mytp.set_enchant_max(False)
    mytp.set_gfx_an_animation_only(False)
    mytp.set_gfx_anim_attack("attack_claws")
    mytp.set_gfx_animated(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(False)
    mytp.set_gfx_animated_no_dir(False)
    mytp.set_gfx_attack_anim(False)
    mytp.set_gfx_bounce_always(False)
    mytp.set_gfx_bounce_on_move(False)
    mytp.set_gfx_dead_anim(False)
    mytp.set_gfx_flickers(False)
    mytp.set_gfx_glows(False)
    mytp.set_gfx_health_bar_autohide(False)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_long_shadow_caster(False)
    mytp.set_gfx_on_fire_anim(False)
    mytp.set_gfx_oversized_and_on_floor(False)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_shown_in_bg(False)
    mytp.set_gfx_solid_shadow(False)
    mytp.set_gfx_very_short_shadow_caster(False)
    mytp.set_gfx_water(False)
    mytp.set_gfx_weapon_carry_anim(False)
    mytp.set_hates_acid(False)
    mytp.set_hates_fire(100)
    mytp.set_hates_poison(False)
    mytp.set_hates_water(False)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("10d10")
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_able_to_fire_at(True)
    mytp.set_is_able_to_tire(True)
    mytp.set_is_acid(False)
    mytp.set_is_acid_lover(False)
    mytp.set_is_alive_on_end_of_anim(False)
    mytp.set_is_always_hit(False)
    mytp.set_is_ascend_dungeon(False)
    mytp.set_is_ascend_sewer(False)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_auto_collect_item(False)
    mytp.set_is_auto_throw(False)
    mytp.set_is_auto_use(False)
    mytp.set_is_bag(False)
    mytp.set_is_bag_item(False)
    mytp.set_is_bag_item_container(False)
    mytp.set_is_bag_item_not_stackable(False)
    mytp.set_is_barrel(False)
    mytp.set_is_bleeder(False)
    mytp.set_is_blood(False)
    mytp.set_is_blood_splatter(False)
    mytp.set_is_bones(False)
    mytp.set_is_brazier(False)
    mytp.set_is_bridge(False)
    mytp.set_is_burnable(False)
    mytp.set_is_carrier_of_treasure_class_a(False)
    mytp.set_is_carrier_of_treasure_class_b(False)
    mytp.set_is_carrier_of_treasure_class_c(False)
    mytp.set_is_chasm(False)
    mytp.set_is_collect_as_keys(False)
    mytp.set_is_collectable(False)
    mytp.set_is_collected_as_gold(False)
    mytp.set_is_combustible(False)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_corridor(False)
    mytp.set_is_critical_to_level(False)
    mytp.set_is_cursor(False)
    mytp.set_is_cursor_can_hover_over(False)
    mytp.set_is_cursor_can_hover_over_x2_click(False)
    mytp.set_is_cursor_path(False)
    mytp.set_is_dead_on_end_of_anim(False)
    mytp.set_is_dead_on_shove(False)
    mytp.set_is_debug_path(False)
    mytp.set_is_debug_type(False)
    mytp.set_is_deep_water(False)
    mytp.set_is_descend_dungeon(False)
    mytp.set_is_descend_sewer(False)
    mytp.set_is_described_when_hovering_over(True)
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
    mytp.set_is_extreme_hazard(False)
    mytp.set_is_fearless(False) # cannot enable as negates avoid_distance
    mytp.set_is_fire(False)
    mytp.set_is_floating(True)
    mytp.set_is_floor(False)
    mytp.set_is_floor_deco(False)
    mytp.set_is_foilage(False)
    mytp.set_is_food(False)
    mytp.set_is_food_eater(False)
    mytp.set_is_glass(False)
    mytp.set_is_gold(False)
    mytp.set_is_hazard(False)
    mytp.set_is_health_booster(False)
    mytp.set_is_hittable(True)
    mytp.set_is_humanoid(False)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_indestructible(False)
    mytp.set_is_intelligent(True)
    mytp.set_is_interesting(False)
    mytp.set_is_item(False)
    mytp.set_is_item_carrier(False)
    mytp.set_is_item_eater(False)
    mytp.set_is_item_organic(False)
    mytp.set_is_jelly(False)
    mytp.set_is_jelly_baby(False)
    mytp.set_is_jelly_baby_eater(False)
    mytp.set_is_jelly_eater(False)
    mytp.set_is_jelly_parent(False)
    mytp.set_is_key(False)
    mytp.set_is_killed_on_hit_or_miss(False)
    mytp.set_is_killed_on_hitting(False)
    mytp.set_is_laser(False)
    mytp.set_is_lava(False)
    mytp.set_is_light_blocker(False)
    mytp.set_is_living(False)
    mytp.set_is_loggable(True)
    mytp.set_is_meat(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_metal(False)
    mytp.set_is_minion(False)
    mytp.set_is_minion_generator(False)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_msg(False)
    mytp.set_is_no_tile(False)
    mytp.set_is_obs_destructable(False)
    mytp.set_is_obs_wall_or_door(False)
    mytp.set_is_openable(False)
    mytp.set_is_organic(False)
    mytp.set_is_player(False)
    mytp.set_is_poison(False)
    mytp.set_is_potion(False)
    mytp.set_is_potion_eater(False)
    mytp.set_is_projectile(False)
    mytp.set_is_removeable_if_out_of_slots(False)
    mytp.set_is_resurrectable(False)
    mytp.set_is_ripple(False)
    mytp.set_is_rock(False)
    mytp.set_is_rusty(False)
    mytp.set_is_secret_door(False)
    mytp.set_is_sewer_wall(False)
    mytp.set_is_shallow_water(False)
    mytp.set_is_shovable(True)
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
    mytp.set_is_tickable(True)
    mytp.set_is_tmp_thing(False)
    mytp.set_is_torch(False)
    mytp.set_is_treasure_class_a(False)
    mytp.set_is_treasure_class_b(False)
    mytp.set_is_treasure_class_c(False)
    mytp.set_is_treasure_type(False)
    mytp.set_is_treasure_type_chest(False)
    mytp.set_is_treasure_type_eater(False)
    mytp.set_is_undead(True)
    mytp.set_is_usable(False)
    mytp.set_is_used_when_thrown(False)
    mytp.set_is_very_combustible(False)
    mytp.set_is_wall(False)
    mytp.set_is_wall_dungeon(False)
    mytp.set_is_wand(False)
    mytp.set_is_wand_eater(False)
    mytp.set_is_water_lover(False)
    mytp.set_is_weapon(False)
    mytp.set_is_weapon_wielder(False)
    mytp.set_is_wooden(False)
    mytp.set_long_text_description("A floating mass of tentacles and eyeballs. These creatures are often employed to monitor the dark and dank dungeons with their impressive vision. Beware their lightning gaze...")
    mytp.set_loves_fire(False)
    mytp.set_loves_poison(False)
    mytp.set_loves_spiderwebs(False)
    mytp.set_monst_size(zx.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_bite_do("tentacleye.on_bite()")
    mytp.set_on_death_do("tentacleye.on_death()")
    mytp.set_on_death_drop_all_items(False)
    mytp.set_on_death_is_open(False)
    mytp.set_on_firing_at_something_do("tentacleye.on_firing_at_something()")
    mytp.set_on_hit_do("tentacleye.on_hit()")
    mytp.set_on_miss_do("tentacleye.on_miss()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(10)
    mytp.set_stat_defence(14)
    mytp.set_stat_strength(12)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A writhing mass of tentacles and eyeballs.")
    mytp.set_text_hits("slashes")
    mytp.set_unused_flag1(False)
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
    mytp.set_unused_flag2(False)
    mytp.set_unused_flag20(False)
    mytp.set_unused_flag21(False)
    mytp.set_unused_flag22(False)
    mytp.set_unused_flag23(False)
    mytp.set_unused_flag24(False)
    mytp.set_unused_flag25(False)
    mytp.set_unused_flag26(False)
    mytp.set_unused_flag27(False)
    mytp.set_unused_flag28(False)
    mytp.set_unused_flag29(False)
    mytp.set_unused_flag3(False)
    mytp.set_unused_flag30(False)
    mytp.set_unused_flag31(False)
    mytp.set_unused_flag32(False)
    mytp.set_unused_flag33(False)
    mytp.set_unused_flag34(False)
    mytp.set_unused_flag35(False)
    mytp.set_unused_flag36(False)
    mytp.set_unused_flag37(False)
    mytp.set_unused_flag38(False)
    mytp.set_unused_flag39(False)
    mytp.set_unused_flag4(False)
    mytp.set_unused_flag40(False)
    mytp.set_unused_flag41(False)
    mytp.set_unused_flag5(False)
    mytp.set_unused_flag6(False)
    mytp.set_unused_flag7(False)
    mytp.set_unused_flag8(False)
    mytp.set_unused_flag9(False)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 300
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.100", is_hp_25_percent=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="tentacleye", text_name="lesser tentacleye")

init()

