import my
import tp


def init_carry(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_equip_carry_anim(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy shining pointy mechanism of justice.")
    mytp.set_z_depth(my.MAP_DEPTH_EQUIP)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 550
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)

    mytp.update()


def init():
    init_carry(name="axe_carry")


init()
