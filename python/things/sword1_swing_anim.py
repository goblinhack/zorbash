import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_is_active(True)
    x.set_is_animated(True)
    x.set_is_animated_can_hflip(True)
    x.set_is_animated_can_vflip(True)
    x.set_is_blit_y_offset(True)
    x.set_is_movable(True)
    x.set_is_outlined(True)
    x.set_is_small_shadow_caster(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 20
    x.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_left=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_right=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_up=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_down=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
   
def init():
    tp_init(name="sword1_use_anim", short_name="sword1_use_anim")

init()
