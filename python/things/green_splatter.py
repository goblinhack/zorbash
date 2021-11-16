import my
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
    mytp.set_is_loggable(False)
    mytp.set_is_loggable(False)
    mytp.set_is_moveable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Splat attack.")
    mytp.set_z_depth(my.MAP_DEPTH_EQUIP)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 10
    mytp.set_tile("green_splatter.1", delay_ms=delay)
    mytp.set_tile("green_splatter.2", delay_ms=delay)
    mytp.set_tile("green_splatter.3", delay_ms=delay)
    mytp.set_tile("green_splatter.4", delay_ms=delay)
    mytp.set_tile("green_splatter.5", delay_ms=delay)
    mytp.set_tile("green_splatter.6", delay_ms=delay)
    mytp.set_tile("green_splatter.7", delay_ms=delay)
    mytp.set_tile("green_splatter.8", delay_ms=delay)
    mytp.set_tile("green_splatter.9", delay_ms=delay)
    mytp.set_tile("green_splatter.10", delay_ms=delay)
    mytp.set_tile("green_splatter.11", delay_ms=delay)
    mytp.set_tile("green_splatter.12", delay_ms=delay)
    mytp.set_tile("green_splatter.13", delay_ms=delay)
    mytp.set_tile("green_splatter.14", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="green_splatter", text_name="green slime splatter")

init()
