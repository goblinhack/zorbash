import my
import tp


def on_born(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "teleport")


def tp_init(name):
    self = tp.Tp(name, "teleport_in")
    # begin sort marker
    my.damage_cold_chance_d1000(self, 0, 1000)
    my.damage_cold_dice(self, "2d6")
    my.damage_nat_att_type(self, "telefreeze")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.light_color(self, "cyan")
    my.light_dist(self, 2)
    my.noise_on_born(self, 100)
    my.noise_on_born(self, 50)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, -100)
    my.text_hits(self, "freezes")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_TOP)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    delay = 5
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".16", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".17", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".18", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".19", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".20", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".21", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".22", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".23", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".24", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".25", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".26", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".27", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".28", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".29", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".30", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".31", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".32", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".33", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".34", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".35", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".36", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".37", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".38", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".39", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".40", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".41", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".42", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".43", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".44", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".45", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".46", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".47", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".48", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".49", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".50", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".51", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".52", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".53", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".54", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".55", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".56", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".57", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".58", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".59", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".60", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".61", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".62", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".63", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="purple", ascii_fg_col_name="",
            tile=name + ".64",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="teleport_in")


init()
