import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_explosion(True)
    mytp.set_is_floating(True)
    mytp.set_is_loggable(True)
    mytp.set_is_tickable(True)
    mytp.set_noise_on_born(21)
    mytp.set_z_depth(my.MAP_DEPTH_EXPLOSION_MINOR)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)

    delay = 200  # too fast and you don't see it
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    delay = 100  # too fast and you don't see it
    mytp.set_tile(tile=name + ".2", delay_ms=delay)
    mytp.set_tile(tile=name + ".3", delay_ms=delay)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    mytp.update()


def init():
    tp_init(name="ghost_explosion")


init()
