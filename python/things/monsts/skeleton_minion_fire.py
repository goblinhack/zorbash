import my
import tp

def on_you_bite_attack(me, x, y):
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
    if my.non_pcg_randint(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_resent_count(10)
    mytp.set_ai_shove_chance_d1000(200)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_check(True)
    mytp.set_damage_bite_chance_d1000(100)
    mytp.set_damage_bite_dice("1d4")
    mytp.set_damage_melee_chance_d1000(900)
    mytp.set_damage_melee_dice("1d3")
    mytp.set_damage_received_doubled_from_water(True)
    mytp.set_distance_minion_leash(12)
    mytp.set_distance_minion_vision_centered_on_manifestor(True)
    mytp.set_distance_vision(13)
    mytp.set_environ_avoids_water(100)
    mytp.set_environ_avoids_water(True)
    mytp.set_environ_prefers_fire(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("4")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_shove(True)
    mytp.set_is_able_to_use_weapons(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_bony(True)
    mytp.set_is_carrier_of_treasure_class_a(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_fearless(True)
    mytp.set_is_hittable(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_loggable(True)
    mytp.set_is_minion(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_resurrectable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_undead(True)
    mytp.set_is_weapon_equiper(True)
    mytp.set_light_color("yellow")
    mytp.set_light_strength(2)
    mytp.set_long_text_description("A collection of burning tortured bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("skeleton_minion_fire.on_death()")
    mytp.set_on_you_are_hit_but_still_alive_do("skeleton_minion_fire.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_bite_attack_do("skeleton_minion_fire.on_you_bite_attack()")
    mytp.set_on_you_miss_do("skeleton_minion_fire.on_you_miss_do()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_resurrect_dice("1d20+30")
    mytp.set_stat_armor_class(15)
    mytp.set_stat_attack_bonus(10) # 10, means no bonus
    mytp.set_stat_constitution(9)
    mytp.set_stat_dexterity(14)
    mytp.set_stat_strength(10)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("The burning bones of one surprised to be moving again and literally on fire.")
    mytp.set_text_hits("claws")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile("skeleton_fire.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_left=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_up=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_down=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_right=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_none=True, delay_ms=delay)

    delay = 20
    mytp.set_tile("skeleton_fire.1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    mytp.set_tile("skeleton_fire.4.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="skeleton_minion_fire", text_name="firey skeleton")

init()
