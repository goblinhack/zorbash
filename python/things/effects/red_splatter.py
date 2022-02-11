import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_red_splatter(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "An artwork comprised mainly of blood.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 5
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
    mytp.set_tile(
        tile=name + ".14",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="red_splatter", text_name="blood splatter")


init()
