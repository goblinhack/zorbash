import zx
import tp

def tp_init(name):
    x = tp.Tp(name)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(False)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_floating(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_z_depth(zx.MAP_DEPTH_EXPLOSION)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile="nothing")
    x.set_tile(tile=name + ".1", delay_ms=100)
    x.set_tile(tile=name + ".2", delay_ms=100)
    x.set_tile(tile=name + ".3", delay_ms=100)
    x.set_tile(tile=name + ".4", delay_ms=100)
    x.set_tile(tile=name + ".5", delay_ms=100)
    x.set_tile(tile=name + ".6", delay_ms=100)
    x.set_tile(tile=name + ".7", delay_ms=100)
    x.set_tile(tile=name + ".8", delay_ms=100)
    x.set_tile(tile=name + ".9", delay_ms=100)
    x.set_tile(tile=name + ".10", delay_ms=100)
    x.set_tile(tile=name + ".11", delay_ms=100)
    x.set_tile(tile=name + ".12", delay_ms=100)
    x.set_tile(tile=name + ".13", delay_ms=100)
    x.set_tile(tile=name + ".14", delay_ms=100)
    x.set_tile(tile=name + ".15", delay_ms=100)
    x.set_tile(tile=name + ".16", delay_ms=100, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="explosion1")

init()
