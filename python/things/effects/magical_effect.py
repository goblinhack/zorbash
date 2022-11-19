import my
import tp


def on_born(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_b")


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.is_explosion(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.noise_on_born(self, 50)
    my.on_born_do(self, "me.on_born()")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 100
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
            tile=name + ".8",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="magical_effect")


init()
