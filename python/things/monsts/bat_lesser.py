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
    my.tp_set_aggression_level_pct(mytp, 10)
    my.tp_set_ai_resent_count(mytp, 100)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_attack_meat(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_type(mytp, "nibble")
    my.tp_set_damage_natural_dice(mytp, "1d4+2")
    my.tp_set_distance_avoid(mytp, 3)
    my.tp_set_distance_vision(mytp, 3)
    my.tp_set_environ_avoids_poison(mytp, 100)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1d10")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_tire(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_bony(mytp, True)
    my.tp_set_is_breather(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_flying(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_water(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_meat(mytp, True)
    my.tp_set_is_monst_class_a(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_red_blooded(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_toughness_soft(mytp, True)
    my.tp_set_long_text_description(mytp, "A snarling mass of flying cuteness. They don't see so well, so best to keep far away.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 0)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stamina(mytp, 100)
    my.tp_set_stat_con(mytp, 10)
    my.tp_set_stat_def(mytp, 12)
    my.tp_set_stat_dex(mytp, 15)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 2)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A little bat.")
    my.tp_set_text_hits(mytp, "claws")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)

    delay = 70
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)

    my.tp_set_tile(mytp, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="bat_lesser", text_name="little fluffy bat")


init()
