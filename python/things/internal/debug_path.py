import my
import tp


def tp_init(name):
    text_name = "debug path"
    self = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_is_debug_path(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "debug path.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, "ai_path1.1")

    my.tp_update(self)


def init():
    tp_init(name="debug_path")


init()
