import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_explosion(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_one_per_tile(self, True)
    my.noise_on_born(self, 21)
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    delay = 200  # too fast and you don't see it
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)
    delay = 100  # too fast and you don't see it
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".4",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="ghost_explosion")


init()
