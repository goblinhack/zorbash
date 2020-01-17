import zx
import tp


def tp_init(name, real_name):
    x = tp.Tp(name, real_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_large_shadow_caster(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_door(True)
    x.set_is_interesting(True)
    x.set_is_loggable(True)
    x.set_z_depth(zx.MAP_DEPTH_EXIT)

    x.set_tile(tile=name + ".1-closed")

    x.update()

def init():
    tp_init(name="door1", real_name="door")

init()
