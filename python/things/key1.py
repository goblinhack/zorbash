import zx
import tp


def key_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("an");
    x.set_gfx_animated(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gfx_bounce_always(True)
    x.set_is_interesting(True)
    x.set_is_key(True)
    x.set_is_light_strength(2)
    x.set_is_movable(True)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=100)

    x.update()

def init():
    key_init(name="key1", text_name="key")

init()
