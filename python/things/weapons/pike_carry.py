import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_bounce_on_move(self, True)
    my.gfx_equip_carry_anim(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.is_gfx_anim_synced_with_owner(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy shining pointy mechanism of justice.")
    my.z_depth(self, my.MAP_DEPTH_EQUIP)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    # This should be synced with its owner, but just in case it is not, we have delay set
    delay = 900
    my.tile(self, tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self, tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self, tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self, tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self, tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self, tile=name + ".6", delay_ms=delay, frame=6)

    my.tp_update(self)


def init():
    tp_init(name="pike_carry")


init()
