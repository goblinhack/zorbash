import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_attack_anim(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy wooden mechanism of justice.")
    mytp.set_z_depth(my.MAP_DEPTH_EQUIP)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    delay = 10
    mytp.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_left=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    mytp.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(
        tile=name + "_left.6",
        delay_ms=delay,
        is_dir_right=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    mytp.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_up=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )
    mytp.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(
        tile=name + "_up.6",
        delay_ms=delay,
        is_dir_down=True,
        is_end_of_anim=True,
        is_dead_on_end_of_anim=True,
    )

    mytp.update()


def init():
    tp_init(name="sword1_wood_swing")


init()
