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
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_SWING)
    # end sort marker
    _common_sword_swing.init(self, name)
    my.tp_update(self)


def init():
    tp_init(name="double_shovel_swing")


init()
