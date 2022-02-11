import my
import tp


def init_carry(name):
    self = tp.Tp(name)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_equip_carry_anim(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Thy shining pointy mechanism of justice.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 550
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)

    my.tp_update(self)


def init():
    init_carry(name="axe_carry")


init()
