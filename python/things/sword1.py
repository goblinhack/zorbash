import zx
import tp


def my_init(name, short_name):
    x = tp.Tp(name)

    x.set_short_name(short_name)
    x.set_is_animated(True)
    x.set_is_movable(True)
    x.set_is_weapon(True)
    x.set_is_animated_walk_flip(True)
    x.set_is_outlined(True)
    x.set_weapon_swing_distance(5)
    x.set_weapon_carry_anim("sword1_carry_anim")
    x.set_weapon_fire_delay_hundredths(5)
    x.set_weapon_swing_anim("sword1_swing_anim")
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_tile(tile=name + ".1")

def init():
    my_init(name="sword1", short_name="sword1")

init()
