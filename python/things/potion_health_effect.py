import zx
import tp

def tp_init(name):
    x = tp.Tp(name)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_floating(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_z_depth(zx.MAP_DEPTH_EXPLOSION)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    #x.set_tile(tile="nothing")
    #x.set_tile(tile=name + ".1", delay_ms=50)
    #x.set_tile(tile=name + ".2", delay_ms=50)
    #x.set_tile(tile=name + ".3", delay_ms=50)
    #x.set_tile(tile=name + ".4", delay_ms=50, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="potion_health_effect")

init()
