import zx
import tp

def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_has_hunger_tick_every_rounds(10)
    x.set_has_initial_health(20)
    x.set_is_active(True)
    x.set_is_animated(True)
    x.set_is_blit_y_offset(True)
    x.set_is_blitted_as_sitting_on_the_ground(True)
    x.set_is_hungry_at_health_pct(70)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_is_outlined(True)
    x.set_is_small_shadow_caster(True)
    x.set_is_starving_at_health_pct(10)
    x.set_scent_distance(30)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay=150
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)

def init():
    tp_init(name="slime2", short_name="slime2")

init()
