import my
import tp


def on_fall(me, x, y):
    my.thing_dead(me, "dissipated")


def tp_init(name):
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_smoke(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # for lifespan tick
    my.tp_set_on_fall_do(mytp, "me.on_fall()")
    my.tp_set_text_a_or_an(mytp, "")
    my.tp_set_text_description(mytp, "Whisps of smoke.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".8", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".9", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".10", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".11", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".12", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".13", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".14", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".15", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".16", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".17", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".18", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".19", delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="smoke")


init()
