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
    mytp.set_aggression_level_pct(20)
    mytp.set_ai_resent_count(100)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_chance_d1000(900)
    mytp.set_damage_natural_attack_type("bite")
    mytp.set_damage_natural_dice("1d8+2")
    mytp.set_damage_poison_chance_d1000(100)
    mytp.set_damage_poison_dice("2d8+1")
    mytp.set_distance_avoid(3)
    mytp.set_distance_vision(3)
    mytp.set_environ_avoids_poison(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_health_initial_dice("2d12")
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(95)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_tire(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_bony(True)
    mytp.set_is_breather(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_flying(True)
    mytp.set_is_hittable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_meat(True)
    mytp.set_is_monst_class_b(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_red_blooded(True)
    mytp.set_is_tickable(True)
    mytp.set_long_text_description("A snarling mass of flying death. These creatures of the night tend to hang around the graves of the newly undead.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_miss_do("me.on_you_miss_do()")
    mytp.set_on_you_natural_attack_do("me.on_you_natural_attack()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_con(10)
    mytp.set_stat_def(13)
    mytp.set_stat_dex(16)
    mytp.set_stat_str(15)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An enormous bat.")
    mytp.set_text_hits("claws")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)

    delay = 70
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6.100", is_hp_25_percent=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()


def init():
    tp_init(name="bat_greater", text_name="huge fluffy bat")


init()
