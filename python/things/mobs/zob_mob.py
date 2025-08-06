import my
import tp


def on_idle_tick_freq_dice(me, x, y):
    if my.thing_is_frozen(me):
        return
    #
    # Make sure to only spawn minions so they have the is_minion flag set
    #
    if my.spawn_next_to(me, "zoblin_minion"):
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
    my.dmg_rcv_doubled_from_water(self, True)
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
    my.health_initial_dice(self, "6d6")
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
    my.is_mob_class_C(self, True)
    my.is_mob(self, True)
    my.is_obs_destructable(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_shootable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "cyan")
    my.light_dist(self, 1)
    my.minion_limit(self, 4)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d10+10:me.on_idle_tick_freq_dice()")
    my.temperature_never_changes(self, True)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "zoblin mobs")
    my.text_apostrophize(self, "zoblin mob's")
    my.text_description_long(self, "A dark portal from which the undead crawl out.")
    my.text_description_short(self, "The undead become a bit less dead here.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MOB)
    # end sort marker

    delay = 500
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="gray",
            tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="zob_mob",
            text_long_name="zoblin generator")


init()
