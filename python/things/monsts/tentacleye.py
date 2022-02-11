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
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 100)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_attack_meat(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_type(self, "whip")
    my.tp_set_damage_natural_dice(self, "2d6")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_distance_avoid(self, 4)
    my.tp_set_distance_vision(self, 8)
    my.tp_set_environ_avoids_fire(self, 10)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_asleep(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "19d10+76")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_change_levels(self, True)
    my.tp_set_is_able_to_fire_at(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_sleep(self, True)
    my.tp_set_is_able_to_tire(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_immune_to_water(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat_eater(self, True)
    my.tp_set_is_meat(self, True)
    my.tp_set_is_monst_class_c(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_toughness_soft(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_long_text_description(self, "A floating mass of tentacles and eyeballs. These creatures are often employed to monitor the dark and dank dungeons with their impressive vision. Beware their lightning gaze...")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 50)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stamina(self, 100)
    my.tp_set_stat_con(self, 10)
    my.tp_set_stat_def(self, 18)
    my.tp_set_stat_dex(self, 14)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 10)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A writhing mass of tentacles and eyeballs.")
    my.tp_set_text_hits(self, "slashes")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 300
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".sleeping.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".sleeping.2", is_sleeping=True, delay_ms=delay)

    my.tp_set_tile(self, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".7.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".8.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="tentacleye", text_name="lesser tentacleye")


init()
