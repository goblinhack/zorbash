import my
import tp
import _common_sword_swing


def tp_init(name):
    self = tp.Tp(name)
    # start sort marker
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated_can_vflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_attack_anim(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    _common_sword_swing.init(self, name)
    my.tp_update(self)


def init():
    tp_init(name="shovel_swing")


init()
