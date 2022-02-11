import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated_can_vflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_attack_anim(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_green_splatter(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Splat attack.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 5
    my.tp_set_tile(mytp, "green_splatter.1", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.2", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.3", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.4", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.5", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.6", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.7", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.8", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.9", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.10", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.11", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.12", delay_ms=delay)
    my.tp_set_tile(mytp, "green_splatter.13", delay_ms=delay)
    mytp.set_tile(
        "green_splatter.14",
        delay_ms=delay,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    tp_init(name="green_splatter", text_name="green slime splatter")


init()
