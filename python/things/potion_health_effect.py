import my
import tp

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_tickable(True)
    mytp.set_is_floating(True)
    mytp.set_is_loggable(False)
    mytp.set_is_loggable(False)
    mytp.set_z_depth(my.MAP_DEPTH_EXPLOSION_MINOR)
    mytp.set_z_prio(my.MAP_PRIO_INFRONT)

    mytp.set_tile(tile="nothing")
    mytp.set_tile(tile=name + ".1", delay_ms=50)
    mytp.set_tile(tile=name + ".2", delay_ms=100)
    mytp.set_tile(tile=name + ".3", delay_ms=100)
    mytp.set_tile(tile=name + ".4", delay_ms=100)
    mytp.set_tile(tile=name + ".5", delay_ms=100)
    mytp.set_tile(tile=name + ".6", delay_ms=100)
    mytp.set_tile(tile=name + ".7", delay_ms=100, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="potion_health_effect")

init()
