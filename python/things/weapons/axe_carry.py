import my
import tp


def init_carry(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_anim_synced_with_owner(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_equip_carry_anim(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CARRY)
    # end sort marker

    # This should be synced with its owner, but just in case it is not, we have delay set
    delay = 900
    my.tile(self,
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self,
            tile=name + ".6", delay_ms=delay, frame=6)

    my.tp_update(self)


def init():
    init_carry(name="axe_carry")


init()
