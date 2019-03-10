import zx
import tp

def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_ai_delay_after_moving_ms(10)
    x.set_ai_scent_distance(30)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(20)
    x.set_collision_radius(0.5)
    x.set_gfx_animated(True)
    x.set_gfx_outlined(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_hunger_at_health_pct(70)
    x.set_hunger_every_rounds(10)
    x.set_hunger_initial_health_at(20)
    x.set_hunger_starving_at_health_pct(10)
    x.set_is_active(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_move_speed_ms(1500)
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
