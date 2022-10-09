import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    my.tile(self,
            tile="nothing")
    my.tile(self,
            tile=name + ".1", delay_ms=50)
    my.tile(self,
            tile=name + ".2", delay_ms=50, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="skill_devoted_thrust_effect")


init()
