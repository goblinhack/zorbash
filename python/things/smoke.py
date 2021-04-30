import zx
import tp

def on_fall(me, x, y):
    zx.thing_killed(me, "dissipated")

def tp_init(name):
    x = tp.Tp(name)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True) # for lifespan tick
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_removeable_if_out_of_slots(True)
    x.set_is_smoke(True)
    x.set_on_fall_do("smoke.on_fall()")
    x.set_text_a_or_an("");
    x.set_text_description("Whisps of smoke.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 150
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay)
    x.set_tile(tile=name + ".15", delay_ms=delay)
    x.set_tile(tile=name + ".16", delay_ms=delay)
    x.set_tile(tile=name + ".17", delay_ms=delay)
    x.set_tile(tile=name + ".18", delay_ms=delay)
    x.set_tile(tile=name + ".19", delay_ms=delay)

    x.update()

def init():
    tp_init(name="smoke")

init()
