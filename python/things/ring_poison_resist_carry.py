import zx
import tp

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_gfx_short_shadow_caster(False)
    mytp.set_gfx_equip_carry_anim(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Might ring of poison resist.")
    mytp.set_z_depth(zx.MAP_DEPTH_EQUIP)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 900
    mytp.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".dead", is_dead=True)

    mytp.update()

def init():
    tp_init(name="ring_poison_resist_carry")

init()
