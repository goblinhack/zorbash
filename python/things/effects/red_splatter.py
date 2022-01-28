import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_loggable(True)
    mytp.set_is_red_splatter(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An artwork comprised mainly of blood.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    delay = 5
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
    mytp.set_tile(
        tile=name + ".14",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    mytp.update()


def init():
    tp_init(name="red_splatter", text_name="blood splatter")


init()
