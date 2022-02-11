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
    self = tp.Tp(name, text_name)
    my.tp_set_ai_shove_chance_d1000(self, 200)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 5)
    my.tp_set_damage_received_doubled_from_water(self, True)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "3d6")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_always_hit(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_mob_challenge_class_a(self, True)
    my.tp_set_is_mob(self, True)
    my.tp_set_is_obs_destructable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_light_color(self, "cyan")
    my.tp_set_light_power(self, 1)
    my.tp_set_long_text_description(self, "A grave portal from which the dead crawl out.")
    my.tp_set_minion_limit(self, 4)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_idle_tick_frequency_dice(self, "1d10+10:me.on_idle_tick_frequency_dice()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "The dead rise again here.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="skel_mob", text_name="skeleton mobber")


init()
