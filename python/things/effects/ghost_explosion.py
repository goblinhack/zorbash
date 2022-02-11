import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_explosion(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_noise_on_born(self, 21)
    my.tp_set_z_depth(self, my.MAP_DEPTH_EXPLOSION_MINOR)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 200  # too fast and you don't see it
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    delay = 100  # too fast and you don't see it
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self,
        tile=name + ".4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="ghost_explosion")


init()
