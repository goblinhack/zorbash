import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.is_floating(self, True)
    my.is_tickable(self, True)
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="nothing")
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".7", delay_ms=100, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="pot_health_effect")


init()
