import builtins
import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_next_to(me, "small_fire")

def tp_init(name):
    x = tp.Tp(name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(100)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_on_fire_anim(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_fire(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_loggable(False)
    x.set_is_movable(True)
    x.set_is_water_hater(100)
    x.set_stats_attack_dice("1d6+1")
    x.set_idle_tick_dice("1d30+30:fire.spawn()")
    x.set_stats_attack_rate_tenths(3)
    x.set_stats_health_initial(10)
    x.set_text_a_or_an("");
    x.set_text_hits("burns");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

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
