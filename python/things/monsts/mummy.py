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
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_resent_count(mytp, 100)
    my.tp_set_ai_shove_chance_d1000(mytp, 200)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_living(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_attack_meat(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_chance_d1000(mytp, 950)
    my.tp_set_damage_natural_attack_type(mytp, "claw")
    my.tp_set_damage_natural_dice(mytp, "1d6+10")
    my.tp_set_damage_necrosis_chance_d1000(mytp, 50)
    my.tp_set_damage_necrosis_dice(mytp, "1")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_damage_received_doubled_from_water(mytp, True)
    my.tp_set_distance_vision(mytp, 5)
    my.tp_set_environ_avoids_fire(mytp, 100)
    my.tp_set_environ_avoids_water(mytp, 100)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "2d20")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_hunger_is_insatiable(mytp, True)
    my.tp_set_is_able_to_change_levels(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_shove(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_fearless(mytp, True)
    my.tp_set_is_green_blooded(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_cold(mytp, True)
    my.tp_set_is_immune_to_necrosis(mytp, True)
    my.tp_set_is_immune_to_poison(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_monst_class_b(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_necrotic_danger_level(mytp, 1)  # danger level
    my.tp_set_is_red_blood_eater(mytp, True)
    my.tp_set_is_resurrectable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_undead(mytp, True)
    my.tp_set_long_text_description(mytp, "Possibly the corpse of one who ventured into this dungeon before. All life is gone now, and what remains is a corpse wrapped in rags. Death is no release for this poor creature. Watch out for its necrotic touch!")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 50)
    my.tp_set_noise_on_moving_or_being_carried(mytp, 5)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_resurrect_dice(mytp, "1d10+30")
    my.tp_set_stat_con(mytp, 15)
    my.tp_set_stat_def(mytp, 11)
    my.tp_set_stat_dex(mytp, 10)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 16)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A staggering corpse, covered in tissue paper.")
    my.tp_set_text_hits(mytp, "claws")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)

    delay = 50
    my.tp_set_tile(mytp, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    delay = 200
    my.tp_set_tile(mytp, tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(
        tile=name + ".1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="mummy", text_name="mummy")


init()
