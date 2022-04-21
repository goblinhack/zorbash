import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_explosion(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.noise_on_born(self, 21)
    my.z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 200  # too fast and you don't see it
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".1", delay_ms=delay)
    delay = 100  # too fast and you don't see it
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            tile=name + ".4",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="ghost_explosion")


init()
