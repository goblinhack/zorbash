import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    # begin sort marker
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_anim_synced_with_owner(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_equip_carry_anim(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_loggable(self, True)
    my.is_player_bodypart_hat(self, True)
    my.is_player_bodypart(self, True)
    my.is_moveable(self, True)
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_PLAYER_HAT)
    # end sort marker

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")
    my.tile(self, tile="nothing")

    my.tile(self, tile="nothing")
    my.tp_update(self)


def init():
    tp_init(name="bodypart_hat0")


init()
