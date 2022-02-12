import my
import tp


def tp_init(name):
    text_name = "debug path"
    self = tp.Tp(name, text_name)
    my.gfx_animated(self, True)
    my.is_debug_path(self, True)
    my.is_floating(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.is_tmp_thing(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "debug path.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, "ai_path1.1")

    my.tp_update(self)


def init():
    tp_init(name="debug_path")


init()
