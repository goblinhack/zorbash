import my
import tp


def init_carry(name):
    self = tp.Tp(name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_equip_carry_anim(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy shining pointy mechanism of justice.")
    my.z_depth(self, my.MAP_DEPTH_EQUIP)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 550
    my.tile(self, tile=name + ".1", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)

    my.tp_update(self)


def init():
    init_carry(name="axe_carry")


init()
