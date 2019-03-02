import zx
import tp

def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_has_hunger_tick_every_rounds(10)
    x.set_has_initial_health(10)
    x.set_is_active(True)
    x.set_is_animated(True)
    x.set_is_hungry_at_health_pct(70)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_is_outlined(True)
    x.set_is_small_shadow_caster(True)
    x.set_is_starving_at_health_pct(10)
    x.set_scent_distance(30)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 100
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)

def init():
    tp_init(name="slime1", short_name="slime1")

init()
