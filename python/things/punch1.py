import zx
import tp


def init1(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("a");
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_dead_anim(False)
    x.set_gfx_attack_anim(True)
    x.set_gfx_show_outlined(True)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_movable(True)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_text_description("Punch out")
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 20
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_down=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_up=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_left=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_right=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".1", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".3", delay_ms=delay, is_dir_none=True)
    x.set_tile(tile=name + ".2", delay_ms=delay, is_dir_none=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()


def init():
    init1(name="punch1", text_name="punch attack")

init()
