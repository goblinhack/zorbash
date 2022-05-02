import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile="nothing")
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".1", delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".2", delay_ms=50, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="skill_devoted_thrust_effect")


init()
