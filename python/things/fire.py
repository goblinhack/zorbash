import zx
import tp

def tp_init(name):
    x = tp.Tp(name)

    x.set_gfx_animated(True)
    x.set_gfx_is_on_fire_anim(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_interesting(True)
    x.set_is_loggable(False)
    x.set_is_movable(True)
    x.set_a_or_an("");
    x.set_stats_attack_hd("1d6+1")
    x.set_stats_attack_rate_tenths(10)
    x.set_is_combustible(False)
    x.set_z_depth(zx.MAP_DEPTH_FIRE)

    delay = 75
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay)
    x.set_tile(tile=name + ".15", delay_ms=delay)
    x.set_tile(tile=name + ".16", delay_ms=delay)
    x.update()

def init():
    tp_init(name="fire")

init()
