import zx
import tp


def tp_init(name, real_name):
    x = tp.Tp(name, real_name)

    x.set_a_or_an("a");
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_show_outlined(True)
    x.set_is_blood(True)
    x.set_is_interesting(True)
    x.set_is_loggable(False)
    x.set_is_nutrition_hd("1d4")
    x.set_stats_health_initial(4)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    x.set_tile(tile=name + ".100", is_hp_100_percent=True)
    x.set_tile(tile=name + ".75", is_hp_75_percent=True)
    x.set_tile(tile=name + ".50", is_hp_50_percent=True)
    x.set_tile(tile=name + ".25", is_hp_25_percent=True)

    x.update()

def init():
    tp_init(name="blood1", real_name="pool of blood")
    tp_init(name="blood2", real_name="pool of blood")
    tp_init(name="blood3", real_name="pool of blood")
    tp_init(name="blood4", real_name="pool of blood")

init()
