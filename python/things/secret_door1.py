import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("a");
    x.set_is_cursor_can_hover_over(True)
    x.set_is_light_blocker(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_interesting(True)
    x.set_is_secret_door(True)
    x.set_normal_placement_rules(True)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    x.set_tile(tile=name + ".1-closed")

    x.update()

def init():
    tp_init(name="secret_door1", text_name="secret door")

init()
