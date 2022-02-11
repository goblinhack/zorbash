import my
import tp


def tp_init(name):
    self = tp.Tp(name, "bones and skin and stuff")
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bones(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Some poor creature's remnants.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)
    my.tp_update(self)


def init():
    tp_init(name="bones.1")
    tp_init(name="bones.2")
    tp_init(name="bones.3")
    tp_init(name="bones.4")
    tp_init(name="bones.5")
    tp_init(name="bones.6")


init()
