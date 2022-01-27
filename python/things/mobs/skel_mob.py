import my
import tp


def on_idle_tick_frequency_dice(me, x, y):
    #
    # Make sure to only spawn minions so they have the is_minion flag set
    #
    if my.pcg_randint(1, 100) < 10:
        if my.level_spawn_next_to(me, "skel_minion_fire"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_BIRTH, "bones1")
    elif my.pcg_randint(1, 100) < 10:
        if my.level_spawn_next_to(me, "skel_minion_wander"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_BIRTH, "bones1")
    else:
        if my.level_spawn_next_to(me, "skel_minion"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_BIRTH, "bones2")


def on_death(me, x, y):
    if my.non_pcg_randint(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")
    my.level_spawn_at_thing(me, "mob_explosion")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_shove_chance_d1000(200)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(5)
    mytp.set_damage_received_doubled_from_water(True)
    mytp.set_environ_avoids_water(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("3d6")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_always_hit(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_burnable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_loggable(True)
    mytp.set_is_mob_challenge_class_a(True)
    mytp.set_is_mob(True)
    mytp.set_is_obs_destructable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_light_color("cyan")
    mytp.set_light_power(1)
    mytp.set_long_text_description("A grave portal from which the dead crawl out.")
    mytp.set_minion_limit(4)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_idle_tick_frequency_dice("1d10+10:me.on_idle_tick_frequency_dice()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("The dead rise again here.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)

    mytp.update()


def init():
    tp_init(name="skel_mob", text_name="skeleton mobber")


init()
