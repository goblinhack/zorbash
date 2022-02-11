import my
import tp


def tp_init(name):
    self = tp.Tp(name)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_equip_carry_anim(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_gfx_anim_synced_with_owner(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Mighty wand.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    # This should be synced with its owner, but just in case it is not, we have delay set
    delay = 900
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay, frame=1)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay, frame=2)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay, frame=3)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay, frame=4)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay, frame=5)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay, frame=6)

    my.tp_update(self)


def init():
    tp_init(name="wand_lightning_carry")


init()
