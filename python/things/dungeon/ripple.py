import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_ripple(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_noise_on_born(mytp, 50)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "An ominous ripple.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 25
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7", delay_ms=delay)
    mytp.set_tile(
        tile=name + ".8",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="ripple1")
    tp_init(name="ripple2")


init()
