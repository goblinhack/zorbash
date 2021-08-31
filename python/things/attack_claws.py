import zx
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_attack_anim(True)
    mytp.set_gfx_dead_anim(False)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_is_moveable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Claw attack.")
    mytp.set_z_depth(zx.MAP_DEPTH_WEAPON)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 5
    mytp.set_tile(tile=name + ".1", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, is_dir_left=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.set_tile(tile=name + ".1", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, is_dir_right=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.set_tile(tile=name + ".1", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, is_dir_up=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.set_tile(tile=name + ".1", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, is_dir_down=True, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.update()


def init():
    tp_init(name="attack_claws", text_name="claw attack")

init()
