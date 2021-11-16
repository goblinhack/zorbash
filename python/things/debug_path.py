import my
import tp


def tp_init(name):
    text_name = "debug path"
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_debug_path(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_is_floating(True)
    mytp.set_is_moveable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("debug path.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile("ai_path1.1")

    mytp.update()

def init():
    tp_init(name="debug_path")

init()
