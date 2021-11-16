import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("1d4")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_blood(True)
    mytp.set_is_interesting(True)
    mytp.set_is_loggable(False)
    mytp.set_is_loggable(False)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d4")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("An artwork comprised mainly of blood.")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".100", is_hp_100_percent=True)
    mytp.set_tile(tile=name + ".75", is_hp_75_percent=True)
    mytp.set_tile(tile=name + ".50", is_hp_50_percent=True)
    mytp.set_tile(tile=name + ".25", is_hp_25_percent=True)

    mytp.update()

def init():
    tp_init(name="floor_blood1", text_name="pool of blood")
    tp_init(name="floor_blood2", text_name="pool of blood")
    tp_init(name="floor_blood3", text_name="pool of blood")
    tp_init(name="floor_blood4", text_name="pool of blood")
    tp_init(name="floor_blood5", text_name="pool of blood")
    tp_init(name="floor_blood6", text_name="pool of blood")
    tp_init(name="floor_blood7", text_name="pool of blood")
    tp_init(name="floor_blood8", text_name="pool of blood")

init()
