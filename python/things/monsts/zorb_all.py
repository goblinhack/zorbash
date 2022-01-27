import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_miss_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(75)
    mytp.set_ai_detect_secret_doors(True)
    mytp.set_ai_resent_count(20)
    mytp.set_ai_shove_chance_d1000(500)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_attack_undead(True)
    mytp.set_capacity_height(10)
    mytp.set_capacity_width(10)
    mytp.set_collateral_damage_pct(50)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_type("claw")
    mytp.set_damage_natural_dice("1d4+2")
    mytp.set_distance_avoid(5)
    mytp.set_distance_jump(3)
    mytp.set_distance_leader_max(5)
    mytp.set_distance_recruitment_max(7)
    mytp.set_distance_vision(7)
    mytp.set_environ_avoids_acid(100)
    mytp.set_environ_avoids_fire(10)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("2d6")
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(95)
    mytp.set_is_able_to_attack_mobs(True)
    mytp.set_is_able_to_break_down_doors(True)
    mytp.set_is_able_to_break_out_of_webs(True)
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_collect_keys(True)
    mytp.set_is_able_to_enchant_items(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_follow(True)
    mytp.set_is_able_to_jump(True)
    mytp.set_is_able_to_learn_skills(True)
    mytp.set_is_able_to_move_diagonally(True)
    mytp.set_is_able_to_open_doors(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_shove(True)
    mytp.set_is_able_to_tire(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_bony(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_explorer(True)
    mytp.set_is_green_blooded(True)
    mytp.set_is_hittable(True)
    mytp.set_is_humanoid(True)
    mytp.set_is_item_carrier(True)
    mytp.set_is_item_collector(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_steal_item_chance_d1000(50)
    mytp.set_is_tickable(True)
    mytp.set_long_text_description("A very lesser minion of Zorbash, Zorblins are small, green skinned beings that lair in caves, abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders like you. However, they usually carry some meagre amounts of gold, dug out from the depths with their bare, shaking hands. Best to find out...")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("zorb_all.on_death()")
    mytp.set_on_death_drop_all_items(True)
    mytp.set_on_you_are_hit_but_still_alive_do("zorb_all.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_miss_do("zorb_all.on_you_miss_do()")
    mytp.set_on_you_natural_attack_do("zorb_all.on_you_natural_attack()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_att_penalty_when_idle(0)
    mytp.set_stat_att_penalty_when_idle_max(0)
    mytp.set_stat_att_penalty_when_in_deep_water(5)
    mytp.set_stat_att_penalty_when_in_shallow_water(2)
    mytp.set_stat_att_penalty_when_stuck(5)
    mytp.set_stat_att_penalty_when_stuck_max(5)
    mytp.set_stat_con(10)
    mytp.set_stat_def(10)
    mytp.set_stat_def_penalty_when_idle(5)
    mytp.set_stat_def_penalty_when_idle_max(5)
    mytp.set_stat_def_penalty_when_in_deep_water(5)
    mytp.set_stat_def_penalty_when_in_shallow_water(2)
    mytp.set_stat_def_penalty_when_stuck(10)
    mytp.set_stat_def_penalty_when_stuck_max(15)
    mytp.set_stat_dex(10)
    mytp.set_stat_str(8)
    mytp.set_text_a_or_an("a")
    mytp.set_text_hits("claws")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)
    return mytp
