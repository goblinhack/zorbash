import zx
import tp

def on_fall(me, x, y):
    zx.thing_killed(me, "dissipated")

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_tickable(True) # for lifespan tick
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_smoke(True)
    mytp.set_on_fall_do("smoke.on_fall()")
    mytp.set_text_a_or_an("")
    mytp.set_text_description("Whisps of smoke.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 150
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)
    mytp.set_tile(tile=name + ".3", delay_ms=delay)
    mytp.set_tile(tile=name + ".4", delay_ms=delay)
    mytp.set_tile(tile=name + ".5", delay_ms=delay)
    mytp.set_tile(tile=name + ".6", delay_ms=delay)
    mytp.set_tile(tile=name + ".7", delay_ms=delay)
    mytp.set_tile(tile=name + ".8", delay_ms=delay)
    mytp.set_tile(tile=name + ".9", delay_ms=delay)
    mytp.set_tile(tile=name + ".10", delay_ms=delay)
    mytp.set_tile(tile=name + ".11", delay_ms=delay)
    mytp.set_tile(tile=name + ".12", delay_ms=delay)
    mytp.set_tile(tile=name + ".13", delay_ms=delay)
    mytp.set_tile(tile=name + ".14", delay_ms=delay)
    mytp.set_tile(tile=name + ".15", delay_ms=delay)
    mytp.set_tile(tile=name + ".16", delay_ms=delay)
    mytp.set_tile(tile=name + ".17", delay_ms=delay)
    mytp.set_tile(tile=name + ".18", delay_ms=delay)
    mytp.set_tile(tile=name + ".19", delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="smoke")

init()
