import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_gfx_can_hflip(True)
    x.set_is_movable(True)
    x.set_gfx_outlined(True)
    x.set_is_weapon(True)
    x.set_short_name(short_name)
    x.set_weapon_carry_anim("sword1_carry_anim")
    x.set_weapon_use_anim("sword1_use_anim")
    x.set_weapon_use_delay_hundredths(5)
    x.set_weapon_use_distance(5)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_gfx_small_shadow_caster(True)

    x.set_tile(tile=name + ".1")

def init():
    tp_init(name="sword1", short_name="sword1")

init()
