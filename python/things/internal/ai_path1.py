import my
import tp


def tp_init(name):
    self = tp.Tp(name, name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_is_debug_path(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_text_description(self, "AI path.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 50
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="ai_path1")


init()
