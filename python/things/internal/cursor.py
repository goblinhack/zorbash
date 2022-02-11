import my
import tp


def tp_init(name):
    text_name = "cursor"
    self = tp.Tp(name, text_name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_cursor(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_tmp_thing(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "Cursor.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    delay = 50
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".7", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".8", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".9", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".10", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".11", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".12", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cursor")


init()
