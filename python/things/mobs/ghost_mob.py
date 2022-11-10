import my
import tp


def on_idle_tick_freq_dice(me, x, y):
    #
    # Make sure to only spawn minions so they have the is_minion flag set
    #
    my.spawn_next_to(me, "ghost_minion")


def on_death(me, x, y):
    my.spawn_at_my_position(me, "mob_explosion")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.ai_shove_chance_d1000(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_received_doubled_from_fire(self, True)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_fire(self, 10)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_glows(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d6")
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal_mob(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_mob_challenge_class_a(self, True)
    my.is_mob(self, True)
    my.is_obs_destructable(self, True)
    my.is_shovable(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "cyan")
    my.light_dist(self, 2)
    my.minion_limit(self, 3)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d5+5:me.on_idle_tick_freq_dice()")
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "A bone portal which spews the angry spirits of those long passed.")
    my.text_short_description(self, "A cursed pile of bones, spawning spirits.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="&", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="ghost_mob", text_long_name="ghost generator")


init()
