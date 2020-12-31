import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_animated_can_vflip(True)
    x.set_gfx_show_outlined(True)
    x.set_is_able_to_fall(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_blood(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_removable_if_out_of_slots(True)
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d4")
    x.set_stats_health_initial(4)
    x.set_text_a_or_an("a");
    x.set_text_description("An artwork comprised mainly of blood")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".100", is_hp_100_percent=True)
    x.set_tile(tile=name + ".75", is_hp_75_percent=True)
    x.set_tile(tile=name + ".50", is_hp_50_percent=True)
    x.set_tile(tile=name + ".25", is_hp_25_percent=True)

    x.update()

def init():
    tp_init(name="floor_blood1", text_name="pool of blood")
    tp_init(name="floor_blood2", text_name="pool of blood")
    tp_init(name="floor_blood3", text_name="pool of blood")
    tp_init(name="floor_blood4", text_name="pool of blood")

init()
