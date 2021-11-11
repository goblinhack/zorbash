import zx
import tp

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_equip_carry_anim(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_tickable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy shining pointy mechanism of justice.")
    mytp.set_z_depth(zx.MAP_DEPTH_WEAPON)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 550
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="scythe_carry")

init()
