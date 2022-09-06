import my
import tp


def tp_init(name):
    self = tp.Tp(name, "bones and skin and stuff")
    # start sort marker
    my.appearing_chance_d1000(self, 100)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_bones(self, True)
    my.is_loggable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "Some poor creature's remnants.")
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char=",", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)
    my.tp_update(self)


def init():
    tp_init(name="bones.1")
    tp_init(name="bones.2")
    tp_init(name="bones.3")
    tp_init(name="bones.4")
    tp_init(name="bones.5")
    tp_init(name="bones.6")


init()
