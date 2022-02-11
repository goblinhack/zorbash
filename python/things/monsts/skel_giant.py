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
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_resent_count(10)
    mytp.set_ai_shove_chance_d1000(200)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_type("claw")
    mytp.set_damage_natural_dice("1d6")
    mytp.set_damage_received_doubled_from_water(True)
    mytp.set_distance_avoid(2)
    mytp.set_distance_vision(7)
    mytp.set_environ_avoids_water(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("10d12+50")
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_see_through_doors(True)
    mytp.set_is_able_to_shove(True)
    mytp.set_is_able_to_use_weapons(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_bony(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_fearless(True)
    mytp.set_is_heavy(True)
    mytp.set_is_hittable(True)
    mytp.set_is_immune_to_acid(True)
    mytp.set_is_immune_to_cold(True)
    mytp.set_is_immune_to_necrosis(True)
    mytp.set_is_immune_to_poison(True)
    mytp.set_is_loggable(True)
    mytp.set_is_monst_class_c(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_red_blood_eater(True)
    mytp.set_is_resurrectable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_undead(True)
    mytp.set_long_text_description("A monstrous skeleton. It towers above you. It seems unhappy. Quite what body this skeleton came from, you hope not to find out. Water and fire are your friends here with creatures like this. Watch, these can rise again!")
    mytp.set_monst_size(my.MONST_SIZE_GIANT)
    mytp.set_noise_decibels_hearing(50)
    mytp.set_noise_on_moving_or_being_carried(25)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_miss_do("me.on_you_miss_do()")
    mytp.set_on_you_natural_attack_do("me.on_you_natural_attack()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_resurrect_dice("1d20+30")
    mytp.set_stat_con(20)
    mytp.set_stat_def(17)
    mytp.set_stat_dex(10)
    mytp.set_stat_luck(10)
    mytp.set_stat_str(21)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A monstrous skeleton, possibly unfriendly.")
    mytp.set_text_hits("claws")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)

    delay = 20
    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    mytp.set_tile(tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(
        tile=name + ".1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    mytp.update()


def init():
    tp_init(name="skel_giant", text_name="giant skeleton")


init()
