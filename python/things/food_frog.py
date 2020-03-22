import zx
import tp


def tp_init(name, real_name):
    x = tp.Tp(name, real_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_food(True)
    x.set_is_interesting(True)
    x.set_is_nutrition_hd("1d4")
    x.set_a_or_an_prefix("a");
    x.set_stats_health_initial(4)
    x.set_z_depth(zx.MAP_DEPTH_ITEM)

    x.set_tile(tile=name, is_hp_100_percent=True)
    x.update()

def init():
    tp_init(name="food_frog1", real_name="chocolate frog")

init()
