import zx
import tp


def tp_init(name):
    x = tp.Tp(name, "some bones and skin and stuff")
    x.set_gfx_show_outlined(True)
    x.set_is_able_to_fall(True)
    x.set_is_bones(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_removeable_if_out_of_slots(True)
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a")
    x.set_text_description("Some poor creature's remants.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name)
    x.update()

def init():
    tp_init(name="bones.1")
    tp_init(name="bones.2")
    tp_init(name="bones.3")
    tp_init(name="bones.4")
    tp_init(name="bones.5")
    tp_init(name="bones.6")

init()
