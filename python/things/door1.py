import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_combustible(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_door(True)
    x.set_is_flammable(True)
    x.set_is_interesting(True)
    x.set_is_light_blocker(True)
    x.set_is_movement_blocking(True)
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("the");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name + ".1-closed")
    x.set_tile(tile=name + ".1-open", is_open=True)

    x.update()

def init():
    tp_init(name="door1", text_name="door")

init()
