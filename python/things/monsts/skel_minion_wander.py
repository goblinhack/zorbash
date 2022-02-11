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
    if my.non_pcg_randint(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_resent_count(mytp, 10)
    my.tp_set_ai_shove_chance_d1000(mytp, 200)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_attack_meat(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_type(mytp, "claw")
    my.tp_set_damage_natural_dice(mytp, "1d3")
    my.tp_set_damage_received_doubled_from_water(mytp, True)
    my.tp_set_distance_mob_max(mytp, 10)
    my.tp_set_distance_vision(mytp, 11)
    my.tp_set_environ_avoids_water(mytp, 100)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "3")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_shove(mytp, True)
    my.tp_set_is_able_to_use_weapons(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_bony(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_fearless(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_acid(mytp, True)
    my.tp_set_is_immune_to_cold(mytp, True)
    my.tp_set_is_immune_to_necrosis(mytp, True)
    my.tp_set_is_immune_to_poison(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_minion(mytp, True)
    my.tp_set_is_monst_class_a(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_red_blood_eater(mytp, True)
    my.tp_set_is_resurrectable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_undead(mytp, True)
    my.tp_set_long_text_description(mytp, "A collection of tortured bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 50)
    my.tp_set_noise_on_moving_or_being_carried(mytp, 25)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_resurrect_dice(mytp, "1d20+30")
    my.tp_set_stat_con(mytp, 9)
    my.tp_set_stat_def(mytp, 13)
    my.tp_set_stat_dex(mytp, 14)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 10)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "The bones of one surprised to be moving again.")
    my.tp_set_text_hits(mytp, "claws")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(mytp, "skeleton.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_left=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_left=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_up=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_up=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_down=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_down=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_right=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_right=True, delay_ms=delay)

    my.tp_set_tile(mytp, "skeleton.1", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4", is_dir_none=True, delay_ms=delay)

    delay = 20
    my.tp_set_tile(mytp, "skeleton.1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tp_set_tile(mytp, "skeleton.4.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.3.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(mytp, "skeleton.2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(
        "skeleton.1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="skel_minion_wander", text_name="skeleton")


init()
