import zx
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_tickable(True) # for lifespan tick
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_lifespan_dice("1d10+10")
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An artwork comprised mainly of green slime.")
    mytp.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile="green_splatter.14")

    mytp.update()

def init():
    tp_init(name="green_splatter", text_name="green slime splatter")

init()
