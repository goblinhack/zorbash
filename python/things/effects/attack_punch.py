import my
import tp


def init1(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated_can_vflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_attack_anim(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Punch out.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 10
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_dir_down=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_dir_up=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_dir_left=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_dir_right=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, is_dir_none=True)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, is_dir_none=True)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, is_dir_none=True)
    mytp.set_tile(
        tile=name + ".4",
        delay_ms=delay,
        is_dir_none=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    init1(name="attack_punch", text_name="punch attack")


init()
