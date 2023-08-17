import my
import tp


def on_idle_tick_freq_dice(me, x, y):
    if my.thing_is_frozen(me):
        return

    if my.spawn_minion_next_to(me, "random_zorblin"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_BIRTH, "bones1")


def on_death(me, x, y):
    if my.py_non_pcg_random_range_inclusive(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")
    my.spawn_at_my_position(me, "mob_explosion")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.chance_d1000_shove(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 5)
    my.dmg_received_doubled_from_water(self, True)
    my.environ_hates_water(self, 100)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "3d6")
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_fire(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_mob_challenge_class_B(self, True)
    my.is_mob(self, True)
    my.is_totem(self, True)
    my.is_obs_destructable(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 1)
    my.minion_limit(self, 4)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d10+10:me.on_idle_tick_freq_dice()")
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A tall pillar smeared in grease and blood and with the grinning face of a monstrous zorblin carved into the stonework. It's eyes follow you. They really do, this is not a figure of speech.")
    my.text_description_short(self, "Goblin holy place.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MOB)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="neuter", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="neuter", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="neuter", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_totem", text_long_name="zorblin totem")


init()
