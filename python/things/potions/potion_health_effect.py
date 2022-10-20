import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_floating(self, True)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile="nothing")
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=50)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".6", delay_ms=100)
    my.tile(self,
            ascii_fg_char="block", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".7", delay_ms=100, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="potion_health_effect")


init()
