import my
import tp


def tp_init(name):
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_equip_carry_anim(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_gfx_anim_synced_with_owner(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_EQUIP)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)

    # This should be synced with its owner, but just in case it is not, we have delay set
    delay = 900
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, frame=1)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, frame=2)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, frame=3)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay, frame=4)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay, frame=5)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay, frame=6)

    my.tp_update(mytp, )


def init():
    tp_init(name="armor_lather_carry")


init()
