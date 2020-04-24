import zx
import tp

def pipe_init(name, real_name):
    x = tp.Tp(name, real_name)

    x.set_a_or_an("a");
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_pipe(True)
    x.set_is_active(True)
    x.set_is_light_strength(2)
    x.set_light_color("blue")
    x.set_z_depth(zx.MAP_DEPTH_ITEM)

    x.set_tile(tile=name)

    x.update()

def init():
    pipe_init(name="pipe", real_name="pipe")

init()
