import my
import tp
import _common_sword_swing


def init_swing(name):
    self = tp.Tp(name)
    # start sort marker
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated_can_vflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_attack_anim(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    # z_prio
    # end sort marker
    _common_sword_swing.init(self, name)
    my.tp_update(self)


def init():
    init_swing(name="axe_swing")


init()
