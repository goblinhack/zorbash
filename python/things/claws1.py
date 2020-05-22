import zx
import tp


def init1(name):
    real_name = "claw attack"
    x = tp.Tp(name, real_name)

    x.set_a_or_an("a");
    x.set_is_gfx_animated(True)
    x.set_is_gfx_animated_can_hflip(True)
    x.set_is_gfx_animated_can_vflip(True)
    x.set_is_gfx_dead_anim(False)
    x.set_is_gfx_attack_anim(True)
    x.set_is_gfx_show_outlined(True)
    x.set_is_loggable(False)
    x.set_is_movable(True)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 10
    x.set_tile(tile=name + ".11", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".13", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".15", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".17", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".19", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".21", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".23", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".52", delay_ms=delay, is_dir_left=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".11", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".13", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".15", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".17", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".19", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".21", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".23", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".52", delay_ms=delay, is_dir_right=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".11", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".13", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".15", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".17", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".19", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".21", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".23", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".52", delay_ms=delay, is_dir_up=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".11", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".13", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".15", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".17", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".19", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".21", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".23", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".52", delay_ms=delay, is_dir_down=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()


def init():
    init1(name="claws1")

init()
