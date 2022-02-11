import my
import tp


def tp_init(name):
    mytp = tp.Tp(name, "bones and skin and stuff")
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bones(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Some poor creature's remnants.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)
    my.tp_update(mytp, )


def init():
    tp_init(name="bones.1")
    tp_init(name="bones.2")
    tp_init(name="bones.3")
    tp_init(name="bones.4")
    tp_init(name="bones.5")
    tp_init(name="bones.6")


init()
