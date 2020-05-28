import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("a");
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_is_combustible(True)
    x.set_is_food(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_interesting(True)
    x.set_nutrition_dice("1d4")
    x.set_normal_placement_rules(True)
    x.set_stats_health_initial(4)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    x.set_tile(tile=name, is_hp_100_percent=True)
    x.update()

def init():
    tp_init(name="food_frog1", text_name="chocolate frog")

init()
