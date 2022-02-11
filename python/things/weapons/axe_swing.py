import my
import tp


def init_swing(name):
    mytp = tp.Tp(name)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated_can_vflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_attack_anim(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_tmp_thing(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Thy shining pointy mechanism of justice.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 10
    my.tp_set_tile(mytp, tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    my.tp_set_tile(mytp, tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_left=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(mytp, tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    my.tp_set_tile(mytp, tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_right=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(mytp, tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    my.tp_set_tile(mytp, tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_up=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    my.tp_set_tile(mytp, tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    my.tp_set_tile(mytp, tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_down=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    my.tp_update(mytp, )


def init():
    init_swing(name="axe_swing")


init()
