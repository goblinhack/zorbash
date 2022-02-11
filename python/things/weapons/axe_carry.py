import my
import tp


def init_carry(name):
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_equip_carry_anim(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Thy shining pointy mechanism of justice.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 550
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)

    my.tp_update(mytp, )


def init():
    init_carry(name="axe_carry")


init()
