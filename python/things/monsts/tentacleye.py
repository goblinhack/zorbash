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


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 10) < 3:
        my.thing_fire_at(me, "laser_energy", target)
        return True
    return False


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_resent_count(mytp, 100)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_attack_meat(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_natural_attack_type(mytp, "whip")
    my.tp_set_damage_natural_dice(mytp, "2d6")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_distance_avoid(mytp, 4)
    my.tp_set_distance_vision(mytp, 8)
    my.tp_set_environ_avoids_fire(mytp, 10)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_asleep(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "19d10+76")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_hunger_is_insatiable(mytp, True)
    my.tp_set_is_able_to_change_levels(mytp, True)
    my.tp_set_is_able_to_fire_at(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_sleep(mytp, True)
    my.tp_set_is_able_to_tire(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_poison(mytp, True)
    my.tp_set_is_immune_to_water(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_meat(mytp, True)
    my.tp_set_is_monst_class_c(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_toughness_soft(mytp, True)
    my.tp_set_is_undead(mytp, True)
    my.tp_set_long_text_description(mytp, "A floating mass of tentacles and eyeballs. These creatures are often employed to monitor the dark and dank dungeons with their impressive vision. Beware their lightning gaze...")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 50)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_firing_at_something_do(mytp, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(mytp, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(mytp, "me.on_you_natural_attack()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stamina(mytp, 100)
    my.tp_set_stat_con(mytp, 10)
    my.tp_set_stat_def(mytp, 18)
    my.tp_set_stat_dex(mytp, 14)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 10)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A writhing mass of tentacles and eyeballs.")
    my.tp_set_text_hits(mytp, "slashes")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 300
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
    my.tp_set_tile(mytp, tile=name + ".sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".sleeping.2", is_sleeping=True, delay_ms=delay)

    my.tp_set_tile(mytp, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".8.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="tentacleye", text_name="lesser tentacleye")


init()
