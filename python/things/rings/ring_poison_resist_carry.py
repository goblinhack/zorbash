import my
import tp

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_equip_carry_anim(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_gfx_anim_synced_with_owner(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Mighty ring of poison resist.")
    mytp.set_z_depth(my.MAP_DEPTH_EQUIP)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)

    # This should be synced with its owner, but just in case it is not, we have delay set
    delay = 900
    mytp.set_tile(tile=name + ".1", delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, frame=6)

    mytp.update()

def init():
    tp_init(name="ring_poison_resist_carry")

init()
